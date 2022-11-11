#include "stdafx.h"
#include "Endox.h"
#include "MonitoraggioFarmaciDosiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMonitoraggioFarmaciDosiSet, CBaseSet)

CMonitoraggioFarmaciDosiSet::CMonitoraggioFarmaciDosiSet()
	: CBaseSet(&m_lID, "ID")
{
	m_lID = 0;
	m_lIDMonitoraggio = 0;
	m_lIDFarmaco = 0;
	m_sDose = "";
	m_bEliminato = FALSE;

	m_nFields = 5;
	SetBaseFilter("");
}

CString CMonitoraggioFarmaciDosiSet::GetDefaultSQL()
{
	return "MONITORAGGIOFARMACIDOSI";
}

void CMonitoraggioFarmaciDosiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDMonitoraggio = 0;
	m_lIDFarmaco = 0;
	m_sDose = "";
	m_bEliminato = FALSE;
}

void CMonitoraggioFarmaciDosiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "idMonitoraggio", m_lIDMonitoraggio);
		RFX_Long(pFX, "idFarmaco", m_lIDFarmaco);
		RFX_Text(pFX, "Dose", m_sDose, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CMonitoraggioFarmaciDosiSet::CreateNew()
{
	return (CBaseSet*)new CMonitoraggioFarmaciDosiSet;
}

void CMonitoraggioFarmaciDosiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMonitoraggioFarmaciDosiSet* pDosiMonitoraggioSet = (CMonitoraggioFarmaciDosiSet*)pOriginalSet;

	if (!pDosiMonitoraggioSet->IsOpen() || pDosiMonitoraggioSet->IsFieldDirty(&pDosiMonitoraggioSet->m_lIDMonitoraggio) || bCopyAll)
		m_lIDMonitoraggio = pDosiMonitoraggioSet->m_lIDMonitoraggio;
	if (!pDosiMonitoraggioSet->IsOpen() || pDosiMonitoraggioSet->IsFieldDirty(&pDosiMonitoraggioSet->m_lIDFarmaco) || bCopyAll)
		m_lIDFarmaco = pDosiMonitoraggioSet->m_lIDFarmaco;
	if (!pDosiMonitoraggioSet->IsOpen() || pDosiMonitoraggioSet->IsFieldDirty(&pDosiMonitoraggioSet->m_sDose) || bCopyAll)
		m_sDose = pDosiMonitoraggioSet->m_sDose;
	if (!pDosiMonitoraggioSet->IsOpen() || pDosiMonitoraggioSet->IsFieldDirty(&pDosiMonitoraggioSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pDosiMonitoraggioSet->m_bEliminato;
}

void CMonitoraggioFarmaciDosiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMonitoraggioFarmaciDosiSet* pOV = (CMonitoraggioFarmaciDosiSet*)pOldValues;
	CMonitoraggioFarmaciDosiSet* pNV = (CMonitoraggioFarmaciDosiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdMonitoraggio", pOV, &pOV->m_lIDMonitoraggio, pNV, &pNV->m_lIDMonitoraggio);
	sp.Execute("IdFarmaco", pOV, &pOV->m_lIDFarmaco, pNV, &pNV->m_lIDFarmaco);
	sp.Execute("Dose", pOV, &pOV->m_sDose, pNV, &pNV->m_sDose);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMonitoraggioFarmaciDosiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMonitoraggioFarmaciDosiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMonitoraggioFarmaciDosiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMonitoraggioFarmaciDosiSet::SetBaseFilter(const CString &strFilter)
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