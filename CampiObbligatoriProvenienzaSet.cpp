#include "stdafx.h"
#include "Endox.h"
#include "CampiObbligatoriProvenienzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCampiObbligatoriProvenienzaSet, CAMBaseSet)

CCampiObbligatoriProvenienzaSet::CCampiObbligatoriProvenienzaSet()
: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CCampiObbligatoriProvenienzaSet::GetDefaultSQL()
{
	return "CAMPIOBBLIGATORIPROVENIENZA";
}

void CCampiObbligatoriProvenienzaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CAMBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lId);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDCAMPOOBBLIGATORIO", m_lIdCampiObbligatori);
		RFX_Long(pFX, "IDPROVENIENZA", m_lIdProvenienza);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

void CCampiObbligatoriProvenienzaSet::SetEmpty()
{
	m_lId = 0;
	m_lIdCampiObbligatori = 0;
	m_lIdProvenienza = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CCampiObbligatoriProvenienzaSet::CreateNew()
{
	return (CBaseSet*)new CCampiObbligatoriProvenienzaSet;
}

void CCampiObbligatoriProvenienzaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCampiObbligatoriProvenienzaSet* pSet = (CCampiObbligatoriProvenienzaSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdCampiObbligatori) || bCopyAll)
		m_lIdCampiObbligatori = pSet->m_lIdCampiObbligatori;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdProvenienza) || bCopyAll)
		m_lIdProvenienza = pSet->m_lIdProvenienza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCampiObbligatoriProvenienzaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCampiObbligatoriProvenienzaSet* pOV = (CCampiObbligatoriProvenienzaSet*)pOldValues;
	CCampiObbligatoriProvenienzaSet* pNV = (CCampiObbligatoriProvenienzaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDCAMPOOBBLIGATORIO", pOV, &pOV->m_lIdCampiObbligatori, pNV, &pNV->m_lIdCampiObbligatori);
	sp.Execute("IDPROVENIENZA", pOV, &pOV->m_lIdProvenienza, pNV, &pNV->m_lIdProvenienza);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCampiObbligatoriProvenienzaSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCampiObbligatoriProvenienzaSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCampiObbligatoriProvenienzaSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCampiObbligatoriProvenienzaSet::SetBaseFilter(const CString &strFilter)
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

BOOL CCampiObbligatoriProvenienzaSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

