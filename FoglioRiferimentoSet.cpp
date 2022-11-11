//Gabriel BUG 6225 - Lista DO
#include "stdafx.h"
#include "Endox.h"
#include "FoglioRiferimentoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFoglioRiferimentoSet, CBaseSet)

CFoglioRiferimentoSet::CFoglioRiferimentoSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CFoglioRiferimentoSet::GetDefaultSQL()
{
	return "FOGLIO_RIFERIMENTO";
}

void CFoglioRiferimentoSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lUO = 0;
	m_sCodicePrestazione = "";
	m_sPercorso = "";
	m_bEliminato = FALSE;
}

void CFoglioRiferimentoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Text(pFX, "CodicePrestazione", m_sCodicePrestazione, 255);
		RFX_Text(pFX, "Percorso", m_sPercorso, 1024);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CFoglioRiferimentoSet::CreateNew()
{
	return (CBaseSet*)new CFoglioRiferimentoSet;
}

void CFoglioRiferimentoSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFoglioRiferimentoSet* pSet = (CFoglioRiferimentoSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodicePrestazione) || bCopyAll)
		m_sCodicePrestazione = pSet->m_sCodicePrestazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPercorso) || bCopyAll)
		m_sPercorso = pSet->m_sPercorso;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CFoglioRiferimentoSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFoglioRiferimentoSet* pOV = (CFoglioRiferimentoSet*)pOldValues;
	CFoglioRiferimentoSet* pNV = (CFoglioRiferimentoSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("CodicePrestazione", pOV, &pOV->m_sCodicePrestazione, pNV, &pNV->m_sCodicePrestazione);
	sp.Execute("Percorso", pOV, &pOV->m_sPercorso, pNV, &pNV->m_sPercorso);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFoglioRiferimentoSet::DeleteRecordset(const CString &strCommento)
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

CString CFoglioRiferimentoSet::SetBaseFilter(const CString &strFilter)
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

BOOL CFoglioRiferimentoSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

CString CFoglioRiferimentoSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CFoglioRiferimentoSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CFoglioRiferimentoSet::GetDescrizione");
	}

	return sReturn;
}

BOOL CFoglioRiferimentoSet::SetDescrizione(long lID, CString sDescrizione)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CFoglioRiferimentoSet::SetDescrizione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFoglioRiferimentoSet::SetDescrizione"))
			{
				m_sDescrizione = sDescrizione;
				if (UpdateRecordset("CFoglioRiferimentoSet::SetDescrizione"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CFoglioRiferimentoSet::SetDescrizione");
	}

	return bReturn;
}

CString CFoglioRiferimentoSet::GetCodicePrestazione(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CFoglioRiferimentoSet::GetCodicePrestazione"))
	{
		if (!IsEOF())
			sReturn = m_sCodicePrestazione;

		CloseRecordset("CFoglioRiferimentoSet::GetCodicePrestazione");
	}

	return sReturn;
}

BOOL CFoglioRiferimentoSet::SetCodicePrestazione(long lID, CString sCodice)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CFoglioRiferimentoSet::SetCodicePrestazione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFoglioRiferimentoSet::SetCodicePrestazione"))
			{
				m_sCodicePrestazione = sCodice;
				if (UpdateRecordset("CFoglioRiferimentoSet::SetCodicePrestazione"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CFoglioRiferimentoSet::SetCodicePrestazione");
	}

	return bReturn;
}

CString CFoglioRiferimentoSet::GetPercorso(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CFoglioRiferimentoSet::GetPercorso"))
	{
		if (!IsEOF())
			sReturn = m_sPercorso;

		CloseRecordset("CFoglioRiferimentoSet::GetPercorso");
	}

	return sReturn;
}

BOOL CFoglioRiferimentoSet::SetPercorso(long lID, CString sCodice)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CFoglioRiferimentoSet::SetPercorso"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFoglioRiferimentoSet::SetPercorso"))
			{
				m_sPercorso = sCodice;
				if (UpdateRecordset("CFoglioRiferimentoSet::SetPercorso"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CFoglioRiferimentoSet::SetPercorso");
	}

	return bReturn;
}

void CFoglioRiferimentoSet::GetListaPercorso(CString sCodicePrestazione, long lUO, CList<CString>* pLista)
{
	CString strFilter;
	strFilter.Format("CodicePrestazione='%s' AND UO=%li", sCodicePrestazione, lUO);

	SetOpenFilter(strFilter);

	if (OpenRecordset("CFoglioRiferimentoSet::GetListaPercorso"))
	{
		while (!IsEOF())
		{
			pLista->AddTail(m_sPercorso);
			MoveNext();
		}

		CloseRecordset("CFoglioRiferimentoSet::GetListaPercorso");
	}
}

BOOL CFoglioRiferimentoSet::GetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetBaseFilter("Eliminato=0 OR Eliminato=1");
	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CFoglioRiferimentoSet::GetEliminato"))
	{
		if (!IsEOF())
			bReturn = m_bEliminato;

		CloseRecordset("CFoglioRiferimentoSet::GetEliminato");
	}

	return bReturn;
}

BOOL CFoglioRiferimentoSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CFoglioRiferimentoSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFoglioRiferimentoSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CFoglioRiferimentoSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CFoglioRiferimentoSet::SetEliminato");
	}

	return bReturn;
}

void CFoglioRiferimentoSet::GetIDList(CList<long>& listID)
{
	SetSortRecord("ID");
	if (OpenRecordset("CFoglioRiferimentoSet::GetIDList"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CFoglioRiferimentoSet::GetIDList");
	}
}