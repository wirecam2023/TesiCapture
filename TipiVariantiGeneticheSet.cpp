#include "stdafx.h"
#include "Endox.h"
#include "TipiVariantiGeneticheSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiVariantiGeneticheSet, CBaseSet)


CTipiVariantiGeneticheSet::CTipiVariantiGeneticheSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 10; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
}

CString CTipiVariantiGeneticheSet::GetDefaultSQL()
{
	return "TipiVariantiGenetiche";
}

void CTipiVariantiGeneticheSet::SetEmpty()
{
	m_lID = 0;
	m_sCodice = "";
	m_sDescrizione = "";
	m_bObbligatorioCodiceVariante = FALSE;
	m_bObbligatorioTipoAlterazione = FALSE;
	m_bObbligatorioTrascrizione = FALSE; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	m_sTestoRtf001 = "";
	m_bEliminato = FALSE;
	m_lOrdine = 0; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	m_bFraseRemovibile = FALSE; //Julio BUG 3791 - Melhoria frases resultado laudo genomica	
}

void CTipiVariantiGeneticheSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Bool(pFX, "ObbligatorioCodiceVariante", m_bObbligatorioCodiceVariante);
		RFX_Bool(pFX, "ObbligatorioTipoAlterazione", m_bObbligatorioTipoAlterazione);
		RFX_Bool(pFX, "ObbligatorioTrascrizione", m_bObbligatorioTrascrizione);//Julio BUG 3791 - Melhoria frases resultado laudo genomica		
		RFX_Text(pFX, "TestoRtf001", m_sTestoRtf001, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
		RFX_Bool(pFX, "FraseRemovibile", m_bFraseRemovibile);//Julio BUG 3791 - Melhoria frases resultado laudo genomica				
		RFX_Long(pFX, "Ordine", m_lOrdine); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	}
}

CBaseSet* CTipiVariantiGeneticheSet::CreateNew()
{
	return (CBaseSet*)new CTipiVariantiGeneticheSet;
}

void CTipiVariantiGeneticheSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiVariantiGeneticheSet* pSet = (CTipiVariantiGeneticheSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bObbligatorioCodiceVariante) || bCopyAll)
		m_bObbligatorioCodiceVariante = pSet->m_bObbligatorioCodiceVariante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bObbligatorioTipoAlterazione) || bCopyAll)
		m_bObbligatorioTipoAlterazione = pSet->m_bObbligatorioTipoAlterazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRtf001) || bCopyAll)
		m_sTestoRtf001 = pSet->m_sTestoRtf001;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;

	//Julio BUG 3791 - Melhoria frases resultado laudo genomica
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	//Julio BUG 3791 - Melhoria frases resultado laudo genomica
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bFraseRemovibile) || bCopyAll)
		m_bFraseRemovibile = pSet->m_bFraseRemovibile;
	//Julio BUG 3791 - Melhoria frases resultado laudo genomica
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bObbligatorioTrascrizione) || bCopyAll)
		m_bObbligatorioTrascrizione = pSet->m_bObbligatorioTrascrizione;
}

void CTipiVariantiGeneticheSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiVariantiGeneticheSet* pOV = (CTipiVariantiGeneticheSet*)pOldValues;
	CTipiVariantiGeneticheSet* pNV = (CTipiVariantiGeneticheSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("ObbligatorioCodiceVariante", pOV, &pOV->m_bObbligatorioCodiceVariante, pNV, &pNV->m_bObbligatorioCodiceVariante);
	sp.Execute("ObbligatorioTipoAlterazione", pOV, &pOV->m_bObbligatorioTipoAlterazione, pNV, &pNV->m_bObbligatorioTipoAlterazione);
	sp.Execute("TestoRtf001", pOV, &pOV->m_sTestoRtf001, pNV, &pNV->m_sTestoRtf001);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);

	//Julio BUG 3791 - Melhoria frases resultado laudo genomica
	sp.Execute("Ordine", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("FraseRemovibile", pOV, &pOV->m_bFraseRemovibile, pNV, &pNV->m_bFraseRemovibile);
	sp.Execute("ObbligatorioTrascrizione", pOV, &pOV->m_bObbligatorioTrascrizione, pNV, &pNV->m_bObbligatorioTrascrizione);
}

BOOL CTipiVariantiGeneticheSet::DeleteRecordset(const CString &strCommento)
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

CString CTipiVariantiGeneticheSet::SetBaseFilter(const CString &strFilter)
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

BOOL CTipiVariantiGeneticheSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

// Public Methods
CString CTipiVariantiGeneticheSet::GetCodice(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::GetCodice"))
	{
		if (!IsEOF())
			sReturn = m_sCodice;

		CloseRecordset("CTipiVariantiGeneticheSet::GetCodice");
	}

	return sReturn;
}
BOOL CTipiVariantiGeneticheSet::SetCodice(long lID, CString sCodice)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::SetCodice"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiVariantiGeneticheSet::SetCodice"))
			{
				m_sCodice = sCodice;
				if (UpdateRecordset("CTipiVariantiGeneticheSet::SetCodice"))
					bReturn = TRUE; 
			}
		}

		CloseRecordset("CTipiVariantiGeneticheSet::SetCodice");
	}

	return bReturn;
}

CString CTipiVariantiGeneticheSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CTipiVariantiGeneticheSet::GetDescrizione");
	}

	return sReturn;
}
BOOL CTipiVariantiGeneticheSet::SetDescrizione(long lID, CString sDescrizione)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::SetDescrizione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiVariantiGeneticheSet::SetDescrizione"))
			{
				m_sDescrizione = sDescrizione;
				if (UpdateRecordset("CTipiVariantiGeneticheSet::SetDescrizione"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiVariantiGeneticheSet::SetDescrizione");
	}

	return bReturn;
}

void CTipiVariantiGeneticheSet::GetObbligatori(long lID, BOOL& bCodiceVariante, BOOL& bTipoAlterazione, BOOL& bTrascrizione)
{	
	bCodiceVariante = FALSE;
	bTipoAlterazione = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::GetObbligatori"))
	{
		if (!IsEOF())
		{
			bCodiceVariante = m_bObbligatorioCodiceVariante;
			bTipoAlterazione = m_bObbligatorioTipoAlterazione;
			bTrascrizione = m_bObbligatorioTrascrizione;
		}

		CloseRecordset("CTipiVariantiGeneticheSet::GetObbligatori");
	}
}

BOOL CTipiVariantiGeneticheSet::SetObbligatori(long lID, BOOL bCodiceVariante, BOOL bTipoAlterazione, BOOL bTrascrizione)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::SetObbligatori"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiVariantiGeneticheSet::SetObbligatori"))
			{
				m_bObbligatorioCodiceVariante = bCodiceVariante;
				m_bObbligatorioTipoAlterazione = bTipoAlterazione;
				m_bObbligatorioTrascrizione = bTrascrizione;

				if (UpdateRecordset("CTipiVariantiGeneticheSet::SetObbligatori"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiVariantiGeneticheSet::SetObbligatori");
	}

	return bReturn;
}

CString CTipiVariantiGeneticheSet::GetTestoRtf(long lID, long lPos)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::GetTestoRtf"))
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
		CloseRecordset("CTipiVariantiGeneticheSet::GetTestoRtf");
	}

	return sReturn;
}
BOOL CTipiVariantiGeneticheSet::SetTestoRtf(long lID, long lPos, CString sTesto)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::SetTestoRtf"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiVariantiGeneticheSet::SetTestoRtf"))
			{
				switch (lPos)
				{
				case 1:
					m_sTestoRtf001 = sTesto;
					break;			
				default:
					break;
				}
				if (UpdateRecordset("CTipiVariantiGeneticheSet::SetTestoRtf"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CTipiVariantiGeneticheSet::SetTestoRtf");
	}

	return bReturn;
}

//Julio BUG 3791 - Melhoria frases resultado laudo genomica
long CTipiVariantiGeneticheSet::GetOrdine(long lID)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::GetOrdine"))
	{
		if (!IsEOF())
			lReturn = m_lOrdine;

		CloseRecordset("CTipiVariantiGeneticheSet::GetOrdine");
	}

	return lReturn;
}

//Julio BUG 3791 - Melhoria frases resultado laudo genomica
BOOL CTipiVariantiGeneticheSet::SetOrdine(long lID, long lOrdine)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::SetOrdine"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiVariantiGeneticheSet::SetOrdine"))
			{
				m_lOrdine = lOrdine;
				if (UpdateRecordset("CTipiVariantiGeneticheSet::SetOrdine"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiVariantiGeneticheSet::SetOrdine");
	}

	return bReturn;
}

//Julio BUG 3791 - Melhoria frases resultado laudo genomica
BOOL CTipiVariantiGeneticheSet::GetFraseRemovibile(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::GetFraseRemovibile"))
	{
		if (!IsEOF())
			bReturn = m_bFraseRemovibile;

		CloseRecordset("CTipiVariantiGeneticheSet::GetFraseRemovibile");
	}

	return bReturn;
}

//Julio BUG 3791 - Melhoria frases resultado laudo genomica
BOOL CTipiVariantiGeneticheSet::SetFraseRemovibile(long lID, BOOL bRemovibile)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::SetFraseRemovibile"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiVariantiGeneticheSet::SetFraseRemovibile"))
			{
				m_bFraseRemovibile = bRemovibile;
				if (UpdateRecordset("CTipiVariantiGeneticheSet::SetFraseRemovibile"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CTipiVariantiGeneticheSet::SetFraseRemovibile");
	}

	return bReturn;
}

BOOL CTipiVariantiGeneticheSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CTipiVariantiGeneticheSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTipiVariantiGeneticheSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CTipiVariantiGeneticheSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CTipiVariantiGeneticheSet::SetEliminato");
	}

	return bReturn;
}

void CTipiVariantiGeneticheSet::GetIDList(CList<long>& listID)
{	
	SetSortRecord("Ordine"); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	if (OpenRecordset("CTipiVariantiGeneticheSet::GetEliminato"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CTipiVariantiGeneticheSet::GetEliminato");
	}
}