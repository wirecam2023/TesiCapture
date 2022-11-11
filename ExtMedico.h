#ifndef _EXT_MEDICO_H_
	#define _EXT_MEDICO_H_

class CEsamiView;
class CMediciSet;
class CBaseSet;

class CExtMedico : public CEdit
{
	DECLARE_DYNCREATE (CExtMedico)

public:

	CExtMedico();
	virtual ~CExtMedico();

	CWnd*				m_pParentView;
	CEsamiView*			m_pEsamiView;
	CBaseSet* 			m_pSet;
	CString*			m_pStrOutput;
	CString*			m_pStrOther[2];
	int					m_nMaxLen;
	long				m_nExtMode;
	CString				m_strTitle;

	CString             m_strRicerca;
	CString             m_strRicercaView;
	BOOL                m_bUpdateRecord;

	void	SetParam (CWnd* pParentForm, CBaseSet* pSet, CString* pStrParent, int nMaxLen, CString strTitle);
	void	SetParam (CEsamiView* pEsamiView, CString* strSede, CString* strTelefono);
	void    SetParam(CWnd* pParentForm, CBaseSet* pSet);
	
	void	SetParam  (int nIndexMode);
	BOOL 	OpenDialog(BOOL bUpdate, CString strValue);

	BOOL	OpenComboMenu(BOOL& bIsOK, CString strValue);
	CString GetCurrentUtentiMedici();

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};

#endif /* _EXTMEDICO_H_ */