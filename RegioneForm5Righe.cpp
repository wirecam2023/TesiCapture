#include "stdafx.h"
#include "Endox.h"
#include "RegioneForm5Righe.h"

#include "EsamiView.h"
#include "Common.h"
#include "EsamiSet.h"
#include "GruppiPrestazioniUseDlg.h"
#include "GruppiPrestazioniPrestazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRegioneForm5Righe::CRegioneForm5Righe(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CRegioneForm5Righe::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 5;

	m_nSearchMode = 0;
}

CRegioneForm5Righe::~CRegioneForm5Righe()
{
}

BEGIN_MESSAGE_MAP(CRegioneForm5Righe, CSubForm)
	ON_WM_CTLCOLOR()

	ON_CBN_EDITCHANGE	(IDC_REGIONE_1,		OnChangeRegione1)
	ON_CBN_SELCHANGE	(IDC_REGIONE_1,		OnChangeRegione1)
	ON_CBN_EDITCHANGE	(IDC_REGIONE_2,		OnChangeRegione2)
	ON_CBN_SELCHANGE	(IDC_REGIONE_2,		OnChangeRegione2)
	ON_CBN_EDITCHANGE	(IDC_REGIONE_3,		OnChangeRegione3)
	ON_CBN_SELCHANGE	(IDC_REGIONE_3,		OnChangeRegione3)
	ON_CBN_EDITCHANGE	(IDC_REGIONE_4,		OnChangeRegione4)
	ON_CBN_SELCHANGE	(IDC_REGIONE_4,		OnChangeRegione4)
	ON_CBN_EDITCHANGE	(IDC_REGIONE_5,		OnChangeRegione5)
	ON_CBN_SELCHANGE	(IDC_REGIONE_5,		OnChangeRegione5)
	ON_EN_CHANGE		(IDC_QTA_1,			OnChangeQta1)
	ON_EN_CHANGE		(IDC_QTA_2,			OnChangeQta2)
	ON_EN_CHANGE		(IDC_QTA_3,			OnChangeQta3)
	ON_EN_CHANGE		(IDC_QTA_4,			OnChangeQta4)
	ON_EN_CHANGE		(IDC_QTA_5,			OnChangeQta5)

	ON_BN_CLICKED(IDC_BTN_GRUPPI, OnBnClickedBtnGruppi)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBnClickedBtnReset)
END_MESSAGE_MAP()

void CRegioneForm5Righe::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Numero [5] = { IDC_NUM_1, IDC_NUM_2, IDC_NUM_3, IDC_NUM_4, IDC_NUM_5 };
	static UINT nID_Regione[5] = { IDC_REGIONE_1, IDC_REGIONE_2, IDC_REGIONE_3, IDC_REGIONE_4, IDC_REGIONE_5 };
	static UINT nID_Qta    [5] = { IDC_QTA_1, IDC_QTA_2, IDC_QTA_3, IDC_QTA_4, IDC_QTA_5 };

	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SURE_00, m_ctrlStatic);

	for(int i = 0; i < m_nIndexPage; i++)
		DDX_Control(pDX, nID_Regione[i], m_ctrlRegione[i]);

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_Regione(pDX, nID_Regione[i], m_ctrLine[m_nIndexLine+i].m_Set.m_lCodice);
			if (pDX->m_bSaveAndValidate)
			{
				int temp = nID_Qta[i];
				CString strValore;
				this->GetDlgItem(temp)->GetWindowText(strValore);
				if (strValore.Compare("") == 0)
					m_ctrLine[m_nIndexLine+i].m_Set.m_lQuantita = 0;
				else
					m_ctrLine[m_nIndexLine+i].m_Set.m_lQuantita = atoi(strValore);
			}
			else
			{
				int temp = nID_Qta[i];
				CString strValore;
				if (m_ctrLine[m_nIndexLine+i].m_Set.m_lQuantita > 0)
					strValore.Format("%li", m_ctrLine[m_nIndexLine+i].m_Set.m_lQuantita);
				else
					strValore = "";
				this->GetDlgItem(temp)->SetWindowText(strValore);
			}
			//DDX_Text(pDX, nID_Qta[i], m_ctrLine[m_nIndexLine+i].m_Set.m_Quantita);
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);

	DDX_Control(pDX, IDC_BTN_GRUPPI, m_ctrlButtonGruppi);
	DDX_Control(pDX, IDC_BTN_RESET, m_ctrlButtonReset);

	DDX_Radio(pDX, IDC_RADIO_AND, m_nSearchMode);
}

