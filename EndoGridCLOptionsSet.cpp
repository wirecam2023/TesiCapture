#include "stdafx.h"
#include "Endox.h"
#include "EndoGridCLOptionsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridCLOptionsSet, CBaseSet)

CEndoGridCLOptionsSet::CEndoGridCLOptionsSet(void)
: CBaseSet(&m_lId, "ID")
{

	m_lId = 0;
	m_sGridIdentifier = "";
	m_fDividerPos = 0.0;
	m_lUO = 0;
	m_bEliminato = FALSE;

	SetBaseFilter("");

	m_nFields = 5;
}

CEndoGridCLOptionsSet::~CEndoGridCLOptionsSet(void)
{
}

void CEndoGridCLOptionsSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, "ID", m_lId);
	RFX_Text(pFX, "GRIDIDENTIFIER", m_sGridIdentifier, 50);
	RFX_Single(pFX, _T("DIVIDERPOS"), m_fDividerPos);
	RFX_Long(pFX, "UO", m_lUO);
	RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
}

CString CEndoGridCLOptionsSet::GetDefaultSQL()
{
	return _T("GRIDCL_OPTIONS");
}

BOOL CEndoGridCLOptionsSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEndoGridCLOptionsSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEndoGridCLOptionsSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEndoGridCLOptionsSet::SetBaseFilter(const CString &strFilter)
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

BOOL CEndoGridCLOptionsSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

CBaseSet* CEndoGridCLOptionsSet::CreateNew()
{
	return (CBaseSet*)new CEndoGridCLOptionsSet;
}

void CEndoGridCLOptionsSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEndoGridCLOptionsSet* pSet = (CEndoGridCLOptionsSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sGridIdentifier) || bCopyAll)
		m_sGridIdentifier = pSet->m_sGridIdentifier;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fDividerPos) || bCopyAll)
		m_fDividerPos = pSet->m_fDividerPos;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEndoGridCLOptionsSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEndoGridCLOptionsSet* pOV = (CEndoGridCLOptionsSet*)pOldValues;
	CEndoGridCLOptionsSet* pNV = (CEndoGridCLOptionsSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("GRIDIDENTIFIER", pOV, &pOV->m_sGridIdentifier, pNV, &pNV->m_sGridIdentifier);
	sp.Execute("DIVIDERPOS", pOV, &pOV->m_fDividerPos, pNV, &pNV->m_fDividerPos);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}