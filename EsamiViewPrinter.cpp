#include "stdafx.h"
#include "Endox.h"
#include "EsamiView.h"

#include <GdiPlus.h>
#include <io.h>

#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\AmTesiSign.h"
#include "DLL_Imaging\h\ImgArchive.h"

#include "AlbumForm.h"
#include "CustomDate.h"
#include "DigitalSignUtil.h"
#include "ElemReportSet.h"
#include "EsamiChiusiSet.h"
#include "EsamiIntegratiSet.h"
#include "EspelliDlg.h"
#include "ExportWaitDlg.h"
#include "ExtMonitoraggiChiusiSet.h"
#include "FasiEsameSet.h"
#include "FieldDlg.h"
#include "FileBmp.h"
#include "MotivoDlg.h"
#include "HeaderFooterSet.h"
#include "ImageElaboration.h"
#include "ImmaginiPuntiSet.h"
#include "LogFileWriter.h"
#include "MediciSet.h"
#include "MmSystem.h"
#include "MyPrintDialog.h"
#include "OrganiSet.h"
#include "PacsArchiver.h"
#include "PdfAnteprimaDlg.h"
#include "PDFCreator.h"
#include "PdfManager.h"
#include "PdfStampaDlg.h"
#include "PuntiPazienteSet.h"
#include "PuntiSet.h"
#include "QueryDlg.h"
#include "ReportsDefaultSet.h"
#include "SediEsameSet.h"
#include "SmartCardPinDlg.h"
#include "TbLogAlbumImmaginiSet.h"
#include "TipoEsameSet.h"
#include "VistaImmaginiNumeroDermoxSet.h"
#include "WebDeployer.h"
#include "EsamiInvioAltraUnitaSet.h" //Gabriel - TCP
#include <sys/types.h>//BUG - Felipe
#include <sys/stat.h>//BUG - Felipe
#include <direct.h>


using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

/// Annulla i pdf firmati sostituendoli con un documento (firmato) di sostituzione
void CEsamiView::AnnullaDocumentiFirmati(long lIDEsame)
{
	theApp.m_sSmartCardPin = "";

	if (AmTesiSign_Initialize(theApp.m_bFirmaDigitaleDebug) != NoError)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_1), MB_ICONSTOP);
		return;
	}

	if (AmTesiSign_ReadSmartCard() != NoError)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_2), MB_ICONSTOP);
		AmTesiSign_Finalize();
		return;
	}

	// Sandro 01/03/2013 //
	INT_PTR iReturn = IDCANCEL;
	CSmartCardPinDlg dlgPin(this);
	do
	{
		iReturn = dlgPin.DoModal();
		if (iReturn == IDCANCEL)
			break;
	}
	while(AmTesiSign_ReadCertificate(dlgPin.m_strPin) != NoError);

	if (iReturn == IDCANCEL)
	{
		AmTesiSign_Finalize();
		return;
	}

	theApp.m_sSmartCardPin = dlgPin.m_strPin;

	// Sandro 21/01/2014 //
	CMotivoDlg dlgAnn(this, "Stai annullando un documento firmato digitalmente.", "Motivo per l'annullo:");
	if (dlgAnn.DoModal() == IDOK)
	{
		STRUCT_STAMPA structStampa;
		if (SelezionaFileReport(&structStampa, theApp.m_sFirmaDigitaleReportAnnullamento))
		{
			long lIdPdf = 0;

			//
			BeginWaitCursor();

			CList<long> listAnnullati;
			long lVersioneReferto = 0;
			long lIDUltimoPdf = 0;

			CPdfList plEsame;
			CPdfManager().GetPdf(lIDEsame, &plEsame);

			// annullo i referti precedenti //
			POSITION pos = plEsame.GetHeadPosition();
			while(pos != NULL)
			{
				PDF pdfTemp = plEsame.GetAt(pos);

				if ((pdfTemp.ptTipo != pdftype_report_annullativo) && pdfTemp.bFirmato && !pdfTemp.bAnnullato)
				{
					if (CPdfManager().SetPdfAnnullatoMotivo(pdfTemp.lID, m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, dlgAnn.GetMotivo()))
						listAnnullati.AddTail(pdfTemp.lID);

					if (pdfTemp.lVersioneReferto >= lVersioneReferto)
						lVersioneReferto = pdfTemp.lVersioneReferto + 1;

					if (lIDUltimoPdf == 0)
						lIDUltimoPdf = pdfTemp.lID;
				}

				plEsame.GetNext(pos);
			}

			m_listIDStampate.RemoveAll();

			CString sPdfFileComplete = "";
			if (CreateHaruPdfReportFile(sPdfFileComplete, &structStampa, FALSE,""))
			{
				long lOper = CPdfAnteprimaDlg(this, this, sPdfFileComplete, ANTEPRIMADLG_FIRMA).DoModal();
				switch(lOper)
				{
					case 0x555: // solo firma senza stampa //
					case 0x777: // firma e stampa //
					{
						lIdPdf = ArchiviaPdf(pdftype_report_annullativo, &sPdfFileComplete, structStampa.m_sReportFileOriginal, TRUE, FALSE, structStampa.m_bFitToPage, lVersioneReferto, lIDUltimoPdf);

						if (lOper == 0x777)
							CPdfStampaDlg(this, theApp.m_sFirmaDigitaleReportAnnullamento, sPdfFileComplete, FALSE, structStampa.m_lPrinterToUse, 0, structStampa.m_bFitToPage).DoModal();

						// Sandro 29/05/2014 // contrassegno le immagini stampate //
						if (m_listIDStampate.GetCount() > 0)
							m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);

						break;
					}
				}

				DeleteFile(sPdfFileComplete);
			}
			m_listIDStampate.RemoveAll();

			if (lIdPdf > 0)
			{
				// archivio su pacs //
				CPacsArchiver pa;
				pa.Archive(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, lIdPdf);

				// inserisco riga nella tabella EXT_ESAMI_CHIUSI //
				// La cancellazione ha come id pdf il pdf con la scritta annullato e come old id pdf il pdf annullato
				CEsamiChiusiSet().InserisciRecord(m_pEsamiSet->m_lContatore, lIdPdf, -1, GetUserIDForLockSuperlock(), "CA", lIDUltimoPdf);

				//
				POSITION pos = listAnnullati.GetHeadPosition();
				while(pos != NULL)
				{
					CPdfManager().SetPdfAnnullato(listAnnullati.GetAt(pos), m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, TRUE);
					listAnnullati.GetNext(pos);
				}

				//
				m_pEsamiSet->SbloccaEsame(this);
				UpdateData(FALSE);
			}
			else
			{
				// annullo l'annullamento :-) //
				POSITION pos = listAnnullati.GetHeadPosition();
				while(pos != NULL)
				{
					CPdfManager().SetPdfAnnullatoMotivo(listAnnullati.GetAt(pos), m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, "");
					listAnnullati.GetNext(pos);
				}
			}

			//
			EndWaitCursor();
		}
		else
		{
			theApp.AfxMessageBoxEndo("La voce 'Firma digitale - Report annullamento' nella tabella 'Configurazioni' non è impostata correttamente!");
		}
	}

	//
	AmTesiSign_Finalize();
}

void CEsamiView::AnteprimaStampaImmagini(UINT operazione, UINT what, long lCopies)
{
	ASSERT((operazione == STAMPA) || (operazione == ANTEPRIMA));
	ASSERT((what == LOCAL_IMAGES) || (what == GLOBAL_IMAGES));

	// Sandro 26/11/2013 //
	if ((what == LOCAL_IMAGES) && (m_pFormImmagini != NULL) && (CFileBmp::CountPrinterList(LOCAL_IMAGES) == 0) && theApp.m_bStampaSelezionaAutomaticaImmaginiStampate)
		m_pFormImmagini->SelectAlreadyPrintedImages();

	// riempio la lista delle immagini da stampare //
	long lSelectedImm = CFileBmp::FillImagesPrinterList(what);

	// controllo che siano state selezionate le immagini //
	if (lSelectedImm == 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPA_IMMAGINI_ERRORE_1));
		return;
	}

	// controllo che l'utente corrente abbia il diritto di stampare le immagini //
	if ((theApp.m_dwPrivileges & AMLogin_Permissions::printout) == 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPA_IMMAGINI_ERRORE_2));
		return;
	}

	// controllo che lo stato del programma sia "compatibile" con la stampa delle immagini //
	if (!m_bPazientiValid || m_bPazientiBusy || !m_bEsamiValid || m_bEsamiBusy)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPA_IMMAGINI_ERRORE_3));
		return;
	}

	// controllo che l'esame appartenga allo stesso distretto //
	if (!m_pEsamiSet->m_bStessoDistretto)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPA_IMMAGINI_ERRORE_4));
		return;
	}

	if (theApp.m_bPersonalizzazioniBrasileFleury && CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPA_IMMAGINI_ERRORE_5));
		return;
	}


	//
	BeginWaitCursor();

	// in modalità 1 invia le immagini DICOM stampate //
	// if (theApp.m_lDcmStoreMode == 1)
		// StoreImmOnPacs();

	// creo il PDF //
	m_listIDStampate.RemoveAll();
	CString sPdfFileComplete = CreateHaruPdfImageFile(m_pEsamiSet->m_sCodEsame);
	if (!sPdfFileComplete.IsEmpty())
	{
		BOOL bStampa = TRUE;

		if (operazione == ANTEPRIMA)
			bStampa = (CPdfAnteprimaDlg(this, NULL, sPdfFileComplete, ANTEPRIMADLG_SEMPLICE).DoModal() == IDOK);

		if (bStampa)
		{
			if (CPdfStampaDlg(this, theApp.GetMessageString(IDS_STAMPA_IMMAGINI), sPdfFileComplete, FALSE, theApp.m_lIDStampanteImmagini, lCopies, TRUE).DoModal() == IDOK)
			{
				if (theApp.m_bPDFImmaginiCrea)
					ArchiviaPdf(pdftype_images, &sPdfFileComplete, "", FALSE, FALSE, TRUE, 0, 0);

				// se necessario deseleziono le immagini //
				if (theApp.m_bAutoDeselect)
					CFileBmp::DeleteListSelected(what);

				// Sandro 29/05/2014 // contrassegno le immagini stampate //
				if (m_listIDStampate.GetCount() > 0)
					m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);
			}
		}

		DeleteFile(sPdfFileComplete);
	}
	m_listIDStampate.RemoveAll();

	// Sandro 26/11/2013 // devo refreshare l'album, ora che contrassegno le immagini stampate //
	m_pFormImmagini->SendMessage(MSG_AFTER_ELABIMAGE, (WPARAM)FALSE);

	//
	EndWaitCursor();
}

void CEsamiView::AnteprimaStampaReport(UINT operazione, BOOL bVerificaCampiObbligatori, CString strReportFile, BOOL bFromQueryDlg, long lCopieStampa, long* lGeneratedPdfId, CString codEsame)
{
	//Gabriel - TCP
	ASSERT((operazione == STAMPA) || (operazione == ANTEPRIMA) || (operazione == CHIUSURA) || (operazione == CHIUSURA_FASE) || (operazione == ANTEPRIMA_NO_STAMPA) || (operazione == CHIUSURA_ESAMECORRELATI));

	// se necessario verifico i campi obbligatori //
	if (bVerificaCampiObbligatori)
		if (!VerificaCampiObbligatoriFase(CO_FASE_CHIUSURA_STAMPA))
			return;

	if (theApp.m_bPersonalizzazioniBrasileFleury && CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPA_IMMAGINI_ERRORE_5));
		return;
	}

	// preparo la struttura per tenere tutti i dati relativi al report //
	STRUCT_STAMPA structStampa;

	// faccio selezionare il report da stampare //
	BOOL bContinue = FALSE;
	if (strReportFile.IsEmpty())
		bContinue = SelezionaFileReport(&structStampa);
	else
		bContinue = SelezionaFileReport(&structStampa, strReportFile);

	if (bContinue)
	{
		BeginWaitCursor();

		// in modalità 1 invia le immagini DICOM stampate //
		// if (theApp.m_lDcmStoreMode == 1)
		// StoreImmOnPacs();		

		// m_pReportElementList = new CList<reportElement*>();

		// creo il PDF //
		m_listIDStampate.RemoveAll();

		CString sPdfFileComplete = "";
		if (bFromQueryDlg)
			sPdfFileComplete = CreateHaruPdfReportFileFromQuery(&structStampa);
		else
			CreateHaruPdfReportFile(sPdfFileComplete, &structStampa, (operazione == CHIUSURA) && theApp.m_bChiusuraEsameAccodaStampaImmagini,codEsame);
	
		//

		if (!sPdfFileComplete.IsEmpty())
		{
			BOOL bStampa = TRUE;

			switch(operazione)
			{
				case ANTEPRIMA:
				{
					bStampa = (CPdfAnteprimaDlg(this, this, sPdfFileComplete, ANTEPRIMADLG_SEMPLICE).DoModal() == IDOK);
					break;
				}
				case ANTEPRIMA_NO_STAMPA:
				{
					CPdfAnteprimaDlg(this, this, sPdfFileComplete, ANTEPRIMADLG_NO_STAMPA).DoModal();
					bStampa = FALSE;
					break;
				}
				case CHIUSURA_FASE:
				{
					long lIDPdfCheSostituisce = 0;
					long lVersioneReferto = 0;
					long lIDPdf = ArchiviaPdf(pdftype_report, &sPdfFileComplete, structStampa.m_sReportFileOriginal, FALSE, FALSE, structStampa.m_bFitToPage, lVersioneReferto, lIDPdfCheSostituisce);

					*lGeneratedPdfId = lIDPdf;

					break;
				}
				case CHIUSURA:
				{
					BOOL bProceed = TRUE;

					// Sandro 11/03/2015 // RAS 20130201 //
					if (theApp.m_bFirmaDigitaleAnteprimaMostra)
						bProceed = (CPdfAnteprimaDlg(this, this, sPdfFileComplete, ANTEPRIMADLG_CHIUSURA).DoModal() == IDOK);

					if (bProceed)
					{
						long lIDPdfCheSostituisce = 0;
						long lVersioneReferto = 0;
						CPdfManager().GetDatiUltimoPdf(m_pEsamiSet->m_lContatore, lIDPdfCheSostituisce, lVersioneReferto);
						lVersioneReferto++;

						// se sono in chiusura archivio SEMPRE il PDF //
						long lIDPdf = ArchiviaPdf(pdftype_report, &sPdfFileComplete, structStampa.m_sReportFileOriginal, FALSE, FALSE, structStampa.m_bFitToPage, lVersioneReferto, lIDPdfCheSostituisce);

						/*
						// archivio l'xml generato //
						CString xmlRerferto = AmXmlReportGenerator_CreateAndGetXmlFromList(m_pReportElementList);
						if ((lIDPdf > 0) && (xmlRerferto.GetLength() > 0))
							CPdfManager().SetDocumentoXml(lIDPdf, xmlRerferto);						
						*/

						if ((lIDPdf > 0) && (lIDPdfCheSostituisce > 0))
							CPdfManager().SetPdfSospeso(lIDPdfCheSostituisce, m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, TRUE);

						// Sandro 20/07/2015 //
						long lIDPdfImmagini = -1;
						if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (m_pFormImmagini != NULL))
						{
							// seleziono tutte le immagini //
							m_pFormImmagini->SelectAllImages();

							// riempio la lista delle immagini da stampare //
							long lSelectedImm = CFileBmp::FillImagesPrinterList(LOCAL_IMAGES);

							// controllo che siano state selezionate le immagini //
							if (lSelectedImm > 0)
							{
								// creo il PDF //
								CString sPdfFileImmagini = CreateHaruPdfImageFile(codEsame);
								if (!sPdfFileImmagini.IsEmpty())
								{
									// archivio la copia del pdf //
									lIDPdfImmagini = ArchiviaPdf(pdftype_images, &sPdfFileImmagini, "", FALSE, FALSE, TRUE, 0, 0);

									Sleep(3000);
									DeleteFile(sPdfFileImmagini);

									// Sandro 26/05/2017 // BUG 456 //

									BOOL bInviaToCarestream = FALSE;

									CString sDataOraChiusuraPrecedente = CEsamiChiusiSet().UltimaDataOraChiusura(m_pEsamiSet->m_lContatore);
									if (!sDataOraChiusuraPrecedente.IsEmpty())
									{
										if (CTbLogAlbumImmaginiSet().HasRigheDopoDataOra(m_pEsamiSet->m_lContatore, sDataOraChiusuraPrecedente))
										{
											// non è la prima volta che viene chiuso l'esame e ci sono state delle modifiche nell'album delle immagini //
											bInviaToCarestream = TRUE;
										}
									}
									else
									{
										// è la prima volta che viene chiuso l'esame //
										bInviaToCarestream = TRUE;
									}

									if(bInviaToCarestream)
										CPdfManager().SetPdfHistorical(lIDPdfImmagini, m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer);
								}
							}
						}

						// inserisco una riga nella tabella EXT_ESAMI_CHIUSI //
						CEsamiChiusiSet().InserisciRecord(m_pEsamiSet->m_lContatore, lIDPdf, lIDPdfImmagini, GetUserIDForLockSuperlock(), "NW");

						// chiudo l'esame //
						m_pEsamiSet->ChiudiEsame(m_sDataOraChiusura, (CRefertoForm*)m_pDynForm[sub_referto]);

						// Sandro 17/07/2015 // RIMA 15052 //
						if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
						{
							CString sFilterEI;
							sFilterEI.Format("IDEsamePrincipale=%li", m_pEsamiSet->m_lContatore);

							CEsamiIntegratiSet setEI;
							setEI.SetOpenFilter(sFilterEI);
							if (setEI.OpenRecordset("CEsamiView::AnteprimaStampaReport"))
							{
								while (!setEI.IsEOF())
								{
									// inserisco una riga nella tabella EXT_ESAMI_CHIUSI //
									CEsamiChiusiSet().InserisciRecord(setEI.m_lIDEsameSecondario, -1, -1, GetUserIDForLockSuperlock(), "NW");

									// chiudo l'esame //
									CEsamiSet().ChiudiEsameIntegrato(setEI.m_lIDEsameSecondario, m_sDataOraChiusura);

									//
									setEI.MoveNext();
								}

								setEI.CloseRecordset("CEsamiView::AnteprimaStampaReport");
							}
						}

						// archivio su pacs //
						CPacsArchiver pa;
						pa.Archive(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, lIDPdf);

						// Sandro 29/05/2014 // contrassegno le immagini stampate //
						if (m_listIDStampate.GetCount() > 0)
							m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);

						// Sandro 11/03/2015 // RAS 20130201 //
						switch (theApp.m_lFirmaDigitaleStampa)
						{
							case 0: // non stampa mai //
							{
								bStampa = FALSE;
								break;
							}
							case 1: // stampa sempre //
							{
								bStampa = TRUE;

								CString sMessaggio = "";
								if (theApp.m_bPersonalizzazioniBrasileFleury)
									bStampa = FleuryPossoStampare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);

								if (!bStampa)
									theApp.AfxMessageBoxEndo(sMessaggio);

								break;
							}
							default: // chiede se stampare o meno //
							{
								bStampa = (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPARE_REFERTO), MB_YESNO | MB_ICONQUESTION) == IDYES);

								if (bStampa && theApp.m_bPersonalizzazioniBrasileFleury)
								{
									CString sMessaggio = "";
									bStampa = FleuryPossoStampare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);

									if (!bStampa)
										theApp.AfxMessageBoxEndo(sMessaggio);
								}

								break;
							}
						}

						*lGeneratedPdfId = lIDPdf;
					}
					else
					{
						m_sDataOraChiusura = "";
						m_pEsamiSet->m_sDataOraSuperLock = "";
						bStampa = FALSE;
					}
					break;
				}
				//Gabriel - TCP
				case CHIUSURA_ESAMECORRELATI:
				{
					BOOL bProceed = TRUE;

					long lIDPdfCheSostituisce = 0;
					long lVersioneReferto = 0;
					CPdfManager().GetDatiUltimoPdf(m_pEsamiSet->m_lContatore, lIDPdfCheSostituisce, lVersioneReferto);
					lVersioneReferto++;

					// se sono in chiusura archivio SEMPRE il PDF //
					long lIDPdf = ArchiviaPdf(pdftype_report, &sPdfFileComplete, structStampa.m_sReportFileOriginal, FALSE, FALSE, structStampa.m_bFitToPage, lVersioneReferto, lIDPdfCheSostituisce);

					if ((lIDPdf > 0) && (lIDPdfCheSostituisce > 0))
						CPdfManager().SetPdfSospeso(lIDPdfCheSostituisce, m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, TRUE);

					// Sandro 20/07/2015 //
					long lIDPdfImmagini = -1;
					if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (m_pFormImmagini != NULL))
					{
						// seleziono tutte le immagini //
						m_pFormImmagini->SelectAllImages();

						// riempio la lista delle immagini da stampare //
						long lSelectedImm = CFileBmp::FillImagesPrinterList(LOCAL_IMAGES);

						// controllo che siano state selezionate le immagini //
						if (lSelectedImm > 0)
						{
							// creo il PDF //
							CString sPdfFileImmagini = CreateHaruPdfImageFile(m_pEsamiSet->m_sCodEsame);
							if (!sPdfFileImmagini.IsEmpty())
							{
								// archivio la copia del pdf //
								lIDPdfImmagini = ArchiviaPdf(pdftype_images, &sPdfFileImmagini, "", FALSE, FALSE, TRUE, 0, 0);

								//
								DeleteFile(sPdfFileImmagini);

								// Sandro 26/05/2017 // BUG 456 //

								BOOL bInviaToCarestream = FALSE;

								CString sDataOraChiusuraPrecedente = CEsamiChiusiSet().UltimaDataOraChiusura(m_pEsamiSet->m_lContatore);
								if (!sDataOraChiusuraPrecedente.IsEmpty())
								{
									if (CTbLogAlbumImmaginiSet().HasRigheDopoDataOra(m_pEsamiSet->m_lContatore, sDataOraChiusuraPrecedente))
									{
										// non è la prima volta che viene chiuso l'esame e ci sono state delle modifiche nell'album delle immagini //
										bInviaToCarestream = TRUE;
									}
								}
								else
								{
									// è la prima volta che viene chiuso l'esame //
									bInviaToCarestream = TRUE;
								}

								if (bInviaToCarestream)
									CPdfManager().SetPdfHistorical(lIDPdfImmagini, m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer);

								CEsamiInvioAltraUnitaSet().SetIdPdfImmagini(lIDPdfImmagini, m_pEsamiSet->m_lContatore);
							}
						}
					}

					// archivio su pacs //
					CPacsArchiver pa;
					pa.Archive(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, lIDPdf);

					// Sandro 29/05/2014 // contrassegno le immagini stampate //
					if (m_listIDStampate.GetCount() > 0)
						m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);

					bStampa = FALSE;

					*lGeneratedPdfId = lIDPdf;
				}
			}

			if (bStampa)
			{
				if (CPdfStampaDlg(this, structStampa.m_sReportFileOriginal, sPdfFileComplete, FALSE, structStampa.m_lPrinterToUse, lCopieStampa, structStampa.m_bFitToPage).DoModal() == IDOK)
				{
					if (structStampa.m_bArchivePDFCopy && (operazione != CHIUSURA)) // se sono in chiusura ho comunque già archiviato il PDF del referto //
						ArchiviaPdf(pdftype_report, &sPdfFileComplete, structStampa.m_sReportFileOriginal, FALSE, FALSE, structStampa.m_bFitToPage, 0, 0);

					if (operazione == CHIUSURA)
					{
						// controllo se devo stampare anche le immagini //
						CString strFilter;
						strFilter.Format("SedeEsame='%s' AND TipoEsame=%li AND Report = 'IMMAGINI'", CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE), m_pEsamiSet->m_lIDEsame);

						CReportsDefaultSet setRepDef;
						setRepDef.SetOpenFilter(strFilter);
						if (setRepDef.OpenRecordset("CEsamiView::OnToolbarStampaReport"))
						{
							if (!setRepDef.IsEOF())
								AnteprimaStampaImmagini(STAMPA, LOCAL_IMAGES, lCopieStampa);

							setRepDef.CloseRecordset("CEsamiView::OnToolbarStampaReport");
						}
					}

					// se necessario deseleziono le immagini //
					if (theApp.m_bAutoDeselect)
						CFileBmp::DeleteListSelected(LOCAL_IMAGES);

					if (operazione != CHIUSURA) // già fatto poche righe sopra //
					{
						// Sandro 29/05/2014 // contrassegno le immagini stampate //
						if (m_listIDStampate.GetCount() > 0)
							m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);
					}
				}
			}

			Sleep(3000);
			DeleteFile(sPdfFileComplete);
		}

		CString directory = theApp.m_sDirTemp + "\\" + codEsame;
		
		DeleteDirectory(directory);

		m_listIDStampate.RemoveAll();

		// Sandro 26/11/2013 // devo refreshare l'album, ora che contrassegno le immagini stampate //
		m_pFormImmagini->SendMessage(MSG_AFTER_ELABIMAGE, (WPARAM)FALSE);

		/*
		// pulisce l'area di memoria. Fatto manualmente perché la struttura è complessa
		AmXmlReportGenerator_ClearMemory(m_pReportElementList);

		delete(m_pReportElementList);
		m_pReportElementList = NULL;
		*/

		//
		EndWaitCursor();
	}
	else
	{
		if (!strReportFile.IsEmpty())
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_ERROR_PRINT_RGL_2), strReportFile);
			theApp.AfxMessageBoxEndo(strError);
		}
	}
}

