#include "stdafx.h"
#include "Endox.h"
#include "MstIndicazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstIndicazioniSet, CBaseSet)

CMstIndicazioniSet::CMstIndicazioniSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	m_lContatore	= 0;
	m_lTipoEsame	= 0;
	m_lPadre		= 0;
	m_sDescrizione	= "";
	m_bEliminato    = FALSE;

	m_nFields = 5;
	SetBaseFilter("");
}

void CMstIndicazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore",		m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "TipoEsame",		m_lTipoEsame);
		RFX_Long (pFX, "Padre",			m_lPadre);
		RFX_Text (pFX, "Descrizione",	m_sDescrizione,		255);
		RFX_Bool (pFX, "Eliminato",     m_bEliminato);
	}
}

CString CMstIndicazioniSet::GetDefaultSQL()
{
	return "EMSTINDICAZIONI";
}

void CMstIndicazioniSet::SetEmpty()
{
	m_lTipoEsame = 0;
	m_lPadre = 0;
	m_sDescrizione = "";
	m_bEliminato = FALSE;
}

CBaseSet* CMstIndicazioniSet::CreateNew()
{
	return (CBaseSet*)new CMstIndicazioniSet;
}

void CMstIndicazioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMstIndicazioniSet* pMstIndicazioniSet = (CMstIndicazioniSet*)pOriginalSet;

	if (!pMstIndicazioniSet->IsOpen() || pMstIndicazioniSet->IsFieldDirty(&pMstIndicazioniSet->m_lTipoEsame) || bCopyAll)
		m_lTipoEsame = pMstIndicazioniSet->m_lTipoEsame;
	if (!pMstIndicazioniSet->IsOpen() || pMstIndicazioniSet->IsFieldDirty(&pMstIndicazioniSet->m_lPadre) || bCopyAll)
		m_lPadre = pMstIndicazioniSet->m_lPadre;
	if (!pMstIndicazioniSet->IsOpen() || pMstIndicazioniSet->IsFieldDirty(&pMstIndicazioniSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pMstIndicazioniSet->m_sDescrizione;
	if (!pMstIndicazioniSet->IsOpen() || pMstIndicazioniSet->IsFieldDirty(&pMstIndicazioniSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pMstIndicazioniSet->m_bEliminato;
}

void CMstIndicazioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMstIndicazioniSet* pOV = (CMstIndicazioniSet*)pOldValues;
	CMstIndicazioniSet* pNV = (CMstIndicazioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("TipoEsame", pOV, &pOV->m_lTipoEsame, pNV, &pNV->m_lTipoEsame);
	sp.Execute("Padre", pOV, &pOV->m_lPadre, pNV, &pNV->m_lPadre);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMstIndicazioniSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMstIndicazioniSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMstIndicazioniSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMstIndicazioniSet::SetBaseFilter(const CString &strFilter)
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