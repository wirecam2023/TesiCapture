#include "stdafx.h"
#include "Endox.h"
#include "ErroriEsterniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CErroriEsterniSet, CBaseSet)

CErroriEsterniSet::CErroriEsterniSet()
	: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("IDServizio");

	m_nFields = 3;
}

CString CErroriEsterniSet::GetDefaultSQL()
{
	return "ErroriEsterni";
}

void CErroriEsterniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDServizio",	m_lIDServizio);
	RFX_Bool(pFX, "Errore", m_bErrore);
	RFX_Text(pFX, "Messaggio", m_sMessaggio, 3999);
}

void CErroriEsterniSet::SetEmpty()
{
	m_lIDServizio = 0;
	m_bErrore = FALSE;
	m_sMessaggio = "";
}