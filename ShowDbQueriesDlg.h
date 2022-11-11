#ifndef _SHOWDBQUERIESDLG_H_
	#define _SHOWDBQUERIESDLG_H_

class CShowDbQueriesDlg : public CResizableDialog
{

public:

    CShowDbQueriesDlg(CWnd* pParent);

	enum { IDD = IDD_SHOW_DB_QUERIES };

	void CreateModelessDialog(CWnd* pParent);

	void WriteLine(DWORD dwMilliseconds, CString strSQL, CString strComment);

protected:

    virtual void DoDataExchange(CDataExchange *pDX);
	virtual void OnCancel() { }
    virtual BOOL OnInitDialog();
	virtual void OnOK() { }

    DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnFind1();
	afx_msg void OnBnClickedBtnFind2();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnSave();

private:

	CEdit m_ctrlEdit;
	CButtonLocalize m_ctrlBtnFind1;
	CButtonLocalize m_ctrlBtnFind2;
	CButtonLocalize m_ctrlBtnReset;
	CButtonLocalize m_ctrlBtnSave;

	long m_lCounter;
	DWORD m_dwLast;

};

#endif  /* _SHOWDBQUERIESDLG_H_ */
