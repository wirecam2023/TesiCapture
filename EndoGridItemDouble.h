#pragma once

class CEndoGridItemDouble : public CXTPPropertyGridItemDouble
{
	DECLARE_DYNAMIC(CEndoGridItemDouble)

public:
	CEndoGridItemDouble(UINT nID, double dValue = 0, double* pBindNumber = NULL, LPCTSTR strFormat = _T("%0.1f"));
	CEndoGridItemDouble(CString strCaption, double dValue = 0, double* pBindNumber = NULL, LPCTSTR strFormat = _T("%0.1f"));
	~CEndoGridItemDouble(void);

protected:
	virtual void OnValueChanged(CString strValue);
};