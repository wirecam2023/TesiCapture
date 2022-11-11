#ifndef _MULTIPAGETIFFNEWDLG_H_
	#define _MULTIPAGETIFFNEWDLG_H_

class CAlbumForm;

/// <summary>
/// Dialogo per la creazione di (e l'aggiunta di frames ai) TIFF multipagina
/// </summary>

class CMultiPageTiffNewEdtDlg : public CDialog
{

	DECLARE_DYNAMIC(CMultiPageTiffNewEdtDlg)

public:

	CMultiPageTiffNewEdtDlg(CWnd* pParent, CEsamiView* pEsamiView, CPazientiSet* pPazienteSet, CEsamiSet* pEsamiSet, long lIDImageTIFF, BOOL bPaziente);
	virtual ~CMultiPageTiffNewEdtDlg();

	enum { IDD = IDD_MULTIPAGETIFF_NEWEDT };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK() { }

	DECLARE_MESSAGE_MAP()

	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedBtnDisco();
	afx_msg void OnBnClickedBtnScanner();

private:

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnDisco;
	CButtonLocalize m_ctrlBtnScanner;

	CStaticLocalize m_ctrlStaticTitle1;
	CStaticLocalize m_ctrlStaticTitle2;

	CAlbumForm* m_pAlbumForm;
	CEsamiView* m_pEsamiView;
	CPazientiSet* m_pPazienteSet;
	CEsamiSet* m_pEsamiSet;
	long m_lIDImageTIFF;
	BOOL m_bPaziente;

};

#endif /* _MULTIPAGETIFFNEWDLG_H_ */