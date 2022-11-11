#include "stdafx.h"
#include "Endox.h"
#include "TipiEsameGruppiDiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiEsameGruppiDiagnosiICD9Set, CBaseSet)

CTipiEsameGruppiDiagnosiICD9Set::CTipiEsameGruppiDiagnosiICD9Set()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CTipiEsameGruppiDiagnosiICD9Set::GetDefaultSQL()
{
	return "TIPIESAMIGRUPPIDIAGNOSIICD9";
}

void CTipiEsameGruppiDiagnosiICD9Set::DoFieldExchange(CFieldExchange* pFX)
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

void CTipiEsameGruppiDiagnosiICD9Set::SetEmpty()
{
	m_lID = 0;
	m_lIDTipoEsame = 0;
	m_lIDGruppo = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CTipiEsameGruppiDiagnosiICD9Set::CreateNew()
{
	return (CBaseSet*)new CTipiEsameGruppiDiagnosiICD9Set;
}

void CTipiEsameGruppiDiagnosiICD9Set::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiEsameGruppiDiagnosiICD9Set* pSet = (CTipiEsameGruppiDiagnosiICD9Set*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = pSet->m_lIDGruppo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CTipiEsameGruppiDiagnosiICD9Set::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiEsameGruppiDiagnosiICD9Set* pOV = (CTipiEsameGruppiDiagnosiICD9Set*)pOldValues;
	CTipiEsameGruppiDiagnosiICD9Set* pNV = (CTipiEsameGruppiDiagnosiICD9Set*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("IDGruppo", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiEsameGruppiDiagnosiICD9Set::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTipiEsameGruppiDiagnosiICD9Set::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTipiEsameGruppiDiagnosiICD9Set::DeleteRecordset");
	}
	return bReturn;
}

CString CTipiEsameGruppiDiagnosiICD9Set::SetBaseFilter(const CString &strFilter)
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