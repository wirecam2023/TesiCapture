#include "stdafx.h"
#include "Endox.h"
#include "AccessoriForm5Righe.h"

#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAccessoriForm5Righe::CAccessoriForm5Righe(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CAccessoriForm5Righe::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 5;

	m_nSearchMode = 2;
}

CAccessoriForm5Righe::~CAccessoriForm5Righe()
{
}

BEGIN_MESSAGE_MAP(CAccessoriForm5Righe, CSubForm)
	ON_WM_CTLCOLOR()

	ON_CBN_EDITCHANGE(IDC_ACCESSORIO_1, OnChangeAccessorio1)
	ON_CBN_SELCHANGE(IDC_ACCESSORIO_1, OnChangeAccessorio1)
	ON_CBN_EDITCHANGE(IDC_ACCESSORIO_2, OnChangeAccessorio2)
	ON_CBN_SELCHANGE(IDC_ACCESSORIO_2, OnChangeAccessorio2)
	ON_CBN_EDITCHANGE(IDC_ACCESSORIO_3, OnChangeAccessorio3)
	ON_CBN_SELCHANGE(IDC_ACCESSORIO_3, OnChangeAccessorio3)
	ON_CBN_EDITCHANGE(IDC_ACCESSORIO_4, OnChangeAccessorio4)
	ON_CBN_SELCHANGE(IDC_ACCESSORIO_4, OnChangeAccessorio4)
	ON_CBN_EDITCHANGE(IDC_ACCESSORIO_5, OnChangeAccessorio5)
	ON_CBN_SELCHANGE(IDC_ACCESSORIO_5, OnChangeAccessorio5)
	ON_EN_CHANGE(IDC_QTA_1, OnChangeQta1)
	ON_EN_CHANGE(IDC_QTA_2, OnChangeQta2)
	ON_EN_CHANGE(IDC_QTA_3, OnChangeQta3)
	ON_EN_CHANGE(IDC_QTA_4, OnChangeQta4)
	ON_EN_CHANGE(IDC_QTA_5, OnChangeQta5)

	ON_BN_CLICKED(IDC_BTN_RESET, OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_RADIO_AND, OnBnClickedRadioAnd)
	ON_BN_CLICKED(IDC_RADIO_OR, OnBnClickedRadioOr)
END_MESSAGE_MAP()

void CAccessoriForm5Righe::DoDataExchange(CDataExchange* pDX)
{
	CSubForm::DoDataExchange(pDX);
	static UINT nID_Numero [5] = { IDC_NUM_1, IDC_NUM_2, IDC_NUM_3, IDC_NUM_4, IDC_NUM_5 };
	static UINT nID_Accessorio[5] = { IDC_ACCESSORIO_1, IDC_ACCESSORIO_2, IDC_ACCESSORIO_3, IDC_ACCESSORIO_4, IDC_ACCESSORIO_5 };
	static UINT nID_Qta    [5] = { IDC_QTA_1, IDC_QTA_2, IDC_QTA_3, IDC_QTA_4, IDC_QTA_5 };

	DDX_Control(pDX, IDC_SURE_00, m_ctrlStatic);

	for(int i = 0; i < m_nIndexPage; i++)
		DDX_Control(pDX, nID_Accessorio[i], m_ctrlAccessori[i]);

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_Accessori(pDX, nID_Accessorio[i], m_ctrLine[m_nIndexLine+i].m_Set.m_lCodice);
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

	DDX_Control(pDX, IDC_BTN_RESET, m_ctrlButtonReset);

	//DDX_Radio(pDX, IDC_RADIO_AND, m_nSearchMode);
}

void CAccessoriForm5Righe::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_accessori5righe] == NULL)
	{
		pEsamiView->m_pDynForm[sub_accessori5righe] = new CAccessoriForm5Righe(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_accessori5righe] != NULL)
		{
			pEsamiView->m_pDynForm[sub_accessori5righe]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_accessori5righe]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_accessori5righe]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_accessori5righe]->CreateChildForm(CAccessoriForm5Righe::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CAccessoriForm5Righe::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		case IDC_ACCESSORIO_1:
		case IDC_ACCESSORIO_2:
		case IDC_ACCESSORIO_3:
		case IDC_ACCESSORIO_4:
		case IDC_ACCESSORIO_5:
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

BOOL CAccessoriForm5Righe::OnInitDialog() 
{
	BOOL bResult = CSubForm::OnInitDialog();
	
	AddAnchor(IDC_SURE_00, CSize(0,25), CSize(40,25));
	AddAnchor(IDC_SURE_01, CSize(0,0), CSize(100,100));
	AddAnchor(IDC_RADIO_AND, CSize(40,20), CSize(45,30));
	AddAnchor(IDC_RADIO_OR, CSize(45,20), CSize(50,30));
	AddAnchor(IDC_BTN_RESET, CSize(75,20), CSize(100,30));
	AddAnchor(IDC_SCROLL, CSize(100,50), CSize(100,100));
	AddAnchor(IDC_NUM_1, CSize(0,60), CSize(0,60));
	AddAnchor(IDC_NUM_2, CSize(0,70), CSize(0,70));
	AddAnchor(IDC_NUM_3, CSize(0,80), CSize(0,80));
	AddAnchor(IDC_NUM_4, CSize(0,90), CSize(0,90));
	AddAnchor(IDC_NUM_5, CSize(0,100), CSize(0,100));
	AddAnchor(IDC_ACCESSORIO_1, CSize(0,60), CSize(100,60));
	AddAnchor(IDC_ACCESSORIO_2, CSize(0,70), CSize(100,70));
	AddAnchor(IDC_ACCESSORIO_3, CSize(0,80), CSize(100,80));
	AddAnchor(IDC_ACCESSORIO_4, CSize(0,90), CSize(100,90));
	AddAnchor(IDC_ACCESSORIO_5, CSize(0,100), CSize(100,100));
	AddAnchor(IDC_QTA_1, CSize(100,60), CSize(100,60));
	AddAnchor(IDC_QTA_2, CSize(100,70), CSize(100,70));
	AddAnchor(IDC_QTA_3, CSize(100,80), CSize(100,80));
	AddAnchor(IDC_QTA_4, CSize(100,90), CSize(100,90));
	AddAnchor(IDC_QTA_5, CSize(100,100), CSize(100,100));

	GetDlgItem(IDC_SURE_00)->SetFont(&theApp.m_fontBold, TRUE);

	theApp.LocalizeDialog(this, CAccessoriForm5Righe::IDD, "AccessoriForm");

	return bResult;
}

void CAccessoriForm5Righe::ModificaForm()
{
	/* Sandro 22/12/2015
	for(int i = 0; i < m_nIndexPage; i++)
		m_ctrlAccessori[i].SetParam(&m_ctrLine[m_nIndexLine+i].m_Set.m_lCodice, m_pEsamiView, m_pAccessoriSet);
	*/
}

LRESULT CAccessoriForm5Righe::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CAccessoriForm5Righe::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CEsamiAccessoriSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CAccessoriForm5Righe::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CAccessoriForm5Righe::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CAccessoriForm5Righe::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
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
		IDC_ACCESSORIO_1,
		IDC_ACCESSORIO_2,
		IDC_ACCESSORIO_3,
		IDC_ACCESSORIO_4,
		IDC_ACCESSORIO_5,
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

LRESULT CAccessoriForm5Righe::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CAccessoriForm5Righe::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CEsamiAccessoriSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CAccessoriForm5Righe::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CAccessoriForm5Righe::OnFormSave");
	}

	return 1;
}

