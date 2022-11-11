#pragma once

class CGenomicaTipiAlterazioniDlg : public CDialog
{
	DECLARE_DYNAMIC(CGenomicaTipiAlterazioniDlg)

public:
	CGenomicaTipiAlterazioniDlg(CWnd* pParent);
	virtual ~CGenomicaTipiAlterazioniDlg();

	enum { IDD = IDD_GENOMICA_TIPIALTERAZIONI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();

	DECLARE_MESSAGE_MAP()

private:
	
	void RiempiLista();
	void CaricaDati();
	void EditDialog(BOOL bEdit);
	void UnselectAll();


	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdit;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;

	CListCtrl m_ctrlList;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;

	CButtonLocalize m_ctrlButtonObbligatorioHGVSc;
	CButtonLocalize m_ctrlButtonObbligatorioHGVSp;

	long m_lIDSelected;
};
