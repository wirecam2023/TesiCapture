#include "stdafx.h"
#include "Endox.h"
#include "VolumeDynForm.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CVolumeDynForm::CVolumeDynForm(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxDynForm(CVolumeDynForm::IDD, pParent, pEsamiView)
{
	m_bAutoUpdate = FALSE;
}

CVolumeDynForm::~CVolumeDynForm(void)
{
}

BEGIN_MESSAGE_MAP(CVolumeDynForm, CEndoxDynForm)

	ON_EN_CHANGE(IDC_EDIT_MISURA_A, OnEnChangeMisuraABC)
	ON_EN_CHANGE(IDC_EDIT_MISURA_B, OnEnChangeMisuraABC)
	ON_EN_CHANGE(IDC_EDIT_MISURA_C, OnEnChangeMisuraABC)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CVolumeDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_volume] == NULL)
	{
		pEsamiView->m_pDynForm[sub_volume] = new CVolumeDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_volume] != NULL)
		{
			pEsamiView->m_pDynForm[sub_volume]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_volume]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_volume]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_volume]->CreateChildForm(CVolumeDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CVolumeDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_MISURA_A, m_ctrlStaticMisuraA);
	DDX_Control(pDX, IDC_STATIC_MISURA_B, m_ctrlStaticMisuraB);
	DDX_Control(pDX, IDC_STATIC_MISURA_C, m_ctrlStaticMisuraC);
	DDX_Control(pDX, IDC_STATIC_VOLUME, m_ctrlStaticVolume);

	DDX_Control(pDX, IDC_EDIT_MISURA_A, m_ctrlEditMisuraA);
	DDX_Control(pDX, IDC_EDIT_MISURA_B, m_ctrlEditMisuraB);
	DDX_Control(pDX, IDC_EDIT_MISURA_C, m_ctrlEditMisuraC);
	DDX_Control(pDX, IDC_EDIT_VOLUME, m_ctrlEditVolume);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		DDX_Text(pDX, IDC_EDIT_MISURA_A1, m_fMisuraA1);
		DDX_Text(pDX, IDC_EDIT_MISURA_A2, m_fMisuraA2);
		DDX_Text(pDX, IDC_EDIT_MISURA_B1, m_fMisuraB1);
		DDX_Text(pDX, IDC_EDIT_MISURA_B2, m_fMisuraB2);
		DDX_Text(pDX, IDC_EDIT_MISURA_C1, m_fMisuraC1);
		DDX_Text(pDX, IDC_EDIT_MISURA_C2, m_fMisuraC2);
		DDX_Text(pDX, IDC_EDIT_VOLUME_1, m_fVolume1);
		DDX_Text(pDX, IDC_EDIT_VOLUME_2, m_fVolume2);

		SetDlgItemText(IDC_EDIT_MISURA_A, "");
		SetDlgItemText(IDC_EDIT_MISURA_B, "");
		SetDlgItemText(IDC_EDIT_MISURA_C, "");
		SetDlgItemText(IDC_EDIT_VOLUME, "");
	}
	else
	{
		if (pDX->m_bSaveAndValidate)
		{
			// Sandro 03/02/2014 //

			CString strText;

			GetDlgItemText(IDC_EDIT_MISURA_A, strText);
			strText.Replace(',','.');
			if (strText.Right(1).Compare(".") == 0)
				strText = strText.Left(strText.GetLength() - 1);
			float fMisuraA = (float)atof(strText);
			strText.Format("%.2f", fMisuraA);
			SetDlgItemText(IDC_EDIT_MISURA_A, strText);

			GetDlgItemText(IDC_EDIT_MISURA_B, strText);
			strText.Replace(',','.');
			if (strText.Right(1).Compare(".") == 0)
				strText = strText.Left(strText.GetLength() - 1);
			float fMisuraB = (float)atof(strText);
			strText.Format("%.2f", fMisuraB);
			SetDlgItemText(IDC_EDIT_MISURA_B, strText);

			GetDlgItemText(IDC_EDIT_MISURA_C, strText);
			strText.Replace(',', '.');
			if (strText.Right(1).Compare(".") == 0)
				strText = strText.Left(strText.GetLength() - 1);
			float fMisuraC = (float)atof(strText);
			strText.Format("%.2f", fMisuraC);
			SetDlgItemText(IDC_EDIT_MISURA_C, strText);

			//

			DDX_FieldText(pDX, IDC_EDIT_MISURA_A, m_pEsamiView->m_pEsamiSet->m_fMisuraA, m_pEsamiView->m_pEsamiSet->GetRecordset());
			DDX_FieldText(pDX, IDC_EDIT_MISURA_B, m_pEsamiView->m_pEsamiSet->m_fMisuraB, m_pEsamiView->m_pEsamiSet->GetRecordset());
			DDX_FieldText(pDX, IDC_EDIT_MISURA_C, m_pEsamiView->m_pEsamiSet->m_fMisuraC, m_pEsamiView->m_pEsamiSet->GetRecordset());

			DDX_FieldText(pDX, IDC_EDIT_VOLUME, m_pEsamiView->m_pEsamiSet->m_fVolume, m_pEsamiView->m_pEsamiSet->GetRecordset());
		}
		else
		{
			DDX_FieldText(pDX, IDC_EDIT_MISURA_A, m_pEsamiView->m_pEsamiSet->m_fMisuraA, m_pEsamiView->m_pEsamiSet->GetRecordset());
			DDX_FieldText(pDX, IDC_EDIT_MISURA_B, m_pEsamiView->m_pEsamiSet->m_fMisuraB, m_pEsamiView->m_pEsamiSet->GetRecordset());
			DDX_FieldText(pDX, IDC_EDIT_MISURA_C, m_pEsamiView->m_pEsamiSet->m_fMisuraC, m_pEsamiView->m_pEsamiSet->GetRecordset());

			UpdateVolume(m_pEsamiView->m_pEsamiSet->m_fMisuraA, m_pEsamiView->m_pEsamiSet->m_fMisuraB, m_pEsamiView->m_pEsamiSet->m_fMisuraC);
		}
	}
}

