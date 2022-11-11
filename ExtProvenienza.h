#ifndef _EXTPROVENIENZA_H_
#define _EXTPROVENIENZA_H_

class CEsamiView;
class CProvenienzaSet;
class CBaseSet;

class CExtProvenienza : public CEdit
{
	DECLARE_DYNCREATE(CExtProvenienza)

public:

	CExtProvenienza();
	virtual ~CExtProvenienza();

	CString m_strRicerca;
	CString m_strRicercaView;

	void    SetParam(CWnd* pParentForm, CBaseSet* pSet);

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

};

#endif /* _EXTPROVENIENZA_H_ */