#include "stdafx.h"
#include "Endox.h"
#include "TipiEsamiOrganiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiEsamiOrganiSet, CBaseSet)

CTipiEsamiOrganiSet::CTipiEsamiOrganiSet()
	: CBaseSet(&m_lID, "ID")
{
	m_lID			= 0;
	m_lTipoEsame	= 0;
	m_lOrgano		= 0;
	m_bEliminato    = FALSE;

	m_nFields = 4;
	SetBaseFilter("");
}

CString CTipiEsamiOrganiSet::GetDefaultSQL()
{
	return "ETIPIESAMIORGANI";
}

void CTipiEsamiOrganiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "TipoEsame",	m_lTipoEsame);
		RFX_Long (pFX, "Organo",	m_lOrgano);
		RFX_Bool (pFX, "Eliminato",	m_bEliminato);
	}
}

void CTipiEsamiOrganiSet::SetEmpty()
{
	m_lID			= 0;
	m_lTipoEsame	= 0;
	m_lOrgano		= 0;
	m_bEliminato    = FALSE;
}

CBaseSet* CTipiEsamiOrganiSet::CreateNew()
{
	return (CBaseSet*)new CTipiEsamiOrganiSet;
}

void CTipiEsamiOrganiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiEsamiOrganiSet* pTipiEsamiOrganiSet = (CTipiEsamiOrganiSet*)pOriginalSet;

	if (!pTipiEsamiOrganiSet->IsOpen() || pTipiEsamiOrganiSet->IsFieldDirty(&pTipiEsamiOrganiSet->m_lTipoEsame) || bCopyAll)
		m_lTipoEsame = pTipiEsamiOrganiSet->m_lTipoEsame;
	if (!pTipiEsamiOrganiSet->IsOpen() || pTipiEsamiOrganiSet->IsFieldDirty(&pTipiEsamiOrganiSet->m_lOrgano) || bCopyAll)
		m_lOrgano = pTipiEsamiOrganiSet->m_lOrgano;
	if (!pTipiEsamiOrganiSet->IsOpen() || pTipiEsamiOrganiSet->IsFieldDirty(&pTipiEsamiOrganiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pTipiEsamiOrganiSet->m_bEliminato;
}

void CTipiEsamiOrganiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiEsamiOrganiSet* pOV = (CTipiEsamiOrganiSet*)pOldValues;
	CTipiEsamiOrganiSet* pNV = (CTipiEsamiOrganiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("TipoEsame", pOV, &pOV->m_lTipoEsame, pNV, &pNV->m_lTipoEsame);
	sp.Execute("Organo", pOV, &pOV->m_lOrgano, pNV, &pNV->m_lOrgano);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiEsamiOrganiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTipiEsamiOrganiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTipiEsamiOrganiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CTipiEsamiOrganiSet::SetBaseFilter(const CString &strFilter)
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