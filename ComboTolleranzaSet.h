#ifndef _COMBOTOLLERANZASET_H_
	#define _COMBOTOLLERANZASET_H_

#include "ComboTransSet.h"

class CComboTolleranzaSet : public CComboTransSet
{

	DECLARE_DYNAMIC(CComboTolleranzaSet)

public:

	CComboTolleranzaSet();

private:

	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();

};

#endif /* _COMBOTOLLERANZASET_H_ */