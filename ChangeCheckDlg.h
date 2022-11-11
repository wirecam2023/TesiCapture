#pragma once

class CChangeCheckDlg : public CDialog
{
	DECLARE_DYNAMIC(CChangeCheckDlg)

public:
	CChangeCheckDlg(LPCTSTR szLabel1, CWnd* pParentWnd = NULL);   // standard constructor
	virtual ~CChangeCheckDlg();

	// Dialog Data
	enum { IDD = IDD_CHANGE_CHECK };

	void SetCheckValue1(BOOL bCheckValue);
	BOOL GetCheckValue1();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButton1, m_ctrlButton2;
	CString m_strLabel1;
	BOOL m_bCheck1;
};