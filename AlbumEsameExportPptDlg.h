#ifndef _ALBUMESAMEEXPORTPPTDLG_H_
	#define _ALBUMESAMEEXPORTPPTDLG_H_

class CAlbumEsameExportPptDlg : public CDialog
{
	DECLARE_DYNAMIC(CAlbumEsameExportPptDlg)

public:

	CAlbumEsameExportPptDlg(CWnd* pParent, CEsamiView* pEsamiView, int iNumExp);
	virtual ~CAlbumEsameExportPptDlg();

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
};

#endif /*_ALBUMESAMEEXPORTPPTDLG_H_ */