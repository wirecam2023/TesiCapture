#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrelieviItemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrelieviItemView, CBaseSet)

CGruppiPrelieviItemView::CGruppiPrelieviItemView()
	: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("ID");

	m_nFields = 7;
}

void CGruppiPrelieviItemView::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDGruppo", m_lIDGruppo);
		RFX_Text(pFX, "Tipo", m_sTipo, 1);
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Intervento", m_sIntervento, 50);
		RFX_Long(pFX, "Prelievi", m_lPrelievi);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
	}
}

CString CGruppiPrelieviItemView::GetDefaultSQL()
{
	return "VISTAGRUPPIPRELIEVIITEM";
}

void CGruppiPrelieviItemView::SetEmpty()
{
	m_lID = 0;
	m_lIDGruppo = 0;
	m_sTipo = "";
	m_sCodice = "";
	m_sIntervento = "";
	m_lPrelievi = 0;
	m_sDescrizione = "";
}