#include "stdafx.h"
#include "Endox.h"
#include "EndoGridCLGruppiUtenteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridCLGruppiUtenteSet, CBaseSet)

CEndoGridCLGruppiUtenteSet::CEndoGridCLGruppiUtenteSet(CDatabase* pDatabase)
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

void CEndoGridCLGruppiUtenteSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEtichetta = 0;
	m_lIDGruppo = 0;
	m_bEliminato = FALSE;
}

void CEndoGridCLGruppiUtenteSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, _T("ID"), m_lID);

	if (m_nFields > 1)
	{
		RFX_Long(pFX, _T("IDETICHETTA_GRIDCL"), m_lIDEtichetta);
		RFX_Long(pFX, _T("IDGRUPPO"), m_lIDGruppo);
		RFX_Bool(pFX, _T("ELIMINATO"), m_bEliminato);
	}
}

CString CEndoGridCLGruppiUtenteSet::GetDefaultSQL()
{
	return _T("GRIDCL_GRUPPIUTENTE");
}

BOOL CEndoGridCLGruppiUtenteSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEndoGridCLGruppiUtenteSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEndoGridCLGruppiUtenteSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEndoGridCLGruppiUtenteSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CEndoGridCLGruppiUtenteSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

CBaseSet* CEndoGridCLGruppiUtenteSet::CreateNew()
{
	return (CBaseSet*)new CEndoGridCLGruppiUtenteSet;
}

void CEndoGridCLGruppiUtenteSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEndoGridCLGruppiUtenteSet* pSet = (CEndoGridCLGruppiUtenteSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEtichetta) || bCopyAll)
		m_lIDEtichetta = pSet->m_lIDEtichetta;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = pSet->m_lIDGruppo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEndoGridCLGruppiUtenteSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEndoGridCLGruppiUtenteSet* pOV = (CEndoGridCLGruppiUtenteSet*)pOldValues;
	CEndoGridCLGruppiUtenteSet* pNV = (CEndoGridCLGruppiUtenteSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDETICHETTA_GRIDCL", pOV, &pOV->m_lIDEtichetta, pNV, &pNV->m_lIDEtichetta);
	sp.Execute("IDGRUPPO", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);	
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}