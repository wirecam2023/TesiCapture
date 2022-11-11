#include "stdafx.h"
#include "Endox.h"
#include "MstDiagnosiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstDiagnosiSet, CBaseSet)

CMstDiagnosiSet::CMstDiagnosiSet()
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

void CMstDiagnosiSet::DoFieldExchange(CFieldExchange* pFX)
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

CString CMstDiagnosiSet::GetDefaultSQL()
{
	return "EMSTDIAGNOSI";
}

void CMstDiagnosiSet::SetEmpty()
{
	m_lOrgano = 0;
	m_lPadre = 0;
	m_lLivello = 0;
	m_sDescrizione = "";
	m_bEliminato = FALSE;
}

CBaseSet* CMstDiagnosiSet::CreateNew()
{
	return (CBaseSet*)new CMstDiagnosiSet;
}

void CMstDiagnosiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMstDiagnosiSet* pMstDiagnosiSet = (CMstDiagnosiSet*)pOriginalSet;

	if (!pMstDiagnosiSet->IsOpen() || pMstDiagnosiSet->IsFieldDirty(&pMstDiagnosiSet->m_lOrgano) || bCopyAll)
		m_lOrgano = pMstDiagnosiSet->m_lOrgano;
	if (!pMstDiagnosiSet->IsOpen() || pMstDiagnosiSet->IsFieldDirty(&pMstDiagnosiSet->m_lPadre) || bCopyAll)
		m_lPadre = pMstDiagnosiSet->m_lPadre;
	if (!pMstDiagnosiSet->IsOpen() || pMstDiagnosiSet->IsFieldDirty(&pMstDiagnosiSet->m_lLivello) || bCopyAll)
		m_lLivello = pMstDiagnosiSet->m_lLivello;
	if (!pMstDiagnosiSet->IsOpen() || pMstDiagnosiSet->IsFieldDirty(&pMstDiagnosiSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pMstDiagnosiSet->m_sDescrizione;
	if (!pMstDiagnosiSet->IsOpen() || pMstDiagnosiSet->IsFieldDirty(&pMstDiagnosiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pMstDiagnosiSet->m_bEliminato;
}

void CMstDiagnosiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMstDiagnosiSet* pOV = (CMstDiagnosiSet*)pOldValues;
	CMstDiagnosiSet* pNV = (CMstDiagnosiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Organo", pOV, &pOV->m_lOrgano, pNV, &pNV->m_lOrgano);
	sp.Execute("Padre", pOV, &pOV->m_lPadre, pNV, &pNV->m_lPadre);
	sp.Execute("Livello", pOV, &pOV->m_lLivello, pNV, &pNV->m_lLivello);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMstDiagnosiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMstDiagnosiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMstDiagnosiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMstDiagnosiSet::SetBaseFilter(const CString &strFilter)
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