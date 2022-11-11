#ifndef _EXPORTDLG_H_
	#define _EXPORTDLG_H_

class CPath;
class CMosaicDlg;

class CExportDlg : public CDialog
{

public:

	CExportDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CExportDlg(void);
	
	enum { IDD = IDD_EXPORT };

	CListBox	m_ctrListSchede;

	CBitmapButtonEx m_btnPrint;
	CBitmapButtonEx m_btnPrintSel;
	CBitmapButtonEx m_btnExp;
	CBitmapButtonEx m_btnExpCD;
	CBitmapButtonEx m_btnExpDVD;
	CBitmapButtonEx m_btnExpPPT;
	CBitmapButtonEx m_btnCanc;
	CBitmapButtonEx m_btnEsc;
	
	CEsamiView*		m_pEsamiView;
	CFileBmp*		m_pBmp;
	CMosaicDlg*		m_pMosaicDlg;
	BOOL			m_bIsActive;
	
	CList <CPath*> m_ListPathDiapo;  

	void	PostCreate (CWnd* pParent, CEsamiView* pEsamiView);

	void 	RemoveAll();
	void 	CaricaListaWith(CObList* pList);
	void	CaricaListaWith(CObList* pList, CString* pStrFilter);
	void	ShowDialog(BOOL bShow);
	BOOL 	ExportImmagini(CString strPath);
	void	StampaImmagini();

	BOOL	FindImage (long nEsame, int nDiapo, int nTipo, long lID);
	
	void	AddImage(structEsame* pRiga, long lID, int type, BOOL bConfirmed, CString strDvdLabel, HBITMAP hBitmap, BOOL bCI);
	void	RemoveImage(long lID);
	
protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog ();
	
	afx_msg void OnImmExport();
	afx_msg void OnImmPrint();
	afx_msg void OnImmPrintSetup();
	afx_msg void OnSelChangeList();
	afx_msg void OnChiudi();
	afx_msg void OnResetList();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnImmExportCD();
	afx_msg void OnImmExportDVD();
	afx_msg void OnImmExportPPT();
	afx_msg void OnBnClickedBtnCanc();

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlBtnReset;
	CStaticLocalize m_ctrlStaticLabel1;
	CStaticLocalize m_ctrlStaticLabel2;

private:

	void AggiornaConteggio();
	void ResetList(BOOL bChiediConferma);

};

#endif /* _EXPORTDLG_H_ */