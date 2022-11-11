#include "stdafx.h"
#include "Endox.h"
#include "CupWorkListManager.h"

#include "DLL_Imaging\h\AMLogin.h"

#include "ConfigurazioniListaPrenotazioniSet.h"
#include "CustomDate.h"
#include "DiagnosiEsamiSet.h"
#include "DiagnosiICD9Set.h"
#include "DocManager.h"
#include "EsamiAccettatiSet.h"
#include "EsamiCaricoAnnullatoSet.h"
#include "EsamiChiusiSet.h"
#include "EsamiNoShowSet.h"
#include "EsamiSet.h"
#include "ExamListDlg.h"
#include "ExtMinPazDataSetSet.h"
#include "ExtOrdiniAllegatiSet.h"
#include "ExtOrdiniDiagnosiICD9Set.h"
#include "ExtOrdiniOperatoriSet.h"
#include "ExtOrdiniProcedureICD9Set.h"
#include "ExtOrdiniSet.h"
#include "ExtPatientEventSet.h"
#include "ExtTransUrgenzaSet.h"
#include "ListaPrenotazioniCupDlg.h"
#include "ListaPrestazioniCupSet.h"
#include "ListSortableCtrl.h"
#include "MediciSet.h"
#include "PazientiSet.h"
#include "PrenotazioneAccettataSP.h"
#include "ProcedureEsamiSet.h"
#include "ProcedureICD9Set.h"
#include "ProvenienzaSet.h"
#include "QueryDlg.h"
#include "RegioneSet.h"
#include "SediEsameSet.h"
#include "TipoEsameNew.h"
#include "VistaEsamiPerWLSet.h"
#include "VistaExtPrestazioniSet.h"
#include "LogFileWriter.h"
#include "DbLocker.h"
#include <MMSystem.h>
#include "EsamiIntegratiSet.h" //Gabriel - TCP FIX

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCupWorkListManager, CBaseSet)

CCupWorkListManager::CCupWorkListManager(CEsamiView* pEsamiView)
	: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");

	SetSortRecord("DATAESAME, COGNOME, NOME");

	m_pEsamiView = pEsamiView;

	m_ImageList.Create(16, 16, ILC_COLOR16, 2, 2);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_LISTA_PREN_NO));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_LISTA_PREN_NI));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_LISTA_PREN_SI));

	// m_bImporting = FALSE;
	m_bTrasferito = FALSE;

	//Gabriel - TCP
	m_bColumnsP3 = CheckColumnExists("VISTA_EXT_ORDINI", "CODICEMEDICOINVIANTE2") && CheckColumnExists("VISTA_EXT_ORDINI", "CODICEMEDICOINVIANTE3") && CheckColumnExists("VISTA_EXT_ORDINI", "CODICEMEDICOINVIANTE4");
	m_bColumnsTCP = CheckColumnExists("VISTA_EXT_ORDINI", "ORDERNUMBERCORRELATI") && CheckColumnExists("VISTA_EXT_ORDINI", "STATOTCP");
	m_nFields = 88 - (m_bColumnsP3 ? 0 : 9) - (m_bColumnsTCP ? 0 : 2); //Julio - BUG 3285 - Adequação de laudos

	m_bTipoEsameDlg = FALSE;
}

CCupWorkListManager::~CCupWorkListManager()
{
}

CString CCupWorkListManager::GetDefaultSQL()
{
	return "VISTA_EXT_ORDINI";
}

void CCupWorkListManager::PrepareList(CListSortableCtrl* pList)
{
	m_iColumn=0;
	pList->InsertColumn(m_iColumn, "", CListSortableCtrl::type_string, LVCFMT_CENTER, 20);
	m_iColumn++;

	pList->SetExtendedStyle(pList->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pList->SetImageList(&m_ImageList, LVSIL_SMALL);

	for(POSITION pos=theApp.m_worklistFields.GetHeadPosition();pos;)
	{
		worklistField tempField = theApp.m_worklistFields.GetNext(pos);
		pList->InsertColumn(m_iColumn, tempField.sTitolo, CListSortableCtrl::type_string, LVCFMT_LEFT, 100);

		m_iColumn++;
	}
}

BOOL CCupWorkListManager::FillList(CListSortableCtrl* pList, CString sAddFilter, CString sDataFilter)
{
	theApp.BeginWaitCursor();
	pList->SetRedraw(FALSE);

	sDataFilter.Trim();
	if (!sDataFilter.IsEmpty())
		sDataFilter += " AND ";

	pList->DeleteAllItems();

	CString fields;
	for (POSITION pos = theApp.m_worklistFields.GetHeadPosition(); pos;)
	{
		worklistField tempField = theApp.m_worklistFields.GetNext(pos);

		if (tempField.sNomeColonna == "")
			continue;

		if (fields.Compare("") == 0)
			fields = tempField.sNomeColonna;
		else
			fields += "," + tempField.sNomeColonna;
	}

	if (fields.Compare("") == 0)
	{
		pList->SetRedraw(TRUE);
		theApp.EndWaitCursor();
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_WL_COLSNOTDEFINED));
		return FALSE;
	}

	CString query;
	//query.Format("SELECT EndoxOrderId as ID_F, ExamDate AS DATAESAME_F, ExamType as ESAME_F, PatientId AS ASSIDEN_F, %s FROM VISTA_EXT_ORDINI_LAYOUT INNER JOIN PROVENIENZA ON origin = codiceProvenienzaEst and PROVENIENZA.eliminato=0 INNER JOIN SaleEsame ON locationCode = codiceIntegrazione and operatingUnitId = SaleEsame.uo and saleesame.eliminato=0 WHERE %s OperatingUnitId=%li and deletedOrder=0 %s order by DATAESAME_F", fields, sDataFilter, theApp.m_lUO, sAddFilter);
	query.Format("SELECT ORDERPHASE as ORDINEFASE_F, EndoxOrderId as ID_F, ExamDate AS DATAESAME_F, ExamType as ESAME_F, PatientId AS ASSIDEN_F, %s FROM VISTA_EXT_ORDINI_LAYOUT INNER JOIN PROVENIENZA ON origin = codiceProvenienzaEst and PROVENIENZA.eliminato=0 INNER JOIN AGENDE ON locationCode = codiceIntegrazione and AGENDE.eliminato=0 JOIN SALEESAME ON AGENDE.IDSALA = SALEESAME.ID AND SALEESAME.UO=%li AND SALEESAME.ELIMINATO=0 WHERE %s OperatingUnitId=%li and deletedOrder=0 %s order by DATAESAME_F", fields, theApp.m_lUO, sDataFilter, theApp.m_lUO, sAddFilter);

#ifdef _DEBUG
	theApp.AfxMessageBoxEndo("CCupWorkListManager::FillList\n\n" + query);
#endif 

	CRecordset richiesteSet(&theApp.m_dbEndox);

	try
	{
		richiesteSet.Open(CRecordset::snapshot, query, CRecordset::readOnly);

		while (!richiesteSet.IsEOF())
		{
			int iItemInserted = -1;
			CString strAvvisi = "";

			CString strOrderPhase;
			richiesteSet.GetFieldValue("ORDINEFASE_F", strOrderPhase);

			CString strId;
			richiesteSet.GetFieldValue("ID_F", strId);
			long lId = atoi(strId);

			CString tipoEsame;
			richiesteSet.GetFieldValue("ESAME_F", tipoEsame);

			//Se all'ordine non corrisponde nessun esame: pallino rosso e message box se si vuole selezionare a mano il tipo esame
			//Se non tutti i dati sono stati transcodificati: pallino giallo
			//Altrimenti presenta un pallino verde
			CString strAssiden;
			richiesteSet.GetFieldValue("ASSIDEN_F", strAssiden);
			if (tipoEsame == "" || (theApp.m_bAssidenKey && strAssiden == "") || (!theApp.m_bAssidenKey && !CampiObbligatoriValorizzati(lId)))
			{
				// Sandro & Simone // 03/07/2015 // le accettazioni "dirette" le mostro sempre col pallino verde //
				// Simone - 02/02/2016 Commento perché non funziona al primo riempimento, funziona solo dopo il tentativo di importazione di un record
				/*if (m_sOrderNumber.Find("ENDOX") >= 0)
				{
				iItemInserted = pList->InsertItem(pList->GetItemCount(), "", 2);
				pList->SetItemData(iItemInserted, lId);
				}
				else
				{*/
				iItemInserted = pList->InsertItem(pList->GetItemCount(), GetStatoRichiestaString(strOrderPhase), 0);
				pList->SetItemData(iItemInserted, -1 * lId);
				//}
			}
			else
			{
				iItemInserted = pList->InsertItem(pList->GetItemCount(), GetStatoRichiestaString(strOrderPhase), 2);
				pList->SetItemData(iItemInserted, lId);
			}

			int subItem = 1;
			for (POSITION pos = theApp.m_worklistFields.GetHeadPosition(); pos;)
			{
				worklistField tempField = theApp.m_worklistFields.GetNext(pos);

				CString strTemp;
				richiesteSet.GetFieldValue(tempField.sNomeColonna, strTemp);

				pList->SetItemText(iItemInserted, subItem, strTemp);

				subItem++;
			}

			richiesteSet.MoveNext();
		}

		richiesteSet.Close();
	}
	catch (CDBException* pEx)
	{
		pList->SetRedraw(TRUE);
		theApp.EndWaitCursor();
		theApp.AfxMessageBoxEndo(pEx->m_strError);
		pEx->Delete();
		return FALSE;
	}

	for (int h = 0; h<m_iColumn; h++)
		pList->SetColumnWidth(h, LVSCW_AUTOSIZE_USEHEADER);

	pList->SetRedraw(TRUE);
	theApp.EndWaitCursor();
	return TRUE;
}

