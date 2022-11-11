#include "stdafx.h"
#include "Endox.h"
#include "VistaUtentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaUtentiSet, CBaseSet)

CVistaUtentiSet::CVistaUtentiSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetSortRecord("ID");

	SetEmpty();

	m_nFields = 2;
}

CString CVistaUtentiSet::GetDefaultSQL()
{
	return "VISTA_UTENTI";
}

void CVistaUtentiSet::SetEmpty()
{
	m_lId = -1;
	m_sUsername = "";
}

void CVistaUtentiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "id", m_lId);
	RFX_Text(pFX, "Username", m_sUsername);
}