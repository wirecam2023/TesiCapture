#include "stdafx.h"
#include "Endox.h"
#include "SezioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSezioniSet, CBaseSet)


CSezioniSet::CSezioniSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 9;
}

CString CSezioniSet::GetDefaultSQL()
{
	return "Sezioni";
}

void CSezioniSet::SetEmpty()
{
	m_lID = 0;
	m_lIDTipoReferto = 0;
	m_sCodice = "";
	m_lIDTipoVariante = 0;
	m_sTitoloRtf = "";
	m_sTestoRtf001 = "";
	m_lOrdine = 0;
	m_bRisultato = FALSE;
	m_bEliminato = FALSE;
}

void CSezioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDTipoReferto", m_lIDTipoReferto);
		RFX_Text(pFX, "Codice", m_sCodice, 255);
		RFX_Long(pFX, "IDTipoVariante", m_lIDTipoVariante);
		RFX_Text(pFX, "TitoloRtf", m_sTitoloRtf, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoRtf001", m_sTestoRtf001, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Long(pFX, "Ordine", m_lOrdine);
		RFX_Bool(pFX, "Risultato", m_bRisultato);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CSezioniSet::CreateNew()
{
	return (CBaseSet*)new CSezioniSet;
}

void CSezioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CSezioniSet* pSet = (CSezioniSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoReferto) || bCopyAll)
		m_lIDTipoReferto = pSet->m_lIDTipoReferto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoVariante) || bCopyAll)
		m_lIDTipoVariante = pSet->m_lIDTipoVariante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitoloRtf) || bCopyAll)
		m_sTitoloRtf = pSet->m_sTitoloRtf;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf001) || bCopyAll)
		m_sTestoRtf001 = pSet->m_sTestoRtf001;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bRisultato) || bCopyAll)
		m_bRisultato = pSet->m_bRisultato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CSezioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CSezioniSet* pOV = (CSezioniSet*)pOldValues;
	CSezioniSet* pNV = (CSezioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDTipoReferto", pOV, &pOV->m_lIDTipoReferto, pNV, &pNV->m_lIDTipoReferto);
	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("IDTipoVariante", pOV, &pOV->m_lIDTipoVariante, pNV, &pNV->m_lIDTipoVariante);
	sp.Execute("TitoloRtf", pOV, &pOV->m_sTitoloRtf, pNV, &pNV->m_sTitoloRtf);
	sp.Execute("TestoRtf001", pOV, &pOV->m_sTestoRtf001, pNV, &pNV->m_sTestoRtf001);
	sp.Execute("Ordine", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("Risultato", pOV, &pOV->m_bRisultato, pNV, &pNV->m_bRisultato);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CSezioniSet::DeleteRecordset(const CString &strCommento)
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

CString CSezioniSet::SetBaseFilter(const CString &strFilter)
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

BOOL CSezioniSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

// Public Methods
CString CSezioniSet::GetCodice(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::GetCodice"))
	{
		if (!IsEOF())
			sReturn = m_sCodice;

		CloseRecordset("CSezioniSet::GetCodice");
	}

	return sReturn;
}
BOOL CSezioniSet::SetCodice(long lID, CString sCodice)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::SetCodice"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSezioniSet::SetCodice"))
			{
				m_sCodice = sCodice;
				if (UpdateRecordset("CSezioniSet::SetCodice"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CSezioniSet::SetCodice");
	}

	return bReturn;
}

CString CSezioniSet::GetTitolo(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::GetTitolo"))
	{
		if (!IsEOF())
			sReturn = m_sTitoloRtf;

		CloseRecordset("CSezioniSet::GetTitolo");
	}

	return sReturn;
}
BOOL CSezioniSet::SetTitolo(long lID, CString sTitolo)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::SetTitolo"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSezioniSet::SetTitolo"))
			{
				m_sTitoloRtf = sTitolo;
				if (UpdateRecordset("CSezioniSet::SetTitolo"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CSezioniSet::SetTitolo");
	}

	return bReturn;
}

CString CSezioniSet::GetTestoRtf(long lID, long lPos)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::GetTestoRtf"))
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
		CloseRecordset("CSezioniSet::GetTestoRtf");
	}

	return sReturn;
}

BOOL CSezioniSet::SetTestoRtf(long lID, long lPos, CString sTesto)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::SetTestoRtf"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSezioniSet::SetTestoRtf"))
			{
				switch (lPos)
				{
				case 1:
					m_sTestoRtf001 = sTesto;
					break;
				default:
					break;
				}
				if (UpdateRecordset("CSezioniSet::SetTestoRtf"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CSezioniSet::SetTestoRtf");
	}

	return bReturn;
}

BOOL CSezioniSet::GetRisultato(long lID, long lIDTipoReferto)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li AND IDTIPOREFERTO=%li", lID, lIDTipoReferto);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::GetRisultato"))
	{
		if (!IsEOF())
			bReturn = m_bRisultato;

		CloseRecordset("CSezioniSet::GetRisultato");
	}

	return bReturn;
}

BOOL CSezioniSet::SetRisultato(long lID, BOOL bRisultato)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::SetRisultato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSezioniSet::SetRisultato"))
			{
				m_bRisultato = bRisultato;

				if (UpdateRecordset("CSezioniSet::SetRisultato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CSezioniSet::SetRisultato");
	}

	return bReturn;
}

BOOL CSezioniSet::VerifyRisultadoField(long lID, long lIDTipoReferto)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Risultato=1 and IDTIPOREFERTO=%li", lIDTipoReferto);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::SetRisultato"))
	{
		if (!IsEOF() && m_lID != lID)		
			bReturn = TRUE;

		CloseRecordset("CSezioniSet::SetRisultato");
	}

	return bReturn;
}

