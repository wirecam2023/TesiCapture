#ifndef _EXTDIAGNOSIICD9EDIT_H_
#define _EXTDIAGNOSIICD9EDIT_H_

class CExtDiagnosiICD9Edit : public CEdit
{
	DECLARE_DYNCREATE(CExtDiagnosiICD9Edit)

public:

	CExtDiagnosiICD9Edit();
	virtual ~CExtDiagnosiICD9Edit();

	void SetParam(CWnd* pParentForm, long* pIdEsame, long* pNumParent);

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

	long* m_pIdEsame;
	long* m_pIdDiagnosi;

	CWnd* m_pParentView;

};

#endif /* _EXTDIAGNOSIICD9EDIT_H_ */