#ifndef _WAITBURNCDDLG_H_
	#define _WAITBURNCDDLG_H_

class CWaitBurnCDDlg : public CDialog
{
	DECLARE_DYNAMIC(CWaitBurnCDDlg)

public:

	CWaitBurnCDDlg(CWnd* pParent);
	virtual ~CWaitBurnCDDlg();

	enum { IDD = IDD_WAIT_BURN_CD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);

	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnOK() {};
	afx_msg void OnCancel();

	CStaticLocalize m_ctrlStaticErr;
	CButtonLocalize m_ctrlButtonCancel;
};

#endif /* _WAITBURNCDDLG_H_ */