#include "stdafx.h"
#include "Endox.h"
#include "DMSWorkListManager.h"

#include "CustomDate.h"
#include "ListaPrestazioniCupSet.h"
#include "ExamListDlg.h"
#include "EsamiSet.h"
#include "ExtMinPazDataSetSet.h"
#include "PazientiSet.h"
#include "PrenotazioneAccettataSP.h"
#include "QueryDlg.h"
#include "RegioneSet.h"
#include "SediEsameSet.h"
#include "TipoEsameNew.h"
#include "VistaExtPrestazioniSet.h"
#include "VistaEsamiPerWLSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDMSWorkListManager, CBaseSet)

CDMSWorkListManager::CDMSWorkListManager(CEsamiView* pEsamiView)
	: CBaseSet(NULL, "VIEW")
{
	SetSortRecord("DATAESAME, COGNOME, NOME");

	m_pEsamiView = pEsamiView;

	m_ImageList.Create(16, 16, ILC_COLOR16, 2, 2);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_LISTA_PREN_NO));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_LISTA_PREN_NI));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_LISTA_PREN_SI));

	m_nFields = 52;
}

CDMSWorkListManager::~CDMSWorkListManager()
{
}

CString CDMSWorkListManager::GetDefaultSQL()
{
	return "VISTA_EXT_ORDINI_DMS";
}

void CDMSWorkListManager::PrepareList(CListCtrlLocalize* pList)
{
	pList->SetExtendedStyle(pList->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pList->SetImageList(&m_ImageList, LVSIL_SMALL);

	pList->InsertColumn(0, "",					LVCFMT_LEFT, 23);
	pList->InsertColumn(1, "Codice vetrino",	LVCFMT_LEFT, 100);
	pList->InsertColumn(2, "Posizione",			LVCFMT_LEFT, 100);
	pList->InsertColumn(3, "Codice prelievo",	LVCFMT_LEFT, 100);
	pList->InsertColumn(4, "Paziente",			LVCFMT_LEFT, 100);
	pList->InsertColumn(5, "Data nascita",		LVCFMT_LEFT, 100);
	pList->InsertColumn(6, "",					LVCFMT_LEFT, 0);
}

BOOL CDMSWorkListManager::FillList(CListCtrlLocalize* pList, CString sCodVet)
{
	pList->DeleteAllItems();

	sCodVet.Replace("'", "''");
	if (sCodVet.IsEmpty())
		SetOpenFilter("trasferito=0");
	else
		SetOpenFilter("trasferito=0 AND CodiceVetrino LIKE '" + sCodVet + "%'");

	// SetSortRecord("CodiceVetrino, PosizioneVetrino, ID");
	
	if (!OpenRecordset("CCupWorkList::RiempiLista"))
		return FALSE;
	
	CString strTmp;
	while (!IsEOF())
	{
		int iItemInserted = -1;
		CString strAvvisi = "";

		//Se all'ordine non corrisponde nessuna prestazione: pallino rosso e message box se si vuole selezionare a mano il tipo esame
		//Se non tutti i dati sono stati transcodificati: pallino giallo
		//Altrimenti presenta un pallino verde
		CVistaExtPrestazioniSet extPrestazioniSet;
		CString strFilter;
		strFilter.Format("idOrdine = %li AND TipoEsame IS NOT NULL", m_lId);
		extPrestazioniSet.SetOpenFilter(strFilter);
		if (extPrestazioniSet.OpenRecordset("CCupWorkList::RiempiLista"))
		{
			CString strEsame;
			if (extPrestazioniSet.IsEOF() || (theApp.m_bAssidenKey && (IsFieldNull(&m_sAssiden) || m_sAssiden == "")) || (!theApp.m_bAssidenKey && !CampiObbligatoriValorizzati(this)))
			{
				iItemInserted = pList->InsertItem(pList->GetItemCount(), "", 0);
				pList->SetItemData(iItemInserted, -1 * m_lId);

				if (extPrestazioniSet.IsEOF())
					strEsame = "";
				else
					if (theApp.m_bMostraCodiceEsame)
						strEsame = extPrestazioniSet.m_sSiglaTipoEsame;
					else
						strEsame = extPrestazioniSet.m_sTipoEsame;
			}
			else
			{
				if (((!IsFieldNull(&m_sProvenienza) && m_sProvenienza != "") && IsFieldNull(&m_lProvenienzaEndox)) || 
				((!IsFieldNull(&m_sCodiceSalaEsame) && m_sCodiceSalaEsame != "") && IsFieldNull(&m_lIdSalaEndox)) || 
				((!IsFieldNull(&m_sCodiceRepartoInviante) && m_sCodiceRepartoInviante != "") && IsFieldNull(&m_lIdRepartoEndox)) || 
				((!IsFieldNull(&m_sCodiceCittadinanza) && m_sCodiceCittadinanza != "") && (IsFieldNull(&m_sCittadinanza) || m_sCittadinanza == "")) ||
				((!IsFieldNull(&m_lISTATResidenza) && m_lISTATResidenza != 0) && (IsFieldNull(&m_sComuneResidenza) || m_sComuneResidenza == "")) ||
				((!IsFieldNull(&m_lISTATNascita) && m_lISTATNascita != 0) && (IsFieldNull(&m_sComuneNascita) || m_sComuneNascita == "")))
				{
					iItemInserted = pList->InsertItem(pList->GetItemCount(), "", 1);
				}
				else
					iItemInserted = pList->InsertItem(pList->GetItemCount(), "", 2);

				if (theApp.m_bMostraCodiceEsame)
					strEsame = extPrestazioniSet.m_sSiglaTipoEsame;
				else
					strEsame = extPrestazioniSet.m_sTipoEsame;
			
				pList->SetItemData(iItemInserted, m_lId);
			}
		
			extPrestazioniSet.CloseRecordset("CCupWorkList::RiempiLista");

			pList->SetItemText(iItemInserted, 1, m_sCodiceVetrino);
			pList->SetItemText(iItemInserted, 2, m_sPosizioneVetrino);

			pList->SetItemText(iItemInserted, 3, m_sAssiden);

			strTmp.Format("%s %s", m_sCognome, m_sNome);
			pList->SetItemText(iItemInserted, 4, strTmp);
			pList->SetItemText(iItemInserted, 5, m_sDataNascita.Right(2) + "/" + m_sDataNascita.Mid(4,2) + "/" + m_sDataNascita.Left(4));
		}

		MoveNext();
	}

	pList->SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	pList->SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	pList->SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	pList->SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	pList->SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);

	CloseRecordset("CDMSWorkListManager::RiempiLista");
	return TRUE;
}

