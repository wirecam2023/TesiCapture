#include "stdafx.h"
#include "Endox.h"
#include "EbusSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEbusSet, CBaseSet)

CEbusSet::CEbusSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 91;
}

CString CEbusSet::GetDefaultSQL()
{
	return "EBUS";
}

void CEbusSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Text(pFX, "Dimensione_12R", m_sDimensione_12R, 255);
		RFX_Text(pFX, "Dimensione_11R", m_sDimensione_11R, 255);
		RFX_Text(pFX, "Dimensione_10R", m_sDimensione_10R, 255);
		RFX_Text(pFX, "Dimensione_4R", m_sDimensione_4R, 255);
		RFX_Text(pFX, "Dimensione_2R", m_sDimensione_2R, 255);
		RFX_Text(pFX, "Dimensione_7", m_sDimensione_7, 255);
		RFX_Text(pFX, "Dimensione_2L", m_sDimensione_2L, 255);
		RFX_Text(pFX, "Dimensione_4L", m_sDimensione_4L, 255);
		RFX_Text(pFX, "Dimensione_10L", m_sDimensione_10L, 255);
		RFX_Text(pFX, "Dimensione_11L", m_sDimensione_11L, 255);
		RFX_Text(pFX, "Dimensione_12L", m_sDimensione_12L, 255);
		RFX_Text(pFX, "Puntura_12R", m_sPuntura_12R, 255);
		RFX_Text(pFX, "Puntura_11R", m_sPuntura_11R, 255);
		RFX_Text(pFX, "Puntura_10R", m_sPuntura_10R, 255);
		RFX_Text(pFX, "Puntura_4R", m_sPuntura_4R, 255);
		RFX_Text(pFX, "Puntura_2R", m_sPuntura_2R, 255);
		RFX_Text(pFX, "Puntura_7", m_sPuntura_7, 255);
		RFX_Text(pFX, "Puntura_2L", m_sPuntura_2L, 255);
		RFX_Text(pFX, "Puntura_4L", m_sPuntura_4L, 255);
		RFX_Text(pFX, "Puntura_10L", m_sPuntura_10L, 255);
		RFX_Text(pFX, "Puntura_11L", m_sPuntura_11L, 255);
		RFX_Text(pFX, "Puntura_12L", m_sPuntura_12L, 255);
		RFX_Text(pFX, "NumeroPunture_12R", m_sNumeroPunture_12R, 255);
		RFX_Text(pFX, "NumeroPunture_11R", m_sNumeroPunture_11R, 255);
		RFX_Text(pFX, "NumeroPunture_10R", m_sNumeroPunture_10R, 255);
		RFX_Text(pFX, "NumeroPunture_4R", m_sNumeroPunture_4R, 255);
		RFX_Text(pFX, "NumeroPunture_2R", m_sNumeroPunture_2R, 255);
		RFX_Text(pFX, "NumeroPunture_7", m_sNumeroPunture_7, 255);
		RFX_Text(pFX, "NumeroPunture_2L", m_sNumeroPunture_2L, 255);
		RFX_Text(pFX, "NumeroPunture_4L", m_sNumeroPunture_4L, 255);
		RFX_Text(pFX, "NumeroPunture_10L", m_sNumeroPunture_10L, 255);
		RFX_Text(pFX, "NumeroPunture_11L", m_sNumeroPunture_11L, 255);
		RFX_Text(pFX, "NumeroPunture_12L", m_sNumeroPunture_12L, 255);
		RFX_Text(pFX, "Forma_12R", m_sForma_12R, 255);
		RFX_Text(pFX, "Forma_11R", m_sForma_11R, 255);
		RFX_Text(pFX, "Forma_10R", m_sForma_10R, 255);
		RFX_Text(pFX, "Forma_4R", m_sForma_4R, 255);
		RFX_Text(pFX, "Forma_2R", m_sForma_2R, 255);
		RFX_Text(pFX, "Forma_7", m_sForma_7, 255);
		RFX_Text(pFX, "Forma_2L", m_sForma_2L, 255);
		RFX_Text(pFX, "Forma_4L", m_sForma_4L, 255);
		RFX_Text(pFX, "Forma_10L", m_sForma_10L, 255);
		RFX_Text(pFX, "Forma_11L", m_sForma_11L, 255);
		RFX_Text(pFX, "Forma_12L", m_sForma_12L, 255);
		RFX_Text(pFX, "Margine_12R", m_sMargine_12R, 255);
		RFX_Text(pFX, "Margine_11R", m_sMargine_11R, 255);
		RFX_Text(pFX, "Margine_10R", m_sMargine_10R, 255);
		RFX_Text(pFX, "Margine_4R", m_sMargine_4R, 255);
		RFX_Text(pFX, "Margine_2R", m_sMargine_2R, 255);
		RFX_Text(pFX, "Margine_7", m_sMargine_7, 255);
		RFX_Text(pFX, "Margine_2L", m_sMargine_2L, 255);
		RFX_Text(pFX, "Margine_4L", m_sMargine_4L, 255);
		RFX_Text(pFX, "Margine_10L", m_sMargine_10L, 255);
		RFX_Text(pFX, "Margine_11L", m_sMargine_11L, 255);
		RFX_Text(pFX, "Margine_12L", m_sMargine_12L, 255);
		RFX_Text(pFX, "Ecogenicita_12R", m_sEcogenicita_12R, 255);
		RFX_Text(pFX, "Ecogenicita_11R", m_sEcogenicita_11R, 255);
		RFX_Text(pFX, "Ecogenicita_10R", m_sEcogenicita_10R, 255);
		RFX_Text(pFX, "Ecogenicita_4R", m_sEcogenicita_4R, 255);
		RFX_Text(pFX, "Ecogenicita_2R", m_sEcogenicita_2R, 255);
		RFX_Text(pFX, "Ecogenicita_7", m_sEcogenicita_7, 255);
		RFX_Text(pFX, "Ecogenicita_2L", m_sEcogenicita_2L, 255);
		RFX_Text(pFX, "Ecogenicita_4L", m_sEcogenicita_4L, 255);
		RFX_Text(pFX, "Ecogenicita_10L", m_sEcogenicita_10L, 255);
		RFX_Text(pFX, "Ecogenicita_11L", m_sEcogenicita_11L, 255);
		RFX_Text(pFX, "Ecogenicita_12L", m_sEcogenicita_12L, 255);
		RFX_Text(pFX, "Filo_12R", m_sFilo_12R, 255);
		RFX_Text(pFX, "Filo_11R", m_sFilo_11R, 255);
		RFX_Text(pFX, "Filo_10R", m_sFilo_10R, 255);
		RFX_Text(pFX, "Filo_4R", m_sFilo_4R, 255);
		RFX_Text(pFX, "Filo_2R", m_sFilo_2R, 255);
		RFX_Text(pFX, "Filo_7", m_sFilo_7, 255);
		RFX_Text(pFX, "Filo_2L", m_sFilo_2L, 255);
		RFX_Text(pFX, "Filo_4L", m_sFilo_4L, 255);
		RFX_Text(pFX, "Filo_10L", m_sFilo_10L, 255);
		RFX_Text(pFX, "Filo_11L", m_sFilo_11L, 255);
		RFX_Text(pFX, "Filo_12L", m_sFilo_12L, 255);
		RFX_Text(pFX, "Necrosi_12R", m_sNecrosi_12R, 255);
		RFX_Text(pFX, "Necrosi_11R", m_sNecrosi_11R, 255);
		RFX_Text(pFX, "Necrosi_10R", m_sNecrosi_10R, 255);
		RFX_Text(pFX, "Necrosi_4R", m_sNecrosi_4R, 255);
		RFX_Text(pFX, "Necrosi_2R", m_sNecrosi_2R, 255);
		RFX_Text(pFX, "Necrosi_7", m_sNecrosi_7, 255);
		RFX_Text(pFX, "Necrosi_2L", m_sNecrosi_2L, 255);
		RFX_Text(pFX, "Necrosi_4L", m_sNecrosi_4L, 255);
		RFX_Text(pFX, "Necrosi_10L", m_sNecrosi_10L, 255);
		RFX_Text(pFX, "Necrosi_11L", m_sNecrosi_11L, 255);
		RFX_Text(pFX, "Necrosi_12L", m_sNecrosi_12L, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CEbusSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_sDimensione_12R = "";
	m_sDimensione_11R = "";
	m_sDimensione_10R = "";
	m_sDimensione_4R = "";
	m_sDimensione_2R = "";
	m_sDimensione_7 = "";
	m_sDimensione_2L = "";
	m_sDimensione_4L = "";
	m_sDimensione_10L = "";
	m_sDimensione_11L = "";
	m_sDimensione_12L = "";
	m_sPuntura_12R = "";
	m_sPuntura_11R = "";
	m_sPuntura_10R = "";
	m_sPuntura_4R = "";
	m_sPuntura_2R = "";
	m_sPuntura_7 = "";
	m_sPuntura_2L = "";
	m_sPuntura_4L = "";
	m_sPuntura_10L = "";
	m_sPuntura_11L = "";
	m_sPuntura_12L = "";
	m_sNumeroPunture_12R = "";
	m_sNumeroPunture_11R = "";
	m_sNumeroPunture_10R = "";
	m_sNumeroPunture_4R = "";
	m_sNumeroPunture_2R = "";
	m_sNumeroPunture_7 = "";
	m_sNumeroPunture_2L = "";
	m_sNumeroPunture_4L = "";
	m_sNumeroPunture_10L = "";
	m_sNumeroPunture_11L = "";
	m_sNumeroPunture_12L = "";
	m_sForma_12R = "";
	m_sForma_11R = "";
	m_sForma_10R = "";
	m_sForma_4R = "";
	m_sForma_2R = "";
	m_sForma_7 = "";
	m_sForma_2L = "";
	m_sForma_4L = "";
	m_sForma_10L = "";
	m_sForma_11L = "";
	m_sForma_12L = "";
	m_sMargine_12R = "";
	m_sMargine_11R = "";
	m_sMargine_10R = "";
	m_sMargine_4R = "";
	m_sMargine_2R = "";
	m_sMargine_7 = "";
	m_sMargine_2L = "";
	m_sMargine_4L = "";
	m_sMargine_10L = "";
	m_sMargine_11L = "";
	m_sMargine_12L = "";
	m_sEcogenicita_12R = "";
	m_sEcogenicita_11R = "";
	m_sEcogenicita_10R = "";
	m_sEcogenicita_4R = "";
	m_sEcogenicita_2R = "";
	m_sEcogenicita_7 = "";
	m_sEcogenicita_2L = "";
	m_sEcogenicita_4L = "";
	m_sEcogenicita_10L = "";
	m_sEcogenicita_11L = "";
	m_sEcogenicita_12L = "";
	m_sFilo_12R = "";
	m_sFilo_11R = "";
	m_sFilo_10R = "";
	m_sFilo_4R = "";
	m_sFilo_2R = "";
	m_sFilo_7 = "";
	m_sFilo_2L = "";
	m_sFilo_4L = "";
	m_sFilo_10L = "";
	m_sFilo_11L = "";
	m_sFilo_12L = "";
	m_sNecrosi_12R = "";
	m_sNecrosi_11R = "";
	m_sNecrosi_10R = "";
	m_sNecrosi_4R = "";
	m_sNecrosi_2R = "";
	m_sNecrosi_7 = "";
	m_sNecrosi_2L = "";
	m_sNecrosi_4L = "";
	m_sNecrosi_10L = "";
	m_sNecrosi_11L = "";
	m_sNecrosi_12L = "";
	m_bEliminato = FALSE;
}

