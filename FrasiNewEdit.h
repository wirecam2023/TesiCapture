#ifndef _FRASINEWEDIT_H_
	#define _FRASINEWEDIT_H_

class CFrasiNewEdit : public CEdit
{
	DECLARE_DYNAMIC(CFrasiNewEdit)

public:

	CFrasiNewEdit();
	virtual ~CFrasiNewEdit();

	void SetParam(CWnd* pParentView, CString strTitolo, long lPrePost);

protected:

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:

	void OpenDialog();

	CWnd* m_pParentView;
	CString m_strTitolo;
	long m_lPrePost;
};

#endif /* _FRASINEWEDIT_H_ */