#include "stdafx.h"
#include "Endox.h"
#include "DosiMonitoraggioSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDosiMonitoraggioSet, CBaseSet)

CDosiMonitoraggioSet::CDosiMonitoraggioSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CDosiMonitoraggioSet::GetDefaultSQL()
{
	return "MONITORAGGIODOSI";
}

void CDosiMonitoraggioSet::SetEmpty()
{
	m_lID = 0;
	m_sNome = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CDosiMonitoraggioSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sNome, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CDosiMonitoraggioSet::CreateNew()
{
	return (CBaseSet*)new CDosiMonitoraggioSet;
}

void CDosiMonitoraggioSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CDosiMonitoraggioSet* pSet = (CDosiMonitoraggioSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNome) || bCopyAll)
		m_sNome = pSet->m_sNome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CDosiMonitoraggioSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CDosiMonitoraggioSet* pOV = (CDosiMonitoraggioSet*)pOldValues;
	CDosiMonitoraggioSet* pNV = (CDosiMonitoraggioSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sNome, pNV, &pNV->m_sNome);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CDosiMonitoraggioSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CDosiMonitoraggioSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CDosiMonitoraggioSet::DeleteRecordset");
	}
	return bReturn;
}

CString CDosiMonitoraggioSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CDosiMonitoraggioSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

long CDosiMonitoraggioSet::Add(CString strDescrizione)
{
	long lReturn = 0;

	if (OpenRecordset("CDosiMonitoraggioSet::AddPrestazione"))
	{
		if (AddNewRecordset("CDosiMonitoraggioSet::AddPrestazione"))
		{
		    m_sNome = strDescrizione;
			if (UpdateRecordset("CDosiMonitoraggioSet::AddPrestazione"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CDosiMonitoraggioSet::AddPrestazione");
	}

	return lReturn;
}

void CDosiMonitoraggioSet::Edt(long lID, CString strDescrizione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CDosiMonitoraggioSet::EdtPrestazione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CDosiMonitoraggioSet::EdtPrestazione"))
			{
				m_sNome = strDescrizione;
				UpdateRecordset("CDosiMonitoraggioSet::EdtPrestazione");
			}
		}

		CloseRecordset("CDosiMonitoraggioSet::EdtPrestazione");
	}
}

void CDosiMonitoraggioSet::Del(long lID)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CDosiMonitoraggioSet::DelPrestazione"))
	{
		if (!IsEOF())
			DeleteRecordset("CDosiMonitoraggioSet::DelPrestazione");

		CloseRecordset("CDosiMonitoraggioSet::DelPrestazione");
	}
}