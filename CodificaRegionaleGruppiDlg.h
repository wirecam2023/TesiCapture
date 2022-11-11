#ifndef _CODIFICAREGIONALEGRUPPIDLG_H_
	#define _CODIFICAREGIONALEGRUPPIDLG_H_

class CCodificaRegionaleGruppiDlg : public CDialog
{
	DECLARE_DYNAMIC(CCodificaRegionaleGruppiDlg)

public:

	CCodificaRegionaleGruppiDlg(CWnd* pParent);
	virtual ~CCodificaRegionaleGruppiDlg();

	enum { IDD = IDD_CODIFICAREGIONALE_GRUPPIRIC };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnNewSx();
	afx_msg void OnBnClickedBtnEdtSx();
	afx_msg void OnBnClickedBtnDelSx();
	afx_msg void OnBnClickedBtnNewDx();
	afx_msg void OnBnClickedBtnEdtDx();
	afx_msg void OnBnClickedBtnDelDx();
	afx_msg void OnBnClickedBtnEsci();

	afx_msg void OnLvnItemchangedListSx(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListDx(NMHDR *pNMHDR, LRESULT *pResult);

private:

	CButtonLocalize m_ctrlBtnNewSx;
	CButtonLocalize m_ctrlBtnEdtSx;
	CButtonLocalize m_ctrlBtnDelSx;
	CButtonLocalize m_ctrlBtnNewDx;
	CButtonLocalize m_ctrlBtnEdtDx;
	CButtonLocalize m_ctrlBtnDelDx;

	CListCtrlLocalize m_ctrlListSx;
	CListCtrlLocalize m_ctrlListDx;

	//

	void RiempiListaSx();
	void RiempiListaDx(long lIDGruppo);

};

#endif /* _CODIFICAREGIONALEGRUPPIDLG_H_ */ 