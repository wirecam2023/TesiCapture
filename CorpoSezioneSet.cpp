#include "stdafx.h"
#include "Endox.h"
#include "CorpoSezioneSet.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCorpoSezioneSet, CBaseSet)


CCorpoSezioneSet::CCorpoSezioneSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CCorpoSezioneSet::GetDefaultSQL()
{
	return "CorpoSezione";
}

void CCorpoSezioneSet::SetEmpty()
{
	m_lIDVariante = 0;
	m_lIDSezione = 0;
	m_lIDVariante = 0;
	m_sCorpoRtf = "";
	m_bEliminato = FALSE;
}


void CCorpoSezioneSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDSezione", m_lIDSezione);
		RFX_Long(pFX, "IDVariante", m_lIDVariante);
		RFX_Text(pFX, "CorpoRtf", m_sCorpoRtf, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CCorpoSezioneSet::CreateNew()
{
	return (CBaseSet*)new CCorpoSezioneSet;
}

void CCorpoSezioneSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCorpoSezioneSet* pSet = (CCorpoSezioneSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDSezione) || bCopyAll)
		m_lIDSezione = pSet->m_lIDSezione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDVariante) || bCopyAll)
		m_lIDVariante = pSet->m_lIDVariante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCorpoRtf) || bCopyAll)
		m_sCorpoRtf = pSet->m_sCorpoRtf;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCorpoSezioneSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCorpoSezioneSet* pOV = (CCorpoSezioneSet*)pOldValues;
	CCorpoSezioneSet* pNV = (CCorpoSezioneSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDSezione", pOV, &pOV->m_lIDSezione, pNV, &pNV->m_lIDSezione);
	sp.Execute("IDVariante", pOV, &pOV->m_lIDVariante, pNV, &pNV->m_lIDVariante);
	sp.Execute("CorpoRtf", pOV, &pOV->m_sCorpoRtf, pNV, &pNV->m_sCorpoRtf);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCorpoSezioneSet::DeleteRecordset(const CString &strCommento)
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

CString CCorpoSezioneSet::SetBaseFilter(const CString &strFilter)
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

BOOL CCorpoSezioneSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

CString CCorpoSezioneSet::GetCorpoRtf(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CCorpoSezioneSet::GetCorpoRtf"))
	{
		if (!IsEOF())
			sReturn = m_sCorpoRtf;

		CloseRecordset("CCorpoSezioneSet::GetCorpoRtf");
	}

	return sReturn;
}

CString CCorpoSezioneSet::GetCorpoRtf(long lIDSezione, long lIDVariante)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("IDSezione=%li AND IDVariante=%li", lIDSezione, lIDVariante);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CCorpoSezioneSet::GetCorpoRtf"))
	{
		if (!IsEOF())
			sReturn = m_sCorpoRtf;

		CloseRecordset("CCorpoSezioneSet::GetCorpoRtf");
	}

	return sReturn;
}
BOOL CCorpoSezioneSet::SetCorpoRtf(long lIDSezione, long lIDVariante, CString sCorpo)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("IDSezione=%li AND IDVariante=%li", lIDSezione, lIDVariante);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CCorpoSezioneSet::SetCorpoRtf"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CCorpoSezioneSet::SetCorpoRtf"))
			{
				m_sCorpoRtf = sCorpo;
				if (UpdateRecordset("CCorpoSezioneSet::SetCorpoRtf"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CCorpoSezioneSet::SetCodice");
	}

	return bReturn;
}

BOOL CCorpoSezioneSet::SetEliminato(long lIDSezione, long lIDVariante)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("IDSezione=%li AND IDVariante=%li", lIDSezione, lIDVariante);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CCorpoSezioneSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CCorpoSezioneSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CCorpoSezioneSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CCorpoSezioneSet::SetEliminato");
	}

	return bReturn;
}

void CCorpoSezioneSet::GetIDList(CList<long>& listID)
{
	SetSortRecord("ID");
	if (OpenRecordset("CTipiMaterialiSet::GetEliminato"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CTipiMaterialiSet::GetEliminato");
	}
}