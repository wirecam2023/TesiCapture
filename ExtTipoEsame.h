#ifndef _EXTTIPOESAME_H_
	#define _EXTTIPOESAME_H_

class CEsamiView;
class CBaseSet;

class CExtTipoEsame : public CEdit
{
	DECLARE_DYNCREATE (CExtTipoEsame)

public:

	CExtTipoEsame();
	virtual ~CExtTipoEsame();

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

#endif /* _EXTTIPOESAME_H_ */