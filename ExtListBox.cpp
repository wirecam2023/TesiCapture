#include "stdafx.h"
#include "Endox.h"
#include "ExtListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExtListBox::CExtListBox()
{
}

CExtListBox::~CExtListBox()
{
}

BEGIN_MESSAGE_MAP(CExtListBox, CListBox)
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CExtListBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int nCurSel = GetCurSel();
	int nFindSel = FindString(nCurSel, CString((TCHAR)nChar, (int)nRepCnt));
	
	if (nFindSel < 0)
		nFindSel = FindString(-1, CString((TCHAR)nChar, (int)nRepCnt));

	if (nFindSel >= 0)
	{
		SetCurSel(nFindSel);

		WPARAM wParam = MAKEWPARAM(GetDlgCtrlID(), LBN_SELCHANGE);

		GetParent()->SendNotifyMessage(WM_COMMAND, wParam, (LPARAM)GetSafeHwnd());
	}
}