void CCupWorkListManager::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Id", m_lId);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "orderNumber",		    m_sOrderNumber,				50);
		RFX_Text(pFX, "DataEsame",				m_sDataEsame,				14);
		RFX_Text(pFX, "Provenienza",			m_sProvenienza,				50);
		RFX_Text(pFX, "CodiceAgenda",			m_sCodiceAgenda,			50);
		RFX_Text(pFX, "Note",					m_sNote,					3999);
		RFX_Text(pFX, "CodiceRepartoInviante",	m_sCodiceRepartoInviante,	50);
		RFX_Text(pFX, "RepartoInviante",		m_sRepartoInviante,			255);
		RFX_Text(pFX, "CodiceMedicoInviante",	m_sCodiceMedicoInviante,	50);
		RFX_Text(pFX, "DescrizioneMedicoInvianteEst",		m_sDescrizioneMedicoInvianteEst,		255);
		RFX_Text(pFX, "Nosologico",				m_sNosologico,				50);
		RFX_Text(pFX, "Urgenza",				m_sUrgenza,					50);
		RFX_Long(pFX, "IDEsameIns",				m_lIDEsameIns);
		RFX_Bool(pFX, "Trasferito",				m_bTrasferito);
		RFX_Text(pFX, "idProvetta",				m_sIdProvetta,				50);
		RFX_Bool(pFX, "AcqSegnalata",			m_bAcqSegnalata);
		RFX_Bool(pFX, "ErogazioneSegnalata",	m_bErogazioneSegnalata);
		RFX_Bool(pFX, "AppuntamentoSegnalato",	m_bAppuntamentoSegnalato);
		RFX_Bool(pFX, "Eliminato",				m_bEliminato);
		RFX_Text(pFX, "Assiden",				m_sAssiden,					50);
		RFX_Text(pFX, "Cognome",				m_sCognome,					255); // 50
		RFX_Text(pFX, "Cognome2",				m_sCognome2,				255); // 50
		RFX_Text(pFX, "Nome",					m_sNome,					255); // 50
		RFX_Text(pFX, "DataNascita",			m_sDataNascita,				14);
		RFX_Long(pFX, "DataNascitaCustom",		m_lDataNascitaCustom);
		RFX_Long(pFX, "ISTATNascita",			m_lISTATNascita);
		RFX_Text(pFX, "DescrizioneComuneNascitaEst",		m_sDescrizioneComuneNascitaEst,			255);
		RFX_Text(pFX, "IndirizzoResidenza",		m_sIndirizzoResidenza,		255);
		RFX_Long(pFX, "ISTATResidenza",			m_lISTATResidenza);
		RFX_Text(pFX, "DescrizioneComuneResidenzaEst",		m_sDescrizioneComuneResidenzaEst,		255); // arriva da EXT_ORDINI.COMUNERESIDENZA ma era già 255, quindi siamo già a posto con questo //
		RFX_Text(pFX, "CAPResidenza",			m_sCapResidenza,			5);
		RFX_Text(pFX, "Telefono1",				m_sTelefono1,				50);
		RFX_Text(pFX, "Telefono2",				m_sTelefono2,				50);
		RFX_Text(pFX, "Cellulare1",				m_sCellulare1,				50);
		RFX_Text(pFX, "Cellulare2",				m_sCellulare2,				50);
		RFX_Text(pFX, "CodiceFiscale",			m_sCodiceFiscale,			16); //
		RFX_Text(pFX, "CodiceSanitario",		m_sCodiceSanitario,			50); //
		RFX_Long(pFX, "Sesso",					m_lSesso);
		RFX_Text(pFX, "UlssResidenza",			m_sUlssResidenza,			10);
		RFX_Text(pFX, "CodiceMedicoCurante",	m_sCodiceMedicoCurante,		50);
		RFX_Text(pFX, "DescrizioneMedicoCuranteEst",		m_sDescrizioneMedicoCuranteEst,			255); // arriva da EXT_ORDINI.MEDICOCURANTE ma era già 255, quindi siamo già a posto con questo //
		//RFX_Text(pFX, "CodiceCittadinanza",		m_sCodiceCittadinanza,		50);
		RFX_Text(pFX, "Cittadinanza",		m_sDescrizioneCittadinanzaEst,			255);
		RFX_Text(pFX, "DataRichiesta",			m_sDataRichiesta,			50);
		RFX_Text(pFX, "ProvinciaEst",			m_sProvinciaEst,			50);
		RFX_Long(pFX, "StatoAccettazione",		m_lStatoAccettazione);
		RFX_Text(pFX, "UOEst",					m_sUOEst,						50);
		RFX_Text(pFX, "IdEpisodioRicovero",		m_sIdEpisodioRicovero,					50);
		RFX_Text(pFX, "DataRicovero",			m_sDataRicovero,						50);
		RFX_Bool(pFX, "CertificazioneMEF",		m_bCertificazioneMEF);
		RFX_Bool(pFX, "CertificazioneSISS",		m_bCertificazioneSISS);
		RFX_Bool(pFX, "OscuramentoVolontario",	m_bOscuramentoVolontario);
		RFX_Text(pFX, "CodiceSTP",				m_sCodiceSTP, 50);
		RFX_Text(pFX, "CodiceIstAssicurativa",	m_sCodiceIstAssicurativa, 50);
		RFX_Text(pFX, "CodiceTEAM",				m_sCodiceTEAM, 50);
		RFX_Text(pFX, "CodiceEsenzione",		m_sCodiceEsenzione, 50);
		RFX_Bool(pFX, "PagamentoRicevuto",		m_bPagamentoRicevuto);

		//Campi JOIN
		//RFX_Long(pFX, "IdProvenienzaEndox",		m_lProvenienzaEndox);
		RFX_Long(pFX, "IdSalaEndox",			m_lIdSalaEndox);
		RFX_Long(pFX, "IdSedeEndox",			m_lIdSedeEndox);
		RFX_Text(pFX, "DescrizioneSala",		m_sDescrizioneSala,			50); //
		RFX_Text(pFX, "DescrizioneSede",		m_sDescrizioneSede,			50); //
		RFX_Long(pFX, "IdRepartoEndox",			m_lIdRepartoEndox);
		RFX_Text(pFX, "DescrizioneReparto",		m_sDescrizioneReparto,					50);
		RFX_Long(pFX, "IdEndoxMedicoInviante",	m_lIDEndoxMedicoInviante);
		RFX_Text(pFX, "MedicoInviante",			m_sMedicoInviante,			255);
		//RFX_Long(pFX, "IdUrgenzaEndox",			m_lIdUrgenzaEndox);
		RFX_Text(pFX, "ComuneNascita",			m_sComuneNascita,			50);
		RFX_Text(pFX, "ComuneResidenza",		m_sComuneResidenza,			50);
		RFX_Long(pFX, "IDEndoxMedicoCurante",	m_lIDEndoxMedicoCurante);
		RFX_Text(pFX, "MedicoCurante",			m_sMedicoCurante,			255);
		//RFX_Text(pFX, "Cittadinanza",			m_sCittadinanza,			255);	
		RFX_Text(pFX, "Provincia",				m_sProvincia,				50);
		RFX_Long(pFX, "UO",						m_lIdUO);
		
		RFX_Long(pFX, "IdProvenienzaNew",		m_lIdProvenienzaNew);
		RFX_Text(pFX, "DescrizioneProvenienzaNew", m_sDescrizioneProvenienzaNew, 255);

		//Simone 13/07/0216
		RFX_Text(pFX, "QUESITODIAGNOSTICO", m_sQuesitoDiagnostico, 3999);
		RFX_Text(pFX, "QUESITODIAGNOSTICOCODIFICATO", m_sQuesitoDiagnosticoCodificato, 50);

		RFX_Text(pFX, "IDENTIFICAZIONEPASSAPORTO", m_sIdentificazionePassaporto, 50);	//Julio - BUG 3285 - Adequação de laudos
		RFX_Text(pFX, "IDENTIFICAZIONEDOC_1", m_sIdentificazioneDoc1, 50);	            //Julio - BUG 3285 - Adequação de laudos
		RFX_Text(pFX, "IDENTIFICAZIONEDOC_2", m_sIdentificazioneDoc2, 50);             	//Julio - BUG 3285 - Adequação de laudos
		
		//Gabriel - P3
		if (m_bColumnsP3)
		{
			RFX_Text(pFX, "CODICEMEDICOINVIANTE2", m_sCodiceMedicoInviante2, 50);
			RFX_Text(pFX, "DESCRIZIONEMEDICOINVIANTE2EST", m_sDescrizioneMedicoInviante2Est, 255);
			RFX_Text(pFX, "MEDICOINVIANTE2", m_sMedicoInviante2, 255);
			RFX_Text(pFX, "CODICEMEDICOINVIANTE3", m_sCodiceMedicoInviante3, 50);
			RFX_Text(pFX, "DESCRIZIONEMEDICOINVIANTE3EST", m_sDescrizioneMedicoInviante3Est, 255);
			RFX_Text(pFX, "MEDICOINVIANTE3", m_sMedicoInviante3, 255);
			RFX_Text(pFX, "CODICEMEDICOINVIANTE4", m_sCodiceMedicoInviante4, 50);
			RFX_Text(pFX, "DESCRIZIONEMEDICOINVIANTE4EST", m_sDescrizioneMedicoInviante4Est, 255);
			RFX_Text(pFX, "MEDICOINVIANTE4", m_sMedicoInviante4, 255);
		}
		//Gabriel - TCP
		if (m_bColumnsTCP)
		{
			RFX_Text(pFX, "ORDERNUMBERCORRELATI", m_sOrderNumberCorrelati, 50);
			RFX_Long(pFX, "STATOTCP", m_lStatoTCP);
		}
	}
}

BOOL CCupWorkListManager::SelectEntry(CListSortableCtrl* pList, int iItem)
{
	BOOL bReturn = TRUE;

	if (IsOpen())
		CloseRecordset("CCupWorkListManager::SelectEntry");

	if ((iItem >= 0) && (iItem < pList->GetItemCount()))
	{
		long lItemData = pList->GetItemData(iItem);

		// Davide - test lock con database
		CString strLock;
		strLock.Format("WORKLIST_%li", abs(lItemData));
		if (!CDbLocker().LockResource(strLock, &theApp.m_dbEndox))
		{
			AfxMessageBox("", MB_ICONSTOP);
			return FALSE;
		}
		//

		CString sFilter;

		//
		if (lItemData < 0)
			sFilter.Format("ID=%li", -lItemData);
		else
			sFilter.Format("ID=%li", lItemData);

		SetBaseFilter(""); // Sandro 20/10/2015 // cambio UO //
		SetOpenFilter(sFilter);

		if (!OpenRecordset("CCupWorkListManager::SelectEntry"))
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));

			// Davide - test lock con database
			CDbLocker().UnlockResource(strLock, &theApp.m_dbEndox);
			//
			return FALSE;
		}

		//

		long lCurPazCode = -1;
		long lIDTipoEsameTemp = -1;

		//La prima fase, eseguita solo se la precedente ha successo, effettua i controlli di base sulla richiesta, come controllare che non sia stata importata da un'altra stazione
		DWORD dwTime = ::timeGetTime();
		int lReturn = SelectEntryFasePreliminare(lItemData, lIDTipoEsameTemp);
		XWriteLogTime("   SelectEntryFasePreliminare", timeGetTime() - dwTime, 0);
		if (lReturn == 0)
		{
			//
			if (bReturn)
			{
				//La seconda fase importa il paziente
				dwTime = ::timeGetTime();
				bReturn = SelectEntryFaseImportazionePaziente(lCurPazCode);
				XWriteLogTime("   SelectEntryFaseImportazionePaziente", timeGetTime() - dwTime, 0);
			}

			//
			if (bReturn)
			{
				//La terza fase, eseguita solo se le precedenti hanno successo, importa l'esame e setta la riga a TRASFERITO
				CString sDataSelezionata = "";

				// Sandro 10/07/2015 // tiro fuori la data partendo dall'item selezionato //

				CString sFilter;
				if (lItemData < 0)
					sFilter.Format("ID=%li", -lItemData);
				else
					sFilter.Format("ID=%li", lItemData);

				CExtOrdiniSet extOrdiniSet;
				extOrdiniSet.SetOpenFilter(sFilter);
				if (extOrdiniSet.OpenRecordset("CCupWorkListManager::SelectEntryFasePreliminare"))
				{
					if (!extOrdiniSet.IsEOF())
						sDataSelezionata = extOrdiniSet.m_sDataEsame;

					extOrdiniSet.CloseRecordset("CCupWorkListManager::SelectEntryFasePreliminare");
				}

				//
				dwTime = ::timeGetTime();
				bReturn = SelectEntryFaseImportazioneEsame(lCurPazCode, lIDTipoEsameTemp, sDataSelezionata);
				XWriteLogTime("   SelectEntryFaseImportazioneEsame", timeGetTime() - dwTime, 0);
			}
		}
		else
			bReturn = FALSE;

		if (!bReturn && lReturn != -2)
		{
			//OPERAZIONI FINALI
			// Apro sempre il recordset
			CString sFilterTemp;
			if (lItemData < 0)
				sFilterTemp.Format("ID=%li", -lItemData);
			else
				sFilterTemp.Format("ID=%li", lItemData);

			try
			{
				CExtOrdiniSet extOrdiniSet;
				extOrdiniSet.SetOpenFilter(sFilterTemp);
				if (extOrdiniSet.OpenRecordset("CCupWorkListManager::SelectEntry"))
				{
					if (!extOrdiniSet.IsEOF())
					{
						if (extOrdiniSet.EditRecordset("CCupWorkListManager::SelectEntry"))
						{
							if (!bReturn)
							{
								// Sandro 11/03/2015 // with Silvano //
								//Se qualcosa è fallito, rimuovo i dati sporchi e rimetto la richiesta in WL

								//Simone 17/12/2015
								// Se idesameins era valorizzato devo, per sicurezza, cancellare l'esame inserito
								if (!extOrdiniSet.IsFieldNull(&extOrdiniSet.m_lIDEsameIns) && extOrdiniSet.m_lIDEsameIns > 0)
								{
									CEsamiSet esamiSet;
									sFilterTemp.Format("contatore=%li", extOrdiniSet.m_lIDEsameIns);
									esamiSet.SetOpenFilter(sFilterTemp);
									if (esamiSet.OpenRecordset("CCupWorkListManager::SelectEntry"))
									{
										if (!esamiSet.IsEOF())
											esamiSet.DeleteRecordset("CCupWorkListManager::SelectEntry");

										esamiSet.CloseRecordset("CCupWorkListManager::SelectEntry");
									}
								}

								extOrdiniSet.m_lStatoAccettazione = LPC_STATO_ACCETTATA;
								extOrdiniSet.SetFieldNull(&extOrdiniSet.m_lIDEsameIns);
							}

							// In ogni caso rimuovo la flag IMPORTING
							// extOrdiniSet.m_bImporting = FALSE;

							if (!extOrdiniSet.UpdateRecordset("CCupWorkListManager::SelectEntry"))
								theApp.AfxMessageBoxEndo("CCupWorkListManager::SelectEntry");
						}

					}

					extOrdiniSet.CloseRecordset("CCupWorkListManager::SelectEntry");
				}
			}
			catch (CDBException* pEx)
			{
				pEx->ReportError();
				pEx->Delete();
			}
		}
		else if (bReturn)
		{
			CString sFilterTemp;
			if (lItemData < 0)
				sFilterTemp.Format("ID=%li", -lItemData);
			else
				sFilterTemp.Format("ID=%li", lItemData);

			CExtOrdiniSet extOrdiniSet;
			extOrdiniSet.SetOpenFilter(sFilterTemp);
			if (extOrdiniSet.OpenRecordset("CCupWorkListManager::SelectEntry"))
			{
				if (!extOrdiniSet.IsEOF())
				{
					if (extOrdiniSet.EditRecordset("CCupWorkListManager::SelectEntry"))
					{
						// In ogni caso rimuovo la flag IMPORTING
						// extOrdiniSet.m_bImporting = FALSE;

						if (!extOrdiniSet.UpdateRecordset("CCupWorkListManager::SelectEntry"))
							theApp.AfxMessageBoxEndo("CCupWorkListManager::SelectEntry");
					}
				}

				extOrdiniSet.CloseRecordset("CCupWorkListManager::SelectEntry");
			}
		}

		// Davide - test lock con database
		CDbLocker().UnlockResource(strLock, &theApp.m_dbEndox);
		//
	}

	if (IsOpen())
		CloseRecordset("CCupWorkListManager::SelectEntry");

	return bReturn;
}

