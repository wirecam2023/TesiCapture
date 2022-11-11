#include "stdafx.h"
#include "Endox.h"
#include "TipiRefertoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiRefertoSet, CBaseSet)

CTipiRefertoSet::CTipiRefertoSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 14;
}

CString CTipiRefertoSet::GetDefaultSQL()
{
	return "TipiReferto";
}

void CTipiRefertoSet::SetEmpty()
{
	m_lID = 0;
	m_sCodice = "";
	m_sTitoloRtf = "";
	m_sTestoRtf001 = "";
	m_sTestoRtf002 = "";
	m_sTestoRtf003 = "";
	m_sTestoRtf004 = "";
	m_sTestoRtf005 = "";
	m_sTestoRtf006 = "";
	m_sTestoRtf007 = "";
	m_sTestoRtf008 = "";
	m_sTestoRtf009 = "";
	m_sTestoRtf010 = "";
	m_bEliminato = FALSE;
}

void CTipiRefertoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "TitoloRtf", m_sTitoloRtf, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf001", m_sTestoRtf001, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf002", m_sTestoRtf002, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf003", m_sTestoRtf003, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf004", m_sTestoRtf004, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf005", m_sTestoRtf005, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf006", m_sTestoRtf006, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf007", m_sTestoRtf007, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf008", m_sTestoRtf008, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf009", m_sTestoRtf009, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf010", m_sTestoRtf010, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CTipiRefertoSet::CreateNew()
{
	return (CBaseSet*)new CTipiRefertoSet;
}
void CTipiRefertoSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiRefertoSet* pSet = (CTipiRefertoSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitoloRtf) || bCopyAll)
		m_sTitoloRtf = pSet->m_sTitoloRtf;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf001) || bCopyAll)
		m_sTestoRtf001 = pSet->m_sTestoRtf001;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf002) || bCopyAll)
		m_sTestoRtf002 = pSet->m_sTestoRtf002;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf003) || bCopyAll)
		m_sTestoRtf003 = pSet->m_sTestoRtf003;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf004) || bCopyAll)
		m_sTestoRtf004 = pSet->m_sTestoRtf004;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf005) || bCopyAll)
		m_sTestoRtf005 = pSet->m_sTestoRtf005;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf006) || bCopyAll)
		m_sTestoRtf006 = pSet->m_sTestoRtf006;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf007) || bCopyAll)
		m_sTestoRtf007 = pSet->m_sTestoRtf007;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf008) || bCopyAll)
		m_sTestoRtf008 = pSet->m_sTestoRtf008;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf009) || bCopyAll)
		m_sTestoRtf009 = pSet->m_sTestoRtf009;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf010) || bCopyAll)
		m_sTestoRtf010 = pSet->m_sTestoRtf010;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CTipiRefertoSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiRefertoSet* pOV = (CTipiRefertoSet*)pOldValues;
	CTipiRefertoSet* pNV = (CTipiRefertoSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("TitoloRtf", pOV, &pOV->m_sTitoloRtf, pNV, &pNV->m_sTitoloRtf);
	sp.Execute("TestoRtf001", pOV, &pOV->m_sTestoRtf001, pNV, &pNV->m_sTestoRtf001);
	sp.Execute("TestoRtf002", pOV, &pOV->m_sTestoRtf002, pNV, &pNV->m_sTestoRtf002);
	sp.Execute("TestoRtf003", pOV, &pOV->m_sTestoRtf003, pNV, &pNV->m_sTestoRtf003);
	sp.Execute("TestoRtf004", pOV, &pOV->m_sTestoRtf004, pNV, &pNV->m_sTestoRtf004);
	sp.Execute("TestoRtf005", pOV, &pOV->m_sTestoRtf005, pNV, &pNV->m_sTestoRtf005);
	sp.Execute("TestoRtf006", pOV, &pOV->m_sTestoRtf006, pNV, &pNV->m_sTestoRtf006);
	sp.Execute("TestoRtf007", pOV, &pOV->m_sTestoRtf007, pNV, &pNV->m_sTestoRtf007);
	sp.Execute("TestoRtf008", pOV, &pOV->m_sTestoRtf008, pNV, &pNV->m_sTestoRtf008);
	sp.Execute("TestoRtf009", pOV, &pOV->m_sTestoRtf009, pNV, &pNV->m_sTestoRtf009);
	sp.Execute("TestoRtf010", pOV, &pOV->m_sTestoRtf010, pNV, &pNV->m_sTestoRtf010);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiRefertoSet::DeleteRecordset(const CString &strCommento)
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

CString CTipiRefertoSet::SetBaseFilter(const CString &strFilter)
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

BOOL CTipiRefertoSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}
// Public Methods
CString CTipiRefertoSet::GetCodice(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiRefertoSet::GetCodice"))
	{
		if (!IsEOF())
			sReturn = m_sCodice;

		CloseRecordset("CTipiRefertoSet::GetCodice");
	}

	return sReturn;
}
BOOL CTipiRefertoSet::SetCodice(long lID, CString sCodice)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiRefertoSet::SetCodice"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiRefertoSet::SetCodice"))
			{
				m_sCodice = sCodice;
				if (UpdateRecordset("CTipiRefertoSet::SetCodice"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiRefertoSet::SetCodice");
	}

	return bReturn;
}

CString CTipiRefertoSet::GetTitolo(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiRefertoSet::GetTitolo"))
	{
		if (!IsEOF())
			sReturn = m_sTitoloRtf;

		CloseRecordset("CTipiRefertoSet::GetTitolo");
	}

	return sReturn;
}
BOOL CTipiRefertoSet::SetTitolo(long lID, CString sTitolo)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiRefertoSet::SetTitolo"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiRefertoSet::SetTitolo"))
			{
				m_sTitoloRtf = sTitolo;
				if (UpdateRecordset("CTipiRefertoSet::SetTitolo"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiRefertoSet::SetTitolo");
	}

	return bReturn;
}

CString CTipiRefertoSet::GetTestoRtf(long lID, long lPos)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiRefertoSet::GetTestoRtf"))
	{
		if (!IsEOF())
		{
			switch (lPos)
			{
			case 1:
				sReturn = m_sTestoRtf001;
				break;
			case 2:
				sReturn = m_sTestoRtf002;
				break;
			case 3:
				sReturn = m_sTestoRtf003;
				break;
			case 4:
				sReturn = m_sTestoRtf004;
				break;
			case 5:
				sReturn = m_sTestoRtf005;
				break;
			case 6:
				sReturn = m_sTestoRtf006;
				break;
			case 7:
				sReturn = m_sTestoRtf007;
				break;
			case 8:
				sReturn = m_sTestoRtf008;
				break;
			case 9:
				sReturn = m_sTestoRtf009;
				break;
			case 10:
				sReturn = m_sTestoRtf010;
				break;
			default:
				break;
			}

		}
		CloseRecordset("CTipiRefertoSet::GetTestoRtf");
	}

	return sReturn;
}
BOOL CTipiRefertoSet::SetTestoRtf(long lID, long lPos, CString sTesto)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiRefertoSet::SetTestoRtf"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiRefertoSet::SetTestoRtf"))
			{
				switch (lPos)
				{
				case 1:
					m_sTestoRtf001 = sTesto;
					break;
				case 2:
					m_sTestoRtf002 = sTesto;
					break;
				case 3:
					m_sTestoRtf003 = sTesto;
					break;
				case 4:
					m_sTestoRtf004 = sTesto;
					break;
				case 5:
					m_sTestoRtf005 = sTesto;
					break;
				case 6:
					m_sTestoRtf006 = sTesto;
					break;
				case 7:
					m_sTestoRtf007 = sTesto;
					break;
				case 8:
					m_sTestoRtf008 = sTesto;
					break;
				case 9:
					m_sTestoRtf009 = sTesto;
					break;
				case 10:
					m_sTestoRtf010 = sTesto;
					break;
				default:
					break;
				}
				if (UpdateRecordset("CTipiRefertoSet::SetTestoRtf"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CTipiRefertoSet::SetTestoRtf");
	}

	return bReturn;
}
BOOL CTipiRefertoSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiRefertoSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiRefertoSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CTipiRefertoSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CTipiRefertoSet::SetEliminato");
	}

	return bReturn;
}
void CTipiRefertoSet::GetIDList(CList<long>& listID)
{
	SetSortRecord("ID");
	if (OpenRecordset("CTipiRefertoSet::GetEliminato"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CTipiRefertoSet::GetEliminato");
	}
}

void CTipiRefertoSet::GetIDTipoRefertoList(CList<long>& listID)
{
	SetSortRecord("ID");
	if (OpenRecordset("CTipiRefertoSet::GetIDTipoRefertoList"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CTipiRefertoSet::GetIDTipoRefertoList");
	}
}