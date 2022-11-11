#include "stdafx.h"
#include "Endox.h"
#include "HeaderFooterSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CHeaderFooterSet, CBaseSet)

CHeaderFooterSet::CHeaderFooterSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

void CHeaderFooterSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 50);
		RFX_Long(pFX, "Tipo", m_lTipo);
		RFX_Long(pFX, "Altezza", m_lAltezza);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CHeaderFooterSet::GetDefaultSQL()
{
	return "HEADERFOOTER";
}

void CHeaderFooterSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lTipo = 0;
	m_lAltezza = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CHeaderFooterSet::CreateNew()
{
	return (CBaseSet*)new CHeaderFooterSet;
}

void CHeaderFooterSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CHeaderFooterSet* pSet = (CHeaderFooterSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTipo) || bCopyAll)
		m_lTipo = pSet->m_lTipo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lAltezza) || bCopyAll)
		m_lAltezza = pSet->m_lAltezza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CHeaderFooterSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CHeaderFooterSet* pOV = (CHeaderFooterSet*)pOldValues;
	CHeaderFooterSet* pNV = (CHeaderFooterSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Tipo", pOV, &pOV->m_lTipo, pNV, &pNV->m_lTipo);
	sp.Execute("Altezza", pOV, &pOV->m_lAltezza, pNV, &pNV->m_lAltezza);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CHeaderFooterSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CHeaderFooterSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CHeaderFooterSet::DeleteRecordset");
	}
	return bReturn;
}

CString CHeaderFooterSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	/*
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
	*/

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

BOOL CHeaderFooterSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

long CHeaderFooterSet::AddRow(CString sDescrizione, long lTipo, long lAltezza)
{
	long lReturn = 0;

	SetOpenFilter("ID=0");
	if (OpenRecordset("CHeaderFooterSet::AddRow"))
	{
		if (AddNewRecordset("CHeaderFooterSet::AddRow"))
		{
			m_sDescrizione = sDescrizione;
			m_lTipo = lTipo;
			m_lAltezza = lAltezza;

			if (UpdateRecordset("CHeaderFooterSet::AddRow"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CHeaderFooterSet::AddRow");
	}

	return lReturn;
}

void CHeaderFooterSet::DelRow(long lID)
{
	if (lID > 0)
	{
		CString sFilter;
		sFilter.Format("ID=%li", lID);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CHeaderFooterSet::DelRow"))
		{
			if (!IsEOF())
				DeleteRecordset("CHeaderFooterSet::DelRow");

			CloseRecordset("CHeaderFooterSet::DelRow");
		}
	}
}