#include "stdafx.h"
#include "Endox.h"
#include "FarmaciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFarmaciSet, CBaseSet)

CFarmaciSet::CFarmaciSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 14;
}

CString CFarmaciSet::GetDefaultSQL()
{
	return "FARMACI";
}

void CFarmaciSet::SetEmpty()
{
	m_lID = 0;
	m_sAIC = "";
	m_sNome = "";
	m_sPrincipioAttivo = "";
	m_sDescrizione = "";
	m_sClasse = "";
	m_sNota1 = "";
	m_sNota2 = "";
	m_sDitta = "";
	m_sCampoLibero = "";
	m_sBugiardinoRTF = "";
	m_sBugiardinoTXT = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CFarmaciSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "AIC", m_sAIC, 10);
		RFX_Text(pFX, "Nome", m_sNome, 255);
		RFX_Text(pFX, "PrincipioAttivo", m_sPrincipioAttivo, 255);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "Classe", m_sClasse, 10);
		RFX_Text(pFX, "Nota1", m_sNota1, 10);
		RFX_Text(pFX, "Nota2", m_sNota2, 10);
		RFX_Text(pFX, "Ditta", m_sDitta, 255);
		RFX_Text(pFX, "CampoLibero", m_sCampoLibero, 3999);
		RFX_Text(pFX, "BugiardinoRTF", m_sBugiardinoRTF, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "BugiardinoTXT", m_sBugiardinoTXT, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CFarmaciSet::CreateNew()
{
	return (CBaseSet*)new CFarmaciSet;
}

void CFarmaciSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFarmaciSet* pSet = (CFarmaciSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sAIC) || bCopyAll)
		m_sAIC = pSet->m_sAIC;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNome) || bCopyAll)
		m_sNome = pSet->m_sNome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPrincipioAttivo) || bCopyAll)
		m_sPrincipioAttivo = pSet->m_sPrincipioAttivo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sClasse) || bCopyAll)
		m_sClasse = pSet->m_sClasse;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNota1) || bCopyAll)
		m_sNota1 = pSet->m_sNota1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNota2) || bCopyAll)
		m_sNota2 = pSet->m_sNota2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDitta) || bCopyAll)
		m_sDitta = pSet->m_sDitta;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCampoLibero) || bCopyAll)
		m_sCampoLibero = pSet->m_sCampoLibero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sBugiardinoRTF) || bCopyAll)
		m_sBugiardinoRTF = pSet->m_sBugiardinoRTF;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sBugiardinoTXT) || bCopyAll)
		m_sBugiardinoTXT = pSet->m_sBugiardinoTXT;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CFarmaciSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFarmaciSet* pOV = (CFarmaciSet*)pOldValues;
	CFarmaciSet* pNV = (CFarmaciSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("AIC", pOV, &pOV->m_sAIC, pNV, &pNV->m_sAIC);
	sp.Execute("Nome", pOV, &pOV->m_sNome, pNV, &pNV->m_sNome);
	sp.Execute("PrincipioAttivo", pOV, &pOV->m_sPrincipioAttivo, pNV, &pNV->m_sPrincipioAttivo);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Classe", pOV, &pOV->m_sClasse, pNV, &pNV->m_sClasse);
	sp.Execute("Nota1", pOV, &pOV->m_sNota1, pNV, &pNV->m_sNota1);
	sp.Execute("Nota2", pOV, &pOV->m_sNota2, pNV, &pNV->m_sNota2);
	sp.Execute("Ditta", pOV, &pOV->m_sDitta, pNV, &pNV->m_sDitta);
	sp.Execute("CampoLibero", pOV, &pOV->m_sCampoLibero, pNV, &pNV->m_sCampoLibero);
	sp.Execute("BugiardinoRTF", pOV, &pOV->m_sBugiardinoRTF, pNV, &pNV->m_sBugiardinoRTF);
	sp.Execute("BugiardinoTXT", pOV, &pOV->m_sBugiardinoTXT, pNV, &pNV->m_sBugiardinoTXT);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFarmaciSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CFarmaciSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CFarmaciSet::DeleteRecordset");
	}
	return bReturn;
}

CString CFarmaciSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CFarmaciSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

CString CFarmaciSet::GetFarmacoRicetta(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	SetOpenFilter(strFilter);
	if (OpenRecordset("CFarmaciSet::GetNome"))
	{
		if (!IsEOF())
		{
			m_sPrincipioAttivo.Trim();
			strReturn = m_sPrincipioAttivo + " (" + m_sNome + ") " + m_sDescrizione;

			strReturn.Replace("()", "");

			while(strReturn.Replace("  ", " ") > 0)
				;
		}

		CloseRecordset("CFarmaciSet::GetNome");
	}

	return strReturn;
}

/*
CString CFarmaciSet::GetNome(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CFarmaciSet::GetNome"))
	{
		if (!IsEOF())
			strReturn = m_sNome;

		CloseRecordset("CFarmaciSet::GetNome");
	}

	return strReturn;
}
*/
