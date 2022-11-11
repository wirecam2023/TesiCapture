#include "stdafx.h"
#include "Endox.h"
#include "VistaCampiObbligatoriFasiNewSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaCampiObbligatoriFasiNewSet, CBaseSet)

CVistaCampiObbligatoriFasiNewSet::CVistaCampiObbligatoriFasiNewSet()
: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("ID");

	m_nFields = 7;
	SetBaseFilter("");
}

CString CVistaCampiObbligatoriFasiNewSet::GetDefaultSQL()
{
	return "VistaCampiObbligatori";
}

void CVistaCampiObbligatoriFasiNewSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	RFX_Long(pFX, "IDTIPOESAME", m_lIdTipoEsame);
	RFX_Text(pFX, "DESCRIZIONETIPOESAME", m_sTipoEsame, 255);
	RFX_Long(pFX, "IDPROVENIENZA", m_lIdProvenienzaNew);
	RFX_Text(pFX, "DESCRIZIONEPROVENIENZA", m_sProvenienza, 255);
	RFX_Long(pFX, "IDFaseNEW", m_lIDFaseNew);
	RFX_Long(pFX, "Campo", m_lCampo);
}

void CVistaCampiObbligatoriFasiNewSet::SetEmpty()
{
	m_lID = 0;
	m_lIdTipoEsame = 0;
	m_sTipoEsame = "";
	m_lIdProvenienzaNew = 0;
	m_sProvenienza = "";
	m_lIDFaseNew = 0;
	m_lCampo = 0;
}

CString CVistaCampiObbligatoriFasiNewSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "IDFASENEW > 0";
	}
	else
	{
		strNewFilter += " AND IDFASENEW > 0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}