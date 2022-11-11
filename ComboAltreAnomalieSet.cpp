#include "stdafx.h"
#include "Endox.h"
#include "ComboAltreAnomalieSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboAltreAnomalieSet, CComboTransSet)

CComboAltreAnomalieSet::CComboAltreAnomalieSet()
: CComboTransSet()
{
}

CString CComboAltreAnomalieSet::GetDefaultSQL()
{
	return "ALTREANOMALIE";
}

CBaseSet* CComboAltreAnomalieSet::CreateNew()
{
	return (CBaseSet*)new CComboAltreAnomalieSet;
}
