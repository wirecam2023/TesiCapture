#include "stdafx.h"
#include "Endox.h"
#include "VistaEsamiPendentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaEsamiPendentiSet, CBaseSet)

CVistaEsamiPendentiSet::CVistaEsamiPendentiSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("ESAMEDATA");

	m_nFields = 16;
}

CString CVistaEsamiPendentiSet::GetDefaultSQL()
{
	// Sandro 20/09/2013 // RAS 20130152 //
	if (theApp.m_bPersonalizzazioniBrasileEinstein)
		return "VistaEsamiPendentiEinstein";

	// Sandro 08/06/2015 //
	if (theApp.m_bPersonalizzazioniBrasileSirio)
		return "VistaEsamiPendentiSirio";

	return "VistaEsamiPendenti";
}

void CVistaEsamiPendentiSet::SetEmpty()
{
	m_sPazienteCognome = "";
	m_sPazienteNome = "";
	m_lEsameID = 0;
	m_sEsameTipo = "";
	m_lEsameData = 0;
	m_sMedicoCognome = "";
	m_sMedicoNome = "";
	m_sEsameSala = "";
	m_sInvianteMedico = "";
	m_sFicha = "";
	m_sFichaItem = "";
	m_lUO = 0;
	m_lRefertoLen = 0;
	m_sRedattoreCognome = "";
	m_sRedattoreNome = "";
	m_sTesto000 = "";
}

void CVistaEsamiPendentiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "PazienteCognome", m_sPazienteCognome, 255);
	RFX_Text(pFX, "PazienteNome", m_sPazienteNome, 255);
	RFX_Long(pFX, "EsameID", m_lEsameID);
	RFX_Text(pFX, "EsameTipo", m_sEsameTipo, 255);
	RFX_Long(pFX, "EsameData", m_lEsameData);
	RFX_Text(pFX, "MedicoCognome", m_sMedicoCognome, 50);
	RFX_Text(pFX, "MedicoNome", m_sMedicoNome, 50);
	RFX_Text(pFX, "EsameSala", m_sEsameSala, 255);
	RFX_Text(pFX, "InvianteMedico", m_sInvianteMedico, 4000);
	RFX_Text(pFX, "FICHA", m_sFicha, 50);
	RFX_Text(pFX, "FICHAITEM", m_sFichaItem, 4000);
	RFX_Long(pFX, "UO", m_lUO);
	RFX_Long(pFX, "RefertoLen", m_lRefertoLen);
	RFX_Text(pFX, "RedattoreCognome", m_sRedattoreCognome, 50);
	RFX_Text(pFX, "RedattoreNome", m_sRedattoreNome, 50);
	RFX_Text(pFX, "Testo000", m_sTesto000, 4000);
}

BOOL CVistaEsamiPendentiSet::MedicoHasEsamiAperti(long lIDMedico)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("MedicoID=%li", lIDMedico);

	SetOpenFilter(strFilter);
	SetSortRecord("");
	if (OpenRecordset("CVistaEsamiPendentiSet::MedicoHasEsamiAperti"))
	{
		if (!IsEOF())
			bReturn = TRUE;

		CloseRecordset("CVistaEsamiPendentiSet::MedicoHasEsamiAperti");
	}

	return bReturn;
}
