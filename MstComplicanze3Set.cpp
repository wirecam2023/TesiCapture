#include "stdafx.h"
#include "Endox.h"
#include "MstComplicanze3Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstComplicanze3Set, CBaseSet)

CMstComplicanze3Set::CMstComplicanze3Set()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

void CMstComplicanze3Set::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Padre", m_lPadre);
		RFX_Long(pFX, "Livello", m_lLivello);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CMstComplicanze3Set::GetDefaultSQL()
{
	return "EMSTComplicanze3";
}

void CMstComplicanze3Set::SetEmpty()
{
	m_lID = 0;
	m_lPadre = 0;
	m_lLivello = 0;
	m_sDescrizione = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CMstComplicanze3Set::CreateNew()
{
	return (CBaseSet*)new CMstComplicanze3Set;
}

void CMstComplicanze3Set::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMstComplicanze3Set* pSet = (CMstComplicanze3Set*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPadre) || bCopyAll)
		m_lPadre = pSet->m_lPadre;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lLivello) || bCopyAll)
		m_lLivello = pSet->m_lLivello;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CMstComplicanze3Set::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMstComplicanze3Set* pOV = (CMstComplicanze3Set*)pOldValues;
	CMstComplicanze3Set* pNV = (CMstComplicanze3Set*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Padre", pOV, &pOV->m_lPadre, pNV, &pNV->m_lPadre);
	sp.Execute("Livello", pOV, &pOV->m_lLivello, pNV, &pNV->m_lLivello);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMstComplicanze3Set::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMstComplicanze3Set::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMstComplicanze3Set::DeleteRecordset");
	}
	return bReturn;
}

CString CMstComplicanze3Set::SetBaseFilter(const CString &strFilter)
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
		
BOOL CMstComplicanze3Set::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
