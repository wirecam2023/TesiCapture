#include "stdafx.h"
#include "Endox.h"
#include "ChirurgiciDynForm.h"

#include "Common.h"
#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CChirurgiciDynForm::CChirurgiciDynForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CChirurgiciDynForm::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 3;
}

CChirurgiciDynForm::~CChirurgiciDynForm()
{
}

BEGIN_MESSAGE_MAP(CChirurgiciDynForm, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_INTERVENTO_1, OnChangeIntervento1)
	ON_EN_CHANGE(IDC_INTERVENTO_2, OnChangeIntervento2)
	ON_EN_CHANGE(IDC_INTERVENTO_3, OnChangeIntervento3)
	ON_EN_CHANGE(IDC_CLASSE_1, OnChangeClasse1)
	ON_EN_CHANGE(IDC_CLASSE_2, OnChangeClasse2)
	ON_EN_CHANGE(IDC_CLASSE_3, OnChangeClasse3)
END_MESSAGE_MAP()

void CChirurgiciDynForm::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Intervento[3] = { IDC_INTERVENTO_1, IDC_INTERVENTO_2, IDC_INTERVENTO_3 };
	static UINT nID_Data      [3] = { IDC_CLASSE_1,     IDC_CLASSE_2,     IDC_CLASSE_3 };
	static UINT nID_Numero    [3] = { IDC_NUM_1,        IDC_NUM_2,        IDC_NUM_3 };

	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SUCH_00, m_ctrlStatic);

	for(int i = 0; i < m_nIndexPage; i++)
	{
		DDX_Control(pDX, nID_Intervento[i], m_ctrlIntervento[i]);
		DDX_Control(pDX, nID_Data[i], m_ctrlData[i]);
	}

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_Text(pDX, nID_Intervento[i], m_ctrLine[m_nIndexLine + i].m_Set.m_sIntervento);

			if (theApp.m_bMostraSoloAnnoInterventiChirurgici)
				DDX_YearEx(pDX, nID_Data[i], m_ctrLine[m_nIndexLine + i].m_Set.m_lClasse);
			else
				DDX_DateMask(pDX, nID_Data[i], m_ctrLine[m_nIndexLine + i].m_Set.m_lClasse, m_ctrLine[m_nIndexLine + i].m_Set.GetRecordset());
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);
}

/*
void CChirurgiciDynForm::CreateForm(CWnd* pParent, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	CRect rectFrame;
	pParentFrame->GetWindowRect(&rectFrame);

	if (pEsamiView->m_pDynForm[sub_chirurgici] == NULL)
	{
		pEsamiView->m_pDynForm[sub_chirurgici] = new CChirurgiciDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_chirurgici] != NULL)
		{
			pEsamiView->m_pDynForm[sub_chirurgici]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_chirurgici]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_chirurgici]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			pEsamiView->m_pDynForm[sub_chirurgici]->CreateChildForm(CChirurgiciDynForm::IDD, pParent, rectFrame);
		}
	}
}
*/

void CChirurgiciDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_chirurgici] == NULL)
	{
		pEsamiView->m_pDynForm[sub_chirurgici] = new CChirurgiciDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_chirurgici] != NULL)
		{
			pEsamiView->m_pDynForm[sub_chirurgici]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_chirurgici]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_chirurgici]->m_lIDFaseBlocco = lIDFaseBlocco;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_chirurgici]->CreateChildForm(CChirurgiciDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CChirurgiciDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_SUCH_00:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_SUCH_01:
		case IDC_NUM_1:
		case IDC_NUM_2:
		case IDC_NUM_3:
		case IDC_INTERVENTO_1:
		case IDC_INTERVENTO_2:
		case IDC_INTERVENTO_3:
		case IDC_CLASSE_1:
		case IDC_CLASSE_2:
		case IDC_CLASSE_3:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CChirurgiciDynForm::OnInitDialog() 
{
	BOOL bResult = CSubForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_SUCH_00)->GetSafeHwnd(), CSize(0,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_SUCH_01)->GetSafeHwnd(), CSize(100,0), CSize(100,1));
	AddAnchor(GetDlgItem(IDC_SCROLL)->GetSafeHwnd(), CSize(100,0), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_NUM_1)->GetSafeHwnd(), CSize(0,1), CSize(0,34));
	AddAnchor(GetDlgItem(IDC_NUM_2)->GetSafeHwnd(), CSize(0,34), CSize(0,67));
	AddAnchor(GetDlgItem(IDC_NUM_3)->GetSafeHwnd(), CSize(0,67), CSize(0,100));
	AddAnchor(GetDlgItem(IDC_INTERVENTO_1)->GetSafeHwnd(), CSize(0,1), CSize(100,34));
	AddAnchor(GetDlgItem(IDC_INTERVENTO_2)->GetSafeHwnd(), CSize(0,34), CSize(100,67));
	AddAnchor(GetDlgItem(IDC_INTERVENTO_3)->GetSafeHwnd(), CSize(0,67), CSize(100,100));
	AddAnchor(GetDlgItem(IDC_CLASSE_1)->GetSafeHwnd(), CSize(100,17), CSize(100,17));
	AddAnchor(GetDlgItem(IDC_CLASSE_2)->GetSafeHwnd(), CSize(100,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_CLASSE_3)->GetSafeHwnd(), CSize(100,83), CSize(100,83));

	GetDlgItem(IDC_SUCH_00)->SetFont(&theApp.m_fontBold, TRUE);

	theApp.LocalizeDialog(this, CChirurgiciDynForm::IDD, "IntChirurgiciForm");

	if (theApp.m_bMostraSoloAnnoInterventiChirurgici)
	{
		SetDlgItemText(IDC_SUCH_01, theApp.GetMessageString(IDS_ANNO));

		for(int i = 0; i < m_nIndexPage; i++)
			m_ctrlData[i].SetEditMask("0000", "____");
	}
	else
	{
		SetDlgItemText(IDC_SUCH_01, theApp.GetMessageString(IDS_DATA));

		for(int i = 0; i < m_nIndexPage; i++)
			m_ctrlData[i].SetEditMask("00/00/0000", "__/__/____");
	}

	return bResult;
}

