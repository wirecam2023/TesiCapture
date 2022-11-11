#ifndef _EXTEDIT_H_
	#define _EXTEDIT_H_

class CBaseSet;

class CExtEdit : public CEdit
{
	DECLARE_DYNCREATE (CExtEdit)

public:

	CExtEdit();
	virtual ~CExtEdit();

	void SetParam(CWnd* pParentForm, long lComboDefine, CBaseSet* pSet, long* pIdEsame, CString* pStrParent, int nMaxLen);
	void SetParam(CWnd* pParentForm, long lComboDefine, CBaseSet* pSet, long* pIdEsame, long* pNumParent, int nMaxLen);
	void SetParam(BOOL bMoreFields, BOOL bSameMultipleSelect, BOOL bOrderByString, BOOL bUseCombo, BOOL bUppercase);

	long m_lContatore;

	CString m_strRicerca;
	CString m_strRicercaView;

protected:

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:

	BOOL OpenComboMenu(BOOL& bIsOK, CString strValue);

	void OpenDialog();
	BOOL OpenDialog(BOOL bUpdate, CString strValue);

	//

	BOOL m_bMoreFields;
	BOOL m_bOrderByString;
	BOOL m_bSameMultipleSelect;
	BOOL m_bUppercase;
	BOOL m_bUseComboEdit;

	int m_nMaxLen;

	long m_lComboDefine;

	//

	CBaseSet* m_pSet;

	long* m_pIdEsame;
	long* m_pNumOutput;

	CString* m_pStrEdit;
	CString* m_pStrOutput;

	CWnd* m_pParentView;

};

#endif /* _EXTEDIT_H_ */