#ifndef _PAZIENTECRONICOSNLISTCTRL_H_
	#define _PAZIENTECRONICOSNLISTCTRL_H_

class CPazienteCronicoDxListCtrl;

class CPazienteCronicoSnListCtrl : public CListCtrl
{

	DECLARE_DYNAMIC(CPazienteCronicoSnListCtrl)

public:

	CPazienteCronicoSnListCtrl();
	~CPazienteCronicoSnListCtrl();

	int GetItemHeight();
	void RedirectVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void SetBindedListCtrl(CPazienteCronicoDxListCtrl* pList);
	void SetWheelNotify(BOOL bNotify) { m_bWheelNotify = bNotify; }

protected:

	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

private:

	CPazienteCronicoDxListCtrl* m_pBindedListCtrl;

	BOOL m_bWheelNotify;

};

#endif /* _PAZIENTECRONICOSNLISTCTRL_H_ */