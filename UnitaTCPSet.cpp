#include "stdafx.h"
#include "Endox.h"
#include "UnitaTCPSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CUnitaTCPSet, CBaseSet)

CUnitaTCPSet::CUnitaTCPSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

void CUnitaTCPSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Unita", m_lUnita);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "Endpoint", m_sEndpoint, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CUnitaTCPSet::GetDefaultSQL()
{
	return "UNITATCP";
}

void CUnitaTCPSet::SetEmpty()
{
	m_lID = 0;
	m_lUnita = 0;
	m_sDescrizione = "";
	m_sEndpoint = "";
	m_bEliminato = FALSE;
}

CBaseSet* CUnitaTCPSet::CreateNew()
{
	return (CBaseSet*)new CUnitaTCPSet;
}

void CUnitaTCPSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CUnitaTCPSet* pSet = (CUnitaTCPSet*)pOriginalSet;


	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUnita) || bCopyAll)
		m_lUnita = pSet->m_lUnita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEndpoint) || bCopyAll)
		m_sEndpoint = pSet->m_sEndpoint;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CUnitaTCPSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CUnitaTCPSet* pOV = (CUnitaTCPSet*)pOldValues;
	CUnitaTCPSet* pNV = (CUnitaTCPSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Unita", pOV, &pOV->m_lUnita, pNV, &pNV->m_lUnita);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Endpoint", pOV, &pOV->m_sEndpoint, pNV, &pNV->m_sEndpoint);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CUnitaTCPSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CUnitaTCPSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CUnitaTCPSet::DeleteRecordset");
	}
	return bReturn;
}

CString CUnitaTCPSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}


BOOL CUnitaTCPSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CUnitaTCPSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CUnitaTCPSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CUnitaTCPSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CUnitaTCPSet::SetEliminato");
	}

	return bReturn;
}

CString CUnitaTCPSet::GetEndpoint(long lUnita)
{
	CString sReturn;

	CString sFilter;
	sFilter.Format("UNITA=%li", lUnita);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CUnitaTCPSet::GetEndpoint"))
	{
		if (!IsEOF())
			sReturn = m_sEndpoint;

		CloseRecordset("CUnitaTCPSet::GetEndpoint");
	}

	return sReturn;
}

long CUnitaTCPSet::GetUnita(long lID)
{
	long lReturn;

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CUnitaTCPSet::GetUnita"))
	{
		if (!IsEOF())
			lReturn = m_lUnita;

		CloseRecordset("CUnitaTCPSet::GetUnita");
	}

	return lReturn;
}