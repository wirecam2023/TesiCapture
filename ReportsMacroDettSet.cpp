#include "stdafx.h"
#include "Endox.h"
#include "ReportsMacroDettSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CReportsMacroDettSet, CBaseSet)

CReportsMacroDettSet::CReportsMacroDettSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CReportsMacroDettSet::GetDefaultSQL()
{
	return "ReportsMacroDett";
}

void CReportsMacroDettSet::SetEmpty()
{
	m_lID = 0;
	m_lIDMacro = 0;
	m_sReport = "";
	m_lCopie = 0;
	m_bEliminato = FALSE;
}

void CReportsMacroDettSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID",	m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDMacro",	m_lIDMacro);
		RFX_Text(pFX, "Report",		m_sReport, 1024);
		RFX_Long(pFX, "Copie",		m_lCopie);
		RFX_Bool(pFX, "Eliminato",	m_bEliminato);
	}
}

CBaseSet* CReportsMacroDettSet::CreateNew()
{
	return (CBaseSet*)new CReportsMacroDettSet;
}

void CReportsMacroDettSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CReportsMacroDettSet* pSet = (CReportsMacroDettSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDMacro) || bCopyAll)
		m_lIDMacro = pSet->m_lIDMacro;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sReport) || bCopyAll)
		m_sReport = pSet->m_sReport;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lCopie) || bCopyAll)
		m_lCopie = pSet->m_lCopie;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CReportsMacroDettSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CReportsMacroDettSet* pOV = (CReportsMacroDettSet*)pOldValues;
	CReportsMacroDettSet* pNV = (CReportsMacroDettSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDMacro", pOV, &pOV->m_lIDMacro, pNV, &pNV->m_lIDMacro);
	sp.Execute("Report", pOV, &pOV->m_sReport, pNV, &pNV->m_sReport);
	sp.Execute("Copie", pOV, &pOV->m_lCopie, pNV, &pNV->m_lCopie);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CReportsMacroDettSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CReportsMacroDettSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CReportsMacroDettSet::DeleteRecordset");
	}
	return bReturn;
}

CString CReportsMacroDettSet::SetBaseFilter(const CString &strFilter)
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

BOOL CReportsMacroDettSet::ReportEdt(long lID, long lIDMacro, CString &sReport, long lCopie)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CReportsMacroDettSet::ReportEdt"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CReportsMacroDettSet::ReportEdt"))
			{
				m_lIDMacro = lIDMacro;
				m_sReport = sReport;
				m_lCopie = lCopie;

				bReturn = UpdateRecordset("CReportsMacroDettSet::ReportEdt");
			}
		}

		CloseRecordset("CReportsMacroDettSet::ReportEdt");
	}

	return bReturn;
}

BOOL CReportsMacroDettSet::ReportUp(long lID1, long lIDMacro)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("IDMacro=%li", lIDMacro);
	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CReportsMacroDettSet::ReportUp"))
	{
		// mi posiziono sopra il record da spostare in su //
		while((!IsEOF()) && (m_lID < lID1))
			MoveNext();

		// mi salvo le informazioni di questo record //
		CString sReport1 = m_sReport;
		long lCopie1 = m_lCopie;

		// torno al record precedente su cui devo fare lo scambio //
		MovePrev();

		// mi salvo le informazioni anche di questo record //
		long lID2 = m_lID;
		CString sReport2 = m_sReport;
		long lCopie2 = m_lCopie;

		// ora posso anche chiudere //
		CloseRecordset("CReportsMacroDettSet::ReportUp");

		// prima di procedere verifico per l'ultima volta che gli ID siano OK //
		if ((lID1 > 0) && (lID1 < 1246576928) && (lID2 > 0) && (lID2 < 1246576928))
		{
			// salvo i dati del record corrente sopra il record precedente //
			if (ReportEdt(lID2, lIDMacro, sReport1, lCopie1))
			{
				// salvo i dati del precedente sul record successivo //
				bReturn = ReportEdt(lID1, lIDMacro, sReport2, lCopie2);
			}
		}
	}

	return bReturn;
}

BOOL CReportsMacroDettSet::ReportDn(long lID1, long lIDMacro)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("IDMacro=%li", lIDMacro);
	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CReportsMacroDettSet::ReportUp"))
	{
		// mi posiziono sopra il record da spostare in giù //
		while((!IsEOF()) && (m_lID < lID1))
			MoveNext();

		// mi salvo le informazioni di questo record //
		CString sReport1 = m_sReport;
		long lCopie1 = m_lCopie;

		// vado al record successivo su cui devo fare lo scambio //
		MoveNext();

		// mi salvo le informazioni anche di questo record //
		long lID2 = m_lID;
		CString sReport2 = m_sReport;
		long lCopie2 = m_lCopie;

		// ora posso anche chiudere //
		CloseRecordset("CReportsMacroDettSet::ReportUp");

		// prima di procedere verifico per l'ultima volta che gli ID siano OK //
		if ((lID1 > 0) && (lID1 < 1246576928) && (lID2 > 0) && (lID2 < 1246576928))
		{
			// salvo i dati del record corrente sopra il record successivo //
			if (ReportEdt(lID2, lIDMacro, sReport1, lCopie1))
			{
				// salvo i dati del successivo sul record precedente //
				bReturn = ReportEdt(lID1, lIDMacro, sReport2, lCopie2);
			}
		}
	}

	return bReturn;
}