#include "stdafx.h"
#include "Endox.h"
#include "BMIDynForm.h"

#include "EsamiView.h"
#include "EsamiSet.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBMIDynForm::CBMIDynForm(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxDynForm(CBMIDynForm::IDD, pParent, pEsamiView)
{
	m_bAutoUpdate = FALSE;
}

CBMIDynForm::~CBMIDynForm(void)
{
}

BEGIN_MESSAGE_MAP(CBMIDynForm, CEndoxDynForm)

	ON_EN_CHANGE(IDC_PESO, OnEnChangePeso)
	ON_EN_CHANGE(IDC_ALTEZZA, OnEnChangeAltezza)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CBMIDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_bmi] == NULL)
	{
		pEsamiView->m_pDynForm[sub_bmi] = new CBMIDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_bmi] != NULL)
		{
			pEsamiView->m_pDynForm[sub_bmi]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_bmi]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_bmi]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_bmi]->CreateChildForm(CBMIDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CBMIDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ANAM_8, theApp.m_sAnamText[7]); // peso //
	DDX_Text(pDX, IDC_ANAM_9, theApp.m_sAnamText[8]); // altezza //
	DDX_Text(pDX, IDC_ANAM_10, theApp.m_sAnamText[9]); // BMI //

	DDX_Control(pDX, IDC_PESO, m_ctrlEditPeso);
	DDX_Control(pDX, IDC_ALTEZZA, m_ctrlEditAltezza);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		DDX_Text(pDX, IDC_PESO_1, m_fPeso1);
		DDX_Text(pDX, IDC_PESO_2, m_fPeso2);
		DDX_Text(pDX, IDC_ALTEZZA_1, m_fAltezza1);
		DDX_Text(pDX, IDC_ALTEZZA_2, m_fAltezza2);
		DDX_Text(pDX, IDC_BMI_1, m_fBMI1);
		DDX_Text(pDX, IDC_BMI_2, m_fBMI2);

		SetDlgItemText(IDC_PESO, "");
		SetDlgItemText(IDC_ALTEZZA, "");
		SetDlgItemText(IDC_BMI, "");
	}
	else
	{
		if (pDX->m_bSaveAndValidate)
		{
			// Sandro 03/02/2014 //

			CString strText;

			GetDlgItemText(IDC_PESO, strText);
			strText.Replace(',','.');
			if (strText.Right(1).Compare(".") == 0)
				strText = strText.Left(strText.GetLength() - 1);
			float fPeso = (float)atof(strText);
			strText.Format("%.2f", fPeso);
			SetDlgItemText(IDC_PESO, strText);

			GetDlgItemText(IDC_ALTEZZA, strText);
			strText.Replace(',','.');
			if (strText.Right(1).Compare(".") == 0)
				strText = strText.Left(strText.GetLength() - 1);
			float fAltezza = (float)atof(strText);
			strText.Format("%.2f", fAltezza);
			SetDlgItemText(IDC_ALTEZZA, strText);

			//

			DDX_FieldText(pDX, IDC_PESO, m_pEsamiView->m_pEsamiSet->m_fPeso, m_pEsamiView->m_pEsamiSet->GetRecordset());
			DDX_FieldText(pDX, IDC_ALTEZZA, m_pEsamiView->m_pEsamiSet->m_fAltezza, m_pEsamiView->m_pEsamiSet->GetRecordset());

			DDX_FieldText(pDX, IDC_BMI, m_pEsamiView->m_pEsamiSet->m_fBMI, m_pEsamiView->m_pEsamiSet->GetRecordset());
		}
		else
		{
			DDX_FieldText(pDX, IDC_PESO, m_pEsamiView->m_pEsamiSet->m_fPeso, m_pEsamiView->m_pEsamiSet->GetRecordset());
			DDX_FieldText(pDX, IDC_ALTEZZA, m_pEsamiView->m_pEsamiSet->m_fAltezza, m_pEsamiView->m_pEsamiSet->GetRecordset());

			UpdateBMI(m_pEsamiView->m_pEsamiSet->m_fPeso, m_pEsamiView->m_pEsamiSet->m_fAltezza);
		}
	}

	GetDlgItem(IDC_ANAM_8)->ShowWindow(theApp.m_bAnamVisi[7] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_PESO)->ShowWindow((theApp.m_bAnamVisi[7] ? SW_SHOW : SW_HIDE) && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_PESO_1)->ShowWindow((theApp.m_bAnamVisi[7] ? SW_SHOW : SW_HIDE) && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_PESO_2)->ShowWindow((theApp.m_bAnamVisi[7] ? SW_SHOW : SW_HIDE) && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_ANAM_9)->ShowWindow(theApp.m_bAnamVisi[8] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_ALTEZZA)->ShowWindow((theApp.m_bAnamVisi[8] ? SW_SHOW : SW_HIDE) && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_ALTEZZA_1)->ShowWindow((theApp.m_bAnamVisi[8] ? SW_SHOW : SW_HIDE) && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_ALTEZZA_2)->ShowWindow((theApp.m_bAnamVisi[8] ? SW_SHOW : SW_HIDE) && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_ANAM_10)->ShowWindow(theApp.m_bAnamVisi[9] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BMI)->ShowWindow((theApp.m_bAnamVisi[9] ? SW_SHOW : SW_HIDE) && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_BMI_1)->ShowWindow((theApp.m_bAnamVisi[9] ? SW_SHOW : SW_HIDE) && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
	GetDlgItem(IDC_BMI_2)->ShowWindow((theApp.m_bAnamVisi[9] ? SW_SHOW : SW_HIDE) && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
}

HBRUSH CBMIDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_ANAM_8:
		case IDC_ANAM_9:
		case IDC_ANAM_10:
		case IDC_PESO:
		case IDC_PESO_1:
		case IDC_PESO_2:
		case IDC_ALTEZZA:
		case IDC_ALTEZZA_1:
		case IDC_ALTEZZA_2:
		case IDC_BMI:
		case IDC_BMI_1:
		case IDC_BMI_2:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hReturn;
}