CBaseSet* CEbusSet::CreateNew()
{
	return (CBaseSet*)new CEbusSet;
}

void CEbusSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEbusSet* pSet = (CEbusSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_12R) || bCopyAll)
		m_sDimensione_12R = pSet->m_sDimensione_12R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_11R) || bCopyAll)
		m_sDimensione_11R = pSet->m_sDimensione_11R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_10R) || bCopyAll)
		m_sDimensione_10R = pSet->m_sDimensione_10R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_4R) || bCopyAll)
		m_sDimensione_4R = pSet->m_sDimensione_4R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_2R) || bCopyAll)
		m_sDimensione_2R = pSet->m_sDimensione_2R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_7) || bCopyAll)
		m_sDimensione_7 = pSet->m_sDimensione_7;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_2L) || bCopyAll)
		m_sDimensione_2L = pSet->m_sDimensione_2L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_4L) || bCopyAll)
		m_sDimensione_4L = pSet->m_sDimensione_4L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_10L) || bCopyAll)
		m_sDimensione_10L = pSet->m_sDimensione_10L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_11L) || bCopyAll)
		m_sDimensione_11L = pSet->m_sDimensione_11L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDimensione_12L) || bCopyAll)
		m_sDimensione_12L = pSet->m_sDimensione_12L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_12R) || bCopyAll)
		m_sPuntura_12R = pSet->m_sPuntura_12R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_11R) || bCopyAll)
		m_sPuntura_11R = pSet->m_sPuntura_11R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_10R) || bCopyAll)
		m_sPuntura_10R = pSet->m_sPuntura_10R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_4R) || bCopyAll)
		m_sPuntura_4R = pSet->m_sPuntura_4R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_2R) || bCopyAll)
		m_sPuntura_2R = pSet->m_sPuntura_2R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_7) || bCopyAll)
		m_sPuntura_7 = pSet->m_sPuntura_7;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_2L) || bCopyAll)
		m_sPuntura_2L = pSet->m_sPuntura_2L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_4L) || bCopyAll)
		m_sPuntura_4L = pSet->m_sPuntura_4L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_10L) || bCopyAll)
		m_sPuntura_10L = pSet->m_sPuntura_10L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_11L) || bCopyAll)
		m_sPuntura_11L = pSet->m_sPuntura_11L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPuntura_12L) || bCopyAll)
		m_sPuntura_12L = pSet->m_sPuntura_12L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_12R) || bCopyAll)
		m_sNumeroPunture_12R = pSet->m_sNumeroPunture_12R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_11R) || bCopyAll)
		m_sNumeroPunture_11R = pSet->m_sNumeroPunture_11R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_10R) || bCopyAll)
		m_sNumeroPunture_10R = pSet->m_sNumeroPunture_10R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_4R) || bCopyAll)
		m_sNumeroPunture_4R = pSet->m_sNumeroPunture_4R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_2R) || bCopyAll)
		m_sNumeroPunture_2R = pSet->m_sNumeroPunture_2R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_7) || bCopyAll)
		m_sNumeroPunture_7 = pSet->m_sNumeroPunture_7;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_2L) || bCopyAll)
		m_sNumeroPunture_2L = pSet->m_sNumeroPunture_2L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_4L) || bCopyAll)
		m_sNumeroPunture_4L = pSet->m_sNumeroPunture_4L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_10L) || bCopyAll)
		m_sNumeroPunture_10L = pSet->m_sNumeroPunture_10L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_11L) || bCopyAll)
		m_sNumeroPunture_11L = pSet->m_sNumeroPunture_11L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroPunture_12L) || bCopyAll)
		m_sNumeroPunture_12L = pSet->m_sNumeroPunture_12L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_12R) || bCopyAll)
		m_sForma_12R = pSet->m_sForma_12R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_11R) || bCopyAll)
		m_sForma_11R = pSet->m_sForma_11R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_10R) || bCopyAll)
		m_sForma_10R = pSet->m_sForma_10R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_4R) || bCopyAll)
		m_sForma_4R = pSet->m_sForma_4R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_2R) || bCopyAll)
		m_sForma_2R = pSet->m_sForma_2R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_7) || bCopyAll)
		m_sForma_7 = pSet->m_sForma_7;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_2L) || bCopyAll)
		m_sForma_2L = pSet->m_sForma_2L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_4L) || bCopyAll)
		m_sForma_4L = pSet->m_sForma_4L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_10L) || bCopyAll)
		m_sForma_10L = pSet->m_sForma_10L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_11L) || bCopyAll)
		m_sForma_11L = pSet->m_sForma_11L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sForma_12L) || bCopyAll)
		m_sForma_12L = pSet->m_sForma_12L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_12R) || bCopyAll)
		m_sMargine_12R = pSet->m_sMargine_12R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_11R) || bCopyAll)
		m_sMargine_11R = pSet->m_sMargine_11R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_10R) || bCopyAll)
		m_sMargine_10R = pSet->m_sMargine_10R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_4R) || bCopyAll)
		m_sMargine_4R = pSet->m_sMargine_4R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_2R) || bCopyAll)
		m_sMargine_2R = pSet->m_sMargine_2R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_7) || bCopyAll)
		m_sMargine_7 = pSet->m_sMargine_7;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_2L) || bCopyAll)
		m_sMargine_2L = pSet->m_sMargine_2L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_4L) || bCopyAll)
		m_sMargine_4L = pSet->m_sMargine_4L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_10L) || bCopyAll)
		m_sMargine_10L = pSet->m_sMargine_10L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_11L) || bCopyAll)
		m_sMargine_11L = pSet->m_sMargine_11L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMargine_12L) || bCopyAll)
		m_sMargine_12L = pSet->m_sMargine_12L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_12R) || bCopyAll)
		m_sEcogenicita_12R = pSet->m_sEcogenicita_12R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_11R) || bCopyAll)
		m_sEcogenicita_11R = pSet->m_sEcogenicita_11R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_10R) || bCopyAll)
		m_sEcogenicita_10R = pSet->m_sEcogenicita_10R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_4R) || bCopyAll)
		m_sEcogenicita_4R = pSet->m_sEcogenicita_4R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_2R) || bCopyAll)
		m_sEcogenicita_2R = pSet->m_sEcogenicita_2R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_7) || bCopyAll)
		m_sEcogenicita_7 = pSet->m_sEcogenicita_7;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_2L) || bCopyAll)
		m_sEcogenicita_2L = pSet->m_sEcogenicita_2L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_4L) || bCopyAll)
		m_sEcogenicita_4L = pSet->m_sEcogenicita_4L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_10L) || bCopyAll)
		m_sEcogenicita_10L = pSet->m_sEcogenicita_10L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_11L) || bCopyAll)
		m_sEcogenicita_11L = pSet->m_sEcogenicita_11L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEcogenicita_12L) || bCopyAll)
		m_sEcogenicita_12L = pSet->m_sEcogenicita_12L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_12R) || bCopyAll)
		m_sFilo_12R = pSet->m_sFilo_12R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_11R) || bCopyAll)
		m_sFilo_11R = pSet->m_sFilo_11R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_10R) || bCopyAll)
		m_sFilo_10R = pSet->m_sFilo_10R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_4R) || bCopyAll)
		m_sFilo_4R = pSet->m_sFilo_4R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_2R) || bCopyAll)
		m_sFilo_2R = pSet->m_sFilo_2R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_7) || bCopyAll)
		m_sFilo_7 = pSet->m_sFilo_7;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_2L) || bCopyAll)
		m_sFilo_2L = pSet->m_sFilo_2L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_4L) || bCopyAll)
		m_sFilo_4L = pSet->m_sFilo_4L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_10L) || bCopyAll)
		m_sFilo_10L = pSet->m_sFilo_10L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_11L) || bCopyAll)
		m_sFilo_11L = pSet->m_sFilo_11L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFilo_12L) || bCopyAll)
		m_sFilo_12L = pSet->m_sFilo_12L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_12R) || bCopyAll)
		m_sNecrosi_12R = pSet->m_sNecrosi_12R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_11R) || bCopyAll)
		m_sNecrosi_11R = pSet->m_sNecrosi_11R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_10R) || bCopyAll)
		m_sNecrosi_10R = pSet->m_sNecrosi_10R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_4R) || bCopyAll)
		m_sNecrosi_4R = pSet->m_sNecrosi_4R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_2R) || bCopyAll)
		m_sNecrosi_2R = pSet->m_sNecrosi_2R;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_7) || bCopyAll)
		m_sNecrosi_7 = pSet->m_sNecrosi_7;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_2L) || bCopyAll)
		m_sNecrosi_2L = pSet->m_sNecrosi_2L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_4L) || bCopyAll)
		m_sNecrosi_4L = pSet->m_sNecrosi_4L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_10L) || bCopyAll)
		m_sNecrosi_10L = pSet->m_sNecrosi_10L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_11L) || bCopyAll)
		m_sNecrosi_11L = pSet->m_sNecrosi_11L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNecrosi_12L) || bCopyAll)
		m_sNecrosi_12L = pSet->m_sNecrosi_12L;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEbusSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEbusSet* pOV = (CEbusSet*)pOldValues;
	CEbusSet* pNV = (CEbusSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("Dimensione_12R", pOV, &pOV->m_sDimensione_12R, pNV, &pNV->m_sDimensione_12R);
	sp.Execute("Dimensione_11R", pOV, &pOV->m_sDimensione_11R, pNV, &pNV->m_sDimensione_11R);
	sp.Execute("Dimensione_10R", pOV, &pOV->m_sDimensione_10R, pNV, &pNV->m_sDimensione_10R);
	sp.Execute("Dimensione_4R", pOV, &pOV->m_sDimensione_4R, pNV, &pNV->m_sDimensione_4R);
	sp.Execute("Dimensione_2R", pOV, &pOV->m_sDimensione_2R, pNV, &pNV->m_sDimensione_2R);
	sp.Execute("Dimensione_7", pOV, &pOV->m_sDimensione_7, pNV, &pNV->m_sDimensione_7);
	sp.Execute("Dimensione_2L", pOV, &pOV->m_sDimensione_2L, pNV, &pNV->m_sDimensione_2L);
	sp.Execute("Dimensione_4L", pOV, &pOV->m_sDimensione_4L, pNV, &pNV->m_sDimensione_4L);
	sp.Execute("Dimensione_10L", pOV, &pOV->m_sDimensione_10L, pNV, &pNV->m_sDimensione_10L);
	sp.Execute("Dimensione_11L", pOV, &pOV->m_sDimensione_11L, pNV, &pNV->m_sDimensione_11L);
	sp.Execute("Dimensione_12L", pOV, &pOV->m_sDimensione_12L, pNV, &pNV->m_sDimensione_12L);
	sp.Execute("Puntura_12R", pOV, &pOV->m_sPuntura_12R, pNV, &pNV->m_sPuntura_12R);
	sp.Execute("Puntura_11R", pOV, &pOV->m_sPuntura_11R, pNV, &pNV->m_sPuntura_11R);
	sp.Execute("Puntura_10R", pOV, &pOV->m_sPuntura_10R, pNV, &pNV->m_sPuntura_10R);
	sp.Execute("Puntura_4R", pOV, &pOV->m_sPuntura_4R, pNV, &pNV->m_sPuntura_4R);
	sp.Execute("Puntura_2R", pOV, &pOV->m_sPuntura_2R, pNV, &pNV->m_sPuntura_2R);
	sp.Execute("Puntura_7", pOV, &pOV->m_sPuntura_7, pNV, &pNV->m_sPuntura_7);
	sp.Execute("Puntura_2L", pOV, &pOV->m_sPuntura_2L, pNV, &pNV->m_sPuntura_2L);
	sp.Execute("Puntura_4L", pOV, &pOV->m_sPuntura_4L, pNV, &pNV->m_sPuntura_4L);
	sp.Execute("Puntura_10L", pOV, &pOV->m_sPuntura_10L, pNV, &pNV->m_sPuntura_10L);
	sp.Execute("Puntura_11L", pOV, &pOV->m_sPuntura_11L, pNV, &pNV->m_sPuntura_11L);
	sp.Execute("Puntura_12L", pOV, &pOV->m_sPuntura_12L, pNV, &pNV->m_sPuntura_12L);
	sp.Execute("NumeroPunture_12R", pOV, &pOV->m_sNumeroPunture_12R, pNV, &pNV->m_sNumeroPunture_12R);
	sp.Execute("NumeroPunture_11R", pOV, &pOV->m_sNumeroPunture_11R, pNV, &pNV->m_sNumeroPunture_11R);
	sp.Execute("NumeroPunture_10R", pOV, &pOV->m_sNumeroPunture_10R, pNV, &pNV->m_sNumeroPunture_10R);
	sp.Execute("NumeroPunture_4R", pOV, &pOV->m_sNumeroPunture_4R, pNV, &pNV->m_sNumeroPunture_4R);
	sp.Execute("NumeroPunture_2R", pOV, &pOV->m_sNumeroPunture_2R, pNV, &pNV->m_sNumeroPunture_2R);
	sp.Execute("NumeroPunture_7", pOV, &pOV->m_sNumeroPunture_7, pNV, &pNV->m_sNumeroPunture_7);
	sp.Execute("NumeroPunture_2L", pOV, &pOV->m_sNumeroPunture_2L, pNV, &pNV->m_sNumeroPunture_2L);
	sp.Execute("NumeroPunture_4L", pOV, &pOV->m_sNumeroPunture_4L, pNV, &pNV->m_sNumeroPunture_4L);
	sp.Execute("NumeroPunture_10L", pOV, &pOV->m_sNumeroPunture_10L, pNV, &pNV->m_sNumeroPunture_10L);
	sp.Execute("NumeroPunture_11L", pOV, &pOV->m_sNumeroPunture_11L, pNV, &pNV->m_sNumeroPunture_11L);
	sp.Execute("NumeroPunture_12L", pOV, &pOV->m_sNumeroPunture_12L, pNV, &pNV->m_sNumeroPunture_12L);
	sp.Execute("Forma_12R", pOV, &pOV->m_sForma_12R, pNV, &pNV->m_sForma_12R);
	sp.Execute("Forma_11R", pOV, &pOV->m_sForma_11R, pNV, &pNV->m_sForma_11R);
	sp.Execute("Forma_10R", pOV, &pOV->m_sForma_10R, pNV, &pNV->m_sForma_10R);
	sp.Execute("Forma_4R", pOV, &pOV->m_sForma_4R, pNV, &pNV->m_sForma_4R);
	sp.Execute("Forma_2R", pOV, &pOV->m_sForma_2R, pNV, &pNV->m_sForma_2R);
	sp.Execute("Forma_7", pOV, &pOV->m_sForma_7, pNV, &pNV->m_sForma_7);
	sp.Execute("Forma_2L", pOV, &pOV->m_sForma_2L, pNV, &pNV->m_sForma_2L);
	sp.Execute("Forma_4L", pOV, &pOV->m_sForma_4L, pNV, &pNV->m_sForma_4L);
	sp.Execute("Forma_10L", pOV, &pOV->m_sForma_10L, pNV, &pNV->m_sForma_10L);
	sp.Execute("Forma_11L", pOV, &pOV->m_sForma_11L, pNV, &pNV->m_sForma_11L);
	sp.Execute("Forma_12L", pOV, &pOV->m_sForma_12L, pNV, &pNV->m_sForma_12L);
	sp.Execute("Margine_12R", pOV, &pOV->m_sMargine_12R, pNV, &pNV->m_sMargine_12R);
	sp.Execute("Margine_11R", pOV, &pOV->m_sMargine_11R, pNV, &pNV->m_sMargine_11R);
	sp.Execute("Margine_10R", pOV, &pOV->m_sMargine_10R, pNV, &pNV->m_sMargine_10R);
	sp.Execute("Margine_4R", pOV, &pOV->m_sMargine_4R, pNV, &pNV->m_sMargine_4R);
	sp.Execute("Margine_2R", pOV, &pOV->m_sMargine_2R, pNV, &pNV->m_sMargine_2R);
	sp.Execute("Margine_7", pOV, &pOV->m_sMargine_7, pNV, &pNV->m_sMargine_7);
	sp.Execute("Margine_2L", pOV, &pOV->m_sMargine_2L, pNV, &pNV->m_sMargine_2L);
	sp.Execute("Margine_4L", pOV, &pOV->m_sMargine_4L, pNV, &pNV->m_sMargine_4L);
	sp.Execute("Margine_10L", pOV, &pOV->m_sMargine_10L, pNV, &pNV->m_sMargine_10L);
	sp.Execute("Margine_11L", pOV, &pOV->m_sMargine_11L, pNV, &pNV->m_sMargine_11L);
	sp.Execute("Margine_12L", pOV, &pOV->m_sMargine_12L, pNV, &pNV->m_sMargine_12L);
	sp.Execute("Ecogenicita_12R", pOV, &pOV->m_sEcogenicita_12R, pNV, &pNV->m_sEcogenicita_12R);
	sp.Execute("Ecogenicita_11R", pOV, &pOV->m_sEcogenicita_11R, pNV, &pNV->m_sEcogenicita_11R);
	sp.Execute("Ecogenicita_10R", pOV, &pOV->m_sEcogenicita_10R, pNV, &pNV->m_sEcogenicita_10R);
	sp.Execute("Ecogenicita_4R", pOV, &pOV->m_sEcogenicita_4R, pNV, &pNV->m_sEcogenicita_4R);
	sp.Execute("Ecogenicita_2R", pOV, &pOV->m_sEcogenicita_2R, pNV, &pNV->m_sEcogenicita_2R);
	sp.Execute("Ecogenicita_7", pOV, &pOV->m_sEcogenicita_7, pNV, &pNV->m_sEcogenicita_7);
	sp.Execute("Ecogenicita_2L", pOV, &pOV->m_sEcogenicita_2L, pNV, &pNV->m_sEcogenicita_2L);
	sp.Execute("Ecogenicita_4L", pOV, &pOV->m_sEcogenicita_4L, pNV, &pNV->m_sEcogenicita_4L);
	sp.Execute("Ecogenicita_10L", pOV, &pOV->m_sEcogenicita_10L, pNV, &pNV->m_sEcogenicita_10L);
	sp.Execute("Ecogenicita_11L", pOV, &pOV->m_sEcogenicita_11L, pNV, &pNV->m_sEcogenicita_11L);
	sp.Execute("Ecogenicita_12L", pOV, &pOV->m_sEcogenicita_12L, pNV, &pNV->m_sEcogenicita_12L);
	sp.Execute("Filo_12R", pOV, &pOV->m_sFilo_12R, pNV, &pNV->m_sFilo_12R);
	sp.Execute("Filo_11R", pOV, &pOV->m_sFilo_11R, pNV, &pNV->m_sFilo_11R);
	sp.Execute("Filo_10R", pOV, &pOV->m_sFilo_10R, pNV, &pNV->m_sFilo_10R);
	sp.Execute("Filo_4R", pOV, &pOV->m_sFilo_4R, pNV, &pNV->m_sFilo_4R);
	sp.Execute("Filo_2R", pOV, &pOV->m_sFilo_2R, pNV, &pNV->m_sFilo_2R);
	sp.Execute("Filo_7", pOV, &pOV->m_sFilo_7, pNV, &pNV->m_sFilo_7);
	sp.Execute("Filo_2L", pOV, &pOV->m_sFilo_2L, pNV, &pNV->m_sFilo_2L);
	sp.Execute("Filo_4L", pOV, &pOV->m_sFilo_4L, pNV, &pNV->m_sFilo_4L);
	sp.Execute("Filo_10L", pOV, &pOV->m_sFilo_10L, pNV, &pNV->m_sFilo_10L);
	sp.Execute("Filo_11L", pOV, &pOV->m_sFilo_11L, pNV, &pNV->m_sFilo_11L);
	sp.Execute("Filo_12L", pOV, &pOV->m_sFilo_12L, pNV, &pNV->m_sFilo_12L);
	sp.Execute("Necrosi_12R", pOV, &pOV->m_sNecrosi_12R, pNV, &pNV->m_sNecrosi_12R);
	sp.Execute("Necrosi_11R", pOV, &pOV->m_sNecrosi_11R, pNV, &pNV->m_sNecrosi_11R);
	sp.Execute("Necrosi_10R", pOV, &pOV->m_sNecrosi_10R, pNV, &pNV->m_sNecrosi_10R);
	sp.Execute("Necrosi_4R", pOV, &pOV->m_sNecrosi_4R, pNV, &pNV->m_sNecrosi_4R);
	sp.Execute("Necrosi_2R", pOV, &pOV->m_sNecrosi_2R, pNV, &pNV->m_sNecrosi_2R);
	sp.Execute("Necrosi_7", pOV, &pOV->m_sNecrosi_7, pNV, &pNV->m_sNecrosi_7);
	sp.Execute("Necrosi_2L", pOV, &pOV->m_sNecrosi_2L, pNV, &pNV->m_sNecrosi_2L);
	sp.Execute("Necrosi_4L", pOV, &pOV->m_sNecrosi_4L, pNV, &pNV->m_sNecrosi_4L);
	sp.Execute("Necrosi_10L", pOV, &pOV->m_sNecrosi_10L, pNV, &pNV->m_sNecrosi_10L);
	sp.Execute("Necrosi_11L", pOV, &pOV->m_sNecrosi_11L, pNV, &pNV->m_sNecrosi_11L);
	sp.Execute("Necrosi_12L", pOV, &pOV->m_sNecrosi_12L, pNV, &pNV->m_sNecrosi_12L);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEbusSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEbusSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEbusSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEbusSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}