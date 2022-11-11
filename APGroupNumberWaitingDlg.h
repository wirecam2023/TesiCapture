#pragma once

class CAPGroupNumberWaitingDlg : public CDialog
{
	DECLARE_DYNAMIC(CAPGroupNumberWaitingDlg)

public:
	CAPGroupNumberWaitingDlg(CWnd* pParentWnd, long lExamID);
	virtual ~CAPGroupNumberWaitingDlg();

	enum { IDD = IDD_READYREPORT_WAITING };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()

private:

	long m_lExamID;

	BOOL ResultChanged();

};

