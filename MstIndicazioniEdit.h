#ifndef _MSTINDICAZIONIEDIT_H_
	#define _MSTINDICAZIONIEDIT_H_

class CMstIndicazioniEdit : public CEdit
{
	DECLARE_DYNAMIC(CMstIndicazioniEdit)

public:

	CMstIndicazioniEdit();
	virtual ~CMstIndicazioniEdit();

	void SetParam(CWnd* pParentView, CEsamiView* pEsamiView);

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()

private:

	void OpenDialog();

	CWnd* m_pParentView;
	CEsamiView* m_pEsamiView;
};

#endif /* _MSTINDICAZIONIEDIT_H_ */