void CRegioneForm5Righe::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_regione5righe] == NULL)
	{
		pEsamiView->m_pDynForm[sub_regione5righe] = new CRegioneForm5Righe(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_regione5righe] != NULL)
		{
			pEsamiView->m_pDynForm[sub_regione5righe]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_regione5righe]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_regione5righe]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_regione5righe]->CreateChildForm(CRegioneForm5Righe::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CRegioneForm5Righe::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_SURE_00:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_NUM_1:
		case IDC_NUM_2:
		case IDC_NUM_3:
		case IDC_NUM_4:
		case IDC_NUM_5:
		case IDC_REGIONE_1:
		case IDC_REGIONE_2:
		case IDC_REGIONE_3:
		case IDC_REGIONE_4:
		case IDC_REGIONE_5:
		case IDC_QTA_1:
		case IDC_QTA_2:
		case IDC_QTA_3:
		case IDC_QTA_4:
		case IDC_QTA_5:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CRegioneForm5Righe::OnInitDialog() 
{
	CSubForm::OnInitDialog();
	
	AddAnchor(IDC_SURE_00, CSize(0,25), CSize(40,25));
	AddAnchor(IDC_SURE_01, CSize(0,0), CSize(100,100));
	AddAnchor(IDC_RADIO_AND, CSize(40,20), CSize(45,30));
	AddAnchor(IDC_RADIO_OR, CSize(45,20), CSize(50,30));
	AddAnchor(IDC_BTN_GRUPPI, CSize(50,20), CSize(75,30));
	AddAnchor(IDC_BTN_RESET, CSize(75,20), CSize(100,30));
	AddAnchor(IDC_SCROLL, CSize(100,50), CSize(100,100));
	AddAnchor(IDC_NUM_1, CSize(0,60), CSize(0,60));
	AddAnchor(IDC_NUM_2, CSize(0,70), CSize(0,70));
	AddAnchor(IDC_NUM_3, CSize(0,80), CSize(0,80));
	AddAnchor(IDC_NUM_4, CSize(0,90), CSize(0,90));
	AddAnchor(IDC_NUM_5, CSize(0,100), CSize(0,100));
	AddAnchor(IDC_REGIONE_1, CSize(0,60), CSize(100,60));
	AddAnchor(IDC_REGIONE_2, CSize(0,70), CSize(100,70));
	AddAnchor(IDC_REGIONE_3, CSize(0,80), CSize(100,80));
	AddAnchor(IDC_REGIONE_4, CSize(0,90), CSize(100,90));
	AddAnchor(IDC_REGIONE_5, CSize(0,100), CSize(100,100));
	AddAnchor(IDC_QTA_1, CSize(100,60), CSize(100,60));
	AddAnchor(IDC_QTA_2, CSize(100,70), CSize(100,70));
	AddAnchor(IDC_QTA_3, CSize(100,80), CSize(100,80));
	AddAnchor(IDC_QTA_4, CSize(100,90), CSize(100,90));
	AddAnchor(IDC_QTA_5, CSize(100,100), CSize(100,100));

	GetDlgItem(IDC_SURE_00)->SetFont(&theApp.m_fontBold, TRUE);

	theApp.LocalizeDialog(this, CRegioneForm5Righe::IDD, "RegioneForm");
	return TRUE;
}

void CRegioneForm5Righe::ModificaForm()
{
	for(int i = 0; i < m_nIndexPage; i++)
		m_ctrlRegione[i].SetParam(&m_ctrLine[m_nIndexLine+i].m_Set.m_lCodice, m_pEsamiView);
}

LRESULT CRegioneForm5Righe::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CRegioneForm5Righe::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CRegioneSet setRegione;
		setRegione.SetOpenFilter(sFilter);
		if (setRegione.OpenRecordset("CRegioneForm5Righe::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setRegione.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setRegione, nCounter, FALSE);

				nCounter++;
				setRegione.MoveNext();
			}

			setRegione.CloseRecordset("CRegioneForm5Righe::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CRegioneForm5Righe::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	if (theApp.m_bPrestazioniReadOnly)
		wParam = TRUE;

	int i;

	UINT pControlID1[] = {
		IDC_QTA_1,
		IDC_QTA_2,
		IDC_QTA_3,
		IDC_QTA_4,
		IDC_QTA_5
	};

	UINT pControlID2[] = {
		IDC_REGIONE_1,
		IDC_REGIONE_2,
		IDC_REGIONE_3,
		IDC_REGIONE_4,
		IDC_REGIONE_5,
		IDC_BTN_GRUPPI,
		IDC_BTN_RESET
	};

	UINT pControlID3[] = {
		IDC_RADIO_AND,
		IDC_RADIO_OR
	};

	for(i = 0; i < (sizeof(pControlID1) / sizeof(UINT)); i++)
		SendDlgItemMessage(pControlID1[i], EM_SETREADONLY, wParam, lParam);

	for(i = 0; i < (sizeof(pControlID2) / sizeof(UINT)); i++)
		GetDlgItem(pControlID2[i])->EnableWindow(!(BOOL)wParam);

	for(i = 0; i < (sizeof(pControlID3) / sizeof(UINT)); i++)
		GetDlgItem(pControlID3[i])->ShowWindow((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) != 0 ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);

	return 1;
}

LRESULT CRegioneForm5Righe::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CRegioneForm5Righe::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CRegioneSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CRegioneForm5Righe::OnFormSave"))
	{
		SaveForm(FALSE, &m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CRegioneForm5Righe::OnFormSave");
	}

	return 1;
}

LRESULT CRegioneForm5Righe::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	// cerco se è stata valorizzata almeno una prestazione //
	BOOL bProceed = FALSE;
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		if ((m_ctrLine[i].m_Set.m_lCodice > 0) && (m_ctrLine[i].m_Set.m_lCodice < 1246576928))
		{
			bProceed = TRUE;
			break;
		}
	}

	// se è stata trovata almeno una prestazione compongo il filtro //
	if (bProceed)
	{
		CString strTempWhere = "";

		for(int i = 0; i < MAX_OBJ_X_FORM; i++)
			if ((m_ctrLine[i].m_Set.m_lCodice > 0) && (m_ctrLine[i].m_Set.m_lCodice < 1246576928))
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "ERegione", i, "Esame", "Codice", m_ctrLine[i].m_Set.m_lCodice, m_nSearchMode%2, MODE_UGUALE);

		strTempWhere.Trim();
		if (!strTempWhere.IsEmpty())
		{
			if (!pStrWhere->IsEmpty())
				(*pStrWhere) += " AND ";

			(*pStrWhere) += "(" + strTempWhere + ")";
		}
	}

	return 1;
}

