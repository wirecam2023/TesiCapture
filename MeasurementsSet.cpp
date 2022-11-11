#include "stdafx.h"
#include "MeasurementsSet.h"
#include "MeasurementsAliasMappingSet.h"
#include "Endox.h"
#include "WriteLogLineSPSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMeasurementsSet, CBaseSet)

CMeasurementsSet::CMeasurementsSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

void CMeasurementsSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDESAME", m_lIDEsame);
		RFX_Text(pFX, "ALIAS", m_sAlias, 255);
		RFX_Text(pFX, "NUMERICVALUE", m_sNumericValue, 255);
		RFX_Text(pFX, "CODEVALUE", m_sCodeValue, 255);
		RFX_Text(pFX, "NOTE", m_sNote, 50);		
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

CString CMeasurementsSet::GetDefaultSQL()
{
	return "MEASUREMENTS";
}

void CMeasurementsSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_sAlias = "";
	m_sNumericValue = "";
	m_sCodeValue = "";
	m_sNote = "";
	m_bEliminato = FALSE;
}

CBaseSet* CMeasurementsSet::CreateNew()
{
	return (CBaseSet*)new CMeasurementsSet;
}

void CMeasurementsSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMeasurementsSet* pSet = (CMeasurementsSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sAlias) || bCopyAll)
		m_sAlias = pSet->m_sAlias;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNumericValue) || bCopyAll)
		m_sNumericValue = pSet->m_sNumericValue;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodeValue) || bCopyAll)
		m_sCodeValue = pSet->m_sCodeValue;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNote) || bCopyAll)
		m_sNote = pSet->m_sNote;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CMeasurementsSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMeasurementsSet* pOV = (CMeasurementsSet*)pOldValues;
	CMeasurementsSet* pNV = (CMeasurementsSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDESAME", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("ALIAS", pOV, &pOV->m_sAlias, pNV, &pNV->m_sAlias);
	sp.Execute("NUMERICVALUE", pOV, &pOV->m_sNumericValue, pNV, &pNV->m_sNumericValue);
	sp.Execute("CODEVALUE", pOV, &pOV->m_sCodeValue, pNV, &pNV->m_sCodeValue);
	sp.Execute("NOTE", pOV, &pOV->m_sNote, pNV, &pNV->m_sNote);	
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

CString CMeasurementsSet::SetBaseFilter(const CString &strFilter)
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

BOOL CMeasurementsSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMeasurementsSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMeasurementsSet::DeleteRecordset");
	}
	return bReturn;
}

void CMeasurementsSet::AddRow(long lIDEsame, CString sAlias, CString sNumericValue, CString sCodeValue, CString sNote)
{
	//identity set to 1
	try
	{
		SetOpenFilter("ID=0");

		if (!IsOpen())
		{
			SetOpenFilter("ID=0");
			Open();
		}

		AddNew();

		m_lIDEsame = lIDEsame;
		m_sAlias = sAlias;
		m_sNumericValue = sNumericValue;
		m_sCodeValue = sCodeValue;
		m_sNote = sNote;
		m_bEliminato = FALSE;

		Update();
		
		CString sIdEsame;
		sIdEsame.Format("%li", m_lIDEsame);		

		CWriteLogLineSPSet().Exec(
			0, lIDEsame, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS", 1, "ID",
			m_lID, "IDESAME", "", sIdEsame, "CMeasurementsSet::AddRow");
		CWriteLogLineSPSet().Exec(
			0, lIDEsame, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS", 1, "ID",
			m_lID, "ALIAS", "", m_sAlias, "CMeasurementsSet::AddRow");
		CWriteLogLineSPSet().Exec(
			0, lIDEsame, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS", 1, "ID",
			m_lID, "NUMERICVALUE", "", m_sNumericValue, "CMeasurementsSet::AddRow");
		CWriteLogLineSPSet().Exec(
			0, lIDEsame, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS", 1, "ID",
			m_lID, "CODEVALUE", "", m_sCodeValue, "CMeasurementsSet::AddRow");
		CWriteLogLineSPSet().Exec(
			0, lIDEsame, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS", 1, "ID",
			m_lID, "NOTE", "", m_sNote, "CMeasurementsSet::AddRow");
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
}
void CMeasurementsSet::DelRow(long lID)
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CMeasurementsSet::DelRow"))
	{
		if (!IsEOF())
			DeleteRecordset("CMeasurementsSet::DelRow");

		CloseRecordset("CMeasurementsSet::DelRow");
	}
}

void CMeasurementsSet::UpdateExamMeasurement(long lID, CString sNumericValue, CString sCodeValue) //Julio - correcao lista biometria
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CMeasurementsSet::UpdateExamMeasurement"))
	{
		if (EditRecordset("CMeasurementsSet::UpdateExamMeasurement"))
		{
			m_sNumericValue = sNumericValue;
			m_sCodeValue = sCodeValue;
			
			UpdateRecordset("CMeasurementsSet::UpdateExamMeasurement");
		}
		CloseRecordset("CMeasurementsSet::UpdateExamMeasurement");
	}
}