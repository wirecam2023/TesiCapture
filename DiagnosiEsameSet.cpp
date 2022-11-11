#include "stdafx.h"
#include "Endox.h"
#include "DiagnosiEsamiSet.h"
#include "DiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDiagnosiEsamiSet, CBaseSet)

CDiagnosiEsamiSet::CDiagnosiEsamiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;

}

CString CDiagnosiEsamiSet::GetDefaultSQL()
{
	return "DIAGNOSIESAMI";	
}

void CDiagnosiEsamiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDDiagnosi = 0;
	m_bEliminato = FALSE;
}

void CDiagnosiEsamiSet::CopyFieldFrom(CDiagnosiEsamiSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lID))
		m_lID = pSet->m_lID;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDEsame))
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDDiagnosi))
		m_lIDDiagnosi = pSet->m_lIDDiagnosi;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;
		
	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CDiagnosiEsamiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDDiagnosi", m_lIDDiagnosi);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CDiagnosiEsamiSet::GetFieldText(long lEsame)
{
	CString strReturn = "";

	CDiagnosiICD9Set setTemp;

	CString strFilter;
	strFilter.Format("IDEsame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CDiagnosiEsamiSet::GetFieldText"))
	{
		while(!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += "\n";

			strReturn += setTemp.GetFieldText(m_lIDDiagnosi);

			MoveNext();
		}
		CloseRecordset("CDiagnosiEsamiSet::GetFieldText");
	}

	return strReturn;
}

CString CDiagnosiEsamiSet::GetStringDescrizione(long lEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("IDEsame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CDiagnosiEsamiSet::GetStringDescrizioni"))
	{
		CDiagnosiICD9Set setTemp;

		while(!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += "\n";

			strReturn += setTemp.GetStringDescrizione(m_lIDDiagnosi);

			MoveNext();
		}
		CloseRecordset("CDiagnosiEsamiSet::GetStringDescrizioni");
	}

	return strReturn;
}

BOOL CDiagnosiEsamiSet::Add(long lEsame, long idDiagnosi)
{
	BOOL strReturn = false;
	
	if (OpenRecordset("CDiagnosiEsamiSet::Add"))
	{
		if (AddNewRecordset("CDiagnosiEsamiSet::Add"))
		{
			m_lIDEsame = lEsame;
			m_lIDDiagnosi = idDiagnosi;

			UpdateRecordset("CDiagnosiEsamiSet::Add");
		}

		CloseRecordset("CDiagnosiEsamiSet::Add");
	}

	return strReturn;
}



CBaseSet* CDiagnosiEsamiSet::CreateNew()
{
	return (CBaseSet*)new CDiagnosiEsamiSet();
}

void CDiagnosiEsamiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CDiagnosiEsamiSet* pSet = (CDiagnosiEsamiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDDiagnosi) || bCopyAll)
		m_lIDDiagnosi = pSet->m_lIDDiagnosi;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CDiagnosiEsamiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CDiagnosiEsamiSet* pOV = (CDiagnosiEsamiSet*)pOldValues;
	CDiagnosiEsamiSet* pNV = (CDiagnosiEsamiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDDiagnosi", pOV, &pOV->m_lIDDiagnosi, pNV, &pNV->m_lIDDiagnosi);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CDiagnosiEsamiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CDiagnosiEsamiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CDiagnosiEsamiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CDiagnosiEsamiSet::SetBaseFilter(const CString &strFilter)
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