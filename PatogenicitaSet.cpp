#include "stdafx.h"
#include "Endox.h"
#include "PatogenicitaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPatogenicitaSet, CBaseSet)

CPatogenicitaSet::CPatogenicitaSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CPatogenicitaSet::GetDefaultSQL()
{
	return "Patogenicita";
}

void CPatogenicitaSet::SetEmpty()
{
	m_lID = 0;
	m_sCodice = "";
	m_sDescrizione = "";
	m_bPositivita = FALSE;
	m_bEliminato = FALSE;
}

void CPatogenicitaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Bool(pFX, "Positivita", m_bPositivita);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CPatogenicitaSet::CreateNew()
{
	return (CBaseSet*)new CPatogenicitaSet;
}

void CPatogenicitaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CPatogenicitaSet* pSet = (CPatogenicitaSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPositivita) || bCopyAll)
		m_bPositivita = pSet->m_bPositivita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CPatogenicitaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CPatogenicitaSet* pOV = (CPatogenicitaSet*)pOldValues;
	CPatogenicitaSet* pNV = (CPatogenicitaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Positivita", pOV, &pOV->m_bPositivita, pNV, &pNV->m_bPositivita);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CPatogenicitaSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("::DeleteRecordset");
	}
	return bReturn;
}

CString CPatogenicitaSet::SetBaseFilter(const CString &strFilter)
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

BOOL CPatogenicitaSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

CString CPatogenicitaSet::GetCodice(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CPatogenicita::GetCodice"))
	{
		if (!IsEOF())
			sReturn = m_sCodice;

		CloseRecordset("CPatogenicita::GetCodice");
	}

	return sReturn;
}
BOOL CPatogenicitaSet::SetCodice(long lID, CString sCodice)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CPatogenicita::SetCodice"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CPatogenicita::SetCodice"))
			{
				m_sCodice = sCodice;
				if (UpdateRecordset("CPatogenicita::SetCodice"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CPatogenicita::SetCodice");
	}

	return bReturn;
}

CString CPatogenicitaSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CPatogenicita::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CPatogenicita::GetDescrizione");
	}

	return sReturn;
}
BOOL CPatogenicitaSet::SetDescrizione(long lID, CString sDescrizione)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CPatogenicita::SetDescrizione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CPatogenicita::SetDescrizione"))
			{
				m_sDescrizione = sDescrizione;
				if (UpdateRecordset("CPatogenicita::SetDescrizione"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CPatogenicita::SetDescrizione");
	}

	return bReturn;
}

BOOL CPatogenicitaSet::GetPositivita(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetBaseFilter("Eliminato=0 OR Eliminato=1");
	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CPatogenicita::GetPositivita"))
	{
		if (!IsEOF())
			bReturn = m_bPositivita;

		CloseRecordset("CPatogenicita::GetPositivita");
	}

	return bReturn;
}

BOOL CPatogenicitaSet::SetPositivita(long lID, BOOL bPositivita)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CPatogenicita::SetPositivita"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CPatogenicita::SetPositivita"))
			{
				m_bPositivita = bPositivita;
				if (UpdateRecordset("CPatogenicita::SetPositivita"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CPatogenicita::SetPositivita");
	}

	return bReturn;
}

BOOL CPatogenicitaSet::GetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetBaseFilter("Eliminato=0 OR Eliminato=1");
	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CPatogenicita::GetEliminato"))
	{
		if (!IsEOF())
			bReturn = m_bEliminato;

		CloseRecordset("CPatogenicita::GetEliminato");
	}

	return bReturn;
}
BOOL CPatogenicitaSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CPatogenicita::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CPatogenicita::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CPatogenicita::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CPatogenicita::SetEliminato");
	}

	return bReturn;
}

void CPatogenicitaSet::GetIDList(CList<long>& listID)
{
	SetSortRecord("ID");
	if (OpenRecordset("CPatogenicita::GetIDList"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CPatogenicita::GetIDList");
	}
}