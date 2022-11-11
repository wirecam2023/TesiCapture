#include "stdafx.h"
#include "Endox.h"
#include "CronicitaCambiaDlg.h"

#include "MalattieCronicheSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCronicitaCambiaDlg, CDialog)

CCronicitaCambiaDlg::CCronicitaCambiaDlg(CWnd* pParent, long lIDCronicitaOld, long lIDCronicitaNew)
	: CDialog(CCronicitaCambiaDlg::IDD, pParent)
{
	m_lIDCronicitaOld = lIDCronicitaOld;
	m_lIDCronicitaNew = lIDCronicitaNew;

	m_nRadio = -1;
}

CCronicitaCambiaDlg::~CCronicitaCambiaDlg()
{
}

BEGIN_MESSAGE_MAP(CCronicitaCambiaDlg, CDialog)

	ON_BN_CLICKED(IDC_RADIO_MANTIENI, OnBnClickedRadioMantieni)
	ON_BN_CLICKED(IDC_RADIO_CAMBIA, OnBnClickedRadioCambia)
	ON_BN_CLICKED(IDC_BTN_CONFERMA, OnBnClickedBtnConferma)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CCronicitaCambiaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_RADIO_MANTIENI, m_ctrlRadioMantieni);
	DDX_Control(pDX, IDC_RADIO_CAMBIA, m_ctrlRadioCambia);
	DDX_Control(pDX, IDC_BTN_CONFERMA, m_ctrlBtnConferma);

	DDX_Radio(pDX, IDC_RADIO_MANTIENI, m_nRadio);
}

void CCronicitaCambiaDlg::OnCancel()
{
}

BOOL CCronicitaCambiaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlStatic01.SetFont(&theApp.m_fontBig);
	m_ctrlStatic02.SetFont(&theApp.m_fontBold);
	m_ctrlRadioMantieni.SetFont(&theApp.m_fontBig);
	m_ctrlRadioCambia.SetFont(&theApp.m_fontBig);
	m_ctrlBtnConferma.SetFont(&theApp.m_fontBold);

	//

	CString sRadio1;
	sRadio1.Format(theApp.GetMessageString(IDS_CRONICITA_MODIFICA1), CMalattieCronicheSet().GetDescrizione(m_lIDCronicitaOld).MakeUpper());
	m_ctrlRadioMantieni.SetWindowText(sRadio1);

	CString sRadio2;
	sRadio2.Format(theApp.GetMessageString(IDS_CRONICITA_MODIFICA2), CMalattieCronicheSet().GetDescrizione(m_lIDCronicitaNew).MakeUpper());
	m_ctrlRadioCambia.SetWindowText(sRadio2);

	//

	theApp.LocalizeDialog(this, CCronicitaCambiaDlg::IDD, "CronicitaCambiaDlg");
	return TRUE;
}

void CCronicitaCambiaDlg::OnOK()
{
}

HBRUSH CCronicitaCambiaDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hReturn = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_01:
		{
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}
	}

	return hReturn;
}

void CCronicitaCambiaDlg::OnBnClickedRadioMantieni()
{
	UpdateData(TRUE);
	m_ctrlBtnConferma.EnableWindow((m_nRadio >= 0) && (m_nRadio <= 1));
}

void CCronicitaCambiaDlg::OnBnClickedRadioCambia()
{
	UpdateData(TRUE);
	m_ctrlBtnConferma.EnableWindow((m_nRadio >= 0) && (m_nRadio <= 1));
}

void CCronicitaCambiaDlg::OnBnClickedBtnConferma()
{
	if (m_ctrlBtnConferma.IsWindowEnabled())
		CDialog::OnOK();
}

long CCronicitaCambiaDlg::GetResult()
{
	long lReturn = 0;

	switch(m_nRadio)
	{
		case 0:
		{
			lReturn = m_lIDCronicitaOld;
			break;
		}
		case 1:
		{
			lReturn = m_lIDCronicitaNew;
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	return lReturn;
}