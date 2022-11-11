#include "stdafx.h"
#include "Endox.h"
#include "ExtOrdiniDiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtOrdiniDiagnosiICD9Set, CBaseSet)

CExtOrdiniDiagnosiICD9Set::CExtOrdiniDiagnosiICD9Set()
: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");
	SetSortRecord("IDRICHIESTA");

	m_nFields = 3;
}

CExtOrdiniDiagnosiICD9Set::~CExtOrdiniDiagnosiICD9Set()
{
}

CString CExtOrdiniDiagnosiICD9Set::GetDefaultSQL()
{
	return "EXT_ORDINI_DIAGNOSIICD9";
}

void CExtOrdiniDiagnosiICD9Set::DoFieldExchange(CFieldExchange* pFX)
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

CString CExtOrdiniDiagnosiICD9Set::SetBaseFilter(const CString &strFilter)
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