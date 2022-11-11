#ifndef _EXTCOMBOTRANS_H_
	#define _EXTCOMBOTRANS_H_

class CEsamiView;
class CComboTransSet;
class CBaseSet;

class CExtComboTrans : public CEdit
{
	DECLARE_DYNCREATE (CExtComboTrans)

public:

	CExtComboTrans ();
	virtual ~CExtComboTrans();

	CWnd*					m_pParentView;
	CEsamiView*				m_pEsamiView;
	CComboTransSet*			m_pComboTransSet;
	CBaseSet* 				m_pSet;
	CString					m_strRicerca;
	CString					m_strRicercaView;

	void	SetParam(CWnd* pParentForm, CComboTransSet* pComboTransSet, CBaseSet* pSet, CEsamiView* pEsamiView);
	BOOL 	OpenDialog(BOOL bUpdate, CString strValue);

	BOOL	OpenComboMenu(BOOL& bIsOK, CString strValue);

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};

#endif /* _EXTCOMBOTRANS_H_ */