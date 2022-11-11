#include "stdafx.h"
#include "Endox.h"
#include "ComboConclusioniColonSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboConclusioniColonSet, CComboTransSet)

CComboConclusioniColonSet::CComboConclusioniColonSet()
	: CComboTransSet()
{
}

CString CComboConclusioniColonSet::GetDefaultSQL()
{
	return "CONCLUSIONICOLON";
}

CBaseSet* CComboConclusioniColonSet::CreateNew()
{
	return (CBaseSet*)new CComboConclusioniColonSet;
}
