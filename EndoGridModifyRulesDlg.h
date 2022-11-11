#pragma once

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

#include "EndoGridRulesListCtrl.h"
#include "EndoGridParameterRulesSet.h"

class CEndoGridModifyRulesDlg : public CDialog
{
	DECLARE_DYNAMIC(CEndoGridModifyRulesDlg)

public:
	CEndoGridModifyRulesDlg(CWnd* pParentWnd, int iGridIndex);
	~CEndoGridModifyRulesDlg(void);

	enum { IDD = IDD_MODIFY_FIELD_RULES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	LRESULT OnListChanged1(WPARAM wParam, LPARAM lParam);
	LRESULT OnListChanged2(WPARAM wParam, LPARAM lParam);
	LRESULT OnListChanged3(WPARAM wParam, LPARAM lParam);
	LRESULT OnListChanged4(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonPrintList();
	afx_msg void OnButtonConfirm();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonUp();
	virtual void OnOK() {}
	DECLARE_MESSAGE_MAP()

	void SetListSubItems(CAMEditComboListCtrl* pList);

	void Load(CAMEditComboListCtrl* pList, CEndoGridParameterRulesSet::RuleType type);
	void Save(CAMEditComboListCtrl* pList, CEndoGridParameterRulesSet::RuleType type);

	void InitializeListCtrl(CAMEditComboListCtrl* pList);

	void AddNew(CAMEditComboListCtrl* pList);
	void Remove(CAMEditComboListCtrl* pList);

	void MoveDown(CAMEditComboListCtrl* pList);
	void MoveUp(CAMEditComboListCtrl* pList);

	void ChangeTab();

	CEndoGridRulesListCtrl m_ctrlList1, m_ctrlList2, m_ctrlList3, m_ctrlList4;
	CButtonLocalize m_ctrlButton1,
		m_ctrlButton2,
		m_ctrlButton3,
		m_ctrlButton4,
		m_ctrlButton5,
		m_ctrlButton6,
		m_ctrlButton7;
	CTabCtrlLocalize m_ctrlTab;

	static UINT m_iListChange1;
	static UINT m_iListChange2;
	static UINT m_iListChange3;
	static UINT m_iListChange4;

private:
	long m_lIDEtichetta;
	CList<long> m_listIDParam;
};
