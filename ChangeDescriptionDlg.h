#pragma once

class CChangeDescriptionDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CChangeDescriptionDlg)

public:
	CChangeDescriptionDlg(CString strTitle, CString strLabel1, CString strDescription1, long lFontSize, BOOL bBold, CWnd* pParent = NULL);
	//CChangeDescriptionDlg(CString strTitle, CString strLabel1, CString strLabel2, CString strDescription1, CString strDescription2, CWnd* pParent = NULL, BOOL bMultiLineEdit = FALSE);
	CChangeDescriptionDlg(CString strTitle, CString strLabel1, CString strLabel2, CString strLabel3, CString strDescription1, CString strDescription2, CString strDescription3, long lFontSize, BOOL bBold, CWnd* pParent = NULL);
	virtual ~CChangeDescriptionDlg();

	enum { IDD = IDD_CHANGE_DESCRIPTION };
	//enum { IDD_MULTI = IDD_CHANGE_DESCRIPTION_MULTI };

	CString m_strDescription1, m_strDescription2, m_strDescription3, m_strFontSize;
	BOOL m_bCheckBold;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CString m_strLabel1, m_strLabel2, m_strLabel3, m_strLabel4;
	CString m_strTitle;

	CButtonLocalize m_ctrlButtonOK, m_ctrlButtonCancel;
};