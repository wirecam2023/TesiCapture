#ifndef _COMBOCONCLUSIONISCREENINGSET_H_
	#define _COMBOCONCLUSIONISCREENINGSET_H_

#include "ComboTransSet.h"

class CComboConclusioniScreeningSet : public CComboTransSet
{

	DECLARE_DYNAMIC(CComboConclusioniScreeningSet)

public:

	CComboConclusioniScreeningSet();

private:

	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();

};

#endif /* _COMBOCONCLUSIONISCREENINGSET_H_ */