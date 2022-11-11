#include "stdafx.h"
#include "Endox.h"
#include "SetupServiziSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSetupServiziSet, CBaseSet)

CSetupServiziSet::CSetupServiziSet()
	: CBaseSet(NULL, "NOLOG") // non lascio traccia delle modifiche //
{
	SetBaseFilter("");
	SetEmpty();
	SetSortRecord("PARAMETRO");

	m_nFields = 3;
}

CString CSetupServiziSet::GetDefaultSQL()
{
	return "CONFIGURAZIONESERVIZI";
}

void CSetupServiziSet::SetEmpty()
{
	m_sIdServizio = "";
	m_sParametro = "";
	m_sValore = "";
}

void CSetupServiziSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "IdServizio", m_sIdServizio);
	RFX_Text(pFX, "Parametro", m_sParametro, 255);
	RFX_Text(pFX, "Valore", m_sValore, 255);
}

CString CSetupServiziSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	/*CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO;
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;
	}*/

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CSetupServiziSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}
