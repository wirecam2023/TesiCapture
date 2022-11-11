#include "stdafx.h"
#include "Endox.h"
#include "VitalSignDispositiviSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVitalSignDispositiviSet, CBaseSet)

CVitalSignDispositiviSet::CVitalSignDispositiviSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CVitalSignDispositiviSet::GetDefaultSQL()
{
	return "VitalSign_Dispositivi";
}

void CVitalSignDispositiviSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "CodiceIdentificativo", m_sCodiceIdentificativo, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CVitalSignDispositiviSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sCodiceIdentificativo = "";	
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CVitalSignDispositiviSet::CreateNew()
{
	return (CBaseSet*)new CVitalSignDispositiviSet;
}

void CVitalSignDispositiviSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CVitalSignDispositiviSet* pSet = (CVitalSignDispositiviSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceIdentificativo) || bCopyAll)
		m_sCodiceIdentificativo = pSet->m_sCodiceIdentificativo;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CVitalSignDispositiviSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CVitalSignDispositiviSet* pOV = (CVitalSignDispositiviSet*)pOldValues;
	CVitalSignDispositiviSet* pNV = (CVitalSignDispositiviSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("CodiceIdentificativo", pOV, &pOV->m_sCodiceIdentificativo, pNV, &pNV->m_sCodiceIdentificativo);	
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CVitalSignDispositiviSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CVitalSignDispositiviSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CVitalSignDispositiviSet::DeleteRecordset");
	}
	return bReturn;
}

CString CVitalSignDispositiviSet::SetBaseFilter(const CString &strFilter)
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

CString CVitalSignDispositiviSet::GetDescrizione(long id)
{
	CString sReturn = "";

	CString filter;
	filter.Format("id=%li", id);

	SetOpenFilter(filter);

	if (OpenRecordset("CVitalSignDispositiviSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CVitalSignDispositiviSet::GetDescrizione");
	}

	return sReturn;
}

BOOL CVitalSignDispositiviSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}