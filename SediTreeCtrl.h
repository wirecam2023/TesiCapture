#ifndef _SEDITREECTRL_H_
	#define _SEDITREECTRL_H_

class CSediTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CSediTreeCtrl)

public:

	CSediTreeCtrl();
	virtual ~CSediTreeCtrl();

protected:

	DECLARE_MESSAGE_MAP()

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#endif /* _SEDITREECTRL_H_ */