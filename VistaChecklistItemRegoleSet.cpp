#include "stdafx.h"
#include "Endox.h"
#include "VistaChecklistItemRegoleSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaChecklistItemRegoleSet, CBaseSet)

CVistaChecklistItemRegoleSet::CVistaChecklistItemRegoleSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CVistaChecklistItemRegoleSet::GetDefaultSQL()
{
	return "VISTACHECKLISTITEMREGOLE";
}

void CVistaChecklistItemRegoleSet::SetEmpty()
{
	m_lIDChecklist = 0;
	m_lIDChecklistItem = 0;
	m_lIDChecklistItemBind = 0;
	m_lTipoRegola = 0;
}

void CVistaChecklistItemRegoleSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDChecklist", m_lIDChecklist);
	RFX_Long(pFX, "IDChecklistItem", m_lIDChecklistItem);
	RFX_Long(pFX, "IDChecklistItemBind", m_lIDChecklistItemBind);
	RFX_Long(pFX, "TipoRegola", m_lTipoRegola);
}
