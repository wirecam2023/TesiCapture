#ifndef _MYLISTBOX_H_
	#define _MYLISTBOX_H_

class CMyListBox : public CListBox
{
	DECLARE_DYNAMIC(CMyListBox)

public:

	CMyListBox();
	virtual ~CMyListBox();

	BOOL EnableWindow(BOOL bEnable = TRUE);
	BOOL IsWindowEnabled();

protected:

	virtual void PreSubclassWindow();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

private:

	BOOL m_bEnabled;

};

#endif /* _MYLISTBOX_H_ */