HBRUSH CVolumeDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_MISURA_A:
		case IDC_STATIC_MISURA_B:
		case IDC_STATIC_MISURA_C:
		case IDC_STATIC_VOLUME:
		case IDC_EDIT_MISURA_A:
		case IDC_EDIT_MISURA_B:
		case IDC_EDIT_MISURA_C:
		case IDC_EDIT_VOLUME:
		case IDC_EDIT_MISURA_A1:
		case IDC_EDIT_MISURA_B1:
		case IDC_EDIT_MISURA_C1:
		case IDC_EDIT_VOLUME_1:
		case IDC_EDIT_MISURA_A2:
		case IDC_EDIT_MISURA_B2:
		case IDC_EDIT_MISURA_C2:
		case IDC_EDIT_VOLUME_2:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hReturn;
}

BOOL CVolumeDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_MISURA_A, CSize(0, 50), CSize(25, 50));
	AddAnchor(IDC_STATIC_MISURA_B, CSize(25, 50), CSize(50, 50));
	AddAnchor(IDC_STATIC_MISURA_C, CSize(50, 50), CSize(75, 50));
	AddAnchor(IDC_STATIC_VOLUME, CSize(75, 50), CSize(100, 50));
	AddAnchor(IDC_EDIT_MISURA_A, CSize(0, 50), CSize(25, 50));
	AddAnchor(IDC_EDIT_MISURA_B, CSize(25, 50), CSize(50, 50));
	AddAnchor(IDC_EDIT_MISURA_C, CSize(50, 50), CSize(75, 50));
	AddAnchor(IDC_EDIT_VOLUME, CSize(75, 50), CSize(100, 50));
	AddAnchor(IDC_EDIT_MISURA_A1, CSize(0, 50), CSize(13, 50));
	AddAnchor(IDC_EDIT_MISURA_A2, CSize(12, 50), CSize(25, 50));
	AddAnchor(IDC_EDIT_MISURA_B1, CSize(25, 50), CSize(38, 50));
	AddAnchor(IDC_EDIT_MISURA_B2, CSize(37, 50), CSize(50, 50));
	AddAnchor(IDC_EDIT_MISURA_C1, CSize(50, 50), CSize(63, 50));
	AddAnchor(IDC_EDIT_MISURA_C2, CSize(62, 50), CSize(75, 50));
	AddAnchor(IDC_EDIT_VOLUME_1, CSize(75, 50), CSize(88, 50));
	AddAnchor(IDC_EDIT_VOLUME_2, CSize(87, 50), CSize(100, 50));

	theApp.LocalizeDialog(this, CVolumeDynForm::IDD, "VolumeDynForm");

	return bReturn;
}

