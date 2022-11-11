#ifndef _COMBOPULIZIASET_H_
	#define _COMBOPULIZIASET_H_

#include "ComboTransSet.h"

class CComboPuliziaSet : public CComboTransSet
{

	DECLARE_DYNAMIC(CComboPuliziaSet)

public:

	CComboPuliziaSet();

private:

	virtual CString GetDefaultSQL();
	virtual CBaseSet* CreateNew();

};

#endif /* _COMBOPULIZIASET_H_ */