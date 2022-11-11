#ifndef _FRASITREEOBJECT_H_
	#define _FRASITREEOBJECT_H_

#include "BaseTreeObject.h"

class CFrasiTreeObject : public CBaseTreeObject
{

public:

	CFrasiTreeObject();

	long		codice;
	long		padre;
	CString		descrizione;
	CString		titolo;
	int			flag;
};

#endif /* _FRASITREEOBJECT_H_ */