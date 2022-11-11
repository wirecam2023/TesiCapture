#include "stdafx.h"
#include "Endox.h"
#include "EndoxListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEndoxListBox::CEndoxListBox(void)
{
}

BOOL CEndoxListBox::PreTranslateMessage(MSG* pMsg) 
{
	BOOL bMsgTranslate = FALSE;

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_DELETE) 
	{
		for (int i = 0; i < GetCount(); i++)
		{
			if (GetSel(i) > 0)
			{
				if (GetParent()->SendMessage(WM_NOTIFY_DELETE_STRING_LISTBOX, (WPARAM)GetSafeHwnd(), (LPARAM)i))
					DeleteString(i--);
			}
		}

		if (GetCount() == 0)
			GetParent()->PostMessage(WM_NOTIFY_EMPTY_LISTBOX, (WPARAM)GetSafeHwnd());

		bMsgTranslate = TRUE;
	}

	return (!bMsgTranslate) ? CListBox::PreTranslateMessage(pMsg) : TRUE;
}