#pragma once

#include "SortableTreeCtrl.h"
//#include "SortableListBox.h"

class CModifyGridCLConfigDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CModifyGridCLConfigDlg)

public:
	CModifyGridCLConfigDlg(CWnd* pParent = NULL, int iIndex = 0);   // standard constructor
	virtual ~CModifyGridCLConfigDlg();

	// Dialog Data
	enum { IDD = IDD_MODIFY_GRIDCL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnNMDblclkTreeFields(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	afx_msg void OnAddField();
	afx_msg void OnAddCategory();
	afx_msg void OnRenameField();
	afx_msg void OnRemoveField();
	virtual BOOL OnInitDialog();
	virtual void OnCancel() {};
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()

	CSortableTreeCtrl m_ctrlTree;

	CButtonLocalize m_ctrlButton1,
		m_ctrlButton2,
		m_ctrlButton3,
		m_ctrlOK;

	BOOL m_bAddNewVersion;

private:
	void RefreshGridCLFields(HTREEITEM hItemParent = NULL);

	void UpdateTreeOrder(CSortableTreeCtrl* pTreeCtrl, HTREEITEM hItemParent = NULL);

	long m_lIDEtichetta;

	//void SelectExamTypeList(long lID);
	//void SaveExamTypeList(long lID);
	//void ResetSelectExamTypeList();
	//void FillExamTypeTree();
};
