#include "stdafx.h"
#include "Endox.h"
#include "VistaFlussoDiStatoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaFlussoDiStatoSet, CBaseSet)

CVistaFlussoDiStatoSet::CVistaFlussoDiStatoSet()
: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");

	SetSortRecord("DataEsame");

	m_nFields = 17;
}

CString CVistaFlussoDiStatoSet::GetDefaultSQL()
{
	return "VISTA_FLUSSODISTATO";
}

void CVistaFlussoDiStatoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "OrdineFase", m_lOrdineFase);
	RFX_Long(pFX, "IdOrdine", m_lIdOrdine);
	RFX_Long(pFX, "IdEsame", m_IdEsame);
	RFX_Text(pFX, "CodEsame", m_sCodEsame, 50);
	RFX_Text(pFX, "DataEsame", m_sDataEsame, 14);
	RFX_Text(pFX, "DataOraConsegnaReferto", m_sDataOraConsegnaReferto, 50);
	RFX_Text(pFX, "DataEsameFormata", m_sDataEsameFormata, 10);
	RFX_Text(pFX, "OraEsame", m_sOraEsame, 5);
	RFX_Text(pFX, "Assiden", m_sAssiden, 50);
	RFX_Text(pFX, "Nome", m_sNome, 50);
	RFX_Text(pFX, "Cognome", m_sCognome, 50);
	RFX_Text(pFX, "DataNascita", m_sDataNascita, 10);
	RFX_Text(pFX, "Sesso", m_sSesso, 1);
	RFX_Text(pFX, "TipoEsame", m_sTipoEsame, 255);
	RFX_Text(pFX, "DescrizioneEsame", m_sDescrizioneEsame, 4000);
	RFX_Text(pFX, "SiglaEsame", m_sSiglaEsame, 255);
	RFX_Long(pFX, "IdUO", m_lIdUO);
}

void CVistaFlussoDiStatoSet::SetEmpty()
{
	m_lOrdineFase = -1;
	m_lIdOrdine = -1;
	m_IdEsame = -1;
	m_sCodEsame = "";
	m_sDataEsame = "";
	m_sDataOraConsegnaReferto = "";
	m_sDataEsameFormata = "";
	m_sOraEsame = "";
	m_sAssiden = "";
	m_sNome = "";
	m_sCognome = "";
	m_sDataNascita = "";
	m_sSesso = "";
	m_sTipoEsame = "";
	m_sDescrizioneEsame = "";
	m_sSiglaEsame = "";
	m_lIdUO = -1;
}

CBaseSet* CVistaFlussoDiStatoSet::CreateNew()
{
	return (CBaseSet*)new CVistaFlussoDiStatoSet;
}

