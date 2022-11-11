#include "stdafx.h"
#include "Endox.h"
#include "MalattieForm.h"

#include "Common.h"
#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMalattieForm::CMalattieForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CMalattieForm::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 3;
}

CMalattieForm::~CMalattieForm()
{
}

BEGIN_MESSAGE_MAP(CMalattieForm, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_MALATTIA_1, OnChangeMalattie1)
	ON_EN_CHANGE(IDC_MALATTIA_2, OnChangeMalattie2)
	ON_EN_CHANGE(IDC_MALATTIA_3, OnChangeMalattie3)
	ON_EN_CHANGE(IDC_EPISODI_1, OnChangeEpisodi1)
	ON_EN_CHANGE(IDC_EPISODI_2, OnChangeEpisodi2)
	ON_EN_CHANGE(IDC_EPISODI_3, OnChangeEpisodi3)
	ON_EN_CHANGE(IDC_CLASSE_1, OnChangeClasse1)
	ON_EN_CHANGE(IDC_CLASSE_2, OnChangeClasse2)
	ON_EN_CHANGE(IDC_CLASSE_3, OnChangeClasse3)
END_MESSAGE_MAP()

void CMalattieForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_malattie] == NULL)
	{
		pEsamiView->m_pDynForm[sub_malattie] = new CMalattieForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_malattie] != NULL)
		{
			pEsamiView->m_pDynForm[sub_malattie]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_malattie]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_malattie]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_malattie]->CreateChildForm(CMalattieForm::IDD, pParent, rectFrame);
		}
	}
}

void CMalattieForm::DoDataExchange(CDataExchange* pDX)
{
	static 	UINT nID_Numero  [3] = { IDC_NUM_1,        IDC_NUM_2,	   IDC_NUM_3 };
	static 	UINT nID_Malattia[3] = { IDC_MALATTIA_1,   IDC_MALATTIA_2, IDC_MALATTIA_3 };
	static 	UINT nID_Data    [3] = { IDC_CLASSE_1,     IDC_CLASSE_2,   IDC_CLASSE_3 };
	static 	UINT nID_Episodi [3] = { IDC_EPISODI_1,    IDC_EPISODI_2,  IDC_EPISODI_3 };
	
	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SUMA_00, m_ctrlStatic[0]);
	DDX_Control(pDX, IDC_SUMA_01, m_ctrlStatic[1]);
	DDX_Control(pDX, IDC_SUMA_02, m_ctrlStatic[2]);

	for(int i = 0; i < m_nIndexPage; i++)
	{
		DDX_Control(pDX, nID_Malattia[i], m_ctrlMalattie[i]);
		DDX_Control(pDX, nID_Data[i], m_ctrlData[i]);
	}

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_Text(pDX, nID_Malattia[i], m_ctrLine[m_nIndexLine + i].m_Set.m_sMalattia);
			DDX_DateMask(pDX, nID_Data[i], m_ctrLine[m_nIndexLine + i].m_Set.m_lClasse, m_ctrLine[m_nIndexLine + i].m_Set.GetRecordset());

			if (pDX->m_bSaveAndValidate == TRUE)
			{
				CString strTemp;
				GetDlgItemText(nID_Episodi[i], strTemp);

				if (strTemp.IsEmpty() == FALSE)
					DDX_Text(pDX, nID_Episodi[i], m_ctrLine[m_nIndexLine + i].m_Set.m_lEpisodi);
				else
					m_ctrLine[m_nIndexLine + i].m_Set.m_lEpisodi = 0;
			}
			else
			{
				if (m_ctrLine[m_nIndexLine + i].m_Set.m_lEpisodi > 0)
					DDX_Text(pDX, nID_Episodi[i], m_ctrLine[m_nIndexLine + i].m_Set.m_lEpisodi);
				else
					SetDlgItemText(nID_Episodi[i], "");
			}
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);
}

