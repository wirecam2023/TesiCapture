#include "stdafx.h"
#include "Endox.h"
#include "FarmaciMonitoraggioSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFarmaciMonitoraggioSet, CBaseSet)

CFarmaciMonitoraggioSet::CFarmaciMonitoraggioSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CFarmaciMonitoraggioSet::GetDefaultSQL()
{
	return "MONITORAGGIOFARMACI";
}

void CFarmaciMonitoraggioSet::SetEmpty()
{
	m_lID = 0;
	m_sNome = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CFarmaciMonitoraggioSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Nome", m_sNome, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CFarmaciMonitoraggioSet::CreateNew()
{
	return (CBaseSet*)new CFarmaciMonitoraggioSet;
}

void CFarmaciMonitoraggioSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFarmaciMonitoraggioSet* pSet = (CFarmaciMonitoraggioSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNome) || bCopyAll)
		m_sNome = pSet->m_sNome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CFarmaciMonitoraggioSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFarmaciMonitoraggioSet* pOV = (CFarmaciMonitoraggioSet*)pOldValues;
	CFarmaciMonitoraggioSet* pNV = (CFarmaciMonitoraggioSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Nome", pOV, &pOV->m_sNome, pNV, &pNV->m_sNome);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFarmaciMonitoraggioSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CFarmaciMonitoraggioSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CFarmaciMonitoraggioSet::DeleteRecordset");
	}
	return bReturn;
}

CString CFarmaciMonitoraggioSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CFarmaciMonitoraggioSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

long CFarmaciMonitoraggioSet::Add(CString strDescrizione)
{
	long lReturn = 0;

	if (OpenRecordset("CFarmaciMonitoraggioSet::AddPrestazione"))
	{
		if (AddNewRecordset("CFarmaciMonitoraggioSet::AddPrestazione"))
		{
		    m_sNome = strDescrizione;
			if (UpdateRecordset("CFarmaciMonitoraggioSet::AddPrestazione"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CFarmaciMonitoraggioSet::AddPrestazione");
	}

	return lReturn;
}

void CFarmaciMonitoraggioSet::Edt(long lID, CString strDescrizione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CFarmaciMonitoraggioSet::EdtPrestazione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFarmaciMonitoraggioSet::EdtPrestazione"))
			{
				m_sNome = strDescrizione;
				UpdateRecordset("CFarmaciMonitoraggioSet::EdtPrestazione");
			}
		}

		CloseRecordset("CFarmaciMonitoraggioSet::EdtPrestazione");
	}
}

void CFarmaciMonitoraggioSet::Del(long lID)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CFarmaciMonitoraggioSet::DelPrestazione"))
	{
		if (!IsEOF())
			DeleteRecordset("CFarmaciMonitoraggioSet::DelPrestazione");

		CloseRecordset("CFarmaciMonitoraggioSet::DelPrestazione");
	}
}