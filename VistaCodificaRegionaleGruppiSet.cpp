#include "stdafx.h"
#include "Endox.h"
#include "VistaCodificaRegionaleGruppiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaCodificaRegionaleGruppiSet, CBaseSet)

CVistaCodificaRegionaleGruppiSet::CVistaCodificaRegionaleGruppiSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("ID");

	m_nFields = 5;
}

CString CVistaCodificaRegionaleGruppiSet::GetDefaultSQL()
{
	return "VistaCodificaRegionaleGruppi";
}

void CVistaCodificaRegionaleGruppiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDGruppo = 0;
	m_sDescrizione = "";
	m_lQuantita = 1;
	m_sTestoLibero = "";
}

void CVistaCodificaRegionaleGruppiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	RFX_Long(pFX, "IDGruppo", m_lIDGruppo);
	RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
	RFX_Long(pFX, "Quantita", m_lQuantita);
	RFX_Text(pFX, "TestoLibero", m_sTestoLibero, 255);
}