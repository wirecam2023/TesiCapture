#include "stdafx.h"
#include "Endox.h"
#include "PazientiStoricoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPazientiStoricoSet, CBaseSet)

CPazientiStoricoSet::CPazientiStoricoSet()
	: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	m_lId = 0;
	m_lIdPaziente = 0;
	m_sAssIden = "";
	m_bEliminato = FALSE;

	m_nFields = 4;
}

void CPazientiStoricoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Id",			m_lId);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IdPaziente",		m_lIdPaziente);
		RFX_Text(pFX, "AssIden",			m_sAssIden,				  50);
		RFX_Bool(pFX, "Eliminato",          m_bEliminato);
	}
}

CString CPazientiStoricoSet::GetDefaultSQL()
{
	return "EPAZIENTI_STORICO";
}

CBaseSet* CPazientiStoricoSet::CreateNew()
{
	return (CBaseSet*)new CPazientiStoricoSet;
}

void CPazientiStoricoSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CPazientiStoricoSet* pPazientiSet = (CPazientiStoricoSet*)pOriginalSet;

	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_lIdPaziente) || bCopyAll)
		m_lIdPaziente = pPazientiSet->m_lIdPaziente;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_sAssIden) || bCopyAll)
		m_sAssIden = pPazientiSet->m_sAssIden;
	if (!pPazientiSet->IsOpen() || pPazientiSet->IsFieldDirty(&pPazientiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pPazientiSet->m_bEliminato;
}

void CPazientiStoricoSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CPazientiStoricoSet* pOV = (CPazientiStoricoSet*)pOldValues;
	CPazientiStoricoSet* pNV = (CPazientiStoricoSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdPaziente", pOV, &pOV->m_lIdPaziente, pNV, &pNV->m_lIdPaziente);
	sp.Execute("AssIden", pOV, &pOV->m_sAssIden, pNV, &pNV->m_sAssIden);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CPazientiStoricoSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CPazientiStoricoSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CPazientiStoricoSet::DeleteRecordset");
	}
	return bReturn;
}

BOOL CPazientiStoricoSet::UndeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CPazientiStoricoSet::UndeleteRecordset"))
	{
		m_bEliminato = FALSE;
		bReturn = UpdateRecordset("CPazientiStoricoSet::UndeleteRecordset");
	}
	return bReturn;
}

CString CPazientiStoricoSet::SetBaseFilter(const CString &strFilter)
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