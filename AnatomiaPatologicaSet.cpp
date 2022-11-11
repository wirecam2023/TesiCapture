#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaSet, CBaseSet)

CAnatomiaPatologicaSet::CAnatomiaPatologicaSet()
	: CBaseSet(&m_lID, "ID")
{
	SetEmpty();

	m_nFields = 15;
	SetBaseFilter("");
}

CString CAnatomiaPatologicaSet::GetDefaultSQL()
{
	return "AnatomiaPatologica";
}

void CAnatomiaPatologicaSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_sIDCampione = "";
	m_sTipo = "";
	m_sIntervCodice = "";
	m_sIntervProcedura = "";
	m_lPrelievi = 1;
	m_sDescrizione = "";
	m_sTopografia = "";
	m_sSnomed1 = "";
	m_sSnomed2 = "";
	m_sSnomed3 = "";
	m_lIDPrestazioneAssociata = 0;
	m_sDescrizioneAnatomia = "";
	m_bEliminato = FALSE;
}

void CAnatomiaPatologicaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Text(pFX, "IDCampione", m_sIDCampione, 50);
		RFX_Text(pFX, "Tipo", m_sTipo, 1);
		RFX_Text(pFX, "IntervCodice", m_sIntervCodice, 50);
		RFX_Text(pFX, "IntervProcedura", m_sIntervProcedura, 255);
		RFX_Long(pFX, "Prelievi", m_lPrelievi);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "Topografia", m_sTopografia, 10);
		RFX_Text(pFX, "Snomed1", m_sSnomed1, 10);
		RFX_Text(pFX, "Snomed2", m_sSnomed2, 10);
		RFX_Text(pFX, "Snomed3", m_sSnomed3, 10);
		RFX_Long(pFX, "IDPrestazioneAssociata", m_lIDPrestazioneAssociata);
		RFX_Text(pFX, "Descrizione_Anatomia", m_sDescrizioneAnatomia, 400);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CAnatomiaPatologicaSet::CreateNew()
{
	return (CBaseSet*)new CAnatomiaPatologicaSet;
}

void CAnatomiaPatologicaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CAnatomiaPatologicaSet* pAnatomiaPatologicaSet = (CAnatomiaPatologicaSet*)pOriginalSet;

	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pAnatomiaPatologicaSet->m_lIDEsame;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_sIDCampione) || bCopyAll)
		m_sIDCampione = pAnatomiaPatologicaSet->m_sIDCampione;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_sTipo) || bCopyAll)
		m_sTipo = pAnatomiaPatologicaSet->m_sTipo;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_sIntervCodice) || bCopyAll)
		m_sIntervCodice= pAnatomiaPatologicaSet->m_sIntervCodice;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_sIntervProcedura) || bCopyAll)
		m_sIntervProcedura = pAnatomiaPatologicaSet->m_sIntervProcedura;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_lPrelievi) || bCopyAll)
		m_lPrelievi = pAnatomiaPatologicaSet->m_lPrelievi;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pAnatomiaPatologicaSet->m_sDescrizione;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_sTopografia) || bCopyAll)
		m_sTopografia = pAnatomiaPatologicaSet->m_sTopografia;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_sSnomed1) || bCopyAll)
		m_sSnomed1 = pAnatomiaPatologicaSet->m_sSnomed1;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_sSnomed2) || bCopyAll)
		m_sSnomed2 = pAnatomiaPatologicaSet->m_sSnomed2;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_sSnomed3) || bCopyAll)
		m_sSnomed3 = pAnatomiaPatologicaSet->m_sSnomed3;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_lIDPrestazioneAssociata) || bCopyAll)
		m_lIDPrestazioneAssociata = pAnatomiaPatologicaSet->m_lIDPrestazioneAssociata;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_sDescrizioneAnatomia) || bCopyAll)
		m_sDescrizioneAnatomia = pAnatomiaPatologicaSet->m_sDescrizioneAnatomia;
	if (!pAnatomiaPatologicaSet->IsOpen() || pAnatomiaPatologicaSet->IsFieldDirty(&pAnatomiaPatologicaSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pAnatomiaPatologicaSet->m_bEliminato;
}

void CAnatomiaPatologicaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CAnatomiaPatologicaSet* pOV = (CAnatomiaPatologicaSet*)pOldValues;
	CAnatomiaPatologicaSet* pNV = (CAnatomiaPatologicaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDCampione", pOV, &pOV->m_sIDCampione, pNV, &pNV->m_sIDCampione);
	sp.Execute("Tipo", pOV, &pOV->m_sTipo, pNV, &pNV->m_sTipo);
	sp.Execute("IntervCodice", pOV, &pOV->m_sIntervCodice, pNV, &pNV->m_sIntervCodice);
	sp.Execute("IntervProcedura", pOV, &pOV->m_sIntervProcedura, pNV, &pNV->m_sIntervProcedura);
	sp.Execute("Prelievi", pOV, &pOV->m_lPrelievi, pNV, &pNV->m_lPrelievi);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Topografia", pOV, &pOV->m_sTopografia, pNV, &pNV->m_sTopografia);
	sp.Execute("Snomed1", pOV, &pOV->m_sSnomed1, pNV, &pNV->m_sSnomed1);
	sp.Execute("Snomed2", pOV, &pOV->m_sSnomed2, pNV, &pNV->m_sSnomed2);
	sp.Execute("Snomed3", pOV, &pOV->m_sSnomed3, pNV, &pNV->m_sSnomed3);
	sp.Execute("IDPrestazioneAssociata", pOV, &pOV->m_lIDPrestazioneAssociata, pNV, &pNV->m_lIDPrestazioneAssociata);
	sp.Execute("Descrizione_Anatomia", pOV, &pOV->m_sDescrizioneAnatomia, pNV, &pNV->m_sDescrizioneAnatomia);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CAnatomiaPatologicaSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CAnatomiaPatologicaSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CAnatomiaPatologicaSet::DeleteRecordset");
	}
	return bReturn;
}

CString CAnatomiaPatologicaSet::SetBaseFilter(const CString &strFilter)
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

BOOL CAnatomiaPatologicaSet::HasMaterials(long idEsame)
{
	BOOL bResult = FALSE;

	CString filter;
	filter.Format("IDESAME=%li", idEsame);

	SetOpenFilter(filter);

	if (OpenRecordset("CAnatomiaPatologicaSet::HasMaterials"))
	{
		if (!IsEOF())		
			bResult = TRUE;		

		CloseRecordset("CAnatomiaPatologicaSet::HasMaterials");
	}

	return bResult;
}