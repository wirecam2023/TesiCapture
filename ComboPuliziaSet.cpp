#include "stdafx.h"
#include "Endox.h"
#include "ComboPuliziaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboPuliziaSet, CComboTransSet)

CComboPuliziaSet::CComboPuliziaSet()
	: CComboTransSet()
{
}

CString CComboPuliziaSet::GetDefaultSQL()
{
	return "PULIZIA";
}

CBaseSet* CComboPuliziaSet::CreateNew()
{
	return (CBaseSet*)new CComboPuliziaSet;
}
