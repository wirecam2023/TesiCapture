#include "stdafx.h"
#include "Endox.h"
#include "EsamiNoShowSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiNoShowSet, CBaseSet)

CEsamiNoShowSet::CEsamiNoShowSet()
: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CEsamiNoShowSet::GetDefaultSQL()
{
	return "EXT_ESAMI_NOSHOW";
}

void CEsamiNoShowSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lId);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IdOrdine", m_lIdOrdine);
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Bool(pFX, "Eseguito", m_bEseguito);
		RFX_Long(pFX, "IdUtente", m_lIdUtente);
		RFX_Text(pFX, "Esito", m_sEsito, 3999);
	}
}

void CEsamiNoShowSet::SetEmpty()
{
	m_lId = 0;
	m_lIdOrdine = 0;
	m_sDataOra = "";
	m_bEseguito = FALSE;
	m_lIdUtente = 0;
	m_sEsito = "";
}

CBaseSet* CEsamiNoShowSet::CreateNew()
{
	return (CBaseSet*)new CEsamiNoShowSet;
}

void CEsamiNoShowSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiNoShowSet* pEsamiNoShow = (CEsamiNoShowSet*)pOriginalSet;

	if (!pEsamiNoShow->IsOpen() || pEsamiNoShow->IsFieldDirty(&pEsamiNoShow->m_lIdOrdine) || bCopyAll)
		m_lIdOrdine = pEsamiNoShow->m_lIdOrdine;
	if (!pEsamiNoShow->IsOpen() || pEsamiNoShow->IsFieldDirty(&pEsamiNoShow->m_sDataOra) || bCopyAll)
		m_sDataOra = pEsamiNoShow->m_sDataOra;
	if (!pEsamiNoShow->IsOpen() || pEsamiNoShow->IsFieldDirty(&pEsamiNoShow->m_bEseguito) || bCopyAll)
		m_bEseguito = pEsamiNoShow->m_bEseguito;
	if (!pEsamiNoShow->IsOpen() || pEsamiNoShow->IsFieldDirty(&pEsamiNoShow->m_lIdUtente) || bCopyAll)
		m_lIdUtente = pEsamiNoShow->m_lIdUtente;
	if (!pEsamiNoShow->IsOpen() || pEsamiNoShow->IsFieldDirty(&pEsamiNoShow->m_sEsito) || bCopyAll)
		m_sEsito = pEsamiNoShow->m_sEsito;
}

void CEsamiNoShowSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiNoShowSet* pOV = (CEsamiNoShowSet*)pOldValues;
	CEsamiNoShowSet* pNV = (CEsamiNoShowSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdOrdine", pOV, &pOV->m_lIdOrdine, pNV, &pNV->m_lIdOrdine);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("Eseguito", pOV, &pOV->m_bEseguito, pNV, &pNV->m_bEseguito);
	sp.Execute("IdUtente", pOV, &pOV->m_lIdUtente, pNV, &pNV->m_lIdUtente);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

CString CEsamiNoShowSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CEsamiNoShowSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CEsamiNoShowSet::InserisciRecord(long idOrdine, long idUtente)
{
	ASSERT(idOrdine > 0 && idUtente > 0);

	CBaseSet::SetBaseFilter("");

	if (OpenRecordset("CEsamiNoShowSet::InserisciRecord"))
	{
		if (AddNewRecordset("CEsamiNoShowSet::InserisciRecord"))
		{
			m_lIdOrdine = idOrdine;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_lIdUtente = idUtente;
			m_sEsito = "";
			UpdateRecordset("CEsamiNoShowSet::InserisciRecord");
		}

		CloseRecordset("CEsamiNoShowSet::InserisciRecord");
	}
}