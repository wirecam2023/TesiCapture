#include "stdafx.h"
#include "Endox.h"
#include "CheckListEsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCheckListEsamiSet, CBaseSet)

CCheckListEsamiSet::CCheckListEsamiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 4;
	SetBaseFilter("");
}

CString CCheckListEsamiSet::GetDefaultSQL()
{
	return "CheckListEsami";
}

void CCheckListEsamiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDCheckList", m_lIDCheckList);
		RFX_Long(pFX, "IDTipoEsame", m_lIDTipoEsame);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CCheckListEsamiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDCheckList = 0;
	m_lIDTipoEsame = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CCheckListEsamiSet::CreateNew()
{
	CCheckListEsamiSet* pNewSet = new CCheckListEsamiSet;

	return (CBaseSet*)pNewSet;
}

void CCheckListEsamiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCheckListEsamiSet* pSet = (CCheckListEsamiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDCheckList) || bCopyAll)
		m_lIDCheckList = pSet->m_lIDCheckList;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCheckListEsamiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCheckListEsamiSet* pOV = (CCheckListEsamiSet*)pOldValues;
	CCheckListEsamiSet* pNV = (CCheckListEsamiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDCheckList", pOV, &pOV->m_lIDCheckList, pNV, &pNV->m_lIDCheckList);
	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCheckListEsamiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCheckListEsamiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCheckListEsamiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCheckListEsamiSet::SetBaseFilter(const CString &strFilter)
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