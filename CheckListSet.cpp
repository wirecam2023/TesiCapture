#include "stdafx.h"
#include "Endox.h"
#include "CheckListSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCheckListSet, CBaseSet)

CCheckListSet::CCheckListSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 10;
}

CString CCheckListSet::GetDefaultSQL()
{
	return "CheckList";
}

void CCheckListSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Long(pFX, "Presentazione", m_lPresentazione);
		RFX_Bool(pFX, "ItemAlmenoUno", m_bItemAlmenoUno);
		RFX_Bool(pFX, "ItemPiuDiUno", m_bItemPiuDiUno);
		RFX_Long(pFX, "CampoCL", m_lCampoCL);
		RFX_Long(pFX, "Ordine", m_lOrdine);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CCheckListSet::SetEmpty()
{
	m_lID = 0;
	m_sCodice = "";
	m_sDescrizione = "";
	m_lPresentazione = 0;
	m_bItemAlmenoUno = FALSE;
	m_bItemPiuDiUno = FALSE;
	m_lCampoCL = -1;
	m_lOrdine = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

BOOL CCheckListSet::GetEspansa(long lID)
{
	BOOL bReturn = TRUE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCheckListSet::GetEspansa"))
	{
		if (!IsEOF())
			bReturn = (m_lPresentazione == 0);

		CloseRecordset("CCheckListSet::GetEspansa");
	}

	return bReturn;
}

/*
BOOL CCheckListSet::GetSceltaMultipla(long lID)
{
	BOOL bReturn = TRUE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCheckListSet::GetSceltaMultipla"))
	{
		if (!IsEOF())
			bReturn = m_bItemPiuDiUno;

		CloseRecordset("CCheckListSet::GetSceltaMultipla");
	}

	return bReturn;
}
*/

CString CCheckListSet::GetStringCodice(long lID)
{
	CString strReturn;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCheckListSet::GetStringCodice"))
	{
		if (!IsEOF())
			strReturn = m_sCodice;

		CloseRecordset("CCheckListSet::GetStringCodice");
	}

	return strReturn;
}

CString CCheckListSet::GetStringDescrizione(long lID)
{
	CString strReturn;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCheckListSet::GetStringDescrizione"))
	{
		if (!IsEOF())
			strReturn = m_sDescrizione;

		CloseRecordset("CCheckListSet::GetStringDescrizione");
	}

	return strReturn;
}

CBaseSet* CCheckListSet::CreateNew()
{
	CCheckListSet* pNewSet = new CCheckListSet;

	return (CBaseSet*)pNewSet;
}

void CCheckListSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCheckListSet* pSet = (CCheckListSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPresentazione) || bCopyAll)
		m_lPresentazione = pSet->m_lPresentazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bItemAlmenoUno) || bCopyAll)
		m_bItemAlmenoUno = pSet->m_bItemAlmenoUno;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bItemPiuDiUno) || bCopyAll)
		m_bItemPiuDiUno = pSet->m_bItemPiuDiUno;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lCampoCL) || bCopyAll)
		m_lCampoCL = pSet->m_lCampoCL;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCheckListSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCheckListSet* pOV = (CCheckListSet*)pOldValues;
	CCheckListSet* pNV = (CCheckListSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Presentazione", pOV, &pOV->m_lPresentazione, pNV, &pNV->m_lPresentazione);
	sp.Execute("ItemAlmenoUno", pOV, &pOV->m_bItemAlmenoUno, pNV, &pNV->m_bItemAlmenoUno);
	sp.Execute("ItemPiuDiUno", pOV, &pOV->m_bItemPiuDiUno, pNV, &pNV->m_bItemPiuDiUno);
	sp.Execute("CampoCL", pOV, &pOV->m_lCampoCL, pNV, &pNV->m_lCampoCL);
	sp.Execute("Ordine", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCheckListSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCheckListSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCheckListSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCheckListSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CCheckListSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
