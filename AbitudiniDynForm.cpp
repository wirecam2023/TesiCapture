#include "stdafx.h"
#include "Endox.h"
#include "AbitudiniDynForm.h"

#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAbitudiniDynForm::CAbitudiniDynForm(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxDynForm(CAbitudiniDynForm::IDD, pParent, pEsamiView)
{
	m_bAutoUpdate = FALSE;
}

CAbitudiniDynForm::~CAbitudiniDynForm(void)
{
}

BEGIN_MESSAGE_MAP(CAbitudiniDynForm, CEndoxDynForm)

	ON_EN_CHANGE(IDC_PESO, OnEnChangePeso)
	ON_EN_CHANGE(IDC_ALTEZZA, OnEnChangeAltezza)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CAbitudiniDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_abitudini] == NULL)
	{
		pEsamiView->m_pDynForm[sub_abitudini] = new CAbitudiniDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_abitudini] != NULL)
		{
			pEsamiView->m_pDynForm[sub_abitudini]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_abitudini]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_abitudini]->m_lIDFaseBlocco = lIDFaseBlocco;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_abitudini]->CreateChildForm(CAbitudiniDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CAbitudiniDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SUAB_00, m_ctrlStatic);

	DDX_Text(pDX, IDC_ANAM_1, theApp.m_sAnamText[0]); // fumo //
	DDX_Text(pDX, IDC_ANAM_2, theApp.m_sAnamText[1]); // sigarette //
	DDX_Text(pDX, IDC_ANAM_3, theApp.m_sAnamText[2]); // caffè //
	DDX_Text(pDX, IDC_ANAM_4, theApp.m_sAnamText[3]); // alcool //
	DDX_Text(pDX, IDC_ANAM_5, theApp.m_sAnamText[4]); // superalcolici //
	DDX_Text(pDX, IDC_ANAM_6, theApp.m_sAnamText[5]); // farmaci //
	DDX_Text(pDX, IDC_ANAM_7, theApp.m_sAnamText[6]); // assunzione //
	DDX_Text(pDX, IDC_ANAM_8, theApp.m_sAnamText[7]); // peso //
	DDX_Text(pDX, IDC_ANAM_9, theApp.m_sAnamText[8]); // altezza //
	DDX_Text(pDX, IDC_ANAM_10, theApp.m_sAnamText[9]); // BMI //

	DDX_Control(pDX, IDC_FUMO, m_ctrlTesto[0]);
	DDX_Control(pDX, IDC_SIGARETTE, m_ctrlTesto[1]);
	DDX_Control(pDX, IDC_CAFFE, m_ctrlTesto[2]);
	DDX_Control(pDX, IDC_ALCOOL, m_ctrlTesto[3]);
	DDX_Control(pDX, IDC_SUPERALCOLICI, m_ctrlTesto[4]);
	DDX_Control(pDX, IDC_FARMACI, m_ctrlFarmaci);
	DDX_Control(pDX, IDC_ASSUNZIONE, m_ctrlTesto[5]);
	DDX_Control(pDX, IDC_PESO, m_ctrlEditPeso);
	DDX_Control(pDX, IDC_ALTEZZA, m_ctrlEditAltezza);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		DDX_Text(pDX, IDC_FUMO,          m_ctrlTesto[0].m_strRicercaView);
		DDX_Text(pDX, IDC_SIGARETTE,     m_ctrlTesto[1].m_strRicercaView);
		DDX_Text(pDX, IDC_CAFFE,         m_ctrlTesto[2].m_strRicercaView);
		DDX_Text(pDX, IDC_ALCOOL,        m_ctrlTesto[3].m_strRicercaView);
		DDX_Text(pDX, IDC_SUPERALCOLICI, m_ctrlTesto[4].m_strRicercaView);
		DDX_Text(pDX, IDC_FARMACI,       m_ctrlFarmaci.m_strRicercaView);
		DDX_Text(pDX, IDC_ASSUNZIONE,    m_ctrlTesto[5].m_strRicercaView);
		DDX_Text(pDX, IDC_PESO_1,		 m_fPeso1);
		DDX_Text(pDX, IDC_PESO_2,		 m_fPeso2);
		DDX_Text(pDX, IDC_ALTEZZA_1,	 m_fAltezza1);
		DDX_Text(pDX, IDC_ALTEZZA_2,	 m_fAltezza2);
		DDX_Text(pDX, IDC_BMI_1,		 m_fBMI1);
		DDX_Text(pDX, IDC_BMI_2,		 m_fBMI2);

		SetDlgItemText(IDC_PESO, "");
		SetDlgItemText(IDC_ALTEZZA, "");
		SetDlgItemText(IDC_BMI, "");
	}
	else
	{
		DDX_FieldCombo(pDX, IDC_FUMO, m_pEsamiView->m_pEsamiSet->m_lFumo, m_pEsamiView->m_pEsamiSet, CMB_ANA_FUMO);
		DDX_FieldCombo(pDX, IDC_SIGARETTE, m_pEsamiView->m_pEsamiSet->m_lSigarette, m_pEsamiView->m_pEsamiSet, CMB_ANA_SIGA);
		DDX_FieldCombo(pDX, IDC_CAFFE, m_pEsamiView->m_pEsamiSet->m_lCaffe, m_pEsamiView->m_pEsamiSet, CMB_ANA_CAFF);
		DDX_FieldCombo(pDX, IDC_ALCOOL, m_pEsamiView->m_pEsamiSet->m_lAlcool, m_pEsamiView->m_pEsamiSet, CMB_ANA_ALCO);
		DDX_FieldCombo(pDX, IDC_SUPERALCOLICI, m_pEsamiView->m_pEsamiSet->m_lSuperAlcolici, m_pEsamiView->m_pEsamiSet, CMB_ANA_SUPE);
		DDX_FieldText(pDX, IDC_FARMACI, m_pEsamiView->m_pEsamiSet->m_sDenFarmaci, m_pEsamiView->m_pEsamiSet->GetRecordset());
		DDX_FieldCombo(pDX, IDC_ASSUNZIONE, m_pEsamiView->m_pEsamiSet->m_lAssunzione, m_pEsamiView->m_pEsamiSet, CMB_ANA_ASSU);

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

	GetDlgItem(IDC_ANAM_1)->ShowWindow(theApp.m_bAnamVisi[0] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_FUMO)->ShowWindow(theApp.m_bAnamVisi[0] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_ANAM_2)->ShowWindow(theApp.m_bAnamVisi[1] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_SIGARETTE)->ShowWindow(theApp.m_bAnamVisi[1] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_ANAM_3)->ShowWindow(theApp.m_bAnamVisi[2] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_CAFFE)->ShowWindow(theApp.m_bAnamVisi[2] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_ANAM_4)->ShowWindow(theApp.m_bAnamVisi[3] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_ALCOOL)->ShowWindow(theApp.m_bAnamVisi[3] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_ANAM_5)->ShowWindow(theApp.m_bAnamVisi[4] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_SUPERALCOLICI)->ShowWindow(theApp.m_bAnamVisi[4] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_ANAM_6)->ShowWindow(theApp.m_bAnamVisi[5] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_FARMACI)->ShowWindow(theApp.m_bAnamVisi[5] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_ANAM_7)->ShowWindow(theApp.m_bAnamVisi[6] ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_ASSUNZIONE)->ShowWindow(theApp.m_bAnamVisi[6] ? SW_SHOW : SW_HIDE);
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

HBRUSH CAbitudiniDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_ANAM_6:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}
		case IDC_SUAB_00:
		case IDC_ANAM_1:
		case IDC_ANAM_2:
		case IDC_ANAM_3:
		case IDC_ANAM_4:
		case IDC_ANAM_5:
		case IDC_ANAM_7:
		case IDC_ANAM_8:
		case IDC_ANAM_9:
		case IDC_ANAM_10:
		case IDC_FUMO:
		case IDC_SIGARETTE:
		case IDC_CAFFE:
		case IDC_ALCOOL:
		case IDC_SUPERALCOLICI:
		case IDC_FARMACI:
		case IDC_ASSUNZIONE:
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

