#include "stdafx.h"
#include "Endox.h"
#include "VistaCheckListSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaCheckListSet, CBaseSet)

CVistaCheckListSet::CVistaCheckListSet()
	: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("Ordine, ID");

	m_nFields = 6;
}

CString CVistaCheckListSet::GetDefaultSQL()
{
	return "VistaCheckList";
}

void CVistaCheckListSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID",	m_lID);
	RFX_Text(pFX, "Codice", m_sCodice, 50);
	RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
	RFX_Long(pFX, "IDTipoEsame", m_lIDTipoEsame);
	RFX_Long(pFX, "CampoCL", m_lCampoCL);
	RFX_Long(pFX, "Ordine", m_lOrdine);
}

void CVistaCheckListSet::SetEmpty()
{
	m_lID = 0;
	m_sCodice = "";
	m_sDescrizione = "";
	m_lIDTipoEsame = 0;
	m_lCampoCL = 0;
	m_lOrdine = 0;
}