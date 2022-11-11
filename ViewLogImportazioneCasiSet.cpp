#include "stdafx.h"
#include "Endox.h"
#include "ViewLogImportazioneCasiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CViewLogImportazioneCasiSet, CBaseSet)

CViewLogImportazioneCasiSet::CViewLogImportazioneCasiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 14;
}

CString CViewLogImportazioneCasiSet::GetDefaultSQL()
{
	return "View_LogImportazioneCasi";
}

void CViewLogImportazioneCasiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "ID", m_lID);
		RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
		RFX_Text(pFX, "Cognome", m_sCognome, 50);
		RFX_Text(pFX, "Nome", m_sNome, 50);
		RFX_Long(pFX, "IDEsameOrigine", m_lIDEsameOrigine);
		RFX_Text(pFX, "CodiceEsternoEsameOrigine", m_sCodiceEsternoEsameOrigine, 50);
		RFX_Text(pFX, "TipoEsameOrigine", m_sTipoEsameOrigine, 255);
		RFX_Long(pFX, "IDEsameDestinazione", m_lIDEsameDestinazione);
		RFX_Text(pFX, "CodiceEsternoEsameDestinazione", m_sCodiceEsternoEsameDestinazione, 50);
		RFX_Text(pFX, "TipoEsameDestinazione", m_sTipoEsameDestinazione, 255);
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Text(pFX, "Utente", m_sUtente, 50);
		RFX_Text(pFX, "Stazione", m_sStazione, 50);
	}
}

void CViewLogImportazioneCasiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDPaziente = 0;
	m_sCognome = "";
	m_sNome = "";
	m_lIDEsameOrigine = 0;
	m_sCodiceEsternoEsameOrigine = "";
	m_sTipoEsameOrigine = "";
	m_lIDEsameDestinazione = 0;
	m_sCodiceEsternoEsameDestinazione = "";
	m_sTipoEsameDestinazione = "";
	m_sDataOra = "";
	m_sUtente = "";
	m_sStazione = "";
}