#ifndef _EXTSTRUMENTIEDIT_H_
	#define _EXTSTRUMENTIEDIT_H_

class CStrumentiSet;
class CBaseSet;

class CExtStrumentiEdit : public CEdit
{
	DECLARE_DYNCREATE (CExtStrumentiEdit)

public:

	CExtStrumentiEdit();
	virtual ~CExtStrumentiEdit();

	CWnd*			m_pParentView;
	CBaseSet* 		m_pSet;
	long*			m_pIdEsame;
	CString*		m_pStrOutput;
	long*			m_pNumOutput;
	CString*		m_pStrEdit;
	BOOL			m_bUseComboEdit;
	int				m_nMaxLen;
	long			m_nExtMode;
	BOOL			m_bMoreFields;
	BOOL			m_bOrderByString;

	CString m_strRicerca, m_strRicercaView;

	void	SetParam(BOOL bMoreFields, BOOL bOrderByString, BOOL bUseCombo);
	void	SetParam(CWnd* pParentForm, CBaseSet* pSet, long* pIdEsame, CString* pStrParent, int nMaxLen);
	
	BOOL 	OpenDialog(BOOL bUpdate, CString strValue);

	BOOL	OpenStrumentiMenu(BOOL& bIsOK, CString strValue);

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );

	DECLARE_MESSAGE_MAP()
};

#endif /* _EXTSTRUMENTIEDIT_H_ */