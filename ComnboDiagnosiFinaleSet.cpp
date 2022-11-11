#include "stdafx.h"
#include "Endox.h"
#include "ComboDiagnosiFinaleSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboDiagnosiFinaleSet, CComboTransSet)

CComboDiagnosiFinaleSet::CComboDiagnosiFinaleSet()
	: CComboTransSet()
{
}

CString CComboDiagnosiFinaleSet::GetDefaultSQL()
{
	return "DIAGNOSIFINALE";
}

CBaseSet* CComboDiagnosiFinaleSet::CreateNew()
{
	return (CBaseSet*)new CComboDiagnosiFinaleSet;
}