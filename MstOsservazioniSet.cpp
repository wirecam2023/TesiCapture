#include "stdafx.h"
#include "Endox.h"
#include "MstOsservazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstOsservazioniSet, CBaseSet)

CMstOsservazioniSet::CMstOsservazioniSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	m_lContatore	= 0;
	m_lOrgano		= 0;
	m_lPadre		= 0;
	m_lLivello		= 0;
	m_sDescrizione	= "";
	m_bEliminato    = FALSE;

	m_nFields = 6;
	SetBaseFilter("");
}

void CMstOsservazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore",		m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "Organo",		m_lOrgano);
		RFX_Long (pFX, "Padre",			m_lPadre);
		RFX_Long (pFX, "Livello",		m_lLivello);
		RFX_Text (pFX, "Descrizione",	m_sDescrizione,		255);
		RFX_Bool (pFX, "Eliminato",     m_bEliminato);
	}
}

CString CMstOsservazioniSet::GetDefaultSQL()
{
	return "EMSTOSSERVAZIONI";
}

void CMstOsservazioniSet::SetEmpty()
{
	m_lOrgano = 0;
	m_lPadre = 0;
	m_lLivello = 0;
	m_sDescrizione = "";
	m_bEliminato = FALSE;
}

CBaseSet* CMstOsservazioniSet::CreateNew()
{
	return (CBaseSet*)new CMstOsservazioniSet;
}

void CMstOsservazioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMstOsservazioniSet* pMstOsservazioniSet = (CMstOsservazioniSet*)pOriginalSet;

	if (!pMstOsservazioniSet->IsOpen() || pMstOsservazioniSet->IsFieldDirty(&pMstOsservazioniSet->m_lOrgano) || bCopyAll)
		m_lOrgano = pMstOsservazioniSet->m_lOrgano;
	if (!pMstOsservazioniSet->IsOpen() || pMstOsservazioniSet->IsFieldDirty(&pMstOsservazioniSet->m_lPadre) || bCopyAll)
		m_lPadre = pMstOsservazioniSet->m_lPadre;
	if (!pMstOsservazioniSet->IsOpen() || pMstOsservazioniSet->IsFieldDirty(&pMstOsservazioniSet->m_lLivello) || bCopyAll)
		m_lLivello = pMstOsservazioniSet->m_lLivello;
	if (!pMstOsservazioniSet->IsOpen() || pMstOsservazioniSet->IsFieldDirty(&pMstOsservazioniSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pMstOsservazioniSet->m_sDescrizione;
	if (!pMstOsservazioniSet->IsOpen() || pMstOsservazioniSet->IsFieldDirty(&pMstOsservazioniSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pMstOsservazioniSet->m_bEliminato;
}

void CMstOsservazioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMstOsservazioniSet* pOV = (CMstOsservazioniSet*)pOldValues;
	CMstOsservazioniSet* pNV = (CMstOsservazioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Organo", pOV, &pOV->m_lOrgano, pNV, &pNV->m_lOrgano);
	sp.Execute("Padre", pOV, &pOV->m_lPadre, pNV, &pNV->m_lPadre);
	sp.Execute("Livello", pOV, &pOV->m_lLivello, pNV, &pNV->m_lLivello);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMstOsservazioniSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMstOsservazioniSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMstOsservazioniSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMstOsservazioniSet::SetBaseFilter(const CString &strFilter)
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