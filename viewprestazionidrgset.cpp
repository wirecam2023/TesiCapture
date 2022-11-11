#include "stdafx.h"
#include "Endox.h"
#include "viewprestazionidrgset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CViewPrestazioniDrgSet, CBaseSet)

CViewPrestazioniDrgSet::CViewPrestazioniDrgSet()
	: CBaseSet(NULL, "VIEW") // è una vista //
{
	SetSortRecord("ID");

	SetEmpty();

	m_nFields = 9;
}

CString CViewPrestazioniDrgSet::GetDefaultSQL()
{
	return "VIEWPRESTAZIONIDRG";
}

void CViewPrestazioniDrgSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lId);
	RFX_Long(pFX, "QUANTITA", m_lQuantita);
	RFX_Long(pFX, "DATA", m_lData);
	RFX_Text(pFX, "CODICENAZIONALE",   m_sCodNazionale, 10);
	RFX_Text(pFX, "CODICEREGIONALE",   m_sCodRegionale, 10);
	RFX_Text(pFX, "DESCRIZIONE",    m_sDescrizione, 255);
	RFX_Single(pFX,"TOTALEGLOBALE", m_fCostoTotale);
	RFX_Text(pFX, "SEDEESAME",    m_sSedeEsame, 255);
	RFX_Long(pFX, "IDSEDEESAME", m_lIdSedeEsame);
}

void CViewPrestazioniDrgSet::SetEmpty()
{
	m_lId = 0;
	m_lQuantita = 0;
	m_lData = 0;
	m_sCodNazionale = "";
	m_sCodRegionale = "";
	m_sDescrizione = "";
	m_fCostoTotale = 0.0f;
	m_sSedeEsame = "";
	m_lIdSedeEsame = 0;
}
