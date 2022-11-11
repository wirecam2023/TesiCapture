#ifndef _MODELESSDLG_H_
	#define _MODELESSDLG_H_

class CModelessDlg : public CDialog
{

public:

	CModelessDlg(CWnd* pParent = NULL, UINT idTitle = 0, int maxPos = 9999, BOOL bShowStop=TRUE);

	enum { IDD = IDD_IMM_TRASF };

	CString	m_strInfo;
	CString	m_strTitle;
	BOOL	m_bStop;
	CProgressCtrl m_ctrlProgress;

	void SetTitle(CString strTitle);
	void SetInfo(CString strInfo);
	void CreateModeless(CWnd* pParent);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnStop();
	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonStop;

private:
	int m_iMaxPos;
	BOOL m_bShowStop;
};

#endif /* _MODELESSDLG_H_ */