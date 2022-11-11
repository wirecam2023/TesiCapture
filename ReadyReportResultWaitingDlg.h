#pragma once

class CReadyReportResultWaitingDlg : public CDialog
{
	DECLARE_DYNAMIC(CReadyReportResultWaitingDlg)

public:
	CReadyReportResultWaitingDlg(CWnd* pParentWnd, long lClosedExamId, BOOL* bResult, CString* sResult);
	virtual ~CReadyReportResultWaitingDlg();

	enum { IDD = IDD_READYREPORT_WAITING };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()

private:

	BOOL* m_bResult;
	CString* m_sResult;

	long m_lClosedExamId;

	BOOL ResultChanged();

};

