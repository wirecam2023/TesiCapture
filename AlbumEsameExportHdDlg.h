#ifndef _ALBUMESAMEEXPORTHDDLG_H_
	#define _ALBUMESAMEEXPORTHDDLG_H_

class CAlbumEsameExportHdDlg : public CDialog
{
	DECLARE_DYNAMIC(CAlbumEsameExportHdDlg)

public:

	CAlbumEsameExportHdDlg(CWnd* pParent, CEsamiView* pEsamiView, int iNumExp, BOOL bAlert=TRUE, CString* outDirectory=NULL);
	virtual ~CAlbumEsameExportHdDlg();

	enum { IDD = IDD_EXPORT_PROGRESS_HD };

	CProgressCtrl m_ctrlProgress;
	BOOL m_bError;

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

	CEsamiView* m_pEsamiView;
	int m_iNumExp;
	BOOL m_bInterrompi;
	CString* m_sOutDirectory;
	BOOL m_bAlert;
};

#endif /*_ALBUMESAMEEXPORTHDDLG_H_ */