#include "stdafx.h"
#include "Endox.h"
#include "TipiAlterazioniSet.h"
#include "Common.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiAlterazioniSet, CBaseSet)


CTipiAlterazioniSet::CTipiAlterazioniSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CTipiAlterazioniSet::GetDefaultSQL()
{
	return "TipiAlterazioni";
}

void CTipiAlterazioniSet::SetEmpty()
{
	m_lID = 0;
	m_sCodice = "";
	m_sDescrizione = "";
	m_bObbligatorioHGVSc = FALSE;
	m_bObbligatorioHGVSp = FALSE;
	m_bEliminato = FALSE;
}

void CTipiAlterazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Bool(pFX, "ObbligatorioHGVSc", m_bObbligatorioHGVSc);
		RFX_Bool(pFX, "ObbligatorioHGVSp", m_bObbligatorioHGVSp);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CTipiAlterazioniSet::CreateNew()
{
	return (CBaseSet*)new CTipiAlterazioniSet;
}

void CTipiAlterazioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiAlterazioniSet* pSet = (CTipiAlterazioniSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bObbligatorioHGVSc) || bCopyAll)
		m_bObbligatorioHGVSc = pSet->m_bObbligatorioHGVSc;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bObbligatorioHGVSp) || bCopyAll)
		m_bObbligatorioHGVSp = pSet->m_bObbligatorioHGVSp;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CTipiAlterazioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiAlterazioniSet* pOV = (CTipiAlterazioniSet*)pOldValues;
	CTipiAlterazioniSet* pNV = (CTipiAlterazioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("ObbligatorioHGVSc", pOV, &pOV->m_bObbligatorioHGVSc, pNV, &pNV->m_bObbligatorioHGVSc);
	sp.Execute("ObbligatorioHGVSp", pOV, &pOV->m_bObbligatorioHGVSp, pNV, &pNV->m_bObbligatorioHGVSp);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiAlterazioniSet::DeleteRecordset(const CString &strCommento)
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

CString CTipiAlterazioniSet::SetBaseFilter(const CString &strFilter)
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

BOOL CTipiAlterazioniSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}


// Public Methods
CString CTipiAlterazioniSet::GetCodice(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiAlterazioniSet::GetCodice"))
	{
		if (!IsEOF())
			sReturn = m_sCodice;

		CloseRecordset("CTipiAlterazioniSet::GetCodice");
	}

	return sReturn;
}
BOOL CTipiAlterazioniSet::SetCodice(long lID, CString sCodice)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiAlterazioniSet::SetCodice"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiAlterazioniSet::SetCodice"))
			{
				m_sCodice = sCodice;
				if (UpdateRecordset("CTipiAlterazioniSet::SetCodice"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiAlterazioniSet::SetCodice");
	}

	return bReturn;
}

CString CTipiAlterazioniSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiAlterazioniSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CTipiAlterazioniSet::GetDescrizione");
	}

	return sReturn;
}
BOOL CTipiAlterazioniSet::SetDescrizione(long lID, CString sDescrizione)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiAlterazioniSet::SetDescrizione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiAlterazioniSet::SetDescrizione"))
			{
				m_sDescrizione = sDescrizione;
				if (UpdateRecordset("CTipiAlterazioniSet::SetDescrizione"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiAlterazioniSet::SetDescrizione");
	}

	return bReturn;
}

void CTipiAlterazioniSet::GetObbligatori(long lID, BOOL& bHGVSc, BOOL& bHGVSp)
{
	bHGVSc = FALSE;
	bHGVSp = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiAlterazioniSet::GetObbligatori"))
	{
		if (!IsEOF())
		{
			bHGVSc = m_bObbligatorioHGVSc;
			bHGVSp = m_bObbligatorioHGVSp;
		}

		CloseRecordset("CTipiAlterazioniSet::GetObbligatori");
	}
}
BOOL CTipiAlterazioniSet::SetObbligatori(long lID, BOOL bHGVSc, BOOL bHGVSp)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiAlterazioniSet::SetObbligatori"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiAlterazioniSet::SetObbligatori"))
			{
				m_bObbligatorioHGVSc = bHGVSc;
				m_bObbligatorioHGVSp = bHGVSp;

				if (UpdateRecordset("CTipiAlterazioniSet::SetObbligatori"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiAlterazioniSet::SetObbligatori");
	}

	return bReturn;
}

BOOL CTipiAlterazioniSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiAlterazioniSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiAlterazioniSet::SetEliminato"))
			{
				m_bEliminato = TRUE;

				if (UpdateRecordset("CTipiAlterazioniSet::SetEliminato"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiAlterazioniSet::SetEliminato");
	}

	return bReturn;
}

void CTipiAlterazioniSet::GetIDList(CList<long>& listID)
{		
	SetSortRecord("ID");
	if (OpenRecordset("CTipiAlterazioniSet::GetEliminato"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}			
		
		CloseRecordset("CTipiAlterazioniSet::GetEliminato");
	}
}