void CEsamiView::CaricaCampiDefault()
{
	// caricamento campi default //
	CEsamiSet ProfilesSet(TRUE);

	CString strFilter;
	strFilter.Format("IDESAME=%li", m_pEsamiSet->m_lIDEsame);
	ProfilesSet.SetOpenFilter(strFilter);
	if (ProfilesSet.OpenRecordset("CEsamiView::OnEsameNew"))
	{
		if (!ProfilesSet.IsEOF())
		{
			// Azzeramento dei campi che non sono logicamente corretti da assegnare al nuovo esame
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lContatore);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lPaziente);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lData);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lMedico);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lAssistente);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lInfermiere1);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lInfermiere2);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_sProgressivoAnno);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_sCodicePrenotazione);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lIDVersione);

			// Sandro 05/12/2012 // mancavano questi due...
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lIDSedeEsame);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_sSalaEsame);

			//
			m_pEsamiSet->CopyFieldFrom(&ProfilesSet, FALSE);
			UpdateData(FALSE);
		}

		ProfilesSet.CloseRecordset("CEsamiView::OnEsameNew");
	}
}

long CEsamiView::CaricaImmaginiPunti(STRUCT_STAMPA* pStruct)
{
	CList<long> listIDOrgani;

	CObSelect* pSel;
	for(int iTmp = 0; iTmp < pStruct->m_lImageToPrint; iTmp++)
	{
		tagPunti tagTemp;
		int lIndex = -1;

		pSel = (CObSelect*)(CFileBmp::m_listPrinter.GetAt(iTmp));
		if (pSel != NULL)
		{
			tagTemp.lIdPunto = CImmaginiPuntiSet().GetIDPunto(pSel->m_lID);

			if (tagTemp.lIdPunto > 0)
			{
				CPuntiSet().GetDatiPunto(tagTemp.lIdPunto, tagTemp.lIdOrgano, tagTemp.lX, tagTemp.lY);

				BOOL bFind = FALSE;
				POSITION pos = pStruct->m_listPuntiStampa.GetHeadPosition();
				while(pos != NULL)
				{
					lIndex++;
					if (m_pFormImmagini->m_listPunti.GetAt(pos).lIdPunto == tagTemp.lIdPunto)
					{
						bFind = TRUE;
						break;
					}
					
					pStruct->m_listPuntiStampa.GetNext(pos);
				}

				if (bFind == FALSE)
				{
					pStruct->m_listPuntiStampa.AddTail(tagTemp);

					// SANDRO 03/08/2011 //
					BOOL bOrganIDFound = FALSE;
					for(int i = 0; i < listIDOrgani.GetCount(); i++)
					{
						if (listIDOrgani.GetAt(listIDOrgani.FindIndex(i)) == tagTemp.lIdOrgano)
						{
							bOrganIDFound = TRUE;
							break;
						}
					}
					if (!bOrganIDFound)
						listIDOrgani.AddTail(tagTemp.lIdOrgano);

					//
					lIndex = pStruct->m_listPuntiStampa.GetCount() - 1;
				}
			}
		}

		pStruct->m_listImmaginiStampa.AddTail(lIndex);
	}

	return listIDOrgani.GetCount();
}

long CEsamiView::ContaImmagini(CString strFileReport)
{
	long lReturn = 0;

	int	nTotSection = GetPrivateProfileInt("List", "TotSection", 0, strFileReport);
	for(int nSection = 1; nSection <= nTotSection; nSection++)
	{
		CString strSezione;
		strSezione.Format("Section%li", nSection);

		CString strTipo;
		strTipo = GetPrivateProfileString("List", strSezione, "", strFileReport);

		if (strTipo.CompareNoCase("Image") == 0)
			lReturn++;
	}

	return lReturn;
}

long CEsamiView::ContaOrgani(CString strFileReport)
{
	long lReturn = 0;

	int	nTotSection = GetPrivateProfileInt("List", "TotSection", 0, strFileReport);
	for(int nSection = 1; nSection <= nTotSection; nSection++)
	{
		CString strSezione;
		strSezione.Format("Section%li", nSection);

		CString strTipo;
		strTipo = GetPrivateProfileString("List", strSezione, "", strFileReport);

		if (strTipo.CompareNoCase("Organ") == 0)
			lReturn++;
	}

	return lReturn;
}

long CEsamiView::OnChiudiEsame()
{
	CString strReportFile = "";
	long lCopie = 0;

	// controllo se esistono dei reports di default associati all'esame //
	CString strFilter;
	strFilter.Format("SedeEsame='%s' AND TipoEsame=%li AND Report<>'IMMAGINI'", CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE), m_pEsamiSet->m_lIDEsame);

	CReportsDefaultSet setRepDef;
	setRepDef.SetOpenFilter(strFilter);
	setRepDef.SetSortRecord("ID");
	if (setRepDef.OpenRecordset("CEsamiView::OnChiudiEsame"))
	{
		if (!setRepDef.IsEOF())
		{
			strReportFile = setRepDef.m_sReport;
			lCopie = setRepDef.m_lCopie;
		}

		setRepDef.CloseRecordset("CEsamiView::OnChiudiEsame");
	}

	CString codEsame = m_pEsamiSet->m_sCodEsame;
	//
	long lGeneratedPdfId = 0;
	AnteprimaStampaReport(CHIUSURA, VERIFICA_SI, strReportFile, FALSE, lCopie, &lGeneratedPdfId, codEsame);

	return CEsamiChiusiSet().GetIdFromPdfId(lGeneratedPdfId);
}

long CEsamiView::GeneraPdfFase(long lIDFase)
{
	long lCopie = 0;

	// controllo se esistono dei reports di default associati all'esame //
	CString strReportFile = CFasiEsameSet().GetReport(lIDFase);

	//
	long lGeneratedPdfId = 0;
	AnteprimaStampaReport(CHIUSURA_FASE, VERIFICA_NO, strReportFile, FALSE, lCopie, &lGeneratedPdfId,"");



	return lGeneratedPdfId;
}

int CEsamiView::GetAltezzaHF(long lID)
{
	long m_lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	CHeaderFooterSet setHF;
	setHF.SetOpenFilter(strFilter);
	if (setHF.OpenRecordset("CEsamiView::GetAltezzaHF"))
	{
		if (!setHF.IsEOF())
			m_lReturn = setHF.m_lAltezza;

		setHF.CloseRecordset("CEsamiView::GetAltezzaHF");
	}

	return m_lReturn;
}

long CEsamiView::GetOrganIndex(int nCurOrgan, CList <tagPunti> &listPunti)
{
	int nElements = listPunti.GetCount();
	int nFound = -1;
	BOOL bAlreadyCount;

	for(int i = 0; i < nElements; i++)
	{
		bAlreadyCount = FALSE;

		POSITION pos1 = listPunti.FindIndex(i);
		if (pos1 != NULL)
		{
			for(int j = 0; j < i; j++)
			{
				POSITION pos2 = listPunti.FindIndex(j);

				if (listPunti.GetAt(pos1).lIdOrgano == listPunti.GetAt(pos2).lIdOrgano)
				{
					bAlreadyCount = TRUE;
					break;
				}
			}

			if (bAlreadyCount == FALSE)
				nFound++;

			if (nFound == nCurOrgan)
				return listPunti.GetAt(pos1).lIdOrgano;
		}
	}

	return 0;
}

void CEsamiView::LeggiCampo(const CString &strFileReport, const CString &strSezione, CString &strEtichetta, CRect &rectInMm, BOOL &bCheck, COLORREF &rgbColor, int &nParam, int &nAlignment, int &nRotation, LOGFONT &lfPrinterFont)
{
	strEtichetta = GetPrivateProfileString(strSezione, "Value", "", strFileReport);
	rectInMm.left = GetPrivateProfileInt(strSezione, "Left", 0, strFileReport);
	rectInMm.right = GetPrivateProfileInt(strSezione, "Right", 0, strFileReport);
	rectInMm.top = GetPrivateProfileInt(strSezione, "Top", 0, strFileReport);
	rectInMm.bottom = GetPrivateProfileInt(strSezione, "Bottom", 0, strFileReport);
	bCheck = GetPrivateProfileInt(strSezione, "Check", FALSE, strFileReport);
	rgbColor = (COLORREF)GetPrivateProfileInt(strSezione, "Color", 0, strFileReport);
	nParam = GetPrivateProfileInt(strSezione, "Param", 0, strFileReport);
	nAlignment = GetPrivateProfileInt(strSezione, "Alignment", 0, strFileReport);
	nRotation = GetPrivateProfileInt(strSezione, "Rotation", 0, strFileReport);

	strcpy_s(lfPrinterFont.lfFaceName, GetPrivateProfileString(strSezione, "Font Name", "MS Sans Serif", strFileReport));
	lfPrinterFont.lfPitchAndFamily = GetPrivateProfileInt(strSezione, "Font Family", 34, strFileReport);
	lfPrinterFont.lfHeight = GetPrivateProfileInt(strSezione, "Font Height", -13, strFileReport);
	lfPrinterFont.lfWeight = GetPrivateProfileInt(strSezione, "Font Weight", 400, strFileReport);
	lfPrinterFont.lfUnderline = GetPrivateProfileInt(strSezione, "Font Under", 0, strFileReport);
	lfPrinterFont.lfItalic = GetPrivateProfileInt(strSezione, "Font Italic", 0, strFileReport);
}

BOOL CEsamiView::PrinterSetup(CString strTitle)
{
	CMyPrintDialog pd(FALSE,PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | PD_HIDEPRINTTOFILE | PD_NOSELECTION, this);

	// Make sure we don't accidentally create a device context
	pd.m_pd.Flags &= ~PD_RETURNDC;   // Reset flag set by constructor.

	// Display the dialog box and let the user make their selection.
	if (pd.DoModal() == IDOK)	
	{
		// The user clicked OK
		// (and POSSIBLY changed printers).
		// In any case, the CMyPrintDialog logic made a copy of the original
		// DEVMODE/DEVNAMES that we passed it and applied the user's
		// changes to that copy and discarded the original copy we passed
		// it. (NOTE: If the user had clicked CANCEL instead, the original
		// values we passed would have been returned unchanged).
		if (m_hDevMode)
			GlobalFree(m_hDevMode);                      // Free old copies.
		if (m_hDevNames)
			GlobalFree(m_hDevNames);                     // Free old copies.
		if (pd.m_pd.hDevMode)
			m_hDevMode  = CopyHandle(pd.m_pd.hDevMode);  // Save new copies.
		if (pd.m_pd.hDevNames)
			m_hDevNames = CopyHandle(pd.m_pd.hDevNames); // Save new copies.

		// Regardless of whether the user clicked OK or CANCEL,
		// we need to ALWAYS do a GlobalFree of CMyPrintDialog's
		// m_pd.hDevMode and m_pd.hDevNames upon return from
		// DoModal in order to prevent a resource leak.
		GlobalFree(pd.m_pd.hDevMode);   // Because DoModal was called,
		GlobalFree(pd.m_pd.hDevNames);  // we need to free these.
		return TRUE;
	}

	// Regardless of whether the user clicked OK or CANCEL,
	// we need to ALWAYS do a GlobalFree of CMyPrintDialog's
	// m_pd.hDevMode and m_pd.hDevNames upon return from
	// DoModal in order to prevent a resource leak.
	GlobalFree(pd.m_pd.hDevMode);   // Because DoModal was called,
	GlobalFree(pd.m_pd.hDevNames);  // we need to free these.
	return FALSE;
}

void CEsamiView::SetDefaultFont(LOGFONT* pPrinterFont)
{
	pPrinterFont->lfHeight = -10;
	pPrinterFont->lfWidth = 0;
	pPrinterFont->lfWeight = 400;
	pPrinterFont->lfItalic = 0;
	pPrinterFont->lfUnderline = 0;
	pPrinterFont->lfEscapement = 0;
	pPrinterFont->lfOrientation = 0;
	pPrinterFont->lfStrikeOut = 0;
	pPrinterFont->lfCharSet = 0;
	pPrinterFont->lfOutPrecision = 1;
	pPrinterFont->lfClipPrecision = 2;
	pPrinterFont->lfQuality = 1;
	pPrinterFont->lfPitchAndFamily = 34;
	strcpy_s(pPrinterFont->lfFaceName, "MS Sans Serif");
}

/////////////////////////////////
// Sandro Gallina - 27/10/2010 //
/////////////////////////////////

