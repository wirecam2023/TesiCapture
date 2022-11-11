#include "stdafx.h"
#include "Endox.h"
#include "MstOrganoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstOrganoSet, CBaseSet)

CMstOrganoSet::CMstOrganoSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CMstOrganoSet::GetDefaultSQL()
{
	return "EMSTORGANO";
}

void CMstOrganoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Organo", m_sOrgano, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CMstOrganoSet::SetEmpty()
{
	m_lContatore = 0;
	m_sOrgano = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CString CMstOrganoSet::GetFieldText(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CMstOrganoSet::GetFieldText"))
	{
		if (!IsEOF())
			strReturn = m_sOrgano;

		CloseRecordset("CMstOrganoSet::GetFieldText");
	}

	return strReturn;
}

CBaseSet* CMstOrganoSet::CreateNew()
{
	return (CBaseSet*)new CMstOrganoSet;
}

void CMstOrganoSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMstOrganoSet* pSet = (CMstOrganoSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sOrgano) || bCopyAll)
		m_sOrgano = pSet->m_sOrgano;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CMstOrganoSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMstOrganoSet* pOV = (CMstOrganoSet*)pOldValues;
	CMstOrganoSet* pNV = (CMstOrganoSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Organo", pOV, &pOV->m_sOrgano, pNV, &pNV->m_sOrgano);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMstOrganoSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMstOrganoSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMstOrganoSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMstOrganoSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CMstOrganoSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
