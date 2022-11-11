#include "stdafx.h"
#include "Endox.h"
#include "FrasiRtfSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFrasiRtfSet, CBaseSet)

CFrasiRtfSet::CFrasiRtfSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 10;
}

void CFrasiRtfSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Sesso", m_lSesso);
		RFX_Long(pFX, "Tipo", m_lTipo);
		RFX_Text(pFX, "Sezione", m_sSezione, 50);
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Text(pFX, "Indice", m_sIndice, 255);
		RFX_Text(pFX, "TestoRTF", m_sTestoRTF, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX, "TestoTXT", m_sTestoTXT, _TEXT_CONTROL_FIELD_LIMIT);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
		RFX_Long(pFX, "UO", m_lUO);
	}
}

CString CFrasiRtfSet::GetDefaultSQL()
{
	return "FrasiRtf";
}

void CFrasiRtfSet::SetEmpty()
{
	m_lID = 0;
	m_lSesso = -1;
	m_lTipo = 0;
	m_sSezione = "";
	m_sCodice = "";
	m_sIndice = "";
	m_sTestoRTF = "";
	m_sTestoTXT = "";
	m_bEliminato = FALSE;
	m_lUO = 0;
}

CBaseSet* CFrasiRtfSet::CreateNew()
{
	return (CBaseSet*)new CFrasiRtfSet;
}

void CFrasiRtfSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFrasiRtfSet* pSet = (CFrasiRtfSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lSesso) || bCopyAll)
		m_lSesso = pSet->m_lSesso;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTipo) || bCopyAll)
		m_lTipo = pSet->m_lTipo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSezione) || bCopyAll)
		m_sSezione = pSet->m_sSezione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIndice) || bCopyAll)
		m_sIndice = pSet->m_sIndice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoRTF) || bCopyAll)
		m_sTestoRTF = pSet->m_sTestoRTF;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTestoTXT) || bCopyAll)
		m_sTestoTXT = pSet->m_sTestoTXT;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
}

void CFrasiRtfSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFrasiRtfSet* pOV = (CFrasiRtfSet*)pOldValues;
	CFrasiRtfSet* pNV = (CFrasiRtfSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Sesso", pOV, &pOV->m_lSesso, pNV, &pNV->m_lSesso);
	sp.Execute("Tipo", pOV, &pOV->m_lTipo, pNV, &pNV->m_lTipo);
	sp.Execute("Sezione", pOV, &pOV->m_sSezione, pNV, &pNV->m_sSezione);
	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Indice", pOV, &pOV->m_sIndice, pNV, &pNV->m_sIndice);
	sp.Execute("TestoRTF", pOV, &pOV->m_sTestoRTF, pNV, &pNV->m_sTestoRTF);
	sp.Execute("TestoTXT", pOV, &pOV->m_sTestoTXT, pNV, &pNV->m_sTestoTXT);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
}

BOOL CFrasiRtfSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CFrasiRtfSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CFrasiRtfSet::DeleteRecordset");
	}
	return bReturn;
}

CString CFrasiRtfSet::SetBaseFilter(const CString &strFilter)
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

BOOL CFrasiRtfSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

CString CFrasiRtfSet::GetTestoRtf(long lID)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CFrasiRtfSet::GetTestoRtf"))
	{
		if (!IsEOF())
			sReturn = m_sTestoRTF;

		CloseRecordset("CFrasiRtfSet::GetTestoRtf");
	}

	return sReturn;
}

CString CFrasiRtfSet::GetTestoTxt(long lID)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CFrasiRtfSet::GetTestoTxt"))
	{
		if (!IsEOF())
			sReturn = m_sTestoTXT;

		CloseRecordset("CFrasiRtfSet::GetTestoTxt");
	}

	return sReturn;
}

//Julio BUG 3457 - Texter
long CFrasiRtfSet::GetIDByCodice(CString sCodice)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("CODICE LIKE '%s'", sCodice);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CFrasiRtfSet::GetIDByCodice"))
	{
		if (!IsEOF())
			lReturn = m_lID;

		CloseRecordset("CFrasiRtfSet::GetIDByCodice");
	}

	return lReturn;
}