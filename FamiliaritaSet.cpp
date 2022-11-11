#include "stdafx.h"
#include "Endox.h"
#include "FamiliaritaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFamiliaritaSet, CBaseSet)

CFamiliaritaSet::CFamiliaritaSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CFamiliaritaSet::GetDefaultSQL()
{
	return "EFAMILIARITA";
}

void CFamiliaritaSet::SetEmpty()
{
	m_lContatore = 0;
	m_lPaziente = 0;
	m_sFamiliarita = "";
	m_lParentela = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CFamiliaritaSet::CopyFieldFrom(CFamiliaritaSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore = pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lPaziente))
		m_lPaziente = pSet->m_lPaziente;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sFamiliarita))
		m_sFamiliarita = pSet->m_sFamiliarita.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lParentela))
		m_lParentela = pSet->m_lParentela;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lUO))
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;

	if (IsOpen())
	{
		SetFieldNull(NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CFamiliaritaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Paziente", m_lPaziente);
		RFX_Text(pFX, "Familiarita", m_sFamiliarita, 3999);
		RFX_Long(pFX, "Parentela", m_lParentela);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CFamiliaritaSet::CreateNew()
{
	return (CBaseSet*)new CFamiliaritaSet;
}

void CFamiliaritaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFamiliaritaSet* pSet = (CFamiliaritaSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPaziente) || bCopyAll)
		m_lPaziente = pSet->m_lPaziente;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFamiliarita) || bCopyAll)
		m_sFamiliarita = pSet->m_sFamiliarita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lParentela) || bCopyAll)
		m_lParentela = pSet->m_lParentela;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CFamiliaritaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFamiliaritaSet* pOV = (CFamiliaritaSet*)pOldValues;
	CFamiliaritaSet* pNV = (CFamiliaritaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Paziente", pOV, &pOV->m_lPaziente, pNV, &pNV->m_lPaziente);
	sp.Execute("Familiarita", pOV, &pOV->m_sFamiliarita, pNV, &pNV->m_sFamiliarita);
	sp.Execute("Parentela", pOV, &pOV->m_lParentela, pNV, &pNV->m_lParentela);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFamiliaritaSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CFamiliaritaSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CFamiliaritaSet::DeleteRecordset");
	}
	return bReturn;
}

CString CFamiliaritaSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CFamiliaritaSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
