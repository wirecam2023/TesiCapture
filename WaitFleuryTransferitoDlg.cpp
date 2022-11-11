// WaitFleuryTransferitoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Endox.h"
#include "WaitFleuryTransferitoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CWaitFleuryTransferitoDlg dialog

IMPLEMENT_DYNAMIC(CWaitFleuryTransferitoDlg, CDialog)

CWaitFleuryTransferitoDlg::CWaitFleuryTransferitoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitFleuryTransferitoDlg::IDD, pParent)
{

}

CWaitFleuryTransferitoDlg::~CWaitFleuryTransferitoDlg()
{
}

void CWaitFleuryTransferitoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CWaitFleuryTransferitoDlg::CreateModelessDialog(CWnd* pParent)
{
	Create(CWaitFleuryTransferitoDlg::IDD, pParent);
	ShowWindow(SW_SHOW);
	//SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

BOOL CWaitFleuryTransferitoDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();
	
	CenterWindow();
	theApp.LocalizeDialog(this, CWaitFleuryTransferitoDlg::IDD, "WaitFleuryTransferitoDlg");
	
	
	return bReturn;
}


BEGIN_MESSAGE_MAP(CWaitFleuryTransferitoDlg, CDialog)
END_MESSAGE_MAP()


// CWaitFleuryTransferitoDlg message handlers
