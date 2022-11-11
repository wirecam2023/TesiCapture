#include "stdafx.h"
#include "Endox.h"
#include "ExtMonitoraggiChiusiSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtMonitoraggiChiusiSet, CBaseSet)

CExtMonitoraggiChiusiSet::CExtMonitoraggiChiusiSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

CString CExtMonitoraggiChiusiSet::GetDefaultSQL()
{
	return "EXT_MONITORAGGI_CHIUSI";
}

void CExtMonitoraggiChiusiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDPdf", m_lIDPdf);		
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Long(pFX, "IDUtente", m_lIDUtente);
		RFX_Long(pFX, "Eseguito", m_lEseguito);
		RFX_Text(pFX, "Esito", m_sEsito, 2000000);
	}
}

void CExtMonitoraggiChiusiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDPdf = 0;
	m_sDataOra = "";
	m_lIDUtente = 0;
	m_lEseguito = IntegrationSendStatus::notSent;
	m_sEsito = "";
}

CBaseSet* CExtMonitoraggiChiusiSet::CreateNew()
{
	return (CBaseSet*)new CExtMonitoraggiChiusiSet;
}

void CExtMonitoraggiChiusiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtMonitoraggiChiusiSet* pChiusi = (CExtMonitoraggiChiusiSet*)pOriginalSet;

	if (!pChiusi->IsOpen() || pChiusi->IsFieldDirty(&pChiusi->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pChiusi->m_lIDEsame;
	if (!pChiusi->IsOpen() || pChiusi->IsFieldDirty(&pChiusi->m_lIDPdf) || bCopyAll)
		m_lIDPdf = pChiusi->m_lIDPdf;
	if (!pChiusi->IsOpen() || pChiusi->IsFieldDirty(&pChiusi->m_sDataOra) || bCopyAll)
		m_sDataOra = pChiusi->m_sDataOra;
	if (!pChiusi->IsOpen() || pChiusi->IsFieldDirty(&pChiusi->m_lIDUtente) || bCopyAll)
		m_lIDUtente = pChiusi->m_lIDUtente;
	if (!pChiusi->IsOpen() || pChiusi->IsFieldDirty(&pChiusi->m_lEseguito) || bCopyAll)
		m_lEseguito = pChiusi->m_lEseguito;
	if (!pChiusi->IsOpen() || pChiusi->IsFieldDirty(&pChiusi->m_sEsito) || bCopyAll)
		m_sEsito = pChiusi->m_sEsito;
}

void CExtMonitoraggiChiusiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtMonitoraggiChiusiSet* pOV = (CExtMonitoraggiChiusiSet*)pOldValues;
	CExtMonitoraggiChiusiSet* pNV = (CExtMonitoraggiChiusiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDPdf", pOV, &pOV->m_lIDPdf, pNV, &pNV->m_lIDPdf);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("IDUtente", pOV, &pOV->m_lIDUtente, pNV, &pNV->m_lIDUtente);	
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

BOOL CExtMonitoraggiChiusiSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CExtMonitoraggiChiusiSet::InserisciRecord(long lIDEsame, long lIDPdf, long lIDUtente)
{
	ASSERT((lIDEsame > 0) && (lIDUtente > 0));

	CBaseSet::SetOpenFilter("ID=0");
	if (OpenRecordset("CExtMonitoraggiChiusiSet::InserisciRecord"))
	{
		if (AddNewRecordset("CExtMonitoraggiChiusiSet::InserisciRecord"))
		{
			m_lIDEsame = lIDEsame;
			m_lIDPdf = lIDPdf;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_lIDUtente = lIDUtente;

			UpdateRecordset("CExtMonitoraggiChiusiSet::InserisciRecord");
		}

		CloseRecordset("CExtMonitoraggiChiusiSet::InserisciRecord");
	}
}

