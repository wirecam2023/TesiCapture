#include "stdafx.h"
#include "Endox.h"
#include "PasswordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPasswordDlg::CPasswordDlg(CWnd* pParent, CString sTitle, CString sPasswordInput)
	: CDialog(CPasswordDlg::IDD1, pParent)
{
	m_uiIDD = CPasswordDlg::IDD1;

	sTitle.Trim();
	sPasswordInput.Trim();
	ASSERT(!sPasswordInput.IsEmpty());

	m_sTitle = sTitle;
	m_sDescription = "";
	m_sPasswordInput = sPasswordInput;

	m_iCounter = 0;
	m_sPasswordUser = "";
}

CPasswordDlg::CPasswordDlg(CWnd* pParent, CString sTitle, CString sDescription, CString sPasswordInput)
	: CDialog(CPasswordDlg::IDD2, pParent)
{
	m_uiIDD = CPasswordDlg::IDD2;

	sTitle.Trim();
	sDescription.Trim();
	sPasswordInput.Trim();
	ASSERT(!sPasswordInput.IsEmpty());

	m_sTitle = sTitle;
	m_sDescription = sDescription;
	m_sPasswordInput = sPasswordInput;

	m_iCounter = 0;
	m_sPasswordUser = "";
}

BEGIN_MESSAGE_MAP(CPasswordDlg, CDialog)
END_MESSAGE_MAP()

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic);

	DDX_Text(pDX, IDC_PASSWORD, m_sPasswordUser);
}

BOOL CPasswordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, m_uiIDD, "PasswordDlg");

	if (m_uiIDD == CPasswordDlg::IDD2)
		SetDlgItemText(IDC_STATIC_2, m_sDescription);

	if (!m_sTitle.IsEmpty())
		SetWindowText(m_sTitle);

	return TRUE;
}

void CPasswordDlg::OnOK() 
{
	UpdateData(TRUE);

	m_sPasswordUser.Trim();
	if (!m_sPasswordUser.IsEmpty() && (m_sPasswordUser.CompareNoCase(m_sPasswordInput) == 0))
	{
		CDialog::OnOK();
		return;
	}

	m_sPasswordUser = "";
	UpdateData(FALSE);

	if (++m_iCounter > 2)
		OnCancel();
}