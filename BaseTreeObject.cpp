#include "stdafx.h"
#include "Endox.h"
#include "BaseTreeObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBaseTreeObject::CBaseTreeObject()
	: CObject()
{              
	figli = 0;
	livello = 0;
	larghezza = 0;
}
