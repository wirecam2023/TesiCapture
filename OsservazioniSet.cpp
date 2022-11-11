#include "stdafx.h"
#include "Endox.h"
#include "OsservazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COsservazioniSet, CBaseSet)

COsservazioniSet::COsservazioniSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	m_lContatore		= 0;
	m_lEsame			= 0;
	m_lOrgano			= -1;
	m_sSede				= "";
	m_sOsservazioni		= "";
	m_bEliminato        = FALSE;

	m_nFields = 6;
	SetBaseFilter("");
}

CString COsservazioniSet::GetDefaultSQL()
{
	return "EOsservazioni";
}

void COsservazioniSet::SetEmpty()
{
	m_lContatore		= 0;
	m_lEsame			= 0;
	m_lOrgano			= -1;
	m_sSede				= "";
	m_sOsservazioni		= "";
	m_bEliminato        = FALSE;
}

void COsservazioniSet::CopyFieldFrom(COsservazioniSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore = pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame = pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lOrgano))
		m_lOrgano = pSet->m_lOrgano;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sSede))
		m_sSede = pSet->m_sSede.Left(255);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sOsservazioni))
		m_sOsservazioni = pSet->m_sOsservazioni.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;
	
	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void COsservazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore",			m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "Esame",				m_lEsame);
		RFX_Long (pFX, "Organo",			m_lOrgano);
		RFX_Text (pFX, "Sede",				m_sSede,		  255);
		RFX_Text (pFX, "Osservazioni",		m_sOsservazioni, 3999);
		RFX_Bool (pFX, "Eliminato",         m_bEliminato);
	}
}

CBaseSet* COsservazioniSet::CreateNew()
{
	return (CBaseSet*)new COsservazioniSet;
}

void COsservazioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	COsservazioniSet* pOsservazioniSet = (COsservazioniSet*)pOriginalSet;

	if (!pOsservazioniSet->IsOpen() || pOsservazioniSet->IsFieldDirty(&pOsservazioniSet->m_lEsame) || bCopyAll)
		m_lEsame = pOsservazioniSet->m_lEsame;
	if (!pOsservazioniSet->IsOpen() || pOsservazioniSet->IsFieldDirty(&pOsservazioniSet->m_lOrgano) || bCopyAll)
		m_lOrgano = pOsservazioniSet->m_lOrgano;
	if (!pOsservazioniSet->IsOpen() || pOsservazioniSet->IsFieldDirty(&pOsservazioniSet->m_sSede) || bCopyAll)
		m_sSede = pOsservazioniSet->m_sSede;
	if (!pOsservazioniSet->IsOpen() || pOsservazioniSet->IsFieldDirty(&pOsservazioniSet->m_sOsservazioni) || bCopyAll)
		m_sOsservazioni = pOsservazioniSet->m_sOsservazioni;
	if (!pOsservazioniSet->IsOpen() || pOsservazioniSet->IsFieldDirty(&pOsservazioniSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pOsservazioniSet->m_bEliminato;
}

void COsservazioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	COsservazioniSet* pOV = (COsservazioniSet*)pOldValues;
	COsservazioniSet* pNV = (COsservazioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Organo", pOV, &pOV->m_lOrgano, pNV, &pNV->m_lOrgano);
	sp.Execute("Sede", pOV, &pOV->m_sSede, pNV, &pNV->m_sSede);
	sp.Execute("Osservazioni", pOV, &pOV->m_sOsservazioni, pNV, &pNV->m_sOsservazioni);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL COsservazioniSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("COsservazioniSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("COsservazioniSet::DeleteRecordset");
	}
	return bReturn;
}

CString COsservazioniSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty() == TRUE)
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}