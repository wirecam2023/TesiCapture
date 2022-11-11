#include "stdafx.h"
#include "Endox.h"
#include "EsamiAccessoriSet.h"

#include "ComboBoxSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiAccessoriSet, CBaseSet)

CEsamiAccessoriSet::CEsamiAccessoriSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CEsamiAccessoriSet::GetDefaultSQL()
{
	return "ESAMIACCESSORI";
}

void CEsamiAccessoriSet::SetEmpty()
{
	m_lContatore = 0;
	m_lEsame = 0;
	m_lCodice = 0;
	m_lQuantita = 0;
	m_bEliminato = FALSE;
}

void CEsamiAccessoriSet::CopyFieldFrom(CEsamiAccessoriSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore	= pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame	= pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lCodice))
		m_lCodice	= pSet->m_lCodice;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lQuantita))
		m_lQuantita	= pSet->m_lQuantita;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;
		
	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CEsamiAccessoriSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Esame", m_lEsame);
		RFX_Long(pFX, "Codice", m_lCodice);
		RFX_Long(pFX, "Quantita", m_lQuantita);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CEsamiAccessoriSet::GetFieldText(long lEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Esame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CEsamiAccessoriSet::GetFieldText"))
	{
		while(!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += "\n";

			strReturn += CComboBoxSet(CMB_ESA_ACCESS).GetFieldText(m_lCodice);

			MoveNext();
		}
		CloseRecordset("CEsamiAccessoriSet::GetFieldText");
	}

	return strReturn;
}

CBaseSet* CEsamiAccessoriSet::CreateNew()
{
	return (CBaseSet*)new CEsamiAccessoriSet;
}

void CEsamiAccessoriSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiAccessoriSet* pEsamiAccessoriSet = (CEsamiAccessoriSet*)pOriginalSet;

	if (!pEsamiAccessoriSet->IsOpen() || pEsamiAccessoriSet->IsFieldDirty(&pEsamiAccessoriSet->m_lEsame) || bCopyAll)
		m_lEsame = pEsamiAccessoriSet->m_lEsame;
	if (!pEsamiAccessoriSet->IsOpen() || pEsamiAccessoriSet->IsFieldDirty(&pEsamiAccessoriSet->m_lCodice) || bCopyAll)
		m_lCodice = pEsamiAccessoriSet->m_lCodice;
	if (!pEsamiAccessoriSet->IsOpen() || pEsamiAccessoriSet->IsFieldDirty(&pEsamiAccessoriSet->m_lQuantita) || bCopyAll)
		m_lQuantita = pEsamiAccessoriSet->m_lQuantita;
	if (!pEsamiAccessoriSet->IsOpen() || pEsamiAccessoriSet->IsFieldDirty(&pEsamiAccessoriSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pEsamiAccessoriSet->m_bEliminato;
}

void CEsamiAccessoriSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiAccessoriSet* pOV = (CEsamiAccessoriSet*)pOldValues;
	CEsamiAccessoriSet* pNV = (CEsamiAccessoriSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Codice", pOV, &pOV->m_lCodice, pNV, &pNV->m_lCodice);
	sp.Execute("Quantita", pOV, &pOV->m_lQuantita, pNV, &pNV->m_lQuantita);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEsamiAccessoriSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEsamiAccessoriSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEsamiAccessoriSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEsamiAccessoriSet::SetBaseFilter(const CString &strFilter)
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