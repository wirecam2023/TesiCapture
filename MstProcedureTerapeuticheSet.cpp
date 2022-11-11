#include "stdafx.h"
#include "Endox.h"
#include "MstProcedureTerapeuticheSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstProcedureTerapeuticheSet, CBaseSet)

CMstProcedureTerapeuticheSet::CMstProcedureTerapeuticheSet()
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

void CMstProcedureTerapeuticheSet::DoFieldExchange(CFieldExchange* pFX)
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

CString CMstProcedureTerapeuticheSet::GetDefaultSQL()
{
	return "EMSTPROCEDURETERAPEUTICHE";
}

void CMstProcedureTerapeuticheSet::SetEmpty()
{
	m_lTipoEsame = 0;
	m_lPadre = 0;
	m_lLivello = 0;
	m_sDescrizione = "";
	m_bEliminato = FALSE;
}

CBaseSet* CMstProcedureTerapeuticheSet::CreateNew()
{
	return (CBaseSet*)new CMstProcedureTerapeuticheSet;
}

void CMstProcedureTerapeuticheSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMstProcedureTerapeuticheSet* pMstProcedureTerapeuticheSet = (CMstProcedureTerapeuticheSet*)pOriginalSet;

	if (!pMstProcedureTerapeuticheSet->IsOpen() || pMstProcedureTerapeuticheSet->IsFieldDirty(&pMstProcedureTerapeuticheSet->m_lTipoEsame) || bCopyAll)
		m_lTipoEsame = pMstProcedureTerapeuticheSet->m_lTipoEsame;
	if (!pMstProcedureTerapeuticheSet->IsOpen() || pMstProcedureTerapeuticheSet->IsFieldDirty(&pMstProcedureTerapeuticheSet->m_lPadre) || bCopyAll)
		m_lPadre = pMstProcedureTerapeuticheSet->m_lPadre;
	if (!pMstProcedureTerapeuticheSet->IsOpen() || pMstProcedureTerapeuticheSet->IsFieldDirty(&pMstProcedureTerapeuticheSet->m_lLivello) || bCopyAll)
		m_lLivello = pMstProcedureTerapeuticheSet->m_lLivello;
	if (!pMstProcedureTerapeuticheSet->IsOpen() || pMstProcedureTerapeuticheSet->IsFieldDirty(&pMstProcedureTerapeuticheSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pMstProcedureTerapeuticheSet->m_sDescrizione;
	if (!pMstProcedureTerapeuticheSet->IsOpen() || pMstProcedureTerapeuticheSet->IsFieldDirty(&pMstProcedureTerapeuticheSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pMstProcedureTerapeuticheSet->m_bEliminato;
}

void CMstProcedureTerapeuticheSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMstProcedureTerapeuticheSet* pOV = (CMstProcedureTerapeuticheSet*)pOldValues;
	CMstProcedureTerapeuticheSet* pNV = (CMstProcedureTerapeuticheSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("TipoEsame", pOV, &pOV->m_lTipoEsame, pNV, &pNV->m_lTipoEsame);
	sp.Execute("Padre", pOV, &pOV->m_lPadre, pNV, &pNV->m_lPadre);
	sp.Execute("Livello", pOV, &pOV->m_lLivello, pNV, &pNV->m_lLivello);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMstProcedureTerapeuticheSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMstProcedureTerapeuticheSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMstProcedureTerapeuticheSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMstProcedureTerapeuticheSet::SetBaseFilter(const CString &strFilter)
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