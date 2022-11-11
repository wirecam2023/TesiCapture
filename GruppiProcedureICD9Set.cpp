#include "stdafx.h"
#include "Endox.h"
#include "GruppiProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiProcedureICD9Set, CBaseSet)

CGruppiProcedureICD9Set::CGruppiProcedureICD9Set()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CGruppiProcedureICD9Set::GetDefaultSQL()
{
	return "GRUPPIPROCEDUREICD9";
}

void CGruppiProcedureICD9Set::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CGruppiProcedureICD9Set::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lUO = 0;
	m_bEliminato = 0;
}

CString CGruppiProcedureICD9Set::GetStringDescrizione(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CGruppiProcedureICD9Set::GetStringDescrizione"))
	{
		if (!IsEOF())
			strReturn = m_sDescrizione;

		CloseRecordset("CGruppiProcedureICD9Set::GetStringDescrizione");
	}

	return strReturn;
}

CBaseSet* CGruppiProcedureICD9Set::CreateNew()
{
	return (CBaseSet*)new CGruppiProcedureICD9Set;
}

void CGruppiProcedureICD9Set::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CGruppiProcedureICD9Set* pSet = (CGruppiProcedureICD9Set*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
	
}

void CGruppiProcedureICD9Set::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CGruppiProcedureICD9Set* pOV = (CGruppiProcedureICD9Set*)pOldValues;
	CGruppiProcedureICD9Set* pNV = (CGruppiProcedureICD9Set*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CGruppiProcedureICD9Set::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CGruppiProcedureICD9Set::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CGruppiProcedureICD9Set::DeleteRecordset");
	}
	return bReturn;
}

CString CGruppiProcedureICD9Set::SetBaseFilter(const CString &strFilter)
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
		
BOOL CGruppiProcedureICD9Set::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
