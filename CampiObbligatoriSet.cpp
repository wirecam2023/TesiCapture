#include "stdafx.h"
#include "Endox.h"
#include "CampiObbligatoriSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCampiObbligatoriSet, CBaseSet)

CCampiObbligatoriSet::CCampiObbligatoriSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CCampiObbligatoriSet::GetDefaultSQL()
{
	return "CampiObbligatori";
}

void CCampiObbligatoriSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID",	m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDTipoEsame", m_lIDTipoEsame);
		RFX_Long(pFX, "IDFaseNew", m_lIDFaseNew);
		RFX_Long(pFX, "Campo", m_lCampo);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CCampiObbligatoriSet::SetEmpty()
{
	m_lID = 0;
	m_lIDTipoEsame = 0;
	m_lIDFaseNew = -1;
	m_lCampo = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CCampiObbligatoriSet::CreateNew()
{
	return (CBaseSet*)new CCampiObbligatoriSet;
}

void CCampiObbligatoriSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCampiObbligatoriSet* pSet = (CCampiObbligatoriSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDFaseNew) || bCopyAll)
		m_lIDFaseNew = pSet->m_lIDFaseNew;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lCampo) || bCopyAll)
		m_lCampo = pSet->m_lCampo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCampiObbligatoriSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCampiObbligatoriSet* pOV = (CCampiObbligatoriSet*)pOldValues;
	CCampiObbligatoriSet* pNV = (CCampiObbligatoriSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("IDFaseNew", pOV, &pOV->m_lIDFaseNew, pNV, &pNV->m_lIDFaseNew);
	sp.Execute("Campo", pOV, &pOV->m_lCampo, pNV, &pNV->m_lCampo);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCampiObbligatoriSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCampiObbligatoriSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCampiObbligatoriSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCampiObbligatoriSet::SetBaseFilter(const CString &strFilter)
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

BOOL CCampiObbligatoriSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
