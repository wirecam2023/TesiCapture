#include "stdafx.h"
#include "Endox.h"
#include "VistaProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaProcedureICD9Set, CBaseSet)

CVistaProcedureICD9Set::CVistaProcedureICD9Set()
	: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");
	SetEmpty();
	SetSortRecord("Descrizione");

	m_nFields = 7;
}

CString CVistaProcedureICD9Set::GetDefaultSQL()
{
	return "VistaProcedureICD9";
}

void CVistaProcedureICD9Set::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
	RFX_Text(pFX, "CodificaInterna", m_sCodificaInterna, 50);
	RFX_Text(pFX, "CodificaICD9Interni", m_sCodificaICD9Interni, 50);
	RFX_Text(pFX, "CodificaICD9Esterni", m_sCodificaICD9Esterni, 50);
	RFX_Long(pFX, "UO", m_lUO);
	RFX_Long(pFX, "IDTipoEsame", m_lIDTipoEsame);
}

void CVistaProcedureICD9Set::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sCodificaInterna = "";
	m_sCodificaICD9Interni = "";
	m_sCodificaICD9Esterni = "";
	m_lUO = 0;
	m_lIDTipoEsame = 0;
}

CString CVistaProcedureICD9Set::SetBaseFilter(const CString &strFilter)
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