#ifndef _PATHNUMBERDLG_H_
	#define _PATHNUMBERDLG_H_

class CPathNumberDlg : public CDialog
{
	DECLARE_DYNAMIC(CPathNumberDlg)

public:

	CPathNumberDlg(CWnd* pParent, const CString &strTitle, const CString &sValue, const long &lValue);
	CPathNumberDlg(CWnd* pParent, UINT idTitle, const CString &sValue, const long &lValue);
	~CPathNumberDlg();

	enum { IDD = IDD_PATHNUMBER_DLG };

	void GetValue(CString& sValue, long& lValue);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnSearch();

private:

	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonOK;

	CEdit m_ctrlEditReport;
	CEdit m_ctrlEditCopie;

	CSpinButtonCtrl m_ctrlSpin;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;

	CString m_sTitle;
	CString m_sValue;
	long m_lValue;

};

#endif /* _PATHNUMBERDLG_H_ */