CString CEsamiView::CreateHaruPdfImageFile(CString codEsame)
{
	BeginWaitCursor();

	//BUG 9964 - Felipe 12/08/2022
	CString newPathTemp = theApp.m_sDirTemp + "\\" + codEsame;
	struct stat st = { 0 };

	if (stat(newPathTemp, &st) == -1) {
		//int r = mkdir(newPathTemp);
		CreateDirectory(newPathTemp, NULL);
	}


	CString strReturn = "";

	SYSTEMTIME timeLocal;
	::GetLocalTime(&timeLocal);

	CString strPdfFile;
	strPdfFile.Format("%s\\%04d%02d%02d%02d%02d%02d%03d.pdf", newPathTemp, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond, timeLocal.wMilliseconds);

	CString strFilter;
	strFilter.Format("Contatore=%li", m_pPazientiSet->m_lContatore);

	BOOL bOrizzontale = GetPdfImagePageOrientation();//Gabriel BUG 6303

	m_PazTempSet.SetOpenFilter(strFilter);
	if (m_PazTempSet.OpenRecordset("CEsamiView::CreateHaruPdfImageFile"))
	{
		if (!m_PazTempSet.IsEOF())
		{
			TAG_HEADERFOOTER tagHeader1;
			GetHeaderFooter(GetStampaImmaginiIDHeader(), bOrizzontale == TRUE ? 210 : 297, tagHeader1);//Gabriel BUG 6303

			TAG_HEADERFOOTER tagHeader2;
			GetHeaderFooter(GetStampaImmaginiIDHeader(), bOrizzontale == TRUE ? 210 : 297, tagHeader2);//Gabriel BUG 6303

			TAG_HEADERFOOTER tagFooter1;
			GetHeaderFooter(GetStampaImmaginiIDFooter(), bOrizzontale == TRUE ? 210 : 297, tagFooter1);//Gabriel BUG 6303

			TAG_HEADERFOOTER tagFooter2;
			GetHeaderFooter(GetStampaImmaginiIDFooter(), bOrizzontale == TRUE ? 210 : 297, tagFooter2);//Gabriel BUG 6303

			LOGFONT lfProductFont;
			lfProductFont.lfHeight = -6;
			lfProductFont.lfWeight = 400;
			lfProductFont.lfItalic = 0;
			lfProductFont.lfUnderline = 0;
			strcpy_s(lfProductFont.lfFaceName, "Verdana");

			LOGFONT lfCommentAndPoint;
			theApp.m_fontBold.GetLogFont(&lfCommentAndPoint);
			lfCommentAndPoint.lfHeight = (lfCommentAndPoint.lfHeight * 3 / 5);

			//Gabriel BUG 6303
			if (AmPdfCreator_Initialize(strPdfFile, HPDF_PAGE_SIZE_A4, bOrizzontale == TRUE ? HPDF_PAGE_LANDSCAPE : HPDF_PAGE_PORTRAIT, &tagHeader1, &tagHeader2, &tagFooter1, &tagFooter2, &lfProductFont, theApp.m_sHeaderPrintImage, &lfCommentAndPoint, theApp.m_bStampaBordiNeriImmagini, theApp.m_bStampaCommentoDentroImmagini, &lfCommentAndPoint, TRUE, theApp.m_bPDFIncorporaFonts, theApp.m_bPDFInibisciCopia, theApp.m_bPDFInibisciStampa, FALSE, theApp.m_bPDFNonProtetti))
				PrintImages(tagHeader2.lHeight, max(tagFooter1.lHeight, tagFooter2.lHeight));

			// il finalize va fatto in ogni caso perché si cancella tutte le immagini contenute //
			AmPdfCreator_Finalize();

			//
			strReturn = strPdfFile;
		}

		m_PazTempSet.CloseRecordset("CEsamiView::CreateHaruPdfImageFile");
	}

	EndWaitCursor();
	return strReturn;
}

CString CEsamiView::CreateHaruPdfCentraleStampaFile(long lIDHeader, long lIDFooter1, long lIDFooter2, CString sReferto)
{
	BeginWaitCursor();

	if (theApp.m_bPersonalizzazioniBrasileFleury && CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPA_IMMAGINI_ERRORE_5));
		return "";
	}

	// Sandro 24/11/2016 //

	sReferto.Replace("Cripto@", "'");

	//

	SYSTEMTIME timeLocal;
	::GetLocalTime(&timeLocal);

	CString strReturn = "";
	strReturn.Format("%s\\%04d%02d%02d%02d%02d%02d%03d.pdf", theApp.m_sDirTemp, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond, timeLocal.wMilliseconds);

	TAG_HEADERFOOTER tagHeader1;
	GetHeaderFooter(lIDHeader, 297, tagHeader1);

	TAG_HEADERFOOTER tagHeader2;
	GetHeaderFooter(lIDHeader, 297, tagHeader2);

	TAG_HEADERFOOTER tagFooter1;
	GetHeaderFooter(lIDFooter1, 297, tagFooter1);

	TAG_HEADERFOOTER tagFooter2;
	GetHeaderFooter(lIDFooter2, 297, tagFooter2);

	LOGFONT lfProductFont;
	lfProductFont.lfHeight = -6;
	lfProductFont.lfWeight = 400;
	lfProductFont.lfItalic = 0;
	lfProductFont.lfUnderline = 0;
	strcpy_s(lfProductFont.lfFaceName, "Verdana");

	LOGFONT lfCommentAndPoint;
	theApp.m_fontBold.GetLogFont(&lfCommentAndPoint);
	lfCommentAndPoint.lfHeight = (lfCommentAndPoint.lfHeight * 3 / 5);

	if (AmPdfCreator_Initialize(strReturn, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT, &tagHeader1, &tagHeader2, &tagFooter1, &tagFooter2, &lfProductFont, theApp.m_sHeaderPrintImage, &lfCommentAndPoint, theApp.m_bStampaBordiNeriImmagini, theApp.m_bStampaCommentoDentroImmagini, &lfCommentAndPoint, TRUE, theApp.m_bPDFIncorporaFonts, theApp.m_bPDFInibisciCopia, theApp.m_bPDFInibisciStampa, FALSE, theApp.m_bPDFNonProtetti))
	{
		TAG_ELEMENT tagElementReferto;
		tagElementReferto.strFieldValue = sReferto;
		tagElementReferto.rectInMm = CRect(10, 50, 200, 100);
		tagElementReferto.bCanExpand = TRUE;
		tagElementReferto.bPaintBorder = FALSE;

#ifdef _DEBUG
		tagElementReferto.bPaintBorder = TRUE;
#endif

		// stampo il testo del referto //
		AmPdfCreator_PrintRTF(tagElementReferto, NULL, NULL);
	}

	// il finalize va fatto in ogni caso perché si cancella tutte le immagini contenute //
	AmPdfCreator_Finalize();

	//
	EndWaitCursor();
	return strReturn;
}

CString CEsamiView::CreateHaruPdfImageFileFromDib(CList<CDib*>* pListImmagini)
{
	BeginWaitCursor();

	CString strReturn = "";

	SYSTEMTIME timeLocal;
	::GetLocalTime(&timeLocal);

	CString strPdfFile;
	strPdfFile.Format("%s\\%04d%02d%02d%02d%02d%02d%03d.pdf", theApp.m_sDirTemp, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond, timeLocal.wMilliseconds);

	CString strFilter;
	strFilter.Format("Contatore=%li", m_pPazientiSet->m_lContatore);

	m_PazTempSet.SetOpenFilter(strFilter);
	if (m_PazTempSet.OpenRecordset("CEsamiView::CreateHaruPdfImageFileFromDib"))
	{
		if (!m_PazTempSet.IsEOF())
		{
			TAG_HEADERFOOTER tagHeader1;
			TAG_HEADERFOOTER tagHeader2;
			TAG_HEADERFOOTER tagFooter1;
			TAG_HEADERFOOTER tagFooter2;

			LOGFONT lfProductFont;
			lfProductFont.lfHeight = -6;
			lfProductFont.lfWeight = 400;
			lfProductFont.lfItalic = 0;
			lfProductFont.lfUnderline = 0;
			strcpy_s(lfProductFont.lfFaceName, "Verdana");

			LOGFONT lfCommentAndPoint;
			theApp.m_fontBold.GetLogFont(&lfCommentAndPoint);
			lfCommentAndPoint.lfHeight = (lfCommentAndPoint.lfHeight * 3 / 5);

			if (AmPdfCreator_Initialize(strPdfFile, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT, &tagHeader1, &tagHeader2, &tagFooter1, &tagFooter2, &lfProductFont, theApp.m_sHeaderPrintImage, &lfCommentAndPoint, FALSE, FALSE, &lfCommentAndPoint, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE))
				PrintImagesFromDibs(pListImmagini);

			// il finalize va fatto in ogni caso perché si cancella tutte le immagini contenute //
			AmPdfCreator_Finalize();

			//
			strReturn = strPdfFile;
		}

		m_PazTempSet.CloseRecordset("CEsamiView::CreateHaruPdfImageFileFromDib");
	}

	EndWaitCursor();
	return strReturn;
}

BOOL CEsamiView::CreateHaruPdfReportFile(CString& sOutputFileComplete, STRUCT_STAMPA* pStructStampa, BOOL bAccodaStampaImmagini, CString codEsame)
{
	TRACE0("----->     CreateHaruPdfReportFile\n");
	
	BeginWaitCursor();

	SYSTEMTIME timeLocal;
	::GetLocalTime(&timeLocal);

	//BUG 9964 - Felipe 12/08/2022
	CString newPathTemp = theApp.m_sDirTemp + "\\" + codEsame;
	struct stat st = { 0 };

	if (stat(newPathTemp, &st) == -1) {
		//int r = mkdir(newPathTemp);
		CreateDirectory(newPathTemp, NULL);
	}
	sOutputFileComplete.Format("%s\\%04d%02d%02d%02d%02d%02d%03d.pdf", newPathTemp , timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond, timeLocal.wMilliseconds);

	CString strFilter;
	strFilter.Format("Contatore=%li", m_pPazientiSet->m_lContatore);

	m_PazTempSet.SetOpenFilter(strFilter);
	if (m_PazTempSet.OpenRecordset("CEsamiView::CreateHaruPdfReportFile"))
	{
		if (!m_PazTempSet.IsEOF())
		{
			TAG_HEADERFOOTER tagHeader1;
			TAG_HEADERFOOTER tagHeader2;
			TAG_HEADERFOOTER tagFooter1;
			TAG_HEADERFOOTER tagFooter2;

			LOGFONT lfProductFont;
			lfProductFont.lfHeight = -6;
			lfProductFont.lfWeight = 400;
			lfProductFont.lfItalic = 0;
			lfProductFont.lfUnderline = 0;
			strcpy_s(lfProductFont.lfFaceName, "Verdana");

			LOGFONT lfCommentAndPoint;
			theApp.m_fontBold.GetLogFont(&lfCommentAndPoint);
			lfCommentAndPoint.lfHeight = (lfCommentAndPoint.lfHeight * 3 / 5);

			// creo PDF completo //
			GetHeaderFooter(GetPrivateProfileInt("Page", "IDHeader1", 0, pStructStampa->m_sReportFilePrinting), GetPrivateProfileInt("Page", "Height", 297, pStructStampa->m_sReportFilePrinting), tagHeader1);
			GetHeaderFooter(GetPrivateProfileInt("Page", "IDHeader2", 0, pStructStampa->m_sReportFilePrinting), GetPrivateProfileInt("Page", "Height", 297, pStructStampa->m_sReportFilePrinting), tagHeader2);
			GetHeaderFooter(GetPrivateProfileInt("Page", "IDFooter1", 0, pStructStampa->m_sReportFilePrinting), GetPrivateProfileInt("Page", "Height", 297, pStructStampa->m_sReportFilePrinting), tagFooter1);
			GetHeaderFooter(GetPrivateProfileInt("Page", "IDFooter2", 0, pStructStampa->m_sReportFilePrinting), GetPrivateProfileInt("Page", "Height", 297, pStructStampa->m_sReportFilePrinting), tagFooter2);
			CreateHaruPdfReportFileComplete(sOutputFileComplete, pStructStampa, &tagHeader1, &tagHeader2, &tagFooter1, &tagFooter2, &lfProductFont, &lfCommentAndPoint, &lfCommentAndPoint, bAccodaStampaImmagini);

			// cancello il file del report temporaneo così lascio la TEMP un po' più in ordine //
			if (pStructStampa->m_sReportFilePrinting.CompareNoCase(theApp.m_sDirTemp + "\\temp.rpx") == 0)
				DeleteFile(pStructStampa->m_sReportFilePrinting);
			//DeleteDirectory(newPathTemp);
			// Sandro 08/07/2011 //
			tagHeader1.listElements.RemoveAll();
			tagHeader2.listElements.RemoveAll();
			tagFooter1.listElements.RemoveAll();
			tagFooter2.listElements.RemoveAll();
			
			//

			if (theApp.m_lDcmStoreMode == 1)
				StoreImmOnPacs();
		}

		m_PazTempSet.CloseRecordset("CEsamiView::CreateHaruPdfReportFile");
	}

	EndWaitCursor();

	return !sOutputFileComplete.IsEmpty();
}

void CEsamiView::CreateHaruPdfReportFileComplete(CString sOutputFile, STRUCT_STAMPA* pStructStampa, TAG_HEADERFOOTER* pTagHeader1, TAG_HEADERFOOTER* pTagHeader2, TAG_HEADERFOOTER* pTagFooter1, TAG_HEADERFOOTER* pTagFooter2, LOGFONT* pLogFontProduct, LOGFONT* pLogFontComment, LOGFONT* pLogFontPoint, BOOL bAccodaStampaImmagini)
{
	TRACE0("----->     CreateHaruPdfReportFileComplete\n");

	if (AmPdfCreator_Initialize(sOutputFile, GetPageSize(pStructStampa->m_sReportFilePrinting), GetPageDirection(pStructStampa->m_sReportFilePrinting), pTagHeader1, pTagHeader2, pTagFooter1, pTagFooter2, pLogFontProduct, theApp.m_sHeaderPrintImage, pLogFontComment, theApp.m_bStampaBordiNeriImmagini, theApp.m_bStampaCommentoDentroImmagini, pLogFontPoint, pStructStampa->m_bFitToPage, theApp.m_bPDFIncorporaFonts, theApp.m_bPDFInibisciCopia, theApp.m_bPDFInibisciStampa, FALSE, theApp.m_bPDFNonProtetti))
	{
		PrintReport(pTagHeader2->lHeight, max(pTagFooter1->lHeight, pTagFooter2->lHeight), pStructStampa);

		// Sandro 05/11/2013 // RAS 20130189 //
		if (bAccodaStampaImmagini)
		{
			// riempio la lista delle immagini da stampare //
			long lSelectedImm = CFileBmp::FillImagesPrinterList(LOCAL_IMAGES);

			// controllo che siano state selezionate le immagini //
			if (lSelectedImm > 0)
			{
				// vado su una nuova pagina //
				AmPdfCreator_AddPage();

				// procedo con la "normale" stampa delle immagini //
				PrintImages(pTagHeader2->lHeight, max(pTagFooter1->lHeight, pTagFooter2->lHeight));
			}
		}
	}

	// il finalize va fatto in ogni caso perché si cancella tutte le immagini contenute //
	AmPdfCreator_Finalize();
}

CString CEsamiView::CreateHaruPdfReportFileFromQuery(STRUCT_STAMPA* pStruct)
{
	BeginWaitCursor();

	CString strReturn = "";

	if (m_pQueryDlg != NULL)
	{
		SYSTEMTIME timeLocal;
		::GetLocalTime(&timeLocal);

		CString strPdfFile;
		strPdfFile.Format("%s\\%04d%02d%02d%02d%02d%02d%03d.pdf", theApp.m_sDirTemp, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond, timeLocal.wMilliseconds);

		TAG_HEADERFOOTER tagHeader1;
		GetHeaderFooter(GetPrivateProfileInt("Page", "IDHeader1", 0, pStruct->m_sReportFilePrinting), GetPrivateProfileInt("Page", "Height", 297, pStruct->m_sReportFilePrinting), tagHeader1);

		TAG_HEADERFOOTER tagHeader2;
		GetHeaderFooter(GetPrivateProfileInt("Page", "IDHeader2", 0, pStruct->m_sReportFilePrinting), GetPrivateProfileInt("Page", "Height", 297, pStruct->m_sReportFilePrinting), tagHeader2);

		TAG_HEADERFOOTER tagFooter1;
		GetHeaderFooter(GetPrivateProfileInt("Page", "IDFooter1", 0, pStruct->m_sReportFilePrinting), GetPrivateProfileInt("Page", "Height", 297, pStruct->m_sReportFilePrinting), tagFooter1);

		TAG_HEADERFOOTER tagFooter2;
		GetHeaderFooter(GetPrivateProfileInt("Page", "IDFooter2", 0, pStruct->m_sReportFilePrinting), GetPrivateProfileInt("Page", "Height", 297, pStruct->m_sReportFilePrinting), tagFooter2);

		LOGFONT lfProductFont;
		lfProductFont.lfHeight = -6;
		lfProductFont.lfWeight = 400;
		lfProductFont.lfItalic = 0;
		lfProductFont.lfUnderline = 0;
		strcpy_s(lfProductFont.lfFaceName, "Verdana");

		LOGFONT lfCommentAndPoint;
		theApp.m_fontBold.GetLogFont(&lfCommentAndPoint);
		lfCommentAndPoint.lfHeight = (lfCommentAndPoint.lfHeight * 3 / 5);

		if (AmPdfCreator_Initialize(strPdfFile, GetPageSize(pStruct->m_sReportFilePrinting), GetPageDirection(pStruct->m_sReportFilePrinting), &tagHeader1, &tagHeader2, &tagFooter1, &tagFooter2, &lfProductFont, theApp.m_sHeaderPrintImage, &lfCommentAndPoint, theApp.m_bStampaBordiNeriImmagini, theApp.m_bStampaCommentoDentroImmagini, &lfCommentAndPoint, TRUE, theApp.m_bPDFIncorporaFonts, theApp.m_bPDFInibisciCopia, theApp.m_bPDFInibisciStampa, FALSE, theApp.m_bPDFNonProtetti))
			PrintReportFromQuery(tagHeader2.lHeight, max(tagFooter1.lHeight, tagFooter2.lHeight), pStruct);

		// il finalize va fatto in ogni caso perché si cancella tutte le immagini contenute //
		AmPdfCreator_Finalize();

		// cancello il file del report temporaneo così lascio la TEMP un po' più in ordine //
		if (pStruct->m_sReportFilePrinting.CompareNoCase(theApp.m_sDirTemp + "\\temp.rpx") == 0)
			DeleteFile(pStruct->m_sReportFilePrinting);

		// Sandro 08/07/2011 //
		tagHeader1.listElements.RemoveAll();
		tagHeader2.listElements.RemoveAll();
		tagFooter1.listElements.RemoveAll();
		tagFooter2.listElements.RemoveAll();

		//
		strReturn = strPdfFile;
	}

	EndWaitCursor();
	return strReturn;
}

HPDF_PageDirection CEsamiView::GetPageDirection(CString sReportFile)
{
	if (GetPrivateProfileInt("Page", "Width", 210, sReportFile) > GetPrivateProfileInt("Page", "Height", 297, sReportFile))
		return HPDF_PAGE_LANDSCAPE;

	return HPDF_PAGE_PORTRAIT;
}

HPDF_PageSizes CEsamiView::GetPageSize(CString sReportFile)
{
	long lWidth = GetPrivateProfileInt("Page", "Width",  210, sReportFile);
	long lHeight = GetPrivateProfileInt("Page", "Height", 297, sReportFile);

	long lMin = min(lWidth, lHeight);
	long lMax = max(lWidth, lHeight);

	if ((lMin == 216) && (lMax == 355))
		return HPDF_PAGE_SIZE_LEGAL;
	else if ((lMin == 216) && (lMax == 279))
		return HPDF_PAGE_SIZE_LETTER;
	else if ((lMin == 184) && (lMax == 266))
		return HPDF_PAGE_SIZE_EXECUTIVE;

	return HPDF_PAGE_SIZE_A4;
}

CString GetLocalFileName(CString strFileName)
{
	CString strReturn = theApp.m_sDirTemp + "\\" + strFileName + ".jpg";

	int aaa = strFileName.ReverseFind('\\');
	if (aaa >= 0)
	{
		int bbb = strFileName.ReverseFind('.');

		if (bbb >= aaa)
			strReturn = theApp.m_sDirTemp + "\\" + strFileName.Mid(aaa + 1, (bbb - aaa) - 1) + ".jpg";
	}

	return strReturn;
}

