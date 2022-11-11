#include "stdafx.h"
#include "Endox.h"
#include "RobotSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRobotSet, CBaseSet)

CRobotSet::CRobotSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 12;
}

CString CRobotSet::GetDefaultSQL()
{
	return "ROBOT";
}

void CRobotSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "DESCRIPTION", m_sDescription, 255);
		RFX_Long(pFX, "TYPE", (long&) m_lType);
		RFX_Text(pFX, "HOST", m_sHost, 255);
		RFX_Long(pFX, "PORT", m_lPort);
		RFX_Text(pFX, "BACKUPLABELPATH", m_sBackupLabelPath, 255);
		RFX_Text(pFX, "PATIENTLABELPATH", m_sPatientLabelPath, 255);
		RFX_Text(pFX, "MERGEDIRECTORYPATH", m_sMergeDirectoryPath, 255);
		RFX_Text(pFX, "TEMPDIRECTORYPATH", m_sTempDirectoryPath, 255);
		RFX_Bool(pFX, "SIMULATIONMODE", m_bSimulationMode);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

void CRobotSet::SetEmpty()
{
	m_lID = 0;
	m_sDescription = "";
	m_lType = Type::Rimage;
	m_sHost = "";
	m_lPort = 0;
	m_sBackupLabelPath = "";
	m_sPatientLabelPath = "";
	m_sMergeDirectoryPath = "";
	m_sTempDirectoryPath = "";
	m_bSimulationMode = FALSE;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CRobotSet::CreateNew()
{
	return (CBaseSet*)new CRobotSet;
}

void CRobotSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CRobotSet* pSet = (CRobotSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescription) || bCopyAll)
		m_sDescription = pSet->m_sDescription;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lType) || bCopyAll)
		m_lType = pSet->m_lType;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sHost) || bCopyAll)
		m_sHost = pSet->m_sHost;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPort) || bCopyAll)
		m_lPort = pSet->m_lPort;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sBackupLabelPath) || bCopyAll)
		m_sBackupLabelPath = pSet->m_sBackupLabelPath;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPatientLabelPath) || bCopyAll)
		m_sPatientLabelPath = pSet->m_sPatientLabelPath;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMergeDirectoryPath) || bCopyAll)
		m_sMergeDirectoryPath = pSet->m_sMergeDirectoryPath;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTempDirectoryPath) || bCopyAll)
		m_sTempDirectoryPath = pSet->m_sTempDirectoryPath;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bSimulationMode) || bCopyAll)
		m_bSimulationMode = pSet->m_bSimulationMode;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CRobotSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CRobotSet* pOV = (CRobotSet*)pOldValues;
	CRobotSet* pNV = (CRobotSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("DESCRIPTION", pOV, &pOV->m_sDescription, pNV, &pNV->m_sDescription);
	sp.Execute("TYPE", pOV, (long*) &pOV->m_lType, pNV, (long*) &pNV->m_lType);
	sp.Execute("HOST", pOV, &pOV->m_sHost, pNV, &pNV->m_sHost);
	sp.Execute("PORT", pOV, &pOV->m_lPort, pNV, &pNV->m_lPort);
	sp.Execute("BACKUPLABELPATH", pOV, &pOV->m_sBackupLabelPath, pNV, &pNV->m_sBackupLabelPath);
	sp.Execute("PATIENTLABELPATH", pOV, &pOV->m_sPatientLabelPath, pNV, &pNV->m_sPatientLabelPath);
	sp.Execute("MERGEDIRECTORYPATH", pOV, &pOV->m_sMergeDirectoryPath, pNV, &pNV->m_sMergeDirectoryPath);
	sp.Execute("TEMPDIRECTORYPATH", pOV, &pOV->m_sTempDirectoryPath, pNV, &pNV->m_sTempDirectoryPath);
	sp.Execute("SIMULATIONMODE", pOV, &pOV->m_bSimulationMode, pNV, &pNV->m_bSimulationMode);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CRobotSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CRobotSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CRobotSet::DeleteRecordset");
	}
	return bReturn;
}

CString CRobotSet::SetBaseFilter(const CString &strFilter)
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

BOOL CRobotSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}