#include "stdafx.h"
#include "Endox.h"
#include "TabellaParametriSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTabellaParametriSet, CBaseSet)

CTabellaParametriSet::CTabellaParametriSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 35;
}

CString CTabellaParametriSet::GetDefaultSQL()
{
	return "TabellaParametri";
}

void CTabellaParametriSet::SetEmpty()
{
	m_lID = 0;
	m_lIDStruttura = 0;
	m_lOrdine = 0;
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
	m_bEliminato = FALSE;
}

void CTabellaParametriSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDStruttura", m_lIDStruttura);
		RFX_Long(pFX, "Ordine", m_lOrdine);
		RFX_Text(pFX, "Parametro", m_sParametro, 50);
		RFX_Text(pFX, "Formula", m_sFormula, 4000);
		RFX_Long(pFX, "Decimali", m_lDecimali);
		RFX_Text(pFX, "UnitaDiMisura", m_sUnitaDiMisura, 50);
		RFX_Text(pFX, "RiferimentoM", m_sRiferimentoM, 50);
		RFX_Single(pFX, "RiferimentoMmin", m_fRiferimentoMmin);
		RFX_Single(pFX, "RiferimentoMmax", m_fRiferimentoMmax);
		RFX_Text(pFX, "RiferimentoF", m_sRiferimentoF, 50);
		RFX_Single(pFX, "RiferimentoFmin", m_fRiferimentoFmin);
		RFX_Single(pFX, "RiferimentoFmax", m_fRiferimentoFmax);
		RFX_Text(pFX, "RiferimentoPed00", m_sRiferimentoPed00, 50);
		RFX_Single(pFX, "RiferimentoPed00min", m_fRiferimentoPed00min);
		RFX_Single(pFX, "RiferimentoPed00max", m_fRiferimentoPed00max);
		RFX_Text(pFX, "RiferimentoPed01", m_sRiferimentoPed01, 50);
		RFX_Single(pFX, "RiferimentoPed01min", m_fRiferimentoPed01min);
		RFX_Single(pFX, "RiferimentoPed01max", m_fRiferimentoPed01max);
		RFX_Text(pFX, "RiferimentoPed02", m_sRiferimentoPed02, 50);
		RFX_Single(pFX, "RiferimentoPed02min", m_fRiferimentoPed02min);
		RFX_Single(pFX, "RiferimentoPed02max", m_fRiferimentoPed02max);
		RFX_Text(pFX, "RiferimentoPed03", m_sRiferimentoPed03, 50);
		RFX_Single(pFX, "RiferimentoPed03min", m_fRiferimentoPed03min);
		RFX_Single(pFX, "RiferimentoPed03max", m_fRiferimentoPed03max);
		RFX_Text(pFX, "RiferimentoPed04", m_sRiferimentoPed04, 50);
		RFX_Single(pFX, "RiferimentoPed04min", m_fRiferimentoPed04min);
		RFX_Single(pFX, "RiferimentoPed04max", m_fRiferimentoPed04max);
		RFX_Text(pFX, "RiferimentoPed05", m_sRiferimentoPed05, 50);
		RFX_Single(pFX, "RiferimentoPed05min", m_fRiferimentoPed05min);
		RFX_Single(pFX, "RiferimentoPed05max", m_fRiferimentoPed05max);
		RFX_Text(pFX, "RiferimentoPed06", m_sRiferimentoPed06, 50);
		RFX_Single(pFX, "RiferimentoPed06min", m_fRiferimentoPed06min);
		RFX_Single(pFX, "RiferimentoPed06max", m_fRiferimentoPed06max);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CTabellaParametriSet::CreateNew()
{
	return (CBaseSet*)new CTabellaParametriSet;
}

void CTabellaParametriSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTabellaParametriSet* pSet = (CTabellaParametriSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDStruttura) || bCopyAll)
		m_lIDStruttura = pSet->m_lIDStruttura;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sParametro) || bCopyAll)
		m_sParametro = pSet->m_sParametro;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFormula) || bCopyAll)
		m_sFormula = pSet->m_sFormula;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDecimali) || bCopyAll)
		m_lDecimali = pSet->m_lDecimali;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUnitaDiMisura) || bCopyAll)
		m_sUnitaDiMisura = pSet->m_sUnitaDiMisura;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRiferimentoM) || bCopyAll)
		m_sRiferimentoM = pSet->m_sRiferimentoM;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoMmin) || bCopyAll)
		m_fRiferimentoMmin = pSet->m_fRiferimentoMmin;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoMmax) || bCopyAll)
		m_fRiferimentoMmax = pSet->m_fRiferimentoMmax;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRiferimentoF) || bCopyAll)
		m_sRiferimentoF = pSet->m_sRiferimentoF;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoFmin) || bCopyAll)
		m_fRiferimentoFmin = pSet->m_fRiferimentoFmin;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoFmax) || bCopyAll)
		m_fRiferimentoFmax = pSet->m_fRiferimentoFmax;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRiferimentoPed00) || bCopyAll)
		m_sRiferimentoPed00 = pSet->m_sRiferimentoPed00;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed00min) || bCopyAll)
		m_fRiferimentoPed00min = pSet->m_fRiferimentoPed00min;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed00max) || bCopyAll)
		m_fRiferimentoPed00max = pSet->m_fRiferimentoPed00max;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRiferimentoPed01) || bCopyAll)
		m_sRiferimentoPed01 = pSet->m_sRiferimentoPed01;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed01min) || bCopyAll)
		m_fRiferimentoPed01min = pSet->m_fRiferimentoPed01min;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed01max) || bCopyAll)
		m_fRiferimentoPed01max = pSet->m_fRiferimentoPed01max;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRiferimentoPed02) || bCopyAll)
		m_sRiferimentoPed02 = pSet->m_sRiferimentoPed02;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed02min) || bCopyAll)
		m_fRiferimentoPed02min = pSet->m_fRiferimentoPed02min;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed02max) || bCopyAll)
		m_fRiferimentoPed02max = pSet->m_fRiferimentoPed02max;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRiferimentoPed03) || bCopyAll)
		m_sRiferimentoPed03 = pSet->m_sRiferimentoPed03;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed03min) || bCopyAll)
		m_fRiferimentoPed03min = pSet->m_fRiferimentoPed03min;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed03max) || bCopyAll)
		m_fRiferimentoPed03max = pSet->m_fRiferimentoPed03max;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRiferimentoPed04) || bCopyAll)
		m_sRiferimentoPed04 = pSet->m_sRiferimentoPed04;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed04min) || bCopyAll)
		m_fRiferimentoPed04min = pSet->m_fRiferimentoPed04min;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed04max) || bCopyAll)
		m_fRiferimentoPed04max = pSet->m_fRiferimentoPed04max;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRiferimentoPed05) || bCopyAll)
		m_sRiferimentoPed05 = pSet->m_sRiferimentoPed05;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed05min) || bCopyAll)
		m_fRiferimentoPed05min = pSet->m_fRiferimentoPed05min;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed05max) || bCopyAll)
		m_fRiferimentoPed05max = pSet->m_fRiferimentoPed05max;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRiferimentoPed06) || bCopyAll)
		m_sRiferimentoPed06 = pSet->m_sRiferimentoPed06;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed06min) || bCopyAll)
		m_fRiferimentoPed06min = pSet->m_fRiferimentoPed06min;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fRiferimentoPed06max) || bCopyAll)
		m_fRiferimentoPed06max = pSet->m_fRiferimentoPed06max;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

BOOL CTabellaParametriSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTabellaParametriSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTabellaParametriSet::DeleteRecordset");
	}
	return bReturn;
}

CString CTabellaParametriSet::SetBaseFilter(const CString &strFilter)
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

void CTabellaParametriSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTabellaParametriSet* pOV = (CTabellaParametriSet*)pOldValues;
	CTabellaParametriSet* pNV = (CTabellaParametriSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDStruttura", pOV, &pOV->m_lIDStruttura, pNV, &pNV->m_lIDStruttura);
	sp.Execute("lOrdine", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("Parametro", pOV, &pOV->m_sParametro, pNV, &pNV->m_sParametro);
	sp.Execute("Formula", pOV, &pOV->m_sFormula, pNV, &pNV->m_sFormula);
	sp.Execute("Decimali", pOV, &pOV->m_lDecimali, pNV, &pNV->m_lDecimali);
	sp.Execute("UnitaDiMisura", pOV, &pOV->m_sUnitaDiMisura, pNV, &pNV->m_sUnitaDiMisura);
	sp.Execute("RiferimentoM", pOV, &pOV->m_sRiferimentoM, pNV, &pNV->m_sRiferimentoM);
	sp.Execute("RiferimentoMmin", pOV, &pOV->m_fRiferimentoMmin, pNV, &pNV->m_fRiferimentoMmin);
	sp.Execute("RiferimentoMmax", pOV, &pOV->m_fRiferimentoMmax, pNV, &pNV->m_fRiferimentoMmax);
	sp.Execute("RiferimentoF", pOV, &pOV->m_sRiferimentoF, pNV, &pNV->m_sRiferimentoF);
	sp.Execute("RiferimentoFmin", pOV, &pOV->m_fRiferimentoFmin, pNV, &pNV->m_fRiferimentoFmin);
	sp.Execute("RiferimentoFmax", pOV, &pOV->m_fRiferimentoFmax, pNV, &pNV->m_fRiferimentoFmax);
	sp.Execute("RiferimentoPed00", pOV, &pOV->m_sRiferimentoPed00, pNV, &pNV->m_sRiferimentoPed00);
	sp.Execute("RiferimentoPed00min", pOV, &pOV->m_fRiferimentoPed00min, pNV, &pNV->m_fRiferimentoPed00min);
	sp.Execute("RiferimentoPed00max", pOV, &pOV->m_fRiferimentoPed00max, pNV, &pNV->m_fRiferimentoPed00max);
	sp.Execute("RiferimentoPed01", pOV, &pOV->m_sRiferimentoPed01, pNV, &pNV->m_sRiferimentoPed01);
	sp.Execute("RiferimentoPed01min", pOV, &pOV->m_fRiferimentoPed01min, pNV, &pNV->m_fRiferimentoPed01min);
	sp.Execute("RiferimentoPed01max", pOV, &pOV->m_fRiferimentoPed01max, pNV, &pNV->m_fRiferimentoPed01max);
	sp.Execute("RiferimentoPed02", pOV, &pOV->m_sRiferimentoPed02, pNV, &pNV->m_sRiferimentoPed02);
	sp.Execute("RiferimentoPed02min", pOV, &pOV->m_fRiferimentoPed02min, pNV, &pNV->m_fRiferimentoPed02min);
	sp.Execute("RiferimentoPed02max", pOV, &pOV->m_fRiferimentoPed02max, pNV, &pNV->m_fRiferimentoPed02max);
	sp.Execute("RiferimentoPed03", pOV, &pOV->m_sRiferimentoPed03, pNV, &pNV->m_sRiferimentoPed03);
	sp.Execute("RiferimentoPed03min", pOV, &pOV->m_fRiferimentoPed03min, pNV, &pNV->m_fRiferimentoPed03min);
	sp.Execute("RiferimentoPed03max", pOV, &pOV->m_fRiferimentoPed03max, pNV, &pNV->m_fRiferimentoPed03max);
	sp.Execute("RiferimentoPed04", pOV, &pOV->m_sRiferimentoPed04, pNV, &pNV->m_sRiferimentoPed04);
	sp.Execute("RiferimentoPed04min", pOV, &pOV->m_fRiferimentoPed04min, pNV, &pNV->m_fRiferimentoPed04min);
	sp.Execute("RiferimentoPed04max", pOV, &pOV->m_fRiferimentoPed04max, pNV, &pNV->m_fRiferimentoPed04max);
	sp.Execute("RiferimentoPed05", pOV, &pOV->m_sRiferimentoPed05, pNV, &pNV->m_sRiferimentoPed05);
	sp.Execute("RiferimentoPed05min", pOV, &pOV->m_fRiferimentoPed05min, pNV, &pNV->m_fRiferimentoPed05min);
	sp.Execute("RiferimentoPed05max", pOV, &pOV->m_fRiferimentoPed05max, pNV, &pNV->m_fRiferimentoPed05max);
	sp.Execute("RiferimentoPed06", pOV, &pOV->m_sRiferimentoPed06, pNV, &pNV->m_sRiferimentoPed06);
	sp.Execute("RiferimentoPed06min", pOV, &pOV->m_fRiferimentoPed06min, pNV, &pNV->m_fRiferimentoPed06min);
	sp.Execute("RiferimentoPed06max", pOV, &pOV->m_fRiferimentoPed06max, pNV, &pNV->m_fRiferimentoPed06max);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

long CTabellaParametriSet::FleuryTrans(long lIDStruttura, CString sParametro)
{
	long lReturn = 0;

	sParametro.Trim();
	sParametro.Replace("'", "''");

	if ((lIDStruttura > 0) && (!sParametro.IsEmpty()))
	{
		CString sFilter;
		sFilter.Format("IDSTRUTTURA = %li AND PARAMETRO = '%s'", lIDStruttura, sParametro);
		SetOpenFilter(sFilter);
		if (OpenRecordset("CTabellaParametriSet::FleuryTrans"))
		{
			if (!IsEOF())
				lReturn = m_lID;

			CloseRecordset("CTabellaParametriSet::FleuryTrans");
		}
	}

	return lReturn;
}