#include "stdafx.h"
#include "Endox.h"
#include "PrenotazioniBolzanoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPrenotazioniBolzanoSet, CBaseSet)

CPrenotazioniBolzanoSet::CPrenotazioniBolzanoSet(CAMBaseDB* pdb)
	: CBaseSet(NULL, "VIEW")
{
	m_lToken = 0;
	m_bArrivato = FALSE;
	m_sGiorno = "";
	m_sOra = "";
	m_sStanza = "";
	m_lContatorePaziente = 0;
	m_sCognomePaziente = "";
	m_sNomePaziente = "";
	m_sPrestazione = "";
	m_sTitoloMedico = "";
	m_sCognomeMedico = "";
	m_sNomeMedico = "";
	m_bAccettata = FALSE;
	m_sNote = "";
	m_sReparto = "";

	m_nFields = 15;
}

CPrenotazioniBolzanoSet::~CPrenotazioniBolzanoSet()
{
}

void CPrenotazioniBolzanoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "TOKEN",				m_lToken				);
	RFX_Bool(pFX, "ARRIVATO",			m_bArrivato             );
	RFX_Text(pFX, "GIORNO_ESAME",		m_sGiorno,			   8);
	RFX_Text(pFX, "ORA_ESAME",			m_sOra,				   4);
	RFX_Text(pFX, "DEN_STANZA",			m_sStanza,			 255);
	RFX_Long(pFX, "CONTATORE",			m_lContatorePaziente    );
	RFX_Text(pFX, "COGNOME",			m_sCognomePaziente,	 255);
	RFX_Text(pFX, "NOME",				m_sNomePaziente,	 255);
	RFX_Text(pFX, "DEN_PRESTAZIONE",	m_sPrestazione,		 255);
	RFX_Text(pFX, "TITOLOMEDICO",		m_sTitoloMedico,	  50);
	RFX_Text(pFX, "COGNOMEMEDICO",		m_sCognomeMedico,	  50);
	RFX_Text(pFX, "NOMEMEDICO",			m_sNomeMedico,		  50);
	RFX_Bool(pFX, "ACCETTATA",			m_bAccettata            );
	RFX_Text(pFX, "NOTE",				m_sNote,			3999); 
	RFX_Text(pFX, "T_REPARTO",			m_sReparto,			 255);
}

CString CPrenotazioniBolzanoSet::GetDefaultSQL()
{
	return "ELENCO_PRENOTAZIONI";
}

void CPrenotazioniBolzanoSet::SetEmpty()
{
	m_lToken = 0;
	m_bArrivato = FALSE;
	m_sGiorno = "";
	m_sOra = "";
	m_sStanza = "";
	m_lContatorePaziente = 0;
	m_sCognomePaziente = "";
	m_sNomePaziente = "";
	m_sPrestazione = "";
	m_sTitoloMedico = "";
	m_sCognomeMedico = "";
	m_sNomeMedico = "";
	m_bAccettata = FALSE;
	m_sNote = "";
	m_sReparto = "";
}