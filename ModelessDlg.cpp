#include "stdafx.h"
#include "Endox.h"
#include "ModelessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModelessDlg::CModelessDlg(CWnd* pParent, UINT idTitle, int maxPos, BOOL bShowStop)
	: CDialog(CModelessDlg::IDD, pParent)
{
	if (idTitle > 0)
		m_strTitle = theApp.GetMessageString(idTitle);

	m_bStop 	= FALSE;
	m_strInfo   = "";

	m_iMaxPos = maxPos;
	m_bShowStop = bShowStop;
}

void CModelessDlg::CreateModeless(CWnd* pParent)
{
	Create(CModelessDlg::IDD, pParent);
	ShowWindow(SW_SHOW);

	SetTitle("");

	MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void CModelessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STOP, m_ctrlButtonStop);
	DDX_Text(pDX, IDC_INFO,    m_strInfo);
	DDX_Text(pDX, IDC_TITLE,   m_strTitle);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
}

BEGIN_MESSAGE_MAP(CModelessDlg, CDialog)
	ON_BN_CLICKED(IDC_STOP, OnStop)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelessDlg message handlers

BOOL CModelessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();
	theApp.LocalizeDialog(this, CModelessDlg::IDD, "ModelessDlg");

	m_ctrlProgress.SetRange32(0, m_iMaxPos);
	m_ctrlButtonStop.ShowWindow(m_bShowStop);
	m_ctrlProgress.SetPos(0);	

	return TRUE;
}

void CModelessDlg::OnStop() 
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MODELESSDLG_CONFIRM), MB_YESNO) == IDYES)
		m_bStop = TRUE;
}

void CModelessDlg::SetTitle(CString strTitle)
{
	m_strTitle 	= strTitle;
	m_strInfo 	= "";

	UpdateData(FALSE);
}

void CModelessDlg::SetInfo(CString strInfo)
{
	m_strInfo 	= strInfo;

	m_ctrlProgress.SetPos(m_ctrlProgress.GetPos() + 1);
	UpdateData(FALSE);	
}
