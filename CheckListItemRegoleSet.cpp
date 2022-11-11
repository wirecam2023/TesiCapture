#include "stdafx.h"
#include "Endox.h"
#include "CheckListItemRegoleSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCheckListItemRegoleSet, CBaseSet)

CCheckListItemRegoleSet::CCheckListItemRegoleSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();
	SetSortRecord("ID");

	m_nFields = 5;
}

void CCheckListItemRegoleSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if(m_nFields > 1)
	{
		RFX_Long(pFX, "IDCheckListItem", m_lIDCheckListItem);
		RFX_Long(pFX, "IDCheckListItemBind", m_lIDCheckListItemBind);
		RFX_Long(pFX, "TipoRegola", m_lTipoRegola);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CCheckListItemRegoleSet::GetDefaultSQL()
{
	return "CHECKLISTITEMREGOLE";
}

void CCheckListItemRegoleSet::SetEmpty()
{
	m_lID = 0;
	m_lIDCheckListItem = 0;
	m_lIDCheckListItemBind = 0;
	m_lTipoRegola = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CCheckListItemRegoleSet::CreateNew()
{
	return (CBaseSet*)new CCheckListItemRegoleSet;
}

void CCheckListItemRegoleSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCheckListItemRegoleSet* pSet = (CCheckListItemRegoleSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDCheckListItem) || bCopyAll)
		m_lIDCheckListItem = pSet->m_lIDCheckListItem;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDCheckListItemBind) || bCopyAll)
		m_lIDCheckListItemBind = pSet->m_lIDCheckListItemBind;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTipoRegola) || bCopyAll)
		m_lTipoRegola = pSet->m_lTipoRegola;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCheckListItemRegoleSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCheckListItemRegoleSet* pOV = (CCheckListItemRegoleSet*)pOldValues;
	CCheckListItemRegoleSet* pNV = (CCheckListItemRegoleSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDCheckListItem", pOV, &pOV->m_lIDCheckListItem, pNV, &pNV->m_lIDCheckListItem);
	sp.Execute("IDCheckListItemBind", pOV, &pOV->m_lIDCheckListItemBind, pNV, &pNV->m_lIDCheckListItemBind);
	sp.Execute("TipoRegola", pOV, &pOV->m_lTipoRegola, pNV, &pNV->m_lTipoRegola);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCheckListItemRegoleSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCheckListItemRegoleSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCheckListItemRegoleSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCheckListItemRegoleSet::SetBaseFilter(const CString &strFilter)
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

void CCheckListItemRegoleSet::AddRow(long lIDCheckListItem, long lIDCheckListItemBind, long lTipoRegola)
{
	SetOpenFilter("ID=0");
	if (OpenRecordset("CCheckListItemRegoleSet::AddRow"))
	{
		if (AddNewRecordset("CCheckListItemRegoleSet::AddRow"))
		{
			m_lIDCheckListItem = lIDCheckListItem;
			m_lIDCheckListItemBind = lIDCheckListItemBind;
			m_lTipoRegola = lTipoRegola;

			UpdateRecordset("CCheckListItemRegoleSet::AddRow");
		}

		CloseRecordset("CCheckListItemRegoleSet::AddRow");
	}
}