#include "stdafx.h"
#include "Endox.h"
#include "AccessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAccessDlg::CAccessDlg(CWnd* pParent)
    : CDialog(CAccessDlg::IDD, pParent)
{
    Create(CAccessDlg::IDD, pParent);
}

BEGIN_MESSAGE_MAP(CAccessDlg, CDialog)
END_MESSAGE_MAP()

void CAccessDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BOOL CAccessDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

    CenterWindow();

    return TRUE;
}