BOOL CBMIDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_ANAM_8, CSize(0, 50), CSize(33, 50));
	AddAnchor(IDC_ANAM_9, CSize(33, 50), CSize(66, 50));
	AddAnchor(IDC_ANAM_10, CSize(66, 50), CSize(100, 50));
	AddAnchor(IDC_PESO, CSize(0, 50), CSize(33, 50));
	AddAnchor(IDC_PESO_1, CSize(0, 50), CSize(17, 50));
	AddAnchor(IDC_PESO_2, CSize(17, 50), CSize(33, 50));
	AddAnchor(IDC_ALTEZZA, CSize(33, 50), CSize(66, 50));
	AddAnchor(IDC_ALTEZZA_1, CSize(33, 50), CSize(50, 50));
	AddAnchor(IDC_ALTEZZA_2, CSize(50, 50), CSize(66, 50));
	AddAnchor(IDC_BMI, CSize(66, 50), CSize(100, 50));
	AddAnchor(IDC_BMI_1, CSize(66, 50), CSize(83, 50));
	AddAnchor(IDC_BMI_2, CSize(83, 50), CSize(100, 50));

	theApp.LocalizeDialog(this, CBMIDynForm::IDD, "BMIDynForm");

	return bReturn;
}

LRESULT CBMIDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CBMIDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CBMIDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	SendDlgItemMessage(IDC_PESO, EM_SETREADONLY, wParam, lParam);
	SendDlgItemMessage(IDC_ALTEZZA, EM_SETREADONLY, wParam, lParam);
	// SendDlgItemMessage(IDC_BMI, EM_SETREADONLY, wParam, lParam);

	return 1;
}

LRESULT CBMIDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_fPeso1 = 0;
	m_fPeso2 = 0;
	m_fAltezza1 = 0;
	m_fAltezza2 = 0;
	m_fBMI1 = 0;
	m_fBMI2 = 0;

	return 1;
}

LRESULT CBMIDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CBMIDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	ComponiRicercaRange(pStrWhere, m_fPeso1, m_fPeso2, "EEsami.Peso");
	ComponiRicercaRange(pStrWhere, m_fAltezza1, m_fAltezza2, "EEsami.Altezza");
	ComponiRicercaRange(pStrWhere, m_fBMI1, m_fBMI2, "EEsami.BMI");

	return 1;
}

long CBMIDynForm::GetContenuto()
{
	return sub_bmi;
}

BOOL CBMIDynForm::CampoObbligatorioValido()
{
	return FALSE;
}

void CBMIDynForm::UpdateBMI(float fPeso, float fAltezza)
{
	if ((fPeso > 0) && (fAltezza > 0))
	{
		CString strTemp;
		strTemp.Format("%.2f", (fPeso * 10000.0f) / (fAltezza * fAltezza));
		SetDlgItemText(IDC_BMI, strTemp);
	}
	else
	{
		SetDlgItemText(IDC_BMI, "0.00");
	}
}

void CBMIDynForm::OnEnChangePeso()
{
	if (!m_bAutoUpdate)
	{
		CString strText;
		int nStartChar;
		int nEndChar;

		//

		GetDlgItemText(IDC_PESO, strText);

		strText.Replace(',','.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditPeso.GetSel(nStartChar, nEndChar);
		m_ctrlEditPeso.SetWindowText(strText);
		m_ctrlEditPeso.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fPeso = (float)atof(strText);

		//

		GetDlgItemText(IDC_ALTEZZA, strText);

		strText.Replace(',','.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditAltezza.GetSel(nStartChar, nEndChar);
		m_ctrlEditAltezza.SetWindowText(strText);
		m_ctrlEditAltezza.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fAltezza = (float)atof(strText);

		//

		UpdateBMI(fPeso, fAltezza);
	}
}

void CBMIDynForm::OnEnChangeAltezza()
{
	if (!m_bAutoUpdate)
	{
		CString strText;
		int nStartChar;
		int nEndChar;

		//

		GetDlgItemText(IDC_PESO, strText);

		strText.Replace(',','.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditPeso.GetSel(nStartChar, nEndChar);
		m_ctrlEditPeso.SetWindowText(strText);
		m_ctrlEditPeso.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fPeso = (float)atof(strText);

		//

		GetDlgItemText(IDC_ALTEZZA, strText);

		strText.Replace(',','.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditAltezza.GetSel(nStartChar, nEndChar);
		m_ctrlEditAltezza.SetWindowText(strText);
		m_ctrlEditAltezza.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fAltezza = (float)atof(strText);

		//

		UpdateBMI(fPeso, fAltezza);
	}
}
