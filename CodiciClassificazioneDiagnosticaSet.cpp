#include "stdafx.h"
#include "Endox.h"
#include "CodiciClassificazioneDiagnosticaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCodiciClassificazioneDiagnostSet, CBaseSet)

CCodiciClassificazioneDiagnostSet::CCodiciClassificazioneDiagnostSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 9;
}

CString CCodiciClassificazioneDiagnostSet::GetDefaultSQL()
{
	return "CODICICLASSIFICAZIONEDIAGNOST";
}

void CCodiciClassificazioneDiagnostSet::SetEmpty()
{
	m_lID = 0;
	m_sCodice = "";
	m_sDescrizione = "";
	m_lClassificazione = 0;
	m_bPositivita = FALSE;
	m_fScore = 0.0;
	m_lIDTipoEsame = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CCodiciClassificazioneDiagnostSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if(m_nFields > 1)
	{
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Long(pFX, "Classificazione", m_lClassificazione);
		RFX_Bool(pFX, "Positivita", m_bPositivita);
		RFX_Single(pFX, "Score", m_fScore);
		RFX_Long(pFX, "IDTipoEsame", m_lIDTipoEsame);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

long CCodiciClassificazioneDiagnostSet::FleuryTrans(CString sCodice, CString sDescrizione)
{
	long lReturn = 0;

	sCodice.Trim();
	sCodice.Replace("'", "''");

	sDescrizione.Trim();
	sDescrizione.Replace("'", "''");

	if ((!sCodice.IsEmpty()) && (!sDescrizione.IsEmpty()))
	{
		CString sFilter;
		sFilter.Format("CODICE = '%s' AND DESCRIZIONE = '%s'", sCodice, sDescrizione);
		SetOpenFilter(sFilter);
		if (OpenRecordset("CCodiciClassificazioneDiagnostSet::FleuryTrans"))
		{
			if (!IsEOF())
				lReturn = m_lID;

			CloseRecordset("CCodiciClassificazioneDiagnostSet::FleuryTrans");
		}
	}

	return lReturn;
}

long CCodiciClassificazioneDiagnostSet::GetLongClassificazione(long lID)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if(OpenRecordset("CCodiciClassificazioneDiagnostSet::GetLongClassificazione"))
	{
		if(!IsEOF())
			lReturn = m_lClassificazione;

		CloseRecordset("CCodiciClassificazioneDiagnostSet::GetLongClassificazione");
	}

	return lReturn;
}

CString CCodiciClassificazioneDiagnostSet::GetStringCodice(long lID)
{
	CString strReturn;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if(OpenRecordset("CCodiciClassificazioneDiagnostSet::GetLongClassificazione"))
	{
		if(!IsEOF())
			strReturn = m_sCodice;

		CloseRecordset("CCodiciClassificazioneDiagnostSet::GetLongClassificazione");
	}

	return strReturn;
}

CString CCodiciClassificazioneDiagnostSet::GetStringDescrizione(long lID)
{
	CString strReturn;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if(OpenRecordset("CCodiciClassificazioneDiagnostSet::GetLongClassificazione"))
	{
		if(!IsEOF())
			strReturn = m_sDescrizione;

		CloseRecordset("CCodiciClassificazioneDiagnostSet::GetLongClassificazione");
	}

	return strReturn;
}

float CCodiciClassificazioneDiagnostSet::GetMaxScore()
{
	float fScore = 0.0;

	if (OpenRecordset("CCodiciClassificazioneDiagnostSet::GetMaxScore"))
	{
		while (!IsEOF())
		{
			fScore = max(fScore, m_fScore);
			MoveNext();
		}

		CloseRecordset("CCodiciClassificazioneDiagnostSet::GetMaxScore");
	}

	return fScore;
}

CBaseSet* CCodiciClassificazioneDiagnostSet::CreateNew()
{
	return (CBaseSet*)new CCodiciClassificazioneDiagnostSet;
}

void CCodiciClassificazioneDiagnostSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCodiciClassificazioneDiagnostSet* pSet = (CCodiciClassificazioneDiagnostSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lClassificazione) || bCopyAll)
		m_lClassificazione = pSet->m_lClassificazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bPositivita) || bCopyAll)
		m_bPositivita = pSet->m_bPositivita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fScore) || bCopyAll)
		m_fScore = pSet->m_fScore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CCodiciClassificazioneDiagnostSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCodiciClassificazioneDiagnostSet* pOV = (CCodiciClassificazioneDiagnostSet*)pOldValues;
	CCodiciClassificazioneDiagnostSet* pNV = (CCodiciClassificazioneDiagnostSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Classificazione", pOV, &pOV->m_lClassificazione, pNV, &pNV->m_lClassificazione);
	sp.Execute("Positivita", pOV, &pOV->m_bPositivita, pNV, &pNV->m_bPositivita);
	sp.Execute("Score", pOV, &pOV->m_fScore, pNV, &pNV->m_fScore);
	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCodiciClassificazioneDiagnostSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if(EditRecordset("::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("::DeleteRecordset");
	}
	return bReturn;
}

CString CCodiciClassificazioneDiagnostSet::SetBaseFilter(const CString &strFilter)
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

BOOL CCodiciClassificazioneDiagnostSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

void CCodiciClassificazioneDiagnostSet::GetStringCodiceDescrizione(long lClassificazioneDiagnosi, CString& sDiagnosiCodice, CString& sDiagnosiDescrizione)
{
	sDiagnosiCodice = "";
	sDiagnosiDescrizione = "";

	if (lClassificazioneDiagnosi > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", lClassificazioneDiagnosi);

		SetOpenFilter(strFilter);
		if (OpenRecordset("CCodiciClassificazioneDiagnostSet::GetStringCodiceDescrizione"))
		{
			if (!IsEOF())
			{
				sDiagnosiCodice = m_sCodice;
				sDiagnosiDescrizione = m_sDescrizione;
			}

			CloseRecordset("CCodiciClassificazioneDiagnostSet::GetStringCodiceDescrizione");
		}
	}
}