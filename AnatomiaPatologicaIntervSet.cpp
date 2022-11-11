#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaIntervSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaIntervSet, CBaseSet)

CAnatomiaPatologicaIntervSet::CAnatomiaPatologicaIntervSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 9;
}

CString CAnatomiaPatologicaIntervSet::GetDefaultSQL()
{
	return "AnatomiaPatologicaInterv";
}

void CAnatomiaPatologicaIntervSet::SetEmpty()
{
	m_lID = 0;
	m_sCodice = "";
	m_sDescrizione = "";
	m_sTipo = "";
	m_lIDPrestazione = 0;
	m_sDescrizioneAnatomia = "";
	m_sAPSede = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CAnatomiaPatologicaIntervSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 50);
		RFX_Text(pFX, "Tipo", m_sTipo, 1);
		RFX_Long(pFX, "ID_Prestazioni", m_lIDPrestazione);
		RFX_Text(pFX, "Descrizione_Anatomia", m_sDescrizioneAnatomia, 400);
		RFX_Text(pFX, "APSede", m_sAPSede, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CAnatomiaPatologicaIntervSet::CreateNew()
{
	return (CBaseSet*)new CAnatomiaPatologicaIntervSet;
}

void CAnatomiaPatologicaIntervSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CAnatomiaPatologicaIntervSet* pSet = (CAnatomiaPatologicaIntervSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTipo) || bCopyAll)
		m_sTipo = pSet->m_sTipo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDPrestazione) || bCopyAll)
		m_lIDPrestazione = pSet->m_lIDPrestazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizioneAnatomia) || bCopyAll)
		m_sDescrizioneAnatomia = pSet->m_sDescrizioneAnatomia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sAPSede) || bCopyAll)
		m_sAPSede = pSet->m_sAPSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CAnatomiaPatologicaIntervSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CAnatomiaPatologicaIntervSet* pOV = (CAnatomiaPatologicaIntervSet*)pOldValues;
	CAnatomiaPatologicaIntervSet* pNV = (CAnatomiaPatologicaIntervSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Tipo", pOV, &pOV->m_sTipo, pNV, &pNV->m_sTipo);
	sp.Execute("ID_Prestazioni", pOV, &pOV->m_lIDPrestazione, pNV, &pNV->m_lIDPrestazione);
	sp.Execute("Descrizione_Anatomia", pOV, &pOV->m_sDescrizioneAnatomia, pNV, &pNV->m_sDescrizioneAnatomia);
	sp.Execute("APSede", pOV, &pOV->m_sAPSede, pNV, &pNV->m_sAPSede);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CAnatomiaPatologicaIntervSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CAnatomiaPatologicaIntervSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CAnatomiaPatologicaIntervSet::DeleteRecordset");
	}
	return bReturn;
}

CString CAnatomiaPatologicaIntervSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CAnatomiaPatologicaIntervSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}