#include "stdafx.h"
#include "Endox.h"
#include "CalibNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CCalibNameDlg, CDialog)

CCalibNameDlg::CCalibNameDlg(CWnd* pParent)
	: CDialog(CCalibNameDlg::IDD, pParent)
{
	m_strName = "";
}

BEGIN_MESSAGE_MAP(CCalibNameDlg, CDialog)
END_MESSAGE_MAP()

void CCalibNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_NOME, m_strName);

	DDX_Control(pDX, IDCANCEL, m_ctrlCancel);
	DDX_Control(pDX, IDOK, m_ctrlOK);
}

void CCalibNameDlg::OnOK()
{
	UpdateData(TRUE);
	m_strName.Replace(' ', '_');
	UpdateData(FALSE);
	
	CDialog::OnOK();
}
