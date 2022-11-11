#include "stdafx.h"
#include "Endox.h"
#include "GetCodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGetCodeDlg::CGetCodeDlg(CWnd* pParent)
	: CDialog(CGetCodeDlg::IDD, pParent)
{
	m_lCode = 0;
	m_lCode2 = 0;
}

void CGetCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_LABEL, m_ctrlStaticLabel);
	DDX_Control(pDX, IDOK,             m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL,         m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_BTN_CHECKSTATUS, m_ctrlButtonCheckStatus);
	
	if (theApp.m_lRicercaCodiceEsame == 0)
	{
		DDX_Text(pDX, IDC_CODE, m_lCode);
		DDX_Text(pDX, IDC_CODE2, m_lCode2);
	}

	DDX_Text(pDX, IDC_CODE, m_sCode);
	DDX_Text(pDX, IDC_CODE2, m_sCode2);
}

BEGIN_MESSAGE_MAP(CGetCodeDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CHECKSTATUS, &CGetCodeDlg::OnBnClickedBtnCheckstatus)
END_MESSAGE_MAP()

BOOL CGetCodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!theApp.m_bPersonalizzazioniBrasileFleury)
	{
		GetDlgItem(IDC_CODE2)->EnableWindow(FALSE);
		if (theApp.m_lRicercaCodiceEsame != 4)
		{
			GetDlgItem(IDC_BTN_CHECKSTATUS)->EnableWindow(FALSE);
		}
	}

	theApp.LocalizeDialog(this, CGetCodeDlg::IDD, "GetCodeDlg");

	GotoDlgCtrl(GetDlgItem(IDC_CODE));

	return TRUE;
}

void CGetCodeDlg::OnOK()
{
	CString temp;
	if (theApp.m_lRicercaCodiceEsame == 0)
	{
		GetDlgItem(IDC_CODE)->GetWindowText(temp);

		if (atoi(temp) == 0)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALFANUMERIC));
			return;
		}
	}

	CDialog::OnOK();
}

void CGetCodeDlg::OnBnClickedBtnCheckstatus()
{
	bCheckStatus = TRUE;
	CDialog::OnOK();
}