CString CSezioniSet::GetRisultatoRtf()
{
	CString sReturn = "";
	long lIDSezione = 0;

	CString strFilter;
	strFilter.Format("Risultato=1");

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::GetRisultatoRtf"))
	{
		if (!IsEOF())
			lIDSezione = m_lID;

		CloseRecordset("CSezioniSet::GetRisultatoRtf");
	}

	if (lIDSezione > 0)
	{
		sReturn = GetTestoRtf(lIDSezione, 1);
	}

	return sReturn;
}

BOOL CSezioniSet::SetTipoReferto(long lID, long p_lIDTipoReferto)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::SetTipoReferto"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSezioniSet::SetTipoReferto"))
			{
				m_lIDTipoReferto = p_lIDTipoReferto;

				if (UpdateRecordset("CSezioniSet::SetTipoReferto"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CSezioniSet::SetTipoVariante");
	}

	return bReturn;
}

long CSezioniSet::GetTipoVariante(long lID)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::GetTipoVariante"))
	{
		if (!IsEOF())
			lReturn = m_lIDTipoVariante;
	}
	CloseRecordset("CSezioniSet::GetTipoVariante");

	return lReturn;
}

BOOL CSezioniSet::SetTipoVariante(long lID, long lIDTipoVariante)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::SetTipoVariante"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSezioniSet::SetTipoVariante"))
			{
				m_lIDTipoVariante = lIDTipoVariante;

				if (UpdateRecordset("CSezioniSet::SetTipoVariante"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CSezioniSet::SetTipoVariante");
	}

	return bReturn;
}

long CSezioniSet::GetOrdine(long lID)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::GetOrdine"))
	{
		if (!IsEOF())
			lReturn = m_lOrdine;
	}
	CloseRecordset("CSezioniSet::GetOrdine");

	return lReturn;
}

BOOL CSezioniSet::SetOrdine(long lID, long lOrdine)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::SetOrdine"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSezioniSet::SetOrdine"))
			{
				m_lOrdine = lOrdine;

				if (UpdateRecordset("CSezioniSet::SetOrdine"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CSezioniSet::SetOrdine");
	}

	return bReturn;
}


long CSezioniSet::GetNextMaxOrdine()
{
	long lReturn = 0;

	SetSortRecord("Ordine desc");
	if (OpenRecordset("CSezioniSet::GetEliminato"))
	{
		if (!IsEOF())
			lReturn = m_lOrdine + 1;
		else
			lReturn = 1;

		CloseRecordset("CSezioniSet::GetEliminato");
	}

	return lReturn;
}

long CSezioniSet::GetNextMaxOrdine(long p_lIDTipoReferto)
{
	if (p_lIDTipoReferto <= 0)
		return 0;

	long lReturn = 0;

	CString strFilter;
	strFilter.Format("IDTipoReferto=%li", p_lIDTipoReferto);
	SetOpenFilter(strFilter);

	SetSortRecord("Ordine desc");
	if (OpenRecordset("CSezioniSet::GetNextMaxOrdine"))
	{
		if (!IsEOF())
			lReturn = m_lOrdine + 1;
		else
			lReturn = 1;

		CloseRecordset("CSezioniSet::GetNextMaxOrdine");
	}

	return lReturn;
}

void CSezioniSet::GetIDListWithOrdineLowerThanPos(CList<long>& listID, long lPos)
{
	SetSortRecord("Ordine");
	if (OpenRecordset("CSezioniSet::GetEliminato"))
	{
		while (!IsEOF())
		{
			if (m_lOrdine < lPos)
				listID.AddTail(m_lID);

			MoveNext();
		}

		CloseRecordset("CSezioniSet::GetEliminato");
	}
}

void CSezioniSet::GetIDListWithOrdineGreaterThanPos(CList<long>& listID, long lPos)
{
	SetSortRecord("Ordine");
	if (OpenRecordset("CSezioniSet::GetEliminato"))
	{
		while (!IsEOF())
		{
			if (m_lOrdine > lPos)
				listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CSezioniSet::GetEliminato");
	}
}

long CSezioniSet::GetIDByOrdine(long lOrdine)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("Ordine=%li", lOrdine);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::GetIDByOrdine"))
	{
		if (!IsEOF())
			lReturn = m_lID;

		CloseRecordset("CSezioniSet::GetIDByOrdine");
	}

	return lReturn;
}

BOOL CSezioniSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CSezioniSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CSezioniSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CSezioniSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CSezioniSet::SetEliminato");
	}

	return bReturn;
}

void CSezioniSet::GetIDList(CList<long>& listID)
{
	SetSortRecord("Ordine");
	if (OpenRecordset("CSezioniSet::GetEliminato"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CSezioniSet::GetEliminato");
	}
}

void CSezioniSet::GetIDListByTipoReferto(CList<long>& listID, long lIDTipoReferto)
{
	CString strFilter;
	strFilter.Format("IDTipoReferto=%li", lIDTipoReferto);
	SetOpenFilter(strFilter);

	SetSortRecord("Ordine");
	if (OpenRecordset("CSezioniSet::GetIDListByTipoReferto"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CSezioniSet::GetIDListByTipoReferto");
	}
}

long CSezioniSet::GetRisultatoID(long lIDTipoReferto)
{
	long lResult = 0;
	
	CString strFilter;
	strFilter.Format("IDTipoReferto=%li and Risultato=1", lIDTipoReferto);
	SetOpenFilter(strFilter);

	SetSortRecord("Ordine");
	if (OpenRecordset("CSezioniSet::GetRisultatoID"))
	{
		if (!IsEOF())
		{
			lResult = m_lID;
		}

		CloseRecordset("CSezioniSet::GetRisultatoID");
	}

	return lResult;
}