void CDMSWorkListManager::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Id", m_lId);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "orderNumber",		    m_sOrderNumber,				50);
		RFX_Text(pFX, "DataEsame",				m_sDataEsame,				14);
		RFX_Text(pFX, "Provenienza",			m_sProvenienza,				50);
		RFX_Text(pFX, "CodiceSalaEsame",		m_sCodiceSalaEsame,			50);
		RFX_Text(pFX, "Note",					m_sNote,					1000);
		RFX_Text(pFX, "CodiceRepartoInviante",	m_sCodiceRepartoInviante,	50);
		RFX_Text(pFX, "CodiceMedicoInviante",	m_sCodiceMedicoInviante,	255);
		RFX_Text(pFX, "Nosologico",				m_sNosologico,				50);
		RFX_Text(pFX, "Urgenza",				m_sUrgenza,					50);
		RFX_Long(pFX, "IDEsameIns",				m_lIDEsameIns);
		RFX_Bool(pFX, "Trasferito",				m_bTrasferito);
		RFX_Text(pFX, "idProvetta",				m_sIdProvetta,				50);
		RFX_Bool(pFX, "AcqSegnalata",			m_bAcqSegnalata);
		RFX_Bool(pFX, "AppuntamentoSegnalato",	m_bAppuntamentoSegnalato);
		RFX_Bool(pFX, "Eliminato",				m_bEliminato);
		RFX_Text(pFX, "Assiden",				m_sAssiden,					50);
		RFX_Text(pFX, "Cognome",				m_sCognome,					50);
		RFX_Text(pFX, "Cognome2",				m_sCognome2,				50);
		RFX_Text(pFX, "Nome",					m_sNome,					50);
		RFX_Text(pFX, "DataNascita",			m_sDataNascita,				14);
		RFX_Long(pFX, "ISTATNascita",			m_lISTATNascita);
		RFX_Text(pFX, "IndirizzoResidenza",		m_sIndirizzoResidenza,	  255);
		RFX_Long(pFX, "ISTATResidenza",			m_lISTATResidenza);
		RFX_Text(pFX, "CAPResidenza",			m_sCapResidenza,		   5);
		RFX_Text(pFX, "Telefono1",				m_sTelefono1,			  50);
		RFX_Text(pFX, "Telefono2",				m_sTelefono2,			  50);
		RFX_Text(pFX, "Cellulare1",				m_sCellulare1,			  50);
		RFX_Text(pFX, "Cellulare2",				m_sCellulare2,			  50);
		RFX_Text(pFX, "CodiceFiscale",			m_sCodiceFiscale,		  16); //
		RFX_Text(pFX, "CodiceSanitario",		m_sCodiceSanitario,		  50); //
		RFX_Long(pFX, "Sesso",					m_lSesso);
		RFX_Long(pFX, "asl",					m_lAsl);
		RFX_Text(pFX, "CodiceMedicoCurante",	m_sCodiceMedicoCurante,		50);
		RFX_Text(pFX, "CodiceCittadinanza",		m_sCodiceCittadinanza,		50);
		RFX_Long(pFX, "IdProvenienzaEndox",		m_lProvenienzaEndox);
		RFX_Long(pFX, "IdSalaEndox",			m_lIdSalaEndox);
		RFX_Long(pFX, "IdSedeEndox",			m_lIdSedeEndox);
		RFX_Long(pFX, "IdRepartoEndox",			m_lIdRepartoEndox);
		RFX_Long(pFX, "IdEndoxMedicoInviante",	m_lIDEndoxMedicoInviante);
		RFX_Text(pFX, "Cittadinanza",			m_sCittadinanza,			50);
		RFX_Long(pFX, "IDEndoxMedicoCurante",	m_lIDEndoxMedicoCurante);
		RFX_Text(pFX, "MedicoInviante",			m_sMedicoInviante,			50);
		RFX_Text(pFX, "MedicoCurante",			m_sMedicoCurante,			50);
		RFX_Text(pFX, "DescrizioneSala",		m_sDescrizioneSala,			50); //
		RFX_Text(pFX, "DescrizioneSede",		m_sDescrizioneSede,			50); //
		RFX_Text(pFX, "ComuneNascita",			m_sComuneNascita,			50);
		RFX_Text(pFX, "ComuneResidenza",		m_sComuneResidenza,			50);
		RFX_Long(pFX, "DataNascitaCustom",		m_lDataNascitaCustom);
		//RFX_Long(pFX, "IdUrgenzaEndox",			m_lIdUrgenzaEndox);
		RFX_Text(pFX, "DescrizioneReparto",		m_sDescrizioneReparto,		50);
		RFX_Text(pFX, "CodiceVetrino",			m_sCodiceVetrino,			4000);
		RFX_Text(pFX, "PosizioneVetrino",		m_sPosizioneVetrino,		4000);
	}
}

