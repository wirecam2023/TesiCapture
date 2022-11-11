#include "stdafx.h"
#include "Endox.h"
#include "FasiEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFasiEsameSet, CBaseSet)

CFasiEsameSet::CFasiEsameSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CFasiEsameSet::GetDefaultSQL()
{
	return "FASIESAME";
}

void CFasiEsameSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "DESCRIZIONE", m_sDescrizione, 255);
		RFX_Long(pFX, "COLOR", m_lColor);
		RFX_Text(pFX, "REPORTCHIUSURA", m_sReport, 1024);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

void CFasiEsameSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";	
	m_lColor = 0;
	m_sReport = "";
	m_bEliminato = FALSE;
}

CBaseSet* CFasiEsameSet::CreateNew()
{
	return (CBaseSet*)new CFasiEsameSet;
}

void CFasiEsameSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFasiEsameSet* pSet = (CFasiEsameSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lColor) || bCopyAll)
		m_lColor = pSet->m_lColor;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sReport) || bCopyAll)
		m_sReport = pSet->m_sReport;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CFasiEsameSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFasiEsameSet* pOV = (CFasiEsameSet*)pOldValues;
	CFasiEsameSet* pNV = (CFasiEsameSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("DESCRIZIONE", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("COLOR", pOV, &pOV->m_lColor, pNV, &pNV->m_lColor);
	sp.Execute("REPORT", pOV, &pOV->m_sReport, pNV, &pNV->m_sReport);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFasiEsameSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CFasiEsameSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CFasiEsameSet::DeleteRecordset");
	}
	return bReturn;
}

CString CFasiEsameSet::SetBaseFilter(const CString &strFilter)
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

CString CFasiEsameSet::GetDescrizione(long id)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("id=%li", id);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CFasiEsameSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CFasiEsameSet::GetDescrizione");
	}

	return sReturn;
}

COLORREF CFasiEsameSet::GetColor(long id)
{
	long colorReturn = 0;

	CString sFilter;
	sFilter.Format("id=%li", id);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CFasiEsameSet::GetDescrizione"))
	{
		if (!IsEOF())
			colorReturn = m_lColor;

		CloseRecordset("CFasiEsameSet::GetDescrizione");
	}

	return colorReturn;
}

CString CFasiEsameSet::GetReport(long id)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("id=%li", id);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CFasiEsameSet::GetReport"))
	{
		if (!IsEOF())
			sReturn = m_sReport;

		CloseRecordset("CFasiEsameSet::GetReport");
	}

	return sReturn;
}