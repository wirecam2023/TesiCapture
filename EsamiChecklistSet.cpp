#include "stdafx.h"
#include "Endox.h"
#include "EsamiChecklistSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiChecklistSet, CBaseSet)

CEsamiChecklistSet::CEsamiChecklistSet()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 4;
	SetBaseFilter("");
}

CString CEsamiChecklistSet::GetDefaultSQL()
{
	return "ESAMICHECKLIST";
}

void CEsamiChecklistSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID",	m_lID);
	if(m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDCheck", m_lIDCheck);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CEsamiChecklistSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDCheck = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CEsamiChecklistSet::CreateNew()
{
	return (CBaseSet*)new CEsamiChecklistSet;
}

void CEsamiChecklistSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiChecklistSet* pSet = (CEsamiChecklistSet*)pOriginalSet;

	if(!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if(!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDCheck) || bCopyAll)
		m_lIDCheck = pSet->m_lIDCheck;
	if(!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEsamiChecklistSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiChecklistSet* pOV = (CEsamiChecklistSet*)pOldValues;
	CEsamiChecklistSet* pNV = (CEsamiChecklistSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDCheck", pOV, &pOV->m_lIDCheck, pNV, &pNV->m_lIDCheck);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEsamiChecklistSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if(EditRecordset("CEsamiChecklistSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEsamiChecklistSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEsamiChecklistSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if(strNewFilter.IsEmpty() == TRUE)
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if(strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}