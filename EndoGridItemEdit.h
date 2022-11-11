#pragma once

#include "BaseSet.h"
#include "EndoGridInplaceEdit.h"
#include "EndoGridItem.h"
//#include "ComboSet.h"

class CEndoGridItemEdit : public CXTPPropertyGridItem
{
	DECLARE_DYNAMIC(CEndoGridItemEdit)

public:
	CEndoGridItemEdit(UINT nID, LPCTSTR strValue = NULL, CString* pBindString = NULL, CAMBaseSet* pSet = NULL, long lComboTable = -1/*, BOOL bCheckReadOnly = TRUE*/);
	CEndoGridItemEdit(CString strCaption, LPCTSTR strValue = NULL, CString* pBindString = NULL, CAMBaseSet* pSet = NULL, long lComboTable = -1/*, BOOL bCheckReadOnly = TRUE*/);
	CEndoGridItemEdit(long lParameterID, CString strCaption, BOOL bAllowMultiSelect, BOOL bFixedCombo);
	~CEndoGridItemEdit(void);

	virtual void OnAddChildItem();
	int GetLimitText();

	virtual CXTPPropertyGridInplaceEdit& GetInplaceEdit() { return m_wndEdit; }

	static BOOL m_bCheckReadOnly;

protected:
	void NotifyDirty();
	void SetLimitText(CString* pBindString = NULL, CAMBaseSet* pSet = NULL);
	virtual void OnValueChanged(CString strValue);
	virtual void OnInplaceButtonDown(CXTPPropertyGridInplaceButton* pButton);
	virtual BOOL OnChar(UINT nChar);
	virtual void OnDrawItemConstraint(CDC* pDC, CXTPPropertyGridItemConstraint* pConstraint, CRect rc, BOOL bSelected);
	void InitItemEdit();
	void PrepareAsFixedCombo();

	int  m_nMax;
	long m_lComboTable;
	CAMBaseSet* m_pSet;

	CEndoGridInplaceEdit m_wndEdit;
	BOOL m_bAllowMultiSelect;
};
