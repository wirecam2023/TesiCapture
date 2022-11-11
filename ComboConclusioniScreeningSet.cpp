#include "stdafx.h"
#include "Endox.h"
#include "ComboConclusioniScreeningSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboConclusioniScreeningSet, CComboTransSet)

CComboConclusioniScreeningSet::CComboConclusioniScreeningSet()
	: CComboTransSet()
{
}

CString CComboConclusioniScreeningSet::GetDefaultSQL()
{
	return "CONCLUSIONISCREENING";
}

CBaseSet* CComboConclusioniScreeningSet::CreateNew()
{
	return (CBaseSet*)new CComboConclusioniScreeningSet;
}
