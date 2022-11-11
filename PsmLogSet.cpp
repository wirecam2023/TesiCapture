#include "stdafx.h"
#include "Endox.h"
#include "PsmLogSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPsmLogSet, CBaseSet)

CPsmLogSet::CPsmLogSet()
: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CPsmLogSet::GetDefaultSQL()
{
	return "PSMLOG";
}

void CPsmLogSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lId);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Long(pFX, "IdEsame", m_lIdEsame);
		RFX_Long(pFX, "IdPaziente", m_lIdPaziente);
		RFX_Text(pFX, "IdEpisodio", m_sIdEpisodio, 50);
		RFX_Text(pFX, "Url", m_sUrl, 3999);
	}
}

void CPsmLogSet::SetEmpty()
{
	m_lId = 0;
	m_sDataOra = "";
	m_lIdPaziente = 0; 
	m_lIdEsame = 0; 
	m_sIdEpisodio = ""; 
	m_sUrl = "";
}

CBaseSet* CPsmLogSet::CreateNew()
{
	return (CBaseSet*)new CPsmLogSet;
}

void CPsmLogSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CPsmLogSet* pPsmSet = (CPsmLogSet*)pOriginalSet;

	if (!pPsmSet->IsOpen() || pPsmSet->IsFieldDirty(&pPsmSet->m_sDataOra) || bCopyAll)
		m_sDataOra = pPsmSet->m_sDataOra;
	if (!pPsmSet->IsOpen() || pPsmSet->IsFieldDirty(&pPsmSet->m_lIdPaziente) || bCopyAll)
		m_lIdPaziente = pPsmSet->m_lIdPaziente;
	if (!pPsmSet->IsOpen() || pPsmSet->IsFieldDirty(&pPsmSet->m_lIdEsame) || bCopyAll)
		m_lIdEsame = pPsmSet->m_lIdEsame;
	if (!pPsmSet->IsOpen() || pPsmSet->IsFieldDirty(&pPsmSet->m_sIdEpisodio) || bCopyAll)
		m_sIdEpisodio = pPsmSet->m_sIdEpisodio;
	if (!pPsmSet->IsOpen() || pPsmSet->IsFieldDirty(&pPsmSet->m_sUrl) || bCopyAll)
		m_sUrl = pPsmSet->m_sUrl;
}

void CPsmLogSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CPsmLogSet* pOV = (CPsmLogSet*)pOldValues;
	CPsmLogSet* pNV = (CPsmLogSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdEsame", pOV, &pOV->m_lIdEsame, pNV, &pNV->m_lIdEsame);
	sp.Execute("IdPaziente", pOV, &pOV->m_lIdPaziente, pNV, &pNV->m_lIdPaziente);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("IdEpisodio", pOV, &pOV->m_sIdEpisodio, pNV, &pNV->m_sIdEpisodio);
	sp.Execute("Url", pOV, &pOV->m_sUrl, pNV, &pNV->m_sUrl);
}

CString CPsmLogSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CPsmLogSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CPsmLogSet::InsertLog(long lPaziente, long lEsame, CString idEpisodio, CString url)
{
	ASSERT(lEsame > 0 && lPaziente > 0);

	CBaseSet::SetBaseFilter("");

	if (OpenRecordset("CPsmLogSet::InsertLog"))
	{
		if (AddNewRecordset("CPsmLogSet::InsertLog"))
		{
			m_lIdEsame = lEsame;
			m_lIdPaziente = lPaziente;
			CCustomDate	DataOggi(TRUE, TRUE);
			m_sDataOra = DataOggi.GetDate("%Y%m%d%H%M00");
			m_sIdEpisodio = idEpisodio;
			m_sUrl = url;
			UpdateRecordset("CPsmLogSet::InsertLog");
		}

		CloseRecordset("CPsmLogSet::InsertLog");
	}
}