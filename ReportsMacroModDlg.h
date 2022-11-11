#ifndef _REPORTSMACROMODDLG_H_
	#define _REPORTSMACROMODDLG_H_

class CReportsMacroModDlg : public CDialog
{

	DECLARE_DYNAMIC(CReportsMacroModDlg)

public:

	CReportsMacroModDlg(CWnd* pParent);
	virtual ~CReportsMacroModDlg();

	enum { IDD = IDD_REPORTSMACRO_MOD_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnNew1();
	afx_msg void OnBnClickedBtnEdt1();
	afx_msg void OnBnClickedBtnDel1();
	afx_msg void OnBnClickedBtnNew2();
	afx_msg void OnBnClickedBtnEdt2();
	afx_msg void OnBnClickedBtnDel2();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDn();
	afx_msg void OnBnClickedCheckStampaImmagini();
	afx_msg void OnBnClickedCheckEtichette();

	afx_msg void OnCbnSelchangeCombo();

	afx_msg void OnDeltaposSpinStampaImmagini(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinEtichetteIstopatologia(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiLista1();
	void RiempiLista2();

	CButtonLocalize m_ctrlBtnNew1;
	CButtonLocalize m_ctrlBtnEdt1;
	CButtonLocalize m_ctrlBtnDel1;
	CButtonLocalize m_ctrlBtnNew2;
	CButtonLocalize m_ctrlBtnEdt2;
	CButtonLocalize m_ctrlBtnDel2;
	CButtonLocalize m_ctrlBtnUp;
	CButtonLocalize m_ctrlBtnDn;
	CButtonLocalize m_ctrlCheckStampaImmagini;
	CButtonLocalize m_ctrlCheckEtichette;
	CButtonLocalize m_ctrlBtnOK;

	CComboBox m_ctrlCombo;

	CEdit m_ctrlEditStampaImmagini;
	CEdit m_ctrlEditEtichetteIstopatologia;

	CListCtrlLocalize m_ctrlList1;
	CListCtrlLocalize m_ctrlList2;

	CSpinButtonCtrl m_ctrlSpinStampaImmagini;
	CSpinButtonCtrl m_ctrlSpinEtichetteIstopatologia;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;

	long m_lIDMacro;

};

#endif /* _REPORTSMACROMODDLG_H_ */