#pragma once

#include "EndoGridItemEdit.h"

class CEndoGridItemNotes : public CEndoGridItemEdit
{
	DECLARE_DYNAMIC(CEndoGridItemNotes)

public:
	CEndoGridItemNotes(UINT nID, LPCTSTR strValue = NULL, CString* pBindString = NULL, CAMBaseSet* pSet = NULL, long lComboTable = -1/*, BOOL bCheckReadOnly = TRUE*/);
	CEndoGridItemNotes(CString strCaption, LPCTSTR strValue = NULL, CString* pBindString = NULL, CAMBaseSet* pSet = NULL, long lComboTable = -1/*, BOOL bCheckReadOnly = TRUE*/);
	~CEndoGridItemNotes(void);

	void SetValue(CString strValue);
	CString GetValue();

	virtual CString GetToolTipText();

protected:
	virtual void OnInplaceButtonDown(CXTPPropertyGridInplaceButton* pButton);
};
