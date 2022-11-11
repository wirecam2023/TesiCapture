#pragma once

#include "EndoGridInplaceEdit.h"

class CEndoGridItemBool : public CXTPPropertyGridItemBool
{
	DECLARE_DYNAMIC(CEndoGridItemBool)

public:
	CEndoGridItemBool(CString strCaption, BOOL bValue = FALSE, BOOL* pBindBool = NULL);
	CEndoGridItemBool(UINT nID, BOOL bValue = FALSE, BOOL* pBindBool = NULL);
	~CEndoGridItemBool(void);

	void OnValueChanged(CString strValue);
	virtual CXTPPropertyGridInplaceEdit& GetInplaceEdit() { return m_wndEdit; };

protected:
	void NotifyDirty();

	CEndoGridInplaceEdit m_wndEdit;
};