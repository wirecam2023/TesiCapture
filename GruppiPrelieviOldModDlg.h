#ifndef _GRUPPIPRELIEVIOLDMODDLG_H_
	#define _GRUPPIPRELIEVIOLDMODDLG_H_

class CGruppiPrelieviOldModDlg : public CDialog
{
	DECLARE_DYNAMIC(CGruppiPrelieviOldModDlg)

public:

	CGruppiPrelieviOldModDlg(CWnd* pParent);
	virtual ~CGruppiPrelieviOldModDlg();

	enum { IDD = IDD_GRUPPIPRELIEVI_MOD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel() { }
	virtual BOOL OnInitDialog();
	virtual void OnOK() { }

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();
	afx_msg void OnBnClickedBtnNewPrel();
	afx_msg void OnBnClickedBtnEdtPrel();
	afx_msg void OnBnClickedBtnDelPrel();
	afx_msg void OnBnClickedBtnEsci();

	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void EditDialog(BOOL bEdit);
	void RiempiLista1();
	void RiempiLista2(long lID);

	CButtonLocalize m_ctrlBtnNew;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnSave;
	CButtonLocalize m_ctrlBtnUndo;
	CButtonLocalize m_ctrlBtnNewPrel;
	CButtonLocalize m_ctrlBtnEdtPrel;
	CButtonLocalize m_ctrlBtnDelPrel;
	CButtonLocalize m_ctrlBtnEsci;

	CEdit m_ctrlEdit;

	CListCtrlLocalize m_ctrlList1;
	CListCtrlLocalize m_ctrlList2;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;

};

#endif /* _GRUPPIPRELIEVIMODDLG_H_ */