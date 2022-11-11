#include "stdafx.h"
#include "Endox.h"
#include "DiagnosiFinaliEsamiSet.h"
#include "DiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDiagnosiFinaliEsamiSet, CBaseSet)

CDiagnosiFinaliEsamiSet::CDiagnosiFinaliEsamiSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;

}

CString CDiagnosiFinaliEsamiSet::GetDefaultSQL()
{
	return "DIAGNOSIFINALIESAMI";
}

void CDiagnosiFinaliEsamiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDDiagnosi = 0;
	m_bEliminato = FALSE;
}

void CDiagnosiFinaliEsamiSet::CopyFieldFrom(CDiagnosiFinaliEsamiSet* pSet)
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
		SetFieldNull(NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CDiagnosiFinaliEsamiSet::DoFieldExchange(CFieldExchange* pFX)
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

CString CDiagnosiFinaliEsamiSet::GetFieldText(long lEsame)
{
	CString strReturn = "";

	CDiagnosiICD9Set setTemp;

	CString strFilter;
	strFilter.Format("IDEsame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CDiagnosiFinaliEsamiSet::GetFieldText"))
	{
		while (!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += "\n";

			strReturn += setTemp.GetFieldText(m_lIDDiagnosi);

			MoveNext();
		}
		CloseRecordset("CDiagnosiFinaliEsamiSet::GetFieldText");
	}

	return strReturn;
}

CString CDiagnosiFinaliEsamiSet::GetStringDescrizione(long lEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("IDEsame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CDiagnosiFinaliEsamiSet::GetStringDescrizioni"))
	{
		CDiagnosiICD9Set setTemp;

		while (!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += "\n";

			strReturn += setTemp.GetStringDescrizione(m_lIDDiagnosi);

			MoveNext();
		}
		CloseRecordset("CDiagnosiFinaliEsamiSet::GetStringDescrizioni");
	}

	return strReturn;
}

BOOL CDiagnosiFinaliEsamiSet::Add(long lEsame, long idDiagnosi)
{
	BOOL strReturn = false;

	if (OpenRecordset("CDiagnosiFinaliEsamiSet::Add"))
	{
		if (AddNewRecordset("CDiagnosiFinaliEsamiSet::Add"))
		{
			m_lIDEsame = lEsame;
			m_lIDDiagnosi = idDiagnosi;

			UpdateRecordset("CDiagnosiFinaliEsamiSet::Add");
		}

		CloseRecordset("CDiagnosiFinaliEsamiSet::Add");
	}

	return strReturn;
}



CBaseSet* CDiagnosiFinaliEsamiSet::CreateNew()
{
	return (CBaseSet*)new CDiagnosiFinaliEsamiSet();
}

void CDiagnosiFinaliEsamiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CDiagnosiFinaliEsamiSet* pSet = (CDiagnosiFinaliEsamiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDDiagnosi) || bCopyAll)
		m_lIDDiagnosi = pSet->m_lIDDiagnosi;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CDiagnosiFinaliEsamiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CDiagnosiFinaliEsamiSet* pOV = (CDiagnosiFinaliEsamiSet*)pOldValues;
	CDiagnosiFinaliEsamiSet* pNV = (CDiagnosiFinaliEsamiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDDiagnosi", pOV, &pOV->m_lIDDiagnosi, pNV, &pNV->m_lIDDiagnosi);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CDiagnosiFinaliEsamiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CDiagnosiFinaliEsamiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CDiagnosiFinaliEsamiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CDiagnosiFinaliEsamiSet::SetBaseFilter(const CString &strFilter)
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