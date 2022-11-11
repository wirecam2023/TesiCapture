#pragma once

class CModifyGridCLPrivilegiConfigDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CModifyGridCLPrivilegiConfigDlg)

public:
	CModifyGridCLPrivilegiConfigDlg(CWnd* pParent = NULL, int iIndex = 0);   // standard constructor
	virtual ~CModifyGridCLPrivilegiConfigDlg();

	// Dialog Data
	enum { IDD = IDD_GRIDCL_PRIV_CONFIG };

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
	int m_iGridIndex;


public:
	afx_msg void OnBnClickedBtnOn();
	afx_msg void OnBnClickedBtnOff();
	afx_msg void OnLvnItemchangedListOff(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListOn(NMHDR *pNMHDR, LRESULT *pResult);
};
