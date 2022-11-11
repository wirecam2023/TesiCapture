#include "stdafx.h"
#include "Endox.h"
#include "VistaAnatomiaPatologicaRichSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaAnatomiaPatologicaRichSet, CBaseSet)

CVistaAnatomiaPatologicaRichSet::CVistaAnatomiaPatologicaRichSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetSortRecord("DATA");

	SetEmpty();

	m_nFields = 18;
}

CString CVistaAnatomiaPatologicaRichSet::GetDefaultSQL()
{
	return "VistaAnatomiaPatologicaRich";
}

void CVistaAnatomiaPatologicaRichSet::SetEmpty()
{
	m_lIDPaziente = 0;
	m_lIDEsame = 0;
	m_sCognome = "";
	m_sNome = "";
	m_lNatoIlCustom = 0;
	m_lTipoEsame = 0;
	//m_sTipoEsame = "";
	m_lData = 0;
	m_lMedico = 0;
	//m_sMedico = "";
	m_lProvenienza = 0;
	m_sProvenienza2 = "";
	m_lStato = -1;
	m_nAnatomiaSpedireRitirare = 0;
	m_bAnatomiaRefertato = FALSE;
	m_bAnatomiaVerificato = FALSE;
	m_bAnatomiaSpeditoRitirato = FALSE;
	m_sDataAnatomiaVerificato = "";
	m_sDataAnatomiaSpeditoRitirato = "";
	m_lTipoDegenzaEsterno = 0;
}

void CVistaAnatomiaPatologicaRichSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	RFX_Text(pFX, "Cognome", m_sCognome);
	RFX_Text(pFX, "Nome", m_sNome);
	RFX_Long(pFX, "NatoIlCustom", m_lNatoIlCustom);
	RFX_Long(pFX, "TipoEsame", m_lTipoEsame);
	//RFX_Text(pFX, "DescrizioneEsame", m_sTipoEsame);
	RFX_Long(pFX, "Data", m_lData);
	RFX_Long(pFX, "Medico", m_lMedico);
	//RFX_Text(pFX, "DescrizioneMedico", m_sMedico);
	RFX_Long(pFX, "Provenienza", m_lProvenienza);
	RFX_Text(pFX, "Provenienza2", m_sProvenienza2);
	RFX_Long(pFX, "Stato", m_lStato);
	RFX_Int(pFX, "SpedireRitirare", m_nAnatomiaSpedireRitirare);
	RFX_Bool(pFX, "Refertato", m_bAnatomiaRefertato);
	RFX_Bool(pFX, "Verificato", m_bAnatomiaVerificato);
	RFX_Bool(pFX, "SpeditoRitirato", m_bAnatomiaSpeditoRitirato);
	RFX_Text(pFX, "DataVerificato", m_sDataAnatomiaVerificato);
	RFX_Text(pFX, "DataSpeditoRitirato", m_sDataAnatomiaSpeditoRitirato);
	RFX_Long(pFX, "TipoDegenzaEsterno", m_lTipoDegenzaEsterno);
}