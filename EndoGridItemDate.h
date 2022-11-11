#pragma once

#include "EndoGridMaskEdit.h"

class CEndoGridItemDate : public CEndoGridMaskEdit
{
public:
	CEndoGridItemDate(UINT nID, CString* pBindDate = NULL, BOOL bToday = TRUE);
	CEndoGridItemDate(CString strCaption, CString* pBindDate = NULL, BOOL bToday = TRUE);

	BOOL IsValidDate();

	void NotifyDirty();

	void SetDate(CString strDate);
	CString GetDate();

	virtual CString GetValueEx();

protected:
	virtual void OnInplaceButtonDown(CXTPPropertyGridInplaceButton* pButton);
	virtual void OnDeselect();

private:
	void Init(CString* pBindDate, BOOL bToday);

	void SetValue(CString strValue) { CEndoGridMaskEdit::SetValue(strValue); };
};