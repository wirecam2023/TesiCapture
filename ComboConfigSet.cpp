#include "stdafx.h"
#include "Endox.h"
#include "ComboConfigSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboConfigSet, CBaseSet)

CComboConfigSet::CComboConfigSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

CString CComboConfigSet::GetDefaultSQL()
{
	return "ECOMBOCONFIGURAZIONI";
}

void CComboConfigSet::SetEmpty()
{
	m_lContatore = 0;
	m_lTabella = 0;
	m_sConfigurazione = "";
	m_lParametroNum = 0;
	m_sParametroStr = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CComboConfigSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Tabella",			m_lTabella);
		RFX_Text(pFX, "Configurazione",		m_sConfigurazione,	 50);
		RFX_Long(pFX, "ParametroNum",		m_lParametroNum);
		RFX_Text(pFX, "ParametroStr",		m_sParametroStr,	255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato",         m_bEliminato);
	}
}

CBaseSet* CComboConfigSet::CreateNew()
{
	return (CBaseSet*)new CComboConfigSet;
}

void CComboConfigSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CComboConfigSet* pSet = (CComboConfigSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTabella) || bCopyAll)
		m_lTabella = pSet->m_lTabella;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sConfigurazione) || bCopyAll)
		m_sConfigurazione = pSet->m_sConfigurazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lParametroNum) || bCopyAll)
		m_lParametroNum = pSet->m_lParametroNum;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sParametroStr) || bCopyAll)
		m_sParametroStr = pSet->m_sParametroStr;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CComboConfigSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CComboConfigSet* pOV = (CComboConfigSet*)pOldValues;
	CComboConfigSet* pNV = (CComboConfigSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Tabella", pOV, &pOV->m_lTabella, pNV, &pNV->m_lTabella);
	sp.Execute("Configurazione", pOV, &pOV->m_sConfigurazione, pNV, &pNV->m_sConfigurazione);
	sp.Execute("ParametroNum", pOV, &pOV->m_lParametroNum, pNV, &pNV->m_lParametroNum);
	sp.Execute("ParametroStr", pOV, &pOV->m_sParametroStr, pNV, &pNV->m_sParametroStr);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CComboConfigSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CComboConfigSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CComboConfigSet::DeleteRecordset");
	}
	return bReturn;
}

CString CComboConfigSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CComboConfigSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
