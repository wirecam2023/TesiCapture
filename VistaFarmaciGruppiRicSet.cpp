#include "stdafx.h"
#include "Endox.h"
#include "VistaFarmaciGruppiRicSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaFarmaciGruppiRicSet, CBaseSet)

CVistaFarmaciGruppiRicSet::CVistaFarmaciGruppiRicSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("ID");

	m_nFields = 7;
}

CString CVistaFarmaciGruppiRicSet::GetDefaultSQL()
{
	return "VistaFarmaciGruppiRic";
}

void CVistaFarmaciGruppiRicSet::SetEmpty()
{
	m_lID = 0;
	m_lIDGruppo = 0;
	m_sNome = "";
	m_sPrincipioAttivo = "";
	m_sDescrizione = "";
	m_lQuantita = 1;
	m_sTestoLibero = "";
}

void CVistaFarmaciGruppiRicSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	RFX_Long(pFX, "IDGruppo", m_lIDGruppo);
	RFX_Text(pFX, "Nome", m_sNome, 255);
	RFX_Text(pFX, "PrincipioAttivo", m_sPrincipioAttivo, 255);
	RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
	RFX_Long(pFX, "Quantita", m_lQuantita);
	RFX_Text(pFX, "TestoLibero", m_sTestoLibero, 255);
}