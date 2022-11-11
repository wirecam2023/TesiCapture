#include "stdafx.h"
#include "Endox.h"
#include "ComboComplicanzeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboComplicanzeSet, CComboTransSet)

CComboComplicanzeSet::CComboComplicanzeSet(BOOL bTardive)
	: CComboTransSet()
{
	m_bTardive = bTardive;
}

CString CComboComplicanzeSet::GetDefaultSQL()
{
	if (m_bTardive)
		return "COMPLICANZETARDIVE";
	else
		return "COMPLICANZEIMMEDIATE";
}

CBaseSet* CComboComplicanzeSet::CreateNew()
{
	return (CBaseSet*)new CComboComplicanzeSet(m_bTardive);
}

