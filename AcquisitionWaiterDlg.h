#ifndef _ACQUISITIONWAITERDLG_H_
	#define _ACQUISITIONWAITERDLG_H_

class CAcquisitionWaiterDlg : public CDialog
{
	DECLARE_DYNAMIC(CAcquisitionWaiterDlg)

public:

	CAcquisitionWaiterDlg(CWnd* pParent);
	virtual ~CAcquisitionWaiterDlg();

	enum { IDD = IDD_ACQUISITION_WAITER };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel() { }
	virtual BOOL OnInitDialog();
	virtual void OnOK() { }

	DECLARE_MESSAGE_MAP()

	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:

	CAnimateCtrl m_ctrlAnim;
	CStaticLocalize m_ctrlStaticLabel;

	// --- //

	BOOL FindProc(LPTSTR szProcName);

};

#endif /* _ACQUISITIONWAITERDLG_H_ */