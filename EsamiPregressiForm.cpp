#include "stdafx.h"
#include "Endox.h"
#include "EsamiPregressiForm.h"

#include "EsamiView.h"
#include "Common.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEsamiPregressiForm::CEsamiPregressiForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CEsamiPregressiForm::IDD, pParent, pEsamiView)
{
	m_nIndexLine = 0;
	m_nIndexPage = 3;
}

CEsamiPregressiForm::~CEsamiPregressiForm()
{
}

BEGIN_MESSAGE_MAP(CEsamiPregressiForm, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_ESAMEPREGRESSO_1, OnChangeEsamePregresso1)
	ON_EN_CHANGE(IDC_ESAMEPREGRESSO_2, OnChangeEsamePregresso2)
	ON_EN_CHANGE(IDC_ESAMEPREGRESSO_3, OnChangeEsamePregresso3)
	ON_EN_CHANGE(IDC_DATA_1, OnChangeData1)
	ON_EN_CHANGE(IDC_DATA_2, OnChangeData2)
	ON_EN_CHANGE(IDC_DATA_3, OnChangeData3)
	ON_EN_CHANGE(IDC_ESITO_1, OnChangeEsito1)
	ON_EN_CHANGE(IDC_ESITO_2, OnChangeEsito2)
	ON_EN_CHANGE(IDC_ESITO_3, OnChangeEsito3)
END_MESSAGE_MAP()

void CEsamiPregressiForm::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_EsamePregresso[3] = { IDC_ESAMEPREGRESSO_1, IDC_ESAMEPREGRESSO_2, IDC_ESAMEPREGRESSO_3 };
	static UINT nID_Data[3] =           { IDC_DATA_1,           IDC_DATA_2,           IDC_DATA_3 };
	static UINT nID_Esito[3] =          { IDC_ESITO_1,          IDC_ESITO_2,          IDC_ESITO_3 };
	static UINT nID_Numero[3] =			{ IDC_NUM_1,            IDC_NUM_2,            IDC_NUM_3 };
	
	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SUIP_00, m_ctrlStatic[0]);
	DDX_Control(pDX, IDC_SUIP_01, m_ctrlStatic[1]);
	DDX_Control(pDX, IDC_SUIP_02, m_ctrlStatic[2]);

	for(int i = 0; i < m_nIndexPage; i++)
	{
		DDX_Control(pDX, nID_EsamePregresso[i], m_ctrlEsamiPregressi[i]);
		DDX_Control(pDX, nID_Data[i], m_ctrlData[i]);
	}

	if (m_pEsamiView->m_pEsamiSet->IsOpen())
	{
		for(int i = 0; i < m_nIndexPage; i++)
		{
			DDX_Text  (pDX, nID_EsamePregresso[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sEsamePregresso);
			DDX_DateMask(pDX, nID_Data[i], m_ctrLine[m_nIndexLine+i].m_Set.m_lData, m_ctrLine[m_nIndexLine+i].m_Set.GetRecordset());
			DDX_Text  (pDX, nID_Esito[i], m_ctrLine[m_nIndexLine+i].m_Set.m_sEsito);
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for(int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine+i+1);
}

void CEsamiPregressiForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_esamipregressi] == NULL)
	{
		pEsamiView->m_pDynForm[sub_esamipregressi] = new CEsamiPregressiForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_esamipregressi] != NULL)
		{
			pEsamiView->m_pDynForm[sub_esamipregressi]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_esamipregressi]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_esamipregressi]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_esamipregressi]->CreateChildForm(CEsamiPregressiForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CEsamiPregressiForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_SUIP_00:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_SUIP_01:
		case IDC_SUIP_02:
		case IDC_NUM_1:
		case IDC_NUM_2:
		case IDC_NUM_3:
		case IDC_ESAMEPREGRESSO_1:
		case IDC_ESAMEPREGRESSO_2:
		case IDC_ESAMEPREGRESSO_3:
		case IDC_DATA_1:
		case IDC_DATA_2:
		case IDC_DATA_3:
		case IDC_ESITO_1:
		case IDC_ESITO_2:
		case IDC_ESITO_3:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CEsamiPregressiForm::OnInitDialog() 
{
	BOOL bResult = CSubForm::OnInitDialog();

	AddAnchor(IDC_SUIP_00, CSize(0,0), CSize(50,1));
	AddAnchor(IDC_SUIP_01, CSize(50,0), CSize(50,1));
	AddAnchor(IDC_SUIP_02, CSize(50,0), CSize(100,1));
	AddAnchor(IDC_SCROLL, CSize(100,0), CSize(100,100));
	AddAnchor(IDC_NUM_1, CSize(0,1), CSize(0,34));
	AddAnchor(IDC_NUM_2, CSize(0,34), CSize(0,67));
	AddAnchor(IDC_NUM_3, CSize(0,67), CSize(0,100));
	AddAnchor(IDC_ESAMEPREGRESSO_1, CSize(0,1), CSize(50,34));
	AddAnchor(IDC_ESAMEPREGRESSO_2, CSize(0,34), CSize(50,67));
	AddAnchor(IDC_ESAMEPREGRESSO_3, CSize(0,67), CSize(50,100));
	AddAnchor(IDC_DATA_1, CSize(50,17), CSize(50,17));
	AddAnchor(IDC_DATA_2, CSize(50,50), CSize(50,50));
	AddAnchor(IDC_DATA_3, CSize(50,83), CSize(50,83));
	AddAnchor(IDC_ESITO_1, CSize(50,1), CSize(100,34));
	AddAnchor(IDC_ESITO_2, CSize(50,34), CSize(100,67));
	AddAnchor(IDC_ESITO_3, CSize(50,67), CSize(100,100));

	GetDlgItem(IDC_SUIP_00)->SetFont(&theApp.m_fontBold, TRUE);

	for(int i = 0; i < m_nIndexPage; i++)
		m_ctrlData[i].SetEditMask("00/00/0000", "__/__/____");

	theApp.LocalizeDialog(this, CEsamiPregressiForm::IDD, "EsamiPregressiForm");

	return bResult;
}

void CEsamiPregressiForm::ModificaForm()
{
	for(int i = 0; i < m_nIndexPage; i++)
	{
		m_ctrlEsamiPregressi[i].SetParam(this, CMB_ESA_ESAMIPREGRESSI, &m_ctrLine[m_nIndexLine + i].m_Set, NULL, &m_ctrLine[m_nIndexLine + i].m_Set.m_sEsamePregresso, 3999);
		m_ctrlEsamiPregressi[i].SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);
	}
}

