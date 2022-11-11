#include "stdafx.h"
#include "Endox.h"
#include "DatabasesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDatabasesSet, CBaseSet)

CDatabasesSet::CDatabasesSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

void CDatabasesSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 50);
		RFX_Text(pFX, "OracleDriver", m_sOracleDriver, 255);
		RFX_Text(pFX, "ServerDBQ", m_sServerDBQ, 255);
		RFX_Text(pFX, "Username", m_sUsername, 255);
		RFX_Text(pFX, "Password", m_sPassword, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CDatabasesSet::GetDefaultSQL()
{
	return "Databases";
}

void CDatabasesSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sOracleDriver = "";
	m_sServerDBQ = "";
	m_sUsername = "";
	m_sPassword = "";
	m_bEliminato = FALSE;
}

CBaseSet* CDatabasesSet::CreateNew()
{
	return (CBaseSet*)new CDatabasesSet;
}

void CDatabasesSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CDatabasesSet* pSet = (CDatabasesSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sOracleDriver) || bCopyAll)
		m_sOracleDriver = pSet->m_sOracleDriver;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sServerDBQ) || bCopyAll)
		m_sServerDBQ = pSet->m_sServerDBQ;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUsername) || bCopyAll)
		m_sUsername = pSet->m_sUsername;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPassword) || bCopyAll)
		m_sPassword = pSet->m_sPassword;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CDatabasesSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CDatabasesSet* pOV = (CDatabasesSet*)pOldValues;
	CDatabasesSet* pNV = (CDatabasesSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("OracleDriver", pOV, &pOV->m_sOracleDriver, pNV, &pNV->m_sOracleDriver);
	sp.Execute("ServerDBQ", pOV, &pOV->m_sServerDBQ, pNV, &pNV->m_sServerDBQ);
	sp.Execute("Username", pOV, &pOV->m_sUsername, pNV, &pNV->m_sUsername);
	sp.Execute("Password", pOV, &pOV->m_sPassword, pNV, &pNV->m_sPassword);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CDatabasesSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CDatabasesSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CDatabasesSet::DeleteRecordset");
	}
	return bReturn;
}

CString CDatabasesSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}