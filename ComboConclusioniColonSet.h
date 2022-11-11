#ifndef _COMBOCONCLUSIONICOLONSET_H_
	#define _COMBOCONCLUSIONICOLONSET_H_

#include "ComboTransSet.h"

class CComboConclusioniColonSet : public CComboTransSet
{

	DECLARE_DYNAMIC(CComboConclusioniColonSet)

public:

	CComboConclusioniColonSet();

private:

	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();

};

#endif /* _COMBOCONCLUSIONICOLONSET_H_ */