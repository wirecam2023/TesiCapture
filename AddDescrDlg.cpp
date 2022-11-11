#include "stdafx.h"
#include "Endox.h"
#include "AddDescrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAddDescrDlg::CAddDescrDlg(CWnd* pParent, CString strTitle, int nLenght, CString strInit, long nExtMode, BOOL bUpperCase)
	: CDialog(CAddDescrDlg::IDD, pParent)
{
	m_strDescription = "";
    
	m_nLenghtMax 		= nLenght; 
	m_strTitle 			= strTitle;
	m_strDescription 	= strInit;
	m_nExtMode 			= nExtMode;
	m_bUpperCase		= bUpperCase;
}

void CAddDescrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DESCRIZIONE, m_strDescription);
	DDV_MaxChars(pDX, m_strDescription, m_nLenghtMax);

	DDX_Control(pDX, IDC_STATIC_LABEL, m_ctrlStaticLabel);
	DDX_Control(pDX, IDOK,             m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL,         m_ctrlButtonCancel);
}

BEGIN_MESSAGE_MAP(CAddDescrDlg, CDialog)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAddDescrDlg message handlers

BOOL CAddDescrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Sandro 05/05/2010 - RIMA 10-028.5 //
	if (m_bUpperCase)
		GetDlgItem(IDC_EDIT_DESCRIZIONE)->ModifyStyle(0, ES_UPPERCASE);
    
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_DESCRIZIONE);
	long nVal = ::GetWindowLong(pEdit->GetSafeHwnd(), GWL_STYLE);
	
	SetWindowLong(pEdit->GetSafeHwnd(), GWL_STYLE, nVal|m_nExtMode);
	
	pEdit->RedrawWindow();
	
	theApp.LocalizeDialog(this, CAddDescrDlg::IDD, "AddDescrDlg");

	if (m_strTitle != "")
		SetWindowText(m_strTitle);

	return TRUE;
}