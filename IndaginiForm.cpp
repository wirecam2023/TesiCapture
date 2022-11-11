#include "stdafx.h"
#include "Endox.h"
#include "IndaginiForm.h"

#include "EsamiView.h"
#include "Common.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CIndaginiForm::CIndaginiForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CIndaginiForm::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 3;
}

CIndaginiForm::~CIndaginiForm()
{
}

BEGIN_MESSAGE_MAP(CIndaginiForm, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_INDAGINE_1, OnChangeIndagine1)
	ON_EN_CHANGE(IDC_INDAGINE_2, OnChangeIndagine2)
	ON_EN_CHANGE(IDC_INDAGINE_3, OnChangeIndagine3)
	ON_BN_CLICKED(IDC_PATOLOGICO_1, OnChangePatologico1)
	ON_BN_CLICKED(IDC_PATOLOGICO_2, OnChangePatologico2)
	ON_BN_CLICKED(IDC_PATOLOGICO_3, OnChangePatologico3)
END_MESSAGE_MAP()

void CIndaginiForm::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Indagine  [3] = { IDC_INDAGINE_1,   IDC_INDAGINE_2,   IDC_INDAGINE_3 };
	static UINT nID_Patologico[3] = { IDC_PATOLOGICO_1, IDC_PATOLOGICO_2, IDC_PATOLOGICO_3 };
	static UINT nID_Numero    [3] = { IDC_NUM_1,        IDC_NUM_2,        IDC_NUM_3 };
	
	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SUIN_00, m_ctrlStatic[0]);
	DDX_Control(pDX, IDC_SUIN_01, m_ctrlStatic[1]);

	for(int i = 0; i < m_nIndexPage; i++)
		DDX_Control(pDX, nID_Indagine[i], m_ctrlIndagine[i]);

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_Text (pDX, nID_Indagine  [i],	m_ctrLine[m_nIndexLine+i].m_Set.m_sIndagine);
			DDX_Check(pDX, nID_Patologico[i],	(int&)m_ctrLine[m_nIndexLine+i].m_Set.m_lPatologico);
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);
}

void CIndaginiForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_indagini] == NULL)
	{
		pEsamiView->m_pDynForm[sub_indagini] = new CIndaginiForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_indagini] != NULL)
		{
			pEsamiView->m_pDynForm[sub_indagini]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_indagini]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_indagini]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_indagini]->CreateChildForm(CIndaginiForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CIndaginiForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_SUIN_00:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_SUIN_01:
		case IDC_NUM_1:
		case IDC_NUM_2:
		case IDC_NUM_3:
		case IDC_INDAGINE_1:
		case IDC_INDAGINE_2:
		case IDC_INDAGINE_3:
		case IDC_PATOLOGICO_1:
		case IDC_PATOLOGICO_2:
		case IDC_PATOLOGICO_3:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CIndaginiForm::OnInitDialog() 
{
	BOOL bResult = CSubForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_SUIN_00)->GetSafeHwnd(), CSize(0,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_SUIN_01)->GetSafeHwnd(), CSize(100,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_SCROLL)->GetSafeHwnd(), CSize(100,0), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_NUM_1)->GetSafeHwnd(), CSize(0,1), CSize(0,34));
	AddAnchor(GetDlgItem(IDC_NUM_2)->GetSafeHwnd(), CSize(0,34), CSize(0,67));
	AddAnchor(GetDlgItem(IDC_NUM_3)->GetSafeHwnd(), CSize(0,67), CSize(0,100));
	AddAnchor(GetDlgItem(IDC_INDAGINE_1)->GetSafeHwnd(), CSize(0,1), CSize(100,34));
	AddAnchor(GetDlgItem(IDC_INDAGINE_2)->GetSafeHwnd(), CSize(0,34), CSize(100,67));
	AddAnchor(GetDlgItem(IDC_INDAGINE_3)->GetSafeHwnd(), CSize(0,67), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_PATOLOGICO_1)->GetSafeHwnd(), CSize(100,17), CSize(100,17));
	AddAnchor(GetDlgItem(IDC_PATOLOGICO_2)->GetSafeHwnd(), CSize(100,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_PATOLOGICO_3)->GetSafeHwnd(), CSize(100,83), CSize(100,83));

	GetDlgItem(IDC_SUIN_00)->SetFont(&theApp.m_fontBold, TRUE);

	theApp.LocalizeDialog(this, CIndaginiForm::IDD, "IndaginiForm");

	return bResult;
}

