#include "stdafx.h"
#include "Endox.h"
#include "EsamiSbloccatiSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiSbloccatiSet, CBaseSet)

CEsamiSbloccatiSet::CEsamiSbloccatiSet()
	: CBaseSet(&m_lId, "ID")
{
	SetEmpty();

	m_nFields = 5;
}

CString CEsamiSbloccatiSet::GetDefaultSQL()
{
	return "EXT_ESAMI_SBLOCCATI";
}

void CEsamiSbloccatiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lId);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IdEsame", m_lIdEsame);
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Long(pFX, "IdUtente", m_lIdUtente);
		RFX_Long(pFX, "Eseguito", m_lEseguito);
	}
}

void CEsamiSbloccatiSet::SetEmpty()
{
	m_lId = 0;
	m_lIdEsame = 0;
	m_sDataOra = "";
	m_lIdUtente = 0;
	m_lEseguito = 0;
}

CBaseSet* CEsamiSbloccatiSet::CreateNew()
{
	return (CBaseSet*)new CEsamiSbloccatiSet;
}

void CEsamiSbloccatiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiSbloccatiSet* pSet = (CEsamiSbloccatiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdEsame) || bCopyAll)
		m_lIdEsame = pSet->m_lIdEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataOra) || bCopyAll)
		m_sDataOra = pSet->m_sDataOra;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdUtente) || bCopyAll)
		m_lIdUtente = pSet->m_lIdUtente;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEseguito) || bCopyAll)
		m_lEseguito = pSet->m_lEseguito;
}

void CEsamiSbloccatiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiSbloccatiSet* pOV = (CEsamiSbloccatiSet*)pOldValues;
	CEsamiSbloccatiSet* pNV = (CEsamiSbloccatiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdEsame", pOV, &pOV->m_lIdEsame, pNV, &pNV->m_lIdEsame);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("IdUtente", pOV, &pOV->m_lIdUtente, pNV, &pNV->m_lIdUtente);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
}

BOOL CEsamiSbloccatiSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CEsamiSbloccatiSet::InserisciRecord(long idEsame, long idUtente)
{
	ASSERT(idEsame > 0 && idUtente > 0);

	if (!((CAMBaseDB*)m_pDatabase)->CheckTableExists(GetDefaultSQL()))
		return;

	SetOpenFilter("ID = 0");
	if (OpenRecordset("CEsamiSbloccatiSet::InserisciRecord"))
	{
		if (AddNewRecordset("CEsamiSbloccatiSet::InserisciRecord"))
		{
			m_lIdEsame = idEsame;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_lIdUtente = idUtente;
			UpdateRecordset("CEsamiSbloccatiSet::InserisciRecord");
		}

		CloseRecordset("CEsamiSbloccatiSet::InserisciRecord");
	}
}