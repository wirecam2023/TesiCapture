#include "stdafx.h"
#include "Endox.h"
#include "CodificaRegionaleGruppiItemsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCodificaRegionaleGruppiItemsSet, CBaseSet)

CCodificaRegionaleGruppiItemsSet::CCodificaRegionaleGruppiItemsSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CCodificaRegionaleGruppiItemsSet::GetDefaultSQL()
{
	return "ECodificaRegionaleGruppiItems";
}

void CCodificaRegionaleGruppiItemsSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDGruppo", m_lIDGruppo);
		RFX_Long(pFX, "IDProcedura", m_lIDProcedura);
		RFX_Long(pFX, "Quantita", m_lQuantita);
		RFX_Text(pFX, "TestoLibero", m_sTestoLibero, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CCodificaRegionaleGruppiItemsSet::SetEmpty()
{
	m_lID = 0;
	m_lIDGruppo = 0;
	m_lIDProcedura = 0;
	m_lQuantita = 1;
	m_sTestoLibero = "";
	m_bEliminato = 0;
}

CBaseSet* CCodificaRegionaleGruppiItemsSet::CreateNew()
{
	return (CBaseSet*)new CCodificaRegionaleGruppiItemsSet;
}

void CCodificaRegionaleGruppiItemsSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCodificaRegionaleGruppiItemsSet* pSet = (CCodificaRegionaleGruppiItemsSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = pSet->m_lIDGruppo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDProcedura) || bCopyAll)
		m_lIDProcedura = pSet->m_lIDProcedura;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lQuantita) || bCopyAll)
		m_lQuantita = pSet->m_lQuantita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoLibero) || bCopyAll)
		m_sTestoLibero = pSet->m_sTestoLibero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCodificaRegionaleGruppiItemsSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCodificaRegionaleGruppiItemsSet* pOV = (CCodificaRegionaleGruppiItemsSet*)pOldValues;
	CCodificaRegionaleGruppiItemsSet* pNV = (CCodificaRegionaleGruppiItemsSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDGruppo", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);
	sp.Execute("IDProcedura", pOV, &pOV->m_lIDProcedura, pNV, &pNV->m_lIDProcedura);
	sp.Execute("Quantita", pOV, &pOV->m_lQuantita, pNV, &pNV->m_lQuantita);
	sp.Execute("TestoLibero", pOV, &pOV->m_sTestoLibero, pNV, &pNV->m_sTestoLibero);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCodificaRegionaleGruppiItemsSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCodificaRegionaleGruppiItemsSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCodificaRegionaleGruppiItemsSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCodificaRegionaleGruppiItemsSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty() == TRUE)
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

long CCodificaRegionaleGruppiItemsSet::GetIDProcedura(long lID)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCodificaRegionaleGruppiItemsSet::GetIDProcedura"))
	{
		if (!IsEOF())
			lReturn = m_lIDProcedura;

		CloseRecordset("CCodificaRegionaleGruppiItemsSet::GetIDProcedura");
	}

	return lReturn;
}