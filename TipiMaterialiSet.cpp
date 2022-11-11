#include "stdafx.h"
#include "Endox.h"
#include "TipiMaterialiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiMaterialiSet, CBaseSet)


CTipiMaterialiSet::CTipiMaterialiSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CTipiMaterialiSet::GetDefaultSQL()
{
	return "TipiMateriali";
}

void CTipiMaterialiSet::SetEmpty()
{
	m_lID = 0;
	m_sCodice = "";
	m_sDescrizione = "";
	m_sTestoRtf001 = "";	
	m_bEliminato = FALSE;
}

void CTipiMaterialiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "TestoRtf001", m_sTestoRtf001, _TEXT_CONTROL_FIELD_LIMIT);		
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CTipiMaterialiSet::CreateNew()
{
	return (CBaseSet*)new CTipiMaterialiSet;
}

void CTipiMaterialiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiMaterialiSet* pSet = (CTipiMaterialiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf001) || bCopyAll)
		m_sTestoRtf001 = pSet->m_sTestoRtf001;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CTipiMaterialiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiMaterialiSet* pOV = (CTipiMaterialiSet*)pOldValues;
	CTipiMaterialiSet* pNV = (CTipiMaterialiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("TestoRtf001", pOV, &pOV->m_sTestoRtf001, pNV, &pNV->m_sTestoRtf001);	
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiMaterialiSet::DeleteRecordset(const CString &strCommento)
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

CString CTipiMaterialiSet::SetBaseFilter(const CString &strFilter)
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

BOOL CTipiMaterialiSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

// Public Methods
CString CTipiMaterialiSet::GetCodice(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiMaterialiSet::GetCodice"))
	{
		if (!IsEOF())
			sReturn = m_sCodice;

		CloseRecordset("CTipiMaterialiSet::GetCodice");
	}

	return sReturn;
}
BOOL CTipiMaterialiSet::SetCodice(long lID, CString sCodice)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiMaterialiSet::SetCodice"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiMaterialiSet::SetCodice"))
			{
				m_sCodice = sCodice;
				if (UpdateRecordset("CTipiMaterialiSet::SetCodice"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiMaterialiSet::SetCodice");
	}

	return bReturn;
}

CString CTipiMaterialiSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiMaterialiSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CTipiMaterialiSet::GetDescrizione");
	}

	return sReturn;
}
BOOL CTipiMaterialiSet::SetDescrizione(long lID, CString sDescrizione)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiMaterialiSet::SetDescrizione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiMaterialiSet::SetDescrizione"))
			{
				m_sDescrizione = sDescrizione;
				if (UpdateRecordset("CTipiMaterialiSet::SetDescrizione"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiMaterialiSet::SetDescrizione");
	}

	return bReturn;
}

CString CTipiMaterialiSet::GetTestoRtf(long lID, long lPos)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiMaterialiSet::GetTestoRtf"))
	{
		if (!IsEOF())
		{
			switch (lPos)
			{
			case 1:
				sReturn = m_sTestoRtf001;
				break;
			default:
				break;
			}

		}
		CloseRecordset("CTipiMaterialiSet::GetTestoRtf");
	}

	return sReturn;
}
BOOL CTipiMaterialiSet::SetTestoRtf(long lID, long lPos, CString sTesto)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiMaterialiSet::SetTestoRtf"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiMaterialiSet::SetTestoRtf"))
			{
				switch (lPos)
				{
				case 1:
					m_sTestoRtf001 = sTesto;
					break;
				default:
					break;
				}
				if (UpdateRecordset("CTipiMaterialiSet::SetTestoRtf"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CTipiMaterialiSet::SetTestoRtf");
	}

	return bReturn;
}

BOOL CTipiMaterialiSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiMaterialiSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiMaterialiSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CTipiMaterialiSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CTipiMaterialiSet::SetEliminato");
	}

	return bReturn;
}
void CTipiMaterialiSet::GetIDList(CList<long>& listID)
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