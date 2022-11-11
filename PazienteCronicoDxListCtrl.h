#ifndef _PAZIENTECRONICODXLISTCTRL_H_
	#define _PAZIENTECRONICODXLISTCTRL_H_

typedef struct CellColor
{
	int nItem;
	int nSubItem;
	COLORREF crBackColor;
} STRUCT_CELLCOLOR;

class CPazienteCronicoSnListCtrl;

class CPazienteCronicoDxListCtrl : public CListCtrl
{

	DECLARE_DYNAMIC(CPazienteCronicoDxListCtrl)

public:

	CPazienteCronicoDxListCtrl();
	~CPazienteCronicoDxListCtrl();

	void AddCellColor(int nItem, int nSubItem, COLORREF crBackColor);
	BOOL DeleteAllItems();
	BOOL DeleteItem(int nItem);
	BOOL EnsureColumnVisible(int nColumn, BOOL bPartialOK);
	void HighlightCell(int nItem, int nSubItem);
	int InsertItem(int nItem, LPCTSTR lpszItem);
	void RedirectVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void RemoveAllCellColor();
	void SetBindedListCtrl(CPazienteCronicoSnListCtrl* pList);
	void SetItemHeight(int iItemHeight);
	BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText);
	void SetWheelNotify(BOOL bNotify) { m_bWheelNotify = bNotify; }

protected:

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	/*
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	*/

private:

	CList<STRUCT_CELLCOLOR> m_ctrlListCellColor;

	//

	CPazienteCronicoSnListCtrl* m_pBindedListCtrl;

	BOOL m_bWheelNotify;

	int m_iItemHeight;

};

#endif /* _PAZIENTECRONICODXLISTCTRL_H_ */