BOOL CAbitudiniDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	GetDlgItem(IDC_SUAB_00)->SetFont(&theApp.m_fontBold);

	AddAnchor(IDC_SUAB_00, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_ANAM_1, CSize(0, 25), CSize(50, 25));
	AddAnchor(IDC_ANAM_2, CSize(0, 50), CSize(50, 50));
	AddAnchor(IDC_ANAM_3, CSize(50, 25), CSize(100, 25));
	AddAnchor(IDC_ANAM_4, CSize(0, 75), CSize(50, 75));
	AddAnchor(IDC_ANAM_5, CSize(0, 100), CSize(50, 100));
	AddAnchor(IDC_ANAM_6, CSize(50, 50), CSize(100, 50));
	AddAnchor(IDC_ANAM_7, CSize(50, 75), CSize(100, 75));
	AddAnchor(IDC_ANAM_8, CSize(50, 100), CSize(67, 100));
	AddAnchor(IDC_ANAM_9, CSize(67, 100), CSize(84, 100));
	AddAnchor(IDC_ANAM_10, CSize(84, 100), CSize(100, 100));
	AddAnchor(IDC_FUMO, CSize(0, 25), CSize(50, 25));
	AddAnchor(IDC_SIGARETTE, CSize(0, 50), CSize(50, 50));
	AddAnchor(IDC_CAFFE, CSize(50, 25), CSize(100, 25));
	AddAnchor(IDC_ALCOOL, CSize(0, 75), CSize(50, 75));
	AddAnchor(IDC_SUPERALCOLICI, CSize(0, 100), CSize(50, 100));
	AddAnchor(IDC_FARMACI, CSize(50, 50), CSize(100, 75));
	AddAnchor(IDC_ASSUNZIONE, CSize(50, 75), CSize(100, 75));
	AddAnchor(IDC_PESO, CSize(50, 100), CSize(67, 100));
	AddAnchor(IDC_PESO_1, CSize(51, 100), CSize(59, 100));
	AddAnchor(IDC_PESO_2, CSize(58, 100), CSize(67, 100));
	AddAnchor(IDC_ALTEZZA, CSize(67, 100), CSize(84, 100));
	AddAnchor(IDC_ALTEZZA_1, CSize(68, 100), CSize(76, 100));
	AddAnchor(IDC_ALTEZZA_2, CSize(75, 100), CSize(84, 100));
	AddAnchor(IDC_BMI, CSize(84, 100), CSize(100, 100));
	AddAnchor(IDC_BMI_1, CSize(85, 100), CSize(93, 100));
	AddAnchor(IDC_BMI_2, CSize(92, 100), CSize(100, 100));

	m_ctrlTesto[0].SetParam(this, CMB_ANA_FUMO, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame,	&m_pEsamiView->m_pEsamiSet->m_lFumo, 255);
	m_ctrlTesto[0].SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
	m_ctrlTesto[1].SetParam(this, CMB_ANA_SIGA, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame,	&m_pEsamiView->m_pEsamiSet->m_lSigarette, 255);
	m_ctrlTesto[1].SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
	m_ctrlTesto[2].SetParam(this, CMB_ANA_CAFF, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame,	&m_pEsamiView->m_pEsamiSet->m_lCaffe, 255);
	m_ctrlTesto[2].SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
	m_ctrlTesto[3].SetParam(this, CMB_ANA_ALCO, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame,	&m_pEsamiView->m_pEsamiSet->m_lAlcool, 255);
	m_ctrlTesto[3].SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
	m_ctrlTesto[4].SetParam(this, CMB_ANA_SUPE, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame,	&m_pEsamiView->m_pEsamiSet->m_lSuperAlcolici, 255);
	m_ctrlTesto[4].SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
	m_ctrlFarmaci.SetParam (this, CMB_ANA_FARM, m_pEsamiView->m_pEsamiSet, NULL,									&m_pEsamiView->m_pEsamiSet->m_sDenFarmaci, 3999);
	m_ctrlFarmaci.SetParam (TRUE, FALSE, TRUE, TRUE, FALSE);
	m_ctrlTesto[5].SetParam(this, CMB_ANA_ASSU, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame,	&m_pEsamiView->m_pEsamiSet->m_lAssunzione, 255);
	m_ctrlTesto[5].SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);

	theApp.LocalizeDialog(this, CAbitudiniDynForm::IDD, "AbitudiniDynForm");

	return bReturn;
}

