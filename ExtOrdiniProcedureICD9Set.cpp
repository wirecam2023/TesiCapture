#include "stdafx.h"
#include "Endox.h"
#include "ExtOrdiniProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtOrdiniProcedureICD9Set, CBaseSet)

CExtOrdiniProcedureICD9Set::CExtOrdiniProcedureICD9Set()
: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");
	SetSortRecord("IDRICHIESTA");

	m_nFields = 3;
}

CExtOrdiniProcedureICD9Set::~CExtOrdiniProcedureICD9Set()
{
}

CString CExtOrdiniProcedureICD9Set::GetDefaultSQL()
{
	return "EXT_ORDINI_PROCEDUREICD9";
}

void CExtOrdiniProcedureICD9Set::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDRichiesta", m_lIDRichiesta);
		RFX_Text(pFX, "codiceicd9", m_sCodiceICD9, 50);
	}
}

CString CExtOrdiniProcedureICD9Set::SetBaseFilter(const CString &strFilter)
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