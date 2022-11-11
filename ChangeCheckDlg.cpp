#include "stdafx.h"
#include "Endox.h"
#include "ChangeCheckDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CChangeCheckDlg, CDialog)

CChangeCheckDlg::CChangeCheckDlg(LPCTSTR szLabel1, CWnd* pParentWnd)
: CDialog(CChangeCheckDlg::IDD, pParentWnd)
{
	m_strLabel1 = szLabel1;	
}

CChangeCheckDlg::~CChangeCheckDlg()
{
}

void CChangeCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_ctrlButton1);
	DDX_Control(pDX, IDOK, m_ctrlButton2);

	DDX_Check(pDX, IDC_CHECK_1, m_bCheck1);
}

BEGIN_MESSAGE_MAP(CChangeCheckDlg, CDialog)
END_MESSAGE_MAP()

BOOL CChangeCheckDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CChangeCheckDlg::IDD, "ChangeCheckDlg");

	if (!m_strLabel1.IsEmpty())
		GetDlgItem(IDC_CHECK_1)->SetWindowText(m_strLabel1);
	else
		GetDlgItem(IDC_CHECK_1)->ShowWindow(SW_HIDE);	

	return TRUE;
}

void CChangeCheckDlg::SetCheckValue1(BOOL bCheckValue)
{
	m_bCheck1 = bCheckValue;
}

BOOL CChangeCheckDlg::GetCheckValue1()
{
	return m_bCheck1;
}
