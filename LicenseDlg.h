#pragma once

// CLicenseDlg dialog

class CLicenseDlg : protected CDialog
{
	DECLARE_DYNAMIC(CLicenseDlg)

public:
	CLicenseDlg(ULONGLONG lActivationsToCheck, CWnd* pParentWnd = NULL);   // standard constructor
	virtual ~CLicenseDlg();

// Dialog Data
	enum { IDD = IDD_LICENSE };

	INT_PTR DoModal();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()

	CString m_strStation;
	CString m_strActivation[8];
	ULONGLONG m_lActivationsToCheck;

	class CLicenseEdit : public CEdit
	{
	public:
		CLicenseEdit();

		void SetNextEdit(CLicenseEdit* pNextEdit);
		void SetPrevEdit(CLicenseEdit* pPrevEdit);

		CLicenseEdit* GetNextEdit() { return m_pNextEdit; }
		CLicenseEdit* GetPrevEdit() { return m_pPrevEdit; }

	protected:
		afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		LRESULT OnMessagePaste(WPARAM wParam, LPARAM lParam);
		DECLARE_MESSAGE_MAP()

		CLicenseEdit* m_pNextEdit, *m_pPrevEdit;
	};

	CLicenseEdit m_ctrlEdit[8];

	static const UINT CLicenseDlg::m_idEdit[8];

private:

	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;

	CButtonLocalize m_ctrlBtnOK;
	CButtonLocalize m_ctrlBtnCancel;

};
