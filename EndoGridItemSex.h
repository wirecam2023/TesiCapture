#pragma once

#include "endogriditemedit.h"

class CEndoGridItemSex : public CEndoGridItemEdit
{
public:
	CEndoGridItemSex(CString strCaption);
	~CEndoGridItemSex(void);

	long GetSex();
	void SetSex(long lSex);
};