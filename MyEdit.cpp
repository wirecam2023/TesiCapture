#include "stdafx.h"
#include "Endox.h"
#include "MyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
END_MESSAGE_MAP()

BOOL CMyEdit::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_TAB || pMsg->wParam == VK_RETURN))
		if ((GetWindowLong(GetSafeHwnd(), GWL_STYLE) & ES_READONLY) == 0)
			if (CWnd* pWnd = GetParent())
				pWnd->PostMessage(EPM_CHECKVALUE, (WPARAM)GetDlgCtrlID(), (LPARAM)pMsg->wParam);

	return CEdit::PreTranslateMessage(pMsg);
}