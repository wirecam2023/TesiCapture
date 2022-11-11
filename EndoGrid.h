#pragma once

#include "NumberList.h"
#include "ObbligatoryFieldErrorList.h"
#include "EndoGridItems.h"

#include "EndoGridCLItems.h"
#include "EndoGridParameterRulesSet.h"

class CEndoGrid : public CXTPPropertyGrid
{
	DECLARE_DYNAMIC(CEndoGrid)

public:
	CEndoGrid(CString sGridID);
	~CEndoGrid();

	BOOL Create(CWnd* pParentWnd, UINT nID);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL		 PreTranslateMessage(MSG* pMsg);

	virtual void SetReadOnly(BOOL bEnable = TRUE);
	BOOL GetReadOnly() { return m_bReadOnly; }

	virtual void Init(){};

	void SetFocusFirstItem();
	void ShowAllItem(BOOL bShow) { m_bShowAllItem = bShow; }

	virtual void SetEvidenceObbligaroryField(BOOL bEnable);
	virtual BOOL GetEvidenceObbligaroryField();

	virtual BOOL IsObbligaroryField(CXTPPropertyGridItem* pItem);
	virtual COLORREF GetRequiredFieldColor() { return RGB(255, 255, 255); };

	afx_msg void ExpandAll();

protected:	

	afx_msg virtual LRESULT OnAppStateChanged(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnPatientChanged(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnExamChanged(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnExamEdit(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnExamUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnExamUndo(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnItemDirty(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnCheckObbligatoryField(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnFocusObbligatoryField(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnGridNotify(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnAnalyzeGridRules(WPARAM wParam, LPARAM lParam);
	//afx_msg virtual LRESULT OnLoadGridRules(WPARAM wParam, LPARAM lParam);
	//virtual void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnUpdateShowHelp(CCmdUI *pCmdUI);
	//afx_msg void OnShowHelp();
	afx_msg void OnCollapse();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

	BOOL                   m_bEvidenceObbligaroryField;
	CNumberList            m_listObbligatoryField;

	BOOL m_bReadOnly, m_bShowAllItem;

	virtual void LoadObbligatoryField();
	virtual BOOL CheckObbligatoryField(CObbligatoryFieldErrorList* pList, CXTPPropertyGridItem* pItemParent = NULL);
	virtual BOOL FocusObbligatoryField(long lFieldID, CXTPPropertyGridItem* pItemParent = NULL);

	void LoadDividerPos();
	void SaveDividerPos();

	virtual void ItemValueChanged(CXTPPropertyGridItem* pItem);	

	struct tagAPPLYRULE
	{
		long lID;
		CEndoGridParameterRulesSet::RuleType RuleType;
		BOOL bRuleValid;
		long lFieldID;
		COLORREF clColor;
		TCHAR szNewValue[256];
	};

	void AnalyzeRules(const CEndoGridCLItems* pItems, CList<tagAPPLYRULE>* pListApplyRule);
	void ApplyRules(const CEndoGridCLItems* pItems, CList<tagAPPLYRULE>* pListRule);
	void LoadRules();

private:
	struct tagFIELDRULE
	{
		long lID;
		CEndoGridParameterRulesSet::RuleType RuleType;
		long lFieldID;
		BOOL bNumeric;
		CEndoGridParameterRulesSet::OperatorType Operator;
		TCHAR szValue[256];
		TCHAR szNewValue[256];
		long lFieldToHide;
		COLORREF clColor;
	};

	struct tagRULEPROCESSED
	{
		long lFieldID;
		CEndoGridParameterRulesSet::RuleType RuleType;
	};

	CList<tagFIELDRULE> m_listRules;
	CString m_sGridID;

};

