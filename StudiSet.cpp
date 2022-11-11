#include "stdafx.h"
#include "Endox.h"

#include "StudiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CStudiSet, CBaseSet)

CStudiSet::CStudiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

void CStudiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CStudiSet::GetDefaultSQL()
{
	return "Studi";
}

void CStudiSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CStudiSet::CreateNew()
{
	return (CBaseSet*)new CStudiSet;
}

void CStudiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CStudiSet* pSet = (CStudiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CStudiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CStudiSet* pOV = (CStudiSet*)pOldValues;
	CStudiSet* pNV = (CStudiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CStudiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CStudiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CStudiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CStudiSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CStudiSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

void CStudiSet::AddStudio(CString sDescrizione)
{
	SetOpenFilter("ID=0");
	if (OpenRecordset("CStudiSet::AddStudio"))
	{
		if (AddNewRecordset("CStudiSet::AddStudio"))
		{
			m_sDescrizione = sDescrizione;
			UpdateRecordset("CStudiSet::AddStudio");
		}

		CloseRecordset("CStudiSet::AddStudio");
	}
}

void CStudiSet::EdtStudio(long lID, CString sDescrizione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CStudiSet::EdtStudio"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CStudiSet::EdtStudio"))
			{
				m_sDescrizione = sDescrizione;
				UpdateRecordset("CStudiSet::EdtStudio");
			}
		}

		CloseRecordset("CStudiSet::EdtStudio");
	}
}

BOOL CStudiSet::DelStudio(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CStudiSet::DelStudio"))
	{
		if (!IsEOF())
			bReturn = DeleteRecordset("CStudiSet::DelStudio");

		CloseRecordset("CStudiSet::DelStudio");
	}

	return bReturn;
}

CString CStudiSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CStudiSet::DelStudio"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CStudiSet::DelStudio");
	}

	return sReturn;
}