LRESULT CEsamiPregressiForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CEsamiPregressiForm::OnFormClone(WPARAM wParam, LPARAM lParam)
{
	long lEsame = (long)lParam;
	if (lEsame > 0)
	{
		CEsamiPregressiSet setTemp;

		CString strFilter;
		strFilter.Format("Esame=%li", lEsame);

		setTemp.SetOpenFilter(strFilter);
		setTemp.SetSortRecord("Contatore");
		if (setTemp.OpenRecordset("CEsamiPregressiForm::OnFormClone"))
		{
			int nIndex = 0;
			while(!setTemp.IsEOF())
			{
				m_ctrLine[nIndex].m_Set.CopyFieldFrom(&setTemp);
				m_ctrLine[nIndex].m_nStato = RECORD_FULL | RECORD_DIRTY;
				m_ctrLine[nIndex].m_lContatore = 0;

				nIndex++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CEsamiPregressiForm::OnFormClone");
		}
	}

	return 1;
}

LRESULT CEsamiPregressiForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("Esame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CEsamiPregressiSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CEsamiPregressiForm::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CEsamiPregressiForm::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CEsamiPregressiForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)))
	{
		static UINT pControlID[] = {
			IDC_ESAMEPREGRESSO_1,
			IDC_ESITO_1
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
			IDC_ESAMEPREGRESSO_1,
			IDC_ESAMEPREGRESSO_2,
			IDC_ESAMEPREGRESSO_3,
			IDC_DATA_1,
			IDC_DATA_2,
			IDC_DATA_3,
			IDC_ESITO_1,
			IDC_ESITO_2,
			IDC_ESITO_3
		};

		for(i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID[i], EM_SETREADONLY, wParam, lParam);

		GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);
	}

	return 1;
}

LRESULT CEsamiPregressiForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_lContatore = 0;
	}

	return 1;
}

LRESULT CEsamiPregressiForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CEsamiPregressiSet setTemp;
	setTemp.SetOpenFilter("Contatore=0");
	if (setTemp.OpenRecordset("CEsamiPregressiForm::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lContatore, &setTemp.m_lEsame);
		setTemp.CloseRecordset("CEsamiPregressiForm::OnFormSave");
	}

	return 1;
}

LRESULT CEsamiPregressiForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CEsamiPregressiSet* pSet = &m_ctrLine[0].m_Set;

	if (pSet)
	{
		ComponiRicercaString(pStrWhere, pSet, &pSet->m_sEsamePregresso, "EsamiPregressi.EsamePregresso", 1);
		ComponiRicercaString(pStrWhere, pSet, &pSet->m_sEsito, "EsamiPregressi.Esito", 1);
	}

	return 1;
}

long CEsamiPregressiForm::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_lContatore;
}

BOOL CEsamiPregressiForm::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CEsamiPregressiForm::IsValidSet(int nCounter)
{
	return (m_ctrLine[nCounter].m_Set.m_sEsamePregresso != "");
}

void CEsamiPregressiForm::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	if (bSetDirty)
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;
	else
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
}

void CEsamiPregressiForm::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CEsamiPregressiSet* pSet = (CEsamiPregressiSet*)pBaseSet;
	if (bToSet)
	{
		pSet->CopyFieldFrom(&m_ctrLine[nCounter].m_Set);
	}
	else
	{
		m_ctrLine[nCounter].m_Set.CopyFieldFrom(pSet);
		m_ctrLine[nCounter].m_nStato = RECORD_FULL;
		m_ctrLine[nCounter].m_lContatore = pSet->m_lContatore;
	}
}

void CEsamiPregressiForm::OnChangeEsamePregresso1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CEsamiPregressiForm::OnChangeEsamePregresso2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CEsamiPregressiForm::OnChangeEsamePregresso3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CEsamiPregressiForm::OnChangeData1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CEsamiPregressiForm::OnChangeData2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CEsamiPregressiForm::OnChangeData3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

void CEsamiPregressiForm::OnChangeEsito1()
{
	SetLineDirty(m_nIndexLine+0, TRUE);
}

void CEsamiPregressiForm::OnChangeEsito2()
{
	SetLineDirty(m_nIndexLine+1, TRUE);
}

void CEsamiPregressiForm::OnChangeEsito3()
{
	SetLineDirty(m_nIndexLine+2, TRUE);
}

long CEsamiPregressiForm::GetContenuto()
{
	return sub_esamipregressi;
}

BOOL CEsamiPregressiForm::CampoObbligatorioValido()
{
	for(int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}