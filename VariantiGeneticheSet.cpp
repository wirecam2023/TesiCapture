#include "stdafx.h"
#include "Endox.h"
#include "VariantiGeneticheSet.h"
#include "Common.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVariantiGeneticheSet, CBaseSet)


CVariantiGeneticheSet::CVariantiGeneticheSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 13;
}

CString CVariantiGeneticheSet::GetDefaultSQL()
{
	return "VariantiGenetiche";
}

void CVariantiGeneticheSet::SetEmpty()
{
	m_lID = 0;
	m_sTitolo = "";
	m_lIDTipoVariante = 0;
	m_sCodice = "";
	m_sTrascrizione = "";
	m_lIDPatogenicita = 0;
	m_sCromossoma = "";
	m_sGene = "";
	m_sPosizioneGene = "";
	m_lIDTipoAlterazione = 0;
	m_sHGVSc = "";
	m_sHGVSp = "";
	m_bEliminato = FALSE;
}


void CVariantiGeneticheSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{		
		RFX_Text(pFX, "Titolo", m_sTitolo, 255);
		RFX_Long(pFX, "IDTipoVariante", m_lIDTipoVariante);
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Trascrizione", m_sTrascrizione, 255);
		RFX_Long(pFX, "IDPatogenicita", m_lIDPatogenicita);
		RFX_Text(pFX, "Cromossoma", m_sCromossoma, 255);
		RFX_Text(pFX, "Gene", m_sGene, 255);
		RFX_Text(pFX, "PosizioneGene", m_sPosizioneGene, 255);
		RFX_Long(pFX, "IDTipoAlterazione", m_lIDTipoAlterazione);
		RFX_Text(pFX, "HGVSc", m_sHGVSc, 50);
		RFX_Text(pFX, "HGVSp", m_sHGVSp, 50);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CVariantiGeneticheSet::CreateNew()
{
	return (CBaseSet*)new CVariantiGeneticheSet;
}

void CVariantiGeneticheSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CVariantiGeneticheSet* pSet = (CVariantiGeneticheSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitolo) || bCopyAll)
		m_sTitolo = pSet->m_sTitolo;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTrascrizione) || bCopyAll)
		m_sTrascrizione = pSet->m_sTrascrizione;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCromossoma) || bCopyAll)
		m_sCromossoma = pSet->m_sCromossoma;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sGene) || bCopyAll)
		m_sGene = pSet->m_sGene;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPosizioneGene) || bCopyAll)
		m_sPosizioneGene = pSet->m_sPosizioneGene;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sHGVSc) || bCopyAll)
		m_sHGVSc = pSet->m_sHGVSc;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sHGVSp) || bCopyAll)
		m_sHGVSp = pSet->m_sHGVSp;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoVariante) || bCopyAll)
		m_lIDTipoVariante = pSet->m_lIDTipoVariante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDPatogenicita) || bCopyAll)
		m_lIDPatogenicita = pSet->m_lIDPatogenicita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoAlterazione) || bCopyAll)
		m_lIDTipoAlterazione = pSet->m_lIDTipoAlterazione;
}

void CVariantiGeneticheSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CVariantiGeneticheSet* pOV = (CVariantiGeneticheSet*)pOldValues;
	CVariantiGeneticheSet* pNV = (CVariantiGeneticheSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Titolo", pOV, &pOV->m_sTitolo, pNV, &pNV->m_sTitolo);
	sp.Execute("IDTipoVariante", pOV, &pOV->m_lIDTipoVariante, pNV, &pNV->m_lIDTipoVariante);
	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Trascrizione", pOV, &pOV->m_sTrascrizione, pNV, &pNV->m_sTrascrizione);
	sp.Execute("IDPatogenicita", pOV, &pOV->m_lIDPatogenicita, pNV, &pNV->m_lIDPatogenicita);
	sp.Execute("Cromossoma", pOV, &pOV->m_sCromossoma, pNV, &pNV->m_sCromossoma);
	sp.Execute("Gene", pOV, &pOV->m_sGene, pNV, &pNV->m_sGene);
	sp.Execute("PosizioneGene", pOV, &pOV->m_sPosizioneGene, pNV, &pNV->m_sPosizioneGene);
	sp.Execute("IDTipoAlterazione", pOV, &pOV->m_lIDTipoAlterazione, pNV, &pNV->m_lIDTipoAlterazione);
	sp.Execute("HGVSc", pOV, &pOV->m_sHGVSc, pNV, &pNV->m_sHGVSc);
	sp.Execute("HGVSp", pOV, &pOV->m_sHGVSp, pNV, &pNV->m_sHGVSp);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CVariantiGeneticheSet::DeleteRecordset(const CString &strCommento)
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

CString CVariantiGeneticheSet::SetBaseFilter(const CString &strFilter)
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

BOOL CVariantiGeneticheSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

// Public Methods
void CVariantiGeneticheSet::Filter(CList<long>& listID, CString sTitolo, long lIDTipoVariante, CString sCodice, CString sTrascrizione, long lIDPatogenicita,
	CString sCromossoma, CString sGene, CString sPosizioneGene, long lIDTipoAlterazione, CString HGVSc, CString HGVSp)
{
	CString sFilter = "";
	
	if (!sTitolo.IsEmpty())
	{
		sFilter += sFilter.GetLength() > 0 ? " AND Titolo LIKE '%%" + sTitolo + "%%'" : "Titolo LIKE '%%" + sTitolo + "%%'";
	}
	if (lIDTipoVariante > 0)
	{
		CString sValore;
		sValore.Format("%li", lIDTipoVariante);
		sFilter += sFilter.GetLength() > 0 ? " AND IDTipoVariante = " + sValore : "IDTipoVariante = " + sValore;
	}
	if (!sCodice.IsEmpty())
	{
		sFilter += sFilter.GetLength() > 0 ? " AND Codice LIKE '%%" + sCodice + "%%'" : "Codice LIKE '%%" + sCodice + "%%'";
	}
	if (!sTrascrizione.IsEmpty())
	{
		sFilter += sFilter.GetLength() > 0 ? " AND Trascrizione LIKE '%%" + sTrascrizione + "%%'" : "Trascrizione LIKE '%%" + sTrascrizione + "%%'";
	}
	if (lIDPatogenicita > 0)
	{
		CString sValore;
		sValore.Format("%li", lIDPatogenicita);
		sFilter += sFilter.GetLength() > 0 ? " AND IDPatogenicita = " + sValore : "IDPatogenicita = " + sValore;
	}
	if (!sCromossoma.IsEmpty())
	{
		sFilter += sFilter.GetLength() > 0 ? " AND Cromossoma LIKE '%%" + sCromossoma + "%%'" : "Cromossoma LIKE '%%" + sCromossoma + "%%'";
	}
	if (!sGene.IsEmpty())
	{
		sFilter += sFilter.GetLength() > 0 ? " AND Gene LIKE '%%" + sGene + "%%'" : "Gene LIKE '%%" + sGene + "%%'";
	}
	if (!sPosizioneGene.IsEmpty())
	{
		sFilter += sFilter.GetLength() > 0 ? " AND PosizioneGene LIKE '%%" + sPosizioneGene + "%%'" : "PosizioneGene = '%%" + sPosizioneGene + "%%'";
	}
	if (lIDTipoAlterazione > 0)
	{
		CString sValore;
		sValore.Format("%li", lIDTipoAlterazione);
		sFilter += sFilter.GetLength() > 0 ? " AND IDTipoAlterazione = " + sValore : "IDTipoAlterazione = " + sValore;
	}
	if (!HGVSc.IsEmpty())
	{
		sFilter += sFilter.GetLength() > 0 ? " AND HGVSc LIKE '%%" + HGVSc + "%%'" : "HGVSc LIKE '%%" + HGVSc + "%%'";
	}
	if (!HGVSp.IsEmpty())
	{
		sFilter += sFilter.GetLength() > 0 ? " AND HGVSp LIKE '%%" + HGVSp + "%%'" : "HGVSp LIKE '%%" + HGVSp + "%%'";
	}

	if (!sFilter.IsEmpty())
		SetOpenFilter(sFilter);
	
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetEliminato"))
	{
		while (!IsEOF() && listID.GetCount() < FILTER_MAX_COUNT)
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CVariantiGeneticheSet::GetEliminato");
	}	
}
CString CVariantiGeneticheSet::GetTitolo(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetTitolo"))
	{
		if (!IsEOF())
			sReturn = m_sTitolo;

		CloseRecordset("CVariantiGeneticheSet::GetTitolo");
	}

	return sReturn;
}
BOOL CVariantiGeneticheSet::SetTitolo(long lID, CString sTitolo)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetCodice"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetCodice"))
			{
				m_sTitolo = sTitolo;
				if (UpdateRecordset("CVariantiGeneticheSet::SetCodice"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetCodice");
	}

	return bReturn;
}
BOOL CVariantiGeneticheSet::CheckTitolo(CString sTitolo)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Titolo='%s'", sTitolo);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetCodice"))
	{
		if (!IsEOF())					
			bReturn = TRUE;		

		CloseRecordset("CVariantiGeneticheSet::SetCodice");
	}

	return bReturn;
}
CString CVariantiGeneticheSet::GetCodice(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetCodice"))
	{
		if (!IsEOF())
			sReturn = m_sCodice;

		CloseRecordset("CVariantiGeneticheSet::GetCodice");
	}

	return sReturn;
}
BOOL CVariantiGeneticheSet::SetCodice(long lID, CString sCodice)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetCodice"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetCodice"))
			{
				m_sCodice = sCodice;
				if (UpdateRecordset("CVariantiGeneticheSet::SetCodice"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetCodice");
	}

	return bReturn;
}

CString CVariantiGeneticheSet::GetTrascrizione(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetTrascrizione"))
	{
		if (!IsEOF())
			sReturn = m_sTrascrizione;

		CloseRecordset("CVariantiGeneticheSet::GetTrascrizione");
	}

	return sReturn;
}
BOOL CVariantiGeneticheSet::SetTrascrizione(long lID, CString sTrascrizione)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetTrascrizione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetTrascrizione"))
			{
				m_sTrascrizione = sTrascrizione;
				if (UpdateRecordset("CVariantiGeneticheSet::SetTrascrizione"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetTrascrizione");
	}

	return bReturn;
}

CString CVariantiGeneticheSet::GetCromossoma(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetCromossoma"))
	{
		if (!IsEOF())
			sReturn = m_sCromossoma;

		CloseRecordset("CVariantiGeneticheSet::GetCromossoma");
	}

	return sReturn;
}
BOOL CVariantiGeneticheSet::SetCromossoma(long lID, CString sCromossoma)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetCromossoma"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetCromossoma"))
			{
				m_sCromossoma = sCromossoma;
				if (UpdateRecordset("CVariantiGeneticheSet::SetCromossoma"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetCromossoma");
	}

	return bReturn;
}
CString CVariantiGeneticheSet::GetGene(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetGene"))
	{
		if (!IsEOF())
			sReturn = m_sGene;

		CloseRecordset("CVariantiGeneticheSet::GetGene");
	}

	return sReturn;
}
BOOL CVariantiGeneticheSet::SetGene(long lID, CString sGene)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetGene"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetGene"))
			{
				m_sGene = sGene;
				if (UpdateRecordset("CVariantiGeneticheSet::SetGene"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetGene");
	}

	return bReturn;
}
CString CVariantiGeneticheSet::GetPosizioneGene(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetPosizioneGene"))
	{
		if (!IsEOF())
			sReturn = m_sPosizioneGene;

		CloseRecordset("CVariantiGeneticheSet::GetPosizioneGene");
	}

	return sReturn;
}
BOOL CVariantiGeneticheSet::SetPosizioneGene(long lID, CString sPosizioneGene)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetPosizioneGene"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetPosizioneGene"))
			{
				m_sPosizioneGene = sPosizioneGene;
				if (UpdateRecordset("CVariantiGeneticheSet::SetPosizioneGene"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetPosizioneGene");
	}

	return bReturn;
}
CString CVariantiGeneticheSet::GetHGVSc(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetHGVSc"))
	{
		if (!IsEOF())
			sReturn = m_sHGVSc;

		CloseRecordset("CVariantiGeneticheSet::GetHGVSc");
	}

	return sReturn;
}
BOOL CVariantiGeneticheSet::SetHGVSc(long lID, CString sHGVSc)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetHGVSc"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetHGVSc"))
			{
				m_sHGVSc = sHGVSc;
				if (UpdateRecordset("CVariantiGeneticheSet::SetHGVSc"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetHGVSc");
	}

	return bReturn;
}
CString CVariantiGeneticheSet::GetHGVSp(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetHGVSp"))
	{
		if (!IsEOF())
			sReturn = m_sHGVSp;

		CloseRecordset("CVariantiGeneticheSet::GetHGVSp");
	}

	return sReturn;
}
BOOL CVariantiGeneticheSet::SetHGVSp(long lID, CString sHGVSp)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetHGVSp"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetHGVSp"))
			{
				m_sHGVSp = sHGVSp;
				if (UpdateRecordset("CVariantiGeneticheSet::SetHGVSp"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetHGVSp");
	}

	return bReturn;
}
long CVariantiGeneticheSet::GetIDTipoVariante(long lID)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetIDTipoVariante"))
	{
		if (!IsEOF())
			lReturn = m_lIDTipoVariante;

		CloseRecordset("CVariantiGeneticheSet::GetIDTipoVariante");
	}

	return lReturn;
}
BOOL CVariantiGeneticheSet::SetIDTipoVariante(long lID, long lIDTipoVariante)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetIDTipoVariante"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetIDTipoVariante"))
			{
				m_lIDTipoVariante = lIDTipoVariante;
				if (UpdateRecordset("CVariantiGeneticheSet::SetIDTipoVariante"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetIDTipoVariante");
	}

	return bReturn;
}
long CVariantiGeneticheSet::GetIDPatogenicita(long lID)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetIDPatogenicita"))
	{
		if (!IsEOF())
			lReturn = m_lIDPatogenicita;

		CloseRecordset("CVariantiGeneticheSet::GetIDPatogenicita");
	}

	return lReturn;
}
BOOL CVariantiGeneticheSet::SetIDPatogenicita(long lID, long lIDPatogenicita)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetIDPatogenicita"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetIDPatogenicita"))
			{
				m_lIDPatogenicita = lIDPatogenicita;
				if (UpdateRecordset("CVariantiGeneticheSet::SetIDPatogenicita"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetIDPatogenicita");
	}

	return bReturn;
}
long CVariantiGeneticheSet::GetIDTipoAlterazione(long lID)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetIDTipoAlterazione"))
	{
		if (!IsEOF())
			lReturn = m_lIDTipoAlterazione;

		CloseRecordset("CVariantiGeneticheSet::GetIDTipoAlterazione");
	}

	return lReturn;
}
BOOL CVariantiGeneticheSet::SetIDTipoAlterazione(long lID, long lIDTipoAlterazione)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetIDTipoAlterazione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetIDTipoAlterazione"))
			{
				m_lIDTipoAlterazione = lIDTipoAlterazione;
				if (UpdateRecordset("CVariantiGeneticheSet::SetIDTipoAlterazione"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CVariantiGeneticheSet::SetIDTipoAlterazione");
	}

	return bReturn;
}

void CVariantiGeneticheSet::GetAllFields(long lID,
	CString& sTitolo, CString& sCodice, CString& sTrascrizione, CString& sCromossoma,
	CString& sGene, CString& sPosizioneGene, CString& sHGVSc, CString& sHGVSp,
	long& lIDTipoVariante, long& lIDPatogenicita, long& lIDTipoAlterazione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::GetIDTipoAlterazione"))
	{
		if (!IsEOF())
		{
			sTitolo = m_sTitolo;
			sCodice = m_sCodice;
			sTrascrizione = m_sTrascrizione;
			sCromossoma = m_sCromossoma;
			sGene = m_sGene;
			sPosizioneGene = m_sPosizioneGene;
			sHGVSc = m_sHGVSc;
			sHGVSp = m_sHGVSp;
			lIDTipoVariante = m_lIDTipoVariante;
			lIDPatogenicita = m_lIDPatogenicita;
			lIDTipoAlterazione = m_lIDTipoAlterazione;
		}

		CloseRecordset("CVariantiGeneticheSet::GetIDTipoAlterazione");
	}
}

BOOL CVariantiGeneticheSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CVariantiGeneticheSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CVariantiGeneticheSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CVariantiGeneticheSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CVariantiGeneticheSet::SetEliminato");
	}

	return bReturn;
}
void CVariantiGeneticheSet::GetIDList(CList<long>& listID)
{
	SetSortRecord("Titolo");
	if (OpenRecordset("CVariantiGeneticheSet::GetIDList"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CVariantiGeneticheSet::GetIDList");
	}
}