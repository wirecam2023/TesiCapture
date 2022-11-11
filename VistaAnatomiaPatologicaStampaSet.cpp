#include "stdafx.h"
#include "Endox.h"
#include "VistaAnatomiaPatologicaStampaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaAnatomiaPatologicaStampaSet, CBaseSet)

CVistaAnatomiaPatologicaStampaSet::CVistaAnatomiaPatologicaStampaSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetSortRecord("IDEsame");

	SetEmpty();

	m_nFields = 10;
}

CString CVistaAnatomiaPatologicaStampaSet::GetDefaultSQL()
{
	return "VistaAnatomiaPatologicaStampa";
}

void CVistaAnatomiaPatologicaStampaSet::SetEmpty()
{
	m_sCognome = "";
	m_sNome = "";
	m_lDataNascita = 0;
	m_lIDEsame = 0;
	m_lDataEsame = 0;
	m_sSedeEsame = "";
	m_sDataOraSpeditoMetafora = "";
	m_lProvenienza = 0;
	m_sOspedale = "";
	m_sReparto = "";
}

void CVistaAnatomiaPatologicaStampaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "Cognome", m_sCognome, 50);
	RFX_Text(pFX, "Nome", m_sNome, 50);
	RFX_Long(pFX, "DataNascita", m_lDataNascita);
	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	RFX_Long(pFX, "DataEsame", m_lDataEsame);
	RFX_Text(pFX, "SedeEsame", m_sSedeEsame, 255);
	RFX_Text(pFX, "DataOraSpeditoMetafora", m_sDataOraSpeditoMetafora, 14);
	RFX_Long(pFX, "Provenienza", m_lProvenienza);
	RFX_Text(pFX, "Ospedale", m_sOspedale, 255);
	RFX_Text(pFX, "Reparto", m_sReparto, 50);
}