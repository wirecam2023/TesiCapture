#include "stdafx.h"
#include "Endox.h"
#include "TbLogCompletoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTbLogCompletoSet, CBaseSet)

CTbLogCompletoSet::CTbLogCompletoSet()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 14;
}

CString CTbLogCompletoSet::GetDefaultSQL()
{
	return "tb_LogCompleto";
}

void CTbLogCompletoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Text(pFX, "Impianto", m_sImpianto, 50);
		RFX_Text(pFX, "Utente", m_sUtente, 50);
		RFX_Text(pFX, "Stazione", m_sStazione, 50);
		RFX_Text(pFX, "Tabella", m_sTabella, 50);
		RFX_Long(pFX, "Operazione", m_lOperazione);
		RFX_Text(pFX, "NomeChiave", m_sNomeChiave, 50);
		RFX_Long(pFX, "ValoreChiave", m_lValoreChiave);
		RFX_Text(pFX, "Campo", m_sCampo, 50);
		RFX_Text(pFX, "ValoreOld", m_sValoreOld, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "ValoreNew", m_sValoreNew, _TEXT_CONTROL_FIELD_LIMIT);
	}
}

void CTbLogCompletoSet::SetEmpty()
{
	m_lID = 0;
	m_lIDPaziente = 0;
	m_lIDEsame = 0;
	m_sDataOra = "";
	m_sImpianto = "";
	m_sUtente = "";
	m_sStazione = "";
	m_sTabella = "";
	m_lOperazione = 0;
	m_sNomeChiave = "";
	m_lValoreChiave = 0;
	m_sCampo = "";
	m_sValoreOld = "";
	m_sValoreNew = "";
}