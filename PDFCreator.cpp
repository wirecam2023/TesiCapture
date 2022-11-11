#include "stdafx.h"
#include "Endox.h"
#include "PDFCreator.h"

#include <io.h>

#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\AMTesiSign.h"

#include "DigitalSignUtil.h"
#include "FirmaConfidenzialitaTrevisoDlg.h"
#include "MediciSet.h"
#include "PDFManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPDFCreator::CPDFCreator(CWnd* pParentWnd, CEsamiSet* pEsamiSet, pdftype pdfType)
{
	m_pParentWnd = pParentWnd;
	m_pEsamiSet = pEsamiSet;
	m_pdfType = pdfType;
}

CPDFCreator::~CPDFCreator(void)
{
}

// Sandro // 05/01/2011 // Archivio un PDF partendo da un file invece che da un buffer //
long CPDFCreator::SavePdfFileIntoRepository(const CString sNote, const long lVersioneReferto, const long lIDPdfCheSostituisce, const BOOL bFitToPage, const CString sFileComplete)
{
	CPdfManager PdfManager;
	long lReturn = -2000;
	if (PdfManager.IsInitialize())
	{
		
		//Gabriel - TCP
		/*if (theApp.m_bAtivaTCP && !m_pEsamiSet->m_sCodesameCorrelati.IsEmpty())
		{
			CString sFilterConiugato;
			sFilterConiugato.Format("CODESAME='%s'", m_pEsamiSet->m_sCodesameCorrelati);

			CEsamiSet setEsameConiugato;
			setEsameConiugato.SetBaseFilter("(UO=0 OR UO>0)");
			setEsameConiugato.SetOpenFilter(sFilterConiugato);

			if (setEsameConiugato.OpenRecordset("CEsamiView::ChiudiEsame"))
			{
				if (!setEsameConiugato.IsEOF())
				{
					lReturn = PdfManager.ImportPdf(setEsameConiugato.m_lPaziente, setEsameConiugato.m_lContatore, m_pdfType, sNote, lVersioneReferto, lIDPdfCheSostituisce, bFitToPage, "", sFileComplete); // lascio vuota la classificazione //
				}

				setEsameConiugato.CloseRecordset("CEsamiView::ChiudiEsame");
			}
		}
		else*/
			lReturn = PdfManager.ImportPdf(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, m_pdfType, sNote, lVersioneReferto, lIDPdfCheSostituisce, bFitToPage, "", sFileComplete); // lascio vuota la classificazione //
		// non togliere le note, serve per visualizzare nelle liste il nome del report da cui è stato generato il PDF //
		
	}
	else
	{
		lReturn = -2001;
	}

	if (lReturn <= 0)
	{
		CString strError;
		strError.Format("%s (%li)", theApp.GetMessageString(IDS_ERR_SAVING_PDF), lReturn);
		theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
	}

	return lReturn;
}