void CChirurgiciDynForm::ModificaForm()
{
	for(int i = 0; i < m_nIndexPage; i++)
	{
		m_ctrlIntervento[i].SetParam(this, CMB_ANA_ICHIRURG, &m_ctrLine[m_nIndexLine + i].m_Set, NULL, &m_ctrLine[m_nIndexLine + i].m_Set.m_sIntervento, 255);
		m_ctrlIntervento[i].SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);
	}
}

LRESULT CChirurgiciDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CChirurgiciDynForm::OnFormClone(WPARAM wParam, LPARAM lParam)
{
	long lEsame = (long)lParam;
	if (lEsame > 0)
	{
		CInterventiChirurgiciSet setTemp;

		CString strFilter;
		strFilter.Format("Esame=%li", lEsame);

		setTemp.SetOpenFilter(strFilter);
		setTemp.SetSortRecord("Contatore");
		if (setTemp.OpenRecordset("CChirurgiciDynForm::OnFormClone"))
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

			setTemp.CloseRecordset("CChirurgiciDynForm::OnFormClone");
		}
	}

	return 1;
}

LRESULT CChirurgiciDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(NULL, NULL);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CInterventiChirurgiciSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CChirurgiciDynForm::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CChirurgiciDynForm::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CChirurgiciDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)))
	{
		static UINT pControlID[] = {
			IDC_INTERVENTO_1
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
			IDC_INTERVENTO_1,
			IDC_CLASSE_1,
			IDC_INTERVENTO_2,
			IDC_CLASSE_2,
			IDC_INTERVENTO_3,
			IDC_CLASSE_3
		};

		for(i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID[i], EM_SETREADONLY, wParam, lParam);

		GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);
	}

	return 1;
}

LRESULT CChirurgiciDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_nContatore = 0;
	}

	return 1;
}

LRESULT CChirurgiciDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CInterventiChirurgiciSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CChirurgiciDynForm::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CChirurgiciDynForm::OnFormSave");
	}

	return 1;
}

LRESULT CChirurgiciDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CInterventiChirurgiciSet* pSet = &m_ctrLine[0].m_Set;

	if (pSet)
		ComponiRicercaString(pStrWhere, pSet, &pSet->m_sIntervento, "EInterventiChirurgici.Intervento", 1);

	return 1;
}

long CChirurgiciDynForm::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_nContatore;
}

BOOL CChirurgiciDynForm::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CChirurgiciDynForm::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_sIntervento != "");
}

void CChirurgiciDynForm::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CChirurgiciDynForm::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CInterventiChirurgiciSet* pSet = (CInterventiChirurgiciSet*)pBaseSet;
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

void CChirurgiciDynForm::OnChangeIntervento1()
{
	SetLineDirty(m_nIndexLine, TRUE);
}

void CChirurgiciDynForm::OnChangeIntervento2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CChirurgiciDynForm::OnChangeIntervento3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CChirurgiciDynForm::OnChangeClasse1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CChirurgiciDynForm::OnChangeClasse2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CChirurgiciDynForm::OnChangeClasse3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

long CChirurgiciDynForm::GetContenuto()
{
	return sub_chirurgici;
}

BOOL CChirurgiciDynForm::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}