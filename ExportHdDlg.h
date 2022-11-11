#ifndef _EXPORTHDDLG_H_
	#define _EXPORTHDDLG_H_

class CExportDlg;

class CExportHdDlg : public CDialog
{
	DECLARE_DYNAMIC(CExportHdDlg)

public:

	CExportHdDlg(CWnd* pParent, CExportDlg* pExportDlg, int iNumExp);
	virtual ~CExportHdDlg();

	enum { IDD = IDD_EXPORT_PROGRESS_HD };

	CProgressCtrl m_ctrlProgress;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnInterrompi();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT nIDEvent);

	DECLARE_MESSAGE_MAP()

private:

	void ExportImmaginiSelezionate();

	CButtonLocalize m_ctrlBtnInterrompi;

	CExportDlg* m_pExportDlg;
	int m_iNumExp;
	BOOL m_bInterrompi;

};

#endif /* _EXPORTHDDLG_H_ */