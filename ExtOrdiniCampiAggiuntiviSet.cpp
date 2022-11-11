#include "stdafx.h"
#include "Endox.h"
#include "ExtOrdiniCampiAggiuntiviSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtOrdiniCampiAggiuntiviSet, CBaseSet)

CExtOrdiniCampiAggiuntiviSet::CExtOrdiniCampiAggiuntiviSet()
	: CBaseSet(NULL, "VIEW")
{
	SetSortRecord("IDRICHIESTA, TABELLA, CAMPO");

	m_nFields = 5;
}

CExtOrdiniCampiAggiuntiviSet::~CExtOrdiniCampiAggiuntiviSet()
{
}

CString CExtOrdiniCampiAggiuntiviSet::GetDefaultSQL()
{
	return "EXT_ORDINI_CAMPIAGGIUNTIVI";
}

void CExtOrdiniCampiAggiuntiviSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDRichiesta", m_lIDRichiesta);
		RFX_Text(pFX, "Tabella", m_sTabella, 50);
		RFX_Text(pFX, "Campo", m_sCampo, 50);
		RFX_Text(pFX, "Valore", m_sValore, _TEXT_CONTROL_FIELD_LIMIT);
	}
}