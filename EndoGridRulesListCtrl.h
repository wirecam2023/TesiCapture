#pragma once

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

class CEndoGridRulesListCtrl : public CAMEditComboListCtrl
{
public:
	CEndoGridRulesListCtrl(int iColumnNotResizable = -1);
	~CEndoGridRulesListCtrl(void);

protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	int m_iColumnNotResizable;
};
