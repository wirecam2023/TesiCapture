#include "stdafx.h"
#include "Endox.h"
#include "VistaCampiObbligatoriDistinctSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaCampiObbligatoriDistinctSet, CBaseSet)

CVistaCampiObbligatoriDistinctSet::CVistaCampiObbligatoriDistinctSet()
: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");
	SetEmpty();
	SetSortRecord("ID");

	m_nFields = 6;
}

CString CVistaCampiObbligatoriDistinctSet::GetDefaultSQL()
{
	return "VISTACAMPIOBBLIGATORIDISTINCT";
}

void CVistaCampiObbligatoriDistinctSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);	
	RFX_Long(pFX, "CAMPO", m_lCampo);
	RFX_Long(pFX, "IDFASENEW", m_lIDFaseNew);
	RFX_Text(pFX, "TIPIESAME", m_sTipiEsame, 3999);
	RFX_Text(pFX, "PROVENIENZE", m_sProvenienze, 3999);
	RFX_Long(pFX, "UO", m_lUO);
}

void CVistaCampiObbligatoriDistinctSet::SetEmpty()
{
	m_lID = 0;
	m_sTipiEsame = "";
	m_sProvenienze = "";
	m_lCampo = 0;
	m_lFase = 0;
	m_lIDFaseNew = 0;
	m_lUO = 0;
}

CString CVistaCampiObbligatoriDistinctSet::SetBaseFilter(const CString &strFilter)
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