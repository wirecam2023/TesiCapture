#include "stdafx.h"
#include "Endox.h"
#include "ComboCauseNonCompletamentoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboCauseNonCompletamentoSet, CComboTransSet)

CComboCauseNonCompletamentoSet::CComboCauseNonCompletamentoSet()
	: CComboTransSet()
{
}

CString CComboCauseNonCompletamentoSet::GetDefaultSQL()
{
	return "CAUSENONCOMPLETO";
}

CBaseSet* CComboCauseNonCompletamentoSet::CreateNew()
{
	return (CBaseSet*)new CComboCauseNonCompletamentoSet;
}
