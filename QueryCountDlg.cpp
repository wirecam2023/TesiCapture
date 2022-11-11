#include "stdafx.h"
#include "Endox.h"
#include "QueryCountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CQueryCountDlg, CDialog)

CQueryCountDlg::CQueryCountDlg(CWnd* pParent)
	: CDialog(CQueryCountDlg::IDD, pParent)
{
}

CQueryCountDlg::~CQueryCountDlg()
{
}

BEGIN_MESSAGE_MAP(CQueryCountDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CLASSIC, OnBnClickedBtnClassic)
	ON_BN_CLICKED(IDC_BTN_COUNT, OnBnClickedBtnCount)
END_MESSAGE_MAP()

void CQueryCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CQueryCountDlg::OnBnClickedBtnClassic()
{
	EndDialog(222);
}

void CQueryCountDlg::OnBnClickedBtnCount()
{
	EndDialog(333);
}