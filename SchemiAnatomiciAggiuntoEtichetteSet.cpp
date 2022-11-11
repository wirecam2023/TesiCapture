// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
#include "stdafx.h"
#include "Endox.h"
#include "SchemiAnatomiciAggiuntoEtichetteSet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSchemiAnatomiciAggiuntoEtichetteSet, CBaseSet)

CSchemiAnatomiciAggiuntoEtichetteSet::CSchemiAnatomiciAggiuntoEtichetteSet()
: CBaseSet(&m_lCONTATORE, "CONTATORE")
{
	SetBaseFilter("ELIMINATO=0");
	SetEmpty();

	m_nFields = 10;
}

CString CSchemiAnatomiciAggiuntoEtichetteSet::GetDefaultSQL()
{
	return "SCHEMI_ANATOMICI_AGGIUNTO_ETICHETTE";
}

void CSchemiAnatomiciAggiuntoEtichetteSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "CONTATORE", m_lCONTATORE);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "ID_SCHEMI_ANATOMICI_AGGIUNTO", m_lID_SCHEMI_ANATOMICI_AGGIUNTO);
		RFX_Long(pFX, "ID_SCHEMI_ANATOMICI_ETICHETTE", m_lID_SCHEMI_ANATOMICI_ETICHETTE);
		RFX_Text(pFX, "DESCRIZIONE", m_sDESCRIZIONE);
		RFX_Long(pFX, "PUNTO_ALTO_SINISTRA_X", m_lPUNTO_ALTO_SINISTRA_X);
		RFX_Long(pFX, "PUNTO_ALTO_SINISTRA_Y", m_lPUNTO_ALTO_SINISTRA_Y);
		RFX_Long(pFX, "PUNTO_BASSO_DESTRA_X",  m_lPUNTO_BASSO_DESTRA_X);
		RFX_Long(pFX, "PUNTO_BASSO_DESTRA_Y",  m_lPUNTO_BASSO_DESTRA_Y);
		RFX_Long(pFX, "COLORE", m_lCOLORE);
		RFX_Bool(pFX, "ELIMINATO", m_bELIMINATO);
	}
}

void CSchemiAnatomiciAggiuntoEtichetteSet::SetEmpty()
{
	m_lCONTATORE = 0;
	m_lID_SCHEMI_ANATOMICI_AGGIUNTO = 0;
	m_lID_SCHEMI_ANATOMICI_ETICHETTE = 0;
	m_sDESCRIZIONE = "";
	m_lPUNTO_ALTO_SINISTRA_X = 0;
	m_lPUNTO_ALTO_SINISTRA_Y = 0;
	m_lPUNTO_BASSO_DESTRA_X = 0;
	m_lPUNTO_BASSO_DESTRA_Y = 0;
	m_lCOLORE = 0;
	m_bELIMINATO = FALSE;
}

CBaseSet* CSchemiAnatomiciAggiuntoEtichetteSet::CreateNew()
{
	return (CBaseSet*)new CSchemiAnatomiciAggiuntoEtichetteSet;
}

void CSchemiAnatomiciAggiuntoEtichetteSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CSchemiAnatomiciAggiuntoEtichetteSet* pSet = (CSchemiAnatomiciAggiuntoEtichetteSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lID_SCHEMI_ANATOMICI_AGGIUNTO) || bCopyAll)
		m_lID_SCHEMI_ANATOMICI_AGGIUNTO = pSet->m_lID_SCHEMI_ANATOMICI_AGGIUNTO;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lID_SCHEMI_ANATOMICI_ETICHETTE) || bCopyAll)
		m_lID_SCHEMI_ANATOMICI_ETICHETTE = pSet->m_lID_SCHEMI_ANATOMICI_ETICHETTE;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDESCRIZIONE) || bCopyAll)
		m_sDESCRIZIONE = pSet->m_sDESCRIZIONE;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPUNTO_ALTO_SINISTRA_X) || bCopyAll)
		m_lPUNTO_ALTO_SINISTRA_X = pSet->m_lPUNTO_ALTO_SINISTRA_X;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPUNTO_ALTO_SINISTRA_Y) || bCopyAll)
		m_lPUNTO_ALTO_SINISTRA_Y = pSet->m_lPUNTO_ALTO_SINISTRA_Y;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPUNTO_BASSO_DESTRA_X) || bCopyAll)
		m_lPUNTO_BASSO_DESTRA_X = pSet->m_lPUNTO_BASSO_DESTRA_X;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPUNTO_BASSO_DESTRA_Y) || bCopyAll)
		m_lPUNTO_BASSO_DESTRA_Y = pSet->m_lPUNTO_BASSO_DESTRA_Y;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lCOLORE) || bCopyAll)
		m_lCOLORE = pSet->m_lCOLORE;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bELIMINATO) || bCopyAll)
		m_bELIMINATO = pSet->m_bELIMINATO;
}