BOOL CCupWorkListManager::CostruisciFiltroPazienteEx(CString *filter, CCupWorkListManager *prenotazione)
{
	// Compongo il filtro con i campi richiesti

	filter->Empty();

	CExtMinPazDataSetSet minPazDataSetSet;
	if (minPazDataSetSet.OpenRecordset("CCupWorkListManager::CostruisciFiltroPaziente"))
	{
		if (!minPazDataSetSet.IsEOF())
		{
			if (minPazDataSetSet.m_bCognome)
			{
				CString sCogn = prenotazione->m_sCognome;
				sCogn.Replace("'", "''");

				if (*filter == "")
					filter->Format("Cognome LIKE '%s'", sCogn);
				else
					filter->AppendFormat(" AND Cognome LIKE '%s'", sCogn);
			}

			if (minPazDataSetSet.m_bCognome2)
			{
				CString sCogn2 = prenotazione->m_sCognome2;
				sCogn2.Replace("'", "''");

				if (*filter == "")
					filter->Format("Cognome2 LIKE '%s'", sCogn2);
				else
					filter->AppendFormat(" AND Cognome2 LIKE '%s'", sCogn2);
			}

			if (minPazDataSetSet.m_bNome)
			{
				CString sNome = prenotazione->m_sNome;
				sNome.Replace("'", "''");

				if (*filter == "")
					filter->Format("Nome LIKE '%s'", sNome);
				else
					filter->AppendFormat(" AND Nome LIKE '%s'", sNome);
			}

			if (minPazDataSetSet.m_bDataNascita)
			{
				if (*filter == "")
					filter->Format("NatoIlCustom=%li", prenotazione->m_lDataNascitaCustom);
				else
					filter->AppendFormat(" AND NatoIlCustom=%li", prenotazione->m_lDataNascitaCustom);
			}

			if (minPazDataSetSet.m_bIstatNascita)
			{
				if (*filter == "")
					filter->Format("IdComuneNascita=%li", prenotazione->m_lISTATNascita);
				else
					filter->AppendFormat(" AND IdComuneNascita=%li", prenotazione->m_lISTATNascita);
			}

			if (minPazDataSetSet.m_bIndirizzoResidenza)
			{
				CString sIndRes = prenotazione->m_sIndirizzoResidenza;
				sIndRes.Replace("'", "''");

				if (*filter == "")
					filter->Format("Via LIKE '%s'", sIndRes);
				else
					filter->AppendFormat(" AND Via LIKE '%s'", sIndRes);
			}

			if (minPazDataSetSet.m_bIstatResidenza)
			{
				if (*filter == "")
					filter->Format("IdComune=%li", prenotazione->m_lISTATResidenza);
				else
					filter->AppendFormat(" AND IdComune=%li", prenotazione->m_lISTATResidenza);
			}

			if (minPazDataSetSet.m_bCapResidenza)
			{
				CString sCapRes = prenotazione->m_sCapResidenza;
				sCapRes.Replace("'", "''");

				if (*filter == "")
					filter->Format("Cap LIKE '%s'", sCapRes);
				else
					filter->AppendFormat(" AND Cap LIKE '%s'", sCapRes);
			}

			if (minPazDataSetSet.m_bTelefono1)
			{
				CString sTel1 = prenotazione->m_sTelefono1;
				sTel1.Replace("'", "''");

				if (*filter == "")
					filter->Format("Telefono1 LIKE '%s'", sTel1);
				else
					filter->AppendFormat(" AND Telefono1 LIKE '%s'", sTel1);
			}

			if (minPazDataSetSet.m_bTelefono2)
			{
				CString sTel2 = prenotazione->m_sTelefono2;
				sTel2.Replace("'", "''");

				if (*filter == "")
					filter->Format("Telefono2 LIKE '%s'", sTel2);
				else
					filter->AppendFormat(" AND Telefono2 LIKE '%s'", sTel2);
			}

			if (minPazDataSetSet.m_bCellulare1)
			{
				CString sCell1 = prenotazione->m_sCellulare1;
				sCell1.Replace("'", "''");

				if (*filter == "")
					filter->Format("Cellulare1 LIKE '%s'", sCell1);
				else
					filter->AppendFormat(" AND Cellulare1 LIKE '%s'", sCell1);
			}

			if (minPazDataSetSet.m_bCellulare2)
			{
				CString sCell2 = prenotazione->m_sCellulare2;
				sCell2.Replace("'", "''");

				if (*filter == "")
					filter->Format("Cellulare2 LIKE '%s'", sCell2);
				else
					filter->AppendFormat(" AND Cellulare2 LIKE '%s'", sCell2);
			}

			if (minPazDataSetSet.m_bCodiceFiscale)
			{
				CString sCodFis = prenotazione->m_sCodiceFiscale;
				sCodFis.Replace("'", "''");

				if (*filter == "")
					filter->Format("CodFisc LIKE '%s'", sCodFis);
				else
					filter->AppendFormat(" AND CodFisc LIKE '%s'", sCodFis);
			}

			if (minPazDataSetSet.m_bCodiceSanitario)
			{
				CString sCodSanit = prenotazione->m_sCodiceSanitario;
				sCodSanit.Replace("'", "''");

				if (*filter == "")
					filter->Format("CodSanit LIKE '%s'", sCodSanit);
				else
					filter->AppendFormat(" AND CodSanit LIKE '%s'", sCodSanit);
			}

			if (minPazDataSetSet.m_bSesso)
			{
				if (*filter == "")
					filter->Format("Sesso=%li", prenotazione->m_lSesso);
				else
					filter->AppendFormat(" AND Sesso=%li", prenotazione->m_lSesso);
			}
		}

		if (!minPazDataSetSet.CloseRecordset("CCupWorkListManager::CostruisciFiltroPaziente"))
			return FALSE;
	}
	else
		return FALSE;

	if (filter->IsEmpty())
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_WL_CONFIGERROR)); //theApp.AfxMessageBoxEndo("C'è un errore grave nella configurazione della worklist, contatta il servizio di assistenza Tesi.");

	return TRUE;
}

CString CCupWorkListManager::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO;
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

void CCupWorkListManager::LoadIntoMemory()
{
	theApp.m_worklistFields.RemoveAll();

	CConfigurazioniListaPrenotazioniSet configSet;
	if (configSet.OpenRecordset("CCupWorkListManager::LoadIntoMemory"))
	{
		while(!configSet.IsEOF())
		{
			worklistField tempField;
			
			tempField.sNomeColonna = configSet.m_sCampo;
			tempField.sTitolo = configSet.m_sTitolo;
			tempField.lDimensioneStampaPerc = configSet.m_lDimensioneStampaPerc;

			theApp.m_worklistFields.AddTail(tempField);

			configSet.MoveNext();
		}

		configSet.CloseRecordset("CCupWorkListManager::LoadIntoMemory");
	}
}

long CCupWorkListManager::GetIdFromEsameIns(long idEsameIns)
{
	long ret = -1;
	CString filter;
	filter.Format("idesameins=%li", idEsameIns);
	SetOpenFilter(filter);
	if (OpenRecordset("CCupWorkListManager::GetIdFromEsameIns"))
	{
		if (!IsEOF())
		{
			ret = m_lId;
		}

		CloseRecordset("CCupWorkListManager::GetIdFromEsameIns");
	}

	return ret;
}

BOOL CCupWorkListManager::AbortIP(CListSortableCtrl* pList, int iItem)
{
	BOOL bReturn = FALSE;

	if ((iItem >= 0) && (iItem < pList->GetItemCount()))
	{
		int nItemData = pList->GetItemData(iItem);

		CString sFilterTemp;
		if (nItemData < 0)
			sFilterTemp.Format("ID=%li", -nItemData);
		else
			sFilterTemp.Format("ID=%li", nItemData);

		//Elimina esame
		SetOpenFilter(sFilterTemp);

		if (OpenRecordset("CCupWorkListManager::AbortIP"))
		{
			if (!IsEOF())
			{
				CEsamiSet esamiSet;
				CString sFilterTemp2;
				sFilterTemp2.Format("contatore=%li", m_lIDEsameIns);
				esamiSet.SetOpenFilter(sFilterTemp2);

				if (esamiSet.OpenRecordset("CCupWorkListManager::AbortIP"))
				{
					if (!esamiSet.IsEOF())
						esamiSet.DeleteRecordset("CCupWorkListManager::AbortIP");

					esamiSet.CloseRecordset("CCupWorkListManager::AbortIP");
				}

				CRegioneSet regioneSet;
				sFilterTemp2.Format("esame=%li", m_lIDEsameIns);
				regioneSet.SetOpenFilter(sFilterTemp2);

				if (regioneSet.OpenRecordset("CCupWorkListManager::AbortIP"))
				{
					while (!regioneSet.IsEOF())
					{
						regioneSet.EditRecordset("CCupWorkListManager::AbortIP");
						regioneSet.m_lIdExtPrestazione = 0;
						regioneSet.UpdateRecordset("CCupWorkListManager::AbortIP");

						regioneSet.MoveNext();
					}

					regioneSet.CloseRecordset("CCupWorkListManager::AbortIP");
				}

				//Rimetti il record in "accettati"
				CExtOrdiniSet extOrdiniSet;
				extOrdiniSet.SetOpenFilter(sFilterTemp);
				if (extOrdiniSet.OpenRecordset("CCupWorkListManager::AbortIP"))
				{
					if (!extOrdiniSet.IsEOF())
					{
						if (extOrdiniSet.EditRecordset("CCupWorkListManager::AbortIP"))
						{
							extOrdiniSet.m_bTrasferito = FALSE;
							extOrdiniSet.m_lStatoAccettazione = LPC_STATO_ACCETTATA;
							extOrdiniSet.SetFieldNull(&extOrdiniSet.m_lIDEsameIns);
							if (!extOrdiniSet.UpdateRecordset("CCupWorkListManager::AbortIP"))
								theApp.AfxMessageBoxEndo("CCupWorkListManager::AbortIP update recordset error");

							long userId;
							AMLogin_GetUserID(&userId);

							if (nItemData < 0)
								CEsamiCaricoAnnullatoSet().InserisciRecord(-nItemData, userId);
							else
								CEsamiCaricoAnnullatoSet().InserisciRecord(nItemData, userId);
									
						}						
					}	

					extOrdiniSet.CloseRecordset("CCupWorkListManager::AbortIP");
				}					
			}

			CloseRecordset("CCupWorkListManager::AbortIP");
		}					
	}

	return bReturn;
}

