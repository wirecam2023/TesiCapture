#include "stdafx.h"
#include "Endox.h"
#include "ProcedureICD9Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProcedureICD9Set, CBaseSet)

CProcedureICD9Set::CProcedureICD9Set()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

CString CProcedureICD9Set::GetDefaultSQL()
{
	return "PROCEDUREICD9";
}

void CProcedureICD9Set::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "CodificaInterna", m_sCodificaInterna, 50);
		RFX_Text(pFX, "CodificaICD9Interni", m_sCodificaICD9Interni, 50);
		RFX_Text(pFX, "CodificaICD9Esterni", m_sCodificaICD9Esterni, 50);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CProcedureICD9Set::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sCodificaInterna = "";
	m_sCodificaICD9Interni = "";
	m_sCodificaICD9Esterni = "";
	m_lUO = 0;
	m_bEliminato = 0;
}

CString CProcedureICD9Set::GetFieldText(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CProcedureICD9Set::GetFieldText"))
	{
		if (!IsEOF())
			strReturn = m_sCodificaInterna + " - " + m_sCodificaICD9Interni + " - " + m_sCodificaICD9Esterni;
		strReturn.Trim();

		CloseRecordset("CProcedureICD9Set::GetFieldText");
	}

	return strReturn;
}

/*
CString CProcedureICD9Set::GetDescrizione(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CProcedureICD9Set::GetDescrizione"))
	{
		if (!IsEOF())
			strReturn = m_sDescrizione;

		CloseRecordset("CProcedureICD9Set::GetDescrizione");
	}

	return strReturn;
}
*/

CString CProcedureICD9Set::GetCodificaInterna(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CProcedureICD9Set::GetCodificaInterna"))
	{
		if (!IsEOF())
			strReturn = m_sCodificaInterna;

		CloseRecordset("CProcedureICD9Set::GetCodificaInterna");
	}

	return strReturn;
}

CString CProcedureICD9Set::GetCodificaICD9Interni(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CProcedureICD9Set::GetCodificaICD9Interni"))
	{
		if (!IsEOF())
			strReturn = m_sCodificaICD9Interni;

		CloseRecordset("CProcedureICD9Set::GetCodificaICD9Interni");
	}

	return strReturn;
}

CString CProcedureICD9Set::GetCodificaICD9Esterni(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CProcedureICD9Set::GetCodificaICD9Esterni"))
	{
		if (!IsEOF())
			strReturn = m_sCodificaICD9Esterni;

		CloseRecordset("CProcedureICD9Set::GetCodificaICD9Esterni");
	}

	return strReturn;
}

long CProcedureICD9Set::GetIdFromICD9(CString codiceICD9)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("CodificaICD9Esterni='%s'", codiceICD9);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CProcedureICD9Set::GetIdFromICD9"))
	{
		if (!IsEOF())
			lReturn = m_lID;

		CloseRecordset("CProcedureICD9Set::GetIdFromICD9");
	}

	return lReturn;
}

CBaseSet* CProcedureICD9Set::CreateNew()
{
	return (CBaseSet*)new CProcedureICD9Set;
}

void CProcedureICD9Set::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CProcedureICD9Set* pSet = (CProcedureICD9Set*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodificaInterna) || bCopyAll)
		m_sCodificaInterna = pSet->m_sCodificaInterna;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodificaICD9Interni) || bCopyAll)
		m_sCodificaICD9Interni = pSet->m_sCodificaICD9Interni;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodificaICD9Esterni) || bCopyAll)
		m_sCodificaICD9Esterni = pSet->m_sCodificaICD9Esterni;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
	
}

void CProcedureICD9Set::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CProcedureICD9Set* pOV = (CProcedureICD9Set*)pOldValues;
	CProcedureICD9Set* pNV = (CProcedureICD9Set*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("CodificaInterna", pOV, &pOV->m_sCodificaInterna, pNV, &pNV->m_sCodificaInterna);
	sp.Execute("CodificaICD9Interni", pOV, &pOV->m_sCodificaICD9Interni, pNV, &pNV->m_sCodificaICD9Interni);
	sp.Execute("CodificaICD9Esterni", pOV, &pOV->m_sCodificaICD9Esterni, pNV, &pNV->m_sCodificaICD9Esterni);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CProcedureICD9Set::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CProcedureICD9Set::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CProcedureICD9Set::DeleteRecordset");
	}
	return bReturn;
}

CString CProcedureICD9Set::SetBaseFilter(const CString &strFilter)
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
		
BOOL CProcedureICD9Set::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
