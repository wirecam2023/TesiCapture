#include "stdafx.h"
#include "Endox.h"
#include "ChangeDescriptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CChangeDescriptionDlg, CXTResizeDialog)

CChangeDescriptionDlg::CChangeDescriptionDlg(CString strTitle, CString strLabel1, CString strDescription1, long lFontSize, BOOL bBold, CWnd* pParent)
: CXTResizeDialog(CChangeDescriptionDlg::IDD, pParent)
{
	m_strDescription1 = strDescription1;
	m_strLabel1 = strLabel1;
	m_strTitle = strTitle;
	m_strFontSize.Format("%li", lFontSize);
	m_bCheckBold = bBold;
}

/*CChangeDescriptionDlg::CChangeDescriptionDlg(CString strTitle, CString strLabel1, CString strLabel2, CString strDescription1, CString strDescription2, CWnd* pParent, BOOL bMultiLineEdit)
: CXTResizeDialog(bMultiLineEdit ? CChangeDescriptionDlg::IDD_MULTI : CChangeDescriptionDlg::IDD, pParent)
{
m_strDescription1 = strDescription1;
m_strDescription2 = strDescription2;

m_strLabel1 = strLabel1;
m_strLabel2 = strLabel2;
m_strTitle = strTitle;
}*/

CChangeDescriptionDlg::CChangeDescriptionDlg(CString strTitle, CString strLabel1, CString strLabel2, CString strLabel3, CString strDescription1, CString strDescription2, CString strDescription3, long lFontSize, BOOL bBold, CWnd* pParent)
	: CXTResizeDialog(CChangeDescriptionDlg::IDD, pParent)
{
	m_strDescription1 = strDescription1;
	m_strDescription2 = strDescription2;
	m_strDescription3 = strDescription3;

	m_strLabel1 = strLabel1;
	m_strLabel2 = strLabel2;
	m_strLabel3 = strLabel3;
	m_strTitle = strTitle;

	m_strFontSize.Format("%li", lFontSize);
	m_bCheckBold = bBold;
}

CChangeDescriptionDlg::~CChangeDescriptionDlg()
{
}

void CChangeDescriptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Text(pDX, IDC_DESCRIPTION_1, m_strDescription1);
	DDX_Text(pDX, IDC_DESCRIPTION_2, m_strDescription2);
	DDX_Text(pDX, IDC_DESCRIPTION_3, m_strDescription3);
	DDX_Text(pDX, IDC_LABEL_1, m_strLabel1);
	DDX_Text(pDX, IDC_LABEL_2, m_strLabel2);
	DDX_Text(pDX, IDC_LABEL_3, m_strLabel3);
	DDX_Check(pDX, IDC_CHECK_BOLD, m_bCheckBold);
	DDX_Text(pDX, IDC_EDIT_FONTSIZE, m_strFontSize);
}

BEGIN_MESSAGE_MAP(CChangeDescriptionDlg, CXTResizeDialog)
END_MESSAGE_MAP()

// CSSCentilesEditDlg message handlers

BOOL CChangeDescriptionDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	SetResize(IDC_DESCRIPTION_1, 0, 0, 1, 0);
	SetResize(IDC_DESCRIPTION_2, 0, 0, 1, 1);
	SetResize(IDC_DESCRIPTION_3, 0, 0, 1, 0);
	SetResize(IDC_STATIC_SIZE, 0, 0, 1, 0);
	SetResize(IDC_CHECK_BOLD, 0, 0, 1, 0);
	SetResize(IDC_EDIT_FONTSIZE, 0, 0, 1, 0);
	SetResize(IDOK, 1, 1, 1, 1);
	SetResize(IDCANCEL, 1, 1, 1, 1);

	theApp.LocalizeDialog(this, CChangeDescriptionDlg::IDD, "ChangeDescriptionDlg");
	SetWindowText(m_strTitle);

	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_DESCRIPTION_1);
	pEdit1->SetFocus();
	pEdit1->SetSel(-1);

	CEdit* pEdit2 = (CEdit*)GetDlgItem(IDC_DESCRIPTION_2);
	pEdit2->SetFocus();
	pEdit2->SetSel(-1);

	if (m_strLabel2.IsEmpty())
	{
		GetDlgItem(IDC_LABEL_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DESCRIPTION_2)->ShowWindow(SW_HIDE);
	}

	if (m_strLabel3.IsEmpty())
	{
		GetDlgItem(IDC_LABEL_3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DESCRIPTION_3)->ShowWindow(SW_HIDE);
	}

	CenterWindow();

	pEdit1->SetFocus();

	return FALSE;
}