#include "stdafx.h"
#include "Endox.h"
#include "DiagnosiICD9FormEx.h"

#include "Common.h"
#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDiagnosiICD9FormEx::CDiagnosiICD9FormEx(CWnd* pParent, CEsamiView* pEsamiView)
	: CSubForm(CDiagnosiICD9FormEx::IDD, pParent, pEsamiView)
{

	m_nIndexLine = 0;
	m_nIndexPage = 3;
}

CDiagnosiICD9FormEx::~CDiagnosiICD9FormEx()
{
}

BEGIN_MESSAGE_MAP(CDiagnosiICD9FormEx, CSubForm)
	ON_WM_CTLCOLOR()

	ON_EN_CHANGE(IDC_DIAGNOSI_1, OnChangeDiagnosi1)
	ON_EN_CHANGE(IDC_DIAGNOSI_2, OnChangeDiagnosi2)
	ON_EN_CHANGE(IDC_DIAGNOSI_3, OnChangeDiagnosi3)
END_MESSAGE_MAP()

void CDiagnosiICD9FormEx::DoDataExchange(CDataExchange* pDX)
{
	static UINT nID_Diagnosi[3] = { IDC_DIAGNOSI_1, IDC_DIAGNOSI_2, IDC_DIAGNOSI_3 };
	static UINT nID_Numero[3] = { IDC_NUM_1, IDC_NUM_2, IDC_NUM_3 };

	CSubForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SUEN_00, m_ctrlStatic);

	for (int i = 0; i < m_nIndexPage; i++)
	{
		DDX_Control(pDX, nID_Diagnosi[i], m_ctrlDiagnosi[i]);
	}	

	//Mi serve per risettare le righe visualizzate durante lo scorrimento
	for (int i = 0; i < m_nIndexPage; i++)
	{
		if (!pDX->m_bSaveAndValidate)
		{
			if (m_ctrLine[m_nIndexLine + i].m_Set.m_lIDDiagnosi > 0)
				GetDlgItem(nID_Diagnosi[i])->SetWindowText(CDiagnosiICD9Set().GetStringCodificaICD9Esterni(m_ctrLine[m_nIndexLine + i].m_Set.m_lIDDiagnosi) + " - " + CDiagnosiICD9Set().GetStringDescrizione(m_ctrLine[m_nIndexLine + i].m_Set.m_lIDDiagnosi));
			else
				GetDlgItem(nID_Diagnosi[i])->SetWindowText("");
		}
	}

	if (!pDX->m_bSaveAndValidate)
		for (int i = 0; i < m_nIndexPage; i++)
			SetDlgItemInt(nID_Numero[i], m_nIndexLine + i + 1);
}

void CDiagnosiICD9FormEx::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_diagnosiicd9ex] == NULL)
	{
		pEsamiView->m_pDynForm[sub_diagnosiicd9ex] = new CDiagnosiICD9FormEx(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_diagnosiicd9ex] != NULL)
		{
			pEsamiView->m_pDynForm[sub_diagnosiicd9ex]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_diagnosiicd9ex]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_diagnosiicd9ex]->m_lIDFaseBlocco = lIDFaseBlocco;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_diagnosiicd9ex]->CreateChildForm(CDiagnosiICD9FormEx::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CDiagnosiICD9FormEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_SUEN_00:
	{
		if (m_lColore >= 0)
			pDC->SetTextColor(theApp.m_color[m_lColore]);

		if (m_crCampoObbligatorio > 0)
			pDC->SetBkColor(m_crCampoObbligatorio);

		break;
	}

	case IDC_SUEN_01:
	case IDC_NUM_1:
	case IDC_NUM_2:
	case IDC_NUM_3:
	case IDC_DIAGNOSI_1:
	case IDC_DIAGNOSI_2:
	case IDC_DIAGNOSI_3:
	{
		if (m_lColore >= 0)
			pDC->SetTextColor(theApp.m_color[m_lColore]);

		break;
	}
	}

	return hBrush;
}