void CEsamiView::AddElementToList(CList<TAG_ELEMENT>& listElements, ENUM_FIELD_TYPE lFieldType, CString sFieldValue, long lLeft, long lRight, long lTop, long lBottom, COLORREF rgbColor, long lCheck, long lParam, CString sFontName, long lFontHeight, long lFontWeight, long lFontUnder, long lFontItalic, long lAlignment, long lRotation, CString sComment, STRUCT_STAMPA* pStruct)
{
	if (lFieldType != TYPE_NONE)
	{
		TAG_ELEMENT tagElement;

		//
		tagElement.lFieldType = lFieldType;

		//
		tagElement.strFieldValue = sFieldValue;

		//
		tagElement.rectInMm.left = lLeft;
		tagElement.rectInMm.right = lRight;
		tagElement.rectInMm.top = lTop;
		tagElement.rectInMm.bottom = lBottom;

		//
		tagElement.rgbColor = (COLORREF)rgbColor;

		//
		tagElement.lMyCheck = lCheck;

		//
		tagElement.lMyParam = lParam;

		//
		strcpy_s(tagElement.lfFont.lfFaceName, sFontName);
		tagElement.lfFont.lfHeight = lFontHeight;
		tagElement.lfFont.lfWeight = lFontWeight;
		tagElement.lfFont.lfUnderline = (unsigned char)lFontUnder;
		tagElement.lfFont.lfItalic = (unsigned char)lFontItalic;

		//
		switch(lAlignment)
		{
			case 1:
			{
				tagElement.hAlignment = HPDF_TALIGN_CENTER;
				break;
			}
			case 2:
			{
				tagElement.hAlignment = HPDF_TALIGN_RIGHT;
				break;
			}
			case 3:
			{
				tagElement.hAlignment = HPDF_TALIGN_JUSTIFY;
				break;
			}
			default:
			{
				tagElement.hAlignment = HPDF_TALIGN_LEFT;
				break;
			}
		}

		//
		switch(lRotation)
		{
			case 1:
			{
				tagElement.lRotation = ROTATION_90_CW;
				break;
			}
			case 2:
			{
				tagElement.lRotation = ROTATION_90_CCW;
				break;
			}
			default:
			{
				tagElement.lRotation = ROTATION_NONE;
				break;
			}
		}

		//
		tagElement.strComment = sComment;

		//
		tagElement.bCanExpand = FALSE;

		//
		tagElement.bPaintBorder = FALSE;

		//
		switch(tagElement.lFieldType)
		{
			case TYPE_ICON:
			{
				if (!tagElement.strFieldValue.IsEmpty())
				{
					// aggiungo comunque l'elemento in coda //
					listElements.AddTail(tagElement);

					// passo anche l'immagine alla libreria //
					HBITMAP hBitOld1;
					if (m_pImgManager->LoadLocalImageEx(tagElement.strFieldValue, &hBitOld1) > 0)
					{
						// Sandro 08/03/2012 // RIMA 11-064.5 //
						HBITMAP hBitNew = CImageElaboration(hBitOld1).ApplyBrightnessContrast(theApp.m_iIEBrightness, theApp.m_iIEContrastRMin, theApp.m_iIEContrastRMax, theApp.m_iIEContrastGMin, theApp.m_iIEContrastGMax, theApp.m_iIEContrastBMin, theApp.m_iIEContrastBMax);

						//
						Bitmap* pBitmap = Bitmap::FromHBITMAP(hBitNew, NULL);
						if (pBitmap->GetLastStatus() == Gdiplus::Ok)
						{
							if (theApp.m_bPDFImmaginiNonCompresse)
							{
								USES_CONVERSION;
								CLSID idClass;
								if (GetEncoderClsid(L"image/png", &idClass))
								{
									CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
									if (pBitmap->Save(T2W(strFileTemp), &idClass, NULL) == Gdiplus::Ok)
										AmPdfCreator_AddImageFromFilePng(tagElement.strFieldValue, strFileTemp);
								}
							}
							else
							{
								USES_CONVERSION;
								CLSID idClass;
								if (GetEncoderClsid(L"image/jpeg", &idClass))
								{
									EncoderParameters encoderParameters;
									encoderParameters.Count = 1;
									encoderParameters.Parameter[0].Guid = EncoderQuality;
									encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
									encoderParameters.Parameter[0].NumberOfValues = 1;
									ULONG quality = theApp.m_lPDFQualitaImmaginiCompresse; // Sandro 20/09/2013 // RAS 20130112 //
									encoderParameters.Parameter[0].Value = &quality;

									CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
									if (pBitmap->Save(T2W(strFileTemp), &idClass, &encoderParameters) == Gdiplus::Ok)
										AmPdfCreator_AddImageFromFileJpg(tagElement.strFieldValue, strFileTemp);
								}
							}
						}
						delete pBitmap;
						DeleteObject(hBitOld1);
						DeleteObject(hBitNew);
					}
				}
				break;
			}
			case TYPE_LABEL:
			{
				// stampo l'etichetta, se il relativo campo è valido //

				TAG_ELEMENT tagTemp = tagElement;

				CList<TAG_ELEMENT> listElementsTemp;
				if (GetField(listElementsTemp, tagElement, TRUE))
				{
					tagElement = tagTemp;
					BOOL bSaltaTutto = FALSE;
					if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) 
						&& tagElement.strFieldValue.CompareNoCase("ChiusuraEsame.Anagrafica") == 0)
					{
						long lIDUtenteConvalida = 0;
						if (m_pEsamiSet->m_bLocked)
							lIDUtenteConvalida = m_pEsamiSet->m_lIdUtenteLock;
						else
							lIDUtenteConvalida = GetUserIDForLockSuperlock();

						long lIDUtenteChiusura = 0;
						if (m_pEsamiSet->m_bSuperLocked)
							lIDUtenteChiusura = m_pEsamiSet->m_lIdUtenteSuperLock;
						else
							lIDUtenteChiusura = GetUserIDForLockSuperlock();

						if (lIDUtenteConvalida == lIDUtenteChiusura)
						{
							tagElement.strFieldValue = theApp.GetMessageString(IDS_REFERTATO_E_FIRMATO_DA);
							tagElement.strFieldValue.Trim();

							if (!tagElement.strFieldValue.IsEmpty())
								listElements.AddTail(tagElement);

							bSaltaTutto = TRUE;
						}
					}
					if (!bSaltaTutto)
					{
						for (int i = 0; i < endox_report_field_num_total; i++)
						{
							if (CFieldDlg::m_strFieldEndox[i].sReport == tagElement.strFieldValue)
							{
								tagElement.strFieldValue = CFieldDlg::m_strFieldEndox[i].sCombo;
								tagElement.strFieldValue.Trim();

								if (!tagElement.strFieldValue.IsEmpty())
									listElements.AddTail(tagElement);

								break;
							}
						}
					}
				}

				//
				break;
			}
			case TYPE_FIELD:
			{
				GetField(listElements, tagElement, FALSE);
				break;
			}
			case TYPE_PARAM:
			{
				GetParam(listElements, tagElement);
				break;
			}
			/*
			case TYPE_IMAGE:
			{
				break;
			}
			*/
			default:
			{
				listElements.AddTail(tagElement);
				break;
			}
		}
	}
}

void CEsamiView::GetParam(CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement)
{	
	CCustomDate	DataOggi(TRUE, TRUE);
	if (tagElement.strFieldValue.CompareNoCase(szParamData) == 0)
	{
		tagElement.strFieldValue = DataOggi.GetDate("%d/%m/%Y");
		listElements.AddTail(tagElement);
		AddElementToDocument("data_documento", tagElement.strFieldValue);
	}
	else if (tagElement.strFieldValue.CompareNoCase(szParamOra) == 0)
	{
		tagElement.strFieldValue = DataOggi.GetDate("%H:%M");
		listElements.AddTail(tagElement);
		AddElementToDocument("ora_documento", tagElement.strFieldValue);
	}
	else if (tagElement.strFieldValue.CompareNoCase(szParamDataLarga) == 0)
	{
		CString strFieldToPrint = DataOggi.GetDate("%d%m%y");

		CRect rectTot = tagElement.rectInMm;
		double dCellWidth = (double)rectTot.Width() / (double)6;
		for(int i = 0; i < strFieldToPrint.GetLength(); i++)
		{
			tagElement.strFieldValue = strFieldToPrint.Mid(i, 1);

			tagElement.rectInMm.left = rectTot.left + (LONG)(dCellWidth * (double)i);
			tagElement.rectInMm.top = rectTot.top;
			tagElement.rectInMm.right = rectTot.left + (LONG)(dCellWidth * (double)(i + 1));
			tagElement.rectInMm.bottom = rectTot.bottom;

			listElements.AddTail(tagElement);
		}

		AddElementToDocument("data_documento", strFieldToPrint);
	}
}

void CEsamiView::GetHeaderFooter(long lID, long lPaperHeight, TAG_HEADERFOOTER& tagReturn)
{
	BOOL bFooter = FALSE;
	long lVerticalShift = 0;

	tagReturn.lHeight = 0;
	tagReturn.listElements.RemoveAll();

	if (lID > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", lID);
	
		CHeaderFooterSet setHF;
		setHF.SetOpenFilter(strFilter);
		if (setHF.OpenRecordset("CEsamiView::GetHeaderFooter"))
		{
			if (!setHF.IsEOF())
			{
				bFooter = (setHF.m_lTipo == 2);
				tagReturn.lHeight = setHF.m_lAltezza;
			}

			setHF.CloseRecordset("CEsamiView::GetHeaderFooter");
		}
	}

	if (tagReturn.lHeight > 0)
	{
		CString strFilter;
		strFilter.Format("IDHeaderFooter=%li", lID);

		if (bFooter)
		{
			// se sono nel footer devo shiftare in giù tutti i campi perchè la loro posizione salvata nel DB è relativa al solo campo footer e non "assoluta" nel foglio //
			lVerticalShift = lPaperHeight - tagReturn.lHeight;
		}

		CElemReportSet setElem;
		setElem.SetOpenFilter(strFilter);
		if (setElem.OpenRecordset("CEsamiView::GetHeaderFooter"))
		{
			while (!setElem.IsEOF())
			{
				AddElementToList(tagReturn.listElements, GetFieldType(setElem.m_strType), setElem.m_strValue, setElem.m_nLeft, setElem.m_nRight, setElem.m_nTop + lVerticalShift, setElem.m_nBottom + lVerticalShift, setElem.m_nColor, setElem.m_nCheck, setElem.m_nParam, setElem.m_strFontName, setElem.m_nFontHeight, setElem.m_nFontWeight, setElem.m_nFontUnder, setElem.m_nFontItalic, setElem.m_nAlignment, setElem.m_nRotation, "", NULL);

				setElem.MoveNext();
			}

			setElem.CloseRecordset("CEsamiView::GetHeaderFooter");
		}

		// Sandro 15/06/2017 // Capitan Pilotto GIUSTAMENTE ha bisogno di mettere i barcode anche in headers e footers //

		POSITION pos = tagReturn.listElements.GetHeadPosition();
		while (pos != NULL)
		{
			TAG_ELEMENT tagTemp = tagReturn.listElements.GetAt(pos);

			if (theApp.m_sBarCodeFontName.CompareNoCase(tagTemp.lfFont.lfFaceName) == 0)
			{
				tagTemp.strFieldValue = "*" + tagTemp.strFieldValue + "*";
				tagReturn.listElements.SetAt(pos, tagTemp);
			}

			tagReturn.listElements.GetNext(pos);
		}
	}
}

