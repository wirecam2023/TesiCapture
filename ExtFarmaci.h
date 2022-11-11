#ifndef _FARMACIEXTEDIT_H_
	#define _FARMACIEXTEDIT_H_

class CFarmaciExtEdit : public CEdit
{

public:

	CFarmaciExtEdit();

	void SetParam(CEsamiView* pEsamiView, CWnd* pFarmaciEdit, BOOL bSingleSelection);

protected:

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:

	void OpenDialog();

	BOOL m_bSingleSelection;

	CEsamiView* m_pEsamiView;
	CWnd* m_pFarmaciEdit;
};

#endif /* _EXTFARMACI_H_ */