BOOL CDiagnosiICD9FormEx::OnInitDialog()
{
	BOOL bResult = CSubForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_SUEN_00)->GetSafeHwnd(), CSize(0, 0), CSize(100, 1));
	AddAnchor(GetDlgItem(IDC_SUEN_01)->GetSafeHwnd(), CSize(100, 0), CSize(100, 1));
	AddAnchor(GetDlgItem(IDC_SCROLL)->GetSafeHwnd(), CSize(100, 0), CSize(100, 100));
	AddAnchor(GetDlgItem(IDC_NUM_1)->GetSafeHwnd(), CSize(0, 1), CSize(0, 34));
	AddAnchor(GetDlgItem(IDC_NUM_2)->GetSafeHwnd(), CSize(0, 34), CSize(0, 67));
	AddAnchor(GetDlgItem(IDC_NUM_3)->GetSafeHwnd(), CSize(0, 67), CSize(0, 100));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_1)->GetSafeHwnd(), CSize(0, 1), CSize(100, 34));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_2)->GetSafeHwnd(), CSize(0, 34), CSize(100, 67));
	AddAnchor(GetDlgItem(IDC_DIAGNOSI_3)->GetSafeHwnd(), CSize(0, 67), CSize(100, 100));

	GetDlgItem(IDC_SUEN_00)->SetFont(&theApp.m_fontBold, TRUE);	

	m_ctrlStatic.SetWindowText(theApp.GetMessageString(IDS_DIAGNOSI_ICD9));

	//theApp.LocalizeDialog(this, CDiagnosiICD9FormEx::IDD, "DiagnosiICD9FormEx");	

	return bResult;
}

void CDiagnosiICD9FormEx::ModificaForm()
{
	for (int i = 0; i < m_nIndexPage; i++)	
		m_ctrlDiagnosi[i].SetParam(this, &m_ctrLine[m_nIndexLine + i].m_Set.m_lIDEsame, &m_ctrLine[m_nIndexLine + i].m_Set.m_lIDDiagnosi);	
}

LRESULT CDiagnosiICD9FormEx::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CDiagnosiICD9FormEx::OnFormClone(WPARAM wParam, LPARAM lParam)
{
	long lEsame = (long)lParam;
	if (lEsame > 0)
	{
		CString strFilter;
		strFilter.Format("IDEsame=%li", lEsame);

		CDiagnosiEsamiSet setDiagnosi;
		setDiagnosi.SetOpenFilter(strFilter);
		setDiagnosi.SetSortRecord("ID");
		if (setDiagnosi.OpenRecordset("CDiagnosiICD9FormEx::OnFormClone"))
		{
			int nIndex = 0;
			while (!setDiagnosi.IsEOF())
			{
				m_ctrLine[nIndex].m_Set.CopyFieldFrom(&setDiagnosi);
				m_ctrLine[nIndex].m_nStato = RECORD_FULL | RECORD_DIRTY;
				m_ctrLine[nIndex].m_lID = 0;

				nIndex++;
				setDiagnosi.MoveNext();
			}

			setDiagnosi.CloseRecordset("CDiagnosiICD9FormEx::OnFormClone");
		}
	}

	return 1;
}

LRESULT CDiagnosiICD9FormEx::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(0, 0);
	GoToFirst();

	if (m_pEsamiView->m_pEsamiSet->IsOpen() && !m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
	{
		CString sFilter;
		sFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

		CDiagnosiEsamiSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CDiagnosiICD9FormEx::OnFormLoad"))
		{
			int nCounter = 0;
			while (!setTemp.IsEOF() && (nCounter < MAX_OBJ_X_FORM))
			{
				UpdateDataLine(&setTemp, nCounter, FALSE);

				nCounter++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CDiagnosiICD9FormEx::OnFormLoad");
		}
	}

	return 1;
}

LRESULT CDiagnosiICD9FormEx::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	int i;

	if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)))
	{
		static UINT pControlID[] = {
			IDC_DIAGNOSI_1
		};

		for (i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
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
			IDC_DIAGNOSI_1,
			IDC_DIAGNOSI_2,
			IDC_DIAGNOSI_3,
		};

		for (i = 0; i < (sizeof(pControlID) / sizeof(UINT)); i++)
			SendDlgItemMessage(pControlID[i], EM_SETREADONLY, wParam, lParam);

		GetDlgItem(IDC_SCROLL)->EnableWindow(TRUE);
	}

	return 1;
}

LRESULT CDiagnosiICD9FormEx::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < MAX_OBJ_X_FORM; i++)
	{
		m_ctrLine[i].m_Set.SetEmpty();
		m_ctrLine[i].m_nStato = RECORD_EMPTY;
		m_ctrLine[i].m_lID = 0;
	}

	return 1;
}

LRESULT CDiagnosiICD9FormEx::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	CDiagnosiEsamiSet setTemp;
	setTemp.SetOpenFilter("ID=0");
	if (setTemp.OpenRecordset("CDiagnosiICD9FormEx::OnFormSave"))
	{
		CSubForm::SaveForm(&m_pEsamiView->m_pEsamiSet->m_lContatore, &setTemp, &setTemp.m_lID, &setTemp.m_lIDEsame, "ID");
		setTemp.CloseRecordset("CDiagnosiICD9FormEx::OnFormSave");
	}

	return 1;
}

