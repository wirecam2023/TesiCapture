#ifndef _EXPORTWAITDLG_H_
	#define _EXPORTWAITDLG_H_

class CExportWaitDlg : public CDialog
{

public:

	CExportWaitDlg(long nItem, CWnd* pParent = NULL);
	~CExportWaitDlg();

	enum { IDD = IDD_EXPORT_WAIT };

	CProgressCtrl m_ctrlProgress;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonCancel;
	long m_nItem;

};

#endif /* _EXPORTWAITDLG_H_ */