#pragma once

#include "EndoGrid.h"
#include "EndoGridCLItems.h"

class CEsamiView;

class CEndoGridChecklist : public CEndoGrid
{
	DECLARE_DYNAMIC(CEndoGridChecklist)

public:
	CEndoGridChecklist(CEsamiView *pEsamiView, long lIndex);
	~CEndoGridChecklist();

	virtual BOOL Create(CWnd* pParentWnd, UINT nID);
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void Init();

	virtual void SetReadOnly(BOOL bEnable = TRUE);

	virtual BOOL IsObbligaroryField(CXTPPropertyGridItem* pItem);
	virtual COLORREF GetRequiredFieldColor();
	void SetRequiredFieldColor(COLORREF color);

	static CString GetIdentifier(CString name, long id);

protected:
	afx_msg virtual LRESULT OnExamChanged(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnExamUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg virtual LRESULT OnExamUndo(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnGridNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	void InsertGeneralField(long lVersionID, long lParentID = 0, CXTPPropertyGridItem* pParentItem = NULL);
	virtual BOOL CheckObbligatoryField(CObbligatoryFieldErrorList* pList, CXTPPropertyGridItem* pItemParent = NULL);
	virtual BOOL FocusObbligatoryField(long lFieldID, CXTPPropertyGridItem* pItemParent = NULL);

	void LoadGeneralData();
	void SaveGeneralData();

	void InitializeItems();

	CEndoGridCLItems m_GeneralItemList;
	CNumberList m_listRequiredField;

	CEsamiView *m_pEsamiView;

private:
	long m_lIdEtichetta;
	COLORREF m_crCampoObbligatorio;

};