LRESULT CAbitudiniDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CAbitudiniDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CAbitudiniDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		SendDlgItemMessage(IDC_FUMO, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_SIGARETTE, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_CAFFE, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_ALCOOL, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_SUPERALCOLICI, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_FARMACI, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_ASSUNZIONE, EM_SETREADONLY, wParam, lParam);
	}
	else
	{
		SendDlgItemMessage(IDC_FUMO, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_SIGARETTE, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_CAFFE, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_ALCOOL, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_SUPERALCOLICI, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_FARMACI, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_ASSUNZIONE, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_PESO, EM_SETREADONLY, wParam, lParam);
		SendDlgItemMessage(IDC_ALTEZZA, EM_SETREADONLY, wParam, lParam);
	}

	return 1;
}

LRESULT CAbitudiniDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < 6; i++)
	{
		m_ctrlTesto[i].m_strRicerca = "";
		m_ctrlTesto[i].m_strRicercaView = "";
	}
	m_ctrlFarmaci.m_strRicerca = "";
	m_ctrlFarmaci.m_strRicercaView = "";

	m_fPeso1 = 0;
	m_fPeso2 = 0;
	m_fAltezza1 = 0;
	m_fAltezza2 = 0;
	m_fBMI1 = 0;
	m_fBMI2 = 0;

	return 1;
}

