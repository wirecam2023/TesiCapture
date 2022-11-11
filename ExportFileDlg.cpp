#include "stdafx.h"
#include "Endox.h"
#include "ExportFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExportFileDlg::CExportFileDlg(CWnd* pParent)
	: CDialog(CExportFileDlg::IDD, pParent)
{
	m_nTipoExport = 0;
}

void CExportFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_TIPO1, m_nTipoExport);
	DDX_Control(pDX, IDOK,     m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_TIPO1, m_ctrlButton1);
	DDX_Control(pDX, IDC_TIPO2, m_ctrlButton2);
	DDX_Control(pDX, IDC_TIPO3, m_ctrlButton3);
	DDX_Control(pDX, IDC_STATIC_GROUP, m_ctrlStaticGroup);
}

BEGIN_MESSAGE_MAP(CExportFileDlg, CDialog)
END_MESSAGE_MAP()

BOOL CExportFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	theApp.LocalizeDialog(this, CExportFileDlg::IDD, "ExportFileDlg");
	return TRUE;
}

void CExportFileDlg::OnOK() 
{
	UpdateData(TRUE);
	CDialog::OnOK();
}
