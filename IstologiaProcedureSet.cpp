#include "stdafx.h"
#include "Endox.h"
#include "IstologiaProcedureSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CIstologiaProcedureSet, CBaseSet)

CIstologiaProcedureSet::CIstologiaProcedureSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

void CIstologiaProcedureSet::DoFieldExchange(CFieldExchange* pFX)
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

CString CIstologiaProcedureSet::GetDefaultSQL()
{
	return "EIstologiaProcedure";
}

void CIstologiaProcedureSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CIstologiaProcedureSet::CreateNew()
{
	return (CBaseSet*)new CIstologiaProcedureSet;
}

void CIstologiaProcedureSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CIstologiaProcedureSet* pSet = (CIstologiaProcedureSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CIstologiaProcedureSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CIstologiaProcedureSet* pOV = (CIstologiaProcedureSet*)pOldValues;
	CIstologiaProcedureSet* pNV = (CIstologiaProcedureSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CIstologiaProcedureSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CIstologiaProcedureSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CIstologiaProcedureSet::DeleteRecordset");
	}
	return bReturn;
}

CString CIstologiaProcedureSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CIstologiaProcedureSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

void CIstologiaProcedureSet::Add(CString sDescrizione)
{
	if (OpenRecordset("CIstologiaProcedureSet::Add"))
	{
		if (AddNewRecordset("CIstologiaProcedureSet::Add"))
		{
		    m_sDescrizione = sDescrizione;
			UpdateRecordset("CIstologiaProcedureSet::Add");
		}

		CloseRecordset("CIstologiaProcedureSet::Add");
	}
}

void CIstologiaProcedureSet::Edt(long lID, CString sDescrizione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CIstologiaProcedureSet::Edt"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CIstologiaProcedureSet::Edt"))
			{
				m_sDescrizione = sDescrizione;
				UpdateRecordset("CIstologiaProcedureSet::Edt");
			}
		}

		CloseRecordset("CIstologiaProcedureSet::Edt");
	}
}

void CIstologiaProcedureSet::Del(long lID)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CIstologiaProcedureSet::Del"))
	{
		if (!IsEOF())
			DeleteRecordset("CIstologiaProcedureSet::Del");

		CloseRecordset("CIstologiaProcedureSet::Del");
	}
}

CString CIstologiaProcedureSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	if (lID > 0)
	{
		CString sFilter;
		sFilter.Format("ID=%li", lID);

		SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
		SetOpenFilter(sFilter);
		if (OpenRecordset("CIstologiaProcedureSet::GetDescrizione"))
		{
			if (!IsEOF())
				sReturn = m_sDescrizione;

			CloseRecordset("CIstologiaProcedureSet::GetDescrizione");
		}
	}

	return sReturn;
}