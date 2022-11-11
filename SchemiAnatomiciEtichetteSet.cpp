// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
#include "stdafx.h"
#include "Endox.h"
#include "SchemiAnatomiciEtichetteSet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSchemiAnatomiciEtichetteSet, CBaseSet)

CSchemiAnatomiciEtichetteSet::CSchemiAnatomiciEtichetteSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("ELIMINATO=0");
	SetEmpty();

	m_nFields = 10;
}

CString CSchemiAnatomiciEtichetteSet::GetDefaultSQL()
{
	return "SCHEMI_ANATOMICI_ETICHETTE";
}

void CSchemiAnatomiciEtichetteSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "ID_SCHEMI_ANATOMICI", m_lID_Schemi_Anatomici);
		RFX_Text(pFX, "DESCRIZIONE", m_sDescrizione);
		RFX_Long(pFX, "PUNTO_ALTO_SINISTRA_X", m_lPunto_Alto_Sinistra_X);
		RFX_Long(pFX, "PUNTO_ALTO_SINISTRA_Y", m_lPunto_Alto_Sinistra_Y);
		RFX_Long(pFX, "PUNTO_BASSO_DESTRA_X", m_lPunto_Basso_Destra_X);
		RFX_Long(pFX, "PUNTO_BASSO_DESTRA_Y", m_lPunto_Basso_Destra_Y);
		RFX_Long(pFX, "COLORE", m_lColore);
		RFX_Double(pFX, "ZOOM_FACTOR", m_dZoom_Factor);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);

		m_pSchemiAnatomiciEtichette.m_lID = m_lID;
		m_pSchemiAnatomiciEtichette.m_lID_Schemi_Anatomici = m_lID_Schemi_Anatomici;
		m_pSchemiAnatomiciEtichette.m_sDescrizione = m_sDescrizione;
		m_pSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_X = m_lPunto_Alto_Sinistra_X;
		m_pSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_Y = m_lPunto_Alto_Sinistra_Y;
		m_pSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_X = m_lPunto_Basso_Destra_X;
		m_pSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_Y = m_lPunto_Basso_Destra_Y;
		m_pSchemiAnatomiciEtichette.m_lColore = m_lColore;
		m_pSchemiAnatomiciEtichette.m_dZoom_Factor = m_dZoom_Factor;
		m_pSchemiAnatomiciEtichette.m_bEliminato = m_bEliminato;
	}
}

void CSchemiAnatomiciEtichetteSet::SetEmpty()
{
	m_lID = 0;
	m_lID_Schemi_Anatomici = 0;
	m_sDescrizione = "";
	m_lPunto_Alto_Sinistra_X = 0;
	m_lPunto_Alto_Sinistra_Y = 0;
	m_lPunto_Basso_Destra_X = 0;
	m_lPunto_Basso_Destra_Y = 0;
	m_lColore = 0;
	m_dZoom_Factor = 0;
	m_bEliminato = FALSE;

	m_pSchemiAnatomiciEtichette.m_lID = 0;
	m_pSchemiAnatomiciEtichette.m_lID_Schemi_Anatomici = 0;
	m_pSchemiAnatomiciEtichette.m_sDescrizione = "";
	m_pSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_X = 0;
	m_pSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_Y = 0;
	m_pSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_X = 0;
	m_pSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_Y = 0;
	m_pSchemiAnatomiciEtichette.m_lColore = 0;
	m_pSchemiAnatomiciEtichette.m_dZoom_Factor = 0;
	m_pSchemiAnatomiciEtichette.m_bEliminato = FALSE;
}

CBaseSet* CSchemiAnatomiciEtichetteSet::CreateNew()
{
	return (CBaseSet*)new CSchemiAnatomiciEtichetteSet;
}

void CSchemiAnatomiciEtichetteSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CSchemiAnatomiciEtichetteSet* pSet = (CSchemiAnatomiciEtichetteSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lID_Schemi_Anatomici) || bCopyAll)
		m_lID_Schemi_Anatomici = pSet->m_lID_Schemi_Anatomici;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPunto_Alto_Sinistra_X) || bCopyAll)
		m_lPunto_Alto_Sinistra_X = pSet->m_lPunto_Alto_Sinistra_X;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPunto_Alto_Sinistra_Y) || bCopyAll)
		m_lPunto_Alto_Sinistra_Y = pSet->m_lPunto_Alto_Sinistra_Y;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPunto_Basso_Destra_X) || bCopyAll)
		m_lPunto_Basso_Destra_X = pSet->m_lPunto_Basso_Destra_X;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPunto_Basso_Destra_Y) || bCopyAll)
		m_lPunto_Basso_Destra_Y = pSet->m_lPunto_Basso_Destra_Y;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lColore) || bCopyAll)
		m_lColore = pSet->m_lColore;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_dZoom_Factor) || bCopyAll)
		m_dZoom_Factor = pSet->m_dZoom_Factor;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CSchemiAnatomiciEtichetteSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CSchemiAnatomiciEtichetteSet* pOV = (CSchemiAnatomiciEtichetteSet*)pOldValues;
	CSchemiAnatomiciEtichetteSet* pNV = (CSchemiAnatomiciEtichetteSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("ID_SCHEMI_ANATOMICI", pOV, &pOV->m_lID_Schemi_Anatomici, pNV, &pNV->m_lID_Schemi_Anatomici);
	sp.Execute("DESCRIZIONE", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("PUNTO_ALTO_SINISTRA_X", pOV, &pOV->m_lPunto_Alto_Sinistra_X, pNV, &pNV->m_lPunto_Alto_Sinistra_X);
	sp.Execute("PUNTO_ALTO_SINISTRA_Y", pOV, &pOV->m_lPunto_Alto_Sinistra_Y, pNV, &pNV->m_lPunto_Alto_Sinistra_Y);
	sp.Execute("PUNTO_BASSO_DESTRA_X", pOV, &pOV->m_lPunto_Basso_Destra_X, pNV, &pNV->m_lPunto_Basso_Destra_X);
	sp.Execute("PUNTO_BASSO_DESTRA_Y", pOV, &pOV->m_lPunto_Basso_Destra_Y, pNV, &pNV->m_lPunto_Basso_Destra_Y);
	sp.Execute("COLORE", pOV, &pOV->m_lColore, pNV, &pNV->m_lColore);
	sp.Execute("ZOOM_FACTOR", pOV, &pOV->m_dZoom_Factor, pNV, &pNV->m_dZoom_Factor);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CSchemiAnatomiciEtichetteSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CSchemiAnatomiciEtichetteSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CSchemiAnatomiciEtichetteSet::DeleteRecordset");
	}
	return bReturn;
}

CString CSchemiAnatomiciEtichetteSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	//CString strUO;
	//strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		//strNewFilter = strUO + " AND ELIMINATO=0";
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		//if (strNewFilter.Find("UO=") < 0)
		//	strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CSchemiAnatomiciEtichetteSet::UpdateRecordset(const CString &strCommento)
{
	//if (m_nEditMode == addnew)
	//	m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

BOOL CSchemiAnatomiciEtichetteSet::SoftRefreshData(CSchemiAnatomiciEtichette* p_pSchemiAnatomiciEtichette)
{
	if (p_pSchemiAnatomiciEtichette == NULL || !IsOpen())
		return FALSE;

	p_pSchemiAnatomiciEtichette->m_lID = m_pSchemiAnatomiciEtichette.m_lID;
	p_pSchemiAnatomiciEtichette->m_lID_Schemi_Anatomici = m_pSchemiAnatomiciEtichette.m_lID_Schemi_Anatomici;
	p_pSchemiAnatomiciEtichette->m_sDescrizione = m_pSchemiAnatomiciEtichette.m_sDescrizione;
	p_pSchemiAnatomiciEtichette->m_lPunto_Alto_Sinistra_X = m_pSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_X;
	p_pSchemiAnatomiciEtichette->m_lPunto_Alto_Sinistra_Y = m_pSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_Y;
	p_pSchemiAnatomiciEtichette->m_lPunto_Basso_Destra_X = m_pSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_X;
	p_pSchemiAnatomiciEtichette->m_lPunto_Basso_Destra_Y = m_pSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_Y;
	p_pSchemiAnatomiciEtichette->m_lColore = m_pSchemiAnatomiciEtichette.m_lColore;
	p_pSchemiAnatomiciEtichette->m_dZoom_Factor = m_pSchemiAnatomiciEtichette.m_dZoom_Factor;
	return TRUE;
}

BOOL CSchemiAnatomiciEtichetteSet::Find(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CSchemiAnatomiciEtichetteSet::Find"))
	{
		if (!IsEOF())
		{
			bReturn = TRUE;
			//DoFieldExchange();
		}
		CloseRecordset("CSchemiAnatomiciEtichetteSet::Find");
	}
	return bReturn;
}

// must return a list
BOOL CSchemiAnatomiciEtichetteSet::FindByFatherID(long p_lID_Schemi_Anatomici)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID_SCHEMI_ANATOMICI=%li", p_lID_Schemi_Anatomici);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CSchemiAnatomiciEtichetteSet::Find"))
	{
		if (!IsEOF())
		{
			bReturn = TRUE;
			//DoFieldExchange();
		}
		CloseRecordset("CSchemiAnatomiciEtichetteSet::Find");
	}
	return bReturn;
}