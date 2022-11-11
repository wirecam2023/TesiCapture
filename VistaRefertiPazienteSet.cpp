#include "stdafx.h"
#include "Endox.h"
#include "VistaRefertiPazienteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaRefertiPazienteSet, CBaseSet)

CVistaRefertiPazienteSet::CVistaRefertiPazienteSet()
	: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("Data, IDEsame");

	m_nFields = 4;
}

CString CVistaRefertiPazienteSet::GetDefaultSQL()
{
	return "VistaRefertiPaziente";
}

void CVistaRefertiPazienteSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	// RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	RFX_Text(pFX, "TipoEsame", m_sTipoEsame, 255);
	RFX_Long(pFX, "Data", m_lData);
	RFX_Text(pFX, "Referto", m_sReferto, _TEXT_CONTROL_FIELD_LIMIT);
}

void CVistaRefertiPazienteSet::SetEmpty()
{
	// m_lIDPaziente = 0;
	m_lIDEsame = 0;
	m_sTipoEsame = "";
	m_lData = 0;
	m_sReferto = "";
}