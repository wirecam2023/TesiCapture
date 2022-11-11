#pragma once

class CNotesDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CNotesDlg)

public:
	CNotesDlg(CString* pString, CWnd* pParent = NULL);   // standard constructor
	virtual ~CNotesDlg();

	// Dialog Data
	enum { IDD = IDD_NOTES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CString* m_pNotes;

	CButtonLocalize m_ctrlButtonOK, m_ctrlButtonCancel;
};
