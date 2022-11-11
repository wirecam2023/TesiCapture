#include "stdafx.h"
#include "Endox.h"
#include "EndoGridParameterRulesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridParameterRulesSet, CBaseSet)

CEndoGridParameterRulesSet::CEndoGridParameterRulesSet(BOOL bJoin, CDatabase* pDatabase)
: CBaseSet((bJoin ? NULL : &m_id), (bJoin ? "VIEW" : "ID"))
{
	SetEmpty();
	SetBaseFilter("");
	SetSortRecord("tiporegola, ordine");

	m_nFields = bJoin ? 17 : 11;

	m_bJoin = bJoin;	
}

void CEndoGridParameterRulesSet::SetEmpty()
{
	m_id = 0;
	m_tiporegola = 0;
	m_idparametro1 = 0;
	m_operatore = 0;
	m_valore = "";
	m_idparametro2 = 0;
	m_valore2 = "";
	m_nota = "";
	m_colore = 0;
	m_ordine = 0;
	m_bEliminato = FALSE;

	m_nomeparametro1 = "";
	m_note1 = "";
	m_fbisd1 = 0;
	m_nomeparametro2 = "";
	m_note2 = "";
	m_fbisd2 = 0;
}

void CEndoGridParameterRulesSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("ID"), m_id);
	RFX_Long(pFX, _T("TIPOREGOLA"), m_tiporegola);
	RFX_Long(pFX, _T("IDPARAMETRO1"), m_idparametro1);
	RFX_Long(pFX, _T("OPERATORE"), m_operatore);
	RFX_Text(pFX, _T("VALORE"), m_valore);
	RFX_Long(pFX, _T("IDPARAMETRO2"), m_idparametro2);
	RFX_Text(pFX, _T("VALORE2"), m_valore2);
	RFX_Text(pFX, _T("NOTA"), m_nota);
	RFX_Long(pFX, _T("COLORE"), m_colore);
	RFX_Long(pFX, _T("ORDINE"), m_ordine);
	RFX_Bool(pFX, _T("ELIMINATO"), m_bEliminato);

	if (m_bJoin)
	{		
		RFX_Text(pFX, _T("NOMEPARAMETRO1"), m_nomeparametro1);
		RFX_Text(pFX, _T("NOTE1"), m_note1);
		RFX_Long(pFX, _T("FBISD1"), m_fbisd1);
		RFX_Text(pFX, _T("NOMEPARAMETRO2"), m_nomeparametro2);
		RFX_Text(pFX, _T("NOTE2"), m_note2);
		RFX_Long(pFX, _T("FBISD2"), m_fbisd2);
	}
}

CString CEndoGridParameterRulesSet::GetDefaultSQL()
{
	return m_bJoin ? _T("GRIDCL_PAR_REGOLE_JOIN") : _T("GRIDCL_PAR_REGOLE");
}

CString CEndoGridParameterRulesSet::SetSortRecord(const CString& strSort)
{
	return CBaseSet::SetSortRecord(strSort);
}

CBaseSet* CEndoGridParameterRulesSet::CreateNew()
{
	CEndoGridParameterRulesSet* pNewSet = new CEndoGridParameterRulesSet(m_bJoin);

	return (CBaseSet*)pNewSet;
}

void CEndoGridParameterRulesSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEndoGridParameterRulesSet* pSet = (CEndoGridParameterRulesSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_tiporegola) || bCopyAll)
		m_tiporegola = pSet->m_tiporegola;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_idparametro1) || bCopyAll)
		m_idparametro1 = pSet->m_idparametro1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_operatore) || bCopyAll)
		m_operatore = pSet->m_operatore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_valore) || bCopyAll)
		m_valore = pSet->m_valore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_idparametro2) || bCopyAll)
		m_idparametro2 = pSet->m_idparametro2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_valore2) || bCopyAll)
		m_valore2 = pSet->m_valore2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_nota) || bCopyAll)
		m_nota = pSet->m_nota;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_colore) || bCopyAll)
		m_colore = pSet->m_colore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_ordine) || bCopyAll)
		m_ordine = pSet->m_ordine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEndoGridParameterRulesSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEndoGridParameterRulesSet* pOV = (CEndoGridParameterRulesSet*)pOldValues;
	CEndoGridParameterRulesSet* pNV = (CEndoGridParameterRulesSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("TIPOREGOLA", pOV, &pOV->m_tiporegola, pNV, &pNV->m_tiporegola);
	sp.Execute("IDPARAMETRO1", pOV, &pOV->m_idparametro1, pNV, &pNV->m_idparametro1);
	sp.Execute("OPERATORE", pOV, &pOV->m_operatore, pNV, &pNV->m_operatore);
	sp.Execute("VALORE", pOV, &pOV->m_valore, pNV, &pNV->m_valore);
	sp.Execute("IDPARAMETRO2", pOV, &pOV->m_idparametro2, pNV, &pNV->m_idparametro2);
	sp.Execute("VALORE2", pOV, &pOV->m_valore2, pNV, &pNV->m_valore2);
	sp.Execute("ORDINE", pOV, &pOV->m_nota, pNV, &pNV->m_nota);
	sp.Execute("COLORE", pOV, &pOV->m_colore, pNV, &pNV->m_colore);
	sp.Execute("ORDINE", pOV, &pOV->m_ordine, pNV, &pNV->m_ordine);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEndoGridParameterRulesSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEndoGridParameterRulesSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEndoGridParameterRulesSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEndoGridParameterRulesSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CEndoGridParameterRulesSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}
