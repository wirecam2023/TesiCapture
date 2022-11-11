#ifndef _ENDOXBAR_H_
	#define _ENDOXBAR_H_

class CEndoxBar : public CToolBar
{
	DECLARE_DYNAMIC(CEndoxBar)

public:

	CEndoxBar();
	virtual ~CEndoxBar();

	BOOL Attach(WINDOWPLACEMENT& wpl);
	BOOL CreateEx(CWnd* pParentWnd, CWnd* pFrameWnd, UINT uiToolBar, UINT uiBitmapNormal, UINT uiBitmapHot, UINT uiBitmapDisabled);

	void DeleteButton(UINT id);

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

private:

	BOOL LoadTCToolBar(UINT uToolBar, UINT uToolBarHot, UINT uToolBarDisabled);
	BOOL SetTCToolBar(UINT uToolBarType, UINT uToolBar);
};

#endif /* _ENDOXBAR_H_ */