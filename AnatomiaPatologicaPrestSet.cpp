#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaPrestSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaPrestSet, CBaseSet)

CAnatomiaPatologicaPrestSet::CAnatomiaPatologicaPrestSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

CString CAnatomiaPatologicaPrestSet::GetDefaultSQL()
{
	return "AnatomiaPatologicaPrest";
}

void CAnatomiaPatologicaPrestSet::SetEmpty()
{
	m_lID = 0;
	m_sPrestazione = "";
	m_sCodice = "";
	m_sDescrizione = "";
	m_sTipoEsame = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CAnatomiaPatologicaPrestSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Prestazione", m_sPrestazione, 50);
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "TipoEsame", m_sTipoEsame, 1);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CAnatomiaPatologicaPrestSet::GetFieldText(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CAnatomiaPatologicaPrestSet::GetFieldText"))
	{
		if (!IsEOF())
		{
			strReturn = m_sDescrizione;
			strReturn.Trim();
		}

		CloseRecordset("CAnatomiaPatologicaPrestSet::GetFieldText");
	}

	return strReturn;
}

CString CAnatomiaPatologicaPrestSet::GetFieldTextComplete(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CAnatomiaPatologicaPrestSet::GetFieldText"))
	{
		if (!IsEOF())
		{
			strReturn = m_sTipoEsame + " - " + m_sDescrizione;
			strReturn.Trim();
		}

		CloseRecordset("CAnatomiaPatologicaPrestSet::GetFieldText");
	}

	return strReturn;
}

CBaseSet* CAnatomiaPatologicaPrestSet::CreateNew()
{
	return (CBaseSet*)new CAnatomiaPatologicaPrestSet;
}

void CAnatomiaPatologicaPrestSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CAnatomiaPatologicaPrestSet* pSet = (CAnatomiaPatologicaPrestSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPrestazione) || bCopyAll)
		m_sPrestazione = pSet->m_sPrestazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTipoEsame) || bCopyAll)
		m_sTipoEsame = pSet->m_sTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CAnatomiaPatologicaPrestSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CAnatomiaPatologicaPrestSet* pOV = (CAnatomiaPatologicaPrestSet*)pOldValues;
	CAnatomiaPatologicaPrestSet* pNV = (CAnatomiaPatologicaPrestSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Prestazione", pOV, &pOV->m_sPrestazione, pNV, &pNV->m_sPrestazione);
	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("TipoEsame", pOV, &pOV->m_sTipoEsame, pNV, &pNV->m_sTipoEsame);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CAnatomiaPatologicaPrestSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CAnatomiaPatologicaPrestSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CAnatomiaPatologicaPrestSet::DeleteRecordset");
	}
	return bReturn;
}

CString CAnatomiaPatologicaPrestSet::SetBaseFilter(const CString &strFilter)
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

BOOL CAnatomiaPatologicaPrestSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
