#pragma once

// CSmartCardPinDlg dialog

class CSmartCardPinDlg : public CDialog
{
	DECLARE_DYNAMIC(CSmartCardPinDlg)

public:
	CSmartCardPinDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSmartCardPinDlg();

// Dialog Data
	enum { IDD = IDD_SMART_CARD_PIN };

	CString m_strPin;

	INT_PTR DoModal();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CStaticLocalize m_ctrlStatic1,
		            m_ctrlStatic2;
	CButtonLocalize m_ctrlButton1,
		            m_ctrlButton2;

	CString m_strUser;
};
