#include "stdafx.h"
#include "Endox.h"
#include "EsamiCaricoAnnullatoSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiCaricoAnnullatoSet, CBaseSet)

CEsamiCaricoAnnullatoSet::CEsamiCaricoAnnullatoSet()
: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CEsamiCaricoAnnullatoSet::GetDefaultSQL()
{
	return "EXT_ESAMI_CARICOANNULLATO";
}

void CEsamiCaricoAnnullatoSet::DoFieldExchange(CFieldExchange* pFX)
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

void CEsamiCaricoAnnullatoSet::SetEmpty()
{
	m_lId = 0;
	m_lIdOrdine = 0;
	m_sDataOra = "";
	m_bEseguito = FALSE;
	m_lIdUtente = 0;
	m_sEsito = "";
}

CBaseSet* CEsamiCaricoAnnullatoSet::CreateNew()
{
	return (CBaseSet*)new CEsamiCaricoAnnullatoSet;
}

void CEsamiCaricoAnnullatoSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiCaricoAnnullatoSet* pEsamiCaricoAnnullato = (CEsamiCaricoAnnullatoSet*)pOriginalSet;

	if (!pEsamiCaricoAnnullato->IsOpen() || pEsamiCaricoAnnullato->IsFieldDirty(&pEsamiCaricoAnnullato->m_lIdOrdine) || bCopyAll)
		m_lIdOrdine = pEsamiCaricoAnnullato->m_lIdOrdine;
	if (!pEsamiCaricoAnnullato->IsOpen() || pEsamiCaricoAnnullato->IsFieldDirty(&pEsamiCaricoAnnullato->m_sDataOra) || bCopyAll)
		m_sDataOra = pEsamiCaricoAnnullato->m_sDataOra;
	if (!pEsamiCaricoAnnullato->IsOpen() || pEsamiCaricoAnnullato->IsFieldDirty(&pEsamiCaricoAnnullato->m_bEseguito) || bCopyAll)
		m_bEseguito = pEsamiCaricoAnnullato->m_bEseguito;
	if (!pEsamiCaricoAnnullato->IsOpen() || pEsamiCaricoAnnullato->IsFieldDirty(&pEsamiCaricoAnnullato->m_lIdUtente) || bCopyAll)
		m_lIdUtente = pEsamiCaricoAnnullato->m_lIdUtente;
	if (!pEsamiCaricoAnnullato->IsOpen() || pEsamiCaricoAnnullato->IsFieldDirty(&pEsamiCaricoAnnullato->m_sEsito) || bCopyAll)
		m_sEsito = pEsamiCaricoAnnullato->m_sEsito;
}

void CEsamiCaricoAnnullatoSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiCaricoAnnullatoSet* pOV = (CEsamiCaricoAnnullatoSet*)pOldValues;
	CEsamiCaricoAnnullatoSet* pNV = (CEsamiCaricoAnnullatoSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdOrdine", pOV, &pOV->m_lIdOrdine, pNV, &pNV->m_lIdOrdine);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("Eseguito", pOV, &pOV->m_bEseguito, pNV, &pNV->m_bEseguito);
	sp.Execute("IdUtente", pOV, &pOV->m_lIdUtente, pNV, &pNV->m_lIdUtente);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

CString CEsamiCaricoAnnullatoSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CEsamiCaricoAnnullatoSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CEsamiCaricoAnnullatoSet::InserisciRecord(long idOrdine, long idUtente)
{
	ASSERT(idOrdine > 0 && idUtente > 0);

	CBaseSet::SetBaseFilter("");

	if (OpenRecordset("CEsamiCaricoAnnullatoSet::InserisciRecord"))
	{
		if (AddNewRecordset("CEsamiCaricoAnnullatoSet::InserisciRecord"))
		{
			m_lIdOrdine = idOrdine;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_lIdUtente = idUtente;
			m_sEsito = "";
			UpdateRecordset("CEsamiCaricoAnnullatoSet::InserisciRecord");
		}

		CloseRecordset("CEsamiCaricoAnnullatoSet::InserisciRecord");
	}
}
//Julio Correcao do problema de exames em pacientes errados
void CEsamiCaricoAnnullatoSet::InserisciRecordForFaliure(long idUtente, long lIdLastAdd, CString sOrderNumber)
{
	CString sMessage;
	sMessage.Format("O sistema detectou que o GetLastAdd retornou [%li] enquanto tentava inserir o exame [%s]", lIdLastAdd, sOrderNumber);
	CBaseSet::SetBaseFilter("");

	if (OpenRecordset("CEsamiCaricoAnnullatoSet::InserisciRecordForFaliure"))
	{
		if (AddNewRecordset("CEsamiCaricoAnnullatoSet::InserisciRecordForFaliure"))
		{
			m_lIdOrdine = 0;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_lIdUtente = idUtente;
			m_sEsito = sMessage;
			m_bEseguito = TRUE;
			UpdateRecordset("CEsamiCaricoAnnullatoSet::InserisciRecordForFaliure");
		}

		CloseRecordset("CEsamiCaricoAnnullatoSet::InserisciRecordForFaliure");
	}
}