BOOL CCupWorkListManager::SetNoShow(CListSortableCtrl* pList, int iItem, long lIDMotivo)
{
	BOOL bReturn = FALSE;

	if ((iItem >= 0) && (iItem < pList->GetItemCount()))
	{
		int nItemData = pList->GetItemData(iItem);

		CString sFilterTemp;
		if (nItemData < 0)
			sFilterTemp.Format("ID=%li", -nItemData);
		else
			sFilterTemp.Format("ID=%li", nItemData);

		//Elimina esame
		SetOpenFilter(sFilterTemp);

		if (OpenRecordset("CCupWorkListManager::SetNoShow"))
		{
			if (!IsEOF())
			{		
				CExtOrdiniSet extOrdiniSet;
				extOrdiniSet.SetOpenFilter(sFilterTemp);
				if (extOrdiniSet.OpenRecordset("CCupWorkListManager::SetNoShow"))
				{
					if (!extOrdiniSet.IsEOF())
					{
						if (extOrdiniSet.EditRecordset("CCupWorkListManager::SetNoShow"))
						{
							extOrdiniSet.m_lStatoAccettazione = LPC_STATO_NONPRESENTATA;
							extOrdiniSet.m_lIDMotivo = lIDMotivo;
							if (!extOrdiniSet.UpdateRecordset("CCupWorkListManager::SetNoShow"))
								theApp.AfxMessageBoxEndo("CCupWorkListManager::SetNoShow update recordset error");

							long userId;
							AMLogin_GetUserID(&userId);

							if (nItemData < 0)
								CEsamiNoShowSet().InserisciRecord(-nItemData, userId);
							else
								CEsamiNoShowSet().InserisciRecord(nItemData, userId);

						}
					}

					extOrdiniSet.CloseRecordset("CCupWorkListManager::SetNoShow");
				}				
							
				CloseRecordset("CCupWorkListManager::SetNoShow");
			}

			CloseRecordset("CCupWorkListManager::SetNoShow");
		}
	}

	return bReturn;
}

BOOL CCupWorkListManager::AbortNoShow(CListSortableCtrl* pList, int iItem)
{
	BOOL bReturn = FALSE;

	if ((iItem >= 0) && (iItem < pList->GetItemCount()))
	{
		int nItemData = pList->GetItemData(iItem);

		CString sFilterTemp;
		if (nItemData < 0)
			sFilterTemp.Format("ID=%li", -nItemData);
		else
			sFilterTemp.Format("ID=%li", nItemData);

		//Elimina esame
		SetOpenFilter(sFilterTemp);

		if (OpenRecordset("CCupWorkListManager::AbortNoShow"))
		{
			if (!IsEOF())
			{
				CExtOrdiniSet extOrdiniSet;
				extOrdiniSet.SetOpenFilter(sFilterTemp);
				if (extOrdiniSet.OpenRecordset("CCupWorkListManager::AbortNoShow"))
				{
					if (!extOrdiniSet.IsEOF())
					{
						if (extOrdiniSet.EditRecordset("CCupWorkListManager::AbortNoShow"))
						{
							extOrdiniSet.m_lStatoAccettazione = LPC_STATO_ACCETTATA;
							if (!extOrdiniSet.UpdateRecordset("CCupWorkListManager::AbortNoShow"))
								theApp.AfxMessageBoxEndo("CCupWorkListManager::AbortNoShow update recordset error");

							long userId;
							AMLogin_GetUserID(&userId);

							if (nItemData < 0)
								CEsamiNoShowSet().InserisciRecord(-nItemData, userId);
							else
								CEsamiNoShowSet().InserisciRecord(nItemData, userId);

						}
					}

					extOrdiniSet.CloseRecordset("CCupWorkListManager::AbortNoShow");
				}
			}

			CloseRecordset("CCupWorkListManager::AbortNoShow");
		}
	}

	return bReturn;
}

BOOL CCupWorkListManager::IsExamAbortable(CListSortableCtrl* pList, int iItem)
{
	BOOL bReturn = FALSE;

	if ((iItem >= 0) && (iItem < pList->GetItemCount()))
	{
		int nItemData = pList->GetItemData(iItem);

		CString sFilterTemp;
		if (nItemData < 0)
			sFilterTemp.Format("ID=%li", -nItemData);
		else
			sFilterTemp.Format("ID=%li", nItemData);

		//Elimina esame
		SetOpenFilter(sFilterTemp);

		if (OpenRecordset("CCupWorkListManager::IsExamAbortable"))
		{
			if (!IsEOF())
			{
				CEsamiSet esamiSet;
				CString sFilterTemp2;
				sFilterTemp2.Format("contatore=%li", m_lIDEsameIns);
				esamiSet.SetOpenFilter(sFilterTemp2);

				if (esamiSet.OpenRecordset("CCupWorkListManager::IsExamAbortable"))
				{
					if (!esamiSet.IsEOF())
						if (!esamiSet.IsFieldNull(&esamiSet.m_sDataOraAcquisizione))
							bReturn = TRUE;

					esamiSet.CloseRecordset("CCupWorkListManager::IsExamAbortable");
				}
				
			}

			CloseRecordset("CCupWorkListManager::IsExamAbortable");
		}
	}

	return bReturn;
}

