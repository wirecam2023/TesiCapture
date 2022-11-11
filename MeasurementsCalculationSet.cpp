//Gabriel - BUG 5533 V2 - Cálculos medidas biométricas
#include "stdafx.h"
#include "MeasurementsCalculationSet.h"
#include "WriteLogLineSPSet.h"
#include "Endox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMeasurementsCalculationSet, CBaseSet)

CMeasurementsCalculationSet::CMeasurementsCalculationSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 10;
}

void CMeasurementsCalculationSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDCALC", m_lIDCalc);
		RFX_Text(pFX, "NAME", m_sName, 255);
		RFX_Long(pFX, "MEASUREMENT1", m_lMeasurement1);
		RFX_Long(pFX, "MEASUREMENT2", m_lMeasurement2);
		RFX_Long(pFX, "MEASUREMENT3", m_lMeasurement3);
		RFX_Long(pFX, "MEASUREMENT4", m_lMeasurement4);
		RFX_Single(pFX, _T("VALUE1"), m_fValue1);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

CString CMeasurementsCalculationSet::GetDefaultSQL()
{
	return "MEASUREMENTS_CALCULATION";
}

void CMeasurementsCalculationSet::SetEmpty()
{
	m_lID = 0;
	m_sName = "";
	m_lIDCalc = 0;
	m_lMeasurement1 = 0;
	m_lMeasurement2 = 0;
	m_lMeasurement3 = 0;
	m_lMeasurement4 = 0;
	m_fValue1 = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CMeasurementsCalculationSet::CreateNew()
{
	return (CBaseSet*)new CMeasurementsCalculationSet;
}

void CMeasurementsCalculationSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMeasurementsCalculationSet* pSet = (CMeasurementsCalculationSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDCalc) || bCopyAll)
		m_lIDCalc = pSet->m_lIDCalc;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sName) || bCopyAll)
		m_sName = pSet->m_sName;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lMeasurement1) || bCopyAll)
		m_lMeasurement1 = pSet->m_lMeasurement1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lMeasurement2) || bCopyAll)
		m_lMeasurement2 = pSet->m_lMeasurement2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lMeasurement3) || bCopyAll)
		m_lMeasurement3 = pSet->m_lMeasurement3;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lMeasurement4) || bCopyAll)
		m_lMeasurement4 = pSet->m_lMeasurement4;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fValue1) || bCopyAll)
		m_fValue1 = pSet->m_fValue1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CMeasurementsCalculationSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMeasurementsCalculationSet* pOV = (CMeasurementsCalculationSet*)pOldValues;
	CMeasurementsCalculationSet* pNV = (CMeasurementsCalculationSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDCALC", pOV, &pOV->m_lIDCalc, pNV, &pNV->m_lIDCalc);
	sp.Execute("NAME", pOV, &pOV->m_sName, pNV, &pNV->m_sName);
	sp.Execute("MEASUREMENT1", pOV, &pOV->m_lMeasurement1, pNV, &pNV->m_lMeasurement1);
	sp.Execute("MEASUREMENT2", pOV, &pOV->m_lMeasurement2, pNV, &pNV->m_lMeasurement2);
	sp.Execute("MEASUREMENT3", pOV, &pOV->m_lMeasurement3, pNV, &pNV->m_lMeasurement3);
	sp.Execute("MEASUREMENT4", pOV, &pOV->m_lMeasurement4, pNV, &pNV->m_lMeasurement4);
	sp.Execute("VALUE1", pOV, &pOV->m_fValue1, pNV, &pNV->m_fValue1);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

CString CMeasurementsCalculationSet::SetBaseFilter(const CString &strFilter)
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

BOOL CMeasurementsCalculationSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	Delete();

	return TRUE;
}


void CMeasurementsCalculationSet::AddRow(long lIDCalc, long lMeasurement1, long lMeasurement2, long lMeasurement3, long lMeasurement4, CString sName, float fValue1)
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

		m_lIDCalc = lIDCalc;
		m_sName = sName;
		m_lMeasurement1 = lMeasurement1;
		m_lMeasurement2 = lMeasurement2;
		m_lMeasurement3 = lMeasurement3;
		m_lMeasurement4 = lMeasurement4;
		m_fValue1 = fValue1;
		m_lUO = theApp.m_lUO;

		Update();

		/*CWriteLogLineSPSet().Exec(
			0, 0, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS_ALIAS_MAPPING", 1, "ID",
			m_lID, "ALIAS", "", m_sAlias, "CMeasurementsAliasMappingSet::AddRow");
		CWriteLogLineSPSet().Exec(
			0, 0, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS_ALIAS_MAPPING", 1, "ID",
			m_lID, "NOMEPARAMETRO", "", m_sNomeParametro, "CMeasurementsAliasMappingSet::AddRow");
		CWriteLogLineSPSet().Exec(
			0, 0, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS_ALIAS_MAPPING", 1, "ID",
			m_lID, "VARIABLENAME", "", m_sVariableName, "CMeasurementsAliasMappingSet::AddRow");
		//Gabriel - BUG 5533 V2 - Filtro por UO
		if (m_bColumnsEspermograma)
		{
			CWriteLogLineSPSet().Exec(
				0, 0, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS_ALIAS_MAPPING", 1, "ID",
				m_lID, "UO", "", sUO, "CMeasurementsAliasMappingSet::AddRow");
		}*/
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

BOOL CMeasurementsCalculationSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CMeasurementsCalculationSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CMeasurementsCalculationSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CMeasurementsCalculationSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CMeasurementsCalculationSet::SetEliminato");
	}

	return bReturn;
}

void CMeasurementsCalculationSet::GetIDList(CList<long>& listID)
{
	SetSortRecord("ID");
	if (OpenRecordset("CMeasurementsCalculationSet::GetIDList"))
	{
		while (!IsEOF())
		{
			listID.AddTail(m_lID);
			MoveNext();
		}

		CloseRecordset("CMeasurementsCalculationSet::GetIDList");
	}
}