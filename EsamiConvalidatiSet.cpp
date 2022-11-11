#include "stdafx.h"
#include "Endox.h"
#include "EsamiConvalidatiSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiConvalidatiSet, CBaseSet)

CEsamiConvalidatiSet::CEsamiConvalidatiSet()
: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CEsamiConvalidatiSet::GetDefaultSQL()
{
	return "EXT_ESAMI_CONVALIDATI";
}

void CEsamiConvalidatiSet::DoFieldExchange(CFieldExchange* pFX)
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

void CEsamiConvalidatiSet::SetEmpty()
{
	m_lId = 0;
	m_lIdEsame = 0;
	m_sDataOra = "";
	m_lIdUtente = 0;
	m_lEseguito = 0;
}

CBaseSet* CEsamiConvalidatiSet::CreateNew()
{
	return (CBaseSet*)new CEsamiConvalidatiSet;
}

void CEsamiConvalidatiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiConvalidatiSet* pEsamiChiusi = (CEsamiConvalidatiSet*)pOriginalSet;

	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lIdEsame) || bCopyAll)
		m_lIdEsame = pEsamiChiusi->m_lIdEsame;	
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_sDataOra) || bCopyAll)
		m_sDataOra = pEsamiChiusi->m_sDataOra;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lIdUtente) || bCopyAll)
		m_lIdUtente = pEsamiChiusi->m_lIdUtente;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lEseguito) || bCopyAll)
		m_lEseguito = pEsamiChiusi->m_lEseguito;
}

void CEsamiConvalidatiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiConvalidatiSet* pOV = (CEsamiConvalidatiSet*)pOldValues;
	CEsamiConvalidatiSet* pNV = (CEsamiConvalidatiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdEsame", pOV, &pOV->m_lIdEsame, pNV, &pNV->m_lIdEsame);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("IdUtente", pOV, &pOV->m_lIdUtente, pNV, &pNV->m_lIdUtente);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
}

CString CEsamiConvalidatiSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CEsamiConvalidatiSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CEsamiConvalidatiSet::InserisciRecord(long idEsame, long idUtente)
{
	ASSERT(idEsame > 0 && idUtente > 0);

	CBaseSet::SetBaseFilter("");

	if (OpenRecordset("CEsamiConvalidatiSet::InserisciRecord"))
	{
		if (AddNewRecordset("CEsamiConvalidatiSet::InserisciRecord"))
		{
			m_lIdEsame = idEsame;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_lIdUtente = idUtente;			
			UpdateRecordset("CEsamiConvalidatiSet::InserisciRecord");
		}

		CloseRecordset("CEsamiConvalidatiSet::InserisciRecord");
	}
}