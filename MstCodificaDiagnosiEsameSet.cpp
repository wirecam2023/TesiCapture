#include "stdafx.h"
#include "Endox.h"
#include "MstCodificaDiagnosiEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstCodificaDiagnosiEsameSet, CBaseSet)

CMstCodificaDiagnosiEsameSet::CMstCodificaDiagnosiEsameSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	m_lContatore	= 0;
	m_lTipoEsame	= 0;
	m_lPadre		= 0;
	m_lLivello		= 0;
	m_sDescrizione	= "";
	m_bEliminato    = FALSE;

	m_nFields = 6;
	SetBaseFilter("");
}

void CMstCodificaDiagnosiEsameSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore",		m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "TipoEsame",		m_lTipoEsame);
		RFX_Long (pFX, "Padre",			m_lPadre);
		RFX_Long (pFX, "Livello",		m_lLivello);
		RFX_Text (pFX, "Descrizione",	m_sDescrizione,		255);
		RFX_Bool (pFX, "Eliminato",     m_bEliminato);
	}
}

CString CMstCodificaDiagnosiEsameSet::GetDefaultSQL()
{
	return "EMSTCODIFICADIAGNOSIESAME";
}

void CMstCodificaDiagnosiEsameSet::SetEmpty()
{
	m_lTipoEsame = 0;
	m_lPadre = 0;
	m_lLivello = 0;
	m_sDescrizione = "";
	m_bEliminato = FALSE;
}

CBaseSet* CMstCodificaDiagnosiEsameSet::CreateNew()
{
	return (CBaseSet*)new CMstCodificaDiagnosiEsameSet;
}

void CMstCodificaDiagnosiEsameSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMstCodificaDiagnosiEsameSet* pMstCodificaDiagnosiEsameSet = (CMstCodificaDiagnosiEsameSet*)pOriginalSet;

	if (!pMstCodificaDiagnosiEsameSet->IsOpen() || pMstCodificaDiagnosiEsameSet->IsFieldDirty(&pMstCodificaDiagnosiEsameSet->m_lTipoEsame) || bCopyAll)
		m_lTipoEsame = pMstCodificaDiagnosiEsameSet->m_lTipoEsame;
	if (!pMstCodificaDiagnosiEsameSet->IsOpen() || pMstCodificaDiagnosiEsameSet->IsFieldDirty(&pMstCodificaDiagnosiEsameSet->m_lPadre) || bCopyAll)
		m_lPadre = pMstCodificaDiagnosiEsameSet->m_lPadre;
	if (!pMstCodificaDiagnosiEsameSet->IsOpen() || pMstCodificaDiagnosiEsameSet->IsFieldDirty(&pMstCodificaDiagnosiEsameSet->m_lLivello) || bCopyAll)
		m_lLivello = pMstCodificaDiagnosiEsameSet->m_lLivello;
	if (!pMstCodificaDiagnosiEsameSet->IsOpen() || pMstCodificaDiagnosiEsameSet->IsFieldDirty(&pMstCodificaDiagnosiEsameSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pMstCodificaDiagnosiEsameSet->m_sDescrizione;
	if (!pMstCodificaDiagnosiEsameSet->IsOpen() || pMstCodificaDiagnosiEsameSet->IsFieldDirty(&pMstCodificaDiagnosiEsameSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pMstCodificaDiagnosiEsameSet->m_bEliminato;
}

void CMstCodificaDiagnosiEsameSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMstCodificaDiagnosiEsameSet* pOV = (CMstCodificaDiagnosiEsameSet*)pOldValues;
	CMstCodificaDiagnosiEsameSet* pNV = (CMstCodificaDiagnosiEsameSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("TipoEsame", pOV, &pOV->m_lTipoEsame, pNV, &pNV->m_lTipoEsame);
	sp.Execute("Padre", pOV, &pOV->m_lPadre, pNV, &pNV->m_lPadre);
	sp.Execute("Livello", pOV, &pOV->m_lLivello, pNV, &pNV->m_lLivello);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMstCodificaDiagnosiEsameSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMstCodificaDiagnosiEsameSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMstCodificaDiagnosiEsameSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMstCodificaDiagnosiEsameSet::SetBaseFilter(const CString &strFilter)
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