#include "stdafx.h"
#include "Endox.h"
#include "GetCalibDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGetCalibDlg::CGetCalibDlg(CWnd* pParent )
	: CDialog(CGetCalibDlg::IDD, pParent)
{
	m_userMis = 0;
	m_scrMis = 0;
}
             
void CGetCalibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_CAMPO_MISURA, m_userMis);
	DDV_MinMaxFloat(pDX, m_userMis, 0, 100000); 
	DDX_Text(pDX, IDC_CAMPO_MISURA_SCR, m_scrMis);
	DDV_MinMaxFloat(pDX, m_scrMis, 0, 100000); 
	DDX_Control(pDX, IDC_STATIC_REAL_DISTANCE, m_ctrlStaticRealDistance);
	DDX_Control(pDX, IDC_STATIC_MONITOR_DISTANCE, m_ctrlStaticMonitorDistance);
	DDX_Control(pDX, IDOK, m_ctrlOk);
	DDX_Control(pDX, IDCANCEL, m_ctrlCancel);

}

BOOL CGetCalibDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CGetCalibDlg::IDD, "GetCalibDlg");

	return TRUE;
}

BEGIN_MESSAGE_MAP(CGetCalibDlg, CDialog)
END_MESSAGE_MAP()