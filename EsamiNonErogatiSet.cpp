#include "stdafx.h"
#include "Endox.h"
#include "EsamiNonErogatiSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiNonErogatiSet, CBaseSet)

CEsamiNonErogatiSet::CEsamiNonErogatiSet()
: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CEsamiNonErogatiSet::GetDefaultSQL()
{
	return "EXT_ESAMI_NONEROGATI";
}

void CEsamiNonErogatiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lId);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IdEsame", m_lIdEsame);
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Long(pFX, "Eseguito", m_lEseguito);
		RFX_Long(pFX, "IdUtente", m_lIdUtente);
		RFX_Text(pFX, "Motivo", m_sMotivo, 3999);
	}
}

void CEsamiNonErogatiSet::SetEmpty()
{
	m_lId = 0;
	m_lIdEsame = 0;
	m_sDataOra = "";
	m_lEseguito = 0;
	m_lIdUtente = 0;	
	m_sMotivo = "";
}

CBaseSet* CEsamiNonErogatiSet::CreateNew()
{
	return (CBaseSet*)new CEsamiNonErogatiSet;
}

void CEsamiNonErogatiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiNonErogatiSet* pEsamiNonErogati = (CEsamiNonErogatiSet*)pOriginalSet;

	if (!pEsamiNonErogati->IsOpen() || pEsamiNonErogati->IsFieldDirty(&pEsamiNonErogati->m_lIdEsame) || bCopyAll)
		m_lIdEsame = pEsamiNonErogati->m_lIdEsame;
	if (!pEsamiNonErogati->IsOpen() || pEsamiNonErogati->IsFieldDirty(&pEsamiNonErogati->m_sDataOra) || bCopyAll)
		m_sDataOra = pEsamiNonErogati->m_sDataOra;
	if (!pEsamiNonErogati->IsOpen() || pEsamiNonErogati->IsFieldDirty(&pEsamiNonErogati->m_lEseguito) || bCopyAll)
		m_lEseguito = pEsamiNonErogati->m_lEseguito;
	if (!pEsamiNonErogati->IsOpen() || pEsamiNonErogati->IsFieldDirty(&pEsamiNonErogati->m_lIdUtente) || bCopyAll)
		m_lIdUtente = pEsamiNonErogati->m_lIdUtente;
	if (!pEsamiNonErogati->IsOpen() || pEsamiNonErogati->IsFieldDirty(&pEsamiNonErogati->m_sMotivo) || bCopyAll)
		m_sMotivo = pEsamiNonErogati->m_sMotivo;
}

void CEsamiNonErogatiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiNonErogatiSet* pOV = (CEsamiNonErogatiSet*)pOldValues;
	CEsamiNonErogatiSet* pNV = (CEsamiNonErogatiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdEsame", pOV, &pOV->m_lIdEsame, pNV, &pNV->m_lIdEsame);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("IdUtente", pOV, &pOV->m_lIdUtente, pNV, &pNV->m_lIdUtente);	
	sp.Execute("Motivo", pOV, &pOV->m_sMotivo, pNV, &pNV->m_sMotivo);
}

CString CEsamiNonErogatiSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CEsamiNonErogatiSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CEsamiNonErogatiSet::InserisciRecord(long idEsame, long idUtente, CString sMotivo)
{
	ASSERT(idEsame > 0 && idUtente > 0);

	CBaseSet::SetBaseFilter("");

	if (OpenRecordset("CEsamiNonErogatiSet::InserisciRecord"))
	{
		if (AddNewRecordset("CEsamiNonErogatiSet::InserisciRecord"))
		{
			m_lIdEsame = idEsame;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_lIdUtente = idUtente;			
			m_sMotivo = sMotivo;
			UpdateRecordset("CEsamiNonErogatiSet::InserisciRecord");
		}

		CloseRecordset("CEsamiNonErogatiSet::InserisciRecord");
	}
}