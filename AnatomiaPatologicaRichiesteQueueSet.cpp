#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaRichiesteQueueSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaRichiesteQueueSet, CBaseSet)

CAnatomiaPatologicaRichiesteQueueSet::CAnatomiaPatologicaRichiesteQueueSet()
	: CBaseSet(&m_lId, "ID")
{
	SetEmpty();

	m_nFields = 8;
	SetBaseFilter("");
}

CString CAnatomiaPatologicaRichiesteQueueSet::GetDefaultSQL()
{
	return "ext_richiesteap_queue";
}

void CAnatomiaPatologicaRichiesteQueueSet::SetEmpty()
{
	m_lId = 0;
	m_lIdEsame = 0;
	m_sDataOra = "";
	m_sTipologia = "";
	m_lEseguito = 0;
	m_lIdUtente = 0;
	m_sErrore = "";
	m_bEliminato = FALSE;
}

void CAnatomiaPatologicaRichiesteQueueSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lId);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIdEsame);
		RFX_Text(pFX, "Dataora", m_sDataOra, 50);
		RFX_Text(pFX, "Tipologia", m_sTipologia, 2);
		RFX_Long(pFX, "Eseguito", m_lEseguito);
		RFX_Long(pFX, "IDUtente", m_lIdUtente);
		RFX_Text(pFX, "Errore", m_sErrore, 4000);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CAnatomiaPatologicaRichiesteQueueSet::CreateNew()
{
	return (CBaseSet*)new CAnatomiaPatologicaRichiesteQueueSet;
}

void CAnatomiaPatologicaRichiesteQueueSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CAnatomiaPatologicaRichiesteQueueSet* pCAnatomiaPatologicaRichiesteQueueSet = (CAnatomiaPatologicaRichiesteQueueSet*)pOriginalSet;

	if (!pCAnatomiaPatologicaRichiesteQueueSet->IsOpen() || pCAnatomiaPatologicaRichiesteQueueSet->IsFieldDirty(&pCAnatomiaPatologicaRichiesteQueueSet->m_lIdEsame) || bCopyAll)
		m_lIdEsame = pCAnatomiaPatologicaRichiesteQueueSet->m_lIdEsame;
	if (!pCAnatomiaPatologicaRichiesteQueueSet->IsOpen() || pCAnatomiaPatologicaRichiesteQueueSet->IsFieldDirty(&pCAnatomiaPatologicaRichiesteQueueSet->m_sDataOra) || bCopyAll)
		m_sDataOra = pCAnatomiaPatologicaRichiesteQueueSet->m_sDataOra;
	if (!pCAnatomiaPatologicaRichiesteQueueSet->IsOpen() || pCAnatomiaPatologicaRichiesteQueueSet->IsFieldDirty(&pCAnatomiaPatologicaRichiesteQueueSet->m_sTipologia) || bCopyAll)
		m_sTipologia = pCAnatomiaPatologicaRichiesteQueueSet->m_sTipologia;
	if (!pCAnatomiaPatologicaRichiesteQueueSet->IsOpen() || pCAnatomiaPatologicaRichiesteQueueSet->IsFieldDirty(&pCAnatomiaPatologicaRichiesteQueueSet->m_lEseguito) || bCopyAll)
		m_lEseguito = pCAnatomiaPatologicaRichiesteQueueSet->m_lEseguito;
	if (!pCAnatomiaPatologicaRichiesteQueueSet->IsOpen() || pCAnatomiaPatologicaRichiesteQueueSet->IsFieldDirty(&pCAnatomiaPatologicaRichiesteQueueSet->m_lIdUtente) || bCopyAll)
		m_lIdUtente = pCAnatomiaPatologicaRichiesteQueueSet->m_lIdUtente;
	if (!pCAnatomiaPatologicaRichiesteQueueSet->IsOpen() || pCAnatomiaPatologicaRichiesteQueueSet->IsFieldDirty(&pCAnatomiaPatologicaRichiesteQueueSet->m_sErrore) || bCopyAll)
		m_sErrore = pCAnatomiaPatologicaRichiesteQueueSet->m_sErrore;
	if (!pCAnatomiaPatologicaRichiesteQueueSet->IsOpen() || pCAnatomiaPatologicaRichiesteQueueSet->IsFieldDirty(&pCAnatomiaPatologicaRichiesteQueueSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pCAnatomiaPatologicaRichiesteQueueSet->m_bEliminato;
}

void CAnatomiaPatologicaRichiesteQueueSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CAnatomiaPatologicaRichiesteQueueSet* pOV = (CAnatomiaPatologicaRichiesteQueueSet*)pOldValues;
	CAnatomiaPatologicaRichiesteQueueSet* pNV = (CAnatomiaPatologicaRichiesteQueueSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIdEsame, pNV, &pNV->m_lIdEsame);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("Tipologia", pOV, &pOV->m_sTipologia, pNV, &pNV->m_sTipologia);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("IdUtente", pOV, &pOV->m_lIdUtente, pNV, &pNV->m_lIdUtente);
	sp.Execute("Errore", pOV, &pOV->m_sErrore, pNV, &pNV->m_sErrore);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CAnatomiaPatologicaRichiesteQueueSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CAnatomiaPatologicaRichiesteQueueSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CAnatomiaPatologicaRichiesteQueueSet::DeleteRecordset");
	}
	return bReturn;
}

CString CAnatomiaPatologicaRichiesteQueueSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty() == TRUE)
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

void CAnatomiaPatologicaRichiesteQueueSet::InserisciRecord(long idEsame, long idUtente, long tipologia)
{
	ASSERT(idEsame > 0 && idUtente > 0 && tipologia > 0);
	SetBaseFilter("");

	if (OpenRecordset("CAnatomiaPatologicaRichiesteQueueSet::InserisciRecord"))
	{
		if (AddNewRecordset("CAnatomiaPatologicaRichiesteQueueSet::InserisciRecord"))
		{
			m_lIdEsame = idEsame;
			CCustomDate	DataOggi(TRUE, TRUE);
			m_sDataOra = DataOggi.GetDate("%Y%m%d%H%M00");
			switch(tipologia)
			{
				case INSERIMENTO:
					m_sTipologia = "NW";
					break;
				case ANNULLAMENTO:
					m_sTipologia = "CA";
					break;
				default:
					m_sTipologia = "UK";
					break;
			}
			m_lIdUtente = idUtente;
			UpdateRecordset("CAnatomiaPatologicaRichiesteQueueSet::InserisciRecord");
		}

		CloseRecordset("CAnatomiaPatologicaRichiesteQueueSet::InserisciRecord");
	}
}