#define BORDER_LEFT 0
#define BORDER_TOP 0
#define BORDER_RIGHT 210
#define BORDER_BOTTOM 297
#define BORDER_PATIENT 4
void CEsamiView::PrintImages(long lHeaderHeight, long lFooterHeight)
{
	// preparo la lista ed il numero delle immagini da stampare //
	CList<IMAGE_TO_PRINT*> listImagesToPrint;
	long lImagesToPrint = CFileBmp::FillListImagesToPrint(m_pImgManager, &listImagesToPrint);
	BOOL bOrizzontale = GetPdfImagePageOrientation();//Gabriel BUG 6303

	// preparo il numero di immagini per pagina //
	long lImagesPerPage = 0;
	switch (theApp.m_nStampaImmaginiTipoDiStampa)
	{
		case 0: // una immagine per pagina //
		{
			lImagesPerPage = 1;
			break;
		}
		case 1: // due immagini per pagina //
		{
			lImagesPerPage = 2;
			break;
		}
		case 2: // quattro immagini per pagina //
		{
			lImagesPerPage = 4;
			break;
		}
		case 3: // sei immagini per pagina //
		{
			lImagesPerPage = 6;
			break;
		}
		case 4: // otto immagini per pagina //
		{
			lImagesPerPage = 8;
			break;
		}
		default:
		{
			ASSERT(FALSE);
		}
	}

	// calcolo il numero di pagine da stampare //
	long lTotalPages = lImagesToPrint / lImagesPerPage;
	if (lImagesToPrint % lImagesPerPage != 0)
		lTotalPages++; // approssimo per eccesso... magari c'era un altro metodo migliore per farlo, ma così dovrebbe funzionare... //

	// creo una lista contenente, pagina per pagina, il numero di immagini che vi saranno stampate //
	CList<long> listImagesPerPage;
	for(int i = 0; i < lTotalPages; i++)
	{
		if (i == lTotalPages - 1)
		{
			// ultima pagina -> le immagini rimaste //
			long lInQuestaPagina = lImagesToPrint;
			listImagesPerPage.AddTail(lInQuestaPagina);
			lImagesToPrint -= lInQuestaPagina;
		}
		else if (i == lTotalPages - 2)
		{
			// penultima pagina -> la metà (più uno, eventualmente) delle immagini rimaste //
			long lInQuestaPagina = lImagesToPrint / 2;
			if (lImagesToPrint % 2 != 0)
				lInQuestaPagina++;
			listImagesPerPage.AddTail(lInQuestaPagina);
			lImagesToPrint -= lInQuestaPagina;
		}
		else
		{
			// pagine precedenti -> tutte piene //
			long lInQuestaPagina = lImagesPerPage;
			listImagesPerPage.AddTail(lInQuestaPagina);
			lImagesToPrint -= lInQuestaPagina;
		}
	}

	// calcolo il bordo superiore //
	long lTop = BORDER_TOP;
	if (lHeaderHeight > 0)
		lTop = lHeaderHeight;
	if (theApp.m_bStampaImmaginiStampaDatiPaziente)
		lTop += BORDER_PATIENT;

	// calcolo il bordo inferiore //
	long lBottom = bOrizzontale == TRUE ? BORDER_RIGHT : BORDER_BOTTOM;//Gabriel BUG 6303
	if (lFooterHeight > 0)
		lBottom = (bOrizzontale == TRUE ? 210 : 297) - lFooterHeight;//Gabriel BUG 6303

	// calcolo le dimensioni effettive dell'area stampabile //
	long lPageHeight = lBottom - lTop;
	long lPageWidth = (bOrizzontale == TRUE ? BORDER_BOTTOM : BORDER_RIGHT) - BORDER_LEFT;//Gabriel BUG 6303

	// calcolo le dimensioni che avrà ogni singola immagine stampate //
	long lImageHeight = 0;
	long lImageWidth = 0;
	switch (theApp.m_nStampaImmaginiTipoDiStampa)
	{
		case 0: // una immagine per pagina //
		{
			lImageHeight = lPageHeight;
			lImageWidth = lPageWidth;

			break;
		}
		case 1: // due immagini per pagina //
		{
			lImageHeight = (lPageHeight - theApp.m_nStampaImmaginiDistanzaImmagini) / 2;
			lImageWidth = lPageWidth;

			break;
		}
		case 2: // quattro immagini per pagina //
		{
			lImageHeight = (lPageHeight - theApp.m_nStampaImmaginiDistanzaImmagini) / 2;
			lImageWidth = (lPageWidth - theApp.m_nStampaImmaginiDistanzaImmagini) / 2;

			break;
		}
		case 3: // sei immagini per pagina //
		{
			lImageHeight = (lPageHeight - (theApp.m_nStampaImmaginiDistanzaImmagini * 2)) / 3;
			lImageWidth = (lPageWidth - theApp.m_nStampaImmaginiDistanzaImmagini) / 2;

			break;
		}
		case 4: // otto immagini per pagina //
		{
			lImageHeight = (lPageHeight - (theApp.m_nStampaImmaginiDistanzaImmagini * 3)) / 4;
			lImageWidth = (lPageWidth - theApp.m_nStampaImmaginiDistanzaImmagini) / 2;

			break;
		}
		default: 
		{
			ASSERT(FALSE);
			break;
		}
	}

	BOOL bPrimaPagina = TRUE;
	long lPrintedImages = 0;
	POSITION pos = listImagesPerPage.GetHeadPosition();
	while(pos != NULL)
	{
		if (!bPrimaPagina)
			AmPdfCreator_AddPage();
		else
			bPrimaPagina = FALSE;

		// stampo dati del paziente e dell'esame //
		if (theApp.m_bStampaImmaginiStampaDatiPaziente)
		{
			CCustomDate dataPaziente(m_pPazientiSet->m_lNatoIlCustom);
			CCustomDate dataEsame(m_pEsamiSet->m_lData);

			CString strDati;

			// Sandro 20/11/2013 // RAS 20130186 //
			if (theApp.m_bMostraSecondoCognome)
				strDati.Format("%s %s %s", m_pPazientiSet->m_sCognome, m_pPazientiSet->m_sCognome2, m_pPazientiSet->m_sNome);
			else
				strDati.Format("%s %s", m_pPazientiSet->m_sCognome, m_pPazientiSet->m_sNome);

			if (dataPaziente.GetDate() > 0)
				strDati += " (" + dataPaziente.GetDate("%d/%m/%Y") + ")";
			if (dataEsame.GetDate() > 0)
				strDati += " - " + CTipoEsameSet().GetDescrizione(m_pEsamiSet->m_lIDEsame) + " del " + dataEsame.GetDate("%d/%m/%Y");

			strDati.Trim();
			while(strDati.Find("  ") >= 0)
				strDati.Replace("  ", " ");

			LOGFONT lfCommentAndPoint;
			theApp.m_fontBold.GetLogFont(&lfCommentAndPoint);
			lfCommentAndPoint.lfHeight = (lfCommentAndPoint.lfHeight * 3 / 5);

			TAG_ELEMENT tagElementPat;
			tagElementPat.lFieldType = TYPE_TEXT;
			tagElementPat.strFieldValue = strDati;
			tagElementPat.rectInMm = CRect(BORDER_LEFT, lTop - BORDER_PATIENT, bOrizzontale == TRUE ? BORDER_BOTTOM : BORDER_RIGHT, lTop);//Gabriel BUG 6303
			tagElementPat.rgbColor = RGB(0, 0, 0);
			tagElementPat.lMyCheck = 0;
			tagElementPat.lMyParam = 0;
			tagElementPat.lfFont = lfCommentAndPoint;
			tagElementPat.hAlignment = HPDF_TALIGN_CENTER;
			tagElementPat.lRotation = ROTATION_NONE;
			tagElementPat.strComment = "";
			tagElementPat.bCanExpand = FALSE;
			tagElementPat.bPaintBorder = FALSE;

			// stampo il testo //
			AmPdfCreator_PrintText(tagElementPat, NULL, NULL);
		}

		switch(listImagesPerPage.GetAt(pos))
		{
			case 1:
			{
				IMAGE_TO_PRINT* pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				CRect rectImage;
				rectImage.left = ((lPageWidth - lImageWidth) / 2) + BORDER_LEFT;
				rectImage.top = ((lPageHeight - lImageHeight) / 2) + lTop;
				rectImage.right = rectImage.left + lImageWidth;
				rectImage.bottom = rectImage.top + lImageHeight;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);
				break;
			}
			case 2:
			{
				IMAGE_TO_PRINT* pSel = NULL;
				CRect rectImage;
				long lTotHeight = (lImageHeight * 2) + theApp.m_nStampaImmaginiDistanzaImmagini;

				//

				rectImage.left = ((lPageWidth - lImageWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				// sopra in centro //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.top = ((lPageHeight - lTotHeight) / 2) + lTop;
				rectImage.bottom = rectImage.top + lImageHeight;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// sotto in centro //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				break;
			}
			case 3:
			{
				if (theApp.m_nStampaImmaginiTipoDiStampa == 2)
				{
					// quattro immagini per pagina //

					IMAGE_TO_PRINT* pSel = NULL;
					CRect rectImage;
					long lTotHeight = (lImageHeight * 2) + theApp.m_nStampaImmaginiDistanzaImmagini;
					long lTotWidth = (lImageWidth * 2) + theApp.m_nStampaImmaginiDistanzaImmagini;

					//

					rectImage.top = ((lPageHeight - lTotHeight) / 2) + lTop;
					rectImage.bottom = rectImage.top + lImageHeight;

					// sopra a sinistra //

					pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

					rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
					rectImage.right = rectImage.left + lImageWidth;

					PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

					// sopra a destra //

					pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

					rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
					rectImage.right = rectImage.left + lImageWidth;

					PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

					//

					rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
					rectImage.bottom = rectImage.top + lImageHeight;

					// sotto in centro //

					pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

					rectImage.left = ((lPageWidth - lImageWidth) / 2) + BORDER_LEFT;
					rectImage.right = rectImage.left + lImageWidth;

					PrintImageOnPdf(pSel, &lPrintedImages, rectImage);
				}
				else 
				{
					// sei immagini per pagina //

					IMAGE_TO_PRINT* pSel = NULL;
					CRect rectImage;
					long lTotHeight = (lImageHeight * 3) + (theApp.m_nStampaImmaginiDistanzaImmagini * 2);

					//

					rectImage.left = ((lPageWidth - lImageWidth) / 2) + BORDER_LEFT;
					rectImage.right = rectImage.left + lImageWidth;

					// sopra in centro //

					pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

					rectImage.top = ((lPageHeight - lTotHeight) / 2) + lTop;
					rectImage.bottom = rectImage.top + lImageHeight;

					PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

					// in mezzo in centro //

					pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

					rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
					rectImage.bottom = rectImage.top + lImageHeight;

					PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

					// sotto in centro //

					pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

					rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
					rectImage.bottom = rectImage.top + lImageHeight;

					PrintImageOnPdf(pSel, &lPrintedImages, rectImage);
				}

				break;
			}
			case 4:
			{
				IMAGE_TO_PRINT* pSel = NULL;
				CRect rectImage;
				long lTotHeight = (lImageHeight * 2) + theApp.m_nStampaImmaginiDistanzaImmagini;
				long lTotWidth = (lImageWidth * 2) + theApp.m_nStampaImmaginiDistanzaImmagini;

				//

				rectImage.top = ((lPageHeight - lTotHeight) / 2) + lTop;
				rectImage.bottom = rectImage.top + lImageHeight;

				// sopra a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// sopra a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// sotto a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// sotto a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				break;
			}
			case 5:
			{
				IMAGE_TO_PRINT* pSel = NULL;
				CRect rectImage;
				long lTotHeight = (lImageHeight * 3) + (theApp.m_nStampaImmaginiDistanzaImmagini * 2);
				long lTotWidth = (lImageWidth * 2) + theApp.m_nStampaImmaginiDistanzaImmagini;

				//

				rectImage.top = ((lPageHeight - lTotHeight) / 2) + lTop;
				rectImage.bottom = rectImage.top + lImageHeight;

				// sopra a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// sopra a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// in mezzo a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// in mezzo a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// sotto in centro //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lImageWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				break;
			}
			case 6:
			{
				IMAGE_TO_PRINT* pSel = NULL;
				CRect rectImage;
				long lTotHeight = (lImageHeight * 3) + (theApp.m_nStampaImmaginiDistanzaImmagini * 2);
				long lTotWidth = (lImageWidth * 2) + theApp.m_nStampaImmaginiDistanzaImmagini;

				//

				rectImage.top = ((lPageHeight - lTotHeight) / 2) + lTop;
				rectImage.bottom = rectImage.top + lImageHeight;

				// sopra a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// sopra a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// in mezzo a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// in mezzo a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// sotto a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// sotto a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				break;
			}
			case 7:
			{
				IMAGE_TO_PRINT* pSel = NULL;
				CRect rectImage;
				long lTotHeight = (lImageHeight * 4) + (theApp.m_nStampaImmaginiDistanzaImmagini * 3);
				long lTotWidth = (lImageWidth * 2) + theApp.m_nStampaImmaginiDistanzaImmagini;

				//

				rectImage.top = ((lPageHeight - lTotHeight) / 2) + lTop;
				rectImage.bottom = rectImage.top + lImageHeight;

				// angolo sopra a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// angolo sopra a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// centro-sopra a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// centro-sopra a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// centro-sotto a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// centro-sotto a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// sotto in centro //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lImageWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				break;
			}
			case 8:
			{
				IMAGE_TO_PRINT* pSel = NULL;
				CRect rectImage;
				long lTotHeight = (lImageHeight * 4) + (theApp.m_nStampaImmaginiDistanzaImmagini * 3);
				long lTotWidth = (lImageWidth * 2) + theApp.m_nStampaImmaginiDistanzaImmagini;

				//

				rectImage.top = ((lPageHeight - lTotHeight) / 2) + lTop;
				rectImage.bottom = rectImage.top + lImageHeight;

				// angolo sopra a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// angolo sopra a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// centro-sopra a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// centro-sopra a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// centro-sotto a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// centro-sotto a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				rectImage.top = rectImage.bottom + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.bottom = rectImage.top + lImageHeight;

				// angolo sotto a sinistra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = ((lPageWidth - lTotWidth) / 2) + BORDER_LEFT;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				// angolo sotto a destra //

				pSel = listImagesToPrint.GetAt(listImagesToPrint.FindIndex(lPrintedImages));

				rectImage.left = rectImage.right + theApp.m_nStampaImmaginiDistanzaImmagini;
				rectImage.right = rectImage.left + lImageWidth;

				PrintImageOnPdf(pSel, &lPrintedImages, rectImage);

				//

				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
		}

		// Sandro 10/07/2014 // stampo una scritta "invisibile" perchè altrimenti AmPdfCreatorHaru non capisce che deve andare alla pagina nuova //

		LOGFONT lfCommentAndPoint;
		theApp.m_fontBold.GetLogFont(&lfCommentAndPoint);
		lfCommentAndPoint.lfHeight = (lfCommentAndPoint.lfHeight * 3 / 5);

		TAG_ELEMENT teStringaVuota;
		teStringaVuota.lFieldType = TYPE_TEXT;
		teStringaVuota.strFieldValue = "";
		teStringaVuota.rectInMm = CRect(1, 1, 1, 1);
		teStringaVuota.rgbColor = RGB(0, 0, 0);
		teStringaVuota.lMyCheck = 0;
		teStringaVuota.lMyParam = 0;
		teStringaVuota.lfFont = lfCommentAndPoint;
		teStringaVuota.hAlignment = HPDF_TALIGN_CENTER;
		teStringaVuota.lRotation = ROTATION_NONE;
		teStringaVuota.strComment = "";
		teStringaVuota.bCanExpand = FALSE;
		teStringaVuota.bPaintBorder = FALSE;

		AmPdfCreator_PrintText(teStringaVuota, NULL, NULL);

		//

		listImagesPerPage.GetNext(pos);
	}

	// svuoto la lista temporanea //
	while(listImagesToPrint.GetCount() > 0)
	{
		delete listImagesToPrint.GetHead();
		listImagesToPrint.RemoveHead();
	}
}

void CEsamiView::PrintImagesFromDibs(CList<CDib*>* pListImmagini)
{
	if (pListImmagini->GetCount() > 0)
	{
		// calcolo il bordo superiore //
		long lTop = BORDER_TOP;

		// calcolo il bordo inferiore //
		long lBottom = BORDER_BOTTOM;

		// calcolo le dimensioni effettive dell'area stampabile //
		long lPageHeight = lBottom - lTop;
		long lPageWidth = BORDER_RIGHT - BORDER_LEFT;

		// calcolo le dimensioni che avrà ogni singola immagine stampata //
		long lImageHeight = lPageHeight;
		long lImageWidth = lPageWidth;

		CRect rectImage;
		rectImage.left = ((lPageWidth - lImageWidth) / 2) + BORDER_LEFT;
		rectImage.top = ((lPageHeight - lImageHeight) / 2) + lTop;
		rectImage.right = rectImage.left + lImageWidth;
		rectImage.bottom = rectImage.top + lImageHeight;

		long lImageNumber = 0;
		POSITION pos = pListImmagini->GetHeadPosition();
		while(pos != NULL)
		{
			if (lImageNumber > 0)
				AmPdfCreator_AddPage();

			PrintImageOnPdfFromDib(pListImmagini->GetAt(pos), lImageNumber, rectImage);

			// Sandro 10/07/2014 // stampo una scritta "invisibile" perchè altrimenti AmPdfCreatorHaru non capisce che deve andare alla pagina nuova //

			LOGFONT lfCommentAndPoint;
			theApp.m_fontBold.GetLogFont(&lfCommentAndPoint);
			lfCommentAndPoint.lfHeight = (lfCommentAndPoint.lfHeight * 3 / 5);

			TAG_ELEMENT teStringaVuota;
			teStringaVuota.lFieldType = TYPE_TEXT;
			teStringaVuota.strFieldValue = "";
			teStringaVuota.rectInMm = CRect(1, 1, 1, 1);
			teStringaVuota.rgbColor = RGB(0, 0, 0);
			teStringaVuota.lMyCheck = 0;
			teStringaVuota.lMyParam = 0;
			teStringaVuota.lfFont = lfCommentAndPoint;
			teStringaVuota.hAlignment = HPDF_TALIGN_CENTER;
			teStringaVuota.lRotation = ROTATION_NONE;
			teStringaVuota.strComment = "";
			teStringaVuota.bCanExpand = FALSE;
			teStringaVuota.bPaintBorder = FALSE;

			AmPdfCreator_PrintText(teStringaVuota, NULL, NULL);

			//

			lImageNumber++;
			pListImmagini->GetNext(pos);
		}
	}
}
#undef BORDER_LEFT
#undef BORDER_TOP
#undef BORDER_RIGHT
#undef BORDER_BOTTOM
#undef BORDER_PATIENT

void CEsamiView::PrintImageOnPdf(IMAGE_TO_PRINT* pSel, long* pImageOnPdfNumber, CRect rectImage)
{
	if (pSel != NULL)
	{
		TAG_ELEMENT tagElement;
		tagElement.lFieldType = TYPE_IMAGE;
		tagElement.strFieldValue.Format("Immagine%02li", *pImageOnPdfNumber);
		tagElement.rectInMm = rectImage;
		tagElement.lMyParam = -1; // numero da stampare //
		tagElement.strComment = "";
		tagElement.bPaintBorder = FALSE;

		// faccio inserire il disco //
		if (pSel->m_bConfirmed)
		{
			while(GetVolumeName() != pSel->m_strDvdLabel)
			{
				CEspelliDlg	dlg(this, pSel->m_strDvdLabel);
				if (dlg.DoModal() == IDCANCEL)
					break;
			}
		}

		//
		m_pImgManager->SetCurrentIDs(pSel->m_lPaziente, pSel->m_lEsame);

		long lCurPage = pSel->m_lFrame;
		long lTotPage = pSel->m_lFrame + 1;
		HBITMAP hBitOld = m_pImgManager->GetImgMP(pSel->m_lID, FALSE, FALSE, FALSE, lCurPage, lTotPage);

		// passo l'immagine alla libreria //
		if (hBitOld != NULL)
		{
			// Sandro 08/03/2012 // RIMA 11-064.5 //
			HBITMAP hBitNew = CImageElaboration(hBitOld).ApplyBrightnessContrast(theApp.m_iIEBrightness, theApp.m_iIEContrastRMin, theApp.m_iIEContrastRMax, theApp.m_iIEContrastGMin, theApp.m_iIEContrastGMax, theApp.m_iIEContrastBMin, theApp.m_iIEContrastBMax);

			//
			Bitmap* pBitmap = Bitmap::FromHBITMAP(hBitNew, NULL);
			if (pBitmap->GetLastStatus() == Gdiplus::Ok)
			{
				if (theApp.m_bPDFImmaginiNonCompresse)
				{
					USES_CONVERSION;
					CLSID idClass;
					if (GetEncoderClsid(L"image/png", &idClass))
					{
						CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
						if (pBitmap->Save(T2W(strFileTemp), &idClass, NULL) == Gdiplus::Ok)
							AmPdfCreator_AddImageFromFilePng(tagElement.strFieldValue, strFileTemp);
					}
				}
				else
				{
					USES_CONVERSION;
					CLSID idClass;
					if (GetEncoderClsid(L"image/jpeg", &idClass))
					{
						EncoderParameters encoderParameters;
						encoderParameters.Count = 1;
						encoderParameters.Parameter[0].Guid = EncoderQuality;
						encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
						encoderParameters.Parameter[0].NumberOfValues = 1;
						ULONG quality = theApp.m_lPDFQualitaImmaginiCompresse; // Sandro 20/09/2013 // RAS 20130112 //
						encoderParameters.Parameter[0].Value = &quality;

						CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
						if (pBitmap->Save(T2W(strFileTemp), &idClass, &encoderParameters) == Gdiplus::Ok)
							AmPdfCreator_AddImageFromFileJpg(tagElement.strFieldValue, strFileTemp);
					}
				}
			}
			delete pBitmap;
			DeleteObject(hBitOld);
			DeleteObject(hBitNew);
		}

		// prendo il commento //
		if (theApp.m_bStampaImmaginiStampaCommenti)
		{
			if ((theApp.m_nApplication == PRG_DERMOX) && theApp.m_bStampaCommentoDentroImmagini)
			{
				long lZZZ;
				CString sZZZ;
				CVistaImmaginiNumeroDermoxSet().GetNumeroDermoxSede(pSel->m_lID, lZZZ, sZZZ);

				if (lZZZ > 0)
					tagElement.strComment.Format("%li", lZZZ);
				else
					tagElement.strComment = "";

				if (!sZZZ.IsEmpty())
				{
					if (!tagElement.strComment.IsEmpty())
						tagElement.strComment += " - ";

					tagElement.strComment += sZZZ;
				}

				CString sComm = m_pImgManager->GetCommento(pSel->m_lID);
				if (!sComm.IsEmpty())
				{
					if (!tagElement.strComment.IsEmpty())
						tagElement.strComment += " - ";

					tagElement.strComment += sComm;
				}
			}
			else
			{
				tagElement.strComment = m_pImgManager->GetCommento(pSel->m_lID);
			}
		}

		// stampo l'immagine //
		AmPdfCreator_PrintImage(tagElement);

		// Sandro 24/09/2015 //
		if (theApp.m_bStampaImmaginiStampaNumero)
		{
			CString sNumber;
			sNumber.Format(" %li", (*pImageOnPdfNumber) + 1);

			LOGFONT lfCommentAndPoint;
			theApp.m_fontBold.GetLogFont(&lfCommentAndPoint);
			lfCommentAndPoint.lfHeight = (lfCommentAndPoint.lfHeight * 3 / 5);

			TAG_ELEMENT tagNumber;
			tagNumber.lFieldType = TYPE_TEXT;
			tagNumber.strFieldValue = sNumber;
			tagNumber.rectInMm = tagElement.rectInMm;
			tagNumber.rgbColor = RGB(255, 255, 255);
			tagNumber.lMyCheck = 0;
			tagNumber.lMyParam = 0;
			tagNumber.lfFont = lfCommentAndPoint;
			tagNumber.hAlignment = HPDF_TALIGN_LEFT;
			tagNumber.lRotation = ROTATION_NONE;
			tagNumber.strComment = "";
			tagNumber.bCanExpand = FALSE;
			tagNumber.bPaintBorder = FALSE;

			// stampo il numero //
			AmPdfCreator_PrintText(tagNumber, NULL, NULL);
		}

		// Sandro 29/05/2014 // salvo la lista di immagini da contrassegnare come stampate //
		m_listIDStampate.AddTail(pSel->m_lID);
	}

	(*pImageOnPdfNumber)++;
}

void CEsamiView::PrintImageOnPdfFromDib(CDib* pDib, long lImageNumber, CRect rectImage)
{
	TAG_ELEMENT tagElement;
	tagElement.lFieldType = TYPE_IMAGE;
	tagElement.strFieldValue.Format("Immagine%02li", lImageNumber);
	tagElement.rectInMm = rectImage;
	tagElement.lMyParam = -1; // numero da stampare //
	tagElement.strComment = "";
	tagElement.bPaintBorder = FALSE;

	//
	HBITMAP hBitmap = pDib->BitmapFromDib(GetDC()->m_hDC, NULL, DIB_PAL_COLORS);

	// passo l'immagine alla libreria //
	if (hBitmap != NULL)
	{
		Bitmap* pBitmap = Bitmap::FromHBITMAP(hBitmap, NULL);
		if (pBitmap->GetLastStatus() == Gdiplus::Ok)
		{
			USES_CONVERSION;
			CLSID idClass;
			if (GetEncoderClsid(L"image/png", &idClass))
			{
				CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
				if (pBitmap->Save(T2W(strFileTemp), &idClass, NULL) == Gdiplus::Ok)
					AmPdfCreator_AddImageFromFilePng(tagElement.strFieldValue, strFileTemp);
			}
		}
		delete pBitmap;
		DeleteObject(hBitmap);
	}

	// stampo l'immagine //
	AmPdfCreator_PrintImage(tagElement);
}

void CEsamiView::PrintReport(long lHeaderHeight, long lFooterHeight, STRUCT_STAMPA* pStruct)
{
	// prendo l'altezza della pagina //
	long lPageHeight = GetPrivateProfileInt("Page", "Height", 297, pStruct->m_sReportFilePrinting);

	// tengo traccia dei dati riguardanti la riga corrente di campi (campi aventi il TOP alla stessa Y) //
	long lRigaCorrenteY;				// --> Y della riga di campi attuale
	long lRigaCorrentePagineAggiunte;	// --> numero MASSIMO di pagine aggiunte dall'attuale riga di campi
	long lRigaCorrenteOffset;			// --> offset "MASSIMO" raggiunto dalla riga attuale di campi
	long lOffsetComplessivo;			// --> offset da applicare a tutti i campi del report

	//
	int nTotSection = GetPrivateProfileInt("List", "TotSection", 0, pStruct->m_sReportFilePrinting);
	for(int nSection = 1; nSection <= nTotSection; nSection++)
	{
		CString strSezione;
		strSezione.Format("Section%d", nSection);

		ENUM_FIELD_TYPE lFieldType = GetFieldType(GetPrivateProfileString("List", strSezione, "", pStruct->m_sReportFilePrinting));
		if (lFieldType != TYPE_NONE)
		{
			TAG_ELEMENT tagElement;

			//
			tagElement.lFieldType = lFieldType;

			//
			tagElement.strFieldValue = GetPrivateProfileString(strSezione, "Value", "", pStruct->m_sReportFilePrinting);

			//
			tagElement.rectInMm.left = GetPrivateProfileInt(strSezione, "Left", 0, pStruct->m_sReportFilePrinting);
			tagElement.rectInMm.right = GetPrivateProfileInt(strSezione, "Right", 0, pStruct->m_sReportFilePrinting);
			tagElement.rectInMm.top = GetPrivateProfileInt(strSezione, "Top", 0, pStruct->m_sReportFilePrinting);
			tagElement.rectInMm.bottom = GetPrivateProfileInt(strSezione, "Bottom", 0, pStruct->m_sReportFilePrinting);

			//
			tagElement.rgbColor = (COLORREF)GetPrivateProfileInt(strSezione, "Color", 0, pStruct->m_sReportFilePrinting);

			//
			tagElement.lMyCheck = GetPrivateProfileInt(strSezione, "Check", FALSE, pStruct->m_sReportFilePrinting);

			//
			tagElement.lMyParam = GetPrivateProfileInt(strSezione, "Param", 0, pStruct->m_sReportFilePrinting);

			//
			strcpy_s(tagElement.lfFont.lfFaceName, GetPrivateProfileString(strSezione, "Font Name", "MS Sans Serif", pStruct->m_sReportFilePrinting));
			tagElement.lfFont.lfHeight = GetPrivateProfileInt(strSezione, "Font Height", -13, pStruct->m_sReportFilePrinting);
			tagElement.lfFont.lfWeight = GetPrivateProfileInt(strSezione, "Font Weight", 400, pStruct->m_sReportFilePrinting);
			tagElement.lfFont.lfUnderline = (unsigned char)GetPrivateProfileInt(strSezione, "Font Under", 0, pStruct->m_sReportFilePrinting);
			tagElement.lfFont.lfItalic = (unsigned char)GetPrivateProfileInt(strSezione, "Font Italic", 0, pStruct->m_sReportFilePrinting);

			//
			switch(GetPrivateProfileInt(strSezione, "Alignment", 0, pStruct->m_sReportFilePrinting))
			{
				case 1:
				{
					tagElement.hAlignment = HPDF_TALIGN_CENTER;
					break;
				}
				case 2:
				{
					tagElement.hAlignment = HPDF_TALIGN_RIGHT;
					break;
				}
				case 3:
				{
					tagElement.hAlignment = HPDF_TALIGN_JUSTIFY;
					break;
				}
				default:
				{
					tagElement.hAlignment = HPDF_TALIGN_LEFT;
					break;
				}
			}

			//
			switch(GetPrivateProfileInt(strSezione, "Rotation", 0, pStruct->m_sReportFilePrinting))
			{
				case 1:
				{
					tagElement.lRotation = ROTATION_90_CW;
					break;
				}
				case 2:
				{
					tagElement.lRotation = ROTATION_90_CCW;
					break;
				}
				default:
				{
					tagElement.lRotation = ROTATION_NONE;
					break;
				}
			}

			//
			tagElement.strComment = "";

			//
			tagElement.bCanExpand = FALSE;

			//
			tagElement.bPaintBorder = FALSE;

			// Sandro 14/10/2011 //
			if (nSection == 1)
			{
				lRigaCorrenteY = tagElement.rectInMm.top;
				lRigaCorrentePagineAggiunte = 0;
				lRigaCorrenteOffset = 0;
				lOffsetComplessivo = 0;
			}
			else
			{
				if (tagElement.rectInMm.top != lRigaCorrenteY)
				{
					lRigaCorrenteY = tagElement.rectInMm.top;
					lRigaCorrentePagineAggiunte = 0;

					lOffsetComplessivo += lRigaCorrenteOffset;
					lRigaCorrenteOffset = 0;

					if (lOffsetComplessivo > 0)
					{
						// qui ci entro solo DOPO che è stato stampato un campo lungo e solo quando i campi vengono SPOSTATI in BASSO (unica situazione in cui potrebbero non starci più nel foglio) //
						// ho una nuova fila di campi... li verifico tutti per vedere se uno di questi andrebbe oltre la fine della pagina //

						BOOL bInserisciPaginaNuova = FALSE;
						int nMySection = nSection;
						CString strMySection;

						long lTop = tagElement.rectInMm.top;
						long lBottom = tagElement.rectInMm.bottom + lOffsetComplessivo;

						long lFooter = lPageHeight - lFooterHeight;

						while(lTop == lRigaCorrenteY)
						{
							if (lBottom > lFooter)
							{
								// dobbiamo inserire la pagina nuova //
								bInserisciPaginaNuova = TRUE;
								break;
							}

							nMySection++;

							// Sandro 25/08/2014 // se tutti i campi alla fine sono allineati si impallava... //
							if (nMySection > nTotSection)
								break;
							//

							strMySection.Format("Section%d", nMySection);

							lTop = GetPrivateProfileInt(strMySection, "Top", 0, pStruct->m_sReportFilePrinting);
							lBottom = GetPrivateProfileInt(strMySection, "Bottom", 0, pStruct->m_sReportFilePrinting) + lOffsetComplessivo;
						}

						if (bInserisciPaginaNuova)
						{
							// cambio pagina //
							AmPdfCreator_AddPage();

							// ora che sono in una pagina nuova modifico l'offset per fare in modo che i controlli ripartano dal bordo superiore //
							lOffsetComplessivo = -(lRigaCorrenteY - lHeaderHeight);
						}
					}
				}

				tagElement.rectInMm.OffsetRect(0, lOffsetComplessivo);
			}

			// procedo con la stampa //
			switch(tagElement.lFieldType)
			{
				case TYPE_ICON:
				{
					// passo l'immagine alla libreria //
					HBITMAP hBitOld1;
					if (m_pImgManager->LoadLocalImageEx(tagElement.strFieldValue, &hBitOld1) > 0)
					{
						// Sandro 08/03/2012 // RIMA 11-064.5 //
						HBITMAP hBitNew = CImageElaboration(hBitOld1).ApplyBrightnessContrast(theApp.m_iIEBrightness, theApp.m_iIEContrastRMin, theApp.m_iIEContrastRMax, theApp.m_iIEContrastGMin, theApp.m_iIEContrastGMax, theApp.m_iIEContrastBMin, theApp.m_iIEContrastBMax);

						//
						Bitmap* pBitmap = Bitmap::FromHBITMAP(hBitNew, NULL);
						if (pBitmap->GetLastStatus() == Gdiplus::Ok)
						{
							if (theApp.m_bPDFImmaginiNonCompresse)
							{
								USES_CONVERSION;
								CLSID idClass;
								if (GetEncoderClsid(L"image/png", &idClass))
								{
									CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
									if (pBitmap->Save(T2W(strFileTemp), &idClass, NULL) == Gdiplus::Ok)
										AmPdfCreator_AddImageFromFilePng(tagElement.strFieldValue, strFileTemp);
								}
							}
							else
							{
								USES_CONVERSION;
								CLSID idClass;
								if (GetEncoderClsid(L"image/jpeg", &idClass))
								{
									EncoderParameters encoderParameters;
									encoderParameters.Count = 1;
									encoderParameters.Parameter[0].Guid = EncoderQuality;
									encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
									encoderParameters.Parameter[0].NumberOfValues = 1;
									ULONG quality = theApp.m_lPDFQualitaImmaginiCompresse; // Sandro 20/09/2013 // RAS 20130112 //
									encoderParameters.Parameter[0].Value = &quality;

									CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
									if (pBitmap->Save(T2W(strFileTemp), &idClass, &encoderParameters) == Gdiplus::Ok)
										AmPdfCreator_AddImageFromFileJpg(tagElement.strFieldValue, strFileTemp);
								}
							}
						}
						delete pBitmap;
						DeleteObject(hBitOld1);
						DeleteObject(hBitNew);
					}

					// stampo l'immagine //
					AmPdfCreator_PrintIcon(tagElement);

					//
					break;
				}
				case TYPE_LINE:
				{
					// stampo la linea //
					AmPdfCreator_PrintLine(tagElement);

					//
					break;
				}
				case TYPE_TEXT:
				{
					// stampo il testo //
					AmPdfCreator_PrintText(tagElement, NULL, NULL);

					//
					break;
				}
				case TYPE_LABEL:
				{
					// stampo l'etichetta, se il relativo campo è valido //

					TAG_ELEMENT tagTemp = tagElement;

					CList<TAG_ELEMENT> listElements;
					if (GetField(listElements, tagElement, TRUE))
					{
						tagElement = tagTemp;

						// Sandro 09/11/2016 // richiesta telefonica di Pilotto (dott.ssa Stanzani) //

						BOOL bSaltaTutto = FALSE;
						if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && tagElement.strFieldValue.CompareNoCase("ChiusuraEsame.Anagrafica") == 0)
						{
							long lIDUtenteConvalida = 0;
							if (m_pEsamiSet->m_bLocked)
								lIDUtenteConvalida = m_pEsamiSet->m_lIdUtenteLock;
							else
								lIDUtenteConvalida = GetUserIDForLockSuperlock();

							long lIDUtenteChiusura = 0;
							if (m_pEsamiSet->m_bSuperLocked)
								lIDUtenteChiusura = m_pEsamiSet->m_lIdUtenteSuperLock;
							else
								lIDUtenteChiusura = GetUserIDForLockSuperlock();

							if (lIDUtenteConvalida == lIDUtenteChiusura)
							{
								tagElement.strFieldValue = theApp.GetMessageString(IDS_REFERTATO_E_FIRMATO_DA);
								tagElement.strFieldValue.Trim();

								if (!tagElement.strFieldValue.IsEmpty())
									AmPdfCreator_PrintText(tagElement, NULL, NULL);

								bSaltaTutto = TRUE;
							}
						}

						//

						if (!bSaltaTutto)
						{
							for (int i = 0; i < endox_report_field_num_total; i++)
							{
								if (CFieldDlg::m_strFieldEndox[i].sReport == tagElement.strFieldValue)
								{
									tagElement.strFieldValue = CFieldDlg::m_strFieldEndox[i].sCombo;
									tagElement.strFieldValue.Trim();

									if (!tagElement.strFieldValue.IsEmpty())
										AmPdfCreator_PrintText(tagElement, NULL, NULL);

									break;
								}
							}
						}
					}

					//
					break;
				}
				case TYPE_FIELD:
				{
					// salvo il bottom del rect originale //
					long lOriginalBottom = tagElement.rectInMm.bottom;

					// carico il campo in una lista (alcuni campi possono venire spezzati in più testi diversi) //
					CList<TAG_ELEMENT> listElements;
					GetField(listElements, tagElement, FALSE);

					// stampo tutti gli elementi //
					long lLocalAddedPages = 0;
					long lLocalY = -1;
					long lLocalOffset1 = 0;
					long lLocalOffset2 = 0;
					long lFinalOffset = 0;

					POSITION pos = listElements.GetHeadPosition();
					while(pos != NULL)
					{
						TAG_ELEMENT tagElement = listElements.GetAt(pos);

						if (lLocalY != tagElement.rectInMm.top)
						{
							lLocalY = tagElement.rectInMm.top;
							lLocalOffset2 += lLocalOffset1;
							lLocalOffset1 = 0;
						}

						tagElement.rectInMm.OffsetRect(0, lLocalOffset2);

						long lFieldAddedPages = 0;
						long lFieldOffset = 0;
						if (tagElement.lFieldType == TYPE_ICON)
						{
							// tagElement.lMyParam = -1;
							AmPdfCreator_PrintIcon(tagElement);
						}
						else if (tagElement.lFieldType == TYPE_LINE)
						{
							AmPdfCreator_PrintLine(tagElement);
						}
						else if (tagElement.lFieldType == TYPE_RTF)
						{
							AmPdfCreator_PrintRTF(tagElement, &lFieldAddedPages, &lFieldOffset);
						}
						else
						{
							// Sandro 04/11/2013 // RAS 20130165 //
							if (tagElement.strFieldValue == "Scheda.ColoreTipoEsame")
							{
								AmPdfCreator_PrintRect(tagElement);
							}
							else
							{
								if (theApp.m_sBarCodeFontName.CompareNoCase(tagElement.lfFont.lfFaceName) == 0)
									tagElement.strFieldValue = "*" + tagElement.strFieldValue + "*";

								AmPdfCreator_PrintText(tagElement, &lFieldAddedPages, &lFieldOffset);
							}
						}

						if (lFieldAddedPages > lLocalAddedPages)
						{
							lLocalAddedPages = lFieldAddedPages;

							lLocalOffset1 = lFieldOffset;

							lFinalOffset = tagElement.rectInMm.bottom + lFieldOffset - lOriginalBottom;
						}
						else if (lFieldAddedPages == lLocalAddedPages)
						{
							if (lFieldOffset > lLocalOffset1)
								lLocalOffset1 = lFieldOffset;

							if (tagElement.rectInMm.bottom + lFieldOffset > lOriginalBottom)
								lFinalOffset = tagElement.rectInMm.bottom + lFieldOffset - lOriginalBottom;
						}

						listElements.GetNext(pos);
					}
					listElements.RemoveAll();

					if (lLocalAddedPages > lRigaCorrentePagineAggiunte)
					{
						lRigaCorrentePagineAggiunte = lLocalAddedPages;
						lRigaCorrenteOffset = lFinalOffset;
					}
					else if (lLocalAddedPages == lRigaCorrentePagineAggiunte)
					{
						if (lFinalOffset > lRigaCorrenteOffset)
							lRigaCorrenteOffset = lFinalOffset;
					}

					//
					break;
				}
				case TYPE_PARAM:
				{
					// carico il parametro in una lista (alcuni parametri possono venire spezzati in più testi diversi) //
					CList<TAG_ELEMENT> listElements;
					GetParam(listElements, tagElement);

					// stampo tutti gli elementi //
					POSITION pos = listElements.GetHeadPosition();
					while(pos != NULL)
						AmPdfCreator_PrintText(listElements.GetNext(pos), NULL, NULL);
					listElements.RemoveAll();

					//
					break;
				}
				case TYPE_IMAGE:
				{
					if (pStruct->m_lImagePrinting < pStruct->m_lImageToPrint)
					{
						CObSelect* pSel = (CObSelect*)(CFileBmp::m_listPrinter.GetAt(pStruct->m_lImagePrinting));
						if (pSel != NULL)
						{
							tagElement.strFieldValue.Format("Immagine%02li", pStruct->m_lImagePrinting);

							// prendo il commento dell'immagine (solo se devo stamparlo) //
							if (tagElement.lMyCheck > 0)
							{
								POSITION pos = m_pFormImmagini->m_ImgListOrgani.GetHeadPosition();
								while(pos != NULL)
								{
									if (pSel->m_lID == m_pFormImmagini->m_ImgListOrgani.GetAt(pos).img.lID)
									{
										if ((theApp.m_nApplication == PRG_DERMOX) && theApp.m_bStampaCommentoDentroImmagini)
										{
											long lZZZ;
											CString sZZZ;
											CVistaImmaginiNumeroDermoxSet().GetNumeroDermoxSede(pSel->m_lID, lZZZ, sZZZ);

											if (lZZZ > 0)
												tagElement.strComment.Format("%li", lZZZ);
											else
												tagElement.strComment = "";

											if (!sZZZ.IsEmpty())
											{
												if (!tagElement.strComment.IsEmpty())
													tagElement.strComment += " - ";

												tagElement.strComment += sZZZ;
											}

											CString sComm = m_pFormImmagini->m_ImgListOrgani.GetAt(pos).img.szDescription;
											if (!sComm.IsEmpty())
											{
												if (!tagElement.strComment.IsEmpty())
													tagElement.strComment += " - ";

												tagElement.strComment += sComm;
											}
										}
										else
										{
											tagElement.strComment = m_pFormImmagini->m_ImgListOrgani.GetAt(pos).img.szDescription;
										}
										break;
									}

									m_pFormImmagini->m_ImgListOrgani.GetNext(pos);
								}
							}

							// prendo il numero dell'immagine //
							POSITION pos = pStruct->m_listImmaginiStampa.FindIndex(pStruct->m_lImagePrinting);
							if (pos != NULL)
								tagElement.lMyParam = pStruct->m_listImmaginiStampa.GetAt(pos);
							else
								tagElement.lMyParam = -1;

							// passo l'immagine alla libreria //
							m_pImgManager->SetCurrentIDs(pSel->m_lPaziente, pSel->m_lEsame);
							HBITMAP hBitOld = m_pImgManager->GetImg(pSel->m_lID, FALSE, FALSE, FALSE);
							if (hBitOld != NULL)
							{
								// Sandro 08/03/2012 // RIMA 11-064.5 //
								HBITMAP hBitNew = CImageElaboration(hBitOld).ApplyBrightnessContrast(theApp.m_iIEBrightness, theApp.m_iIEContrastRMin, theApp.m_iIEContrastRMax, theApp.m_iIEContrastGMin, theApp.m_iIEContrastGMax, theApp.m_iIEContrastBMin, theApp.m_iIEContrastBMax);

								//
								Bitmap* pBitmap = Bitmap::FromHBITMAP(hBitNew, NULL);
								if (pBitmap->GetLastStatus() == Gdiplus::Ok)
								{
									if (theApp.m_bPDFImmaginiNonCompresse)
									{
										USES_CONVERSION;
										CLSID idClass;
										if (GetEncoderClsid(L"image/png", &idClass))
										{
											CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
											if (pBitmap->Save(T2W(strFileTemp), &idClass, NULL) == Gdiplus::Ok)
												AmPdfCreator_AddImageFromFilePng(tagElement.strFieldValue, strFileTemp);
										}
									}
									else
									{
										USES_CONVERSION;
										CLSID idClass;
										if (GetEncoderClsid(L"image/jpeg", &idClass))
										{
											EncoderParameters encoderParameters;
											encoderParameters.Count = 1;
											encoderParameters.Parameter[0].Guid = EncoderQuality;
											encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
											encoderParameters.Parameter[0].NumberOfValues = 1;
											ULONG quality = theApp.m_lPDFQualitaImmaginiCompresse; // Sandro 20/09/2013 // RAS 20130112 //
											encoderParameters.Parameter[0].Value = &quality;

											CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
											if (pBitmap->Save(T2W(strFileTemp), &idClass, &encoderParameters) == Gdiplus::Ok)
												AmPdfCreator_AddImageFromFileJpg(tagElement.strFieldValue, strFileTemp);
										}
									}
								}
								delete pBitmap;
								DeleteObject(hBitOld);
								DeleteObject(hBitNew);
							}

							// stampo l'immagine //
							AmPdfCreator_PrintImage(tagElement);

							// Sandro 29/05/2014 // salvo la lista di immagini da contrassegnare come stampate //
							m_listIDStampate.AddTail(pSel->m_lID);
						}

						pStruct->m_lImagePrinting++;
					}

					break;
				}
				case TYPE_ORGAN:
				{
					tagElement.strFieldValue = "";

					long lOrganIndex = 0;
					if (theApp.m_nApplication == PRG_DERMOX)
					{
						char szPathImm[MAX_PATH];
						char szPathMin[MAX_PATH];
						if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
						{
							tagElement.strFieldValue.Format("%s\\Organ\\sagome.org", szPathImm);
						}
						else
						{
							ASSERT(FALSE);
						}
					}
					else
					{
						if (pStruct->m_lOrganPrinting < pStruct->m_lOrganToPrint)
						{
							lOrganIndex = GetOrganIndex(pStruct->m_lOrganPrinting, pStruct->m_listPuntiStampa);
							if (lOrganIndex > 0)
							{
								// prendo il nome del file immagine dell'organo //
								CString strFilter;
								strFilter.Format("ID=%li", lOrganIndex);

								COrganiSet setOrgani;
								setOrgani.SetOpenFilter(strFilter);
								if (setOrgani.OpenRecordset("CEsamiView::AddElementToList"))
								{
									if (!setOrgani.IsEOF())
									{
										char szPathImm[MAX_PATH];
										char szPathMin[MAX_PATH];
										if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
										{
											tagElement.strFieldValue.Format("%s\\Organ\\%06li.org", szPathImm, setOrgani.m_lID);
										}
										else
										{
											ASSERT(FALSE);
										}
									}

									setOrgani.CloseRecordset("CEsamiView::AddElementToList");
								}
							}

							pStruct->m_lOrganPrinting++;
						}
					}

					// passo l'immagine alla libreria //
					if (!tagElement.strFieldValue.IsEmpty() && (_access(tagElement.strFieldValue, 00) == 0))
					{
						HBITMAP hBitOld1;
						if (m_pImgManager->LoadLocalImageEx(tagElement.strFieldValue, &hBitOld1) > 0)
						{
							// Sandro 08/03/2012 // RIMA 11-064.5 //
							HBITMAP hBitNew = CImageElaboration(hBitOld1).ApplyBrightnessContrast(theApp.m_iIEBrightness, theApp.m_iIEContrastRMin, theApp.m_iIEContrastRMax, theApp.m_iIEContrastGMin, theApp.m_iIEContrastGMax, theApp.m_iIEContrastBMin, theApp.m_iIEContrastBMax);

							//
							Bitmap* pBitmap = Bitmap::FromHBITMAP(hBitNew, NULL);
							if (pBitmap->GetLastStatus() == Gdiplus::Ok)
							{
								if (theApp.m_bPDFImmaginiNonCompresse)
								{
									USES_CONVERSION;
									CLSID idClass;
									if (GetEncoderClsid(L"image/png", &idClass))
									{
										CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
										if (pBitmap->Save(T2W(strFileTemp), &idClass, NULL) == Gdiplus::Ok)
											AmPdfCreator_AddImageFromFilePng(tagElement.strFieldValue, strFileTemp);
									}
								}
								else
								{
									USES_CONVERSION;
									CLSID idClass;
									if (GetEncoderClsid(L"image/jpeg", &idClass))
									{
										EncoderParameters encoderParameters;
										encoderParameters.Count = 1;
										encoderParameters.Parameter[0].Guid = EncoderQuality;
										encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
										encoderParameters.Parameter[0].NumberOfValues = 1;
										ULONG quality = theApp.m_lPDFQualitaImmaginiCompresse; // Sandro 20/09/2013 // RAS 20130112 //
										encoderParameters.Parameter[0].Value = &quality;

										CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
										if (pBitmap->Save(T2W(strFileTemp), &idClass, &encoderParameters) == Gdiplus::Ok)
											AmPdfCreator_AddImageFromFileJpg(tagElement.strFieldValue, strFileTemp);
									}
								}
							}
							delete pBitmap;
							DeleteObject(hBitOld1);
							DeleteObject(hBitNew);
						}

						// stampo l'organo //
						AmPdfCreator_PrintOrgan(tagElement);

						// stampo i punti //
						if (theApp.m_nApplication == PRG_DERMOX)
						{
							CString strFilter;
							strFilter.Format("IDPaziente=%li", m_pPazientiSet->m_lContatore);

							CPuntiPazienteSet setPunti;
							setPunti.SetOpenFilter(strFilter);
							if (setPunti.OpenRecordset("CEsamiView::PrintReport"))
							{
								while(!setPunti.IsEOF())
								{
									// imposto l'elemento //
									tagElement.rectInMm = CRect(setPunti.m_lX * 120, setPunti.m_lY * 175, setPunti.m_lX * 120, setPunti.m_lY * 175);
									tagElement.lMyParam = setPunti.m_lNumeroDermox - 1;

									// stampo il punto //
									tagElement.lMyCheck = 1;
									AmPdfCreator_PrintPointAndNumber(tagElement);

									//
									setPunti.MoveNext();
								}

								setPunti.CloseRecordset("CEsamiView::PrintReport");
							}
						}
						else
						{
							long lNumber = 0;
							POSITION pos = pStruct->m_listPuntiStampa.GetHeadPosition();
							while(pos != NULL)
							{
								tagPunti tagPunto = pStruct->m_listPuntiStampa.GetAt(pos);

								if (tagPunto.lIdOrgano == lOrganIndex)
								{
									// imposto l'elemento //
									tagElement.rectInMm = CRect(tagPunto.lX, tagPunto.lY, tagPunto.lX, tagPunto.lY);
									tagElement.lMyParam = lNumber;

									// stampo il punto //
									tagElement.lMyCheck = 0;
									AmPdfCreator_PrintPointAndNumber(tagElement);

									//
									lNumber++;
								}

								pStruct->m_listPuntiStampa.GetNext(pos);
							}
						}
					}

					break;
				}
				default:
				{
					ASSERT(FALSE);
					break;
				}
			}
		}
	}
}

void CEsamiView::PrintReportFromQuery(long lHeaderHeight, long lFooterHeight, STRUCT_STAMPA* pStruct)
{
	// prendo l'altezza della pagina //
	long lPageHeight = GetPrivateProfileInt("Page", "Height", 297, pStruct->m_sReportFilePrinting);

	// tengo traccia dei dati riguardanti la riga corrente di campi (campi aventi il TOP alla stessa Y) //
	long lRigaCorrenteY;				// --> Y della riga di campi attuale
	long lRigaCorrentePagineAggiunte;	// --> numero MASSIMO di pagine aggiunte dall'attuale riga di campi
	long lRigaCorrenteOffset;			// --> offset "MASSIMO" raggiunto dalla riga attuale di campi
	long lOffsetComplessivo;			// --> offset da applicare a tutti i campi del report

	// prendo l'altezza della riga //
	long lRowHeight = GetPrivateProfileInt("Page", "RowHeight", 10, pStruct->m_sReportFilePrinting);

	// prendo la larghezza della pagina //
	long lPageWidth = GetPrivateProfileInt("Page", "Width", 210, pStruct->m_sReportFilePrinting);

	// prendo il numero di campi da stampare in ogni riga //
	int nTotSection = GetPrivateProfileInt("List", "TotSection", 0, pStruct->m_sReportFilePrinting);

	// apro la finestra modeless per ingannare l'attesa dell'utente //
	CExportWaitDlg dlgWait(m_pQueryDlg->m_lTotale, m_pQueryDlg);
	dlgWait.Create(IDD_EXPORT_WAIT, m_pQueryDlg);
	dlgWait.ShowWindow(SW_SHOW);
	BeginWaitCursor();

	// eseguo la stampa per ogni riga dei risultati //
	for(int i = 0; i < m_pQueryDlg->m_lTotale; i++)
	{
		// seleziono il record corretto //
		m_pQueryDlg->SelectListRow(i);

		//
		dlgWait.m_ctrlProgress.SetPos(i);
		dlgWait.RedrawWindow();

		//
		CString strFilter;
		strFilter.Format("Contatore=%li", m_pPazientiSet->m_lContatore);

		m_PazTempSet.SetOpenFilter(strFilter);
		if (m_PazTempSet.OpenRecordset("CEsamiView::PrintReportFromQuery"))
		{
			if (!m_PazTempSet.IsEOF())
			{
				for(int nSect = 0; nSect < nTotSection; nSect++)
				{
					CString strSezione;
					strSezione.Format("Section%d", nSect + 1);

					ENUM_FIELD_TYPE lFieldType = GetFieldType(GetPrivateProfileString("List", strSezione, "", pStruct->m_sReportFilePrinting));
					if (lFieldType != TYPE_NONE)
					{
						TAG_ELEMENT tagElement;

						//
						tagElement.lFieldType = lFieldType;

						//
						tagElement.strFieldValue = GetPrivateProfileString(strSezione, "Value", "", pStruct->m_sReportFilePrinting);

						//
						tagElement.rectInMm.left = GetPrivateProfileInt(strSezione, "Left", 0, pStruct->m_sReportFilePrinting);
						tagElement.rectInMm.right = GetPrivateProfileInt(strSezione, "Right", 0, pStruct->m_sReportFilePrinting);
						tagElement.rectInMm.top = GetPrivateProfileInt(strSezione, "Top", 0, pStruct->m_sReportFilePrinting) + (lRowHeight * i);
						tagElement.rectInMm.bottom = GetPrivateProfileInt(strSezione, "Bottom", 0, pStruct->m_sReportFilePrinting) + (lRowHeight * i);

						//
						tagElement.rgbColor = (COLORREF)GetPrivateProfileInt(strSezione, "Color", 0, pStruct->m_sReportFilePrinting);

						//
						tagElement.lMyCheck = GetPrivateProfileInt(strSezione, "Check", FALSE, pStruct->m_sReportFilePrinting);

						//
						tagElement.lMyParam = GetPrivateProfileInt(strSezione, "Param", 0, pStruct->m_sReportFilePrinting);

						//
						strcpy_s(tagElement.lfFont.lfFaceName, GetPrivateProfileString(strSezione, "Font Name", "MS Sans Serif", pStruct->m_sReportFilePrinting));
						tagElement.lfFont.lfHeight = GetPrivateProfileInt(strSezione, "Font Height", -13, pStruct->m_sReportFilePrinting);
						tagElement.lfFont.lfWeight = GetPrivateProfileInt(strSezione, "Font Weight", 400, pStruct->m_sReportFilePrinting);
						tagElement.lfFont.lfUnderline = (unsigned char)GetPrivateProfileInt(strSezione, "Font Under", 0, pStruct->m_sReportFilePrinting);
						tagElement.lfFont.lfItalic = (unsigned char)GetPrivateProfileInt(strSezione, "Font Italic", 0, pStruct->m_sReportFilePrinting);

						//
						switch(GetPrivateProfileInt(strSezione, "Alignment", 0, pStruct->m_sReportFilePrinting))
						{
							case 1:
							{
								tagElement.hAlignment = HPDF_TALIGN_CENTER;
								break;
							}
							case 2:
							{
								tagElement.hAlignment = HPDF_TALIGN_RIGHT;
								break;
							}
							case 3:
							{
								tagElement.hAlignment = HPDF_TALIGN_JUSTIFY;
								break;
							}
							default:
							{
								tagElement.hAlignment = HPDF_TALIGN_LEFT;
								break;
							}
						}

						//
						switch(GetPrivateProfileInt(strSezione, "Rotation", 0, pStruct->m_sReportFilePrinting))
						{
							case 1:
							{
								tagElement.lRotation = ROTATION_90_CW;
								break;
							}
							case 2:
							{
								tagElement.lRotation = ROTATION_90_CCW;
								break;
							}
							default:
							{
								tagElement.lRotation = ROTATION_NONE;
								break;
							}
						}

						//
						tagElement.strComment = "";

						//
						tagElement.bCanExpand = FALSE;

						//
						tagElement.bPaintBorder = FALSE;

						// Sandro 14/10/2011 //
						if ((i == 0) && (nSect == 0))
						{
							lRigaCorrenteY = tagElement.rectInMm.top;
							lRigaCorrentePagineAggiunte = 0;
							lRigaCorrenteOffset = 0;
							lOffsetComplessivo = 0;
						}
						else
						{
							if (tagElement.rectInMm.top != lRigaCorrenteY)
							{
								lRigaCorrenteY = tagElement.rectInMm.top;
								lRigaCorrentePagineAggiunte = 0;

								lOffsetComplessivo += lRigaCorrenteOffset;
								lRigaCorrenteOffset = 0;

								// if (lOffsetComplessivo > 0)
								{
									// qui ci entro solo DOPO che è stato stampato un campo lungo e solo quando i campi vengono SPOSTATI in BASSO (unica situazione in cui potrebbero non starci più nel foglio) //
									// ho una nuova fila di campi... li verifico tutti per vedere se uno di questi andrebbe oltre la fine della pagina //

									BOOL bInserisciPaginaNuova = FALSE;
									int nMySection = nSect;
									CString strMySection;

									long lTop = tagElement.rectInMm.top;
									long lBottom = tagElement.rectInMm.bottom + lOffsetComplessivo;

									long lFooter = lPageHeight - lFooterHeight;

									while(lTop == lRigaCorrenteY)
									{
										if (lBottom > lFooter)
										{
											// dobbiamo inserire la pagina nuova //
											bInserisciPaginaNuova = TRUE;
											break;
										}

										nMySection++;

										// Sandro 25/08/2014 // se tutti i campi alla fine sono allineati si impallava... //
										if (nMySection > nTotSection)
											break;
										//

										strMySection.Format("Section%d", nMySection);

										lTop = GetPrivateProfileInt(strMySection, "Top", 0, pStruct->m_sReportFilePrinting) + (lRowHeight * i);
										lBottom = GetPrivateProfileInt(strMySection, "Bottom", 0, pStruct->m_sReportFilePrinting) + lOffsetComplessivo + (lRowHeight * i);
									}

									if (bInserisciPaginaNuova)
									{
										// cambio pagina //
										AmPdfCreator_AddPage();

										// ora che sono in una pagina nuova modifico l'offset per fare in modo che i controlli ripartano dal bordo superiore //
										lOffsetComplessivo = -(lRigaCorrenteY - lHeaderHeight);
									}
								}
							}

							tagElement.rectInMm.OffsetRect(0, lOffsetComplessivo);
						}

						// procedo con la stampa //
						switch(tagElement.lFieldType)
						{
							case TYPE_ICON:
							{
								// passo l'immagine alla libreria //
								HBITMAP hBitOld1;
								if (m_pImgManager->LoadLocalImageEx(tagElement.strFieldValue, &hBitOld1) > 0)
								{
									// Sandro 08/03/2012 // RIMA 11-064.5 //
									HBITMAP hBitNew = CImageElaboration(hBitOld1).ApplyBrightnessContrast(theApp.m_iIEBrightness, theApp.m_iIEContrastRMin, theApp.m_iIEContrastRMax, theApp.m_iIEContrastGMin, theApp.m_iIEContrastGMax, theApp.m_iIEContrastBMin, theApp.m_iIEContrastBMax);

									//
									Bitmap* pBitmap = Bitmap::FromHBITMAP(hBitNew, NULL);
									if (pBitmap->GetLastStatus() == Gdiplus::Ok)
									{
										if (theApp.m_bPDFImmaginiNonCompresse)
										{
											USES_CONVERSION;
											CLSID idClass;
											if (GetEncoderClsid(L"image/png", &idClass))
											{
												CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
												if (pBitmap->Save(T2W(strFileTemp), &idClass, NULL) == Gdiplus::Ok)
													AmPdfCreator_AddImageFromFilePng(tagElement.strFieldValue, strFileTemp);
											}
										}
										else
										{
											USES_CONVERSION;
											CLSID idClass;
											if (GetEncoderClsid(L"image/jpeg", &idClass))
											{
												EncoderParameters encoderParameters;
												encoderParameters.Count = 1;
												encoderParameters.Parameter[0].Guid = EncoderQuality;
												encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
												encoderParameters.Parameter[0].NumberOfValues = 1;
												ULONG quality = theApp.m_lPDFQualitaImmaginiCompresse; // Sandro 20/09/2013 // RAS 20130112 //
												encoderParameters.Parameter[0].Value = &quality;

												CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
												if (pBitmap->Save(T2W(strFileTemp), &idClass, &encoderParameters) == Gdiplus::Ok)
													AmPdfCreator_AddImageFromFileJpg(tagElement.strFieldValue, strFileTemp);
											}
										}
									}
									delete pBitmap;
									DeleteObject(hBitOld1);
									DeleteObject(hBitNew);
								}

								// stampo l'immagine //
								AmPdfCreator_PrintIcon(tagElement);

								//
								break;
							}
							case TYPE_LINE:
							{
								// stampo la linea //
								AmPdfCreator_PrintLine(tagElement);

								//
								break;
							}
							case TYPE_TEXT:
							{
								// stampo il testo //
								AmPdfCreator_PrintText(tagElement, NULL, NULL);

								//
								break;
							}
							case TYPE_LABEL:
							{
								// stampo l'etichetta, se il relativo campo è valido //

								TAG_ELEMENT tagTemp = tagElement;

								CList<TAG_ELEMENT> listElements;
								if (GetField(listElements, tagElement, TRUE))
								{
									tagElement = tagTemp;

									for(int i = 0; i < endox_report_field_num_total; i++)
									{
										if (CFieldDlg::m_strFieldEndox[i].sReport == tagElement.strFieldValue)
										{
											tagElement.strFieldValue = CFieldDlg::m_strFieldEndox[i].sCombo;
											tagElement.strFieldValue.Trim();

											if (!tagElement.strFieldValue.IsEmpty())
												AmPdfCreator_PrintText(tagElement, NULL, NULL);

											break;
										}
									}
								}

								//
								break;
							}
							case TYPE_FIELD:
							{
								// salvo il bottom del rect originale //
								long lOriginalBottom = tagElement.rectInMm.bottom;

								// carico il campo in una lista (alcuni campi possono venire spezzati in più testi diversi) //
								CList<TAG_ELEMENT> listElements;
								GetField(listElements, tagElement, FALSE);

								// stampo tutti gli elementi //
								long lLocalAddedPages = 0;
								long lLocalY = -1;
								long lLocalOffset1 = 0;
								long lLocalOffset2 = 0;
								long lFinalOffset = 0;

								POSITION pos = listElements.GetHeadPosition();
								while(pos != NULL)
								{
									TAG_ELEMENT tagElement = listElements.GetAt(pos);

									if (lLocalY != tagElement.rectInMm.top)
									{
										lLocalY = tagElement.rectInMm.top;
										lLocalOffset2 += lLocalOffset1;
										lLocalOffset1 = 0;
									}

									tagElement.rectInMm.OffsetRect(0, lLocalOffset2);

									long lFieldAddedPages = 0;
									long lFieldOffset = 0;
									if (tagElement.lFieldType == TYPE_RTF)
									{
										AmPdfCreator_PrintRTF(tagElement, &lFieldAddedPages, &lFieldOffset);
									}
									else
									{
										if (theApp.m_sBarCodeFontName.CompareNoCase(tagElement.lfFont.lfFaceName) == 0)
											tagElement.strFieldValue = "*" + tagElement.strFieldValue + "*";

										AmPdfCreator_PrintText(tagElement, &lFieldAddedPages, &lFieldOffset);
									}

									if (lFieldAddedPages > lLocalAddedPages)
									{
										lLocalAddedPages = lFieldAddedPages;

										lLocalOffset1 = lFieldOffset;

										lFinalOffset = tagElement.rectInMm.bottom + lFieldOffset - lOriginalBottom;
									}
									else if (lFieldAddedPages == lLocalAddedPages)
									{
										if (lFieldOffset > lLocalOffset1)
											lLocalOffset1 = lFieldOffset;

										if (tagElement.rectInMm.bottom + lFieldOffset > lOriginalBottom)
											lFinalOffset = tagElement.rectInMm.bottom + lFieldOffset - lOriginalBottom;
									}

									listElements.GetNext(pos);
								}
								listElements.RemoveAll();

								if (lLocalAddedPages > lRigaCorrentePagineAggiunte)
								{
									lRigaCorrentePagineAggiunte = lLocalAddedPages;
									lRigaCorrenteOffset = lFinalOffset;
								}
								else if (lLocalAddedPages == lRigaCorrentePagineAggiunte)
								{
									if (lFinalOffset > lRigaCorrenteOffset)
										lRigaCorrenteOffset = lFinalOffset;
								}

								//
								break;
							}
							case TYPE_PARAM:
							{
								// carico il parametro in una lista (alcuni parametri possono venire spezzati in più testi diversi) //
								CList<TAG_ELEMENT> listElements;
								GetParam(listElements, tagElement);

								// stampo tutti gli elementi //
								POSITION pos = listElements.GetHeadPosition();
								while(pos != NULL)
									AmPdfCreator_PrintText(listElements.GetNext(pos), NULL, NULL);
								listElements.RemoveAll();

								//
								break;
							}
							case TYPE_IMAGE:
							{
								if (pStruct->m_lImagePrinting < pStruct->m_lImageToPrint)
								{
									CObSelect* pSel = (CObSelect*)(CFileBmp::m_listPrinter.GetAt(pStruct->m_lImagePrinting));
									if (pSel != NULL)
									{
										tagElement.strFieldValue.Format("Immagine%02li", pStruct->m_lImagePrinting);

										// prendo il commento dell'immagine (solo se devo stamparlo) //
										if (tagElement.lMyCheck > 0)
										{
											POSITION pos = m_pFormImmagini->m_ImgListOrgani.GetHeadPosition();
											while(pos != NULL)
											{
												if (pSel->m_lID == m_pFormImmagini->m_ImgListOrgani.GetAt(pos).img.lID)
												{
													tagElement.strComment = m_pFormImmagini->m_ImgListOrgani.GetAt(pos).img.szDescription;
													break;
												}

												m_pFormImmagini->m_ImgListOrgani.GetNext(pos);
											}
										}

										// prendo il numero dell'immagine //
										POSITION pos = pStruct->m_listImmaginiStampa.FindIndex(pStruct->m_lImagePrinting);
										if (pos != NULL)
											tagElement.lMyParam = pStruct->m_listImmaginiStampa.GetAt(pos);
										else
											tagElement.lMyParam = -1;

										// passo l'immagine alla libreria //
										m_pImgManager->SetCurrentIDs(pSel->m_lPaziente, pSel->m_lEsame);
										HBITMAP hBitOld = m_pImgManager->GetImg(pSel->m_lID, FALSE, FALSE, FALSE);
										if (hBitOld != NULL)
										{
											// Sandro 08/03/2012 // RIMA 11-064.5 //
											HBITMAP hBitNew = CImageElaboration(hBitOld).ApplyBrightnessContrast(theApp.m_iIEBrightness, theApp.m_iIEContrastRMin, theApp.m_iIEContrastRMax, theApp.m_iIEContrastGMin, theApp.m_iIEContrastGMax, theApp.m_iIEContrastBMin, theApp.m_iIEContrastBMax);

											//
											Bitmap* pBitmap = Bitmap::FromHBITMAP(hBitNew, NULL);
											if (pBitmap->GetLastStatus() == Gdiplus::Ok)
											{
												if (theApp.m_bPDFImmaginiNonCompresse)
												{
													USES_CONVERSION;
													CLSID idClass;
													if (GetEncoderClsid(L"image/png", &idClass))
													{
														CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
														if (pBitmap->Save(T2W(strFileTemp), &idClass, NULL) == Gdiplus::Ok)
															AmPdfCreator_AddImageFromFilePng(tagElement.strFieldValue, strFileTemp);
													}
												}
												else
												{
													USES_CONVERSION;
													CLSID idClass;
													if (GetEncoderClsid(L"image/jpeg", &idClass))
													{
														EncoderParameters encoderParameters;
														encoderParameters.Count = 1;
														encoderParameters.Parameter[0].Guid = EncoderQuality;
														encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
														encoderParameters.Parameter[0].NumberOfValues = 1;
														ULONG quality = theApp.m_lPDFQualitaImmaginiCompresse; // Sandro 20/09/2013 // RAS 20130112 //
														encoderParameters.Parameter[0].Value = &quality;

														CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
														if (pBitmap->Save(T2W(strFileTemp), &idClass, &encoderParameters) == Gdiplus::Ok)
															AmPdfCreator_AddImageFromFileJpg(tagElement.strFieldValue, strFileTemp);
													}
												}
											}
											delete pBitmap;
											DeleteObject(hBitOld);
											DeleteObject(hBitNew);
										}

										// stampo l'immagine //
										AmPdfCreator_PrintImage(tagElement);
									
										// Sandro 29/05/2014 // salvo la lista di immagini da contrassegnare come stampate //
										m_listIDStampate.AddTail(pSel->m_lID);
									}

									pStruct->m_lImagePrinting++;
								}

								break;
							}
							case TYPE_ORGAN:
							{
								if (pStruct->m_lOrganPrinting < pStruct->m_lOrganToPrint)
								{
									long lOrganIndex = GetOrganIndex(pStruct->m_lOrganPrinting, pStruct->m_listPuntiStampa);

									if (lOrganIndex > 0)
									{
										// prendo il nome del file immagine dell'organo //

										CString strFilter;
										strFilter.Format("ID=%li", lOrganIndex);

										COrganiSet setOrgani;
										setOrgani.SetOpenFilter(strFilter);
										if (setOrgani.OpenRecordset("CEsamiView::PrintReportFromQuery"))
										{
											if (!setOrgani.IsEOF())
											{
												char szPathImm[MAX_PATH];
												char szPathMin[MAX_PATH];
												if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
												{
													tagElement.strFieldValue.Format("%s\\Organ\\%06li.org", szPathImm, setOrgani.m_lID);

													// passo l'immagine alla libreria //
													HBITMAP hBitOld1;
													if (m_pImgManager->LoadLocalImageEx(tagElement.strFieldValue, &hBitOld1) > 0)
													{
														// Sandro 08/03/2012 // RIMA 11-064.5 //
														HBITMAP hBitNew = CImageElaboration(hBitOld1).ApplyBrightnessContrast(theApp.m_iIEBrightness, theApp.m_iIEContrastRMin, theApp.m_iIEContrastRMax, theApp.m_iIEContrastGMin, theApp.m_iIEContrastGMax, theApp.m_iIEContrastBMin, theApp.m_iIEContrastBMax);

														//
														Bitmap* pBitmap = Bitmap::FromHBITMAP(hBitNew, NULL);
														if (pBitmap->GetLastStatus() == Gdiplus::Ok)
														{
															if (theApp.m_bPDFImmaginiNonCompresse)
															{
																USES_CONVERSION;
																CLSID idClass;
																if (GetEncoderClsid(L"image/png", &idClass))
																{
																	CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
																	if (pBitmap->Save(T2W(strFileTemp), &idClass, NULL) == Gdiplus::Ok)
																		AmPdfCreator_AddImageFromFilePng(tagElement.strFieldValue, strFileTemp);
																}
															}
															else
															{
																USES_CONVERSION;
																CLSID idClass;
																if (GetEncoderClsid(L"image/jpeg", &idClass))
																{
																	EncoderParameters encoderParameters;
																	encoderParameters.Count = 1;
																	encoderParameters.Parameter[0].Guid = EncoderQuality;
																	encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
																	encoderParameters.Parameter[0].NumberOfValues = 1;
																	ULONG quality = theApp.m_lPDFQualitaImmaginiCompresse; // Sandro 20/09/2013 // RAS 20130112 //
																	encoderParameters.Parameter[0].Value = &quality;

																	CString strFileTemp = GetLocalFileName(tagElement.strFieldValue);
																	if (pBitmap->Save(T2W(strFileTemp), &idClass, &encoderParameters) == Gdiplus::Ok)
																		AmPdfCreator_AddImageFromFileJpg(tagElement.strFieldValue, strFileTemp);
																}
															}
														}
														delete pBitmap;
														DeleteObject(hBitOld1);
														DeleteObject(hBitNew);
													}

													// stampo l'organo //
													AmPdfCreator_PrintOrgan(tagElement);
												}
												else
												{
													ASSERT(FALSE);
												}
											}

											setOrgani.CloseRecordset("CEsamiView::PrintReportFromQuery");
										}

										// stampo i punti //
										long lNumber = 0;
										POSITION pos = pStruct->m_listPuntiStampa.GetHeadPosition();
										while(pos != NULL)
										{
											tagPunti tagPunto = pStruct->m_listPuntiStampa.GetAt(pos);

											if (tagPunto.lIdOrgano == pStruct->m_lOrganPrinting + 1)
											{
												// imposto l'elemento //
												tagElement.rectInMm = CRect(tagPunto.lX, tagPunto.lY, tagPunto.lX, tagPunto.lY);
												tagElement.lMyParam = lNumber;

												// stampo il punto //
												tagElement.lMyCheck = 0;
												AmPdfCreator_PrintPointAndNumber(tagElement);

												//
												lNumber++;
											}

											pStruct->m_listPuntiStampa.GetNext(pos);
										}
									}

									pStruct->m_lOrganPrinting++;
								}

								break;
							}
							default:
							{
								ASSERT(FALSE);
								break;
							}
						}
					}
				}
			}

			m_PazTempSet.CloseRecordset("CEsamiView::PrintReportFromQuery");
		}
	}

	// distruggo la finestra modeless //
	EndWaitCursor();
	dlgWait.DestroyWindow();
}

ENUM_FIELD_TYPE CEsamiView::GetFieldType(CString strTipo)
{
	ENUM_FIELD_TYPE lReturn = TYPE_NONE;

	if (!strTipo.IsEmpty())
	{
		if (strTipo.CompareNoCase("Icon") == 0)
			lReturn = TYPE_ICON;
		else if (strTipo.CompareNoCase("Line") == 0)
			lReturn = TYPE_LINE;
		else if (strTipo.CompareNoCase("Text") == 0)
			lReturn = TYPE_TEXT;
		else if (strTipo.CompareNoCase("Label") == 0)
			lReturn = TYPE_LABEL;
		else if (strTipo.CompareNoCase("Field") == 0)
			lReturn = TYPE_FIELD;
		else if (strTipo.CompareNoCase("Rtf") == 0)
			lReturn = TYPE_RTF;
		else if (strTipo.CompareNoCase("Param") == 0)
			lReturn = TYPE_PARAM;
		else if (strTipo.CompareNoCase("Image") == 0)
			lReturn = TYPE_IMAGE;
		else if (strTipo.CompareNoCase("Organ") == 0)
			lReturn = TYPE_ORGAN;
		else if (strTipo.CompareNoCase("PageNum") == 0)
			lReturn = TYPE_CURPAGE;
		else if (strTipo.CompareNoCase("PageTot") == 0)
			lReturn = TYPE_TOTPAGES;
		else
			ASSERT(FALSE);
	}

	return lReturn;
}

long CEsamiView::ArchiviaPdf(pdftype pdfType, CString* pStrPdfFileComplete, CString sNote, BOOL bFirma, BOOL bSaltaFirma, BOOL bFitToPage, long lVersioneReferto, long lIDPdfCheSostituisce)
{
	long lReturn = 0;
	long lContatoreEsame = m_pEsamiSet->m_lContatore;
	long lContatorePaziente = m_pEsamiSet->m_lPaziente;
	
	CPDFCreator pdfCreator(this, m_pEsamiSet, pdfType);

	//Gabriel - TCP
	/*if (theApp.m_bAtivaTCP && !m_pEsamiSet->m_sCodesameCorrelati.IsEmpty())
	{
		CString sFilterConiugato;
		sFilterConiugato.Format("CODESAME='%s'", m_pEsamiSet->m_sCodesameCorrelati);

		CEsamiSet setEsameConiugato;
		setEsameConiugato.SetBaseFilter("(UO=0 OR UO>0)");
		setEsameConiugato.SetOpenFilter(sFilterConiugato);

		if (setEsameConiugato.OpenRecordset("CEsamiView::ArchiviaPdf"))
		{
			if (!setEsameConiugato.IsEOF())
			{
				lContatoreEsame = setEsameConiugato.m_lPaziente;
				lContatorePaziente =setEsameConiugato.m_lContatore;
			}

			setEsameConiugato.CloseRecordset("CEsamiView::ArchiviaPdf");
		}
	}*/

	if (!bFirma || bSaltaFirma)
		lReturn = pdfCreator.SavePdfFileIntoRepository(sNote, lVersioneReferto, lIDPdfCheSostituisce, bFitToPage, *pStrPdfFileComplete);
	else
		lReturn = pdfCreator.SaveSignedPdfFileIntoRepository(sNote, lVersioneReferto, lIDPdfCheSostituisce, bFitToPage, pStrPdfFileComplete);

	//Gabriel - TCP
	if (bSaltaFirma && (lReturn > 0))
		CPdfManager().SetPdfFirmato(lReturn, lContatorePaziente, lContatoreEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer);

	// eventualmente lo pubblico //
	if (theApp.m_bPubblicazioneAuto)
	{
		CImgManager imTemp(theApp.m_sPathImageOD, &theApp.m_dbEndox);
		imTemp.SetCurrentIDs(lContatorePaziente, lContatoreEsame);

		CImgList listImg;

		DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
		int nImages = imTemp.GetImgList(&listImg);
		if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
			CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, lContatorePaziente, lContatoreEsame, nImages, "CEsamiView::ArchiviaPdf");

		CString sInterfacciaWebPlacer = "";
		if ((m_pEsamiSet != NULL) && (m_pEsamiSet->IsOpen()) && (!m_pEsamiSet->IsBOF()) && (!m_pEsamiSet->IsEOF()))
		{
			if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lProvenienza) && !m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lInviante))
			{
				switch (m_pEsamiSet->m_lProvenienza)
				{
					case INTERNO:
					{
						sInterfacciaWebPlacer.Format("I%li", m_pEsamiSet->m_lInviante);
						break;
					}
					case ESTERNO:
					{
						sInterfacciaWebPlacer.Format("E%li", m_pEsamiSet->m_lInviante);
						break;
					}
				}
			}
		}

		CWebDeployer webCreator(&theApp.m_dbEndox);
		webCreator.DeployReferto(&theApp.m_sPercorsoTemporaneoWEB, &theApp.m_sInterfacciaWebTo, &theApp.m_sInterfacciaWebFrom, m_pPazientiSet, m_pEsamiSet, &listImg, pStrPdfFileComplete);

		POSITION pos = listImg.GetHeadPosition();
		while (pos != NULL)
		{
			DeleteObject(listImg.GetAt(pos).hBmp);
			DeleteObject(listImg.GetAt(pos).hBmpSelected);
			listImg.GetNext(pos);
		}
		listImg.RemoveAll();
	}

	return lReturn;
}

