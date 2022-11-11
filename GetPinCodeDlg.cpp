#include "stdafx.h"
#include "Endox.h"
#include "GetPinCodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGetPinCodeDlg::CGetPinCodeDlg(CWnd* pParent)
	: CDialog(CGetPinCodeDlg::IDD, pParent)
{
	m_sPinCode = "";
}

void CGetPinCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_LABEL, m_ctrlStaticLabel);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);

	DDX_Text(pDX, IDC_PINCODE, m_sPinCode);
}

BEGIN_MESSAGE_MAP(CGetPinCodeDlg, CDialog)
END_MESSAGE_MAP()

BOOL CGetPinCodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CGetPinCodeDlg::IDD, "GetPinCodeDlg");
	return TRUE;
}