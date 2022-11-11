#include "stdafx.h"
#include "Endox.h"
#include "EsamiPregressiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiPregressiSet, CBaseSet)

CEsamiPregressiSet::CEsamiPregressiSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	m_lContatore = 0;
	m_lEsame = 0;
	m_lData = 0;
	m_sEsamePregresso = "";
	m_sEsito = "";
	m_bEliminato = FALSE;

	m_nFields = 6;
	SetBaseFilter("");
}

CString CEsamiPregressiSet::GetDefaultSQL()
{
	return "ESAMIPREGRESSI";
}

void CEsamiPregressiSet::SetEmpty()
{
	m_lContatore = 0;
	m_lEsame = 0;
	m_lData = 0;
	m_sEsamePregresso = "";
	m_sEsito = "";
	m_bEliminato = FALSE;
}

void CEsamiPregressiSet::CopyFieldFrom(CEsamiPregressiSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore = pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame = pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lData))
		m_lData = pSet->m_lData;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sEsamePregresso))
		m_sEsamePregresso = pSet->m_sEsamePregresso.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sEsito))
		m_sEsito = pSet->m_sEsito.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;

	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CEsamiPregressiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore",		 m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "Esame",			 m_lEsame);
		RFX_Long (pFX, "Data",			 m_lData);
		RFX_Text (pFX, "EsamePregresso", m_sEsamePregresso,	3999);
		RFX_Text (pFX, "Esito",			 m_sEsito,			3999);
		RFX_Bool (pFX, "Eliminato",		 m_bEliminato);
	}
}

CBaseSet* CEsamiPregressiSet::CreateNew()
{
	return (CBaseSet*)new CEsamiPregressiSet;
}

void CEsamiPregressiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiPregressiSet* pEsamiPregressiSet = (CEsamiPregressiSet*)pOriginalSet;

	if (!pEsamiPregressiSet->IsOpen() || pEsamiPregressiSet->IsFieldDirty(&pEsamiPregressiSet->m_lEsame) || bCopyAll)
		m_lEsame = pEsamiPregressiSet->m_lEsame;
	if (!pEsamiPregressiSet->IsOpen() || pEsamiPregressiSet->IsFieldDirty(&pEsamiPregressiSet->m_lData) || bCopyAll)
		m_lData = pEsamiPregressiSet->m_lData;
	if (!pEsamiPregressiSet->IsOpen() || pEsamiPregressiSet->IsFieldDirty(&pEsamiPregressiSet->m_sEsamePregresso) || bCopyAll)
		m_sEsamePregresso = pEsamiPregressiSet->m_sEsamePregresso;
	if (!pEsamiPregressiSet->IsOpen() || pEsamiPregressiSet->IsFieldDirty(&pEsamiPregressiSet->m_sEsito) || bCopyAll)
		m_sEsito = pEsamiPregressiSet->m_sEsito;
	if (!pEsamiPregressiSet->IsOpen() || pEsamiPregressiSet->IsFieldDirty(&pEsamiPregressiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pEsamiPregressiSet->m_bEliminato;
}

void CEsamiPregressiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiPregressiSet* pOV = (CEsamiPregressiSet*)pOldValues;
	CEsamiPregressiSet* pNV = (CEsamiPregressiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Data", pOV, &pOV->m_lData, pNV, &pNV->m_lData);
	sp.Execute("EsamePregresso", pOV, &pOV->m_sEsamePregresso, pNV, &pNV->m_sEsamePregresso);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEsamiPregressiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEsamiPregressiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEsamiPregressiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEsamiPregressiSet::SetBaseFilter(const CString &strFilter)
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