#include "stdafx.h"
#include "Endox.h"
#include "FluoroscopiaDynForm.h"

#include "EsamiView.h"
#include "EsamiSet.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFluoroscopiaDynForm::CFluoroscopiaDynForm(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxDynForm(CFluoroscopiaDynForm::IDD, pParent, pEsamiView)
{
}

CFluoroscopiaDynForm::~CFluoroscopiaDynForm(void)
{
}

BEGIN_MESSAGE_MAP(CFluoroscopiaDynForm, CEndoxDynForm)

	ON_MESSAGE(MSG_FREEEDIT_FOCUS_LOST, OnEditFocusLost)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CFluoroscopiaDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_fluoroscopia] == NULL)
	{
		pEsamiView->m_pDynForm[sub_fluoroscopia] = new CFluoroscopiaDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_fluoroscopia] != NULL)
		{
			pEsamiView->m_pDynForm[sub_fluoroscopia]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_fluoroscopia]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_fluoroscopia]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_fluoroscopia]->CreateChildForm(CFluoroscopiaDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CFluoroscopiaDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_FLUO_TXT, m_ctrlFluo);
	DDX_Control(pDX, IDC_MINUTI_TXT, m_ctrlMin);
	DDX_Control(pDX, IDC_SECONDI_TXT, m_ctrlSec);
	DDX_Control(pDX, IDC_DOSE_TXT, m_ctrlDose);

	DDX_Control(pDX, IDC_MINUTI, m_ctrlTesto[0]);
	DDX_Control(pDX, IDC_SECONDI, m_ctrlTesto[1]);
	DDX_Control(pDX, IDC_DOSE, m_ctrlTesto[2]);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		DDX_Text(pDX, IDC_MINUTI_1,		 m_lMinuti1);
		DDX_Text(pDX, IDC_MINUTI_2,		 m_lMinuti2);
		DDX_Text(pDX, IDC_SECONDI_1,	 m_lSecondi1);
		DDX_Text(pDX, IDC_SECONDI_2,	 m_lSecondi2);
		DDX_Text(pDX, IDC_DOSE_1,		 m_fDose1);
		DDX_Text(pDX, IDC_DOSE_2,		 m_fDose2);

		SetDlgItemText(IDC_MINUTI, "0");
		SetDlgItemText(IDC_SECONDI, "0");
		SetDlgItemText(IDC_DOSE, "0");
	}
	else
	{
		DDX_FieldText (pDX, IDC_MINUTI, m_pEsamiView->m_pEsamiSet->m_lFluoroscopiaMinuti, m_pEsamiView->m_pEsamiSet->GetRecordset());
		DDX_FieldText (pDX, IDC_SECONDI, m_pEsamiView->m_pEsamiSet->m_lFluoroscopiaSecondi, m_pEsamiView->m_pEsamiSet->GetRecordset());
		DDX_FieldText (pDX, IDC_DOSE, m_pEsamiView->m_pEsamiSet->m_fFluoroscopiaDose, m_pEsamiView->m_pEsamiSet->GetRecordset());
	}
	
	GetDlgItem(IDC_FLUO_TXT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MINUTI_TXT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MINUTI)->ShowWindow(SW_SHOW && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_MINUTI_1)->ShowWindow(SW_SHOW && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_MINUTI_2)->ShowWindow(SW_SHOW && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_SECONDI_TXT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_SECONDI)->ShowWindow(SW_SHOW && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_SECONDI_1)->ShowWindow(SW_SHOW && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_SECONDI_2)->ShowWindow(SW_SHOW && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_DOSE_TXT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_DOSE)->ShowWindow(SW_SHOW && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_DOSE_1)->ShowWindow(SW_SHOW && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_DOSE_2)->ShowWindow(SW_SHOW && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
}

HBRUSH CFluoroscopiaDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_FLUO_TXT:
		case IDC_MINUTI_TXT:
		case IDC_SECONDI_TXT:
		case IDC_DOSE_TXT:
		case IDC_MINUTI:
		case IDC_MINUTI_1:
		case IDC_MINUTI_2:
		case IDC_SECONDI:
		case IDC_SECONDI_1:
		case IDC_SECONDI_2:
		case IDC_DOSE:
		case IDC_DOSE_1:
		case IDC_DOSE_2:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hReturn;
}

