#include "stdafx.h"
#include "Endox.h"
#include "DistrettiSediEsamiSet.h"

#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDistrettiSediEsamiSet, CBaseSet)

CDistrettiSediEsamiSet::CDistrettiSediEsamiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CDistrettiSediEsamiSet::GetDefaultSQL()
{
	return "DistrettiSediEsami";
}

void CDistrettiSediEsamiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDDistretto", m_lIDDistretto);
		RFX_Long(pFX, "IDSedeEsame", m_lIDSedeEsame);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CDistrettiSediEsamiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDDistretto = 0;
	m_lIDSedeEsame = 0;
	m_bEliminato = FALSE;
}

long CDistrettiSediEsamiSet::GetIDDistretto(long lIDSedeEsame)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("IDSedeEsame=%li", lIDSedeEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CDistrettiSediEsamiSet::GetIDDistretto"))
	{
		if (!IsEOF())
			lReturn = m_lIDDistretto;

		CloseRecordset("CDistrettiSediEsamiSet::GetIDDistretto");
	}

	return lReturn;
}

BOOL CDistrettiSediEsamiSet::GetStessoDistretto(long lIDSedeEsame)
{
/*
#ifdef _DEBUG
	return TRUE;
#endif
*/

	// --- //

	BOOL bReturn = FALSE;

	if (lIDSedeEsame == theApp.m_lIDSedeEsameDefault)
	{
		bReturn = TRUE;
	}
	else
	{
		CString strFilter;
		strFilter.Format("IDSedeEsame=%li OR IDSedeEsame=%li", lIDSedeEsame, theApp.m_lIDSedeEsameDefault);

		SetOpenFilter(strFilter);
		if (OpenRecordset("CDistrettiSediEsamiSet::GetStessoDistretto"))
		{
			long lIDDistretto = -1;

			while(!IsEOF())
			{
				if (lIDDistretto <= 0)
				{
					lIDDistretto = m_lIDDistretto;
				}
				else
				{
					bReturn = (lIDDistretto == m_lIDDistretto);
					break;
				}

				MoveNext();
			}

			CloseRecordset("CDistrettiSediEsamiSet::GetStessoDistretto");
		}
	}

	return bReturn;
}

CBaseSet* CDistrettiSediEsamiSet::CreateNew()
{
	return (CBaseSet*)new CDistrettiSediEsamiSet;;
}

void CDistrettiSediEsamiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CDistrettiSediEsamiSet* pSet = (CDistrettiSediEsamiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDDistretto) || bCopyAll)
		m_lIDDistretto = pSet->m_lIDDistretto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDSedeEsame) || bCopyAll)
		m_lIDSedeEsame = pSet->m_lIDSedeEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CDistrettiSediEsamiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CDistrettiSediEsamiSet* pOV = (CDistrettiSediEsamiSet*)pOldValues;
	CDistrettiSediEsamiSet* pNV = (CDistrettiSediEsamiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDDistretto", pOV, &pOV->m_lIDDistretto, pNV, &pNV->m_lIDDistretto);
	sp.Execute("IDSedeEsame", pOV, &pOV->m_lIDSedeEsame, pNV, &pNV->m_lIDSedeEsame);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CDistrettiSediEsamiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CDistrettiSediEsamiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CDistrettiSediEsamiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CDistrettiSediEsamiSet::SetBaseFilter(const CString &strFilter)
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