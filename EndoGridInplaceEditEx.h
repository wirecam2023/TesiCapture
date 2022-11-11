#pragma once

class CEndoGridInplaceEditEx : public CXTPPropertyGridInplaceEdit
{
	DECLARE_DYNAMIC(CEndoGridInplaceEditEx)
public:
	CEndoGridInplaceEditEx(void);
	~CEndoGridInplaceEditEx(void);

protected:
	void NotifyDirty();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
};
