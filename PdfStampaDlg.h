#ifndef _PDFSTAMPADLG_H_
	#define _PDFSTAMPADLG_H_

class CPdfStampaDlg : public CDialog
{
	DECLARE_DYNAMIC(CPdfStampaDlg)

public:

	CPdfStampaDlg(CWnd* pParent, CString sRptFile, CString sPdfFile, BOOL bCrypted, long lPrinterToUse, long lCopies, BOOL bFitToPage);
	virtual ~CPdfStampaDlg();

	enum { IDD = IDD_PDF_STAMPA };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);

private:

	CAnimateCtrl m_ctrlAnim;
	CStaticLocalize m_ctrlStatic;

	CString m_sRptFile;
	CString m_sPdfFile;
	BOOL m_bCrypted;
	long m_lPrinterToUse;
	long m_lCopies;
	BOOL m_bFitToPage;

	BYTE* m_pBufferPdf;

	UINT m_uiTemp;

};

#endif /* _PDFSTAMPADLG_H_ */