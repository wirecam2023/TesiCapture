#include "stdafx.h"
#include "Endox.h"
#include "StrumentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CStrumentiSet, CBaseSet)

CStrumentiSet::CStrumentiSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

void CStrumentiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Testo", m_sTesto, 255);
		RFX_Text(pFX, "Sede", m_sSede, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CStrumentiSet::GetDefaultSQL()
{
	return "STRUMENTI";
}

void CStrumentiSet::SetEmpty()
{
	m_lContatore = 0;
	m_sTesto = "";
	m_sSede = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CStrumentiSet::CreateNew()
{
	return (CBaseSet*)new CStrumentiSet;
}

void CStrumentiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CStrumentiSet* pSet = (CStrumentiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTesto) || bCopyAll)
		m_sTesto = pSet->m_sTesto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSede) || bCopyAll)
		m_sSede = pSet->m_sSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CStrumentiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CStrumentiSet* pOV = (CStrumentiSet*)pOldValues;
	CStrumentiSet* pNV = (CStrumentiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Testo", pOV, &pOV->m_sTesto, pNV, &pNV->m_sTesto);
	sp.Execute("Sede", pOV, &pOV->m_sSede, pNV, &pNV->m_sSede);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CStrumentiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CStrumentiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CStrumentiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CStrumentiSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CStrumentiSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
