#include "stdafx.h"
#include "Endox.h"
#include "ComboRAOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboRAOSet, CBaseSet)

CComboRAOSet::CComboRAOSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CComboRAOSet::GetDefaultSQL()
{
	return "ERAO";
}

void CComboRAOSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lPercentualeRicetta = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CComboRAOSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "DescrizioneRAO", m_sDescrizione, 50);
		RFX_Long(pFX, "PercentualeRicetta", m_lPercentualeRicetta);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

long CComboRAOSet::AddRAO(CString sDescrizione)
{
	long lReturn = 0;

	if (OpenRecordset("CComboRAOSet::AddPrestazione"))
	{
		if (AddNewRecordset("CComboRAOSet::AddPrestazione"))
		{
			m_sDescrizione = sDescrizione;

			if (UpdateRecordset("CComboRAOSet::AddPrestazione"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CComboRAOSet::AddPrestazione");
	}

	return lReturn;
}

void CComboRAOSet::EdtRAO(long lID, CString sDescrizione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CComboRAOSet::EdtPrestazione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CComboRAOSet::EdtPrestazione"))
			{
				UpdateRecordset("CComboRAOSet::EdtPrestazione");
			}
		}

		CloseRecordset("CComboRAOSet::EdtPrestazione");
	}
}

BOOL CComboRAOSet::DelRAO(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CComboRAOSet::DelRAO"))
	{
		if (!IsEOF())
			bReturn = DeleteRecordset("CComboRAOSet::DelRAO");

		CloseRecordset("CComboRAOSet::DelRAO");
	}

	return bReturn;
}

CBaseSet* CComboRAOSet::CreateNew()
{
	return (CBaseSet*)new CComboRAOSet;
}

void CComboRAOSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CComboRAOSet* pSet = (CComboRAOSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPercentualeRicetta) || bCopyAll)
		m_lPercentualeRicetta = pSet->m_lPercentualeRicetta;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CComboRAOSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CComboRAOSet* pOV = (CComboRAOSet*)pOldValues;
	CComboRAOSet* pNV = (CComboRAOSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("DescrizioneRAO", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("PercentualeRicetta", pOV, &pOV->m_lPercentualeRicetta, pNV, &pNV->m_lPercentualeRicetta);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

CString CComboRAOSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	if (lID > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", lID);

		SetOpenFilter(strFilter);
		if (OpenRecordset("CComboRAOSet::GetDescrizione"))
		{
			if (!IsEOF())
				sReturn = m_sDescrizione;

			CloseRecordset("CComboRAOSet::GetDescrizione");
		}
	}

	return sReturn;
}

long CComboRAOSet::GetPercentualeRicetta(long lID)
{
	long lReturn = -1;

	if (lID > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", lID);

		SetOpenFilter(strFilter);
		if (OpenRecordset("CComboRAOSet::GetPercentualeRicetta"))
		{
			if (!IsEOF() && !IsFieldNull(&m_lPercentualeRicetta))
				lReturn = m_lPercentualeRicetta;

			CloseRecordset("CComboRAOSet::GetPercentualeRicetta");
		}
	}

	return lReturn;
}

BOOL CComboRAOSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CComboRAOSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CComboRAOSet::DeleteRecordset");
	}
	return bReturn;
}

CString CComboRAOSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CComboRAOSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
