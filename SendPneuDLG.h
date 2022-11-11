#pragma once


// CSendPneuDLG dialog

class CSendPneuDLG : public CDialog
{
	DECLARE_DYNAMIC(CSendPneuDLG)

public:
	CSendPneuDLG(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSendPneuDLG();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SENDPNEU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool IsCancel;
	bool IsOnlyCard;
	bool IsWithPneu;
 	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOnlyCard();
	afx_msg void OnBnClickedWithPneu();
};
