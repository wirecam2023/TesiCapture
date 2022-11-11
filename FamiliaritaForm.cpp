#include "stdafx.h"
#include "Endox.h"
#include "FamiliaritaForm.h"

#include "ComboBoxSet.h"
#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "PazientiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFamiliaritaForm::CFamiliaritaForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CFamiliaritaForm::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 3;
}

CFamiliaritaForm::~CFamiliaritaForm()
{
}

BEGIN_MESSAGE_MAP(CFamiliaritaForm, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_FAMILIARITA_1, OnChangeFamiliarita1)
	ON_EN_CHANGE(IDC_FAMILIARITA_2, OnChangeFamiliarita2)
	ON_EN_CHANGE(IDC_FAMILIARITA_3, OnChangeFamiliarita3)
	ON_EN_CHANGE(IDC_PARENTELA_1, OnChangeParentela1)
	ON_EN_CHANGE(IDC_PARENTELA_2, OnChangeParentela2)
	ON_EN_CHANGE(IDC_PARENTELA_3, OnChangeParentela3)
END_MESSAGE_MAP()

void CFamiliaritaForm::DoDataExchange(CDataExchange* pDX)
{
	static 	UINT nID_Familiarita[] = {IDC_FAMILIARITA_1, IDC_FAMILIARITA_2, IDC_FAMILIARITA_3};
	static 	UINT nID_Parentela  [] = {IDC_PARENTELA_1,   IDC_PARENTELA_2,   IDC_PARENTELA_3  };
	static 	UINT nID_Numero     [] = {IDC_NUM_1,         IDC_NUM_2,         IDC_NUM_3        };
	
	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SUFA_00, m_ctrlStatic[0]);
	DDX_Control(pDX, IDC_SUFA_01, m_ctrlStatic[1]);

	for(int i = 0; i < m_nIndexPage; i++)
	{
		DDX_Control(pDX, nID_Familiarita[i], m_ctrlFamiliarita[i]);
		DDX_Control(pDX, nID_Parentela[i], m_ctrlParentela[i]);
	}

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_Text(pDX, nID_Familiarita[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sFamiliarita);
			DDX_Combo(pDX, nID_Parentela[i], m_ctrLine[m_nIndexLine + i].m_Set.m_lParentela, CMB_PAZ_PARENTELA);
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);
}

void CFamiliaritaForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_familiarita] == NULL)
	{
		pEsamiView->m_pDynForm[sub_familiarita] = new CFamiliaritaForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_familiarita] != NULL)
		{
			pEsamiView->m_pDynForm[sub_familiarita]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_familiarita]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_familiarita]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_familiarita]->CreateChildForm(CFamiliaritaForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CFamiliaritaForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_SUFA_00:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_SUFA_01:
		case IDC_NUM_1:
		case IDC_NUM_2:
		case IDC_NUM_3:
		case IDC_FAMILIARITA_1:
		case IDC_FAMILIARITA_2:
		case IDC_FAMILIARITA_3:
		case IDC_PARENTELA_1:
		case IDC_PARENTELA_2:
		case IDC_PARENTELA_3:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CFamiliaritaForm::OnInitDialog() 
{
	BOOL bResult = CSubForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_SUFA_00)->GetSafeHwnd(), CSize(0,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_SUFA_01)->GetSafeHwnd(), CSize(100,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_SCROLL)->GetSafeHwnd(), CSize(100,0), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_NUM_1)->GetSafeHwnd(), CSize(0,1), CSize(0,34));
	AddAnchor(GetDlgItem(IDC_NUM_2)->GetSafeHwnd(), CSize(0,34), CSize(0,67));
	AddAnchor(GetDlgItem(IDC_NUM_3)->GetSafeHwnd(), CSize(0,67), CSize(0,100));
	AddAnchor(GetDlgItem(IDC_FAMILIARITA_1)->GetSafeHwnd(), CSize(0,1), CSize(100,34));
	AddAnchor(GetDlgItem(IDC_FAMILIARITA_2)->GetSafeHwnd(), CSize(0,34), CSize(100,67));
	AddAnchor(GetDlgItem(IDC_FAMILIARITA_3)->GetSafeHwnd(), CSize(0,67), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_PARENTELA_1)->GetSafeHwnd(), CSize(100,17), CSize(100,17));
	AddAnchor(GetDlgItem(IDC_PARENTELA_2)->GetSafeHwnd(), CSize(100,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_PARENTELA_3)->GetSafeHwnd(), CSize(100,83), CSize(100,83));

	GetDlgItem(IDC_SUFA_00)->SetFont(&theApp.m_fontBold, TRUE);

	theApp.LocalizeDialog(this, CFamiliaritaForm::IDD, "FamiliaritaForm");

	return bResult;
}

