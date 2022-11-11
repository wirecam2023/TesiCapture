#ifndef _EXTTERAPIA_H_
	#define _EXTTERAPIA_H_

class CBaseSet;

class CExtTerapia : public CEdit
{
	DECLARE_DYNCREATE (CExtTerapia)

public:

	CExtTerapia ();
	virtual ~CExtTerapia();

	CWnd*			m_pParentView;
	CBaseSet* 		m_pSet;
	long*			m_pIdEsame;
	CString*		m_pStrOutput;
	BOOL			m_bUseComboEdit;
	int				m_nMaxLen;
	long			m_nExtMode;

	void	SetParam(CWnd* pParentForm, CBaseSet* pSet, long* pIdEsame, CString* pStrParent, int nMaxLen);
	
	void	SetParam  (BOOL bUseCombo, int nIndexMode);
	BOOL 	OpenDialog(BOOL bUpdate, CString strValue);

	BOOL	OpenComboMenu(BOOL& bIsOK, CString strValue);

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()

};

#endif /* _EXTTERAPIA_H_ */