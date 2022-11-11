#pragma once


// CWaitFleuryTransferitoDlg dialog

class CWaitFleuryTransferitoDlg : public CDialog
{
	DECLARE_DYNAMIC(CWaitFleuryTransferitoDlg)

public:
	CWaitFleuryTransferitoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWaitFleuryTransferitoDlg();

// Dialog Data
	enum { IDD = IDD_WAITING_FLEURY_TRANSFERITO };

	void CreateModelessDialog(CWnd* pParent);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
