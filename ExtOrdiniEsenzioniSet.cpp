#include "stdafx.h"
#include "Endox.h"
#include "ExtOrdiniEsenzioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtOrdiniEsenzioniSet, CBaseSet)

CExtOrdiniEsenzioniSet::CExtOrdiniEsenzioniSet()
	: CBaseSet(NULL, "VIEW")
{
	SetSortRecord("IDRICHIESTA, DATASCADENZA, CODICE");

	m_nFields = 5;
}

CExtOrdiniEsenzioniSet::~CExtOrdiniEsenzioniSet()
{
}

CString CExtOrdiniEsenzioniSet::GetDefaultSQL()
{
	return "EXT_ORDINI_ESENZIONI";
}

void CExtOrdiniEsenzioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDRichiesta", m_lIDRichiesta);
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "DataScadenza", m_sDataScadenza, 8);
	}
}