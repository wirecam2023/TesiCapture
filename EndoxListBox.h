#pragma once

#define WM_NOTIFY_DELETE_STRING_LISTBOX   WM_USER + 0x1000
#define WM_NOTIFY_EMPTY_LISTBOX           WM_USER + 0x1001

class CEndoxListBox : public CListBox
{
public:
	CEndoxListBox(void);

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
