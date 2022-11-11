#include "stdafx.h"
#include "Endox.h"
#include "ComboTolleranzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboTolleranzaSet, CComboTransSet)

CComboTolleranzaSet::CComboTolleranzaSet()
	: CComboTransSet()
{
}

CString CComboTolleranzaSet::GetDefaultSQL()
{
	return "TOLLERANZA";
}

CBaseSet* CComboTolleranzaSet::CreateNew()
{
	return (CBaseSet*)new CComboTolleranzaSet;
}


