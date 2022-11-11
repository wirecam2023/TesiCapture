#ifndef _COMBOCOMPLICANZESET_H_
	#define _COMBOCOMPLICANZESET_H_

#include "ComboTransSet.h"

class CComboComplicanzeSet : public CComboTransSet
{

	DECLARE_DYNAMIC(CComboComplicanzeSet)

public:

	CComboComplicanzeSet(BOOL bTardive);

private:

	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();

	BOOL m_bTardive;

};

#endif /* _COMBOCOMPLICANZESET_H_ */