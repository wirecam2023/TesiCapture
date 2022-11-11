#include "stdafx.h"
#include "Endox.h"
#include "GruppiProcedureICD9ProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiProcedureICD9ProcedureICD9Set, CBaseSet)

CGruppiProcedureICD9ProcedureICD9Set::CGruppiProcedureICD9ProcedureICD9Set()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 4;
	SetBaseFilter("");
}

void CGruppiProcedureICD9ProcedureICD9Set::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDGruppo", m_lIDGruppo);
		RFX_Long(pFX, "IDProcedura", m_lIDProcedura);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CGruppiProcedureICD9ProcedureICD9Set::GetDefaultSQL()
{
	return "GRUPPIPROCEDUREICD9PROCEDUICD9";
}

void CGruppiProcedureICD9ProcedureICD9Set::SetEmpty()
{
	m_lID = 0;
	m_lIDGruppo = 0;
	m_lIDProcedura = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CGruppiProcedureICD9ProcedureICD9Set::CreateNew()
{
	return (CBaseSet*)new CGruppiProcedureICD9ProcedureICD9Set;
}

void CGruppiProcedureICD9ProcedureICD9Set::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CGruppiProcedureICD9ProcedureICD9Set* gruppiProcedureICD9ProcedureICD9Set = (CGruppiProcedureICD9ProcedureICD9Set*)pOriginalSet;

	if (!gruppiProcedureICD9ProcedureICD9Set->IsOpen() || gruppiProcedureICD9ProcedureICD9Set->IsFieldDirty(&gruppiProcedureICD9ProcedureICD9Set->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = gruppiProcedureICD9ProcedureICD9Set->m_lIDGruppo;
	if (!gruppiProcedureICD9ProcedureICD9Set->IsOpen() || gruppiProcedureICD9ProcedureICD9Set->IsFieldDirty(&gruppiProcedureICD9ProcedureICD9Set->m_lIDProcedura) || bCopyAll)
		m_lIDProcedura = gruppiProcedureICD9ProcedureICD9Set->m_lIDProcedura;
	if (!gruppiProcedureICD9ProcedureICD9Set->IsOpen() || gruppiProcedureICD9ProcedureICD9Set->IsFieldDirty(&gruppiProcedureICD9ProcedureICD9Set->m_bEliminato) || bCopyAll)
		m_bEliminato = gruppiProcedureICD9ProcedureICD9Set->m_bEliminato;
}

void CGruppiProcedureICD9ProcedureICD9Set::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CGruppiProcedureICD9ProcedureICD9Set* pOV = (CGruppiProcedureICD9ProcedureICD9Set*)pOldValues;
	CGruppiProcedureICD9ProcedureICD9Set* pNV = (CGruppiProcedureICD9ProcedureICD9Set*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDGruppo", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);
	sp.Execute("IDProcedura", pOV, &pOV->m_lIDProcedura, pNV, &pNV->m_lIDProcedura);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CGruppiProcedureICD9ProcedureICD9Set::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CGruppiProcedureICD9ProcedureICD9Set::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CGruppiProcedureICD9ProcedureICD9Set::DeleteRecordset");
	}
	return bReturn;
}

CString CGruppiProcedureICD9ProcedureICD9Set::SetBaseFilter(const CString &strFilter)
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