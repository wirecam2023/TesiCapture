#include "stdafx.h"
#include "Endox.h"
#include "ExportWaitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExportWaitDlg::CExportWaitDlg(long nItem, CWnd* pParent)
	: CDialog(CExportWaitDlg::IDD, pParent)
{
	m_nItem = nItem;
}

CExportWaitDlg::~CExportWaitDlg()
{
	DestroyWindow();
}

void CExportWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
	DDX_Control(pDX, IDCANCEL,     m_ctrlButtonCancel);
}

BEGIN_MESSAGE_MAP(CExportWaitDlg, CDialog)
END_MESSAGE_MAP()

BOOL CExportWaitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlProgress.SetRange(0, short(m_nItem));
	m_ctrlProgress.SetPos(0);

	CenterWindow();

	theApp.LocalizeDialog(this, CExportWaitDlg::IDD, "ExportWaitDlg");

	return TRUE;
}
