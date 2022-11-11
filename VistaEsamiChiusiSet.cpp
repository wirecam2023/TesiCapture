#include "stdafx.h"
#include "Endox.h"
#include "VistaEsamiChiusiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaEsamiChiusiSet, CBaseSet)

CVistaEsamiChiusiSet::CVistaEsamiChiusiSet()
: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");

	SetSortRecord("dataora");

	m_nFields = 11;

}

CVistaEsamiChiusiSet::~CVistaEsamiChiusiSet()
{
}

CString CVistaEsamiChiusiSet::GetDefaultSQL()
{
	return "VISTA_ESAMICHIUSI";
}

void CVistaEsamiChiusiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "idchiusura", m_lIdChiusura);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "idesame", m_lIdEsame);
		RFX_Long(pFX, "idpdf", m_lIdPdf);
		RFX_Text(pFX, "dataora", m_sDataOra, 14);
		RFX_Long(pFX, "idutente", m_lIdUtente);
		RFX_Text(pFX, "tipologia", m_sTipologia, 50);
		RFX_Long(pFX, "tipologiaWorklist", m_lTipologiaWorklist);
		RFX_Text(pFX, "esito", m_sEsito, 10000000);
		RFX_Text(pFX, "codesame", m_sCodEsame, 50);
		RFX_Long(pFX, "paziente", m_lIdPaziente);
		RFX_Long(pFX, "eseguito", m_lEseguito);
	}
}

