#include "stdafx.h"
#include "Endox.h"
#include "EsamiRefertazioneRemotaSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiRefertazioneRemotaSet, CBaseSet)

CEsamiRefertazioneRemotaSet::CEsamiRefertazioneRemotaSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CEsamiRefertazioneRemotaSet::GetDefaultSQL()
{
	return "EXT_ESAMI_REFERTAZIONEREMOTA";
}

void CEsamiRefertazioneRemotaSet::DoFieldExchange(CFieldExchange* pFX)
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

void CEsamiRefertazioneRemotaSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_sDataOra = "";
	m_lIDUtente = 0;
	m_lEseguito = IntegrationSendStatus::notSent;
	m_sEsito = "";
}

CBaseSet* CEsamiRefertazioneRemotaSet::CreateNew()
{
	return (CBaseSet*)new CEsamiRefertazioneRemotaSet;
}

void CEsamiRefertazioneRemotaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiRefertazioneRemotaSet* pEsamiChiusi = (CEsamiRefertazioneRemotaSet*)pOriginalSet;

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

void CEsamiRefertazioneRemotaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiRefertazioneRemotaSet* pOV = (CEsamiRefertazioneRemotaSet*)pOldValues;
	CEsamiRefertazioneRemotaSet* pNV = (CEsamiRefertazioneRemotaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("IDUtente", pOV, &pOV->m_lIDUtente, pNV, &pNV->m_lIDUtente);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

BOOL CEsamiRefertazioneRemotaSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

BOOL CEsamiRefertazioneRemotaSet::InserisciRecord(long lIDEsame, long lIDUtente)
{
	ASSERT((lIDEsame > 0) && (lIDUtente > 0));

	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("IDEsame=%li",lIDEsame);
	SetOpenFilter(strFilter);
	
	BOOL bAlreadyPresent = FALSE;
	if (OpenRecordset("CEsamiRefertazioneRemotaSet::InserisciRecord"))
	{
		bAlreadyPresent = !IsEOF();
		CloseRecordset("CEsamiRefertazioneRemotaSet::InserisciRecord");
	}

	if (!bAlreadyPresent)
	{
		SetOpenFilter("ID=0");
		if (OpenRecordset("CEsamiRefertazioneRemotaSet::InserisciRecord"))
		{
			if (AddNewRecordset("CEsamiRefertazioneRemotaSet::InserisciRecord"))
			{
				m_lIDEsame = lIDEsame;
				m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
				m_lIDUtente = lIDUtente;

				bReturn = UpdateRecordset("CEsamiRefertazioneRemotaSet::InserisciRecord");
			}

			CloseRecordset("CEsamiRefertazioneRemotaSet::InserisciRecord");
		}
	}

	return bReturn;
}

void CEsamiRefertazioneRemotaSet::EliminaRecord(long lIDEsame, CString sEsito)
{
	ASSERT(lIDEsame > 0);

	CString sFilter;
	sFilter.Format("IDESAME=%li and ESEGUITO=0", lIDEsame);

	CBaseSet::SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiRefertazioneRemotaSet::EliminaRecord"))
	{
		while (!IsEOF())
		{
			if (EditRecordset("CEsamiRefertazioneRemotaSet::EliminaRecord"))
			{
				m_lEseguito = -1;
				m_sEsito = sEsito;

				UpdateRecordset("CEsamiRefertazioneRemotaSet::EliminaRecord");
			}

			MoveNext();
		}

		CloseRecordset("CEsamiRefertazioneRemotaSet::EliminaRecord");
	}
}