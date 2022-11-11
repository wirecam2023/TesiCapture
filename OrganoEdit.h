#ifndef _ORGANOEDIT_H_
	#define _ORGANOEDIT_H_

class COrganoEdit : public CEdit
{

public:

	COrganoEdit();

	long m_lIDSede;

	void SetParam(CEsamiView* pEsamiView, CWnd* pOrganoEdit, CWnd* pSedeEdit, CWnd* pParent = NULL);

protected:

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:

	void OpenDialog();

	CEsamiView* m_pEsamiView;
	CWnd* m_pOrganoEdit;
	CWnd* m_pSedeEdit;

	CWnd* m_pParent;
};

#endif /* _ORGANOEDIT_H_ */