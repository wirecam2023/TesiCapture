#ifndef _REPORTSDEFAULTMODDLG_H_
	#define _REPORTSDEFAULTMODDLG_H_

class CReportsDefaultModDlg : public CDialog
{
	DECLARE_DYNAMIC(CReportsDefaultModDlg)

public:

	CReportsDefaultModDlg(CWnd* pParent);
	virtual ~CReportsDefaultModDlg();

	enum { IDD = IDD_REPORTSDEFAULT_MOD_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDn();
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();
	afx_msg void OnBnClickedCheckStampaImmagini();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnLbnSelchangeListEsami();
	afx_msg void OnLbnSelchangeListSedi();
	afx_msg void OnLvnItemchangedListReports(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiListEsami();
	void RiempiListSedi();
	void RiempiListReports();
	void SetStato(int nStato);
	void SalvaEsame();

	CButtonLocalize m_ctrlBtnUp;
	CButtonLocalize m_ctrlBtnDn;
	CButtonLocalize m_ctrlBtnSearch;
	CButtonLocalize m_ctrlBtnNew;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnSave;
	CButtonLocalize m_ctrlBtnUndo;
	CButtonLocalize m_ctrlBtnOK;

	CEdit m_ctrlEditReport;
	CEdit m_ctrlEditCopie;
	CEdit m_ctrlEditCopieImm;

	CListBox m_ctrlListSedi;
	CListBox m_ctrlListEsami;
	CListCtrlLocalize m_ctrlListReports;

	CSpinButtonCtrl m_ctrlSpin;
	CSpinButtonCtrl m_ctrlSpinImm;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic06;

	CButtonLocalize m_ctrlStampaImmagini;

	int m_nStato;
	CString m_sSede;
	long m_lTipoEsame;

};

#endif /* _REPORTSDEFAULTMODDLG_H_ */