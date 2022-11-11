#include "stdafx.h"
#include "Endox.h"
#include "CheckListCheckedElementSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCheckListCheckedElementSet, CBaseSet)

CCheckListCheckedElementSet::CCheckListCheckedElementSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CCheckListCheckedElementSet::GetDefaultSQL()
{
	return "CheckListCheckedElement";
}

void CCheckListCheckedElementSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDItem", m_lIDItem);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CCheckListCheckedElementSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDItem = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CCheckListCheckedElementSet::CreateNew()
{
	CCheckListCheckedElementSet* pNewSet = new CCheckListCheckedElementSet;

	return (CBaseSet*)pNewSet;
}

void CCheckListCheckedElementSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCheckListCheckedElementSet* pSet = (CCheckListCheckedElementSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDItem) || bCopyAll)
		m_lIDItem = pSet->m_lIDItem;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCheckListCheckedElementSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCheckListCheckedElementSet* pOV = (CCheckListCheckedElementSet*)pOldValues;
	CCheckListCheckedElementSet* pNV = (CCheckListCheckedElementSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDItem", pOV, &pOV->m_lIDItem, pNV, &pNV->m_lIDItem);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCheckListCheckedElementSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCheckListCheckedElementSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCheckListCheckedElementSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCheckListCheckedElementSet::SetBaseFilter(const CString &strFilter)
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

BOOL CCheckListCheckedElementSet::AddCheck(long lIDEsame, long lIDItem)
{
	BOOL bReturn = FALSE;

	SetOpenFilter("ID=0");
	if (OpenRecordset("CCheckListCheckedElementSet::AddCheck"))
	{
		if (AddNewRecordset("CCheckListCheckedElementSet::AddCheck"))
		{
			m_lIDEsame = lIDEsame;
			m_lIDItem = lIDItem;
			m_bEliminato = FALSE;
			
			bReturn = UpdateRecordset("CCheckListCheckedElementSet::AddCheck");
		}

		CloseRecordset("CCheckListCheckedElementSet::AddCheck");
	}

	return bReturn;
}

BOOL CCheckListCheckedElementSet::DelCheck(long lIDEsame, long lIDItem)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("IDEsame=%li AND IDItem=%li", lIDEsame, lIDItem);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCheckListCheckedElementSet::DelCheck"))
	{
		while(!IsEOF())
		{
			bReturn = DeleteRecordset("CCheckListCheckedElementSet::DelCheck");
			MoveNext();
		}

		CloseRecordset("CCheckListCheckedElementSet::DelCheck");
	}

	return bReturn;
}