#include "stdafx.h"
#include "Endox.h"
#include "QueryOnlyPatiensDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CQueryOnlyPatiensDlg, CDialog)

CQueryOnlyPatiensDlg::CQueryOnlyPatiensDlg(CWnd* pParent)
	: CDialog(CQueryOnlyPatiensDlg::IDD, pParent)
{
}

CQueryOnlyPatiensDlg::~CQueryOnlyPatiensDlg()
{
}

BEGIN_MESSAGE_MAP(CQueryOnlyPatiensDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CLASSIC, OnBnClickedBtnClassic)
	ON_BN_CLICKED(IDC_BTN_ONLYPATIENS, OnBnClickedBtnOnlyPatiens)
END_MESSAGE_MAP()

void CQueryOnlyPatiensDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CQueryOnlyPatiensDlg::OnBnClickedBtnClassic()
{
	EndDialog(222);
}

void CQueryOnlyPatiensDlg::OnBnClickedBtnOnlyPatiens()
{
	EndDialog(333);
}