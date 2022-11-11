#include "stdafx.h"
#include "Endox.h"
#include "VistaTabellaStruttureParametriSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaTabellaStruttureParametriSet, CBaseSet)

CVistaTabellaStruttureParametriSet::CVistaTabellaStruttureParametriSet()
: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();

	m_nFields = 35;
}

CString CVistaTabellaStruttureParametriSet::GetDefaultSQL()
{
	return "VistaTabellaStruttureParametri";
}

void CVistaTabellaStruttureParametriSet::SetEmpty()
{
	m_lIDTipoEsame = 0;
	m_lIDStruttura = 0;
	m_sStruttura = "";
	m_lIDParametro = 0;
	m_sParametro = "";
	m_sFormula = "";
	m_lDecimali = 0;
	m_sUnitaDiMisura = "";
	m_sRiferimentoM = "";
	m_fRiferimentoMmin = 0;
	m_fRiferimentoMmax = 0;
	m_sRiferimentoF = "";
	m_fRiferimentoFmin = 0;
	m_fRiferimentoFmax = 0;
	m_sRiferimentoPed00 = "";
	m_fRiferimentoPed00min = 0;
	m_fRiferimentoPed00max = 0;
	m_sRiferimentoPed01 = "";
	m_fRiferimentoPed01min = 0;
	m_fRiferimentoPed01max = 0;
	m_sRiferimentoPed02 = "";
	m_fRiferimentoPed02min = 0;
	m_fRiferimentoPed02max = 0;
	m_sRiferimentoPed03 = "";
	m_fRiferimentoPed03min = 0;
	m_fRiferimentoPed03max = 0;
	m_sRiferimentoPed04 = "";
	m_fRiferimentoPed04min = 0;
	m_fRiferimentoPed04max = 0;
	m_sRiferimentoPed05 = "";
	m_fRiferimentoPed05min = 0;
	m_fRiferimentoPed05max = 0;
	m_sRiferimentoPed06 = "";
	m_fRiferimentoPed06min = 0;
	m_fRiferimentoPed06max = 0;
}

void CVistaTabellaStruttureParametriSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDTipoEsame", m_lIDTipoEsame);
	RFX_Long(pFX, "IDStruttura", m_lIDStruttura);
	RFX_Text(pFX, "Struttura", m_sStruttura);
	RFX_Long(pFX, "IDParametro", m_lIDParametro);
	RFX_Text(pFX, "Parametro", m_sParametro);
	RFX_Text(pFX, "Formula", m_sFormula, 4000);
	RFX_Long(pFX, "Decimali", m_lDecimali);
	RFX_Text(pFX, "UnitaDiMisura", m_sUnitaDiMisura, 50);
	RFX_Text(pFX, "RiferimentoM", m_sRiferimentoM);
	RFX_Single(pFX, "RiferimentoMmin", m_fRiferimentoMmin);
	RFX_Single(pFX, "RiferimentoMmax", m_fRiferimentoMmax);
	RFX_Text(pFX, "RiferimentoF", m_sRiferimentoF);
	RFX_Single(pFX, "RiferimentoFmin", m_fRiferimentoFmin);
	RFX_Single(pFX, "RiferimentoFmax", m_fRiferimentoFmax);
	RFX_Text(pFX, "RiferimentoPed00", m_sRiferimentoPed00);
	RFX_Single(pFX, "RiferimentoPed00min", m_fRiferimentoPed00min);
	RFX_Single(pFX, "RiferimentoPed00max", m_fRiferimentoPed00max);
	RFX_Text(pFX, "RiferimentoPed01", m_sRiferimentoPed01);
	RFX_Single(pFX, "RiferimentoPed01min", m_fRiferimentoPed01min);
	RFX_Single(pFX, "RiferimentoPed01max", m_fRiferimentoPed01max);
	RFX_Text(pFX, "RiferimentoPed02", m_sRiferimentoPed02);
	RFX_Single(pFX, "RiferimentoPed02min", m_fRiferimentoPed02min);
	RFX_Single(pFX, "RiferimentoPed02max", m_fRiferimentoPed02max);
	RFX_Text(pFX, "RiferimentoPed03", m_sRiferimentoPed03);
	RFX_Single(pFX, "RiferimentoPed03min", m_fRiferimentoPed03min);
	RFX_Single(pFX, "RiferimentoPed03max", m_fRiferimentoPed03max);
	RFX_Text(pFX, "RiferimentoPed04", m_sRiferimentoPed04);
	RFX_Single(pFX, "RiferimentoPed04min", m_fRiferimentoPed04min);
	RFX_Single(pFX, "RiferimentoPed04max", m_fRiferimentoPed04max);
	RFX_Text(pFX, "RiferimentoPed05", m_sRiferimentoPed05);
	RFX_Single(pFX, "RiferimentoPed05min", m_fRiferimentoPed05min);
	RFX_Single(pFX, "RiferimentoPed05max", m_fRiferimentoPed05max);
	RFX_Text(pFX, "RiferimentoPed06", m_sRiferimentoPed06);
	RFX_Single(pFX, "RiferimentoPed06min", m_fRiferimentoPed06min);
	RFX_Single(pFX, "RiferimentoPed06max", m_fRiferimentoPed06max);
}