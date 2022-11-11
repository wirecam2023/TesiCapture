#ifndef _COMUNEEDIT_H_
	#define _COMUNEEDIT_H_

class CComuneEdit : public CEdit
{

public:

	CComuneEdit();
	
	void SetParam(CEsamiView* pEsamiView, long* pCampoComune, CWnd* pComuneEdit, CWnd* pCAPEdit, CWnd* pProvinciaEdit);

protected:

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:

	void OpenDialog();

	CEsamiView* m_pEsamiView;
	long* m_pCampoComune;
	CWnd* m_pComuneEdit;
	CWnd* m_pCAPEdit;
	CWnd* m_pProvinciaEdit;
};

#endif /* _COMUNEEDIT_H_ */