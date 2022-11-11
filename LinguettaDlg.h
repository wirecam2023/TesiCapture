#pragma once

class CLinguettaDlg : public CDialog
{

	DECLARE_DYNAMIC(CLinguettaDlg)

public:

	CLinguettaDlg(CWnd* pParent, BOOL bAddNew, CTabCtrl* pTabCtrl);
	virtual ~CLinguettaDlg();

	enum { IDD = IDD_LINGUETTA };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedRadio();
	afx_msg void OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit();

	CSpinButtonCtrl m_ctrlSpin;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CStaticLocalize m_ctrlStatic7;
	CButtonLocalize m_ctrlButton1;
	CButtonLocalize m_ctrlButton2;

	DECLARE_MESSAGE_MAP()

private:

	BOOL m_bAddNew;
	CTabCtrl* m_pTabCtrl;

	long m_lIndex;
	long m_lOldIndex;
	LPARAM m_LParam;
	CString m_sEditText;
	CString m_sOldEditText;
	long m_lOldAlbum;
	int m_nRadioAlbum;
	BOOL m_bOldCheck;
	BOOL m_bCheck;
};
