#include "stdafx.h"
#include "Endox.h"
#include "EsamiInvioAltraUnitaSet.h"
#include "CustomDate.h"
#include "UnitaTCPSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiInvioAltraUnitaSet, CBaseSet)

CEsamiInvioAltraUnitaSet::CEsamiInvioAltraUnitaSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 10;
}

CString CEsamiInvioAltraUnitaSet::GetDefaultSQL()
{
	return "EXT_ESAMI_INVIOALTRAUNITA";
}

void CEsamiInvioAltraUnitaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDESAME", m_lIDEsame);
		RFX_Long(pFX, "IDPDF", m_lIDPdf);
		RFX_Long(pFX, "IDPDFIMMAGINI", m_lIDPdfImmagini);
		RFX_Text(pFX, "DATAORA", m_sDataOra, 14);
		RFX_Long(pFX, "IDUTENTE", m_lIDUtente);
		RFX_Long(pFX, "UNITA", m_lUnita);
		RFX_Text(pFX, "ENDPOINT", m_sEndpoint, 255);
		RFX_Long(pFX, "ESEGUITO", m_lEseguito);
		RFX_Text(pFX, "ESITO", m_sEsito, 2000000);
	}
}

void CEsamiInvioAltraUnitaSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDPdf = 0;
	m_lIDPdfImmagini = 0;
	m_sDataOra = "";
	m_lIDUtente = 0;
	m_lUnita = 0;
	m_sEndpoint = "";
	m_lEseguito = IntegrationSendStatus::notSent;
	m_sEsito = "";
}

CBaseSet* CEsamiInvioAltraUnitaSet::CreateNew()
{
	return (CBaseSet*)new CEsamiInvioAltraUnitaSet;
}

void CEsamiInvioAltraUnitaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiInvioAltraUnitaSet* pEsami = (CEsamiInvioAltraUnitaSet*)pOriginalSet;

	if (!pEsami->IsOpen() || pEsami->IsFieldDirty(&pEsami->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pEsami->m_lIDEsame;
	if (!pEsami->IsOpen() || pEsami->IsFieldDirty(&pEsami->m_lIDPdf) || bCopyAll)
		m_lIDPdf = pEsami->m_lIDPdf;
	if (!pEsami->IsOpen() || pEsami->IsFieldDirty(&pEsami->m_lIDPdfImmagini) || bCopyAll)
		m_lIDPdfImmagini = pEsami->m_lIDPdfImmagini;
	if (!pEsami->IsOpen() || pEsami->IsFieldDirty(&pEsami->m_sDataOra) || bCopyAll)
		m_sDataOra = pEsami->m_sDataOra;
	if (!pEsami->IsOpen() || pEsami->IsFieldDirty(&pEsami->m_lIDUtente) || bCopyAll)
		m_lIDUtente = pEsami->m_lIDUtente;
	if (!pEsami->IsOpen() || pEsami->IsFieldDirty(&pEsami->m_lUnita) || bCopyAll)
		m_lUnita = pEsami->m_lUnita;
	if (!pEsami->IsOpen() || pEsami->IsFieldDirty(&pEsami->m_sEndpoint) || bCopyAll)
		m_sEndpoint = pEsami->m_sEndpoint;
	if (!pEsami->IsOpen() || pEsami->IsFieldDirty(&pEsami->m_lEseguito) || bCopyAll)
		m_lEseguito = pEsami->m_lEseguito;
	if (!pEsami->IsOpen() || pEsami->IsFieldDirty(&pEsami->m_sEsito) || bCopyAll)
		m_sEsito = pEsami->m_sEsito;
}

void CEsamiInvioAltraUnitaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiInvioAltraUnitaSet* pOV = (CEsamiInvioAltraUnitaSet*)pOldValues;
	CEsamiInvioAltraUnitaSet* pNV = (CEsamiInvioAltraUnitaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDPDF", pOV, &pOV->m_lIDPdf, pNV, &pNV->m_lIDPdf);
	sp.Execute("IDPDFImmagini", pOV, &pOV->m_lIDPdfImmagini, pNV, &pNV->m_lIDPdfImmagini);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("IDUtente", pOV, &pOV->m_lIDUtente, pNV, &pNV->m_lIDUtente);
	sp.Execute("Unita", pOV, &pOV->m_lUnita, pNV, &pNV->m_lUnita);
	sp.Execute("Endpoint", pOV, &pOV->m_sEndpoint, pNV, &pNV->m_sEndpoint);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

BOOL CEsamiInvioAltraUnitaSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

BOOL CEsamiInvioAltraUnitaSet::InserisciRecord(long lIDEsame, long lIDUtente, long lUnita)
{
	ASSERT((lIDEsame > 0) && (lIDUtente > 0));

	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("IDEsame=%li", lIDEsame);
	SetOpenFilter(strFilter);

	BOOL bAlreadyPresent = FALSE;
	if (OpenRecordset("CEsamiInvioAltraUnitaSet::InserisciRecord"))
	{
		bAlreadyPresent = !IsEOF();
		CloseRecordset("CEsamiInvioAltraUnitaSet::InserisciRecord");
	}

	if (!bAlreadyPresent)
	{
		SetOpenFilter("ID=0");
		if (OpenRecordset("CEsamiInvioAltraUnitaSet::InserisciRecord"))
		{
			if (AddNewRecordset("CEsamiInvioAltraUnitaSet::InserisciRecord"))
			{
				m_lIDEsame = lIDEsame;
				m_lIDPdf = 0;
				m_lIDPdfImmagini = 0;
				m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
				m_lIDUtente = lIDUtente;
				m_lUnita = lUnita;
				m_sEndpoint = CUnitaTCPSet().GetEndpoint(lUnita);

				bReturn = UpdateRecordset("CEsamiInvioAltraUnitaSet::InserisciRecord");
			}

			CloseRecordset("CEsamiInvioAltraUnitaSet::InserisciRecord");
		}
	}

	return bReturn;
}

void CEsamiInvioAltraUnitaSet::EliminaRecord(long lIDEsame, CString sEsito)
{
	ASSERT(lIDEsame > 0);

	CString sFilter;
	sFilter.Format("IDESAME=%li and ESEGUITO=0", lIDEsame);

	CBaseSet::SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiInvioAltraUnitaSet::EliminaRecord"))
	{
		while (!IsEOF())
		{
			if (EditRecordset("CEsamiInvioAltraUnitaSet::EliminaRecord"))
			{
				m_lEseguito = -1;
				m_sEsito = sEsito;

				UpdateRecordset("CEsamiInvioAltraUnitaSet::EliminaRecord");
			}

			MoveNext();
		}

		CloseRecordset("CEsamiInvioAltraUnitaSet::EliminaRecord");
	}
}

void CEsamiInvioAltraUnitaSet::SetIdPdf(long lIDPdf, long lIDEsame)
{
	ASSERT(lIDEsame > 0);

	CString sFilter;
	sFilter.Format("IDESAME=%li and ESEGUITO=0", lIDEsame);

	CBaseSet::SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiInvioAltraUnitaSet::SetIdPdf"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CEsamiInvioAltraUnitaSet::SetIdPdf"))
			{
				m_lIDPdf = lIDPdf;

				UpdateRecordset("CEsamiInvioAltraUnitaSet::SetIdPdf");
			}
		}

		CloseRecordset("CEsamiInvioAltraUnitaSet::SetIdPdf");
	}
}
void CEsamiInvioAltraUnitaSet::SetIdPdfImmagini(long lIDPdfImmagini, long lIDEsame)
{
	ASSERT(lIDEsame > 0);

	CString sFilter;
	sFilter.Format("IDESAME=%li and ESEGUITO=0", lIDEsame);

	CBaseSet::SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiInvioAltraUnitaSet::SetIdPdfImmagini"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CEsamiInvioAltraUnitaSet::SetIdPdfImmagini"))
			{
				m_lIDPdfImmagini = lIDPdfImmagini;

				UpdateRecordset("CEsamiInvioAltraUnitaSet::SetIdPdfImmagini");
			}
		}

		CloseRecordset("CEsamiInvioAltraUnitaSet::SetIdPdfImmagini");
	}
}