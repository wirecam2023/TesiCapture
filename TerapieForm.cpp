#include "stdafx.h"
#include "Endox.h"
#include "TerapieForm.h"

#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTerapieForm::CTerapieForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CTerapieForm::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 3;
}

CTerapieForm::~CTerapieForm()
{
}

BEGIN_MESSAGE_MAP(CTerapieForm, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_TERAPIA_1, OnChangeTerapia1)
	ON_EN_CHANGE(IDC_TERAPIA_2, OnChangeTerapia2)
	ON_EN_CHANGE(IDC_TERAPIA_3, OnChangeTerapia3)
	ON_EN_CHANGE(IDC_DURATA_1, OnChangeDurata1)
	ON_EN_CHANGE(IDC_DURATA_2, OnChangeDurata2)
	ON_EN_CHANGE(IDC_DURATA_3, OnChangeDurata3)
	ON_EN_CHANGE(IDC_DOSE_1, OnChangeDose1)
	ON_EN_CHANGE(IDC_DOSE_2, OnChangeDose2)
	ON_EN_CHANGE(IDC_DOSE_3, OnChangeDose3)
END_MESSAGE_MAP()

void CTerapieForm::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Terapia[3] = { IDC_TERAPIA_1, IDC_TERAPIA_2, IDC_TERAPIA_3 };
	static UINT nID_Durata [3] = { IDC_DURATA_1,  IDC_DURATA_2,  IDC_DURATA_3 };
	static UINT nID_Dose   [3] = { IDC_DOSE_1,    IDC_DOSE_2,    IDC_DOSE_3 };
	static UINT nID_Numero [3] = { IDC_NUM_1,     IDC_NUM_2,     IDC_NUM_3 };
	
	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SUTE_00, m_ctrlStatic[0]);
	DDX_Control(pDX, IDC_SUTE_01, m_ctrlStatic[1]);
	DDX_Control(pDX, IDC_SUTE_02, m_ctrlStatic[2]);

	for(int i = 0; i < m_nIndexPage; i++)
	{
		if (theApp.m_bUsaProntuario)
			DDX_Control(pDX, nID_Terapia[i], m_ctrlTerapiaPront[i]);
		else
			DDX_Control(pDX, nID_Terapia[i], m_ctrlTerapiaCombo[i]);
		DDX_Control(pDX, nID_Durata[i], m_ctrlDurata[i]);
		DDX_Control(pDX, nID_Dose[i], m_ctrlDose[i]);
	}

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_Text(pDX, nID_Terapia[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sTerapia);
			DDX_Combo(pDX, nID_Durata[i], m_ctrLine[m_nIndexLine + i].m_Set.m_lDurata, CMB_ESA_TERAPIAINATTODURATA);
			DDX_Combo(pDX, nID_Dose[i], m_ctrLine[m_nIndexLine + i].m_Set.m_lDose, CMB_ESA_TERAPIAINATTODOSAGG);
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);
}

void CTerapieForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_terapiainatto] == NULL)
	{
		pEsamiView->m_pDynForm[sub_terapiainatto] = new CTerapieForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_terapiainatto] != NULL)
		{
			pEsamiView->m_pDynForm[sub_terapiainatto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_terapiainatto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_terapiainatto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_terapiainatto]->CreateChildForm(CTerapieForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CTerapieForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_SUTE_00:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_SUTE_01:
		case IDC_SUTE_02:
		case IDC_NUM_1:
		case IDC_NUM_2:
		case IDC_NUM_3:
		case IDC_TERAPIA_1:
		case IDC_TERAPIA_2:
		case IDC_TERAPIA_3:
		case IDC_DURATA_1:
		case IDC_DURATA_2:
		case IDC_DURATA_3:
		case IDC_DOSE_1:
		case IDC_DOSE_2:
		case IDC_DOSE_3:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CTerapieForm::OnInitDialog() 
{
	BOOL bResult = CSubForm::OnInitDialog();

	AddAnchor(IDC_SUTE_00, CSize(0,0), CSize(50,1));
	AddAnchor(IDC_SUTE_01, CSize(50,0), CSize(75,1));
	AddAnchor(IDC_SUTE_02, CSize(75,0), CSize(100,1));
	AddAnchor(IDC_SCROLL, CSize(100,0), CSize(100,100));
	AddAnchor(IDC_NUM_1, CSize(0,1), CSize(0,34));
	AddAnchor(IDC_NUM_2, CSize(0,34), CSize(0,67));
	AddAnchor(IDC_NUM_3, CSize(0,67), CSize(0,100));
	AddAnchor(IDC_TERAPIA_1, CSize(0,1), CSize(50,34));
	AddAnchor(IDC_TERAPIA_2, CSize(0,34), CSize(50,67));
	AddAnchor(IDC_TERAPIA_3, CSize(0,67), CSize(50,100));
	AddAnchor(IDC_DURATA_1, CSize(50,17), CSize(75,17));
	AddAnchor(IDC_DURATA_2, CSize(50,50), CSize(75,50));
	AddAnchor(IDC_DURATA_3, CSize(50,83), CSize(75,83));
	AddAnchor(IDC_DOSE_1, CSize(75,17), CSize(100,17));
	AddAnchor(IDC_DOSE_2, CSize(75,50), CSize(100,50));
	AddAnchor(IDC_DOSE_3, CSize(75,83), CSize(100,83));

	GetDlgItem(IDC_SUTE_00)->SetFont(&theApp.m_fontBold, TRUE);

	theApp.LocalizeDialog(this, CTerapieForm::IDD, "TerapieForm");

	return bResult;
}

void CTerapieForm::ModificaForm()
{
	UINT nID[] = { IDC_TERAPIA_1, IDC_TERAPIA_2, IDC_TERAPIA_3 };
	for(int i = 0; i < m_nIndexPage; i++)
	{
		if (theApp.m_bUsaProntuario)
		{
			m_ctrlTerapiaPront[i].SetParam(m_pEsamiView, GetDlgItem(nID[i]), TRUE);
		}
		else
		{
			m_ctrlTerapiaCombo[i].SetParam(this, CMB_ESA_TERAPIAINATTO, &m_ctrLine[m_nIndexLine + i].m_Set, NULL, &m_ctrLine[m_nIndexLine + i].m_Set.m_sTerapia, 255);
			m_ctrlTerapiaCombo[i].SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);
		}

		m_ctrlDurata[i].SetParam(this, CMB_ESA_TERAPIAINATTODURATA, &m_ctrLine[m_nIndexLine + i].m_Set, NULL, &m_ctrLine[m_nIndexLine + i].m_Set.m_lDurata, 255);
		m_ctrlDurata[i].SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);

		m_ctrlDose[i].SetParam(this, CMB_ESA_TERAPIAINATTODOSAGG, &m_ctrLine[m_nIndexLine + i].m_Set, NULL, &m_ctrLine[m_nIndexLine + i].m_Set.m_lDose, 255);
		m_ctrlDose[i].SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);
	}
}

LRESULT CTerapieForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CTerapieForm::OnFormClone(WPARAM wParam, LPARAM lParam)
{
	long lEsame = (long)lParam;
	if (lEsame > 0)
	{
		CTerapieSet setTemp;

		CString strFilter;
		strFilter.Format("Esame=%li", lEsame);

		setTemp.SetOpenFilter(strFilter);
		setTemp.SetSortRecord("Contatore");
		if (setTemp.OpenRecordset("CTerapieForm::OnFormClone"))
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

			setTemp.CloseRecordset("CTerapieForm::OnFormClone");
		}
	}

	return 1;
}

LRESULT CTerapieForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CTerapieSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CTerapieForm::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}
			setTemp.CloseRecordset("CTerapieForm::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CTerapieForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)))
	{
		static UINT pControlID[] = {
			IDC_TERAPIA_1
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
			IDC_TERAPIA_1,
			IDC_DURATA_1,
			IDC_DOSE_1,
			IDC_TERAPIA_2,
			IDC_DURATA_2,
			IDC_DOSE_2,
			IDC_TERAPIA_3,
			IDC_DURATA_3,
			IDC_DOSE_3
		};

		for(i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID[i], EM_SETREADONLY, wParam, lParam);

		GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);
	}

	return 1;
}

LRESULT CTerapieForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CTerapieForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CTerapieSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CTerapieForm::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CTerapieForm::OnFormSave");
	}

	return 1;
}

LRESULT CTerapieForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CTerapieSet* pSet = &m_ctrLine[0].m_Set;

	if (pSet)
		ComponiRicercaString(pStrWhere, pSet, &pSet->m_sTerapia, "ETerapie.Terapia", 3);

	return 1;
}

long CTerapieForm::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CTerapieForm::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CTerapieForm::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_sTerapia != "");
}

void CTerapieForm::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CTerapieForm::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CTerapieSet* pSet = (CTerapieSet*)pBaseSet;
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

void CTerapieForm::OnChangeTerapia1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CTerapieForm::OnChangeTerapia2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CTerapieForm::OnChangeTerapia3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CTerapieForm::OnChangeDurata1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CTerapieForm::OnChangeDurata2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CTerapieForm::OnChangeDurata3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CTerapieForm::OnChangeDose1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CTerapieForm::OnChangeDose2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CTerapieForm::OnChangeDose3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

long CTerapieForm::GetContenuto()
{
	return sub_terapiainatto;
}

BOOL CTerapieForm::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}