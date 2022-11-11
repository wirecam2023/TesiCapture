#include "stdafx.h"
#include "Endox.h"
#include "WorkListDicom.h"
#include "SediEsameSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CWorkListDicom, CWorkListManager)

CString CWorkListDicom::GetDefaultSQL()
{
	return "VIEWDICOMWORKLIST";
}

CWorkListDicom::CWorkListDicom(CEsamiView* pEsamiView) : CWorkListManager(pEsamiView)
{
	m_ImageList.Create(16, 16, ILC_COLOR16, 2, 2);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_LISTA_PREN_NO));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_LISTA_PREN_SI));

	m_nFields = 13;
}
		
void CWorkListDicom::PrepareList(CListCtrl* pList)
{
	pList->SetExtendedStyle(pList->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pList->SetImageList(&m_ImageList, LVSIL_SMALL);

	pList->InsertColumn(0, "",														LVCFMT_CENTER, 150);
	pList->InsertColumn(1, theApp.GetMessageString(IDS_ORE),						LVCFMT_CENTER,  50);
	pList->InsertColumn(2, theApp.GetMessageString(IDS_ESAMIVIEW_PATIENT_NUM_2),	LVCFMT_LEFT,   150);
	pList->InsertColumn(3, theApp.GetMessageString(IDS_PRESTAZIONE),				LVCFMT_LEFT,   150);
	pList->InsertColumn(4, theApp.GetMessageString(IDS_NOTE),						LVCFMT_LEFT,   150);
	pList->InsertColumn(5, theApp.GetMessageString(IDS_SEDEANATOMICA),			LVCFMT_LEFT,   150);
	pList->InsertColumn(6, "",														LVCFMT_LEFT,     0);
}

//
BOOL CWorkListDicom::FillList(CListCtrl* pList, CString strAddFilter)
{
	pList->DeleteAllItems();

	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);	

	CString strFilter;
	strFilter.Format("examdate LIKE '%04d%02d%02d%%'", 
		             SystemTime.wYear, 
					 SystemTime.wMonth, 
					 SystemTime.wDay);

	if (strAddFilter.IsEmpty())
		SetOpenFilter(strFilter);
	else
		SetOpenFilter(strFilter + " AND " + strAddFilter);
	SetSortRecord("patientlastname, patientfirstname");
	
	if (!OpenRecordset("CWorkListDicom::RiempiLista"))
		return FALSE;
	
	if (IsBOF() && IsEOF())
	{
		CloseRecordset("CWorkListDicom::RiempiLista");
		/*theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PRENOTAZIONE_EMPTY));*/
		return FALSE;
	}

	CString strTmp;
	while (!IsEOF())
	{
		int iItemInserted = pList->InsertItem(pList->GetItemCount(), m_sAccessionNumber, 0);

		strTmp.Format("%s:%s", m_sExamDate.Mid(8, 2), m_sExamDate.Mid(10, 2));
		pList->SetItemText(iItemInserted, 1, strTmp);

		strTmp.Format("%s %s", m_sPatientLastName, m_sPatientFirstName);
		pList->SetItemText(iItemInserted, 2, strTmp);
		pList->SetItemText(iItemInserted, 3, m_sExamTypeDescription);
		pList->SetItemText(iItemInserted, 4, m_sNotes);
		pList->SetItemText(iItemInserted, 5, m_sSiteDescription);
		MoveNext();
	}
	CloseRecordset("CWorkListDicom::RiempiLista");

	pList->SetColumnWidth(0, 24);
	pList->SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	pList->SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	pList->SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	pList->SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	pList->SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);

	return TRUE;
}