LRESULT CDiagnosiICD9FormEx::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CDiagnosiEsamiSet* pSet = &m_ctrLine[0].m_Set;

	if (pSet)
	{
		ComponiRicercaFromEx(pStrWhere, pStrFrom, m_ctrlDiagnosi[0].m_strRicerca, "DiagnosiEsami", 0, "IdDiagnosi", "IdEsame", TRUE, TRUE);
	}

	return 1;
}

long CDiagnosiICD9FormEx::GetCounterSetOfLine(int nCounter)
{
	return m_ctrLine[nCounter].m_lID;
}

BOOL CDiagnosiICD9FormEx::IsLineDirty(int nCounter)
{
	return (m_ctrLine[nCounter].m_nStato & RECORD_DIRTY);
}

BOOL CDiagnosiICD9FormEx::IsValidSet(int nCounter)
{	
	return (CDiagnosiICD9Set().GetStringDescrizione(m_ctrLine[nCounter].m_Set.m_lIDDiagnosi) != "");
}

void CDiagnosiICD9FormEx::SetLineDirty(int nCounter, BOOL bSetDirty)
{
	static UINT nID_Diagnosi[3] = { IDC_DIAGNOSI_1, IDC_DIAGNOSI_2, IDC_DIAGNOSI_3 };

	if (bSetDirty)
	{
		m_ctrLine[nCounter].m_nStato |= RECORD_DIRTY;		
		for (int i = 0; i < m_nIndexPage; i++)
		{
			if (nCounter == m_nIndexLine + i)
			{
				if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
					GetDlgItem(nID_Diagnosi[i])->SetWindowText(m_ctrlDiagnosi[i].m_strRicercaView);
				else
					GetDlgItem(nID_Diagnosi[i])->SetWindowText(CDiagnosiICD9Set().GetStringCodificaICD9Esterni(m_ctrLine[m_nIndexLine + i].m_Set.m_lIDDiagnosi) + " - " + CDiagnosiICD9Set().GetStringDescrizione(m_ctrLine[m_nIndexLine + i].m_Set.m_lIDDiagnosi));
			}
		}		
	}
	else
	{
		m_ctrLine[nCounter].m_nStato &= ~RECORD_DIRTY;
		for (int i = 0; i < m_nIndexPage; i++)
		{
			if (nCounter == m_nIndexLine + i)
				GetDlgItem(nID_Diagnosi[i])->SetWindowText("");
		}
	}
}

void CDiagnosiICD9FormEx::UpdateDataLine(CBaseSet* pBaseSet, int nCounter, BOOL bToSet)
{
	CDiagnosiEsamiSet* pSet = (CDiagnosiEsamiSet*)pBaseSet;
	if (bToSet)
	{
		pSet->CopyFieldFrom(&m_ctrLine[nCounter].m_Set);
	}
	else
	{
		m_ctrLine[nCounter].m_Set.CopyFieldFrom(pSet);
		m_ctrLine[nCounter].m_nStato = RECORD_FULL;
		m_ctrLine[nCounter].m_lID = pSet->m_lID;

		static UINT nID_Diagnosi[3] = { IDC_DIAGNOSI_1, IDC_DIAGNOSI_2, IDC_DIAGNOSI_3 };
		for (int i = 0; i < m_nIndexPage; i++)
		{
			if (nCounter == m_nIndexLine + i)
				GetDlgItem(nID_Diagnosi[i])->SetWindowText(CDiagnosiICD9Set().GetStringCodificaICD9Esterni(m_ctrLine[m_nIndexLine + i].m_Set.m_lIDDiagnosi) + " - " + CDiagnosiICD9Set().GetStringDescrizione(m_ctrLine[m_nIndexLine + i].m_Set.m_lIDDiagnosi));
		}		
	}
}

void CDiagnosiICD9FormEx::OnChangeDiagnosi1()
{
	SetLineDirty(m_nIndexLine + 0, TRUE);
}

void CDiagnosiICD9FormEx::OnChangeDiagnosi2()
{
	SetLineDirty(m_nIndexLine + 1, TRUE);
}

void CDiagnosiICD9FormEx::OnChangeDiagnosi3()
{
	SetLineDirty(m_nIndexLine + 2, TRUE);
}

long CDiagnosiICD9FormEx::GetContenuto()
{
	return sub_diagnosiicd9ex;
}

BOOL CDiagnosiICD9FormEx::CampoObbligatorioValido()
{
	for (int i = 0; i < MAX_OBJ_X_FORM; i++)
		if (m_ctrLine[i].m_nStato != RECORD_EMPTY)
			return TRUE;

	return FALSE;
}