// Sandro // 05/01/2011 // Archivio un PDF partendo da un file invece che da un buffer //
long CPDFCreator::SaveSignedPdfFileIntoRepository(const CString sNote, const long lVersioneReferto, const long lIDPdfCheSostituisce, const BOOL bFitToPage, CString* pStrFileComplete)
{
	CPdfManager PdfManager;
	long lReturn = -2000;
	if (PdfManager.IsInitialize())
	{
		switch(theApp.m_enumFirmaDigitale)
		{
			case CEndoxApp::sign_comped:
			{
				// Sandro 27/02/2013 // controllo che il codice fiscale estratto dalla smartcard sia presente nella tabella EMedici //

				long lConteggioMedici = 0;

				AmTesiSign_SMARTCARDDATA scData;
				AmTesiSign_GetSmartCardData(&scData);

				CString sCodiceFiscaleSmartCard = scData.szUserFiscalCode;
				sCodiceFiscaleSmartCard.MakeUpper();
				sCodiceFiscaleSmartCard.Trim();

				CString sFilter;
				sFilter.Format("CodiceFiscale='%s'", sCodiceFiscaleSmartCard);

				CMediciSet setMedici;
				setMedici.SetOpenFilter(sFilter);
				if (setMedici.OpenRecordset("CPDFCreator::SaveSignedPdfFileIntoRepository"))
				{
					while(!setMedici.IsEOF())
					{
						lConteggioMedici++;
						setMedici.MoveNext();
					}

					setMedici.CloseRecordset("CPDFCreator::SaveSignedPdfFileIntoRepository");
				}

				if (lConteggioMedici < 1)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_09), MB_ICONSTOP);
					DeleteFile(*pStrFileComplete);
					return FALSE;
				}

				if (lConteggioMedici > 1)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_10), MB_ICONSTOP);
					DeleteFile(*pStrFileComplete);
					return FALSE;
				}

				// Sandro 29/10/2014 // RAS 20140089 //
				if (theApp.m_bFirmaDigitaleSmartcardUgualeMedico1)
				{
					// controllo se il codice fiscale della smartcard corrisponde a quello del medico che ha fatto l'esame //

					BOOL bOK = FALSE;

					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lMedico) && (m_pEsamiSet->m_lMedico > 0))
					{
						CString sCodiceFiscaleMedico = CMediciSet().GetCodiceFiscaleFromContatore(m_pEsamiSet->m_lMedico);
						sCodiceFiscaleMedico.Trim();

						if (sCodiceFiscaleMedico.GetLength() > 0)
							if (sCodiceFiscaleSmartCard.CompareNoCase(sCodiceFiscaleMedico) == 0)
								bOK = TRUE;
					}

					if (!bOK)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_11), MB_ICONSTOP);
						DeleteFile(*pStrFileComplete);
						return FALSE;
					}
				}

				// Sandro 29/10/2014 // RAS 20140089 //
				if (theApp.m_bFirmaDigitaleSmartcardUgualeUtenteEndox)
				{
					// controllo se il codice fiscale della smartcard corrisponde a quello dell'utente attualmente loggato in Endox //

					BOOL bOK = FALSE;

					long lUserID;
					AMLogin_GetUserID(&lUserID);

					CString sCodiceFiscaleUtente = CMediciSet().GetCodiceFiscaleFromUserID(lUserID);
					sCodiceFiscaleUtente.Trim();

					if (sCodiceFiscaleUtente.GetLength() > 0)
						if (sCodiceFiscaleSmartCard.CompareNoCase(sCodiceFiscaleUtente) == 0)
							bOK = TRUE;

					if (!bOK)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_12), MB_ICONSTOP);
						DeleteFile(*pStrFileComplete);
						return FALSE;
					}
				}

				// RIMA 12149.1 // Treviso: grado di confidenzialità //
				CString sClassificazione = "";

				// aggiungo firma digitale al PDF... //
				if (AmTesiSign_SignFile(*pStrFileComplete, theApp.m_sSmartCardPin) != NoError)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_3), MB_ICONSTOP);
					DeleteFile(*pStrFileComplete);
					return FALSE;
				}

				// cancello PDF non firmato... //
				DeleteFile(*pStrFileComplete);

				if (_access((*pStrFileComplete) + ".p7m", 00) != 0)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_4), MB_ICONSTOP);
					AmTesiSign_Finalize();
					return FALSE;
				}

				// importo su archivio... //
				CString sSmartCardUtente = "";
				CDigitalSignUtil::GetSmartCardUtente(&sSmartCardUtente);

				CString sSmartCardNumero = "";
				CDigitalSignUtil::GetSmartCardNumero(&sSmartCardNumero);

				CString sSmartCardEnteCertificato = "";
				CDigitalSignUtil::GetSmartCardEnteCertificato(&sSmartCardEnteCertificato);

				//Gabriel - TCP
				/*if (theApp.m_bAtivaTCP && !m_pEsamiSet->m_sCodesameCorrelati.IsEmpty())
				{
					CString sFilterConiugato;
					sFilterConiugato.Format("CODESAME='%s'", m_pEsamiSet->m_sCodesameCorrelati);

					CEsamiSet setEsameConiugato;
					setEsameConiugato.SetBaseFilter("(UO=0 OR UO>0)");
					setEsameConiugato.SetOpenFilter(sFilterConiugato);

					if (setEsameConiugato.OpenRecordset("CEsamiView::ChiudiEsame"))
					{
						if (!setEsameConiugato.IsEOF())
						{
							if (PdfManager.ImportSignedPdf(setEsameConiugato.m_lPaziente, setEsameConiugato.m_lContatore, m_pdfType, sNote, sSmartCardUtente, sSmartCardNumero, sSmartCardEnteCertificato, lVersioneReferto, lIDPdfCheSostituisce, bFitToPage, sClassificazione, CString((*pStrFileComplete) + ".p7m"), &lReturn))
								(*pStrFileComplete) += ".p7m";
						}

						setEsameConiugato.CloseRecordset("CEsamiView::ChiudiEsame");
					}
				}
				else
				{*/
					// non togliere le note, serve per visualizzare nelle liste il nome del report da cui è stato generato il PDF //
				if (PdfManager.ImportSignedPdf(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, m_pdfType, sNote, sSmartCardUtente, sSmartCardNumero, sSmartCardEnteCertificato, lVersioneReferto, lIDPdfCheSostituisce, bFitToPage, sClassificazione, CString((*pStrFileComplete) + ".p7m"), &lReturn))
					(*pStrFileComplete) += ".p7m";
				//}
				

				// cancello PDF firmato.. //
				// DeleteFile(strFile + ".p7m");

				break;
			}
		}
	}

	if (lReturn <= 0)
	{
		CString strError;
		strError.Format("%s (%li)", theApp.GetMessageString(IDS_ERR_SAVING_PDF), lReturn);
		theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
	}

	return lReturn;
}

