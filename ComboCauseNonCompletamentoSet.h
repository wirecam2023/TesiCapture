#ifndef _COMBOCAUSENONCOMPLETAMENTOSET_H_
	#define _COMBOCAUSENONCOMPLETAMENTOSET_H_

#include "ComboTransSet.h"

class CComboCauseNonCompletamentoSet : public CComboTransSet
{

	DECLARE_DYNAMIC(CComboCauseNonCompletamentoSet)

public:

	CComboCauseNonCompletamentoSet();

private:

	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();

};

#endif /* _COMBOCAUSENONCOMPLETAMENTOSET_H_ */