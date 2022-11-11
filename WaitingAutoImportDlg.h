#ifndef _WAITINGAUTOIMPORTDLG_H_
	#define _WAITINGAUTOIMPORTDLG_H_

class CAlbumForm;

class CWaitingAutoImportDlg : public CDialog
{
	DECLARE_DYNAMIC(CWaitingAutoImportDlg)

public:

	CWaitingAutoImportDlg(CWnd* pParent, CAlbumForm* pAlbumForm, BOOL p_bIsContinuousCapture = FALSE);
	virtual ~CWaitingAutoImportDlg();

	enum { IDD = IDD_WAITING_AUTO_IMPORT };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	void OnCancel();
	BOOL OnInitDialog();
	void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);

private:

	void DeleteEmptyDirectories();
	long ImportAndDeleteImagesFromPath(CString sPath);
	long ImportaImmagine(CString strFile);
	long MoveImagesFromPathToPath(CString sPath);

	//

	CAnimateCtrl m_ctrlAnim;
	CButtonLocalize m_ctrlBtnOK;
	CStaticLocalize m_ctrlStaticProgress1;
	CStaticLocalize m_ctrlStaticProgress2;
	CStatic m_ctrlStaticProgress3;

	CAlbumForm* m_pAlbumForm;

	//

	BOOL m_bExit;
	BOOL m_bIsContinuousCapture;
	long m_lImmaginiAcquisite;

};

#endif /* _WAITINGAUTOIMPORTDLG_H_ */