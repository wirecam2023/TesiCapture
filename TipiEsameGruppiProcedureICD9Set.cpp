#include "stdafx.h"
#include "Endox.h"
#include "TipiEsameGruppiProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiEsameGruppiProcedureICD9Set, CBaseSet)

CTipiEsameGruppiProcedureICD9Set::CTipiEsameGruppiProcedureICD9Set()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CTipiEsameGruppiProcedureICD9Set::GetDefaultSQL()
{
	return "TIPIESAMIGRUPPIPROCEDUREICD9";
}

void CTipiEsameGruppiProcedureICD9Set::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "IDTipoEsame", m_lIDTipoEsame);
		RFX_Long (pFX, "IDGruppo", m_lIDGruppo);
		RFX_Bool (pFX, "Eliminato", m_bEliminato);
	}
}

void CTipiEsameGruppiProcedureICD9Set::SetEmpty()
{
	m_lID = 0;
	m_lIDTipoEsame = 0;
	m_lIDGruppo = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CTipiEsameGruppiProcedureICD9Set::CreateNew()
{
	return (CBaseSet*)new CTipiEsameGruppiProcedureICD9Set;
}

void CTipiEsameGruppiProcedureICD9Set::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiEsameGruppiProcedureICD9Set* pSet = (CTipiEsameGruppiProcedureICD9Set*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = pSet->m_lIDGruppo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CTipiEsameGruppiProcedureICD9Set::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiEsameGruppiProcedureICD9Set* pOV = (CTipiEsameGruppiProcedureICD9Set*)pOldValues;
	CTipiEsameGruppiProcedureICD9Set* pNV = (CTipiEsameGruppiProcedureICD9Set*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("IDGruppo", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiEsameGruppiProcedureICD9Set::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTipiEsameGruppiProcedureICD9Set::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTipiEsameGruppiProcedureICD9Set::DeleteRecordset");
	}
	return bReturn;
}

CString CTipiEsameGruppiProcedureICD9Set::SetBaseFilter(const CString &strFilter)
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