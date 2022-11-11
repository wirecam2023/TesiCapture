#include "stdafx.h"
#include "Endox.h"
#include "ExtPrestazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtPrestazioniSet, CBaseSet)

CExtPrestazioniSet::CExtPrestazioniSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 10;
}

CString CExtPrestazioniSet::GetDefaultSQL()
{
	return "EXT_PRESTAZIONI";
}

void CExtPrestazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDOrdine", m_lIDOrdine);
		RFX_Text(pFX, "IDPrestazione", m_sIDPrestazione, 50);
		RFX_Text(pFX, "CodicePrestazione", m_sCodicePrestazione, 50);
		RFX_Text(pFX, "DescrizionePrestazione", m_sDescrizionePrestazione, 255);
		RFX_Text(pFX, "Note", m_sNote, 4000);
		RFX_Long(pFX, "Quantita", m_lQuantita);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
		RFX_Text(pFX, "DataRichiesta", m_sDataRichiesta, 14);
		RFX_Text(pFX, "NumeroRicetta", m_sNumeroRicetta, 50);
	}
}

void CExtPrestazioniSet::SetEmpty()
{
	m_lID = 0;
	m_lIDOrdine = 0;
	m_sIDPrestazione = "";
	m_sCodicePrestazione = "";
	m_sDescrizionePrestazione = "";
	m_sNote = "";
	m_lQuantita = 0;
	m_bEliminato = FALSE;
	m_sDataRichiesta = "";
	m_sNumeroRicetta = "";
}

CBaseSet* CExtPrestazioniSet::CreateNew()
{
	return (CBaseSet*)new CExtPrestazioniSet;
}

void CExtPrestazioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtPrestazioniSet* pSet = (CExtPrestazioniSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDOrdine) || bCopyAll)
		m_lIDOrdine = pSet->m_lIDOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIDPrestazione) || bCopyAll)
		m_sIDPrestazione = pSet->m_sIDPrestazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodicePrestazione) || bCopyAll)
		m_sCodicePrestazione = pSet->m_sCodicePrestazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizionePrestazione) || bCopyAll)
		m_sDescrizionePrestazione = pSet->m_sDescrizionePrestazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNote) || bCopyAll)
		m_sNote = pSet->m_sNote;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lQuantita) || bCopyAll)
		m_lQuantita = pSet->m_lQuantita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataRichiesta) || bCopyAll)
		m_sDataRichiesta = pSet->m_sDataRichiesta;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumeroRicetta) || bCopyAll)
		m_sNumeroRicetta = pSet->m_sNumeroRicetta;
}

void CExtPrestazioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtPrestazioniSet* pOV = (CExtPrestazioniSet*)pOldValues;
	CExtPrestazioniSet* pNV = (CExtPrestazioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("ID", pOV, &pOV->m_lID, pNV, &pNV->m_lID);
	sp.Execute("IDOrdine", pOV, &pOV->m_lIDOrdine, pNV, &pNV->m_lIDOrdine);
	sp.Execute("IDPrestazione", pOV, &pOV->m_sIDPrestazione, pNV, &pNV->m_sIDPrestazione);
	sp.Execute("CodicePrestazione", pOV, &pOV->m_sCodicePrestazione, pNV, &pNV->m_sCodicePrestazione);
	sp.Execute("DescrizionePrestazione", pOV, &pOV->m_sDescrizionePrestazione, pNV, &pNV->m_sDescrizionePrestazione);
	sp.Execute("Note", pOV, &pOV->m_sNote, pNV, &pNV->m_sNote);
	sp.Execute("Quantita", pOV, &pOV->m_lQuantita, pNV, &pNV->m_lQuantita);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
	sp.Execute("DataRichiesta", pOV, &pOV->m_sDataRichiesta, pNV, &pNV->m_sDataRichiesta);
	sp.Execute("NumeroRicetta", pOV, &pOV->m_sNumeroRicetta, pNV, &pNV->m_sNumeroRicetta);
}

BOOL CExtPrestazioniSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CExtPrestazioniSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CExtPrestazioniSet::DeleteRecordset");
	}
	return bReturn;
}

CString CExtPrestazioniSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

/* BOOL CExtPrestazioniSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
} */

CString CExtPrestazioniSet::GetNumeroRicetta(int idExtPrestazione)
{
    CString strNewFilter, strNumeroRicetta;
	strNewFilter.Format("id=%li", idExtPrestazione);

	SetOpenFilter(strNewFilter);

	if (OpenRecordset("CExtPrestazioniSet::GetNumeroRicetta"))
	{
		if (!IsEOF())
			strNumeroRicetta = m_sNumeroRicetta;
		
		CloseRecordset("CExtPrestazioniSet::GetNumeroRicetta");
	}

	return strNumeroRicetta;
}

CString CExtPrestazioniSet::GetCodice(CString sIDPrestazione)
{
	CString strNewFilter, strCodice;
	strNewFilter.Format("idprestazione='%s'", sIDPrestazione);

	SetOpenFilter(strNewFilter);

	if (OpenRecordset("CExtPrestazioniSet::GetCodice"))
	{
		if (!IsEOF())
			strCodice = m_sCodicePrestazione;

		CloseRecordset("CExtPrestazioniSet::GetCodice");
	}

	return strCodice;
}

CString CExtPrestazioniSet::GetDescrizione(CString sIDPrestazione)
{
	CString strNewFilter, strDescrizione;
	strNewFilter.Format("idprestazione='%s'", sIDPrestazione);

	SetOpenFilter(strNewFilter);

	if (OpenRecordset("CExtPrestazioniSet::GetDescrizione"))
	{
		if (!IsEOF())
			strDescrizione = m_sDescrizionePrestazione;

		CloseRecordset("CExtPrestazioniSet::GetDescrizione");
	}

	return strDescrizione;
}