#include "stdafx.h"
#include "Endox.h"
#include "IstologiaTipiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CIstologiaTipiSet, CBaseSet)

CIstologiaTipiSet::CIstologiaTipiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

void CIstologiaTipiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CIstologiaTipiSet::GetDefaultSQL()
{
	return "EIstologiaTipi";
}

void CIstologiaTipiSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CIstologiaTipiSet::CreateNew()
{
	return (CBaseSet*)new CIstologiaTipiSet;
}

void CIstologiaTipiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CIstologiaTipiSet* pSet = (CIstologiaTipiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CIstologiaTipiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CIstologiaTipiSet* pOV = (CIstologiaTipiSet*)pOldValues;
	CIstologiaTipiSet* pNV = (CIstologiaTipiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CIstologiaTipiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CIstologiaTipiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CIstologiaTipiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CIstologiaTipiSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CIstologiaTipiSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

void CIstologiaTipiSet::Add(CString sDescrizione)
{
	if (OpenRecordset("CIstologiaTipiSet::Add"))
	{
		if (AddNewRecordset("CIstologiaTipiSet::Add"))
		{
		    m_sDescrizione = sDescrizione;
			UpdateRecordset("CIstologiaTipiSet::Add");
		}

		CloseRecordset("CIstologiaTipiSet::Add");
	}
}

void CIstologiaTipiSet::Edt(long lID, CString sDescrizione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CIstologiaTipiSet::Edt"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CIstologiaTipiSet::Edt"))
			{
				m_sDescrizione = sDescrizione;
				UpdateRecordset("CIstologiaTipiSet::Edt");
			}
		}

		CloseRecordset("CIstologiaTipiSet::Edt");
	}
}

void CIstologiaTipiSet::Del(long lID)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CIstologiaTipiSet::Del"))
	{
		if (!IsEOF())
			DeleteRecordset("CIstologiaTipiSet::Del");

		CloseRecordset("CIstologiaTipiSet::Del");
	}
}

CString CIstologiaTipiSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	if (lID > 0)
	{
		CString sFilter;
		sFilter.Format("ID=%li", lID);

		SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
		SetOpenFilter(sFilter);
		if (OpenRecordset("CIstologiaTipiSet::GetDescrizione"))
		{
			if (!IsEOF())
				sReturn = m_sDescrizione;

			CloseRecordset("CIstologiaTipiSet::GetDescrizione");
		}
	}

	return sReturn;
}