//Gabriel BUG 6303
BOOL CEsamiView::GetPdfImagePageOrientation()
{
	CList<CString> sSiglasList;
	CString str = _T(theApp.m_sStampaImmaginiSiglePerStampaOrizzontale);

	int nTokenPos = 0;
	CString strToken = str.Tokenize(_T(";"), nTokenPos);

	while (!strToken.IsEmpty())
	{
		sSiglasList.AddTail(strToken);
		strToken = str.Tokenize(_T(";"), nTokenPos);
	}

	CString sSiglaEsame;

	for (int i = 0; i < sSiglasList.GetCount(); i++)
	{
		if (sSiglasList.GetAt(sSiglasList.FindIndex(i)) == GetSiglaPrestazione())
		{
			return TRUE;
			break;
		}
	}

	return FALSE;
}

//Gabriel - TCP
long CEsamiView::OnChiudiEsameCorrelati(long lIdEsame)
{
	long lIDPdf = 0;
	long lIDPdfImmagini = 0;
	CString sIDPdf = "";
	CString sIDPdfImmagini = "";

	//Gabriel - TCP
	if (theApp.m_bAtivaTCP && !m_pEsamiSet->m_sCodesameCorrelati.IsEmpty())
	{
		CString sFilterCorrelato;
		sFilterCorrelato.Format("CODESAME='%s'", m_pEsamiSet->m_sCodesameCorrelati);

		CEsamiSet setEsameCorrelato;
		setEsameCorrelato.SetBaseFilter("(UO=0 OR UO>0)");
		setEsameCorrelato.SetOpenFilter(sFilterCorrelato);

		if (setEsameCorrelato.OpenRecordset("CEsamiView::ChiudiEsame"))
		{
			if (!setEsameCorrelato.IsEOF())
			{
				CString sQueryPdf;
				sQueryPdf.Format("SELECT ID FROM PDF WHERE TIPO = 0 AND ELIMINATO = 0 AND IDESAME=%li", setEsameCorrelato.m_lContatore);

				try
				{
					CRecordset getIdPdf(&theApp.m_dbEndox);

					getIdPdf.Open(CRecordset::snapshot, sQueryPdf, CRecordset::readOnly);
					getIdPdf.GetFieldValue("ID", sIDPdf);
					getIdPdf.Close();
				}
				catch (CDBException* pEx)
				{
					pEx->Delete();
				}

				CString sQueryPdfImmagini;
				sQueryPdfImmagini.Format("SELECT ID FROM PDF WHERE TIPO = 1 AND ELIMINATO = 0 AND IDESAME=%li", setEsameCorrelato.m_lContatore);

				try
				{
					CRecordset getIdPdfImmagini(&theApp.m_dbEndox);

					getIdPdfImmagini.Open(CRecordset::snapshot, sQueryPdfImmagini, CRecordset::readOnly);
					getIdPdfImmagini.GetFieldValue("ID", sIDPdfImmagini);
					getIdPdfImmagini.Close();
				}
				catch (CDBException* pEx)
				{
					pEx->Delete();
				}

				lIDPdf = sIDPdf != "" ? atol(sIDPdf) : 0;
				lIDPdfImmagini = sIDPdfImmagini != "" ? atol(sIDPdfImmagini) : 0;
				
				// inserisco una riga nella tabella EXT_ESAMI_CHIUSI //
				CEsamiChiusiSet().InserisciRecord(setEsameCorrelato.m_lContatore, lIDPdf, lIDPdfImmagini, setEsameCorrelato.m_lIdUtenteSuperLock, "NW");
				CEsamiChiusiSet().InserisciRecord(m_pEsamiSet->m_lContatore, -1, -1, GetUserIDForLockSuperlock(), "NW");

				// chiudo l'esame //
				CEsamiSet().ChiudiEsameIntegrato(m_pEsamiSet->m_lContatore, m_sDataOraChiusura);
			}

			setEsameCorrelato.CloseRecordset("CEsamiView::ChiudiEsame");
		}
	}
	
	return CEsamiChiusiSet().GetIdFromPdfId(lIDPdf);
}

//Gabriel - TCP
long CEsamiView::OnGeneraRefertoEsamePrincipale(){
	CString strReportFile = "";
	long lCopie = 0;

	// controllo se esistono dei reports di default associati all'esame //
	CString strFilter;
	strFilter.Format("SedeEsame='%s' AND TipoEsame=%li AND Report<>'IMMAGINI'", CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE), m_pEsamiSet->m_lIDEsame);

	CReportsDefaultSet setRepDef;
	setRepDef.SetOpenFilter(strFilter);
	setRepDef.SetSortRecord("ID");
	if (setRepDef.OpenRecordset("CEsamiView::OnGeneraRefertoEsamePrincipale"))
	{
		if (!setRepDef.IsEOF())
		{
			strReportFile = setRepDef.m_sReport;
			lCopie = setRepDef.m_lCopie;
		}

		setRepDef.CloseRecordset("CEsamiView::OnGeneraRefertoEsamePrincipale");
	}

	long lGeneratedPdfId = 0;
	AnteprimaStampaReport(CHIUSURA_ESAMECORRELATI, VERIFICA_SI, strReportFile, FALSE, lCopie, &lGeneratedPdfId,"");

	return lGeneratedPdfId;
}