#ifndef _ENDOXMENU_H_
	#define _ENDOXMENU_H_

class CEndoxMenu : public CMenu
{

public:

	CEndoxMenu();
	virtual ~CEndoxMenu();

	BOOL LoadMenu(UINT nIDResource);
	// BOOL TrackPopupMenu(UINT nFlags, int x, int y, CWnd* pWnd, LPCRECT lpRect = 0);

};

#endif /* _ENDOXMENU_H_ */