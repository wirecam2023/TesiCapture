#include "stdafx.h"
#include "Endox.h"
#include "GruppiDiagnosiICD9DiagnosiICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiDiagnosiICD9DiagnosiICD9Set, CBaseSet)

CGruppiDiagnosiICD9DiagnosiICD9Set::CGruppiDiagnosiICD9DiagnosiICD9Set()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 4;
	SetBaseFilter("");
}

void CGruppiDiagnosiICD9DiagnosiICD9Set::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDGruppo", m_lIDGruppo);
		RFX_Long(pFX, "IDDiagnosi", m_lIDDiagnosi);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CGruppiDiagnosiICD9DiagnosiICD9Set::GetDefaultSQL()
{
	return "GRUPPIDIAGNOSIICD9DIAGNOSIICD9";
}

void CGruppiDiagnosiICD9DiagnosiICD9Set::SetEmpty()
{
	m_lID = 0;
	m_lIDGruppo = 0;
	m_lIDDiagnosi = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CGruppiDiagnosiICD9DiagnosiICD9Set::CreateNew()
{
	return (CBaseSet*)new CGruppiDiagnosiICD9DiagnosiICD9Set;
}

void CGruppiDiagnosiICD9DiagnosiICD9Set::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CGruppiDiagnosiICD9DiagnosiICD9Set* GruppiDiagnosiICD9DiagnosiICD9Set = (CGruppiDiagnosiICD9DiagnosiICD9Set*)pOriginalSet;

	if (!GruppiDiagnosiICD9DiagnosiICD9Set->IsOpen() || GruppiDiagnosiICD9DiagnosiICD9Set->IsFieldDirty(&GruppiDiagnosiICD9DiagnosiICD9Set->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = GruppiDiagnosiICD9DiagnosiICD9Set->m_lIDGruppo;
	if (!GruppiDiagnosiICD9DiagnosiICD9Set->IsOpen() || GruppiDiagnosiICD9DiagnosiICD9Set->IsFieldDirty(&GruppiDiagnosiICD9DiagnosiICD9Set->m_lIDDiagnosi) || bCopyAll)
		m_lIDDiagnosi = GruppiDiagnosiICD9DiagnosiICD9Set->m_lIDDiagnosi;
	if (!GruppiDiagnosiICD9DiagnosiICD9Set->IsOpen() || GruppiDiagnosiICD9DiagnosiICD9Set->IsFieldDirty(&GruppiDiagnosiICD9DiagnosiICD9Set->m_bEliminato) || bCopyAll)
		m_bEliminato = GruppiDiagnosiICD9DiagnosiICD9Set->m_bEliminato;
}

void CGruppiDiagnosiICD9DiagnosiICD9Set::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CGruppiDiagnosiICD9DiagnosiICD9Set* pOV = (CGruppiDiagnosiICD9DiagnosiICD9Set*)pOldValues;
	CGruppiDiagnosiICD9DiagnosiICD9Set* pNV = (CGruppiDiagnosiICD9DiagnosiICD9Set*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDGruppo", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);
	sp.Execute("IDProcedura", pOV, &pOV->m_lIDDiagnosi, pNV, &pNV->m_lIDDiagnosi);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CGruppiDiagnosiICD9DiagnosiICD9Set::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CGruppiDiagnosiICD9DiagnosiICD9Set::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CGruppiDiagnosiICD9DiagnosiICD9Set::DeleteRecordset");
	}
	return bReturn;
}

CString CGruppiDiagnosiICD9DiagnosiICD9Set::SetBaseFilter(const CString &strFilter)
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