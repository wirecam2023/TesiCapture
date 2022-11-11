#include "stdafx.h"
#include "Endox.h"
#include "PuntiSediSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPuntiSediSet, CBaseSet)

CPuntiSediSet::CPuntiSediSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 3;
}

CString CPuntiSediSet::GetDefaultSQL()
{
	return "PUNTISEDI";
}

void CPuntiSediSet::SetEmpty()
{
	m_lID = 0;
	m_sSede = "";
	m_bEliminato = FALSE;
}

void CPuntiSediSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Sede", m_sSede, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CPuntiSediSet::CreateNew()
{
	return (CBaseSet*)new CPuntiSediSet;
}

void CPuntiSediSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CPuntiSediSet* pSet = (CPuntiSediSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSede) || bCopyAll)
		m_sSede = pSet->m_sSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CPuntiSediSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CPuntiSediSet* pOV = (CPuntiSediSet*)pOldValues;
	CPuntiSediSet* pNV = (CPuntiSediSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Sede", pOV, &pOV->m_sSede, pNV, &pNV->m_sSede);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CPuntiSediSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CPuntiSediSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CPuntiSediSet::DeleteRecordset");
	}
	return bReturn;
}

CString CPuntiSediSet::SetBaseFilter(const CString &strFilter)
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