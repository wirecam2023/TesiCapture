#include "stdafx.h"
#include "Endox.h"
#include "ConfigurazioniListaPrenotazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CConfigurazioniListaPrenotazioniSet, CBaseSet)

CConfigurazioniListaPrenotazioniSet::CConfigurazioniListaPrenotazioniSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();
	SetSortRecord("Ordine");

	m_nFields = 7;
}

CString CConfigurazioniListaPrenotazioniSet::GetDefaultSQL()
{
	return "ConfigurazioniListaPren";
}

void CConfigurazioniListaPrenotazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Id", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Ordine", m_lOrdine);
		RFX_Text(pFX, "Titolo", m_sTitolo, 50);
		RFX_Text(pFX, "Campo", m_sCampo, 255);
		RFX_Long(pFX, "Dimensione", m_lDimensione);
		RFX_Long(pFX, "DimensioneStampaPerc", m_lDimensioneStampaPerc);	
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CConfigurazioniListaPrenotazioniSet::SetEmpty()
{
	m_lID = 0;
	m_lOrdine = 0;
	m_sTitolo = "";
	m_sCampo = "";
	m_lDimensione = 0;
	m_lDimensioneStampaPerc = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CConfigurazioniListaPrenotazioniSet::CreateNew()
{
	return (CBaseSet*)new CConfigurazioniListaPrenotazioniSet;
}

void CConfigurazioniListaPrenotazioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CConfigurazioniListaPrenotazioniSet* pSet = (CConfigurazioniListaPrenotazioniSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitolo) || bCopyAll)
		m_sTitolo = pSet->m_sTitolo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCampo) || bCopyAll)
		m_sCampo = pSet->m_sCampo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDimensione) || bCopyAll)
		m_lDimensione = pSet->m_lDimensione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDimensioneStampaPerc) || bCopyAll)
		m_lDimensioneStampaPerc = pSet->m_lDimensioneStampaPerc;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CConfigurazioniListaPrenotazioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CConfigurazioniListaPrenotazioniSet* pOV = (CConfigurazioniListaPrenotazioniSet*)pOldValues;
	CConfigurazioniListaPrenotazioniSet* pNV = (CConfigurazioniListaPrenotazioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Ordine", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("Titolo", pOV, &pOV->m_sTitolo, pNV, &pNV->m_sTitolo);
	sp.Execute("Campo", pOV, &pOV->m_sCampo, pNV, &pNV->m_sCampo);
	sp.Execute("Dimensione", pOV, &pOV->m_lDimensione, pNV, &pNV->m_lDimensione);
	sp.Execute("Percorso", pOV, &pOV->m_lDimensioneStampaPerc, pNV, &pNV->m_lDimensioneStampaPerc);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CConfigurazioniListaPrenotazioniSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CConfigurazioniListaPrenotazioniSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CConfigurazioniListaPrenotazioniSet::DeleteRecordset");
	}
	return bReturn;
}

CString CConfigurazioniListaPrenotazioniSet::SetBaseFilter(const CString &strFilter)
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