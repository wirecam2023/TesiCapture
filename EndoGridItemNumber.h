#pragma once

class CEndoGridItemNumber : public CXTPPropertyGridItemNumber
{
	DECLARE_DYNAMIC(CEndoGridItemNumber)

public:
	CEndoGridItemNumber(CString strCaption, long nValue = 0, long* pBindNumber = NULL);
	CEndoGridItemNumber(UINT nID, long nValue = 0, long* pBindNumber = NULL);
	virtual ~CEndoGridItemNumber();

protected:
	virtual void OnValueChanged(CString strValue);
};
