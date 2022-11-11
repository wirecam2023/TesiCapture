#ifndef _EXTLISTCOMBO_H_
	#define _EXTLISTCOMBO_H_

#include "ExtList.h"

class CExtListCombo : public CExtList
{
	DECLARE_DYNCREATE (CExtListCombo)

public:

	CExtListCombo();
	virtual ~CExtListCombo();

	BOOL SetParamSet(long lComboDefine, BOOL bOrderByString);

protected:

	DECLARE_MESSAGE_MAP()

};

#endif /* _EXTLISTCOMBO_H_ */