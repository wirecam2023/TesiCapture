#ifndef _WAITINGDICOMDLG_H_
	#define _WAITINGDICOMDLG_H_

class CWaitingDicomDlg : public CDialog
{
	DECLARE_DYNAMIC(CWaitingDicomDlg)
	
public:

	CWaitingDicomDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL p_bIsContinuousCapture = FALSE);
	virtual ~CWaitingDicomDlg();

	enum { IDD = IDD_WAITING_DICOM };

	void CreateModelessDialog(CWnd* pParent);

	BOOL m_bIsContinuousCaptureImporting;

protected:
	CRITICAL_SECTION m_cs;

	virtual void DoDataExchange(CDataExchange* pDX);
	void OnCancel();
	BOOL OnInitDialog();
	void OnTimer(UINT nIDEvent);
	void OnOK();
	
	int CountImageFilesInFolder();	
	void AddAndRefreshNumberInDialog(int p_iUnit);		

	void AcquisizioneCapturaContinua();
	static UINT AcqFromTeleImportThreadCapturaContinua(LPVOID pParam);
	static void AcqFromTeleImportThreadMoveFile(LPVOID pParam, CString p_strFile, long PazientiSetContatore, long EsamiSetContatore, CString sHash);
		
	BOOL IsHashAlreadyImported(CString sHash);

	void KillAndExit();
	
	void LogMessage(CString sMessage);
	CString GetLogString();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnEsci();

	//Gabriel BUG 7768 - Continuous capture problem
	long ImportAndDeleteImagesFromPath(CString sPath);

	long ImportaImmagine(CString strFile);

	void DeleteEmptyDirectories();

private:

	CAnimateCtrl m_ctrlAnim;
	CButtonLocalize m_ctrlBtnTerminaAcquisizione;
	CStaticLocalize m_ctrlStaticProgressLabel;
	CStatic m_ctrlStaticNumeroImmagini;

	long m_lAlbumCount;
	int m_iQtyFilesCapturaContinua;
	BOOL m_bIsContinuousCapture;	
	
	CList<CString> m_listHashesAlreadyImported;
	CString strLogInThread;

	BOOL m_bExit;

	CEsamiView* m_pEsamiView;
};

#endif /* _WAITINGDICOMDLG_H_ */