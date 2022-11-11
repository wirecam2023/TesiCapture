#include "stdafx.h"
#include "Endox.h"
#include "ProcedureEsamiSet.h"
#include "ProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProcedureEsamiSet, CBaseSet)

CProcedureEsamiSet::CProcedureEsamiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CProcedureEsamiSet::GetDefaultSQL()
{
	return "PROCEDUREESAMI";
}

void CProcedureEsamiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDProcedura = 0;
	m_bEliminato = FALSE;
}

void CProcedureEsamiSet::CopyFieldFrom(CProcedureEsamiSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lID))
		m_lID = pSet->m_lID;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDEsame))
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDProcedura))
		m_lIDProcedura = pSet->m_lIDProcedura;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;
		
	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CProcedureEsamiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "IDEsame", m_lIDEsame);
		RFX_Long (pFX, "IDProcedura", m_lIDProcedura);
		RFX_Bool (pFX, "Eliminato", m_bEliminato);
	}
}

CString CProcedureEsamiSet::GetFieldText(long lEsame)
{
	CString strReturn = "";

	CProcedureICD9Set setTemp;

	CString strFilter;
	strFilter.Format("IDEsame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CProcedureEsamiSet::GetFieldText"))
	{
		while(!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += "\n";

			strReturn += setTemp.GetFieldText(m_lIDProcedura);

			MoveNext();
		}
		CloseRecordset("CProcedureEsamiSet::GetFieldText");
	}

	return strReturn;
}

BOOL CProcedureEsamiSet::Add(long lEsame, long idProcedura)
{
	BOOL strReturn = false;

	if (OpenRecordset("CProcedureEsamiSet::Add"))
	{
		if (AddNewRecordset("CProcedureEsamiSet::Add"))
		{
			m_lIDEsame = lEsame;
			m_lIDProcedura = idProcedura;

			UpdateRecordset("CProcedureEsamiSet::Add");
		}

		CloseRecordset("CProcedureEsamiSet::Add");
	}

	return strReturn;
}

/*
CString CProcedureEsamiSet::GetStringDescrizione(long lEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("IDEsame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CProcedureEsamiSet::GetStringDescrizioni"))
	{
		CProcedureICD9Set setTemp;

		while(!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += "\n";

			strReturn += setTemp.GetDescrizione(m_lIDProcedura);

			MoveNext();
		}
		CloseRecordset("CProcedureEsamiSet::GetStringDescrizioni");
	}

	return strReturn;
}
*/

CBaseSet* CProcedureEsamiSet::CreateNew()
{
	return (CBaseSet*)new CProcedureEsamiSet;
}

void CProcedureEsamiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CProcedureEsamiSet* pSet = (CProcedureEsamiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDProcedura) || bCopyAll)
		m_lIDProcedura = pSet->m_lIDProcedura;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CProcedureEsamiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CProcedureEsamiSet* pOV = (CProcedureEsamiSet*)pOldValues;
	CProcedureEsamiSet* pNV = (CProcedureEsamiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDProcedura", pOV, &pOV->m_lIDProcedura, pNV, &pNV->m_lIDProcedura);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CProcedureEsamiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CProcedureEsamiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CProcedureEsamiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CProcedureEsamiSet::SetBaseFilter(const CString &strFilter)
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