#ifndef _EDITSTRINGCHECKDLG_H_
	#define _EDITSTRINGCHECKDLG_H_

class CEditStringCheckDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditStringCheckDlg)

public:

	CEditStringCheckDlg(CWnd* pParent, const CString &sTitle, const CString &sValue, long lType, BOOL bChecked);
	CEditStringCheckDlg(CWnd* pParent, UINT idTitle, const CString &sValue, long lType, BOOL bChecked);
	~CEditStringCheckDlg();

	enum { IDD = IDD_EDITSTRINGCHECK_DLG };

	void GetColonnaSetting(CString &sValue, long &lType, BOOL &bChecked);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditValue();

private:

	CString m_sTitle;

	CString m_sValue;
	long m_lType;
	BOOL m_bChecked;

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlCheck01;

	CComboBox m_ctrlComboTipo;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;

};

#endif /* _EDITSTRINGCHECKDLG_H_ */