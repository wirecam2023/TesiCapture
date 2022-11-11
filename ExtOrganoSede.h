#ifndef _EXTORGANOSEDE_H_
	#define _EXTORGANOSEDE_H_

class CEsamiView;
class CMstSediSet;
class CBaseSet;

class CExtOrganoSede : public CEdit
{
	DECLARE_DYNCREATE (CExtOrganoSede)

public:

	CExtOrganoSede();
	virtual ~CExtOrganoSede();

	CWnd*				m_pParentView;
	CEsamiView*			m_pEsamiView;
	CMstSediSet*		m_pSediSet;
	CBaseSet* 			m_pSet;
	CString*			m_pStrOutput;
	CString*			m_pStrOther[2];
	int					m_nMaxLen;
	long				m_nExtMode;
	CString				m_strTitle;

	CString             m_strRicerca;
	CString             m_strRicercaView;
	BOOL                m_bUpdateRecord;

	void	SetParam (CWnd* pParentForm, CMstSediSet* pSediSet, CBaseSet* pSet, CString* pStrParent, CString strTitle);
	void	SetParam (CEsamiView* pEsamiView, CString* strSede, CString* strTelefono);
	void    SetParam(CWnd* pParentForm, CMstSediSet* pSediSet, CBaseSet* pSet);
	
	void	SetParam  (int nIndexMode);
	BOOL 	OpenDialog(BOOL bUpdate, CString strValue);

	BOOL	OpenComboMenu(BOOL& bIsOK, CString strValue);

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};

#endif /* _EXTORGANOSEDE_H_ */