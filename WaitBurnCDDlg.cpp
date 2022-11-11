#include "stdafx.h"
#include "Endox.h"
#include "WaitBurnCDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CWaitBurnCDDlg, CDialog)

CWaitBurnCDDlg::CWaitBurnCDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitBurnCDDlg::IDD, pParent)
{
}

CWaitBurnCDDlg::~CWaitBurnCDDlg()
{
}

void CWaitBurnCDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ERR, m_ctrlStaticErr);
	DDX_Control(pDX, IDCANCEL,       m_ctrlButtonCancel);
}

BEGIN_MESSAGE_MAP(CWaitBurnCDDlg, CDialog)
END_MESSAGE_MAP()

// CWaitBurnCDDlg message handlers

BOOL CWaitBurnCDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	theApp.LocalizeDialog(this, CWaitBurnCDDlg::IDD, "WaitBurnCDDlg");
	return TRUE;
}

void CWaitBurnCDDlg::OnCancel()
{
	m_pParentWnd->SendMessage(WM_COMMAND, IDC_BTN_INTERROMPI);
	CDialog::OnCancel();
}