BOOL CFluoroscopiaDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_FLUO_TXT, CSize(0, 40), CSize(33, 40));
	AddAnchor(IDC_MINUTI_TXT, CSize(17, 50), CSize(33, 50));
	AddAnchor(IDC_SECONDI_TXT, CSize(50, 50), CSize(66, 50));
	AddAnchor(IDC_DOSE_TXT, CSize(83, 50), CSize(100, 50));
	AddAnchor(IDC_MINUTI, CSize(0, 50), CSize(17, 50));
	AddAnchor(IDC_MINUTI_1, CSize(0, 50), CSize(8, 50));
	AddAnchor(IDC_MINUTI_2, CSize(8, 50), CSize(17, 50));
	AddAnchor(IDC_SECONDI, CSize(33, 50), CSize(50, 50));
	AddAnchor(IDC_SECONDI_1, CSize(33, 50), CSize(41, 50));
	AddAnchor(IDC_SECONDI_2, CSize(41, 50), CSize(50, 50));
	AddAnchor(IDC_DOSE, CSize(66, 50), CSize(83, 50));
	AddAnchor(IDC_DOSE_1, CSize(66, 50), CSize(74, 50));
	AddAnchor(IDC_DOSE_2, CSize(74, 50), CSize(83, 50));

	GetDlgItem(IDC_FLUO_TXT)->SetFont(&theApp.m_fontBold, TRUE);

	SetWindowLong(m_ctrlTesto[0].GetSafeHwnd(), GWL_STYLE, GetWindowLong(m_ctrlTesto[0].GetSafeHwnd(), GWL_STYLE) | ES_NUMBER);
	SetWindowLong(m_ctrlTesto[1].GetSafeHwnd(), GWL_STYLE, GetWindowLong(m_ctrlTesto[1].GetSafeHwnd(), GWL_STYLE) | ES_NUMBER);

	theApp.LocalizeDialog(this, CFluoroscopiaDynForm::IDD, "FluoroscopiaDynForm");

	return bReturn;
}

LRESULT CFluoroscopiaDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CFluoroscopiaDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CFluoroscopiaDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	SendDlgItemMessage(IDC_MINUTI, EM_SETREADONLY, wParam, lParam);
	SendDlgItemMessage(IDC_SECONDI, EM_SETREADONLY, wParam, lParam);
	SendDlgItemMessage(IDC_DOSE, EM_SETREADONLY, wParam, lParam);

	return 1;
}

LRESULT CFluoroscopiaDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_lMinuti1 = 0;
	m_lMinuti2 = 0;
	m_lSecondi1 = 0;
	m_lSecondi2 = 0;
	m_fDose1 = 0;
	m_fDose2 = 0;

	return 1;
}

LRESULT CFluoroscopiaDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CFluoroscopiaDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	ComponiRicercaRange(pStrWhere, m_lMinuti1, m_lMinuti2, "EEsami.FluoroscopiaMinuti");
	ComponiRicercaRange(pStrWhere, m_lSecondi1, m_lSecondi2, "EEsami.FluoroscopiaSecondi");
	ComponiRicercaRange(pStrWhere, m_fDose1, m_fDose2, "EEsami.FluoroscopiaDose");

	return 1;
}

long CFluoroscopiaDynForm::GetContenuto()
{
	return sub_fluoroscopia;
}

BOOL CFluoroscopiaDynForm::CampoObbligatorioValido()
{
	return FALSE;
}

LRESULT CFluoroscopiaDynForm::OnEditFocusLost(WPARAM wParam, LPARAM lParam)
{
	HWND OldHwnd = (HWND) wParam;
	CString temp;
	TCHAR tTemp[MAX_PATH];
	::GetWindowText(OldHwnd, tTemp, MAX_PATH);
	temp.Format("%s", tTemp);

	for(int i = 0; i < temp.GetLength(); i++)
	{
		CString tempChar = temp.Mid(i, 1);
		if (tempChar.Compare(".") != 0 && tempChar.Compare(",") != 0 && tempChar.Compare("0") != 0)
		{
			float fTemp = (float)atof(tempChar);
			if (fTemp == 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_ALFANUM));
				::SetFocus(OldHwnd);
				return -1;
			}
		}
	}

	temp.Replace(',','.');
	if (temp.Right(1).Compare(".") == 0)
		temp = temp.Left(temp.GetLength() - 1);
	::SetWindowText(OldHwnd, temp);

	return 0;
}