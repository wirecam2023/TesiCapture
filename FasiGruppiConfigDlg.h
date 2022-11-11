#pragma once

class CFasiGruppiConfigDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CFasiGruppiConfigDlg)

public:
	CFasiGruppiConfigDlg(CWnd* pParent, long lIdFase);   // standard constructor
	virtual ~CFasiGruppiConfigDlg();

	// Dialog Data
	enum { IDD = IDD_FASI_GRUPPI_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support	
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()


	CStaticLocalize m_ctrlStatic1, m_ctrlStatic2;
	CListCtrl m_ctrlListOn;
	CListCtrl m_ctrlListOff;
	CButtonLocalize m_ctrlBtnOn, m_ctrlBtnOff, m_ctrlBtnSave, m_ctrlBtnAbort;

	void  RiempiListaOff();
	void  RiempiListaOn();

private:
	long m_lIdFase;
	CList<long> m_activeGroupList;

public:
	afx_msg void OnBnClickedBtnOn();
	afx_msg void OnBnClickedBtnOff();
	afx_msg void OnLvnItemchangedListOff(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListOn(NMHDR *pNMHDR, LRESULT *pResult);
};
