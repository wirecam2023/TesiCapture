#include "stdafx.h"
#include "Endox.h"
#include "TerapieTestoForm.h"

#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTerapieTestoForm::CTerapieTestoForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CTerapieTestoForm::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 3;
}

CTerapieTestoForm::~CTerapieTestoForm()
{
}

BEGIN_MESSAGE_MAP(CTerapieTestoForm, CSubForm)
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

void CTerapieTestoForm::DoDataExchange(CDataExchange* pDX)
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
			DDX_Text(pDX, nID_Durata[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sDurata);
			DDX_Text(pDX, nID_Dose[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sDose);
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);
}

void CTerapieTestoForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_terapiainatto_testo] == NULL)
	{
		pEsamiView->m_pDynForm[sub_terapiainatto_testo] = new CTerapieTestoForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_terapiainatto_testo] != NULL)
		{
			pEsamiView->m_pDynForm[sub_terapiainatto_testo]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_terapiainatto_testo]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_terapiainatto_testo]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_terapiainatto_testo]->CreateChildForm(CTerapieTestoForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CTerapieTestoForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

BOOL CTerapieTestoForm::OnInitDialog() 
{
	BOOL bResult = CSubForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_SUTE_00)->GetSafeHwnd(), CSize(0,0), CSize(50,1));
	AddAnchor(GetDlgItem(IDC_SUTE_01)->GetSafeHwnd(), CSize(50,0), CSize(75,1));
	AddAnchor(GetDlgItem(IDC_SUTE_02)->GetSafeHwnd(), CSize(75,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_SCROLL)->GetSafeHwnd(), CSize(100,0), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_NUM_1)->GetSafeHwnd(), CSize(0,1), CSize(0,34));
	AddAnchor(GetDlgItem(IDC_NUM_2)->GetSafeHwnd(), CSize(0,34), CSize(0,67));
	AddAnchor(GetDlgItem(IDC_NUM_3)->GetSafeHwnd(), CSize(0,67), CSize(0,100));
	AddAnchor(GetDlgItem(IDC_TERAPIA_1)->GetSafeHwnd(), CSize(0,1), CSize(50,34));
	AddAnchor(GetDlgItem(IDC_TERAPIA_2)->GetSafeHwnd(), CSize(0,34), CSize(50,67));
	AddAnchor(GetDlgItem(IDC_TERAPIA_3)->GetSafeHwnd(), CSize(0,67), CSize(50,100));
	AddAnchor(GetDlgItem(IDC_DURATA_1)->GetSafeHwnd(), CSize(50,17), CSize(75,17));
	AddAnchor(GetDlgItem(IDC_DURATA_2)->GetSafeHwnd(), CSize(50,50), CSize(75,50));
	AddAnchor(GetDlgItem(IDC_DURATA_3)->GetSafeHwnd(), CSize(50,83), CSize(75,83));
	AddAnchor(GetDlgItem(IDC_DOSE_1)->GetSafeHwnd(), CSize(75,17), CSize(100,17));
	AddAnchor(GetDlgItem(IDC_DOSE_2)->GetSafeHwnd(), CSize(75,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_DOSE_3)->GetSafeHwnd(), CSize(75,83), CSize(100,83));

	GetDlgItem(IDC_SUTE_00)->SetFont(&theApp.m_fontBold, TRUE);

	theApp.LocalizeDialog(this, CTerapieTestoForm::IDD, "TerapieForm");

	return bResult;
}

void CTerapieTestoForm::ModificaForm()
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
	}
}

LRESULT CTerapieTestoForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CTerapieTestoForm::OnFormClone(WPARAM wParam, LPARAM lParam)
{
	if (!theApp.m_bPersonalizzazioniBrasileCamargo && !theApp.m_bPersonalizzazioniBrasileFleury)
	{
		long lEsame = (long)lParam;
		if (lEsame > 0)
		{
			CTerapieSet setTemp;

			CString strFilter;
			strFilter.Format("Esame=%li", lEsame);

			setTemp.SetOpenFilter(strFilter);
			setTemp.SetSortRecord("Contatore");
			if (setTemp.OpenRecordset("CTerapieTestoForm::OnFormClone"))
			{
				int nIndex = 0;
				while (!setTemp.IsEOF())
				{
					m_ctrLine[nIndex].m_Set.CopyFieldFrom(&setTemp);
					m_ctrLine[nIndex].m_nStato = RECORD_FULL | RECORD_DIRTY;
					m_ctrLine[nIndex].m_nContatore = 0;

					nIndex++;
					setTemp.MoveNext();
				}

				setTemp.CloseRecordset("CTerapieTestoForm::OnFormClone");
			}
		}
	}

	return 1;
}

LRESULT CTerapieTestoForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CTerapieSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CTerapieTestoForm::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}
			setTemp.CloseRecordset("CTerapieTestoForm::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CTerapieTestoForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
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

LRESULT CTerapieTestoForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CTerapieTestoForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CTerapieSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CTerapieTestoForm::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CTerapieTestoForm::OnFormSave");
	}

	return 1;
}

LRESULT CTerapieTestoForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CTerapieSet* pSet = &m_ctrLine[0].m_Set;

	if (pSet)
		ComponiRicercaString(pStrWhere, pSet, &pSet->m_sTerapia, "ETerapie.Terapia", 3);

	return 1;
}

long CTerapieTestoForm::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CTerapieTestoForm::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CTerapieTestoForm::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_sTerapia != "");
}

void CTerapieTestoForm::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CTerapieTestoForm::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
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

void CTerapieTestoForm::OnChangeTerapia1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CTerapieTestoForm::OnChangeTerapia2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CTerapieTestoForm::OnChangeTerapia3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CTerapieTestoForm::OnChangeDurata1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CTerapieTestoForm::OnChangeDurata2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CTerapieTestoForm::OnChangeDurata3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CTerapieTestoForm::OnChangeDose1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CTerapieTestoForm::OnChangeDose2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CTerapieTestoForm::OnChangeDose3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

long CTerapieTestoForm::GetContenuto()
{
	return sub_terapiainatto;
}

BOOL CTerapieTestoForm::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}