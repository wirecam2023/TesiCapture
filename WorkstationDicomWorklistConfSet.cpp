#include "stdafx.h"
#include "Endox.h"
#include "WorkstationDicomWorklistConfSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CWorkstationDicomWorklistConfSet, CBaseSet)

CWorkstationDicomWorklistConfSet::CWorkstationDicomWorklistConfSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CWorkstationDicomWorklistConfSet::GetDefaultSQL()
{
	return "WORKSTATIONDICOMWORKLISTCONF";
}

void CWorkstationDicomWorklistConfSet::SetEmpty()
{
	m_lID = 0;
	m_sWorkstation = "";
	m_bActive = FALSE;
	m_sAET = "";
	m_lPort = 0;
	m_bWriteLog = FALSE;
}

void CWorkstationDicomWorklistConfSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "WORKSTATION", m_sWorkstation, 255);
		RFX_Bool(pFX, "ACTIVE", m_bActive);
		RFX_Text(pFX, "AET", m_sAET, 255);
		RFX_Long(pFX, "PORT", m_lPort);
		RFX_Bool(pFX, "WRITELOG", m_bWriteLog);
	}
}

BOOL CWorkstationDicomWorklistConfSet::GetWorkstationState(CString& sAET, long& lPort, BOOL& bWriteLog)
{
	BOOL bReturn = FALSE;

	sAET = "";
	lPort = 0;
	bWriteLog = FALSE;

	CString sWorkstation = theApp.m_sNomeComputer;
	sWorkstation.Replace("'", "''");
	sWorkstation.MakeUpper();

	CString sFilter;
	sFilter.Format("UPPER(WORKSTATION)='%s'", sWorkstation);
	SetOpenFilter(sFilter);
	if (OpenRecordset("CWorkstationDicomWorklistConfSet::GetWorkstationState"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CWorkstationDicomWorklistConfSet::GetWorkstationState"))
			{
				m_sWorkstation = sWorkstation;
				m_bActive = FALSE;
				m_sAET = sAET;
				m_lPort = lPort;
				m_bWriteLog = bWriteLog;

				UpdateRecordset("CWorkstationDicomWorklistConfSet::GetWorkstationState");
			}
		}
		else
		{
			bReturn = m_bActive;
			sAET = m_sAET;
			lPort = m_lPort;
			bWriteLog = m_bWriteLog;
		}

		CloseRecordset("CWorkstationDicomWorklistConfSet::GetWorkstationState");
	}

	return bReturn;
}

CBaseSet* CWorkstationDicomWorklistConfSet::CreateNew()
{
	return (CBaseSet*)new CWorkstationDicomWorklistConfSet;
}

void CWorkstationDicomWorklistConfSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CWorkstationDicomWorklistConfSet* pSet = (CWorkstationDicomWorklistConfSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sWorkstation) || bCopyAll)
		m_sWorkstation = pSet->m_sWorkstation;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bActive) || bCopyAll)
		m_bActive = pSet->m_bActive;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sAET) || bCopyAll)
		m_sAET = pSet->m_sAET;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPort) || bCopyAll)
		m_lPort = pSet->m_lPort;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bWriteLog) || bCopyAll)
		m_bWriteLog = pSet->m_bWriteLog;
}

void CWorkstationDicomWorklistConfSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CWorkstationDicomWorklistConfSet* pOV = (CWorkstationDicomWorklistConfSet*)pOldValues;
	CWorkstationDicomWorklistConfSet* pNV = (CWorkstationDicomWorklistConfSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("WORKSTATION", pOV, &pOV->m_sWorkstation, pNV, &pNV->m_sWorkstation);
	sp.Execute("ACTIVE", pOV, &pOV->m_bActive, pNV, &pNV->m_bActive);
	sp.Execute("AET", pOV, &pOV->m_sAET, pNV, &pNV->m_sAET);
	sp.Execute("PORT", pOV, &pOV->m_lPort, pNV, &pNV->m_lPort);
	sp.Execute("WRITELOG", pOV, &pOV->m_bWriteLog, pNV, &pNV->m_bWriteLog);
}

BOOL CWorkstationDicomWorklistConfSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	/* if (EditRecordset("CWorkstationDicomWorklistConfSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CWorkstationDicomWorklistConfSet::DeleteRecordset");
	} */
	return bReturn;
}

/*
CString CWorkstationDicomWorklistConfSet::SetBaseFilter(const CString &strFilter)
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
*/
	
/*
BOOL CWorkstationDicomWorklistConfSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
*/