void CIndaginiForm::ModificaForm()
{
	for(int i = 0; i < m_nIndexPage; i++)
	{
		m_ctrlIndagine[i].SetParam(this, CMB_ANA_INDAGINE, &m_ctrLine[m_nIndexLine + i].m_Set, NULL, &m_ctrLine[m_nIndexLine + i].m_Set.m_sIndagine, 255);
		m_ctrlIndagine[i].SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);
	}
}

LRESULT CIndaginiForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CIndaginiForm::OnFormClone(WPARAM wParam, LPARAM lParam)
{
	long lEsame = (long)lParam;
	if (lEsame > 0)
	{
		CIndaginiPregresseSet setTemp;

		CString strFilter;
		strFilter.Format("Esame=%li", lEsame);

		setTemp.SetOpenFilter(strFilter);
		setTemp.SetSortRecord("Contatore");
		if (setTemp.OpenRecordset("CIndaginiForm::OnFormClone"))
		{
			int nIndex = 0;
			while(!setTemp.IsEOF())
			{
				m_ctrLine[nIndex].m_Set.CopyFieldFrom(&setTemp);
				m_ctrLine[nIndex].m_nStato = RECORD_FULL | RECORD_DIRTY;
				m_ctrLine[nIndex].m_nContatore = 0;

				nIndex++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CIndaginiForm::OnFormClone");
		}
	}

	return 1;
}

LRESULT CIndaginiForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CIndaginiPregresseSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CIndaginiForm::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CIndaginiForm::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CIndaginiForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)))
	{
		static UINT pControlID[] = {
			IDC_INDAGINE_1
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
			IDC_INDAGINE_1,
			IDC_INDAGINE_2,
			IDC_INDAGINE_3
		};

		static UINT pControlID2[] = {
			IDC_PATOLOGICO_1,
			IDC_PATOLOGICO_2,
			IDC_PATOLOGICO_3
		};

		for(i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID[i], EM_SETREADONLY, wParam, lParam);

		for(i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			GetDlgItem(pControlID2[i])->EnableWindow(!(BOOL)wParam);

		GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);
	}

	return 1;
}

LRESULT CIndaginiForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CIndaginiForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CIndaginiPregresseSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CIndaginiForm::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CIndaginiForm::OnFormSave");
	}

	return 1;
}

LRESULT CIndaginiForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CIndaginiPregresseSet* pSet = &m_ctrLine[0].m_Set;

	if (pSet)
		ComponiRicercaString(pStrWhere, pSet, &pSet->m_sIndagine, "EIndaginiPregresse.Indagine", 1);

	return 1;
}

long CIndaginiForm::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CIndaginiForm::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CIndaginiForm::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_sIndagine != "");
}

void CIndaginiForm::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CIndaginiForm::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CIndaginiPregresseSet* pSet = (CIndaginiPregresseSet*)pBaseSet;
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

void CIndaginiForm::OnChangeIndagine1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIndaginiForm::OnChangeIndagine2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIndaginiForm::OnChangeIndagine3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CIndaginiForm::OnChangePatologico1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CIndaginiForm::OnChangePatologico2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CIndaginiForm::OnChangePatologico3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

long CIndaginiForm::GetContenuto()
{
	return sub_indagini;
}

BOOL CIndaginiForm::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}