BOOL CCupWorkListManager::CampiObbligatoriValorizzati(long idRichiesta)
{
	BOOL bReturn = TRUE;

	CCupWorkListManager tempWl(m_pEsamiView);
	CString filter;
	filter.Format("id = %li", idRichiesta);
	tempWl.SetOpenFilter(filter);

	if (tempWl.OpenRecordset("CCupWorkListManager::CampiObbligatoriValorizzati"))
	{
		//Controllo se i campi obbligatori sono valorizzati		
		CExtMinPazDataSetSet minPazDataSetSet;
		if (minPazDataSetSet.OpenRecordset("CCupWorkListManager::CampiObbligatoriValorizzati"))
		{
			if (!minPazDataSetSet.IsEOF())
			{
				if (minPazDataSetSet.m_bCognome && (tempWl.IsFieldNull(&tempWl.m_sCognome) || tempWl.m_sCognome == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bCognome2 && (tempWl.IsFieldNull(&tempWl.m_sCognome2) || tempWl.m_sCognome2 == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bNome && (tempWl.IsFieldNull(&tempWl.m_sNome) || tempWl.m_sNome == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bDataNascita && (tempWl.IsFieldNull(&tempWl.m_sDataNascita) || tempWl.m_sDataNascita == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bIstatNascita && (tempWl.IsFieldNull(&tempWl.m_lISTATNascita) || tempWl.m_lISTATNascita == 0))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bIndirizzoResidenza && (tempWl.IsFieldNull(&tempWl.m_sIndirizzoResidenza) || tempWl.m_sIndirizzoResidenza == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bIstatResidenza && (tempWl.IsFieldNull(&tempWl.m_lISTATResidenza) || tempWl.m_lISTATResidenza == 0))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bCapResidenza && (tempWl.IsFieldNull(&tempWl.m_sCapResidenza) || tempWl.m_sCapResidenza == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bTelefono1 && (tempWl.IsFieldNull(&tempWl.m_sTelefono1) || tempWl.m_sTelefono1 == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bTelefono2 && (tempWl.IsFieldNull(&tempWl.m_sTelefono2) || tempWl.m_sTelefono2 == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bCellulare1 && (tempWl.IsFieldNull(&tempWl.m_sCellulare1) || tempWl.m_sCellulare1 == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bCellulare2 && (tempWl.IsFieldNull(&tempWl.m_sCellulare2) || tempWl.m_sCellulare2 == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bCodiceFiscale && (tempWl.IsFieldNull(&tempWl.m_sCodiceFiscale) || tempWl.m_sCodiceFiscale == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bCodiceSanitario && (tempWl.IsFieldNull(&tempWl.m_sCodiceSanitario) || tempWl.m_sCodiceSanitario == ""))
					bReturn = FALSE;
				if (minPazDataSetSet.m_bSesso && (tempWl.IsFieldNull(&tempWl.m_lSesso)))
					bReturn = FALSE;
			}

			minPazDataSetSet.CloseRecordset("CCupWorkListManager::CampiObbligatoriValorizzati");
		}

		tempWl.CloseRecordset("CCupWorkListManager::CampiObbligatoriValorizzati");
	}

	return bReturn;
}

// Sandro 05/03/2014 //
BOOL CCupWorkListManager::SelectEntryFaseImportazioneEsame(long &lCurPazCode, long &idTipoEsameTemp, CString sDataSelezionata)
{
	BOOL bReturn = TRUE;

	try
	{
		CString sTesto094 = "";
		CString sTesto095 = "";
		CString sTesto096 = "";

		//Recupero il tipo esame che deve essere importato
		if (idTipoEsameTemp < 0)
		{
			CVistaExtPrestazioniSet extPrestazioniSet;
			CString strFilter;
			strFilter.Format("idOrdine = %li AND TipoEsame IS NOT NULL", m_lId);
			extPrestazioniSet.SetOpenFilter(strFilter);
			if (extPrestazioniSet.OpenRecordset("CCupWorkList::SelectEntryFaseImportazioneEsame"))
			{
				if (!extPrestazioniSet.IsEOF())
				{
					idTipoEsameTemp = extPrestazioniSet.m_lIdTipoEsameEndox;
					sTesto094 = extPrestazioniSet.m_sCodicePrestazione;
					sTesto095 = extPrestazioniSet.m_sDescrizionePrestazione;
				}

				if (!extPrestazioniSet.CloseRecordset("CCupWorkList::SelectEntryFaseImportazioneEsame"))
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
					//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
					return FALSE;
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
				//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
				return FALSE;
			}
		}

		//Simone - Prima di inserire l'esame devo verificare se esiste un esame di quel tipo, per lo stesso paziente e con codesame = null
		//			Se dovesse esistere propongo all'utente l'abbinamento
		//		Se sono più di uno devo proporre una lista dove l'utente può scegliere quale esame abbinare
		CVistaEsamiPerWLSet tempEsamiSet;
		CString strFilter;
		strFilter.Format("IdEsame = %li AND Paziente = %li AND (Codesame IS NULL OR Codesame = '' OR Codesame like 'ENDOX%%') AND eliminato = 0 and contatore not in (select distinct idesame from EXT_ESAMI_CHIUSI where eseguito = 1)", idTipoEsameTemp, lCurPazCode);
		strFilter.AppendFormat(" and DataEsame like '%s%%'", sDataSelezionata.Left(8));

		tempEsamiSet.SetOpenFilter(strFilter);

		if (tempEsamiSet.OpenRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame"))
		{
			/*if (!tempEsamiSet.IsEOF())
			{
				CString message;
				message = theApp.GetMessageString(IDS_LISTAPREN_ESAMETROVATO1) + "\r\n" + theApp.GetMessageString(IDS_LISTAPREN_ESAMETROVATO2) + "\r\n" + theApp.GetMessageString(IDS_LISTAPREN_ESAMETROVATO3);
				theApp.AfxMessageBoxEndo(message, MB_TOPMOST);
				//Mostro la lista degli esami utilizzabili
				long idExam = -1;
				CExamListDlg examList(m_pEsamiView, &tempEsamiSet, &idExam);
				if (examList.DoModal() == IDOK)
				{
					if (bReturn)
					{
						//Abbina esame
						if (examList.m_iOperation == 2)
						{
							UpdateDatiEsame(lCurPazCode, idExam, sTesto094, sTesto095, sTesto096);
							DeleteOldRequest(m_lId, idExam); //Setta ad eliminato la vecchia richiesta in wl se esiste

							if (theApp.AfxMessageBoxEndo("Riprocessare gli eventuali erogati associati all'esame?", MB_YESNO) == IDYES)
								UpdateEsamiChiusi(idExam); //Prende le chiusure fatte precedentemente all'abbinamento e le rimette in coda

							UpdateWithExamID(m_lId, idExam);

							m_pEsamiView->RicercaCodicePaziente(lCurPazCode, idExam, FALSE, TRUE);
							m_pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);
						}

						//Inserisci nuovo
						if (examList.m_iOperation == 1)
						{
							m_pEsamiView->RicercaCodicePaziente(lCurPazCode, 0, FALSE, TRUE);
							m_pEsamiView->OnEsameNewAutoCup(idTipoEsameTemp, m_lId);

							m_pEsamiView->OnEsameUpdateCup();
							if (m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
							{
								tempEsamiSet.CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
								//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
								return FALSE;
							}
							UpdateDatiEsame(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->GetLastAdd(), sTesto094, sTesto095, sTesto096);
							UpdateWithExamID(m_lId, m_pEsamiView->m_pEsamiSet->GetLastAdd());

							m_pEsamiView->MovePazientiAndEsami(NULL, TRUE, TRUE);
						}
					}
				}
				else
				{
					//Operazione annullata
					tempEsamiSet.CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
					//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
					return FALSE;
				}
			}
			else*/
			{
				if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_LISTAPREN_ESAMENEW), MB_YESNO) == IDNO)
				{
					tempEsamiSet.CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
					//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
					return FALSE;
				}

				DWORD dwTime = ::timeGetTime();
				m_pEsamiView->RicercaCodicePaziente(lCurPazCode, 0, FALSE, TRUE);
				XWriteLogTime("   SelectEntryFaseImportazioneEsame RicercaCodicePaziente", timeGetTime() - dwTime, 0);

				dwTime = ::timeGetTime();
				m_pEsamiView->OnEsameNewAutoCup(idTipoEsameTemp, m_lId);
				XWriteLogTime("   SelectEntryFaseImportazioneEsame OnEsameNewAutoCup", timeGetTime() - dwTime, 0);

				dwTime = ::timeGetTime();
				BOOL bContinue = m_pEsamiView->OnEsameUpdateCup();
				XWriteLogTime("   SelectEntryFaseImportazioneEsame OnEsameUpdateCup", timeGetTime() - dwTime, 0);

				if (bContinue)
				{
					if (m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
					{
						tempEsamiSet.CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
						//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
						return FALSE;
					}
					//Julio Correcao do problema de exames em pacientes errados
					dwTime = ::timeGetTime();
					if (SelectEntryFaseCheckForMistakenLastAdd()) //Se um erro for encontrado nao vou em frente
					{
						AfxMessageBox("Ocorreu um erro enquanto o sistema tentava criar o exame. Tente novamente em alguns segundos.");
						return FALSE;
					}
					
					XWriteLogTime("   SelectEntryFaseImportazioneEsame SelectEntryFaseCheckForMistakenLastAdd", timeGetTime() - dwTime, 0);
					//

					dwTime = ::timeGetTime();
					UpdateDatiEsame(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->GetLastAdd(), sTesto094, sTesto095, sTesto096);
					XWriteLogTime("   SelectEntryFaseImportazioneEsame UpdateDatiEsame", timeGetTime() - dwTime, 0);

					dwTime = ::timeGetTime();
					UpdateWithExamID(m_lId, m_pEsamiView->m_pEsamiSet->GetLastAdd());
					XWriteLogTime("   SelectEntryFaseImportazioneEsame UpdateWithExamID", timeGetTime() - dwTime, 0);

					dwTime = ::timeGetTime();
					m_pEsamiView->MovePazientiAndEsami(NULL, TRUE, TRUE);
					XWriteLogTime("   SelectEntryFaseImportazioneEsame MovePazientiAndEsami", timeGetTime() - dwTime, 0);
				}
				else
				{
					if (theApp.m_bSaveCompleteLog)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_LISTAPREN_ADD_EXAM_ERROR));
						CLogFileWriter::Get()->WriteLogLine0("Erro no m_pEsamiView->OnEsameUpdateCup()");
						CLogFileWriter::Get()->WriteLogLine0("");
						bReturn = FALSE;
					}
				}
			}
		}

		tempEsamiSet.CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
		//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazioneEsame");
	}
	catch (CDBException* pEx)
	{
		theApp.AfxMessageBoxEndo("Fase esame unattended error");
		pEx->ReportError();
		pEx->Delete();
		return FALSE;
	}
	catch (CMemoryException* pEx)
	{
		theApp.AfxMessageBoxEndo("Fase esame unattended error");
		pEx->ReportError();
		pEx->Delete();
		return FALSE;
	}
	catch (...)
	{
		theApp.AfxMessageBoxEndo("Fase esame unattended error");
		return FALSE;
	}

	return bReturn;
}

void CCupWorkListManager::DeleteOldRequest(long idWorklist, long lIDEsame)
{
	CString filter;
	filter.Format("idesameins = %li and id <> %li", lIDEsame, idWorklist);
	CExtOrdiniSet set;
	set.SetOpenFilter(filter);

	if (set.OpenRecordset("CCupWorkListManager::DeleteOldRequest"))
	{
		while (!set.IsEOF())
		{
			set.EditRecordset("CCupWorkListManager::DeleteOldRequest");
			set.m_lIDEsameIns = -1;
			set.UpdateRecordset("CCupWorkListManager::DeleteOldRequest");

			set.DeleteRecordset("CCupWorkListManager::DeleteOldRequest");

			set.MoveNext();
		}

		set.CloseRecordset("CCupWorkListManager::DeleteOldRequest");
	}
}

void CCupWorkListManager::UpdateEsamiChiusi(long lIDEsame)
{
	CString filter;
	filter.Format("idesame = %li", lIDEsame);
	CEsamiChiusiSet set;
	set.SetOpenFilter(filter);
	set.SetSortRecord("id");

	if (set.OpenRecordset("CCupWorkListManager::UpdateEsamiChiusi"))
	{
		while (!set.IsEOF())
		{
			set.EditRecordset("CCupWorkListManager::UpdateEsamiChiusi");
			set.m_lEseguito = 0;
			set.UpdateRecordset("CCupWorkListManager::UpdateEsamiChiusi");

			set.MoveNext();
		}

		set.CloseRecordset("CCupWorkListManager::UpdateEsamiChiusi");
	}
}

void CCupWorkListManager::UpdateWithExamID(long lIDPrenotazione, long lIDEsame)
{
	CExtOrdiniSet extOrdiniSet;
	CString filter;
	filter.Format("id=%li", lIDPrenotazione);
	extOrdiniSet.SetOpenFilter(filter);

	if (extOrdiniSet.OpenRecordset("CCupWorkListManager::UpdateWithExamID"))
	{
		if (!extOrdiniSet.IsEOF())
		{
			if (extOrdiniSet.EditRecordset("CCupWorkListManager::UpdateWithExamID"))
			{
				extOrdiniSet.m_bTrasferito = TRUE;
				extOrdiniSet.m_lStatoAccettazione = LPC_STATO_INCORSO;
				extOrdiniSet.m_lIDEsameIns = lIDEsame;
				if (!extOrdiniSet.UpdateRecordset("CCupWorkListManager::UpdateWithExamID"))
					theApp.AfxMessageBoxEndo("CCupWorkListManager::UpdateWithExamID update recordset error");

				//Aggiungo l'esame alla lista degli esami accettati
				long userId;
				AMLogin_GetUserID(&userId);
				CEsamiAccettatiSet().InserisciRecord(lIDEsame, userId);
			}
		}

		extOrdiniSet.CloseRecordset("CCupWorkListManager::UpdateWithExamID");
	}
}

void CCupWorkListManager::UpdateDatiEsame(long lIDPaziente, long lIDEsame, CString sTesto94, CString sTesto95, CString sTesto96)
{
	try
	{
		CEsamiSet tempExamSet;
		CString filter;
		filter.Format("contatore = %li", lIDEsame);
		tempExamSet.SetOpenFilter(filter);
		if (tempExamSet.OpenRecordset("CCupWorkListManager::UpdateDatiEsame"))
		{
			if (!tempExamSet.IsEOF())
			{
				tempExamSet.EditRecordset("CCupWorkListManager::UpdateDatiEsame");

				/*if (!IsFieldNull(&m_lIdUrgenzaEndox))
				tempExamSet.m_nCodiceRAO = m_lIdUrgenzaEndox;*/

				tempExamSet.m_sCodEsame = m_sOrderNumber;

				//Perchè questo? Dovrebbe essere presto da ext_ordini.nosologico... proviamo
				//tempExamSet.m_sRicovero = m_pEsamiView->m_pPazientiSet->m_sCodiceRicovero;
				tempExamSet.m_sRicovero = m_sNosologico;

				//Se riesco a transcodificare il medico metto la transcodifica, altrimenti metto il codice così come mi è arrivato
				if (!IsFieldNull(&m_lIDEndoxMedicoInviante))
					tempExamSet.m_lInvMedico = m_lIDEndoxMedicoInviante;

				if (!IsFieldNull(&m_sMedicoInviante) && m_sMedicoInviante.Trim() != "")
					tempExamSet.m_sInvMedico = m_sMedicoInviante;
				else if (!IsFieldNull(&m_sDescrizioneMedicoInvianteEst) && m_sDescrizioneMedicoInvianteEst.Trim() != "")
					tempExamSet.m_sInvMedico = m_sDescrizioneMedicoInvianteEst;

				//Gabriel - P3
				if (m_bColumnsP3)
				{
					if (!IsFieldNull(&m_sMedicoInviante2) && m_sMedicoInviante2.Trim() != "")
						tempExamSet.m_sInvMedico2 = m_sMedicoInviante2;
					else if (!IsFieldNull(&m_sDescrizioneMedicoInviante2Est) && m_sDescrizioneMedicoInviante2Est.Trim() != "")
						tempExamSet.m_sInvMedico2 = m_sDescrizioneMedicoInviante2Est;

					if (!IsFieldNull(&m_sMedicoInviante3) && m_sMedicoInviante3.Trim() != "")
						tempExamSet.m_sInvMedico3 = m_sMedicoInviante3;
					else if (!IsFieldNull(&m_sDescrizioneMedicoInviante3Est) && m_sDescrizioneMedicoInviante3Est.Trim() != "")
						tempExamSet.m_sInvMedico3 = m_sDescrizioneMedicoInviante3Est;

					if (!IsFieldNull(&m_sMedicoInviante4) && m_sMedicoInviante4.Trim() != "")
						tempExamSet.m_sInvMedico4 = m_sMedicoInviante4;
					else if (!IsFieldNull(&m_sDescrizioneMedicoInviante4Est) && m_sDescrizioneMedicoInviante4Est.Trim() != "")
						tempExamSet.m_sInvMedico4 = m_sDescrizioneMedicoInviante4Est;
				}

				//Gabriel - TCP FIX
				if (m_bColumnsTCP)
				{
					if (!IsFieldNull(&m_sOrderNumberCorrelati) && m_sOrderNumberCorrelati.Trim() != "")
					{
						tempExamSet.m_sCodesameCorrelati = m_sOrderNumberCorrelati;
						if (m_lStatoTCP == 1)
							CEsamiSet().SetConiugatoPrincipaleSecondario(m_sOrderNumberCorrelati, m_sOrderNumber, TRUE);
					}
				}
				
				if (!IsFieldNull(&m_sNote) && m_sNote.Trim() != "")
					tempExamSet.m_sAppunti = m_sNote;
				if (!IsFieldNull(&m_lIdRepartoEndox))
					tempExamSet.m_lInviante = m_lIdRepartoEndox;

				//Simone - RIMA 15157
				// Devo agganciarmi alla nuova provenienza, dalla quale deduco se è interno o esterno
				if (!IsFieldNull(&m_lIdProvenienzaNew))
				{
					tempExamSet.m_lIdProvenienzaNew = m_lIdProvenienzaNew;
					tempExamSet.m_lProvenienza = CProvenienzaSet().GetInternoEsterno(m_lIdProvenienzaNew);
				}

				//Simone - RAS 20150049
				if (theApp.m_sSalaEsameDefault.Trim().GetLength() > 0)
					tempExamSet.m_sSalaEsame = theApp.m_sSalaEsameDefault.Trim();
				else if (!IsFieldNull(&m_sDescrizioneSala) && m_sDescrizioneSala.Trim() != "")
					tempExamSet.m_sSalaEsame = m_sDescrizioneSala;
				else
					tempExamSet.m_sSalaEsame = "";

				if (!IsFieldNull(&m_lIdSedeEndox))
					tempExamSet.m_lIDSedeEsame = m_lIdSedeEndox;

				//Se l'oscuramento volontario arriva dal cup, deve essere attivato e bloccato
				if (m_bOscuramentoVolontario == TRUE)
				{
					tempExamSet.m_bSissOscuramento50 = TRUE;
					tempExamSet.m_bSissOscuramento50Bloccato = TRUE;
				}
				else
				{
					tempExamSet.m_bSissOscuramento50 = FALSE;
					tempExamSet.m_bSissOscuramento50Bloccato = FALSE;
				}

				tempExamSet.m_sEsenzioneDaIntegrazione = m_sCodiceEsenzione;
				tempExamSet.m_bPagamentoRicevuto = m_bPagamentoRicevuto;

				tempExamSet.m_lLivelloUrgenza = CExtTransUrgenzaSet().GetPriorityFromCode(m_sUrgenza);

				tempExamSet.m_sQuesitoDiagnostico = m_sQuesitoDiagnostico;
				tempExamSet.m_sQuesitoDiagnosticoCodificato = m_sQuesitoDiagnosticoCodificato;

				// Sandro 15/11/2016 //

				if (theApp.m_bPersonalizzazioniBrasileFleury)
				{
					tempExamSet.m_setEP.m_sTesto094 = sTesto94;
					tempExamSet.m_setEP.m_sTesto095 = sTesto95;
					tempExamSet.m_setEP.m_sTesto096 = sTesto96;
				}

				//Operatori
				CExtOrdiniOperatoriSet operatoriSet;
				CString strFilt;
				strFilt.Format("idRichiesta = %li", m_lId);
				operatoriSet.SetOpenFilter(strFilt);
				if (operatoriSet.OpenRecordset("CEsamiView::UpdateDatiEsame"))
				{
					while (!operatoriSet.IsEOF())
					{
						long idOperatore = CMediciSet().GetContatoreFromCodice(operatoriSet.m_sCodice);
						if (idOperatore > 0)
						{
							if (tempExamSet.IsFieldNull(&tempExamSet.m_lMedico) || tempExamSet.m_lMedico <= 0)
								tempExamSet.m_lMedico = idOperatore;
							else if (tempExamSet.IsFieldNull(&tempExamSet.m_lAssistente) || tempExamSet.m_lAssistente <= 0)
								tempExamSet.m_lAssistente = idOperatore;
						}


						operatoriSet.MoveNext();
					}

					operatoriSet.CloseRecordset("CEsamiView::UpdateDatiEsame");
				}

				tempExamSet.UpdateRecordset("CCupWorkListManager::UpdateDatiEsame");
			}

			tempExamSet.CloseRecordset("CCupWorkListManager::UpdateDatiEsame");
		}

		//Gabriel - TCP FIX
		if (m_bColumnsTCP)
		{
			if (!IsFieldNull(&m_sOrderNumberCorrelati) && m_sOrderNumberCorrelati.Trim() != "" && m_lStatoTCP == 1)
			{
				//Gabriel - TCP FIX
				long lContatorePrincipale = CEsamiSet().GetContatore(m_sOrderNumberCorrelati);
				long lContatoreSecondario = CEsamiSet().GetContatore(m_sOrderNumber);
				CEsamiIntegratiSet().AddRecord(lContatorePrincipale, lContatoreSecondario, TRUE);
			}
		}

		//Importo tutte le prestazioni di quell'ordine NON ELIMINATE
		CVistaExtPrestazioniSet extPrestazioniSet;
		CRegioneSet regioneSet;
		CString strFilter;
		strFilter.Format("IDORDINE = %li", m_lId);
		extPrestazioniSet.SetOpenFilter(strFilter);
		if (extPrestazioniSet.OpenRecordset("CCupWorkListManager::UpdateDatiEsame"))
		{
			while (!extPrestazioniSet.IsEOF())
			{
				if (!extPrestazioniSet.IsFieldNull(&extPrestazioniSet.m_lIdPrestazioneEndox) && extPrestazioniSet.m_lIdPrestazioneEndox > 0)
				{
					if (!regioneSet.IsOpen())
					{
						regioneSet.SetOpenFilter("Contatore=0");
						regioneSet.OpenRecordset("CCupWorkListManager::UpdateDatiEsame");
					}

					if (regioneSet.AddNewRecordset("CCupWorkListManager::UpdateDatiEsame"))
					{
						regioneSet.m_lEsame = lIDEsame;
						regioneSet.m_lCodice = extPrestazioniSet.m_lIdPrestazioneEndox;
						regioneSet.m_lQuantita = extPrestazioniSet.m_lQuantita;
						regioneSet.m_lIdExtPrestazione = extPrestazioniSet.m_lId;
						//Simone - Stato CUP deve essere messo a 0 altrimenti la prestazione verrebbe segnalata come aggiunta a mano
						regioneSet.m_lStatoCUP = 0;

						regioneSet.UpdateRecordset("CCupWorkListManager::UpdateDatiEsame");
					}
				}

				extPrestazioniSet.MoveNext();
			}

			tempExamSet.CloseRecordset("CCupWorkListManager::UpdateDatiEsame");
		}

		if (regioneSet.IsOpen())
			regioneSet.CloseRecordset("CCupWorkListManager::UpdateDatiEsame");

		CExtOrdiniAllegatiSet allegatiSetTemp;
		strFilter.Format("idRichiesta = %li and getOnDemand=0", m_lId); //Prendo solo gli allegati che non sono on-demand, i quali vanno presi solo se richiesti dal medico durante l'esame
		allegatiSetTemp.SetOpenFilter(strFilter);
		if (allegatiSetTemp.OpenRecordset("CEsamiView::UpdateDatiEsame"))
		{
			while (!allegatiSetTemp.IsEOF())
			{
				CTime timeNow = CTime::GetCurrentTime();
				CMyDocManager manager;
				manager.ImportDoc(lIDPaziente, lIDEsame, allegatiSetTemp.m_sDescrizione, timeNow.Format("%Y%m%d%H%M%S"), allegatiSetTemp.m_sPath, FALSE);

				::DeleteFile(allegatiSetTemp.m_sPath);

				allegatiSetTemp.MoveNext();
			}

			allegatiSetTemp.CloseRecordset("CEsamiView::UpdateDatiEsame");
		}

		//Diagnosi
		CExtOrdiniDiagnosiICD9Set diagnosiSet;
		strFilter.Format("idRichiesta = %li", m_lId);
		diagnosiSet.SetOpenFilter(strFilter);
		if (diagnosiSet.OpenRecordset("CEsamiView::UpdateDatiEsame"))
		{
			while (!diagnosiSet.IsEOF())
			{
				long idDiagnosi = CDiagnosiICD9Set().GetIdFromICD9(diagnosiSet.m_sCodiceICD9);
				if (idDiagnosi > 0)
					CDiagnosiEsamiSet().Add(lIDEsame, idDiagnosi);

				diagnosiSet.MoveNext();
			}

			diagnosiSet.CloseRecordset("CEsamiView::UpdateDatiEsame");
		}

		//Procedure
		CExtOrdiniProcedureICD9Set procedureSet;
		strFilter.Format("idRichiesta = %li", m_lId);
		procedureSet.SetOpenFilter(strFilter);
		if (procedureSet.OpenRecordset("CEsamiView::UpdateDatiEsame"))
		{
			while (!procedureSet.IsEOF())
			{
				long idProcedura = CProcedureICD9Set().GetIdFromICD9(procedureSet.m_sCodiceICD9);
				if (idProcedura > 0)
					CProcedureEsamiSet().Add(lIDEsame, idProcedura);

				procedureSet.MoveNext();
			}

			procedureSet.CloseRecordset("CEsamiView::UpdateDatiEsame");
		}

	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
}

// Sandro 05/03/2014 //
int CCupWorkListManager::SelectEntryFasePreliminare(long lItemData, long &idTipoEsameTemp)
{
	int lReturn = 0;

	try
	{
		if (m_bTrasferito) // || m_bImporting)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_WL_TRASFERITO));
			//CloseRecordset("CCupWorkListManager::SelectEntryFasePreliminare");
			lReturn = -2;
		}
		else
		{
			// Sandro 11/03/2015 // with Silvano //
			try
			{
				CString sFilter;

				//
				if (lItemData < 0)
					sFilter.Format("ID=%li", -lItemData);
				else
					sFilter.Format("ID=%li", lItemData);

				CExtOrdiniSet extOrdiniSet;
				extOrdiniSet.SetOpenFilter(sFilter);
				if (extOrdiniSet.OpenRecordset("CCupWorkListManager::SelectEntryFasePreliminare"))
				{
					if (!extOrdiniSet.IsEOF())
					{
						// se lItemData è negativo significa che la prenotazione non è importabile automaticamente (pallino rosso) //
						if (lItemData < 0)
						{
							if (!IsEOF())
							{
								if (theApp.m_bAssidenKey && (IsFieldNull(&m_sAssiden) || m_sAssiden == ""))
								{
									//CloseRecordset("CCupWorkList::SelectEntryFasePreliminare");
									theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERRPREN_ID_NOTFOUND));
									lReturn = -1;
								}
								else
								{
									if (!theApp.m_bAssidenKey && !CampiObbligatoriValorizzati(m_lId))
									{
										//CloseRecordset("CCupWorkList::SelectEntryFasePreliminare");
										theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERRPREN_SET_NOTFOUND));
										lReturn = -1;
									}
									else
									{
										// se l'assiden invece c'è, per forza siamo nel secondo caso dove manca la definizione del tipo esame //
										//CloseRecordset("CCupWorkList::SelectEntryFasePreliminare");
										if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAME_NOTDEF), MB_YESNO) == IDYES)
										{
											m_bTipoEsameDlg = TRUE;
											CTipoEsameNewDlg dlg(m_pEsamiView, m_pEsamiView, FALSE, TRUE, 0);
											if (dlg.DoModal() == IDOK)
												idTipoEsameTemp = dlg.GetTipoEsame();
											else
											{
												m_bTipoEsameDlg = FALSE;
												lReturn = -1;
											}
											m_bTipoEsameDlg = FALSE;
										}
										else
											lReturn = -1;
									}
								}

							}
						}
					}

					extOrdiniSet.CloseRecordset("CCupWorkListManager::SelectEntryFasePreliminare");
				}

				//CString strQuery = "UPDATE EXT_ORDINI SET TRASFERITO=1 WHERE " + sFilter;
				//theApp.m_dbEndox.ExecuteSQL(strQuery);
			}
			catch (CDBException* pEx)
			{
				pEx->ReportError();
				pEx->Delete();
			}
		}
	}
	catch (CDBException* pEx)
	{
		theApp.AfxMessageBoxEndo("Fase preliminare unattended error");
		pEx->ReportError();
		pEx->Delete();
		lReturn = -1;
	}
	catch (CMemoryException* pEx)
	{
		theApp.AfxMessageBoxEndo("Fase preliminare unattended error");
		pEx->ReportError();
		pEx->Delete();
		lReturn = -1;
	}
	catch (...)
	{
		theApp.AfxMessageBoxEndo("Fase preliminare unattended error");
		lReturn = -1;
	}

	return lReturn;
}

