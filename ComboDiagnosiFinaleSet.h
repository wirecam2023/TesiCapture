#ifndef _COMBODIAGNOSIFINALESET_H_
	#define _COMBODIAGNOSIFINALESET_H_

#include "ComboTransSet.h"

class CComboDiagnosiFinaleSet : public CComboTransSet
{

	DECLARE_DYNAMIC(CComboDiagnosiFinaleSet)

public:

	CComboDiagnosiFinaleSet();

private:

	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();

};

#endif /* _COMBODIAGNOSIFINALESET_H_ */