long CRegioneForm5Righe::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CRegioneForm5Righe::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_lCodice != 0);
}

void CRegioneForm5Righe::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CRegioneSet* pSet = (CRegioneSet*)pBaseSet;
	if (bToSet)
	{
		pSet->CopyFieldFrom(&m_ctrLine[nCounter].m_Set);
	}
	else
	{
		m_ctrLine[nCounter].m_Set.CopyFieldFrom(pSet);
		m_ctrLine[nCounter].m_nStato = RECORD_FULL;
		m_ctrLine[nCounter].m_nContatore = pSet->m_lContatore;
	}
}

BOOL CRegioneForm5Righe::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

void CRegioneForm5Righe::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
	{
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;

		if (m_ctrLine[nCounter].m_Set.m_lQuantita < 1)
			m_ctrLine[nCounter].m_Set.m_lQuantita = 1;
	}
	else
	{
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
	}
}

void CRegioneForm5Righe::OnChangeRegione1()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine + 0, TRUE);
	UpdateData(FALSE);
}

void CRegioneForm5Righe::OnChangeRegione2()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine+1, TRUE);
	UpdateData(FALSE);
}

void CRegioneForm5Righe::OnChangeRegione3()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine+2, TRUE);
	UpdateData(FALSE);
}

void CRegioneForm5Righe::OnChangeRegione4()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine+3, TRUE);
	UpdateData(FALSE);
}

void CRegioneForm5Righe::OnChangeRegione5()
{
	UpdateData(TRUE);
	SetLineDirty(m_nIndexLine+4, TRUE);
	UpdateData(FALSE);
}

void CRegioneForm5Righe::OnChangeQta1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CRegioneForm5Righe::OnChangeQta2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CRegioneForm5Righe::OnChangeQta3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CRegioneForm5Righe::OnChangeQta4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);
}

void CRegioneForm5Righe::OnChangeQta5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);
}

long CRegioneForm5Righe::GetContenuto()
{
	return sub_regione5righe;
}

BOOL CRegioneForm5Righe::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}

