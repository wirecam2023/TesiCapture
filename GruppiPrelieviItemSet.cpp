#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrelieviItemSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrelieviItemSet, CBaseSet)

CGruppiPrelieviItemSet::CGruppiPrelieviItemSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

void CGruppiPrelieviItemSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDGruppo", m_lIDGruppo);
		RFX_Long(pFX, "IDIntervento", m_lIDIntervento);
		RFX_Long(pFX, "Prelievi", m_lPrelievi);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CGruppiPrelieviItemSet::GetDefaultSQL()
{
	return "GRUPPIPRELIEVIITEM";
}

void CGruppiPrelieviItemSet::SetEmpty()
{
	m_lID = 0;
	m_lIDGruppo = 0;
	m_lIDIntervento = 0;
	m_lPrelievi = 0;
	m_sDescrizione = "";
	m_bEliminato = FALSE;
}

CBaseSet* CGruppiPrelieviItemSet::CreateNew()
{
	return (CBaseSet*)new CGruppiPrelieviItemSet;
}

void CGruppiPrelieviItemSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CGruppiPrelieviItemSet* pSet = (CGruppiPrelieviItemSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = pSet->m_lIDGruppo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDIntervento) || bCopyAll)
		m_lIDIntervento = pSet->m_lIDIntervento;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPrelievi) || bCopyAll)
		m_lPrelievi = pSet->m_lPrelievi;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CGruppiPrelieviItemSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CGruppiPrelieviItemSet* pOV = (CGruppiPrelieviItemSet*)pOldValues;
	CGruppiPrelieviItemSet* pNV = (CGruppiPrelieviItemSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDGruppo", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);
	sp.Execute("IDIntervento", pOV, &pOV->m_lIDIntervento, pNV, &pNV->m_lIDIntervento);
	sp.Execute("Prelievi", pOV, &pOV->m_lPrelievi, pNV, &pNV->m_lPrelievi);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CGruppiPrelieviItemSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CGruppiPrelieviItemSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CGruppiPrelieviItemSet::DeleteRecordset");
	}
	return bReturn;
}

CString CGruppiPrelieviItemSet::SetBaseFilter(const CString &strFilter)
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