void CFamiliaritaForm::ModificaForm()
{
	for(int i = 0; i < m_nIndexPage; i++)
	{
		m_ctrlFamiliarita[i].SetParam(this, CMB_PAZ_FAMILIARI, &m_ctrLine[m_nIndexLine + i].m_Set, NULL, &m_ctrLine[m_nIndexLine + i].m_Set.m_sFamiliarita, 255);
		m_ctrlFamiliarita[i].SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);

		m_ctrlParentela[i].SetParam(this, CMB_PAZ_PARENTELA, &m_ctrLine[m_nIndexLine + i].m_Set, NULL, &m_ctrLine[m_nIndexLine + i].m_Set.m_lParentela, 255);
		m_ctrlParentela[i].SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);
	}
}

LRESULT CFamiliaritaForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CFamiliaritaForm::OnFormAnnullaPaziente(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CFamiliaritaForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pPazientiSet->IsOpen() && !m_pEsamiView->m_pPazientiSet->IsFieldNull(&m_pEsamiView->m_pPazientiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Paziente=%li", m_pEsamiView->m_pPazientiSet->m_lContatore);

		CFamiliaritaSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CFamiliaritaForm::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CFamiliaritaForm::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CFamiliaritaForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)))
	{
		static UINT pControlID[] = {
			IDC_FAMILIARITA_1
		};

		for(i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID[i], EM_SETREADONLY, wParam, lParam);

		m_ctrlScroll.SetScrollPos(0);
		GetDlgItem(IDC_SCROLL)->EnableWindow(FALSE);

		m_nIndexLine = 0;

		ModificaForm();

		UpdateData(FALSE);
	}
	else
	{
		static UINT pControlID[] = {
			IDC_FAMILIARITA_1,
			IDC_PARENTELA_1,
			IDC_FAMILIARITA_2,
			IDC_PARENTELA_2,
			IDC_FAMILIARITA_3,
			IDC_PARENTELA_3
		};

		for(i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID[i], EM_SETREADONLY, wParam, lParam);

		GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);
	}

	return 1;
}

LRESULT CFamiliaritaForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CFamiliaritaForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CFamiliaritaSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CFamiliaritaForm::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lPaziente, &setTemp, &setTemp.m_lContatore, &setTemp.m_lPaziente);
		setTemp.CloseRecordset("CFamiliaritaForm::OnFormSave");
	}

	return 1;
}

LRESULT CFamiliaritaForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CFamiliaritaSet* pSet = &m_ctrLine[0].m_Set;

	ComponiRicercaString(pStrWhere, pSet, &pSet->m_sFamiliarita, "EFamiliarita.Familiarita", 1);

	// Sandro 15/02/2012 //
	if (pStrWhere->Find("EFamiliarita.Familiarita") > 0)
	{
		CString strTempFilter;
		strTempFilter.Format("EFamiliarita.UO=%li", theApp.m_lUO);

		*pStrWhere += " AND ";
		*pStrWhere += strTempFilter;
	}

	//
	return 1;
}


long CFamiliaritaForm::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CFamiliaritaForm::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CFamiliaritaForm::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_sFamiliarita  != "");
}

void CFamiliaritaForm::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CFamiliaritaForm::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CFamiliaritaSet* pSet = (CFamiliaritaSet*)pBaseSet;
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

void CFamiliaritaForm::OnChangeFamiliarita1()
{
	SetLineDirty(m_nIndexLine + 0, TRUE);
}

void CFamiliaritaForm::OnChangeFamiliarita2()
{
	SetLineDirty(m_nIndexLine + 1, TRUE);
}

void CFamiliaritaForm::OnChangeFamiliarita3()
{
	SetLineDirty(m_nIndexLine + 2, TRUE);
}

void CFamiliaritaForm::OnChangeParentela1()
{
	SetLineDirty(m_nIndexLine + 0, TRUE);
}

void CFamiliaritaForm::OnChangeParentela2()
{
	SetLineDirty(m_nIndexLine + 1, TRUE);
}

void CFamiliaritaForm::OnChangeParentela3()
{
	SetLineDirty(m_nIndexLine + 2, TRUE);
}

long CFamiliaritaForm::GetContenuto()
{
	return sub_familiarita;
}

BOOL CFamiliaritaForm::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}
