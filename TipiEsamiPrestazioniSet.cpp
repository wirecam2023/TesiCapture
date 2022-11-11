#include "stdafx.h"
#include "Endox.h"
#include "TipiEsamiPrestazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiEsamiPrestazioniSet, CBaseSet)

CTipiEsamiPrestazioniSet::CTipiEsamiPrestazioniSet()
	: CBaseSet(&m_lID, "ID")
{
	m_lID			= 0;
	m_lTipoEsame	= 0;
	m_lPrestazione	= 0;
	m_bEliminato    = FALSE;

	m_nFields = 4;
	SetBaseFilter("");
}

CString CTipiEsamiPrestazioniSet::GetDefaultSQL()
{
	return "TIPIESAMIPRESTAZIONI";
}

void CTipiEsamiPrestazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "TipoEsame",	m_lTipoEsame);
		RFX_Long (pFX, "Prestazione", m_lPrestazione);
		RFX_Bool (pFX, "Eliminato", m_bEliminato);
	}
}

void CTipiEsamiPrestazioniSet::SetEmpty()
{
	m_lID			= 0;
	m_lTipoEsame	= 0;
	m_lPrestazione	= 0;
	m_bEliminato    = FALSE;
}

CBaseSet* CTipiEsamiPrestazioniSet::CreateNew()
{
	return (CBaseSet*)new CTipiEsamiPrestazioniSet;
}

void CTipiEsamiPrestazioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiEsamiPrestazioniSet* pTipiEsamiPrestazioniSet = (CTipiEsamiPrestazioniSet*)pOriginalSet;

	if (!pTipiEsamiPrestazioniSet->IsOpen() || pTipiEsamiPrestazioniSet->IsFieldDirty(&pTipiEsamiPrestazioniSet->m_lTipoEsame) || bCopyAll)
		m_lTipoEsame = pTipiEsamiPrestazioniSet->m_lTipoEsame;
	if (!pTipiEsamiPrestazioniSet->IsOpen() || pTipiEsamiPrestazioniSet->IsFieldDirty(&pTipiEsamiPrestazioniSet->m_lPrestazione) || bCopyAll)
		m_lPrestazione = pTipiEsamiPrestazioniSet->m_lPrestazione;
	if (!pTipiEsamiPrestazioniSet->IsOpen() || pTipiEsamiPrestazioniSet->IsFieldDirty(&pTipiEsamiPrestazioniSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pTipiEsamiPrestazioniSet->m_bEliminato;
}

void CTipiEsamiPrestazioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiEsamiPrestazioniSet* pOV = (CTipiEsamiPrestazioniSet*)pOldValues;
	CTipiEsamiPrestazioniSet* pNV = (CTipiEsamiPrestazioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("TipoEsame", pOV, &pOV->m_lTipoEsame, pNV, &pNV->m_lTipoEsame);
	sp.Execute("Prestazione", pOV, &pOV->m_lPrestazione, pNV, &pNV->m_lPrestazione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiEsamiPrestazioniSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTipiEsamiPrestazioniSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTipiEsamiPrestazioniSet::DeleteRecordset");
	}
	return bReturn;
}

CString CTipiEsamiPrestazioniSet::SetBaseFilter(const CString &strFilter)
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