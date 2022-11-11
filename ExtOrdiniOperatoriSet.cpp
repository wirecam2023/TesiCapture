#include "stdafx.h"
#include "Endox.h"
#include "ExtOrdiniOperatoriSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtOrdiniOperatoriSet, CBaseSet)

CExtOrdiniOperatoriSet::CExtOrdiniOperatoriSet()
: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");
	SetSortRecord("IDRICHIESTA");

	m_nFields = 3;
}

CExtOrdiniOperatoriSet::~CExtOrdiniOperatoriSet()
{
}

CString CExtOrdiniOperatoriSet::GetDefaultSQL()
{
	return "EXT_ORDINI_OPERATORI";
}

void CExtOrdiniOperatoriSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDRichiesta", m_lIDRichiesta);
		RFX_Text(pFX, "codice", m_sCodice, 50);
	}
}

CString CExtOrdiniOperatoriSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}