LRESULT CVolumeDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CVolumeDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CVolumeDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_ctrlEditMisuraA.ShowWindow(SW_HIDE);
		m_ctrlEditMisuraB.ShowWindow(SW_HIDE);
		m_ctrlEditMisuraC.ShowWindow(SW_HIDE);
		m_ctrlEditVolume.ShowWindow(SW_HIDE);

		GetDlgItem(IDC_EDIT_MISURA_A1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MISURA_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MISURA_B1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MISURA_B2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MISURA_C1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MISURA_C2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_VOLUME_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_VOLUME_2)->ShowWindow(SW_SHOW);
	}
	else
	{
		m_ctrlEditMisuraA.ShowWindow(SW_SHOW);
		m_ctrlEditMisuraB.ShowWindow(SW_SHOW);
		m_ctrlEditMisuraC.ShowWindow(SW_SHOW);
		m_ctrlEditVolume.ShowWindow(SW_SHOW);

		GetDlgItem(IDC_EDIT_MISURA_A1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MISURA_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MISURA_B1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MISURA_B2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MISURA_C1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MISURA_C2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_VOLUME_1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_VOLUME_2)->ShowWindow(SW_HIDE);

		if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
			wParam = TRUE;

		SendDlgItemMessage(IDC_EDIT_MISURA_A, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_EDIT_MISURA_B, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_EDIT_MISURA_C, EM_SETREADONLY, wParam, lParam);
	}

	return 1;
}

LRESULT CVolumeDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_fMisuraA1 = 0;
	m_fMisuraA2 = 0;
	m_fMisuraB1 = 0;
	m_fMisuraB2 = 0;
	m_fMisuraC1 = 0;
	m_fMisuraC2 = 0;
	m_fVolume1 = 0;
	m_fVolume2 = 0;

	return 1;
}

LRESULT CVolumeDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CVolumeDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	ComponiRicercaRange(pStrWhere, m_fMisuraA1, m_fMisuraA2, "EEsami.MisuraA");
	ComponiRicercaRange(pStrWhere, m_fMisuraB1, m_fMisuraB2, "EEsami.MisuraB");
	ComponiRicercaRange(pStrWhere, m_fMisuraC1, m_fMisuraC2, "EEsami.MisuraC");
	ComponiRicercaRange(pStrWhere, m_fVolume1, m_fVolume2, "EEsami.Volume");

	return 1;
}

long CVolumeDynForm::GetContenuto()
{
	return sub_volume;
}

BOOL CVolumeDynForm::CampoObbligatorioValido()
{
	return FALSE;
}

void CVolumeDynForm::UpdateVolume(float fMisuraA, float fMisuraB, float fMisuraC)
{
	CString strTemp;
	strTemp.Format("%.2f", fMisuraA * fMisuraB * fMisuraC * (float)0.52);
	SetDlgItemText(IDC_EDIT_VOLUME, strTemp);
}

void CVolumeDynForm::OnEnChangeMisuraABC()
{
	if (!m_bAutoUpdate)
	{
		CString strText;
		int nStartChar;
		int nEndChar;

		//

		GetDlgItemText(IDC_EDIT_MISURA_A, strText);

		strText.Replace(',','.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditMisuraA.GetSel(nStartChar, nEndChar);
		m_ctrlEditMisuraA.SetWindowText(strText);
		m_ctrlEditMisuraA.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fMisuraA = (float)atof(strText);

		//

		GetDlgItemText(IDC_EDIT_MISURA_B, strText);

		strText.Replace(',','.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditMisuraB.GetSel(nStartChar, nEndChar);
		m_ctrlEditMisuraB.SetWindowText(strText);
		m_ctrlEditMisuraB.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fMisuraB = (float)atof(strText);

		//

		GetDlgItemText(IDC_EDIT_MISURA_C, strText);

		strText.Replace(',', '.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditMisuraC.GetSel(nStartChar, nEndChar);
		m_ctrlEditMisuraC.SetWindowText(strText);
		m_ctrlEditMisuraC.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fMisuraC = (float)atof(strText);

		//

		UpdateVolume(fMisuraA, fMisuraB, fMisuraC);
	}
}