void CRegioneForm5Righe::OnBnClickedBtnGruppi()
{
	m_ctrlButtonGruppi.SetCheck(BST_UNCHECKED);
	UpdateData(TRUE);

	CGruppiPrestazioniUseDlg dlg(this, m_pEsamiView, m_pEsamiView->m_pEsamiSet->m_lIDEsame);
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_lReturn > 0)
		{
			CString strFilter;
			strFilter.Format("IDGruppo=%li", dlg.m_lReturn);

			CGruppiPrestazioniPrestazioniSet setTemp;
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CRegioneForm::OnBnClickedBtnGruppi"))
			{
				for(int i = 0; i < MAX_OBJ_X_FORM; i++)
				{
					if ((m_ctrLine[i].m_nStato == RECORD_EMPTY) || (m_ctrLine[i].m_Set.m_lCodice <= 0))
					{
						if (setTemp.IsEOF())
							break;

						// m_ctrLine[i].m_Set.m_Contatore = 0;
						m_ctrLine[i].m_Set.m_lEsame = 0;
						m_ctrLine[i].m_Set.m_lCodice = setTemp.m_lIDPrestazione;
						m_ctrLine[i].m_Set.m_lQuantita = 1;
						m_ctrLine[i].m_nStato = RECORD_FULL | RECORD_DIRTY;
						// m_ctrLine[i].m_nContatore = 0;

						setTemp.MoveNext();
					}
				}
				setTemp.CloseRecordset("CRegioneForm::OnBnClickedBtnGruppi");
			}

			UpdateData(FALSE);
		}
	}
}

void CRegioneForm5Righe::OnBnClickedBtnReset()
{
	m_ctrlButtonReset.SetCheck(BST_UNCHECKED);

	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
		{
			m_ctrLine[i].m_Set.m_lCodice = 0;
			m_ctrLine[i].m_nStato = RECORD_EMPTY;
			SetLineDirty(i, TRUE);
		}
	}

	m_ctrlScroll.SetScrollPos(0);
	m_nIndexLine = 0;

	UpdateData(FALSE);
}

