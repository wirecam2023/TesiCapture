#ifndef _WAITREMOTETHREADDLG_H_
	#define _WAITREMOTETHREADDLG_H_

class CWaitRemoteThreadDlg : public CDialog
{

	DECLARE_DYNAMIC(CWaitRemoteThreadDlg)

public:

	CWaitRemoteThreadDlg(CWnd* pParent, CEsamiView* pEsamiView, long lPaziente, long lEsame);
	virtual ~CWaitRemoteThreadDlg();

	enum { IDD = IDD_WAITING };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	LRESULT OnDestroyWaitRemoteThreadDlg(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateProgress(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	struct tagTHREAD
	{
		CEsamiView* pEsamiView;
		long lPaziente;
		long lEsame;
		HWND hWndParent;
	};

	//

	static UINT Thread(LPVOID pParam);

	//

	CAnimateCtrl m_ctrlAnim;
	CProgressCtrl m_ctrlProgress;

	//

	tagTHREAD m_ThreadParam;

	UINT m_idString;
	UINT m_iMax;

};

#endif /* _WAITREMOTETHREADDLG_H_ */