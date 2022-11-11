#include "stdafx.h"
#include "Endox.h"
#include "FarmaciGruppiRicItemsSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFarmaciGruppiRicItemsSet, CBaseSet)

CFarmaciGruppiRicItemsSet::CFarmaciGruppiRicItemsSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CFarmaciGruppiRicItemsSet::GetDefaultSQL()
{
	return "FARMACIGRUPPIRICITEMS";
}

void CFarmaciGruppiRicItemsSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDGruppo", m_lIDGruppo);
		RFX_Long(pFX, "IDFarmaco", m_lIDFarmaco);
		RFX_Long(pFX, "Quantita", m_lQuantita);
		RFX_Text(pFX, "TestoLibero", m_sTestoLibero, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CFarmaciGruppiRicItemsSet::SetEmpty()
{
	m_lID = 0;
	m_lIDGruppo = 0;
	m_lIDFarmaco = 0;
	m_lQuantita = 1;
	m_sTestoLibero = "";
	m_bEliminato = 0;
}

CBaseSet* CFarmaciGruppiRicItemsSet::CreateNew()
{
	return (CBaseSet*)new CFarmaciGruppiRicItemsSet;
}

void CFarmaciGruppiRicItemsSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFarmaciGruppiRicItemsSet* pSet = (CFarmaciGruppiRicItemsSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = pSet->m_lIDGruppo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDFarmaco) || bCopyAll)
		m_lIDFarmaco = pSet->m_lIDFarmaco;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lQuantita) || bCopyAll)
		m_lQuantita = pSet->m_lQuantita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoLibero) || bCopyAll)
		m_sTestoLibero = pSet->m_sTestoLibero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CFarmaciGruppiRicItemsSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFarmaciGruppiRicItemsSet* pOV = (CFarmaciGruppiRicItemsSet*)pOldValues;
	CFarmaciGruppiRicItemsSet* pNV = (CFarmaciGruppiRicItemsSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDGruppo", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);
	sp.Execute("IDFarmaco", pOV, &pOV->m_lIDFarmaco, pNV, &pNV->m_lIDFarmaco);
	sp.Execute("Quantita", pOV, &pOV->m_lQuantita, pNV, &pNV->m_lQuantita);
	sp.Execute("TestoLibero", pOV, &pOV->m_sTestoLibero, pNV, &pNV->m_sTestoLibero);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFarmaciGruppiRicItemsSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CFarmaciGruppiRicItemsSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CFarmaciGruppiRicItemsSet::DeleteRecordset");
	}
	return bReturn;
}

CString CFarmaciGruppiRicItemsSet::SetBaseFilter(const CString &strFilter)
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

long CFarmaciGruppiRicItemsSet::GetIDFarmaco(long lID)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CFarmaciGruppiRicItemsSet::GetIDFarmaco"))
	{
		if (!IsEOF())
			lReturn = m_lIDFarmaco;

		CloseRecordset("CFarmaciGruppiRicItemsSet::GetIDFarmaco");
	}

	return lReturn;
}