//
BOOL CWorkListDicom::SelectEntry(CListCtrl* pList, int iItem)
{
	CString strAccessionNumber = pList->GetItemText(iItem, 0);

	CString strFilter;
	strFilter.Format("accessionnumber = '%s'", strAccessionNumber);
	SetOpenFilter(strFilter);
	
	if (!OpenRecordset("CWorkListDicom::SelectEntry"))
		return FALSE;

	CPazientiSet PazientiSet;
	strFilter.Format("assiden = '%s'", m_sPatientUID);
	PazientiSet.SetOpenFilter(strFilter);
	if (!PazientiSet.OpenRecordset("CWorkListDicom::SelectEntry"))
	{
		CloseRecordset("CWorkListDicom::SelectEntry");
		return FALSE;
	}

	BOOL bReturn = FALSE;
	if (PazientiSet.IsEOF())
	{
		if (!IsFieldNull(&m_sPatientLastName) && !m_sPatientLastName.IsEmpty() &&
			!IsFieldNull(&m_sPatientFirstName)&& !m_sPatientFirstName.IsEmpty() &&
			!IsFieldNull(&m_sPatientBornDate) && m_sPatientBornDate.GetLength() == 14)
		{
			if (PazientiSet.AddNewRecordset("CWorkListDicom::SelectEntry"))
			{
				PazientiSet.m_sAssIden = m_sPatientUID;
				PazientiSet.m_sCognome = m_sPatientLastName;
				PazientiSet.m_sNome	   = m_sPatientFirstName;
				PazientiSet.m_lSessoPaz= m_lPatientSex;
				PazientiSet.m_lNatoIlCustom = CCustomDate(atoi(m_sPatientBornDate.Mid(0, 4)), 
					                                      atoi(m_sPatientBornDate.Mid(4, 2)), 
														  atoi(m_sPatientBornDate.Mid(6, 2)), 
														  0, 0, 0).GetDate();
				
				if (PazientiSet.UpdateRecordset("CWorkListDicom::SelectEntry"))
				{
					PazientiSet.CloseRecordset("CWorkListDicom::SelectEntry");

					strFilter.Format("assiden = '%s'", m_sPatientUID);
					PazientiSet.SetOpenFilter(strFilter);
					PazientiSet.SetSortRecord("Contatore");

					PazientiSet.OpenRecordset("CWorkListDicom::SelectEntry");
					PazientiSet.MoveLast();

					try {

						CString strQueryInsertPatientDicom;
						strQueryInsertPatientDicom.Format("INSERT INTO DICOMPATIENT (IDPATIENT, DICOMPID) VALUES (%li, '%s')", 
											  PazientiSet.m_lContatore,
											  m_sPatientUID);
						GetDatabase()->ExecuteSQL(strQueryInsertPatientDicom);
					}
					catch(CDBException* e)
					{
						TCHAR szError[MAX_PATH];
						e->GetErrorMessage(szError, MAX_PATH); 
						theApp.AfxMessageBoxEndo(szError);
						e->Delete();
					}

					m_pEsamiView->RicercaCodicePaziente(PazientiSet.m_lContatore, 0, FALSE, TRUE);
					m_pEsamiView->MovePazientiAndEsami(NULL, TRUE, TRUE);
					bReturn = InsertExam(strAccessionNumber, PazientiSet.m_lContatore);
				}
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo("Non ci sono dati sufficienti per proseguire con l'inserimento del paziente!");
		}
	}
	else
	{
		PazientiSet.UndeleteRecordset("CWorkListDicom::SelectEntry"); // lo faccio sempre per sicurezza //

		m_pEsamiView->RicercaCodicePaziente(PazientiSet.m_lContatore, 0, FALSE, TRUE);
		m_pEsamiView->MovePazientiAndEsami(NULL, TRUE, TRUE);
		bReturn = InsertExam(strAccessionNumber, PazientiSet.m_lContatore);
	}

	return bReturn;
}

BOOL CWorkListDicom::InsertExam(CString strAccessionNumber, long lPatientID)
{
	if (!IsFieldNull(&m_lExamType))
	{
		m_pEsamiView->OnEsameNewAuto(m_lExamType, -1);
		m_pEsamiView->OnEsameUpdate();
		if (m_pEsamiView->m_pEsamiSet->EditRecordset("CWorkListDicom::InsertExam"))
		{
			m_pEsamiView->m_pEsamiSet->m_sCodEsame = strAccessionNumber;
			m_pEsamiView->m_pEsamiSet->UpdateRecordset("CWorkListDicom::InsertExam");
		}

		if (InsertStudySerie(lPatientID, m_pEsamiView->m_pEsamiSet->m_lContatore))
		{
			try {

				CString strQueryUpdate;
				strQueryUpdate.Format("UPDATE DICOMWORKLIST SET IDEXAMINSERTED = %li WHERE ACCESSIONNUMBER = '%s'", 
									  m_pEsamiView->m_pEsamiSet->m_lContatore,
									  strAccessionNumber);
				GetDatabase()->ExecuteSQL(strQueryUpdate);
			}
			catch(CDBException* e)
			{
				TCHAR szError[MAX_PATH];
				e->GetErrorMessage(szError, MAX_PATH); 
				theApp.AfxMessageBoxEndo(szError);
				e->Delete();
			}
		
			return TRUE;
		}
		else
		{
			try {

				CString strQueryUpdate;
				strQueryUpdate.Format("UPDATE EESAMI SET CODESAME = '' WHERE CONTATORE = '%li'", 
									  m_pEsamiView->m_pEsamiSet->m_lContatore);
				GetDatabase()->ExecuteSQL(strQueryUpdate);
			}
			catch(CDBException* e)
			{
				TCHAR szError[MAX_PATH];
				e->GetErrorMessage(szError, MAX_PATH); 
				theApp.AfxMessageBoxEndo(szError);
				e->Delete();
			}
		
			return TRUE;

		}
	}	

	return FALSE;
}

BOOL CWorkListDicom::InsertStudySerie(long lPatientID, long lExamID)
{
	BOOL bReturn = FALSE;

	if (!IsFieldNull(&m_sStudyUidProposed) && (!IsFieldNull(&this->m_sSerieUidProposed)))
	{
		try {
			CString strQueryStudy, strQuerySerie;

			strQueryStudy.Format("INSERT INTO DICOMSTUDY (INSTANCEUID, IDPATIENT, STUDYDATE) VALUES ('%s', %li, '%s')", 
							     m_sStudyUidProposed,
								 lPatientID,
								 m_sExamDate);

			strQuerySerie.Format("INSERT INTO DICOMSERIES (IDEXAM, INSTANCEUID, STUDYINSTANCEUID) VALUES (%li, '%s', '%s')", 
								 lExamID,
								 m_sSerieUidProposed,
								 m_sStudyUidProposed);
			
			GetDatabase()->ExecuteSQL(strQueryStudy);
			GetDatabase()->ExecuteSQL(strQuerySerie);
			bReturn = TRUE;
		}
		catch(CDBException* e)
		{
			TCHAR szError[MAX_PATH];
			e->GetErrorMessage(szError, MAX_PATH); 
			theApp.AfxMessageBoxEndo(szError);
			e->Delete();
		}
	}

	return bReturn;
}

void CWorkListDicom::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "patientuid",				m_sPatientUID,			 64);
	RFX_Text(pFX, "patientlastname",		m_sPatientLastName,		255);
	RFX_Text(pFX, "patientfirstname",		m_sPatientFirstName,	255);
	RFX_Text(pFX, "patientborndate",		m_sPatientBornDate,		 14);
	RFX_Long(pFX, "patientsex",				m_lPatientSex);
	RFX_Text(pFX, "examdate",				m_sExamDate,			 14);
	RFX_Long(pFX, "examtype",				m_lExamType);
	RFX_Text(pFX, "examtypedescription",	m_sExamTypeDescription,	255);
	RFX_Text(pFX, "accessionnumber",		m_sAccessionNumber,		 50);
	RFX_Text(pFX, "studyuidproposed",		m_sStudyUidProposed,	 64);
	RFX_Text(pFX, "serieuidproposed",		m_sSerieUidProposed,	 64);
	RFX_Text(pFX, "notes",					m_sNotes,				255);
	RFX_Text(pFX, "DescrizioneSede",		m_sSiteDescription,		255);
}