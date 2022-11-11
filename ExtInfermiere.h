#ifndef _EXTINFERMIERE_H_
	#define _EXTINFERMIERE_H_

class CEsamiView;
class CBaseSet;

class CExtInfermiere : public CEdit
{
	DECLARE_DYNCREATE (CExtInfermiere)

public:

	CExtInfermiere ();
	virtual ~CExtInfermiere();

	CWnd*				m_pParentView;
	CEsamiView*			m_pEsamiView;
	CBaseSet* 			m_pSet;
	CString             m_strRicerca;
	CString             m_strRicercaView;

	void	SetParam(CWnd* pParentForm, CBaseSet* pSet);
	BOOL 	OpenDialog(BOOL bUpdate, CString strValue);
	BOOL	OpenComboMenu(BOOL& bIsOK, CString strValue);

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};

#endif /* _EXTINFERMIERE_H_ */