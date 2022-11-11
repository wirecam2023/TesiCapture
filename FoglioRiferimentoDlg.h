//Gabriel BUG 6225 - Lista DO
#pragma once

#ifndef _FOGLIORIFERIMENTODLG_H_
#define _FOGLIORIFERIMENTODLG_H_

class CFoglioRiferimentoDlg : public CDialog
{
	DECLARE_DYNAMIC(CFoglioRiferimentoDlg)

public:

	CFoglioRiferimentoDlg(CWnd* pParent);
	virtual ~CFoglioRiferimentoDlg();

	enum { IDD = IDD_VARI_FOGLIORIFERIMENTO };

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
	afx_msg void OnBnClickedBtnPath();

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();
	void CaricaDati();
	void EditDialog(BOOL bEdit);
	void UnselectAll();
	void RiempiComboCodicePrestazione();

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdit;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonPath;

	CListCtrl m_ctrlList;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;

	CComboBox m_ctrlComboSigla;

	long m_lIDSelected;
};
#endif /* _FOGLIORIFERIMENTODLG_H_ */