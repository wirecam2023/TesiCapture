#include "stdafx.h"
#include "Endox.h"
#include "EndoGridCLVersionSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridCLVersionSet, CBaseSet)

CEndoGridCLVersionSet::CEndoGridCLVersionSet(CDatabase* pDatabase)
: CBaseSet(&m_lID, "ID")
{
	m_lID = 0;
	m_lParameterID = 0;
	m_lVersionID = 0;
	m_bEliminato = FALSE;
	m_nFields = 4;
}

void CEndoGridCLVersionSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("ID"), m_lID);
	RFX_Long(pFX, _T("IDPARAMETRO"), m_lParameterID);
	RFX_Long(pFX, _T("IDVERSIONE"), m_lVersionID);
	RFX_Bool(pFX, _T("ELIMINATO"), m_bEliminato);
}

CString CEndoGridCLVersionSet::GetDefaultSQL()
{
	return _T("GRIDCL_PARAM_VERS");
}

long CEndoGridCLVersionSet::GetLastGridVersion()
{
	long lReturn = 0;

	SetOpenFilter("");
	SetSortRecord("IDVERSIONE");
	if (OpenRecordset("CEndoGridCLVersionSet::GetLastGridVersion"))
	{
		if (!IsEOF() && !IsBOF())
		{
			MoveLast();//Davide - Replica OK
			lReturn = m_lVersionID;
		}

		CloseRecordset("CEndoGridCLVersionSet::GetLastGridVersion");
	}	

	return lReturn;
}

void CEndoGridCLVersionSet::DuplicateVersion(long lOldVersionID, long lNewVersionID)
{
	CString strFilter, strQuery;
	strFilter.Format("IDVERSIONE = %li", lOldVersionID);
	SetOpenFilter(strFilter);

	if (OpenRecordset("CEndoGridCLVersionSet::DuplicateVersion"))
	{
		while (!IsEOF())
		{
			CEndoGridCLVersionSet tempSet;
			if (tempSet.OpenRecordset("CEndoGridCLVersionSet::DuplicateVersion"))
			{
				if (tempSet.AddNewRecordset("CEndoGridCLVersionSet::DuplicateVersion"))
				{
					tempSet.m_lParameterID = m_lParameterID;
					tempSet.m_lVersionID = lNewVersionID;

					tempSet.UpdateRecordset("CEndoGridCLVersionSet::DuplicateVersion");
				}

				tempSet.CloseRecordset("CEndoGridCLVersionSet::DuplicateVersion");
			}

			MoveNext();
		}

		CloseRecordset("CEndoGridCLVersionSet::DuplicateVersion");
	}	
}

BOOL CEndoGridCLVersionSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEndoGridCLVersionSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEndoGridCLVersionSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEndoGridCLVersionSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();
	
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CEndoGridCLVersionSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

CBaseSet* CEndoGridCLVersionSet::CreateNew()
{
	return (CBaseSet*)new CEndoGridCLVersionSet;
}

void CEndoGridCLVersionSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEndoGridCLVersionSet* pSet = (CEndoGridCLVersionSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lParameterID) || bCopyAll)
		m_lParameterID = pSet->m_lParameterID;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lVersionID) || bCopyAll)
		m_lVersionID = pSet->m_lVersionID;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEndoGridCLVersionSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEndoGridCLVersionSet* pOV = (CEndoGridCLVersionSet*)pOldValues;
	CEndoGridCLVersionSet* pNV = (CEndoGridCLVersionSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDPARAMETRO", pOV, &pOV->m_lParameterID, pNV, &pNV->m_lParameterID);
	sp.Execute("IDVERSIONE", pOV, &pOV->m_lVersionID, pNV, &pNV->m_lVersionID);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}