//Julio Correcao do problema de exames em pacientes errados 
//Julio Correcao (espero) do erro do sistema colocando um exame de um paciente em um outro
//Retornando FALSE quer dizer que esta tudo ok com o check, retornando TRUE quer dizer que uma inconsistência foi encontrada
BOOL CCupWorkListManager::SelectEntryFaseCheckForMistakenLastAdd()
{
	/*
	Em alguns casos o sistema não está conseguindo inserir o exame mas não da erro.
	O fluxo de criacao de exame pela worklist continua e ele chega em 
	UpdateDatiEsame(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->GetLastAdd(), sTesto094, sTesto095, sTesto096);
	isso faz com que o sistema atualize o ultimo exame realizado pela estação atual, com os dados do exame sendo criado na worklist

	Vou fazer um check na ext_ordini pra ver se o getLastAdd retornado já não consta como idesameins de um outro exame
	espero que isso previna o update dos dados.
	*/
	BOOL bResult = FALSE;

	long lLastAdd = m_pEsamiView->m_pEsamiSet->GetLastAdd();

	CExtOrdiniSet extOrdiniSet;
	CString filter;
	filter.Format("IdEsameIns=%li", lLastAdd);
	extOrdiniSet.SetOpenFilter(filter);

	if (extOrdiniSet.OpenRecordset("CCupWorkListManager::SelectEntryFaseCheckForMistakenLastAdd"))
	{
		if (!extOrdiniSet.IsEOF()) //Encontrou um regsitro, teoricamente nunca deveria encontrar
		{
			bResult = TRUE;
			
			//Vou guardar um log de que deu errado para analises futuras
			//estou usando esta tabela para nao precisar atualizar o banco de dados, mas ela nao foi feita para isso
			long userId;
			AMLogin_GetUserID(&userId);
			CEsamiCaricoAnnullatoSet().InserisciRecordForFaliure(userId, lLastAdd, m_sOrderNumber);		
			
		}

		extOrdiniSet.CloseRecordset("CCupWorkListManager::SelectEntryFaseCheckForMistakenLastAdd");
	}
	return bResult;
}

