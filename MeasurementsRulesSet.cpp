//Gabriel - BUG 5533 V2 - Regras medidas biométricas
#include "stdafx.h"
#include "MeasurementsRulesSet.h"
#include "WriteLogLineSPSet.h"
#include "Endox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMeasurementsRulesSet, CBaseSet)

CMeasurementsRulesSet::CMeasurementsRulesSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 10;
}

void CMeasurementsRulesSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "NAME", m_sName, 255);
		RFX_Long(pFX, "IDRULE", m_lIDRule);
		RFX_Long(pFX, "IDCONDITION", m_lIDCondition);
		RFX_Long(pFX, "MEASUREMENTCONDITION", m_lMeasurementCondition);
		RFX_Long(pFX, "MEASUREMENTRULE", m_lMeasurementRule);
		RFX_Text(pFX, "VALUECONDITION1", m_sValueCondition1, 255);
		RFX_Text(pFX, "VALUECONDITION2", m_sValueCondition2, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

CString CMeasurementsRulesSet::GetDefaultSQL()
{
	return "MEASUREMENTS_RULES";
}

void CMeasurementsRulesSet::SetEmpty()
{
	m_lID = 0;
	m_sName = "";
	m_lIDRule = 0;
	m_lIDCondition = 0;
	m_lMeasurementCondition = 0;
	m_lMeasurementRule = 0;
	m_sValueCondition1 = "";
	m_sValueCondition2 = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CMeasurementsRulesSet::CreateNew()
{
	return (CBaseSet*)new CMeasurementsRulesSet;
}

void CMeasurementsRulesSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMeasurementsRulesSet* pSet = (CMeasurementsRulesSet*)pOriginalSet;
	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sName) || bCopyAll)
		m_sName = pSet->m_sName;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDRule) || bCopyAll)
		m_lIDRule = pSet->m_lIDRule;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDCondition) || bCopyAll)
		m_lIDCondition = pSet->m_lIDCondition;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lMeasurementCondition) || bCopyAll)
		m_lMeasurementCondition = pSet->m_lMeasurementCondition;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lMeasurementRule) || bCopyAll)
		m_lMeasurementRule = pSet->m_lMeasurementRule;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sValueCondition1) || bCopyAll)
		m_sValueCondition1 = pSet->m_sValueCondition1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sValueCondition2) || bCopyAll)
		m_sValueCondition2 = pSet->m_sValueCondition2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CMeasurementsRulesSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMeasurementsRulesSet* pOV = (CMeasurementsRulesSet*)pOldValues;
	CMeasurementsRulesSet* pNV = (CMeasurementsRulesSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("NAME", pOV, &pOV->m_sName, pNV, &pNV->m_sName);
	sp.Execute("IDRULE", pOV, &pOV->m_lIDRule, pNV, &pNV->m_lIDRule);
	sp.Execute("IDCONDITION", pOV, &pOV->m_lIDCondition, pNV, &pNV->m_lIDCondition);
	sp.Execute("MEASUREMENTCONDITION", pOV, &pOV->m_lMeasurementCondition, pNV, &pNV->m_lMeasurementCondition);
	sp.Execute("MEASUREMENTRULE", pOV, &pOV->m_lMeasurementRule, pNV, &pNV->m_lMeasurementRule);
	sp.Execute("VALUECONDITION1", pOV, &pOV->m_sValueCondition1, pNV, &pNV->m_sValueCondition1);
	sp.Execute("VALUECONDITION2", pOV, &pOV->m_sValueCondition2, pNV, &pNV->m_sValueCondition2);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

CString CMeasurementsRulesSet::SetBaseFilter(const CString &strFilter)
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

BOOL CMeasurementsRulesSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	Delete();

	return TRUE;
}


void CMeasurementsRulesSet::AddRow(long lIDCondition, long lMeasurementCondition, long lIDRule, long lMeasurementRule, CString sName, CString sValueCondition1, CString sValueCondition2)
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

		m_sName = sName;
		m_lIDRule = lIDRule;
		m_lMeasurementRule = lMeasurementRule;
		m_lIDCondition = lIDCondition;
		m_lMeasurementCondition = lMeasurementCondition;
		m_sValueCondition1 = sValueCondition1;
		m_sValueCondition2 = sValueCondition2;
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

BOOL CMeasurementsRulesSet::SetEliminato(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CMeasurementsRulesSet::SetEliminato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CMeasurementsRulesSet::SetEliminato"))
			{
				m_bEliminato = TRUE;
				if (UpdateRecordset("CMeasurementsRulesSet::SetEliminato"))
					bReturn = TRUE;
			}
		}
		CloseRecordset("CMeasurementsRulesSet::SetEliminato");
	}

	return bReturn;
}