void CRegioneForm5Righe::SaveForm(BOOL bPaziente, long* pParamOfFilter, CBaseSet* pSet, long* pCounterSet, long* pParamSet)
{
	BOOL bError;
	CString strFilter;

	// Sandro 26/01/2014 // RAS 20140009 //

	if (theApp.m_bCodificaRegionaleEliminaDuplicati)
	{
		// cerco ed eventualmente elimino le voci duplicate //

		BOOL bTrovatoDuplicato = FALSE;

		for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		{
			if (m_ctrLine[i].m_Set.m_lCodice > 0)
			{
				for(int j = i + 1; j < MAX_OBJ_X_FORM; j++)
				{
					if (m_ctrLine[i].m_Set.m_lCodice == m_ctrLine[j].m_Set.m_lCodice)
					{
						m_ctrLine[j].m_Set.m_lCodice = 0;
						SetLineDirty(j, TRUE);

						bTrovatoDuplicato = TRUE;
					}
				}
			}
		}

		if (bTrovatoDuplicato)
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REGIONE_DUPLICATI));
	}

	//
	CRegioneSet tempRegioneSet;
	for(int nCounter = 0; nCounter < MAX_OBJ_X_FORM; nCounter++)
	{
		BOOL bSave		= FALSE;
		long nContatore = 0;
		
		if (IsLineDirty(nCounter))
		{
			if (IsValidSet(nCounter))
			{
				nContatore = GetCounterSetOfLine(nCounter);
				
				if (nContatore)
				{
					strFilter.Format("Contatore=%li", nContatore);
		
					/* Simone - 21/11/2013. La modifica di una riga deve, in realtà, cancellare il record precedente ed inserirne uno nuovo */
					/*if (pSet->RecordsetReOpen(bError, strFilter, "Contatore", "CRegioneForm5Righe::SaveForm"))
						bSave = pSet->EditRecordset("CRegioneForm::SaveForm");*/

					//Settare lo stato a 3, ovvero DA CANCELLARE
					tempRegioneSet.SetOpenFilter(strFilter);
					if (tempRegioneSet.OpenRecordset("CRegioneForm::SaveForm"))
					{
						//Update 10/03/14 - La prestazione deve essere segnata "da cancellare" solo se questa è 0, ovvero è già stata notificata al cup. In caso contrario ritorna a 0						
						tempRegioneSet.EditRecordset("CRegioneForm::SaveForm");
						switch(tempRegioneSet.m_lStatoCUP)
						{
							case 0:
								tempRegioneSet.m_lStatoCUP = 3;
								break;
							case 1:
								tempRegioneSet.m_lStatoCUP = 0;
								break;
							case 3:
								tempRegioneSet.m_lStatoCUP = 3;
								break;
							default:
								break;
						}
							
						tempRegioneSet.UpdateRecordset("CRegioneForm::SaveForm");					
						tempRegioneSet.CloseRecordset("CRegioneForm::SaveForm");
					}

					if (pSet->RecordsetReOpen(bError, strFilter, "Contatore", "CRegioneForm5Righe::SaveForm"))
						pSet->DeleteRecordset("CRegioneForm5Righe::SaveForm");

					bSave = pSet->AddNewRecordset("CRegioneForm5Righe::SaveForm");
				}
				else
				{
					bSave = pSet->AddNewRecordset("CRegioneForm5Righe::SaveForm");
				}
			}
			else
			{
				nContatore = GetCounterSetOfLine(nCounter);
				
				if (nContatore)
				{
					strFilter.Format("Contatore=%li", nContatore);

					//Settare lo stato a 3, ovvero DA CANCELLARE
					tempRegioneSet.SetOpenFilter(strFilter);
					if (tempRegioneSet.OpenRecordset("CRegioneForm::SaveForm"))
					{
						tempRegioneSet.EditRecordset("CRegioneForm::SaveForm");
						switch (tempRegioneSet.m_lStatoCUP)
						{
							case 1:
								tempRegioneSet.m_lStatoCUP = 0;
								break;
							default:
								tempRegioneSet.m_lStatoCUP = 3;
								break;
						}
						
						tempRegioneSet.UpdateRecordset("CRegioneForm::SaveForm");
						tempRegioneSet.CloseRecordset("CRegioneForm::SaveForm");
					}
		
					if (pSet->RecordsetReOpen(bError, strFilter, "Contatore", "CRegioneForm5Righe::SaveForm"))
						pSet->DeleteRecordset("CRegioneForm5Righe::SaveForm");
				}
			}
		}

		if (bSave)
		{
			UpdateDataLine(pSet, nCounter, TRUE);

			if (nContatore)
			{
				//sono in Edit...
				*pParamSet = *pParamOfFilter;

				pSet->SetFieldDirty(pCounterSet, FALSE);
			}
			else
			{
				//sono in AddNew...
				*pParamSet = *pParamOfFilter;
				
				pSet->SetFieldDirty(pCounterSet, FALSE);
				pSet->SetFieldNull (pCounterSet, TRUE);
			}

			if (pSet->UpdateRecordset("CRegioneForm5Righe::SaveForm"))
			{
				SetLineDirty(nCounter, FALSE);
			}
			else
			{
				pSet->NoEditRecordset("CRegioneForm5Righe::SaveForm");
				
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_SUBFORM_DONT_SAVE), "CRegioneForm5Righe::SaveForm", nCounter);
				theApp.AfxMessageBoxEndo(strError);
			}

			/*if (nContatore)
			{
				//Settare lo stato a 2, ovvero DA MODIFICARE
				tempRegioneSet.SetOpenFilter(strFilter);
				if (tempRegioneSet.OpenRecordset("CRegioneForm::SaveForm"))
				{
					//Notifico la modifica solo se ho notificato l'inserimento
					if (tempRegioneSet.m_StatoCUP == 0)
					{
						tempRegioneSet.EditRecordset("CRegioneForm::SaveForm");
						tempRegioneSet.m_StatoCUP = 2;
						tempRegioneSet.UpdateRecordset("CRegioneForm::SaveForm");
						tempRegioneSet.CloseRecordset("CRegioneForm::SaveForm");
					}
				}
			}
			else
			{*/
				//Settare lo stato a 1, ovvero DA INSERIRE
				strFilter.Format("contatore = %li", pSet->GetLastAdd());
				tempRegioneSet.SetOpenFilter(strFilter);
				if (tempRegioneSet.OpenRecordset("CRegioneForm::SaveForm"))
				{
					tempRegioneSet.EditRecordset("CRegioneForm::SaveForm");
					tempRegioneSet.m_lStatoCUP = 1;
					tempRegioneSet.m_lIdExtPrestazione = 0;
					tempRegioneSet.UpdateRecordset("CRegioneForm::SaveForm");
					tempRegioneSet.CloseRecordset("CRegioneForm::SaveForm");
				}
			//}

		}
	}
}