LRESULT CAbitudiniDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CAbitudiniDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	ComponiRicercaRadioEx(pStrWhere, m_ctrlTesto[0].m_strRicerca, "EEsami.Fumo");
	ComponiRicercaRadioEx(pStrWhere, m_ctrlTesto[1].m_strRicerca, "EEsami.Sigarette");
	ComponiRicercaRadioEx(pStrWhere, m_ctrlTesto[2].m_strRicerca, "EEsami.Caffe");
	ComponiRicercaRadioEx(pStrWhere, m_ctrlTesto[3].m_strRicerca, "EEsami.Alcool");
	ComponiRicercaRadioEx(pStrWhere, m_ctrlTesto[4].m_strRicerca, "EEsami.Superalcolici");
	ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sDenFarmaci, "EEsami.Den_Farmaci", 1);
	ComponiRicercaRadioEx(pStrWhere, m_ctrlTesto[5].m_strRicerca, "EEsami.Assunzione");
	ComponiRicercaRange(pStrWhere, m_fPeso1, m_fPeso2, "EEsami.Peso");
	ComponiRicercaRange(pStrWhere, m_fAltezza1, m_fAltezza2, "EEsami.Altezza");
	ComponiRicercaRange(pStrWhere, m_fBMI1, m_fBMI2, "EEsami.BMI");

	return 1;
}

long CAbitudiniDynForm::GetContenuto()
{
	return sub_abitudini;
}

BOOL CAbitudiniDynForm::CampoObbligatorioValido()
{
	CString strEdit;
	GetDlgItemText(IDC_FARMACI, strEdit);

	if (!strEdit.IsEmpty())
		return TRUE;

	return FALSE;
}

void CAbitudiniDynForm::UpdateBMI(float fPeso, float fAltezza)
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

void CAbitudiniDynForm::OnEnChangePeso()
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

void CAbitudiniDynForm::OnEnChangeAltezza()
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
