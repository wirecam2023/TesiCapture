#pragma once

class CEndoGridItemEnum : public CXTPPropertyGridItem
{
	DECLARE_DYNAMIC(CEndoGridItemEnum)

public:
	CEndoGridItemEnum(CString strCaption);
	virtual ~CEndoGridItemEnum(void);

	void SetEnumValue(long lValue);
	long GetEnumValue();

	void AddEnumValue(long lID, CString strValue);

protected:
	virtual void OnValueChanged(CString strValue);

	struct tagVALUE
	{
		long lID;
		TCHAR szValue[1024];
	};
	CList<tagVALUE> m_list;
};