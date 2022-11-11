#include "stdafx.h"
#include "Endox.h"
#include "TipiEsamiDiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiEsamiDiagnosiICD9Set, CBaseSet)

CTipiEsamiDiagnosiICD9Set::CTipiEsamiDiagnosiICD9Set()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CTipiEsamiDiagnosiICD9Set::GetDefaultSQL()
{
	return "TIPIESAMIDIAGNOSIICD9";
}

void CTipiEsamiDiagnosiICD9Set::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "IDTipoEsame", m_lIDTipoEsame);
		RFX_Long (pFX, "IDDiagnosi", m_lIDDiagnosi);
		RFX_Bool (pFX, "Eliminato", m_bEliminato);
	}
}

void CTipiEsamiDiagnosiICD9Set::SetEmpty()
{
	m_lID = 0;
	m_lIDTipoEsame = 0;
	m_lIDDiagnosi = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CTipiEsamiDiagnosiICD9Set::CreateNew()
{
	return (CBaseSet*)new CTipiEsamiDiagnosiICD9Set;
}

void CTipiEsamiDiagnosiICD9Set::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiEsamiDiagnosiICD9Set* pSet = (CTipiEsamiDiagnosiICD9Set*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDDiagnosi) || bCopyAll)
		m_lIDDiagnosi = pSet->m_lIDDiagnosi;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CTipiEsamiDiagnosiICD9Set::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiEsamiDiagnosiICD9Set* pOV = (CTipiEsamiDiagnosiICD9Set*)pOldValues;
	CTipiEsamiDiagnosiICD9Set* pNV = (CTipiEsamiDiagnosiICD9Set*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("IDDiagnosi", pOV, &pOV->m_lIDDiagnosi, pNV, &pNV->m_lIDDiagnosi);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiEsamiDiagnosiICD9Set::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTipiEsamiDiagnosiICD9Set::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTipiEsamiDiagnosiICD9Set::DeleteRecordset");
	}
	return bReturn;
}

CString CTipiEsamiDiagnosiICD9Set::SetBaseFilter(const CString &strFilter)
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