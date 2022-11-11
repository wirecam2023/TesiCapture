#include "stdafx.h"
#include "Endox.h"
#include "SetupSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSetupSet, CBaseSet)

CSetupSet::CSetupSet()
	: CBaseSet(NULL, "NOLOG") // non lascio traccia delle modifiche //
{
	SetBaseFilter("");
	SetEmpty();
	SetSortRecord("VOCE");

	m_nFields = 3;
}

CString CSetupSet::GetDefaultSQL()
{
	return "CONFIGURAZIONI";
}

void CSetupSet::SetEmpty()
{
	m_lUO = 0;
	m_sVoce = "";
	m_sValore = "";
}

void CSetupSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "UO", m_lUO);
	RFX_Text(pFX, "VOCE", m_sVoce, 255);
	RFX_Text(pFX, "VALORE", m_sValore, 255);
}

CString CSetupSet::SetBaseFilter(const CString &strFilter)
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

BOOL CSetupSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