HBRUSH CMalattieForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_SUMA_00:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_SUMA_01:
		case IDC_SUMA_02:
		case IDC_NUM_1:
		case IDC_NUM_2:
		case IDC_NUM_3:
		case IDC_MALATTIA_1:
		case IDC_MALATTIA_2:
		case IDC_MALATTIA_3:
		case IDC_EPISODI_1:
		case IDC_EPISODI_2:
		case IDC_EPISODI_3:
		case IDC_CLASSE_1:
		case IDC_CLASSE_2:
		case IDC_CLASSE_3:
		case IDC_LABEL:
		case IDC_STATIC_EPIS:
		case IDC_STATIC_DATA:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CMalattieForm::OnInitDialog() 
{
	BOOL bResult = CSubForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_SUMA_00)->GetSafeHwnd(), CSize(0,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_SUMA_01)->GetSafeHwnd(), CSize(100,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_SUMA_02)->GetSafeHwnd(), CSize(100,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_SCROLL)->GetSafeHwnd(), CSize(100,0), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_NUM_1)->GetSafeHwnd(), CSize(0,1), CSize(0,34));
	AddAnchor(GetDlgItem(IDC_NUM_2)->GetSafeHwnd(), CSize(0,34), CSize(0,67));
	AddAnchor(GetDlgItem(IDC_NUM_3)->GetSafeHwnd(), CSize(0,67), CSize(0,100));
	AddAnchor(GetDlgItem(IDC_MALATTIA_1)->GetSafeHwnd(), CSize(0,1), CSize(100,34));
	AddAnchor(GetDlgItem(IDC_MALATTIA_2)->GetSafeHwnd(), CSize(0,34), CSize(100,67));
	AddAnchor(GetDlgItem(IDC_MALATTIA_3)->GetSafeHwnd(), CSize(0,67), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_EPISODI_1)->GetSafeHwnd(), CSize(100,17), CSize(100,17));
	AddAnchor(GetDlgItem(IDC_EPISODI_2)->GetSafeHwnd(), CSize(100,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_EPISODI_3)->GetSafeHwnd(), CSize(100,83), CSize(100,83));
	AddAnchor(GetDlgItem(IDC_CLASSE_1)->GetSafeHwnd(), CSize(100,17), CSize(100,17));
	AddAnchor(GetDlgItem(IDC_CLASSE_2)->GetSafeHwnd(), CSize(100,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_CLASSE_3)->GetSafeHwnd(), CSize(100,83), CSize(100,83));

	GetDlgItem(IDC_SUMA_00)->SetFont(&theApp.m_fontBold, TRUE);

	for(int i = 0; i < m_nIndexPage; i++)
		m_ctrlData[i].SetEditMask("00/00/0000", "__/__/____");

	theApp.LocalizeDialog(this, CMalattieForm::IDD, "MalattieForm");

	return bResult;
}

void CMalattieForm::ModificaForm()
{
	for(int i=0; i<m_nIndexPage; i++)
	{
		m_ctrlMalattie[i].SetParam(this, CMB_ANA_MALATTIE, &m_ctrLine[m_nIndexLine + i].m_Set, NULL, &m_ctrLine[m_nIndexLine + i].m_Set.m_sMalattia, 255);
		m_ctrlMalattie[i].SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);
	}
}

LRESULT CMalattieForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CMalattieForm::OnFormClone(WPARAM wParam, LPARAM lParam)
{
	long lEsame = (long)lParam;
	if (lEsame > 0)
	{
		CMalattieSet setTemp;

		CString strFilter;
		strFilter.Format("Esame=%li", lEsame);

		setTemp.SetOpenFilter(strFilter);
		setTemp.SetSortRecord("Contatore");
		if (setTemp.OpenRecordset("CMalattieForm::OnFormClone"))
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

			setTemp.CloseRecordset("CMalattieForm::OnFormClone");
		}
	}

	return 1;
}

LRESULT CMalattieForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CMalattieSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CMalattieForm::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CMalattieForm::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CMalattieForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)))
	{
		static UINT pControlID[] = {
			IDC_MALATTIA_1
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
			IDC_MALATTIA_1,
			IDC_CLASSE_1,
			IDC_EPISODI_1,
			IDC_MALATTIA_2,
			IDC_CLASSE_2,
			IDC_EPISODI_2,
			IDC_MALATTIA_3,
			IDC_CLASSE_3,
			IDC_EPISODI_3
		};

		for(i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID[i], EM_SETREADONLY, wParam, lParam);

		GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);
	}

	return 1;
}

LRESULT CMalattieForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CMalattieForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CMalattieSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CMalattieForm::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CMalattieForm::OnFormSave");
	}

	return 1;
}

LRESULT CMalattieForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CMalattieSet* pSet = &m_ctrLine[0].m_Set;

	if (pSet)
		ComponiRicercaString(pStrWhere, pSet, &pSet->m_sMalattia, "EMalattie.Malattia", 0);

	return 1;
}

long CMalattieForm::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CMalattieForm::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CMalattieForm::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_sMalattia  != "");
}

void CMalattieForm::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CMalattieForm::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CMalattieSet* pSet = (CMalattieSet*)pBaseSet;
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

void CMalattieForm::OnChangeMalattie1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CMalattieForm::OnChangeMalattie2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CMalattieForm::OnChangeMalattie3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CMalattieForm::OnChangeClasse1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CMalattieForm::OnChangeClasse2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CMalattieForm::OnChangeClasse3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CMalattieForm::OnChangeEpisodi1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CMalattieForm::OnChangeEpisodi2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CMalattieForm::OnChangeEpisodi3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

long CMalattieForm::GetContenuto()
{
	return sub_malattie;
}

BOOL CMalattieForm::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}

CString CMalattieForm::GetStringEpisodi(long lEpisodi)
{
	CString strReturn;
	strReturn.Format("%li", lEpisodi);
	return strReturn;
}