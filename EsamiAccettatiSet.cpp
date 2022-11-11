#include "stdafx.h"
#include "Endox.h"
#include "EsamiAccettatiSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiAccettatiSet, CBaseSet)

CEsamiAccettatiSet::CEsamiAccettatiSet()
: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CEsamiAccettatiSet::GetDefaultSQL()
{
	return "EXT_ESAMI_ACCETTATI";
}

void CEsamiAccettatiSet::DoFieldExchange(CFieldExchange* pFX)
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
	}
}

void CEsamiAccettatiSet::SetEmpty()
{
	m_lId = 0;
	m_lIdEsame = 0;
	m_sDataOra = "";
	m_lEseguito = 0;
	m_lIdUtente = 0;	
}

CBaseSet* CEsamiAccettatiSet::CreateNew()
{
	return (CBaseSet*)new CEsamiAccettatiSet;
}

void CEsamiAccettatiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiAccettatiSet* pEsamiAccettati = (CEsamiAccettatiSet*)pOriginalSet;

	if (!pEsamiAccettati->IsOpen() || pEsamiAccettati->IsFieldDirty(&pEsamiAccettati->m_lIdEsame) || bCopyAll)
		m_lIdEsame = pEsamiAccettati->m_lIdEsame;
	if (!pEsamiAccettati->IsOpen() || pEsamiAccettati->IsFieldDirty(&pEsamiAccettati->m_sDataOra) || bCopyAll)
		m_sDataOra = pEsamiAccettati->m_sDataOra;
	if (!pEsamiAccettati->IsOpen() || pEsamiAccettati->IsFieldDirty(&pEsamiAccettati->m_lEseguito) || bCopyAll)
		m_lEseguito = pEsamiAccettati->m_lEseguito;
	if (!pEsamiAccettati->IsOpen() || pEsamiAccettati->IsFieldDirty(&pEsamiAccettati->m_lIdUtente) || bCopyAll)
		m_lIdUtente = pEsamiAccettati->m_lIdUtente;
	
}

void CEsamiAccettatiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiAccettatiSet* pOV = (CEsamiAccettatiSet*)pOldValues;
	CEsamiAccettatiSet* pNV = (CEsamiAccettatiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdEsame", pOV, &pOV->m_lIdEsame, pNV, &pNV->m_lIdEsame);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("IdUtente", pOV, &pOV->m_lIdUtente, pNV, &pNV->m_lIdUtente);		
}

CString CEsamiAccettatiSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CEsamiAccettatiSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CEsamiAccettatiSet::InserisciRecord(long idEsame, long idUtente)
{
	ASSERT(idEsame > 0 && idUtente > 0);

	CBaseSet::SetBaseFilter("");
	SetOpenFilter("ID = 0");
	if (OpenRecordset("CEsamiAccettatiSet::InserisciRecord"))
	{
		if (AddNewRecordset("CEsamiAccettatiSet::InserisciRecord"))
		{
			m_lIdEsame = idEsame;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_lIdUtente = idUtente;			
			UpdateRecordset("CEsamiAccettatiSet::InserisciRecord");
		}

		CloseRecordset("CEsamiAccettatiSet::InserisciRecord");
	}
}