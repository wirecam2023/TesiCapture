#pragma once

#include "EndoGridCLParameterSet.h"

class CEndoGrid;

class CEndoGridModifyFieldRulesChildDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CEndoGridModifyFieldRulesChildDlg)

public:
	CEndoGridModifyFieldRulesChildDlg(long lItemSelectedID, long lIDEtichetta, BOOL bItemCategoriesCheck, CPoint point, CWnd* pParentWnd);
	~CEndoGridModifyFieldRulesChildDlg(void);

	enum { IDD = IDD_MODIFY_FIELD_RULES_CHILD };

	long GetItemSelectedID();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnItemClicked(NMHDR* pNMHDR, LRESULT* pResult);
	LRESULT OnItemChecked(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()

	void InsertUserFields(long lVersionID, HTREEITEM hItemParent);
	//void InsertStaticGrid(HTREEITEM hItemParent);
	//void InsertPatientGrid(HTREEITEM hItemParent);

	void FillGridItemChilds(CEndoGrid* pGridItem, HTREEITEM hItemParent);

	void FillTree();
	void SetItemAsRoot(HTREEITEM hItem);

	CTreeCtrl m_ctrlTree;

	BOOL m_bItemCategoriesCheck;
	CPoint m_ptStart;

	HTREEITEM m_hItemSelected;
	long m_lItemSelectedID;

	BOOL m_bCanExit;
	long m_lIDEtichetta;
};