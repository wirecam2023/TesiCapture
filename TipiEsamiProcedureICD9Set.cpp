#include "stdafx.h"
#include "Endox.h"
#include "TipiEsamiProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiEsamiProcedureICD9Set, CBaseSet)

CTipiEsamiProcedureICD9Set::CTipiEsamiProcedureICD9Set()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CTipiEsamiProcedureICD9Set::GetDefaultSQL()
{
	return "TIPIESAMIPROCEDUREICD9";
}

void CTipiEsamiProcedureICD9Set::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "IDTipoEsame", m_lIDTipoEsame);
		RFX_Long (pFX, "IDProcedura", m_lIDProcedura);
		RFX_Bool (pFX, "Eliminato", m_bEliminato);
	}
}

void CTipiEsamiProcedureICD9Set::SetEmpty()
{
	m_lID = 0;
	m_lIDTipoEsame = 0;
	m_lIDProcedura = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CTipiEsamiProcedureICD9Set::CreateNew()
{
	return (CBaseSet*)new CTipiEsamiProcedureICD9Set;
}

void CTipiEsamiProcedureICD9Set::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiEsamiProcedureICD9Set* pSet = (CTipiEsamiProcedureICD9Set*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDProcedura) || bCopyAll)
		m_lIDProcedura = pSet->m_lIDProcedura;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CTipiEsamiProcedureICD9Set::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiEsamiProcedureICD9Set* pOV = (CTipiEsamiProcedureICD9Set*)pOldValues;
	CTipiEsamiProcedureICD9Set* pNV = (CTipiEsamiProcedureICD9Set*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("IDProcedura", pOV, &pOV->m_lIDProcedura, pNV, &pNV->m_lIDProcedura);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiEsamiProcedureICD9Set::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTipiEsamiProcedureICD9Set::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTipiEsamiProcedureICD9Set::DeleteRecordset");
	}
	return bReturn;
}

CString CTipiEsamiProcedureICD9Set::SetBaseFilter(const CString &strFilter)
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