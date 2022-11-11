#include "stdafx.h"
#include "Endox.h"
#include "MstComplicanze2Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstComplicanze2Set, CBaseSet)

CMstComplicanze2Set::CMstComplicanze2Set()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

void CMstComplicanze2Set::DoFieldExchange(CFieldExchange* pFX)
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

CString CMstComplicanze2Set::GetDefaultSQL()
{
	return "EMSTComplicanze2";
}

void CMstComplicanze2Set::SetEmpty()
{
	m_lID = 0;
	m_lPadre = 0;
	m_lLivello = 0;
	m_sDescrizione = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CMstComplicanze2Set::CreateNew()
{
	return (CBaseSet*)new CMstComplicanze2Set;
}

void CMstComplicanze2Set::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMstComplicanze2Set* pSet = (CMstComplicanze2Set*)pOriginalSet;

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

void CMstComplicanze2Set::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMstComplicanze2Set* pOV = (CMstComplicanze2Set*)pOldValues;
	CMstComplicanze2Set* pNV = (CMstComplicanze2Set*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Padre", pOV, &pOV->m_lPadre, pNV, &pNV->m_lPadre);
	sp.Execute("Livello", pOV, &pOV->m_lLivello, pNV, &pNV->m_lLivello);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMstComplicanze2Set::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMstComplicanze2Set::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMstComplicanze2Set::DeleteRecordset");
	}
	return bReturn;
}

CString CMstComplicanze2Set::SetBaseFilter(const CString &strFilter)
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
		
BOOL CMstComplicanze2Set::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
