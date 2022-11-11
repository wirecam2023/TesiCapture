#ifndef _EXTOSPEDALE_H_
	#define _EXTOSPEDALE_H_

class CExtOspedale : public CEdit
{
	DECLARE_DYNCREATE (CExtOspedale)

public:

	CExtOspedale();
	virtual ~CExtOspedale();

	BOOL OpenDialog(BOOL bUpdate, CString strValue);
	BOOL OpenComboMenu(BOOL& bIsOK, CString strValue);

	void SetParam(CWnd* pParentForm, long* plParent, int nMaxLen);
	void SetParam(int nIndexMode);

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()

private:

	int m_nMaxLen;

	long m_lExtMode;

	//

	long* m_plOutput;
	CWnd* m_pParentView;

};

#endif /* _EXTMEDICOCURANTE_H_ */