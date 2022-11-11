#include "stdafx.h"
#include "Endox.h"
#include "CampiObbligatoriPazienteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCampiObbligatoriPazienteSet, CBaseSet)

CCampiObbligatoriPazienteSet::CCampiObbligatoriPazienteSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CCampiObbligatoriPazienteSet::GetDefaultSQL()
{
	return "CampiObbligatoriPaziente";
}

void CCampiObbligatoriPazienteSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID",	m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 50);
		RFX_Long(pFX, "IDStatic", m_lIDStatic);
		RFX_Long(pFX, "IDEdit", m_lIDEdit);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CCampiObbligatoriPazienteSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lIDStatic = 0;
	m_lIDEdit = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CCampiObbligatoriPazienteSet::CreateNew()
{
	return (CBaseSet*)new CCampiObbligatoriPazienteSet;
}

void CCampiObbligatoriPazienteSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCampiObbligatoriPazienteSet* pSet = (CCampiObbligatoriPazienteSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDStatic) || bCopyAll)
		m_lIDStatic = pSet->m_lIDStatic;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEdit) || bCopyAll)
		m_lIDEdit = pSet->m_lIDEdit;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCampiObbligatoriPazienteSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCampiObbligatoriPazienteSet* pOV = (CCampiObbligatoriPazienteSet*)pOldValues;
	CCampiObbligatoriPazienteSet* pNV = (CCampiObbligatoriPazienteSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("IDStatic", pOV, &pOV->m_lIDStatic, pNV, &pNV->m_lIDStatic);
	sp.Execute("IDEdit", pOV, &pOV->m_lIDEdit, pNV, &pNV->m_lIDEdit);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCampiObbligatoriPazienteSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCampiObbligatoriPazienteSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCampiObbligatoriPazienteSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCampiObbligatoriPazienteSet::SetBaseFilter(const CString &strFilter)
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

BOOL CCampiObbligatoriPazienteSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

BOOL CCampiObbligatoriPazienteSet::IsObbligatorioEdit(long lIDEdit)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("IDEdit=%li", lIDEdit);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCampiObbligatoriPazienteSet::IsObbligatorioEdit"))
	{
		if (!IsEOF())
			bReturn = TRUE;

		CloseRecordset("CCampiObbligatoriPazienteSet::IsObbligatorioEdit");
	}

	return bReturn;
}

BOOL CCampiObbligatoriPazienteSet::IsObbligatorioStatic(long lIDStatic)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("IDStatic=%li", lIDStatic);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCampiObbligatoriPazienteSet::IsObbligatorioStatic"))
	{
		if (!IsEOF())
			bReturn = TRUE;

		CloseRecordset("CCampiObbligatoriPazienteSet::IsObbligatorioStatic");
	}

	return bReturn;
}

CString CCampiObbligatoriPazienteSet::GetDescrizione(long lIDEdit)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("IDEdit=%li", lIDEdit);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CCampiObbligatoriPazienteSet::GetDescrizione"))
	{
		if (!IsEOF())
			strReturn = m_sDescrizione;

		CloseRecordset("CCampiObbligatoriPazienteSet::GetDescrizione");
	}

	return strReturn;
}