BOOL CPDFCreator::SavePDFSignedIntoRepository(const CString sNote, const CString sSmartCardUtente, const CString sSmartCardNumero, const CString sSmartCardEnteCertificato, const long lVersioneReferto, const long lIDPdfCheSostituisce, const BOOL bFitToPage, const CString sClassificazione, const CString sFileComplete, long* pPdfID)
{
	CPdfManager PdfManager;
	BOOL bReturn = FALSE;
	if (PdfManager.IsInitialize())
	{
		//Gabriel - TCP
		/*if (theApp.m_bAtivaTCP && !m_pEsamiSet->m_sCodesameCorrelati.IsEmpty())
		{
			CString sFilterConiugato;
			sFilterConiugato.Format("CODESAME='%s'", m_pEsamiSet->m_sCodesameCorrelati);

			CEsamiSet setEsameConiugato;
			setEsameConiugato.SetBaseFilter("(UO=0 OR UO>0)");
			setEsameConiugato.SetOpenFilter(sFilterConiugato);

			if (setEsameConiugato.OpenRecordset("CEsamiView::ChiudiEsame"))
			{
				if (!setEsameConiugato.IsEOF())
				{
					bReturn = PdfManager.ImportSignedPdf(setEsameConiugato.m_lPaziente, setEsameConiugato.m_lContatore, m_pdfType, sNote, sSmartCardUtente, sSmartCardNumero, sSmartCardEnteCertificato, lVersioneReferto, lIDPdfCheSostituisce, bFitToPage, sClassificazione, sFileComplete, pPdfID);
				}

				setEsameConiugato.CloseRecordset("CEsamiView::ChiudiEsame");
			}
		}
		else
		{*/
		bReturn = PdfManager.ImportSignedPdf(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, m_pdfType, sNote, sSmartCardUtente, sSmartCardNumero, sSmartCardEnteCertificato, lVersioneReferto, lIDPdfCheSostituisce, bFitToPage, sClassificazione, sFileComplete, pPdfID);
			// non togliere le note, serve per visualizzare nelle liste il nome del report da cui è stato generato il PDF //
		//}
	}

	if (!bReturn)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERR_SAVING_PDF), MB_ICONSTOP);
		*pPdfID = 0;
	}

	return bReturn;
}
