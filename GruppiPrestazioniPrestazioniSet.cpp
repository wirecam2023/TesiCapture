#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrestazioniPrestazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrestazioniPrestazioniSet, CBaseSet)

CGruppiPrestazioniPrestazioniSet::CGruppiPrestazioniPrestazioniSet()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 4;
	SetBaseFilter("");
}

void CGruppiPrestazioniPrestazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDGruppo", m_lIDGruppo);
		RFX_Long(pFX, "IDPrestazione", m_lIDPrestazione);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CGruppiPrestazioniPrestazioniSet::GetDefaultSQL()
{
	return "GRUPPIPRESTAZIONIPRESTAZIONI";
}

void CGruppiPrestazioniPrestazioniSet::SetEmpty()
{
	m_lID = 0;
	m_lIDGruppo = 0;
	m_lIDPrestazione = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CGruppiPrestazioniPrestazioniSet::CreateNew()
{
	return (CBaseSet*)new CGruppiPrestazioniPrestazioniSet;
}

void CGruppiPrestazioniPrestazioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CGruppiPrestazioniPrestazioniSet* pGruppiPrestazioniPrestazioniSet = (CGruppiPrestazioniPrestazioniSet*)pOriginalSet;

	if (!pGruppiPrestazioniPrestazioniSet->IsOpen() || pGruppiPrestazioniPrestazioniSet->IsFieldDirty(&pGruppiPrestazioniPrestazioniSet->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = pGruppiPrestazioniPrestazioniSet->m_lIDGruppo;
	if (!pGruppiPrestazioniPrestazioniSet->IsOpen() || pGruppiPrestazioniPrestazioniSet->IsFieldDirty(&pGruppiPrestazioniPrestazioniSet->m_lIDPrestazione) || bCopyAll)
		m_lIDPrestazione = pGruppiPrestazioniPrestazioniSet->m_lIDPrestazione;
	if (!pGruppiPrestazioniPrestazioniSet->IsOpen() || pGruppiPrestazioniPrestazioniSet->IsFieldDirty(&pGruppiPrestazioniPrestazioniSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pGruppiPrestazioniPrestazioniSet->m_bEliminato;
}

void CGruppiPrestazioniPrestazioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CGruppiPrestazioniPrestazioniSet* pOV = (CGruppiPrestazioniPrestazioniSet*)pOldValues;
	CGruppiPrestazioniPrestazioniSet* pNV = (CGruppiPrestazioniPrestazioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDGruppo", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);
	sp.Execute("IDPrestazione", pOV, &pOV->m_lIDPrestazione, pNV, &pNV->m_lIDPrestazione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CGruppiPrestazioniPrestazioniSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CGruppiPrestazioniPrestazioniSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CGruppiPrestazioniPrestazioniSet::DeleteRecordset");
	}
	return bReturn;
}

CString CGruppiPrestazioniPrestazioniSet::SetBaseFilter(const CString &strFilter)
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