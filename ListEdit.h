#ifndef _LISTEDIT_H_
	#define _LISTEDIT_H_

class CListEdit : public CEdit
{
	DECLARE_DYNCREATE (CListEdit)

public:

	CListEdit ();
	virtual ~CListEdit();

	CWnd*		m_pParentView;
	CListBox*	m_pListBox;

	void SetParam(CWnd* pParentForm, CListBox* pListBox);

protected:

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};

#endif /* _LISTEDIT_H_ */