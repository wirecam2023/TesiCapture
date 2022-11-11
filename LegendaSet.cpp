#include "stdafx.h"
#include "Endox.h"
#include "LegendaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CLegendaSet, CBaseSet)

CLegendaSet::CLegendaSet()
	: CBaseSet(NULL, "NOLOG") // non lascio traccia delle modifiche //
{
	SetBaseFilter("");
	SetSortRecord("VOCE");

	m_nFields = 3;
}

CString CLegendaSet::GetDefaultSQL()
{
	return "LEGENDA";
}

void CLegendaSet::SetEmpty()
{
	m_lUO = 0;
	m_lVoce = 0;
	m_sValore = "";
}

void CLegendaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "UO", m_lUO);
	RFX_Long(pFX, "Voce", m_lVoce);
	RFX_Text(pFX, "Valore", m_sValore, 25000);
}

CString CLegendaSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO;
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
