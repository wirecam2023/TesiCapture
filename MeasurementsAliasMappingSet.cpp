#include "stdafx.h"
#include "MeasurementsAliasMappingSet.h"
#include "WriteLogLineSPSet.h"
#include "Endox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMeasurementsAliasMappingSet, CBaseSet)

CMeasurementsAliasMappingSet::CMeasurementsAliasMappingSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_bColumnsEspermograma = CheckColumnExists("MEASUREMENTS_ALIAS_MAPPING", "UO") && CheckColumnExists("MEASUREMENTS_ALIAS_MAPPING", "VALUETYPE") && CheckColumnExists("MEASUREMENTS_ALIAS_MAPPING", "DECIMALS"); //Gabriel - BUG 5533 V2 - Filtro por UO

	m_nFields = m_bColumnsEspermograma ? 7 : 4; //Gabriel - BUG 5533 V2 - Filtro por UO
}

void CMeasurementsAliasMappingSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "ALIAS", m_sAlias, 50);
		RFX_Text(pFX, "NOMEPARAMETRO", m_sNomeParametro, 50);
		RFX_Text(pFX, "VARIABLENAME", m_sVariableName, 50);
		
		//Gabriel - BUG 5533 V2 - Filtro por UO
		if (m_bColumnsEspermograma)
		{
			RFX_Long(pFX, "UO", m_lUO);
			RFX_Text(pFX, "VALUETYPE", m_sValueType, 255);
			RFX_Long(pFX, "DECIMALS", m_lDecimals);
		}
	}
}

CString CMeasurementsAliasMappingSet::GetDefaultSQL()
{
	return "MEASUREMENTS_ALIAS_MAPPING";
}

void CMeasurementsAliasMappingSet::SetEmpty()
{
	m_lID = 0;
	m_sAlias = "";
	m_sNomeParametro = "";
	m_sVariableName = "";	
	m_lUO = 0; //Gabriel - BUG 5533 V2 - Filtro por UO
	m_sValueType = ""; //Gabriel - BUG 5533 V2 - Filtro por UO
	m_lDecimals = 0; //Gabriel - BUG 5533 V2 - Filtro por UO
}

CBaseSet* CMeasurementsAliasMappingSet::CreateNew()
{
	return (CBaseSet*)new CMeasurementsAliasMappingSet;
}

void CMeasurementsAliasMappingSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMeasurementsAliasMappingSet* pSet = (CMeasurementsAliasMappingSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sAlias) || bCopyAll)
		m_sAlias = pSet->m_sAlias;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sVariableName) || bCopyAll)
		m_sVariableName = pSet->m_sVariableName;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNomeParametro) || bCopyAll)
		m_sNomeParametro = pSet->m_sNomeParametro;
	//Gabriel - BUG 5533 V2 - Filtro por UO
	if (m_bColumnsEspermograma)
	{
		if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
			m_lUO = pSet->m_lUO;
		if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sValueType) || bCopyAll)
			m_sValueType = pSet->m_sValueType;
		if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDecimals) || bCopyAll)
			m_lDecimals = pSet->m_lDecimals;
	}
}

void CMeasurementsAliasMappingSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMeasurementsAliasMappingSet* pOV = (CMeasurementsAliasMappingSet*)pOldValues;
	CMeasurementsAliasMappingSet* pNV = (CMeasurementsAliasMappingSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("ALIAS", pOV, &pOV->m_sAlias, pNV, &pNV->m_sAlias);
	sp.Execute("NOMEPARAMETRO", pOV, &pOV->m_sNomeParametro, pNV, &pNV->m_sNomeParametro);
	sp.Execute("VARIABLENAME", pOV, &pOV->m_sVariableName, pNV, &pNV->m_sVariableName);	
	if (m_bColumnsEspermograma)
	{
		sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO); //Gabriel - BUG 5533 V2 - Filtro por UO
		sp.Execute("VALUETYPE", pOV, &pOV->m_sValueType, pNV, &pNV->m_sValueType); //Gabriel - BUG 5533 V2 - Filtro por UO
		sp.Execute("DECIMALS", pOV, &pOV->m_lDecimals, pNV, &pNV->m_lDecimals); //Gabriel - BUG 5533 V2 - Filtro por UO
	}
		
}

CString CMeasurementsAliasMappingSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();
	
	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CMeasurementsAliasMappingSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());
	
	Delete();

	return TRUE;
}


void CMeasurementsAliasMappingSet::AddRow(CString sAlias, CString sVariableName, CString sNomeParametro, CString sValueType, long lDecimals)
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

		m_sAlias = sAlias;
		m_sNomeParametro = sNomeParametro;
		m_sVariableName = sVariableName;
		m_sValueType = sValueType;
		m_lDecimals = lDecimals;
		
		CString sUO;
		if (m_bColumnsEspermograma)
		{
			m_lUO = theApp.m_lUO;//Gabriel - BUG 5533 V2 - Filtro por UO

			sUO.Format("%li", m_lUO);
		}
		Update();

		CWriteLogLineSPSet().Exec(
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
			CWriteLogLineSPSet().Exec(
				0, 0, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS_ALIAS_MAPPING", 1, "ID",
				m_lID, "VALUETYPE", "", m_sValueType, "CMeasurementsAliasMappingSet::AddRow");
			CString sDecimals;
			sDecimals.Format("%li", m_lDecimals);
			CWriteLogLineSPSet().Exec(
				0, 0, theApp.m_sUtenteLoggato, "", "", "MEASUREMENTS_ALIAS_MAPPING", 1, "ID",
				m_lID, "DECIMALS", "", m_sValueType, "CMeasurementsAliasMappingSet::AddRow");
		}
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

void CMeasurementsAliasMappingSet::DelRow(long lID)
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CMeasurementsAliasMappingSet::DelRow"))
	{
		if (!IsEOF())
			DeleteRecordset("CMeasurementsAliasMappingSet::DelRow");

		CloseRecordset("CMeasurementsAliasMappingSet::DelRow");
	}
}

//Gabriel - BUG 5533 V2
CString CMeasurementsAliasMappingSet::GetAlias(long lID)
{
	CString sFilter, sReturn;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CMeasurementsAliasMappingSet::GetAlias"))
	{
		if (!IsEOF())
			sReturn = m_sAlias;

		CloseRecordset("CMeasurementsAliasMappingSet::GetAlias");
	}

	return sReturn;
}

//Gabriel - BUG 5533 V2
long CMeasurementsAliasMappingSet::GetDecimals(long lID)
{
	long lReturn;
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CMeasurementsAliasMappingSet::GetDecimals"))
	{
		if (!IsEOF())
			lReturn = m_lDecimals;

		CloseRecordset("CMeasurementsAliasMappingSet::GetDecimals");
	}

	return lReturn;
}

//Gabriel - BUG 5533 V2
BOOL CMeasurementsAliasMappingSet::IsNumeric(long lID)
{
	BOOL bReturn = FALSE;
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CMeasurementsAliasMappingSet::GetDecimals"))
	{
		if (!IsEOF())
			bReturn = m_sValueType == "Numérico" ? TRUE : FALSE;

		CloseRecordset("CMeasurementsAliasMappingSet::GetDecimals");
	}

	return bReturn;
}