#include "stdafx.h"
#include "Endox.h"
#include "ReportsEtichetteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CReportsEtichetteSet, CBaseSet)

CReportsEtichetteSet::CReportsEtichetteSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CReportsEtichetteSet::GetDefaultSQL()
{
	return "ReportsEtichette";
}

void CReportsEtichetteSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizioneMenu = "";
	m_sReportFile = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CReportsEtichetteSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "DescrizioneMenu", m_sDescrizioneMenu, 50);
		RFX_Text(pFX, "ReportFile", m_sReportFile, 1024);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CReportsEtichetteSet::CreateNew()
{
	return (CBaseSet*)new CReportsEtichetteSet;
}

void CReportsEtichetteSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CReportsEtichetteSet* pSet = (CReportsEtichetteSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizioneMenu) || bCopyAll)
		m_sDescrizioneMenu = pSet->m_sDescrizioneMenu;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sReportFile) || bCopyAll)
		m_sReportFile = pSet->m_sReportFile;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CReportsEtichetteSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CReportsEtichetteSet* pOV = (CReportsEtichetteSet*)pOldValues;
	CReportsEtichetteSet* pNV = (CReportsEtichetteSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("DescrizioneMenu", pOV, &pOV->m_sDescrizioneMenu, pNV, &pNV->m_sDescrizioneMenu);
	sp.Execute("ReportFile", pOV, &pOV->m_sReportFile, pNV, &pNV->m_sReportFile);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CReportsEtichetteSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CReportsEtichetteSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CReportsEtichetteSet::DeleteRecordset");
	}
	return bReturn;
}

CString CReportsEtichetteSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CReportsEtichetteSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

CString CReportsEtichetteSet::GetReportFile(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CReportsEtichetteSet::GetReportFile"))
	{
		if (!IsEOF())
			sReturn = m_sReportFile;

		CloseRecordset("CReportsEtichetteSet::GetReportFile");
	}

	return sReturn;
}