#pragma once

#include "TreeCtrlExpanded.h"

class CSortableTreeCtrl : public CTreeCtrlExpanded
{
public:
	CSortableTreeCtrl(void);
	~CSortableTreeCtrl(void);

	BOOL MoveSelectedUp();
	BOOL MoveSelectedDown();
};
