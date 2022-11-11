#ifndef _EXTINVIANTE_H_
	#define _EXTINVIANTE_H_

class CEsamiView;
class CInviantiSet;
class CBaseSet;

class CExtInviante : public CEdit
{
	DECLARE_DYNCREATE (CExtInviante)

public:

	CExtInviante();
	virtual ~CExtInviante();

	CString m_strRicerca;
	CString m_strRicercaView;

	void    SetParam(CWnd* pParentForm, CBaseSet* pSet, long* pInviante);
	
	BOOL 	OpenDialog(BOOL bUpdate, CString strValue);
	BOOL	OpenComboMenu(BOOL& bIsOK, CString strValue);

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()

private:

	CWnd* m_pParentView;
	CEsamiView* m_pEsamiView;
	CBaseSet* m_pSet;
	long* m_pInviante;

};

#endif /* _EXTINVIANTE_H_ */