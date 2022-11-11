#ifndef _CHECKLISTTREECTRL_H_
	#define _CHECKLISTTREECTRL_H_

struct Color_Font
{
	COLORREF color;
	LOGFONT  logfont;
};

class CCheckListTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CCheckListTreeCtrl)

public:

	CCheckListTreeCtrl();
	virtual ~CCheckListTreeCtrl();

	BOOL SetMyCheck(HTREEITEM hItem, BOOL bCheck);
	void LoadSelectedItems(long lIDEsame);

	CList<long> m_listSelectedItem;

protected:

	DECLARE_MESSAGE_MAP()

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

private:

	BOOL SetCheck(HTREEITEM hItem, BOOL bCheck);

	CMap <void*, void*, Color_Font, Color_Font&> m_mapColorFont;

	long m_lIDEsame;

	int m_xRClick;
	int m_yRClick;

};

#endif /* _CHECKLISTTREECTRL_H_ */