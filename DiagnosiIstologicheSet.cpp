#include "stdafx.h"
#include "Endox.h"
#include "DiagnosiIstologicheSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDiagnosiIstologicheSet, CBaseSet)

CDiagnosiIstologicheSet::CDiagnosiIstologicheSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

void CDiagnosiIstologicheSet::DoFieldExchange(CFieldExchange* pFX)
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

CString CDiagnosiIstologicheSet::GetDefaultSQL()
{
	return "DiagnosiIstologiche";
}

void CDiagnosiIstologicheSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CDiagnosiIstologicheSet::CreateNew()
{
	return (CBaseSet*)new CDiagnosiIstologicheSet;
}

void CDiagnosiIstologicheSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CDiagnosiIstologicheSet* pSet = (CDiagnosiIstologicheSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CDiagnosiIstologicheSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CDiagnosiIstologicheSet* pOV = (CDiagnosiIstologicheSet*)pOldValues;
	CDiagnosiIstologicheSet* pNV = (CDiagnosiIstologicheSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CDiagnosiIstologicheSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CDiagnosiIstologicheSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CDiagnosiIstologicheSet::DeleteRecordset");
	}
	return bReturn;
}

CString CDiagnosiIstologicheSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CDiagnosiIstologicheSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

void CDiagnosiIstologicheSet::Add(CString sDescrizione)
{
	if (OpenRecordset("CDiagnosiIstologicheSet::Add"))
	{
		if (AddNewRecordset("CDiagnosiIstologicheSet::Add"))
		{
		    m_sDescrizione = sDescrizione;
			UpdateRecordset("CDiagnosiIstologicheSet::Add");
		}

		CloseRecordset("CDiagnosiIstologicheSet::Add");
	}
}

void CDiagnosiIstologicheSet::Edt(long lID, CString sDescrizione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CDiagnosiIstologicheSet::Edt"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CDiagnosiIstologicheSet::Edt"))
			{
				m_sDescrizione = sDescrizione;
				UpdateRecordset("CDiagnosiIstologicheSet::Edt");
			}
		}

		CloseRecordset("CDiagnosiIstologicheSet::Edt");
	}
}

void CDiagnosiIstologicheSet::Del(long lID)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CDiagnosiIstologicheSet::Del"))
	{
		if (!IsEOF())
			DeleteRecordset("CDiagnosiIstologicheSet::Del");

		CloseRecordset("CDiagnosiIstologicheSet::Del");
	}
}

CString CDiagnosiIstologicheSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	if (lID > 0)
	{
		CString sFilter;
		sFilter.Format("ID=%li", lID);

		SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
		SetOpenFilter(sFilter);
		if (OpenRecordset("CDiagnosiIstologicheSet::GetDescrizione"))
		{
			if (!IsEOF())
				sReturn = m_sDescrizione;

			CloseRecordset("CDiagnosiIstologicheSet::GetDescrizione");
		}
	}

	return sReturn;
}