#include "stdafx.h"
#include "Endox.h"
#include "EsamiChiusiSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiChiusiSet, CBaseSet)

CEsamiChiusiSet::CEsamiChiusiSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 10;
}

CString CEsamiChiusiSet::GetDefaultSQL()
{
	return "EXT_ESAMI_CHIUSI";
}

void CEsamiChiusiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDPdf", m_lIDPdf);
		RFX_Long(pFX, "IDPdfImmagini", m_lIDPdfImmagini);
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Long(pFX, "IDUtente", m_lIDUtente);
		RFX_Text(pFX, "Tipologia", m_sTipologia, 2);
		RFX_Long(pFX, "IDPdfOld", m_lIDPdfOld);
		RFX_Long(pFX, "Eseguito", m_lEseguito);
		RFX_Text(pFX, "Esito", m_sEsito, 2000000);
	}
}

void CEsamiChiusiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDPdf = 0;
	m_lIDPdfImmagini = 0;
	m_sDataOra = "";
	m_lIDUtente = 0;
	m_sTipologia = "";
	m_lIDPdfOld = 0;
	m_lEseguito = IntegrationSendStatus::notSent;
	m_sEsito = "";
}

CBaseSet* CEsamiChiusiSet::CreateNew()
{
	return (CBaseSet*)new CEsamiChiusiSet;
}

void CEsamiChiusiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiChiusiSet* pEsamiChiusi = (CEsamiChiusiSet*)pOriginalSet;

	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pEsamiChiusi->m_lIDEsame;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lIDPdf) || bCopyAll)
		m_lIDPdf = pEsamiChiusi->m_lIDPdf;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lIDPdfImmagini) || bCopyAll)
		m_lIDPdfImmagini = pEsamiChiusi->m_lIDPdfImmagini;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_sDataOra) || bCopyAll)
		m_sDataOra = pEsamiChiusi->m_sDataOra;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lIDUtente) || bCopyAll)
		m_lIDUtente = pEsamiChiusi->m_lIDUtente;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_sTipologia) || bCopyAll)
		m_sTipologia = pEsamiChiusi->m_sTipologia;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lIDPdfOld) || bCopyAll)
		m_lIDPdfOld = pEsamiChiusi->m_lIDPdfOld;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_lEseguito) || bCopyAll)
		m_lEseguito = pEsamiChiusi->m_lEseguito;
	if (!pEsamiChiusi->IsOpen() || pEsamiChiusi->IsFieldDirty(&pEsamiChiusi->m_sEsito) || bCopyAll)
		m_sEsito = pEsamiChiusi->m_sEsito;
}

void CEsamiChiusiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiChiusiSet* pOV = (CEsamiChiusiSet*)pOldValues;
	CEsamiChiusiSet* pNV = (CEsamiChiusiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDPdf", pOV, &pOV->m_lIDPdf, pNV, &pNV->m_lIDPdf);
	sp.Execute("IDPdfImmagini", pOV, &pOV->m_lIDPdfImmagini, pNV, &pNV->m_lIDPdfImmagini);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("IDUtente", pOV, &pOV->m_lIDUtente, pNV, &pNV->m_lIDUtente);
	sp.Execute("Tipologia", pOV, &pOV->m_sTipologia, pNV, &pNV->m_sTipologia);
	sp.Execute("IDPdfOld", pOV, &pOV->m_lIDPdfOld, pNV, &pNV->m_lIDPdfOld);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

BOOL CEsamiChiusiSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CEsamiChiusiSet::InserisciRecord(long lIDEsame, long lIDPdf, long lIDPdfImmagini, long lIDUtente, CString sTipologia, long lIDPdfOld)
{
	ASSERT((lIDEsame > 0) && (lIDUtente > 0));
	ASSERT(sTipologia.GetLength() < 3);

	CBaseSet::SetOpenFilter("ID=0");
	if (OpenRecordset("CEsamiChiusiSet::InserisciRecord"))
	{
		if (AddNewRecordset("CEsamiChiusiSet::InserisciRecord"))
		{
			m_lIDEsame = lIDEsame;
			m_lIDPdf = lIDPdf;
			m_lIDPdfImmagini = lIDPdfImmagini;
			m_sDataOra = theApp.GetServerDate();
			m_lIDUtente = lIDUtente;
			m_sTipologia = sTipologia.Left(2);
			m_lIDPdfOld = lIDPdfOld;

			UpdateRecordset("CEsamiChiusiSet::InserisciRecord");
		}

		CloseRecordset("CEsamiChiusiSet::InserisciRecord");
	}
}
//Julio 25/09/2018  - Pdf imagens perde referencia na ext_esami_chiusi quando exame assinado em mobilidade
void CEsamiChiusiSet::UpdateRecord(long lIDEsame, long lIDPdf, long lIDPdfImmagini, long lIDUtente)
{
	ASSERT(lIDEsame > 0);

	CString filter;
	filter.Format("IDEsame=%li", lIDEsame);	

	SetOpenFilter(filter);
	SetSortRecord("ID DESC");

	if (OpenRecordset("CEsamiChiusiSet::UpdateRecord"))
	{		
		if (!IsEOF())
		{			
			if (EditRecordset("CEsamiChiusiSet::RemoveFromExam"))
			{				
				m_lIDPdf = lIDPdf;
				m_lIDPdfImmagini = lIDPdfImmagini;
				m_lEseguito = 0;				
				UpdateRecordset("CEsamiChiusiSet::UpdateRecord");
			}
		}
		else
		{				
			InserisciRecord(lIDEsame, lIDPdf, lIDPdfImmagini, lIDUtente, "NW");
		}		
		CloseRecordset("CEsamiChiusiSet::UpdateRecord");
	}
}

long CEsamiChiusiSet::GetIdFromPdfId(long lPdfId)
{
	if (lPdfId <= 0)
		return 0;

	long lReturn = 0;

	CString filter;
	filter.Format("IDPDF=%li", lPdfId);

	SetOpenFilter(filter);

	if (OpenRecordset("CEsamiChiusiSet::GetIdFromPdfId"))
	{
		if (!IsEOF())
			lReturn = m_lID;

		CloseRecordset("CEsamiChiusiSet::GetIdFromPdfId");
	}

	return lReturn;
}

void CEsamiChiusiSet::RemoveFromExam(long lClosedExamId)
{
	ASSERT(lClosedExamId > 0);

	CString filter;
	filter.Format("ID=%li", lClosedExamId);

	SetOpenFilter(filter);

	if (OpenRecordset("CEsamiChiusiSet::RemoveFromExam"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CEsamiChiusiSet::RemoveFromExam"))
			{
				m_lIDEsame = -1;

				UpdateRecordset("CEsamiChiusiSet::RemoveFromExam");
			}
		}

		CloseRecordset("CEsamiChiusiSet::RemoveFromExam");
	}
}

long CEsamiChiusiSet::GetPdfIdFromId(long lId)
{
	if (lId <= 0)
		return 0;

	long lReturn = 0;

	CString filter;
	filter.Format("ID=%li", lId);

	SetOpenFilter(filter);

	if (OpenRecordset("CEsamiChiusiSet::GetPdfIdFromId"))
	{
		if (!IsEOF())
			lReturn = m_lIDPdf;

		CloseRecordset("CEsamiChiusiSet::GetPdfIdFromId");
	}

	return lReturn;
}

CString CEsamiChiusiSet::UltimaDataOraChiusura(long lIDEsame)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("IDEsame = %li", lIDEsame);

	SetOpenFilter(sFilter);
	SetSortRecord("DataOra DESC");

	if (OpenRecordset("CEsamiChiusiSet::UltimaDataOraChiusura"))
	{
		if (!IsEOF())
		{
			sReturn = m_sDataOra;
			sReturn.Trim();

			if (!sReturn.IsEmpty())
			{
				while (sReturn.GetLength() < 14)
					sReturn += "0";
			}
		}

		CloseRecordset("CEsamiChiusiSet::UltimaDataOraChiusura");
	}

	return sReturn;
}