BOOL CDMSWorkListManager::SelectEntry(CListCtrlLocalize* pList, int iItem, CString dataSelezionata)
{
	int element = pList->GetItemData(iItem);

	int idTipoEsameTemp = -1;

	//Se l'id è negativo significa che la prenotazione non è importabile automaticamente (pallino rosso)
	if (element < 0)
	{
		CString strFilter;
		strFilter.Format("id = %li", element * -1);
		SetOpenFilter(strFilter);
	
		if (!OpenRecordset("CCupWorkList::SelectEntry"))
			return FALSE;
	
		if (IsBOF() && IsEOF())
		{
			CloseRecordset("CCupWorkList::SelectEntry");
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PRENOTAZIONE_NOTFOUND));
			return FALSE;
		}

		CString strTmp;
		if (!IsEOF())
		{
			if (theApp.m_bAssidenKey && (IsFieldNull(&m_sAssiden) || m_sAssiden == ""))
			{
				CloseRecordset("CCupWorkList::SelectEntry");
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERRPREN_ID_NOTFOUND));
				return FALSE;
			}

			if (!theApp.m_bAssidenKey && !CampiObbligatoriValorizzati(this))
			{
				CloseRecordset("CCupWorkList::SelectEntry");
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERRPREN_SET_NOTFOUND));
				return FALSE;
			}

			//Se l'assiden invece c'è, per forza siamo nel secondo caso dove manca la definizione del tipo esame
			CloseRecordset("CCupWorkList::SelectEntry");
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TIPOESAME_NOTDEF), MB_YESNO) == IDYES)
			{
				CTipoEsameNewDlg dlg(m_pEsamiView, m_pEsamiView, FALSE, TRUE, 0);
				if (dlg.DoModal() == IDOK)
					idTipoEsameTemp = dlg.GetTipoEsame();
				else
					return FALSE;
			}
			else
				return FALSE;

		}
	}

	//
	CString strFilter;
	strFilter.Format("id = %li", element);
	SetOpenFilter(strFilter);
	
	if (!OpenRecordset("CDMSWorkListManager::SelectEntry"))
		return FALSE;	

	//Bisogna controllare che il paziente non sia già inserito ed eventualmente inserirlo, successivamente bisogna inserire l'esame, i suoi dettagli e le prestazioni associate
	CPazientiSet pazientiSet;
	CString filter;

	if (theApp.m_bAssidenKey)
		filter.Format("assiden = '%s'", m_sAssiden); // assiden = '%s' and eliminato = 0 // Sandro: l'eliminato non serve perchè c'è già di base nel recordset pazienti //
	else
		CostruisciFiltroPaziente(&filter, this);

	pazientiSet.SetOpenFilter(filter);

	long lCurPazCode = -1;

	if (pazientiSet.OpenRecordset("CDMSWorkListManager::SelectEntry"))
	{
		if (pazientiSet.IsEOF())
		{
			if (pazientiSet.AddNewRecordset("CDMSWorkListManager::SelectEntry"))
			{
				//Associazione campi
				pazientiSet.m_sAssIden = m_sAssiden;
				pazientiSet.m_sCognome = m_sCognome;
				pazientiSet.m_sNome = m_sNome;
				pazientiSet.m_lNatoIlCustom = m_lDataNascitaCustom;
				pazientiSet.m_sNatoA = m_sComuneNascita;
				pazientiSet.m_lIDComuneNascita = m_lISTATNascita;
				pazientiSet.m_sVia = m_sIndirizzoResidenza;
				pazientiSet.m_sCitta = m_sComuneResidenza;
				pazientiSet.m_lIDComune = m_lISTATResidenza;
				pazientiSet.m_sCAP = m_sCapResidenza;
				pazientiSet.m_sTelefono1 = m_sTelefono1;
				pazientiSet.m_sTelefono2 = m_sTelefono2;
				pazientiSet.m_sCellulare1 = m_sCellulare1;
				pazientiSet.m_sCellulare2 = m_sCellulare2;
				pazientiSet.m_sCodFisc = m_sCodiceFiscale; //
				pazientiSet.m_sCodSanit = m_sCodiceSanitario; //
				pazientiSet.m_sUlssResidenza.Format("%li", m_lAsl);
				pazientiSet.m_lSessoPaz = m_lSesso;
					
				//Cerco di transcodificare i dati, altrimenti scrivo direttamente il codice
				CString medicoCurante = "", cittadinanza = "";
				if (!IsFieldNull(&m_sMedicoCurante) && m_sMedicoCurante.Trim() != "")
					pazientiSet.m_sMedicoCurante = m_sMedicoCurante;
				else
					pazientiSet.m_sMedicoCurante = m_sCodiceMedicoCurante;
				if (!IsFieldNull(&m_sCittadinanza) && m_sCittadinanza.Trim() != "")
					pazientiSet.m_sNazionalita = m_sCittadinanza;
				else
					pazientiSet.m_sNazionalita = m_sCodiceCittadinanza;
					
				if (pazientiSet.UpdateRecordset("CDMSWorkListManager::SelectEntry"))
					lCurPazCode = pazientiSet.GetLastAdd();
			}
		}
		else
		{
			if (pazientiSet.GetRecordCount() == 1)
				lCurPazCode = pazientiSet.m_lContatore;
			else
			{
				CQueryDlg queryDlg(m_pEsamiView, FALSE, "", TRUE, TRUE);
				CPazientiSet *pazientiViewSet = new CPazientiSet();
				pazientiViewSet->SetOpenFilter(filter);
				pazientiViewSet->SetSortRecord("Cognome, Nome, NatoIlCustom");
				pazientiViewSet->OpenRecordset("CDMSWorkListManager::SelectEntry");

				if (pazientiViewSet->IsEOF())
					return FALSE;

				queryDlg.m_lRelazione = SOLO_PAZIENTI;
				queryDlg.m_strPazFilter = filter;
				queryDlg.m_strEsameFrom = "";
				queryDlg.m_strEsameWhere = "";
				queryDlg.m_pPazientiSet = pazientiViewSet;
				queryDlg.m_pJoinEsamiSet = NULL;
				queryDlg.m_bCercaPaziente = TRUE;
				queryDlg.DoModal();

				lCurPazCode = queryDlg.m_lCurrentPri;

				pazientiViewSet->CloseRecordset("CDMSWorkListManager::SelectEntry");

				if (lCurPazCode == 0)
					return FALSE;
			}
		}

		pazientiSet.CloseRecordset("CDMSWorkListManager::SelectEntry");
	}

	//Recupero il tipo esame che deve essere importato
	if (idTipoEsameTemp < 0)
	{
		CVistaExtPrestazioniSet extPrestazioniSet;
		strFilter.Format("idOrdine = %li AND TipoEsame IS NOT NULL", m_lId);
		extPrestazioniSet.SetOpenFilter(strFilter);
		if (extPrestazioniSet.OpenRecordset("CCupWorkList::SelectEntry"))
		{
			if (!extPrestazioniSet.IsEOF())
				idTipoEsameTemp = extPrestazioniSet.m_lIdTipoEsameEndox;

			extPrestazioniSet.CloseRecordset("CCupWorkList::SelectEntry");
		}
	}

	//Simone - Prima di inserire l'esame devo verificare se esiste un esame di quel tipo, per lo stesso paziente e con codesame = null
	//			Se dovesse esistere propongo all'utente l'abbinamento
	//		Se sono più di uno devo proporre una lista dove l'utente può scegliere quale esame abbinare
	CVistaEsamiPerWLSet tempEsamiSet;
	strFilter.Format("DataEsame like '%s' and IdEsame = %li AND Paziente = %li AND (Codesame IS NULL OR Codesame = '') AND eliminato = 0", dataSelezionata, idTipoEsameTemp, lCurPazCode);
	tempEsamiSet.SetOpenFilter(strFilter);
	if (tempEsamiSet.OpenRecordset("CDMSWorkListManager::SelectEntry"))
	{
		if (!tempEsamiSet.IsEOF())
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_LISTAPREN_ESAMETROVATO), MB_TOPMOST);
			//Mostro la lista degli esami utilizzabili
			long idExam = -1;
			CExamListDlg examList(m_pEsamiView, &tempEsamiSet, &idExam);
			if (examList.DoModal() == IDOK)
			{
				//Abbina esame
				if (examList.m_iOperation == 2)
				{
					m_pEsamiView->RicercaCodicePaziente(lCurPazCode, idExam, FALSE, TRUE);
					UpdateDatiEsame(tempEsamiSet.m_lContatore);
					UpdateWithExamID(m_lId, tempEsamiSet.m_lContatore);
				}

				//Inserisci nuovo
				if (examList.m_iOperation == 1)
				{
					m_pEsamiView->RicercaCodicePaziente(lCurPazCode, 0, FALSE, TRUE);
					m_pEsamiView->OnEsameNewAutoCup(idTipoEsameTemp, m_lId);

					m_pEsamiView->OnEsameUpdateCup();
					if (m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
					{
						tempEsamiSet.CloseRecordset("CDMSWorkListManager::SelectEntry");
						CloseRecordset("CDMSWorkListManager::SelectEntry");
						return FALSE;
					}
					UpdateDatiEsame(m_pEsamiView->m_pEsamiSet->GetLastAdd());
					UpdateWithExamID(m_lId, m_pEsamiView->m_pEsamiSet->GetLastAdd());
				}
			}
			else
			{
				//Operazione annullata
				tempEsamiSet.CloseRecordset("CDMSWorkListManager::SelectEntry");
				CloseRecordset("CDMSWorkListManager::SelectEntry");
				return FALSE;
			}
		}
		else
		{
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_LISTAPREN_ESAMENEW), MB_YESNO) == IDNO)
			{
				tempEsamiSet.CloseRecordset("CDMSWorkListManager::SelectEntry");
				CloseRecordset("CDMSWorkListManager::SelectEntry");
				return FALSE;
			}
			
			m_pEsamiView->RicercaCodicePaziente(lCurPazCode, 0, FALSE, TRUE);
			m_pEsamiView->OnEsameNewAutoCup(idTipoEsameTemp, m_lId);

			m_pEsamiView->OnEsameUpdateCup();
			if (m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
			{
				tempEsamiSet.CloseRecordset("CDMSWorkListManager::SelectEntry");
				CloseRecordset("CDMSWorkListManager::SelectEntry");
				return FALSE;
			}
			UpdateDatiEsame(m_pEsamiView->m_pEsamiSet->GetLastAdd());
			UpdateWithExamID(m_lId, m_pEsamiView->m_pEsamiSet->GetLastAdd());
		}
		
		m_pEsamiView->MovePazientiAndEsami(NULL, TRUE, TRUE);

		tempEsamiSet.CloseRecordset("CDMSWorkListManager::SelectEntry");
	}

	CloseRecordset("CDMSWorkListManager::SelectEntry");
	return TRUE;
}

