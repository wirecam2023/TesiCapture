#pragma once

#include "ToolBarEx.h"

class CEditDynFormToolbar : public CToolBarEx
{

public:

	CEditDynFormToolbar(void);
	~CEditDynFormToolbar(void);

	void Create(UINT idFrame, CWnd* pParentWnd);

protected:

	virtual LRESULT OnToolbarPressButton(WPARAM wParam, LPARAM lParam);

};