#pragma once

#include "ColorItemListBox.h"

class CEndoGridComboDlg : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CEndoGridComboDlg)

public:
	CEndoGridComboDlg(long lComboTable, CString strText, BOOL bAllowMultiSelect, CWnd* pParentWnd = NULL);   // standard constructor
	virtual ~CEndoGridComboDlg();

	enum { IDD = IDD_COMBO_OWNERDRAW_DLG };

	CString m_strEdit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg virtual void OnAdd();
	afx_msg virtual void OnRemove();
	afx_msg virtual void OnDetail(){};
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnLbnDblclkList();
	afx_msg void OnEnChangeEdit();
	afx_msg void OnReset();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	virtual void FillList();
	void EnlargeWndFromText();
	void SelectFromList();

	virtual CListBox* GetListBox() { return &m_ctrlListColor; }

	CButtonLocalize m_ctrlButtonReset,
		m_ctrlButtonAdd,
		m_ctrlButtonRemove,
		m_ctrlButtonDetail,
		m_ctrlButtonOK,
		m_ctrlButtonCancel;
	//CListBox m_ctrlList;
	long m_lComboTable;
	BOOL m_bAllowMultiSelect;

	CColorItemListBox m_ctrlListColor;
	CList<long> m_listRule;
};
