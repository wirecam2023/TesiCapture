#include "stdafx.h"
#include "Endox.h"
#include "EsamiControlloQualitaSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiControlloQualitaSet, CBaseSet)

CEsamiControlloQualitaSet::CEsamiControlloQualitaSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CEsamiControlloQualitaSet::GetDefaultSQL()
{
	return "EXT_ESAMI_CONTROLLOQUALITA";
}

void CEsamiControlloQualitaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Long(pFX, "IDUtente", m_lIDUtente);
		RFX_Long(pFX, "Eseguito", m_lEseguito);
		RFX_Text(pFX, "Esito", m_sEsito, 2000000);
	}
}

void CEsamiControlloQualitaSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_sDataOra = "";
	m_lIDUtente = 0;
	m_lEseguito = IntegrationSendStatus::notSent;
	m_sEsito = "";
}

CBaseSet* CEsamiControlloQualitaSet::CreateNew()
{
	return (CBaseSet*)new CEsamiControlloQualitaSet;
}

void CEsamiControlloQualitaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiControlloQualitaSet* pEsamiChiusi = (CEsamiControlloQualitaSet*)pOriginalSet;

	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pEsamiChiusi->m_lIDEsame;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_sDataOra) || bCopyAll)
		m_sDataOra = pEsamiChiusi->m_sDataOra;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lIDUtente) || bCopyAll)
		m_lIDUtente = pEsamiChiusi->m_lIDUtente;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lEseguito) || bCopyAll)
		m_lEseguito = pEsamiChiusi->m_lEseguito;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_sEsito) || bCopyAll)
		m_sEsito = pEsamiChiusi->m_sEsito;
}

void CEsamiControlloQualitaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiControlloQualitaSet* pOV = (CEsamiControlloQualitaSet*)pOldValues;
	CEsamiControlloQualitaSet* pNV = (CEsamiControlloQualitaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("IDUtente", pOV, &pOV->m_lIDUtente, pNV, &pNV->m_lIDUtente);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

BOOL CEsamiControlloQualitaSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CEsamiControlloQualitaSet::InserisciRecord(long lIDEsame, long lIDUtente)
{
	ASSERT((lIDEsame > 0) && (lIDUtente > 0));

	CBaseSet::SetOpenFilter("ID=0");
	if (OpenRecordset("CEsamiControlloQualitaSet::InserisciRecord"))
	{
		if (AddNewRecordset("CEsamiControlloQualitaSet::InserisciRecord"))
		{
			m_lIDEsame = lIDEsame;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_lIDUtente = lIDUtente;

			UpdateRecordset("CEsamiControlloQualitaSet::InserisciRecord");
		}

		CloseRecordset("CEsamiControlloQualitaSet::InserisciRecord");
	}
}

void CEsamiControlloQualitaSet::EliminaRecord(long lIDEsame, CString sEsito)
{
	ASSERT(lIDEsame > 0);

	CString sFilter;
	sFilter.Format("IDESAME=%li and ESEGUITO=0", lIDEsame);

	CBaseSet::SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiControlloQualitaSet::EliminaRecord"))
	{
		while (!IsEOF())
		{
			if (EditRecordset("CEsamiControlloQualitaSet::EliminaRecord"))
			{
				m_lEseguito = -1;
				m_sEsito = sEsito;

				UpdateRecordset("CEsamiControlloQualitaSet::EliminaRecord");
			}

			MoveNext();
		}

		CloseRecordset("CEsamiControlloQualitaSet::EliminaRecord");
	}
}