// Sandro 05/03/2014 //
BOOL CCupWorkListManager::SelectEntryFaseImportazionePaziente(long &lCurPazCode)
{
	BOOL bReturn = TRUE;

	try
	{
		// Bisogna controllare che il paziente non sia già inserito ed eventualmente inserirlo, successivamente bisogna inserire l'esame, i suoi dettagli e le prestazioni associate
		CPazientiSet pazientiSet;
		CString filter = "";

		if (theApp.m_bAssidenKey)
		{
			filter.Format("assiden = '%s'", m_sAssiden); // assiden = '%s' and eliminato = 0 // Sandro: l'eliminato non serve perchè c'è già di base nel recordset pazienti //
		}
		else
		{
			if (!CostruisciFiltroPazienteEx(&filter, this))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
				//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
				return FALSE;
			}

			filter += " and (assiden is null or assiden = '')";
		}

		pazientiSet.SetOpenFilter(filter);

		if (pazientiSet.OpenRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
		{
			if (pazientiSet.IsEOF())
			{
				// non c'è --> devo inserirlo //

				if (pazientiSet.AddNewRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
				{
					//Associazione campi
					pazientiSet.m_sAssIden = m_sAssiden;
					pazientiSet.m_sCognome = m_sCognome;
					pazientiSet.m_sCognome2 = m_sCognome2;
					pazientiSet.m_sNome = m_sNome;
					pazientiSet.m_lNatoIlCustom = m_lDataNascitaCustom;
					pazientiSet.m_lIDComuneNascita = m_lISTATNascita;
					if (!IsFieldNull(&m_sComuneNascita) && m_sComuneNascita.Trim() != "")
						pazientiSet.m_sNatoA = m_sComuneNascita;
					else
						pazientiSet.m_sNatoA = m_sDescrizioneComuneNascitaEst;
					pazientiSet.m_sVia = m_sIndirizzoResidenza;
					pazientiSet.m_lIDComune = m_lISTATResidenza;
					if (!IsFieldNull(&m_sComuneResidenza) && m_sComuneResidenza.Trim() != "")
					{
						pazientiSet.m_sCitta = m_sComuneResidenza;
						pazientiSet.m_sProvincia = m_sProvincia;
					}
					else
					{
						pazientiSet.m_sCitta = m_sDescrizioneComuneResidenzaEst;
						pazientiSet.m_sProvincia = m_sProvinciaEst;
					}
					pazientiSet.m_sCAP = m_sCapResidenza;
					pazientiSet.m_sTelefono1 = m_sTelefono1;
					pazientiSet.m_sTelefono2 = m_sTelefono2;
					pazientiSet.m_sCellulare1 = m_sCellulare1;
					pazientiSet.m_sCellulare2 = m_sCellulare2;
					pazientiSet.m_sCodFisc = m_sCodiceFiscale; //
					pazientiSet.m_sCodSanit = m_sCodiceSanitario; //
					pazientiSet.m_sUlssResidenza = m_sUlssResidenza;
					pazientiSet.m_lSessoPaz = m_lSesso;

					if (!IsFieldNull(&m_sMedicoCurante) && m_sMedicoCurante.Trim() != "")
						pazientiSet.m_sMedicoCurante = m_sMedicoCurante;
					else
						pazientiSet.m_sMedicoCurante = m_sDescrizioneMedicoCuranteEst;
					/*if (!IsFieldNull(&m_sCittadinanza) && m_sCittadinanza.Trim() != "")
					pazientiSet.m_sNazionalita = m_sCittadinanza;
					else*/
					pazientiSet.m_sNazionalita = m_sDescrizioneCittadinanzaEst;

					pazientiSet.m_lStatoAPC = 3;

					pazientiSet.m_bCertificazioneMEF = m_bCertificazioneMEF;
					pazientiSet.m_bCertificazioneSISS = m_bCertificazioneSISS;

					pazientiSet.m_sCodiceSTP = m_sCodiceSTP;
					pazientiSet.m_sCodiceIstAssicurativa = m_sCodiceIstAssicurativa;
					pazientiSet.m_sCodiceTEAM = m_sCodiceTEAM;

					
					pazientiSet.m_sIdentificazionePassaporto = m_sIdentificazionePassaporto;	//Julio - BUG 3285 - Adequação de laudos
					pazientiSet.m_sIdentificazioneDoc1 = m_sIdentificazioneDoc1;				//Julio - BUG 3285 - Adequação de laudos
					pazientiSet.m_sIdentificazioneDoc2 = m_sIdentificazioneDoc2;				//Julio - BUG 3285 - Adequação de laudos

					if (pazientiSet.UpdateRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
					{
						lCurPazCode = pazientiSet.GetLastAdd();
						CExtPatientEventSet().AddEvent(lCurPazCode, acquirePatient);
					}
					else
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
						//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
						return FALSE;
					}
				}
				else
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
					//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
					return FALSE;
				}
			}
			else
			{
				//2 possibilità di averlo trovato: 1-assiden 2-ibrida
				//Paziente c'è. 
				if (theApp.m_bAssidenKey)
				{
					if (pazientiSet.EditRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
					{
						lCurPazCode = pazientiSet.m_lContatore;

						if (!IsFieldNull(&m_sCognome) && m_sCognome.Trim() != "")
							pazientiSet.m_sCognome = m_sCognome.Trim();
						if (!IsFieldNull(&m_sCognome2) && m_sCognome2.Trim() != "")
							pazientiSet.m_sCognome2 = m_sCognome2.Trim();
						if (!IsFieldNull(&m_sNome) && m_sNome.Trim() != "")
							pazientiSet.m_sNome = m_sNome.Trim();
						if (!IsFieldNull(&m_lDataNascitaCustom) && m_lDataNascitaCustom > 0)
							pazientiSet.m_lNatoIlCustom = m_lDataNascitaCustom;
						if (!IsFieldNull(&m_lISTATNascita) && m_lISTATNascita > 0)
							pazientiSet.m_lIDComuneNascita = m_lISTATNascita;
						if (!IsFieldNull(&m_sComuneNascita) && m_sComuneNascita.Trim() != "")
							pazientiSet.m_sNatoA = m_sComuneNascita.Trim();
						else
							if (!IsFieldNull(&m_sDescrizioneComuneNascitaEst) && m_sDescrizioneComuneNascitaEst.Trim() != "")
								pazientiSet.m_sNatoA = m_sDescrizioneComuneNascitaEst.Trim();
						if (!IsFieldNull(&m_sIndirizzoResidenza) && m_sIndirizzoResidenza.Trim() != "")
							pazientiSet.m_sVia = m_sIndirizzoResidenza.Trim();
						if (!IsFieldNull(&m_lISTATResidenza) && m_lISTATResidenza > 0)
							pazientiSet.m_lIDComune = m_lISTATResidenza;
						if (!IsFieldNull(&m_sComuneResidenza) && m_sComuneResidenza.Trim() != "")
						{
							pazientiSet.m_sCitta = m_sComuneResidenza.Trim();
							pazientiSet.m_sProvincia = m_sProvincia.Trim();
						}
						else
						{
							if (!IsFieldNull(&m_sDescrizioneComuneResidenzaEst) && m_sDescrizioneComuneResidenzaEst.Trim() != "")
							{
								pazientiSet.m_sCitta = m_sDescrizioneComuneResidenzaEst.Trim();
								pazientiSet.m_sProvincia = m_sProvinciaEst.Trim();
							}
						}
						if (!IsFieldNull(&m_sCapResidenza) && m_sCapResidenza.Trim() != "")
							pazientiSet.m_sCAP = m_sCapResidenza.Trim();
						if (!IsFieldNull(&m_sTelefono1) && m_sTelefono1.Trim() != "")
							pazientiSet.m_sTelefono1 = m_sTelefono1.Trim();
						if (!IsFieldNull(&m_sTelefono2) && m_sTelefono2.Trim() != "")
							pazientiSet.m_sTelefono2 = m_sTelefono2.Trim();
						if (!IsFieldNull(&m_sCellulare1) && m_sCellulare1.Trim() != "")
							pazientiSet.m_sCellulare1 = m_sCellulare1.Trim();
						if (!IsFieldNull(&m_sCellulare2) && m_sCellulare2.Trim() != "")
							pazientiSet.m_sCellulare2 = m_sCellulare2.Trim();
						if (!IsFieldNull(&m_sCodiceFiscale) && m_sCodiceFiscale.Trim() != "")
							pazientiSet.m_sCodFisc = m_sCodiceFiscale.Trim(); //
						if (!IsFieldNull(&m_sCodiceSanitario) && m_sCodiceSanitario.Trim() != "")
							pazientiSet.m_sCodSanit = m_sCodiceSanitario.Trim(); //
						if (!IsFieldNull(&m_sUlssResidenza) && m_sUlssResidenza.Trim() != "")
							pazientiSet.m_sUlssResidenza = m_sUlssResidenza.Trim();
						if (!IsFieldNull(&m_lSesso) && m_lSesso >= -1)
							pazientiSet.m_lSessoPaz = m_lSesso;

						if (!IsFieldNull(&m_sMedicoCurante) && m_sMedicoCurante.Trim() != "")
							pazientiSet.m_sMedicoCurante = m_sMedicoCurante.Trim();
						else
							if (!IsFieldNull(&m_sDescrizioneMedicoCuranteEst) && m_sDescrizioneMedicoCuranteEst.Trim() != "")
								pazientiSet.m_sMedicoCurante = m_sDescrizioneMedicoCuranteEst.Trim();

						if (!IsFieldNull(&m_sDescrizioneCittadinanzaEst) && m_sDescrizioneCittadinanzaEst.Trim() != "")
							pazientiSet.m_sNazionalita = m_sDescrizioneCittadinanzaEst.Trim();

						//Con assiden key se il paziente ce l'ho già lo segno come utilizzato
						pazientiSet.m_lStatoAPC = 4;

						if (!IsFieldNull(&m_bCertificazioneMEF))
							pazientiSet.m_bCertificazioneMEF = m_bCertificazioneMEF;
						if (!IsFieldNull(&m_bCertificazioneSISS))
							pazientiSet.m_bCertificazioneSISS = m_bCertificazioneSISS;

						if (!IsFieldNull(&m_sCodiceSTP) && m_sCodiceSTP.Trim() != "")
							pazientiSet.m_sCodiceSTP = m_sCodiceSTP.Trim();
						if (!IsFieldNull(&m_sCodiceIstAssicurativa) && m_sCodiceIstAssicurativa.Trim() != "")
							pazientiSet.m_sCodiceIstAssicurativa = m_sCodiceIstAssicurativa.Trim();
						if (!IsFieldNull(&m_sCodiceTEAM) && m_sCodiceTEAM.Trim() != "")
							pazientiSet.m_sCodiceTEAM = m_sCodiceTEAM.Trim();

						//Julio - BUG 3285 - Adequação de laudos
						if (!IsFieldNull(&m_sIdentificazionePassaporto) && m_sIdentificazionePassaporto.Trim() != "")
							  pazientiSet.m_sIdentificazionePassaporto = m_sIdentificazionePassaporto.Trim();

						//Julio - BUG 3285 - Adequação de laudos
						if (!IsFieldNull(&m_sIdentificazioneDoc1) && m_sIdentificazioneDoc1.Trim() != "")
							  pazientiSet.m_sIdentificazioneDoc1 = m_sIdentificazioneDoc1.Trim();

						//Julio - BUG 3285 - Adequação de laudos
						if (!IsFieldNull(&m_sIdentificazioneDoc2) && m_sIdentificazioneDoc2.Trim() != "")
							  pazientiSet.m_sIdentificazioneDoc2 = m_sIdentificazioneDoc2.Trim();




						if (!pazientiSet.UpdateRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
							//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
							return FALSE;
						}

						CExtPatientEventSet().AddEvent(lCurPazCode, usePatient);
					}
					else
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
						//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
						return FALSE;
					}
				}
				else
				{
					//Mostro una lista dei pazienti trovati in modo da poter decidere a quale di questi abbinare l'esame o se inserirne uno nuovo
					CQueryDlg queryDlg(m_pEsamiView, TRUE, "", TRUE, FALSE, FALSE);
					CPazientiSet *pazientiViewSet = new CPazientiSet();
					pazientiViewSet->SetOpenFilter(filter);
					pazientiViewSet->SetSortRecord("Cognome, Nome, NatoIlCustom");
					pazientiViewSet->OpenRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");

					//Ho usato lo stesso filtro che mi ha portato a !IsEof(). Se trovo IsEOF(), quindi, c'è qualcosa che non va
					if (pazientiViewSet->IsEOF())
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
						//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
						return FALSE;
					}

					queryDlg.m_lRelazione = SOLO_PAZIENTI;
					queryDlg.m_strPazFilter = filter;
					queryDlg.m_strEsameFrom = "";
					queryDlg.m_strEsameWhere = "";
					queryDlg.m_pPazientiSet = pazientiViewSet;
					queryDlg.m_pJoinEsamiSet = NULL;
					queryDlg.m_bCercaPaziente = TRUE;

					//Se ho premuto ESC non faccio nulla
					if (queryDlg.DoModal() == IDCANCEL)
						return FALSE;

					if (queryDlg.m_bAddNew)
					{
						// non c'è --> devo inserirlo //

						if (pazientiSet.AddNewRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
						{
							//Associazione campi
							pazientiSet.m_sAssIden = m_sAssiden;
							pazientiSet.m_sCognome = m_sCognome;
							pazientiSet.m_sCognome2 = m_sCognome2;
							pazientiSet.m_sNome = m_sNome;
							pazientiSet.m_lNatoIlCustom = m_lDataNascitaCustom;
							pazientiSet.m_lIDComuneNascita = m_lISTATNascita;
							if (!IsFieldNull(&m_sComuneNascita) && m_sComuneNascita.Trim() != "")
								pazientiSet.m_sNatoA = m_sComuneNascita;
							else
								pazientiSet.m_sNatoA = m_sDescrizioneComuneNascitaEst;
							pazientiSet.m_sVia = m_sIndirizzoResidenza;
							pazientiSet.m_lIDComune = m_lISTATResidenza;
							if (!IsFieldNull(&m_sComuneResidenza) && m_sComuneResidenza.Trim() != "")
							{
								pazientiSet.m_sCitta = m_sComuneResidenza;
								pazientiSet.m_sProvincia = m_sProvincia;
							}
							else
							{
								pazientiSet.m_sCitta = m_sDescrizioneComuneResidenzaEst;
								pazientiSet.m_sProvincia = m_sProvinciaEst;
							}
							pazientiSet.m_sCAP = m_sCapResidenza;
							pazientiSet.m_sTelefono1 = m_sTelefono1;
							pazientiSet.m_sTelefono2 = m_sTelefono2;
							pazientiSet.m_sCellulare1 = m_sCellulare1;
							pazientiSet.m_sCellulare2 = m_sCellulare2;
							pazientiSet.m_sCodFisc = m_sCodiceFiscale; //
							pazientiSet.m_sCodSanit = m_sCodiceSanitario; //
							pazientiSet.m_sUlssResidenza = m_sUlssResidenza;
							pazientiSet.m_lSessoPaz = m_lSesso;

							if (!IsFieldNull(&m_sMedicoCurante) && m_sMedicoCurante.Trim() != "")
								pazientiSet.m_sMedicoCurante = m_sMedicoCurante;
							else
								pazientiSet.m_sMedicoCurante = m_sDescrizioneMedicoCuranteEst;
							/*if (!IsFieldNull(&m_sCittadinanza) && m_sCittadinanza.Trim() != "")
							pazientiSet.m_sNazionalita = m_sCittadinanza;
							else*/
							pazientiSet.m_sNazionalita = m_sDescrizioneCittadinanzaEst;

							pazientiSet.m_lStatoAPC = 3;

							pazientiSet.m_bCertificazioneMEF = m_bCertificazioneMEF;
							pazientiSet.m_bCertificazioneSISS = m_bCertificazioneSISS;

							pazientiSet.m_sCodiceSTP = m_sCodiceSTP;
							pazientiSet.m_sCodiceIstAssicurativa = m_sCodiceIstAssicurativa;
							pazientiSet.m_sCodiceTEAM = m_sCodiceTEAM;
							
							pazientiSet.m_sIdentificazionePassaporto = m_sIdentificazionePassaporto;	//Julio - BUG 3285 - Adequação de laudos
							pazientiSet.m_sIdentificazioneDoc1 = m_sIdentificazioneDoc1;				//Julio - BUG 3285 - Adequação de laudos
							pazientiSet.m_sIdentificazioneDoc2 = m_sIdentificazioneDoc2;				//Julio - BUG 3285 - Adequação de laudos


							if (pazientiSet.UpdateRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
							{
								lCurPazCode = pazientiSet.GetLastAdd();
								CExtPatientEventSet().AddEvent(lCurPazCode, acquirePatient);
							}
							else
							{
								theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
								//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
								return FALSE;
							}
						}
						else
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
							//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
							return FALSE;
						}
					}
					else
					{
						lCurPazCode = queryDlg.m_lCurrentPri;

						pazientiSet.MoveFirst();
						while (!pazientiSet.IsEOF())
						{
							if (pazientiSet.m_lContatore == lCurPazCode)
							{
								if (pazientiSet.EditRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
								{
									pazientiSet.m_sAssIden = m_sAssiden;
									if (!IsFieldNull(&m_sCognome) && m_sCognome.Trim() != "")
										pazientiSet.m_sCognome = m_sCognome.Trim();
									if (!IsFieldNull(&m_sCognome2) && m_sCognome2.Trim() != "")
										pazientiSet.m_sCognome2 = m_sCognome2.Trim();
									if (!IsFieldNull(&m_sNome) && m_sNome.Trim() != "")
										pazientiSet.m_sNome = m_sNome.Trim();
									if (!IsFieldNull(&m_lDataNascitaCustom) && m_lDataNascitaCustom > 0)
										pazientiSet.m_lNatoIlCustom = m_lDataNascitaCustom;
									if (!IsFieldNull(&m_lISTATNascita) && m_lISTATNascita > 0)
										pazientiSet.m_lIDComuneNascita = m_lISTATNascita;
									if (!IsFieldNull(&m_sComuneNascita) && m_sComuneNascita.Trim() != "")
										pazientiSet.m_sNatoA = m_sComuneNascita.Trim();
									else
										if (!IsFieldNull(&m_sDescrizioneComuneNascitaEst) && m_sDescrizioneComuneNascitaEst.Trim() != "")
											pazientiSet.m_sNatoA = m_sDescrizioneComuneNascitaEst.Trim();
									if (!IsFieldNull(&m_sIndirizzoResidenza) && m_sIndirizzoResidenza.Trim() != "")
										pazientiSet.m_sVia = m_sIndirizzoResidenza.Trim();
									if (!IsFieldNull(&m_lISTATResidenza) && m_lISTATResidenza > 0)
										pazientiSet.m_lIDComune = m_lISTATResidenza;
									if (!IsFieldNull(&m_sComuneResidenza) && m_sComuneResidenza.Trim() != "")
									{
										pazientiSet.m_sCitta = m_sComuneResidenza.Trim();
										pazientiSet.m_sProvincia = m_sProvincia.Trim();
									}
									else
									{
										if (!IsFieldNull(&m_sDescrizioneComuneResidenzaEst) && m_sDescrizioneComuneResidenzaEst.Trim() != "")
										{
											pazientiSet.m_sCitta = m_sDescrizioneComuneResidenzaEst.Trim();
											pazientiSet.m_sProvincia = m_sProvinciaEst.Trim();
										}
									}
									if (!IsFieldNull(&m_sCapResidenza) && m_sCapResidenza.Trim() != "")
										pazientiSet.m_sCAP = m_sCapResidenza.Trim();
									if (!IsFieldNull(&m_sTelefono1) && m_sTelefono1.Trim() != "")
										pazientiSet.m_sTelefono1 = m_sTelefono1.Trim();
									if (!IsFieldNull(&m_sTelefono2) && m_sTelefono2.Trim() != "")
										pazientiSet.m_sTelefono2 = m_sTelefono2.Trim();
									if (!IsFieldNull(&m_sCellulare1) && m_sCellulare1.Trim() != "")
										pazientiSet.m_sCellulare1 = m_sCellulare1.Trim();
									if (!IsFieldNull(&m_sCellulare2) && m_sCellulare2.Trim() != "")
										pazientiSet.m_sCellulare2 = m_sCellulare2.Trim();
									if (!IsFieldNull(&m_sCodiceFiscale) && m_sCodiceFiscale.Trim() != "")
										pazientiSet.m_sCodFisc = m_sCodiceFiscale.Trim(); //
									if (!IsFieldNull(&m_sCodiceSanitario) && m_sCodiceSanitario.Trim() != "")
										pazientiSet.m_sCodSanit = m_sCodiceSanitario.Trim(); //
									if (!IsFieldNull(&m_sUlssResidenza) && m_sUlssResidenza.Trim() != "")
										pazientiSet.m_sUlssResidenza = m_sUlssResidenza.Trim();
									if (!IsFieldNull(&m_lSesso) && m_lSesso >= -1)
										pazientiSet.m_lSessoPaz = m_lSesso;

									if (!IsFieldNull(&m_sMedicoCurante) && m_sMedicoCurante.Trim() != "")
										pazientiSet.m_sMedicoCurante = m_sMedicoCurante.Trim();
									else
										if (!IsFieldNull(&m_sDescrizioneMedicoCuranteEst) && m_sDescrizioneMedicoCuranteEst.Trim() != "")
											pazientiSet.m_sMedicoCurante = m_sDescrizioneMedicoCuranteEst.Trim();

									if (!IsFieldNull(&m_sDescrizioneCittadinanzaEst) && m_sDescrizioneCittadinanzaEst.Trim() != "")
										pazientiSet.m_sNazionalita = m_sDescrizioneCittadinanzaEst.Trim();

									//Con assiden key se il paziente ce l'ho già lo segno come utilizzato
									pazientiSet.m_lStatoAPC = 4;

									if (!IsFieldNull(&m_bCertificazioneMEF))
										pazientiSet.m_bCertificazioneMEF = m_bCertificazioneMEF;
									if (!IsFieldNull(&m_bCertificazioneSISS))
										pazientiSet.m_bCertificazioneSISS = m_bCertificazioneSISS;

									if (!IsFieldNull(&m_sCodiceTEAM) && m_sCodiceTEAM.Trim() != "")
										pazientiSet.m_sCodiceSTP = m_sCodiceSTP.Trim();
									if (!IsFieldNull(&m_sCodiceIstAssicurativa) && m_sCodiceIstAssicurativa.Trim() != "")
										pazientiSet.m_sCodiceIstAssicurativa = m_sCodiceIstAssicurativa.Trim();
									if (!IsFieldNull(&m_sCodiceTEAM) && m_sCodiceTEAM.Trim() != "")
										pazientiSet.m_sCodiceTEAM = m_sCodiceTEAM.Trim();

									//Julio - BUG 3285 - Adequação de laudos
									if (!IsFieldNull(&m_sIdentificazionePassaporto) && m_sIdentificazionePassaporto.Trim() != "")
									      pazientiSet.m_sIdentificazionePassaporto =   m_sIdentificazionePassaporto.Trim();
									//Julio - BUG 3285 - Adequação de laudos
									if (!IsFieldNull(&m_sIdentificazioneDoc1) && m_sIdentificazioneDoc1.Trim() != "")
										  pazientiSet.m_sIdentificazioneDoc1 =   m_sIdentificazioneDoc1.Trim();
									//Julio - BUG 3285 - Adequação de laudos
									if (!IsFieldNull(&m_sIdentificazioneDoc2) && m_sIdentificazioneDoc2.Trim() != "")
										  pazientiSet.m_sIdentificazioneDoc2 =   m_sIdentificazioneDoc2.Trim();


									if (!pazientiSet.UpdateRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
									{
										theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
										CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
										return FALSE;
									}

									CExtPatientEventSet().AddEvent(lCurPazCode, usePatient);
								}
								else
								{
									theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
									//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
									return FALSE;
								}
								break;
							}

							pazientiSet.MoveNext();
						}
					}

					pazientiViewSet->CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");

					if (lCurPazCode == 0)
						return FALSE;
				}

			}

			if (!pazientiSet.CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
				//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
				return FALSE;
			}
		}

		//A causa dei recenti presunti problemi da Battaglia, viene controllato di essere posizionati sul giusto paziente
		if (lCurPazCode <= 0)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
			//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
			return FALSE;
		}

		CPazientiSet tempPazSet;
		CString filterPaziente;
		filterPaziente.Format("contatore = %li", lCurPazCode);
		tempPazSet.SetOpenFilter(filterPaziente);
		if (tempPazSet.OpenRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
		{
			if (tempPazSet.IsEOF())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
				//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
				return FALSE;
			}
			else
			{
				if (tempPazSet.m_sAssIden != m_sAssiden || tempPazSet.m_sCognome != m_sCognome || tempPazSet.m_sNome != m_sNome)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
					//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
					return FALSE;
				}
			}

			if (!tempPazSet.CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente"))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
				//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
				return FALSE;
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DBCONN_ERR));
			//CloseRecordset("CCupWorkListManager::SelectEntryFaseImportazionePaziente");
			return FALSE;
		}
	}
	catch (CDBException* pEx)
	{
		theApp.AfxMessageBoxEndo("Fase paziente unattended error");
		pEx->ReportError();
		pEx->Delete();
		return FALSE;
	}
	catch (CMemoryException* pEx)
	{
		theApp.AfxMessageBoxEndo("Fase paziente unattended error");
		pEx->ReportError();
		pEx->Delete();
		return FALSE;
	}
	catch (...)
	{
		theApp.AfxMessageBoxEndo("Fase paziente unattended error");
		return FALSE;
	}

	return bReturn;
}

