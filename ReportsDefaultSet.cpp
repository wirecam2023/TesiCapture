#include "stdafx.h"
#include "Endox.h"
#include "ReportsDefaultSet.h"

#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CReportsDefaultSet, CBaseSet)

CReportsDefaultSet::CReportsDefaultSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

CString CReportsDefaultSet::GetDefaultSQL()
{
	return "ReportsDefault";
}

void CReportsDefaultSet::SetEmpty()
{
	m_lID = 0;
	m_sSedeEsame = "";
	m_lTipoEsame = 0;
	m_sReport = "";
	m_lCopie = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CReportsDefaultSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID",	m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "SedeEsame", m_sSedeEsame, 255);
		RFX_Long(pFX, "TipoEsame", m_lTipoEsame);
		RFX_Text(pFX, "Report", m_sReport, 1024);
		RFX_Long(pFX, "Copie", m_lCopie);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CReportsDefaultSet::CreateNew()
{
	return (CBaseSet*)new CReportsDefaultSet;
}

void CReportsDefaultSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CReportsDefaultSet* pSet = (CReportsDefaultSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSedeEsame) || bCopyAll)
		m_sSedeEsame = pSet->m_sSedeEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTipoEsame) || bCopyAll)
		m_lTipoEsame = pSet->m_lTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sReport) || bCopyAll)
		m_sReport = pSet->m_sReport;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lCopie) || bCopyAll)
		m_lCopie = pSet->m_lCopie;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

BOOL CReportsDefaultSet::ReportAdd(CString &sSedeEsame, long lTipoEsame, CString sReport, long lCopie)
{
	BOOL bReturn = FALSE;

	if (OpenRecordset("CReportsDefaultSet::ReportAdd"))
	{
		if (AddNewRecordset("CReportsDefaultSet::ReportAdd"))
		{
			m_sSedeEsame = sSedeEsame;
			m_lTipoEsame = lTipoEsame;
			m_sReport = sReport;
			m_lCopie = lCopie;

			bReturn = UpdateRecordset("CReportsDefaultSet::ReportAdd");
		}

		CloseRecordset("CReportsDefaultSet::ReportAdd");
	}

	return bReturn;
}

BOOL CReportsDefaultSet::ReportDel(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CReportsDefaultSet::ReportDel"))
	{
		if (!IsEOF())
			bReturn = DeleteRecordset("CReportsDefaultSet::ReportDel");

		CloseRecordset("CReportsDefaultSet::ReportDel");
	}

	return bReturn;
}

BOOL CReportsDefaultSet::ReportEdt(long lID, CString &sSedeEsame, long lTipoEsame, CString sReport, long lCopie)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CReportsDefaultSet::ReportEdt"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CReportsDefaultSet::ReportEdt"))
			{
				m_sSedeEsame = sSedeEsame;
				m_lTipoEsame = lTipoEsame;
				m_sReport = sReport;
				m_lCopie = lCopie;

				bReturn = UpdateRecordset("CReportsDefaultSet::ReportEdt");
			}
		}

		CloseRecordset("CReportsDefaultSet::ReportEdt");
	}

	return bReturn;
}

BOOL CReportsDefaultSet::ReportUp(long lID1, CString &sSedeEsame, long lTipoEsame)
{
	BOOL bReturn = FALSE;

	// Sandro 15/07/2013 //
	CString sSedeTemp = sSedeEsame;
	sSedeTemp.Replace("'", "''");

	CString strFilter;
	strFilter.Format("SedeEsame='%s' AND TipoEsame=%li", sSedeTemp, lTipoEsame);
	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CReportsDefaultSet::ReportUp"))
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
		CloseRecordset("CReportsDefaultSet::ReportUp");

		// prima di procedere verifico per l'ultima volta che gli ID siano OK //
		if ((lID1 > 0) && (lID1 < 1246576928) && (lID2 > 0) && (lID2 < 1246576928))
		{
			// salvo i dati del record corrente sopra il record precedente //
			if (ReportEdt(lID2, sSedeEsame, lTipoEsame, sReport1, lCopie1))
			{
				// salvo i dati del precedente sul record successivo //
				bReturn = ReportEdt(lID1, sSedeEsame, lTipoEsame, sReport2, lCopie2);
			}
		}
	}

	return bReturn;
}

BOOL CReportsDefaultSet::ReportDn(long lID1, CString &sSedeEsame, long lTipoEsame)
{
	BOOL bReturn = FALSE;

	// Sandro 15/07/2013 //
	CString sSedeTemp = sSedeEsame;
	sSedeTemp.Replace("'", "''");

	CString strFilter;
	strFilter.Format("SedeEsame='%s' AND TipoEsame=%li", sSedeTemp, lTipoEsame);
	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CReportsDefaultSet::ReportUp"))
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
		CloseRecordset("CReportsDefaultSet::ReportUp");

		// prima di procedere verifico per l'ultima volta che gli ID siano OK //
		if ((lID1 > 0) && (lID1 < 1246576928) && (lID2 > 0) && (lID2 < 1246576928))
		{
			// salvo i dati del record corrente sopra il record successivo //
			if (ReportEdt(lID2, sSedeEsame, lTipoEsame, sReport1, lCopie1))
			{
				// salvo i dati del successivo sul record precedente //
				bReturn = ReportEdt(lID1, sSedeEsame, lTipoEsame, sReport2, lCopie2);
			}
		}
	}

	return bReturn;
}

CString CReportsDefaultSet::GetDefaultReport(long lTipoEsame)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("SedeEsame='%s' AND TipoEsame=%li AND Report<>'IMMAGINI'", CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE), lTipoEsame);

	SetOpenFilter(sFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CEsamiView::GetDefaultReport"))
	{
		if (!IsEOF())
		{
			sReturn = m_sReport;
			sReturn.Trim();
		}

		CloseRecordset("CEsamiView::GetDefaultReport");
	}

	return sReturn;
}

void CReportsDefaultSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CReportsDefaultSet* pOV = (CReportsDefaultSet*)pOldValues;
	CReportsDefaultSet* pNV = (CReportsDefaultSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("SedeEsame", pOV, &pOV->m_sSedeEsame, pNV, &pNV->m_sSedeEsame);
	sp.Execute("TipoEsame", pOV, &pOV->m_lTipoEsame, pNV, &pNV->m_lTipoEsame);
	sp.Execute("Report", pOV, &pOV->m_sReport, pNV, &pNV->m_sReport);
	sp.Execute("Copie", pOV, &pOV->m_lCopie, pNV, &pNV->m_lCopie);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CReportsDefaultSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CReportsDefaultSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CReportsDefaultSet::DeleteRecordset");
	}
	return bReturn;
}

CString CReportsDefaultSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CReportsDefaultSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