LRESULT CAccessoriForm5Righe::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
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
				ComponiRicercaNewLong(pStrFrom, &strTempWhere, "EsamiAccessori", i, "Esame", "Codice", m_ctrLine[i].m_Set.m_lCodice, m_nSearchMode, MODE_UGUALE);

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

long CAccessoriForm5Righe::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CAccessoriForm5Righe::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_lCodice != 0);
}

void CAccessoriForm5Righe::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CEsamiAccessoriSet* pSet = (CEsamiAccessoriSet*)pBaseSet;
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

BOOL CAccessoriForm5Righe::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

void CAccessoriForm5Righe::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CAccessoriForm5Righe::OnChangeAccessorio1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);

	CString strValore;

	GetDlgItem(IDC_QTA_1)->GetWindowText(strValore);
	if (strValore == "" || strValore == "0")
		GetDlgItem(IDC_QTA_1)->SetWindowText("1");

	GetDlgItem(IDC_ACCESSORIO_1)->GetWindowText(strValore);
	if (strValore == "")
		GetDlgItem(IDC_QTA_1)->SetWindowText("");
}

void CAccessoriForm5Righe::OnChangeAccessorio2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);

	CString strValore;

	GetDlgItem(IDC_QTA_2)->GetWindowText(strValore);
	if (strValore == "" || strValore == "0")
		GetDlgItem(IDC_QTA_2)->SetWindowText("1");

	GetDlgItem(IDC_ACCESSORIO_2)->GetWindowText(strValore);
	if (strValore == "")
		GetDlgItem(IDC_QTA_2)->SetWindowText("");
}

void CAccessoriForm5Righe::OnChangeAccessorio3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);

	CString strValore;

	GetDlgItem(IDC_QTA_3)->GetWindowText(strValore);
	if (strValore == "" || strValore == "0")
		GetDlgItem(IDC_QTA_3)->SetWindowText("1");

	GetDlgItem(IDC_ACCESSORIO_3)->GetWindowText(strValore);
	if (strValore == "")
		GetDlgItem(IDC_QTA_3)->SetWindowText("");
}

void CAccessoriForm5Righe::OnChangeAccessorio4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);

	CString strValore;

	GetDlgItem(IDC_QTA_4)->GetWindowText(strValore);
	if (strValore == "" || strValore == "0")
		GetDlgItem(IDC_QTA_4)->SetWindowText("1");

	GetDlgItem(IDC_ACCESSORIO_4)->GetWindowText(strValore);
	if (strValore == "")
		GetDlgItem(IDC_QTA_4)->SetWindowText("");
}

void CAccessoriForm5Righe::OnChangeAccessorio5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);

	CString strValore;

	GetDlgItem(IDC_QTA_5)->GetWindowText(strValore);
	if (strValore == "" || strValore == "0")
		GetDlgItem(IDC_QTA_5)->SetWindowText("1");

	GetDlgItem(IDC_ACCESSORIO_5)->GetWindowText(strValore);
	if (strValore == "")
		GetDlgItem(IDC_QTA_5)->SetWindowText("");
}

void CAccessoriForm5Righe::OnChangeQta1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CAccessoriForm5Righe::OnChangeQta2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CAccessoriForm5Righe::OnChangeQta3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CAccessoriForm5Righe::OnChangeQta4()
{
	SetLineDirty(m_nIndexLine+3, TRUE);
}

void CAccessoriForm5Righe::OnChangeQta5()
{
	SetLineDirty(m_nIndexLine+4, TRUE);
}

long CAccessoriForm5Righe::GetContenuto()
{
	return sub_accessori5righe;
}

BOOL CAccessoriForm5Righe::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}

void CAccessoriForm5Righe::OnBnClickedBtnReset()
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

void CAccessoriForm5Righe::OnBnClickedRadioAnd()
{
	m_nSearchMode = 2;
}

void CAccessoriForm5Righe::OnBnClickedRadioOr()
{
	m_nSearchMode = 1;
}
