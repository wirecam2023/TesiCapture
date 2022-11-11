#include "stdafx.h"
#include "Endox.h"
#include "MyCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMyCombo, CComboBox)

CMyCombo::CMyCombo()
{
}

CMyCombo::~CMyCombo()
{
}

BEGIN_MESSAGE_MAP(CMyCombo, CComboBox)
END_MESSAGE_MAP()

BOOL CMyCombo::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_TAB || pMsg->wParam == VK_RETURN))
		if ((GetWindowLong(GetSafeHwnd(), GWL_STYLE) & ES_READONLY) == 0)
			if (CWnd* pWnd = GetParent())
				pWnd->PostMessage(EPM_CHECKVALUE, (WPARAM)GetDlgCtrlID(), (LPARAM)pMsg->wParam);

	return CComboBox::PreTranslateMessage(pMsg);
}