void CDMSWorkListManager::UpdateWithExamID(long lIDPrenotazione, long lIDEsame)
{
	
	CString strQuery;
	strQuery.Format("UPDATE EXT_ORDINI SET TRASFERITO = 1, IDESAMEINS = %li WHERE ID = %li", lIDEsame, lIDPrenotazione);

	try
	{
		theApp.m_dbEndox.ExecuteSQL(strQuery);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
}

void CDMSWorkListManager::UpdateDatiEsame(long lIDEsame)
{
	try
	{
		CEsamiSet tempExamSet;
		CString filter;
		filter.Format("contatore = %li", lIDEsame);
		tempExamSet.SetOpenFilter(filter);
		if (tempExamSet.OpenRecordset("CDMSWorkListManager::UpdateDatiEsame"))
		{
			if (!tempExamSet.IsEOF())
			{
				tempExamSet.EditRecordset("CDMSWorkListManager::UpdateDatiEsame");

				/*if (!IsFieldNull(&m_lIdUrgenzaEndox))
					tempExamSet.m_nCodiceRAO = m_lIdUrgenzaEndox;*/

				if (!IsFieldNull(&m_sOrderNumber) && !m_sOrderNumber.IsEmpty())
					tempExamSet.m_sCodEsame = m_sOrderNumber;

				if (!IsFieldNull(&m_sNosologico) && !m_sNosologico.IsEmpty())
					tempExamSet.m_sRicovero = m_sNosologico;

				// se riesco a transcodificare il medico metto la transcodifica, altrimenti metto il codice così come mi è arrivato //
				if (!IsFieldNull(&m_sMedicoInviante) && !m_sMedicoInviante.Trim().IsEmpty())
					tempExamSet.m_sInvMedico = m_sMedicoInviante;
				else
					tempExamSet.m_sInvMedico = m_sCodiceMedicoInviante;

				if (!IsFieldNull(&m_sNote) && !m_sNote.IsEmpty())
					tempExamSet.m_sAppunti = m_sNote;

				if (!IsFieldNull(&m_lIdRepartoEndox))
					tempExamSet.m_lInviante = m_lIdRepartoEndox;

				if (!IsFieldNull(&m_lProvenienzaEndox))
					tempExamSet.m_lProvenienza = m_lProvenienzaEndox;

				// if (!IsFieldNull(&m_sDescrizioneSala) && !m_sDescrizioneSala.IsEmpty())
				// 	tempExamSet.m_sSalaEsame = m_sDescrizioneSala;

				// if (!IsFieldNull(&m_lIdSedeEndox))
				//	tempExamSet.m_lIDSedeEsame = m_lIdSedeEndox;

				tempExamSet.UpdateRecordset("CDMSWorkListManager::UpdateDatiEsame");
			}
			
			tempExamSet.CloseRecordset("CDMSWorkListManager::UpdateDatiEsame");
		}

		//Importo tutte le prestazioni di quell'ordine NON ELIMINATE
		CVistaExtPrestazioniSet extPrestazioniSet;
		CRegioneSet regioneSet;
		CString strFilter;
		strFilter.Format("idOrdine = %li", m_lId);
		extPrestazioniSet.SetOpenFilter(strFilter);
		if (extPrestazioniSet.OpenRecordset("CDMSWorkListManager::UpdateDatiEsame"))
		{
			while(!extPrestazioniSet.IsEOF())
			{
				if (regioneSet.OpenRecordset("CDMSWorkListManager::UpdateDatiEsame"))
				{
					if (regioneSet.AddNewRecordset("CDMSWorkListManager::UpdateDatiEsame"))
					{
						regioneSet.m_lEsame = lIDEsame;
						regioneSet.m_lCodice = extPrestazioniSet.m_lIdPrestazioneEndox;
						regioneSet.m_lQuantita = extPrestazioniSet.m_lQuantita;
						regioneSet.m_lIdExtPrestazione = extPrestazioniSet.m_lId;
						//Simone - Stato CUP deve essere messo a 0 altrimenti la prestazione verrebbe segnalata come aggiunta a mano
						regioneSet.m_lStatoCUP = 0;
						regioneSet.UpdateRecordset("CDMSWorkListManager::SelectEntry");
						extPrestazioniSet.MoveNext();
					}

					regioneSet.CloseRecordset("CDMSWorkListManager::UpdateDatiEsame");
				}
			}
			
			tempExamSet.CloseRecordset("CDMSWorkListManager::UpdateDatiEsame");
		}

	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
}

BOOL CDMSWorkListManager::CampiObbligatoriValorizzati(CDMSWorkListManager *prenotazione)
{
	//Controllo se i campi obbligatori sono valorizzati
	BOOL bReturn = TRUE;
	CExtMinPazDataSetSet minPazDataSetSet;
	if (minPazDataSetSet.OpenRecordset("CDMSWorkListManager::CampiObbligatoriValorizzati"))
	{
		if (!minPazDataSetSet.IsEOF())
		{
			if (minPazDataSetSet.m_bCognome && (IsFieldNull(&prenotazione->m_sCognome) || prenotazione->m_sCognome == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bCognome2 && (IsFieldNull(&prenotazione->m_sCognome2) || prenotazione->m_sCognome2 == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bNome && (IsFieldNull(&prenotazione->m_sNome) || prenotazione->m_sNome == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bDataNascita && (IsFieldNull(&prenotazione->m_sDataNascita) || prenotazione->m_sDataNascita == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bIstatNascita && (IsFieldNull(&prenotazione->m_lISTATNascita) || prenotazione->m_lISTATNascita == 0))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bIndirizzoResidenza && (IsFieldNull(&prenotazione->m_sIndirizzoResidenza) || prenotazione->m_sIndirizzoResidenza == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bIstatResidenza && (IsFieldNull(&prenotazione->m_lISTATResidenza) || prenotazione->m_lISTATResidenza == 0))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bCapResidenza && (IsFieldNull(&prenotazione->m_sCapResidenza) || prenotazione->m_sCapResidenza == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bTelefono1 && (IsFieldNull(&prenotazione->m_sTelefono1) || prenotazione->m_sTelefono1 == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bTelefono2 && (IsFieldNull(&prenotazione->m_sTelefono2) || prenotazione->m_sTelefono2 == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bCellulare1 && (IsFieldNull(&prenotazione->m_sCellulare1) || prenotazione->m_sCellulare1 == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bCellulare2 && (IsFieldNull(&prenotazione->m_sCellulare2) || prenotazione->m_sCellulare2 == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bCodiceFiscale && (IsFieldNull(&prenotazione->m_sCodiceFiscale) || prenotazione->m_sCodiceFiscale == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bCodiceSanitario && (IsFieldNull(&prenotazione->m_sCodiceSanitario) || prenotazione->m_sCodiceSanitario == ""))
				bReturn = FALSE;
			if (minPazDataSetSet.m_bSesso && (IsFieldNull(&prenotazione->m_lSesso)))
				bReturn = FALSE;
		}

		minPazDataSetSet.CloseRecordset("CDMSWorkListManager::CampiObbligatoriValorizzati");
	}
	
	return bReturn;
}

void CDMSWorkListManager::CostruisciFiltroPaziente(CString *filter, CDMSWorkListManager *prenotazione)
{
	//Compongo il filtro con i campi richiesti
	filter->Format("");
	CExtMinPazDataSetSet minPazDataSetSet;
	if (minPazDataSetSet.OpenRecordset("CDMSWorkListManager::CostruisciFiltroPaziente"))
	{
		if (!minPazDataSetSet.IsEOF())
		{
			if (minPazDataSetSet.m_bCognome)
				if (*filter == "")
					filter->Format("Cognome = '%s'", prenotazione->m_sCognome);
				else
					filter->AppendFormat(" AND Cognome = '%s'", prenotazione->m_sCognome);

			if (minPazDataSetSet.m_bCognome2)
				if (*filter == "")
					filter->Format("Cognome2 = '%s'", prenotazione->m_sCognome2);
				else
					filter->AppendFormat(" AND Cognome = '%s'", prenotazione->m_sCognome2);

			if (minPazDataSetSet.m_bNome)
				if (*filter == "")
					filter->Format("Nome = '%s'", prenotazione->m_sNome);
				else
					filter->AppendFormat(" AND Nome = '%s'", prenotazione->m_sNome);

			if (minPazDataSetSet.m_bDataNascita)
				if (*filter == "")
					filter->Format("NatoIlCustom = %li", prenotazione->m_lDataNascitaCustom);
				else
					filter->AppendFormat(" AND NatoIlCustom = %li", prenotazione->m_lDataNascitaCustom);

			if (minPazDataSetSet.m_bIstatNascita)
				if (*filter == "")
					filter->Format("IdComuneNascita = %li", prenotazione->m_lISTATNascita);
				else
					filter->AppendFormat(" AND IdComuneNascita = %li", prenotazione->m_lISTATNascita);

			if (minPazDataSetSet.m_bIndirizzoResidenza)
				if (*filter == "")
					filter->Format("Via = '%s'", prenotazione->m_sIndirizzoResidenza);
				else
					filter->AppendFormat(" AND Via = '%s'", prenotazione->m_sIndirizzoResidenza);

			if (minPazDataSetSet.m_bIstatResidenza)
				if (*filter == "")
					filter->Format("IdComune = %li", prenotazione->m_lISTATResidenza);
				else
					filter->AppendFormat(" AND IdComune = %li", prenotazione->m_lISTATResidenza);

			if (minPazDataSetSet.m_bCapResidenza)
				if (*filter == "")
					filter->Format("Cap = '%s'", prenotazione->m_sCapResidenza);
				else
					filter->AppendFormat(" AND Cap = '%s'", prenotazione->m_sCapResidenza);

			if (minPazDataSetSet.m_bTelefono1)
				if (*filter == "")
					filter->Format("Telefono1 = '%s'", prenotazione->m_sTelefono1);
				else
					filter->AppendFormat(" AND Telefono1 = '%s'", prenotazione->m_sTelefono1);

			if (minPazDataSetSet.m_bTelefono2)
				if (*filter == "")
					filter->Format("Telefono2 = '%s'", prenotazione->m_sTelefono2);
				else
					filter->AppendFormat(" AND Telefono2 = '%s'", prenotazione->m_sTelefono2);

			if (minPazDataSetSet.m_bCellulare1)
				if (*filter == "")
					filter->Format("Cellulare1 = '%s'", prenotazione->m_sCellulare1);
				else
					filter->AppendFormat(" AND Cellulare1 = '%s'", prenotazione->m_sCellulare1);

			if (minPazDataSetSet.m_bCellulare2)
				if (*filter == "")
					filter->Format("Cellulare2 = '%s'", prenotazione->m_sCellulare2);
				else
					filter->AppendFormat(" AND Cellulare2 = '%s'", prenotazione->m_sCellulare2);

			if (minPazDataSetSet.m_bCodiceFiscale)
				if (*filter == "")
					filter->Format("CodFisc = '%s'", prenotazione->m_sCodiceFiscale);
				else
					filter->AppendFormat(" AND CodFisc = '%s'", prenotazione->m_sCodiceFiscale);

			if (minPazDataSetSet.m_bCodiceSanitario)
				if (*filter == "")
					filter->Format("CodSanit = '%s'", prenotazione->m_sCodiceSanitario);
				else
					filter->AppendFormat(" AND CodSanit = '%s'", prenotazione->m_sCodiceSanitario);

			if (minPazDataSetSet.m_bSesso)
				if (*filter == "")
					filter->Format("Sesso = %li", prenotazione->m_lSesso);
				else
					filter->AppendFormat(" AND Sesso = %li", prenotazione->m_lSesso);
		}

		minPazDataSetSet.CloseRecordset("CDMSWorkListManager::CostruisciFiltroPaziente");
	}
}