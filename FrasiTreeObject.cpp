#include "stdafx.h"
#include "Endox.h"
#include "FrasiTreeObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFrasiTreeObject::CFrasiTreeObject()
	: CBaseTreeObject()
{              
	codice		= 0; 
	padre		= 0;
	descrizione	= "";
	titolo		= "";
	flag		= 0;
}