void CSchemiAnatomiciAggiuntoEtichetteSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CSchemiAnatomiciAggiuntoEtichetteSet* pOV = (CSchemiAnatomiciAggiuntoEtichetteSet*)pOldValues;
	CSchemiAnatomiciAggiuntoEtichetteSet* pNV = (CSchemiAnatomiciAggiuntoEtichetteSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("ID_SCHEMI_ANATOMICI", pOV, &pOV->m_lID_SCHEMI_ANATOMICI_AGGIUNTO, pNV, &pNV->m_lID_SCHEMI_ANATOMICI_AGGIUNTO);
	sp.Execute("DESCRIZIONE", pOV, &pOV->m_lID_SCHEMI_ANATOMICI_ETICHETTE, pNV, &pNV->m_lID_SCHEMI_ANATOMICI_ETICHETTE);
	sp.Execute("PUNTO_ALTO_SINISTRA_X", pOV, &pOV->m_lPUNTO_ALTO_SINISTRA_X, pNV, &pNV->m_lPUNTO_ALTO_SINISTRA_X);
	sp.Execute("PUNTO_ALTO_SINISTRA_Y", pOV, &pOV->m_lPUNTO_ALTO_SINISTRA_Y, pNV, &pNV->m_lPUNTO_ALTO_SINISTRA_Y);
	sp.Execute("PUNTO_BASSO_DESTRA_X", pOV,  &pOV->m_lPUNTO_BASSO_DESTRA_X, pNV,  &pNV->m_lPUNTO_BASSO_DESTRA_X);
	sp.Execute("PUNTO_BASSO_DESTRA_Y", pOV,  &pOV->m_lPUNTO_BASSO_DESTRA_Y, pNV,  &pNV->m_lPUNTO_BASSO_DESTRA_Y);
	sp.Execute("COLORE", pOV, &pOV->m_lCOLORE, pNV, &pNV->m_lCOLORE);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bELIMINATO, pNV, &pNV->m_bELIMINATO);
}

BOOL CSchemiAnatomiciAggiuntoEtichetteSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CSchemiAnatomiciAggiuntoEtichetteSet::DeleteRecordset"))
	{
		m_bELIMINATO = TRUE;
		bReturn = UpdateRecordset("CSchemiAnatomiciAggiuntoEtichetteSet::DeleteRecordset");
	}
	return bReturn;
}

CString CSchemiAnatomiciAggiuntoEtichetteSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CSchemiAnatomiciAggiuntoEtichetteSet::UpdateRecordset(const CString &strCommento)
{
	//if (m_nEditMode == addnew)
	//	m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}


BOOL CSchemiAnatomiciAggiuntoEtichetteSet::Find(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CSchemiAnatomiciAggiuntoEtichetteSet::Find"))
	{
		if (!IsEOF())
		{
			bReturn = TRUE;
			//DoFieldExchange();
		}
		CloseRecordset("CSchemiAnatomiciAggiuntoEtichetteSet::Find");
	}
	return bReturn;
}

// must return a list
BOOL CSchemiAnatomiciAggiuntoEtichetteSet::FindByFatherID(long p_lID_Schemi_Anatomici)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID_SCHEMI_ANATOMICI=%li", p_lID_Schemi_Anatomici);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CSchemiAnatomiciAggiuntoEtichetteSet::Find"))
	{
		if (!IsEOF())
		{
			bReturn = TRUE;
			//DoFieldExchange();
		}
		CloseRecordset("CSchemiAnatomiciAggiuntoEtichetteSet::Find");
	}
	return bReturn;
}