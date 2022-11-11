#ifndef _FARMACIGRUPPIRICDLG_H_
	#define _FARMACIGRUPPIRICDLG_H_

class CFarmaciGruppiRicDlg : public CDialog
{
	DECLARE_DYNAMIC(CFarmaciGruppiRicDlg)

public:

	CFarmaciGruppiRicDlg(CWnd* pParent);
	virtual ~CFarmaciGruppiRicDlg();

	enum { IDD = IDD_FARMACI_GRUPPIRIC };

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

#endif /* _FARMACIGRUPPIRICDLG_H_ */ 