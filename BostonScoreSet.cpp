#include "stdafx.h"
#include "Endox.h"
#include "BostonScoreSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CBostonScoreSet, CBaseSet)

CBostonScoreSet::CBostonScoreSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

void CBostonScoreSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Valore", m_lValore);
		RFX_Text(pFX, "FraseStampata", m_sFraseStampata, 4000);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CBostonScoreSet::GetDefaultSQL()
{
	return "BostonScore";
}

void CBostonScoreSet::SetEmpty()
{
	m_lID = 0;
	m_lValore = -1;
	m_sFraseStampata = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CBostonScoreSet::CreateNew()
{
	return (CBaseSet*)new CBostonScoreSet;
}

void CBostonScoreSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CBostonScoreSet* pSet = (CBostonScoreSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lValore) || bCopyAll)
		m_lValore = pSet->m_lValore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFraseStampata) || bCopyAll)
		m_sFraseStampata = pSet->m_sFraseStampata;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CBostonScoreSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CBostonScoreSet* pOV = (CBostonScoreSet*)pOldValues;
	CBostonScoreSet* pNV = (CBostonScoreSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Valore", pOV, &pOV->m_lValore, pNV, &pNV->m_lValore);
	sp.Execute("FraseStampata", pOV, &pOV->m_sFraseStampata, pNV, &pNV->m_sFraseStampata);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CBostonScoreSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CBostonScoreSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CBostonScoreSet::DeleteRecordset");
	}
	return bReturn;
}

CString CBostonScoreSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CBostonScoreSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

void CBostonScoreSet::AddEdt(long lValore, CString sFraseStampata)
{
	CString sFilter;
	sFilter.Format("Valore=%li", lValore);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CBostonScoreSet::AddEdt"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CBostonScoreSet::AddEdt"))
			{
				m_lValore = lValore;
				m_sFraseStampata = sFraseStampata;
				UpdateRecordset("CBostonScoreSet::AddEdt");
			}
		}
		else
		{
			if (EditRecordset("CBostonScoreSet::AddEdt"))
			{
				m_sFraseStampata = sFraseStampata;
				UpdateRecordset("CBostonScoreSet::AddEdt");
			}
		}

		CloseRecordset("CBostonScoreSet::AddEdt");
	}
}
