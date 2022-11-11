#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaEsamiPrestSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaEsamiPrestSet, CBaseSet)

CAnatomiaPatologicaEsamiPrestSet::CAnatomiaPatologicaEsamiPrestSet()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 4;
	SetBaseFilter("");
}

CString CAnatomiaPatologicaEsamiPrestSet::GetDefaultSQL()
{
	return "AnatomiaPatologicaEsamiPrest";
}

void CAnatomiaPatologicaEsamiPrestSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDPrestazione = 0;
	m_bEliminato = FALSE;
}

void CAnatomiaPatologicaEsamiPrestSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDPrestazione", m_lIDPrestazione);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

long CAnatomiaPatologicaEsamiPrestSet::AddPrestazione(long lIDEsame, long lIDPrestazione)
{
	long lReturn = 0;

	if (OpenRecordset("CAnatomiaPatologicaEsamiPrestSet::AddPrestazione"))
	{
		if (AddNewRecordset("CAnatomiaPatologicaEsamiPrestSet::AddPrestazione"))
		{
			m_lIDEsame = lIDEsame;
			m_lIDPrestazione = lIDPrestazione;

			if (UpdateRecordset("CAnatomiaPatologicaEsamiPrestSet::AddPrestazione"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CAnatomiaPatologicaEsamiPrestSet::AddPrestazione");
	}

	return lReturn;
}

void CAnatomiaPatologicaEsamiPrestSet::EdtPrestazione(long lID, long lIDPrestazione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CAnatomiaPatologicaEsamiPrestSet::EdtPrestazione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CAnatomiaPatologicaEsamiPrestSet::EdtPrestazione"))
			{
				m_lIDPrestazione = lIDPrestazione;
				UpdateRecordset("CAnatomiaPatologicaEsamiPrestSet::EdtPrestazione");
			}
		}

		CloseRecordset("CAnatomiaPatologicaEsamiPrestSet::EdtPrestazione");
	}
}

void CAnatomiaPatologicaEsamiPrestSet::DelPrestazione(long lID)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CAnatomiaPatologicaEsamiPrestSet::DelPrestazione"))
	{
		if (!IsEOF())
			DeleteRecordset("CAnatomiaPatologicaEsamiPrestSet::DelPrestazione");

		CloseRecordset("CAnatomiaPatologicaEsamiPrestSet::DelPrestazione");
	}
}

CBaseSet* CAnatomiaPatologicaEsamiPrestSet::CreateNew()
{
	return (CBaseSet*)new CAnatomiaPatologicaEsamiPrestSet;
}

void CAnatomiaPatologicaEsamiPrestSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CAnatomiaPatologicaEsamiPrestSet* pAnatomiaPatologicaEsamiPrestSet = (CAnatomiaPatologicaEsamiPrestSet*)pOriginalSet;

	if (!pAnatomiaPatologicaEsamiPrestSet->IsOpen() || pAnatomiaPatologicaEsamiPrestSet->IsFieldDirty(&pAnatomiaPatologicaEsamiPrestSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pAnatomiaPatologicaEsamiPrestSet->m_lIDEsame;
	if (!pAnatomiaPatologicaEsamiPrestSet->IsOpen() || pAnatomiaPatologicaEsamiPrestSet->IsFieldDirty(&pAnatomiaPatologicaEsamiPrestSet->m_lIDPrestazione) || bCopyAll)
		m_lIDPrestazione = pAnatomiaPatologicaEsamiPrestSet->m_lIDPrestazione;
	if (!pAnatomiaPatologicaEsamiPrestSet->IsOpen() || pAnatomiaPatologicaEsamiPrestSet->IsFieldDirty(&pAnatomiaPatologicaEsamiPrestSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pAnatomiaPatologicaEsamiPrestSet->m_bEliminato;
}

void CAnatomiaPatologicaEsamiPrestSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CAnatomiaPatologicaEsamiPrestSet* pOV = (CAnatomiaPatologicaEsamiPrestSet*)pOldValues;
	CAnatomiaPatologicaEsamiPrestSet* pNV = (CAnatomiaPatologicaEsamiPrestSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDPrestazione", pOV, &pOV->m_lIDPrestazione, pNV, &pNV->m_lIDPrestazione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CAnatomiaPatologicaEsamiPrestSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CAnatomiaPatologicaEsamiPrestSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CAnatomiaPatologicaEsamiPrestSet::DeleteRecordset");
	}
	return bReturn;
}

CString CAnatomiaPatologicaEsamiPrestSet::SetBaseFilter(const CString &strFilter)
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