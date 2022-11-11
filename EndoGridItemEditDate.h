#pragma once

#include "EndoGridItemEdit.h"

class CEndoGridItemEditDate : public CEndoGridItemEdit
{
	DECLARE_DYNAMIC(CEndoGridItemEditDate)

public:
	CEndoGridItemEditDate(CString strCaption);
	~CEndoGridItemEditDate(void);

	virtual CXTPPropertyGridInplaceEdit& GetInplaceEdit() { return m_wndEdit; }

protected:
	virtual void OnInplaceButtonDown(CXTPPropertyGridInplaceButton* pButton);

	CXTPPropertyGridInplaceEdit m_wndEdit;
};
