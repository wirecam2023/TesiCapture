#pragma once

class CEndoGridInplaceEdit : public CXTPPropertyGridInplaceEdit
{
	DECLARE_DYNAMIC(CEndoGridInplaceEdit)

public:
	CEndoGridInplaceEdit(void);
	~CEndoGridInplaceEdit(void);

protected:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
};
