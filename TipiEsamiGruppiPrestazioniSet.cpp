#include "stdafx.h"
#include "Endox.h"
#include "TipiEsamiGruppiPrestazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiEsamiGruppiPrestazioniSet, CBaseSet)

CTipiEsamiGruppiPrestazioniSet::CTipiEsamiGruppiPrestazioniSet()
	: CBaseSet(&m_lID, "ID")
{
	m_lID = 0;
	m_lTipoEsame	= 0;
	m_lGruppo		= 0;
	m_bEliminato = FALSE;

	m_nFields = 4;
	SetBaseFilter("");
}

CString CTipiEsamiGruppiPrestazioniSet::GetDefaultSQL()
{
	return "TIPIESAMIGRUPPIPRESTAZIONI";
}

void CTipiEsamiGruppiPrestazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "TipoEsame",	m_lTipoEsame);
		RFX_Long (pFX, "Gruppo", m_lGruppo);
		RFX_Bool (pFX, "Eliminato", m_bEliminato);
	}
}

void CTipiEsamiGruppiPrestazioniSet::SetEmpty()
{
	m_lID = 0;
	m_lTipoEsame = 0;
	m_lGruppo	= 0;
	m_bEliminato = FALSE;
}

CBaseSet* CTipiEsamiGruppiPrestazioniSet::CreateNew()
{
	return (CBaseSet*)new CTipiEsamiGruppiPrestazioniSet;
}

void CTipiEsamiGruppiPrestazioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiEsamiGruppiPrestazioniSet* pTipiEsamiGruppiPrestazioniSet = (CTipiEsamiGruppiPrestazioniSet*)pOriginalSet;

	if (!pTipiEsamiGruppiPrestazioniSet->IsOpen() || pTipiEsamiGruppiPrestazioniSet->IsFieldDirty(&pTipiEsamiGruppiPrestazioniSet->m_lTipoEsame) || bCopyAll)
		m_lTipoEsame = pTipiEsamiGruppiPrestazioniSet->m_lTipoEsame;
	if (!pTipiEsamiGruppiPrestazioniSet->IsOpen() || pTipiEsamiGruppiPrestazioniSet->IsFieldDirty(&pTipiEsamiGruppiPrestazioniSet->m_lGruppo) || bCopyAll)
		m_lGruppo = pTipiEsamiGruppiPrestazioniSet->m_lGruppo;
	if (!pTipiEsamiGruppiPrestazioniSet->IsOpen() || pTipiEsamiGruppiPrestazioniSet->IsFieldDirty(&pTipiEsamiGruppiPrestazioniSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pTipiEsamiGruppiPrestazioniSet->m_bEliminato;
}

void CTipiEsamiGruppiPrestazioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiEsamiGruppiPrestazioniSet* pOV = (CTipiEsamiGruppiPrestazioniSet*)pOldValues;
	CTipiEsamiGruppiPrestazioniSet* pNV = (CTipiEsamiGruppiPrestazioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("TipoEsame", pOV, &pOV->m_lTipoEsame, pNV, &pNV->m_lTipoEsame);
	sp.Execute("Gruppo", pOV, &pOV->m_lGruppo, pNV, &pNV->m_lGruppo);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiEsamiGruppiPrestazioniSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTipiEsamiGruppiPrestazioniSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTipiEsamiGruppiPrestazioniSet::DeleteRecordset");
	}
	return bReturn;
}

CString CTipiEsamiGruppiPrestazioniSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
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