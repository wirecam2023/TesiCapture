#include "stdafx.h"
#include "Endox.h"
#include "NreLottiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CNRELottiSet, CBaseSet)

CNRELottiSet::CNRELottiSet()
	: CBaseSet(&m_lId, "ID")
{
	SetEmpty();

	m_nFields = 7;
}

CString CNRELottiSet::GetDefaultSQL()
{
	return "NRELOTTI";
}

void CNRELottiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "id",	m_lId);
	if (m_nFields > 1)
	{
		RFX_Text (pFX, "regione",	m_sRegione,	3);
		RFX_Text (pFX, "codRaggruppamento",	m_sCodRaggruppamento,	2);
		RFX_Text (pFX, "codiceLotto",	m_sCodiceLotto,	7);
		RFX_Long (pFX, "contatore",	m_lContatore);
		RFX_Long (pFX, "maxContatore",	m_lContatoreMax);
		RFX_Long (pFX, "idUtente",	m_lIdUtente);
	}
}

void CNRELottiSet::SetEmpty()
{
	m_lId = 0;
	m_sRegione = "";
	m_sCodRaggruppamento = "";
	m_sCodiceLotto = "";
	m_lContatore = 0;
	m_lContatoreMax = 0;
	m_lIdUtente = 0;
}

CBaseSet* CNRELottiSet::CreateNew()
{
	return (CBaseSet*)new CNRELottiSet;
}

void CNRELottiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CNRELottiSet* pSet = (CNRELottiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRegione) || bCopyAll)
		m_sRegione = pSet->m_sRegione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodRaggruppamento) || bCopyAll)
		m_sCodRaggruppamento = pSet->m_sCodRaggruppamento;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceLotto) || bCopyAll)
		m_sCodiceLotto = pSet->m_sCodiceLotto;
	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lContatore) || bCopyAll)
		m_lContatore = pSet->m_lContatore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lContatoreMax) || bCopyAll)
		m_lContatoreMax = pSet->m_lContatoreMax;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdUtente) || bCopyAll)
		m_lIdUtente = pSet->m_lIdUtente;
	
}

void CNRELottiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CNRELottiSet* pOV = (CNRELottiSet*)pOldValues;
	CNRELottiSet* pNV = (CNRELottiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("regione", pOV, &pOV->m_sRegione, pNV, &pNV->m_sRegione);
	sp.Execute("codRaggruppamento", pOV, &pOV->m_sCodRaggruppamento, pNV, &pNV->m_sCodRaggruppamento);
	sp.Execute("codiceLotto", pOV, &pOV->m_sCodiceLotto, pNV, &pNV->m_sCodiceLotto);

	sp.Execute("contatore", pOV, &pOV->m_lContatore, pNV, &pNV->m_lContatore);
	sp.Execute("maxContatore", pOV, &pOV->m_lContatoreMax, pNV, &pNV->m_lContatoreMax);
	sp.Execute("idUtente", pOV, &pOV->m_lIdUtente, pNV, &pNV->m_lIdUtente);
}

BOOL CNRELottiSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}