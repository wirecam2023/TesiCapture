#ifndef _COMBOALTREANOMALIESET_H_
#define _COMBOALTREANOMALIESET_H_

#include "ComboTransSet.h"

class CComboAltreAnomalieSet : public CComboTransSet
{

	DECLARE_DYNAMIC(CComboAltreAnomalieSet)

public:

	CComboAltreAnomalieSet();

private:

	virtual CString GetDefaultSQL();
	virtual CBaseSet* CreateNew();

};

#endif /* _COMBOALTREANOMALIESET_H_ */