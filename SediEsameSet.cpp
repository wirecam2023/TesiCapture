#include "stdafx.h"
#include "Endox.h"
#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSediEsameSet, CBaseSet)

CSediEsameSet::CSediEsameSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 8;
}

CString CSediEsameSet::GetDefaultSQL()
{
	return "SediEsame";
}

void CSediEsameSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "SiglaProgressivo", m_sSiglaProgressivo, 1);
		RFX_Text(pFX, "APSede", m_sAPSede, 255);
		RFX_Text(pFX, "DicomSede", m_sDicomSede, 255);
		RFX_Text(pFX, "CodicePresidioOspedaliero", m_sCodicePresidioOspedaliero, 50);
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CSediEsameSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sSiglaProgressivo = "";
	m_sAPSede = "";
	m_sDicomSede = "";
	m_sCodicePresidioOspedaliero = "";
	m_sCodice = "";
	m_bEliminato = FALSE;
}

CBaseSet* CSediEsameSet::CreateNew()
{
	return (CBaseSet*)new CSediEsameSet;
}

void CSediEsameSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CSediEsameSet* pSet = (CSediEsameSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSiglaProgressivo) || bCopyAll)
		m_sSiglaProgressivo = pSet->m_sSiglaProgressivo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sAPSede) || bCopyAll)
		m_sAPSede = pSet->m_sAPSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDicomSede) || bCopyAll)
		m_sDicomSede = pSet->m_sDicomSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodicePresidioOspedaliero) || bCopyAll)
		m_sCodicePresidioOspedaliero = pSet->m_sCodicePresidioOspedaliero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CSediEsameSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CSediEsameSet* pOV = (CSediEsameSet*)pOldValues;
	CSediEsameSet* pNV = (CSediEsameSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("SiglaProgressivo", pOV, &pOV->m_sSiglaProgressivo, pNV, &pNV->m_sSiglaProgressivo);
	sp.Execute("APSede", pOV, &pOV->m_sAPSede, pNV, &pNV->m_sAPSede);
	sp.Execute("DicomSede", pOV, &pOV->m_sDicomSede, pNV, &pNV->m_sDicomSede);
	sp.Execute("CodicePresidioOspedaliero", pOV, &pOV->m_sCodicePresidioOspedaliero, pNV, &pNV->m_sCodicePresidioOspedaliero);
	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

long CSediEsameSet::GetID(CString sDescrizione)
{
	long lReturn = 0;

	sDescrizione.MakeUpper();

	// Sandro 15/07/2013 //
	sDescrizione.Replace("'", "''");

	CString strFilter;
	strFilter.Format("UPPER(Descrizione)='%s'", sDescrizione);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CSediEsameSet::GetID"))
	{
		if (!IsEOF())
			lReturn = m_lID;

		CloseRecordset("CSediEsameSet::GetID");
	}

	return lReturn;
}

CString CSediEsameSet::GetDescrizione(long lID, BOOL bForQuery)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	CString sOldBaseFilter = SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	SetOpenFilter(strFilter);
	if (OpenRecordset("CSediEsameSet::GetDescrizione"))
	{
		if (!IsEOF())
		{
			strReturn = m_sDescrizione;
			strReturn.MakeUpper();

			// Sandro 15/07/2013 //
			if (bForQuery)
				strReturn.Replace("'", "''");
		}

		SetBaseFilter(sOldBaseFilter);
		CloseRecordset("CSediEsameSet::GetDescrizione");
	}

	return strReturn;
}

CString CSediEsameSet::GetSigla(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CSediEsameSet::GetSigla"))
	{
		if (!IsEOF())
		{
			strReturn = m_sSiglaProgressivo;
			strReturn.MakeUpper();
		}

		CloseRecordset("CSediEsameSet::GetSigla");
	}

	return strReturn;
}

CString CSediEsameSet::GetAPSede(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CSediEsameSet::GetAPSede"))
	{
		if (!IsEOF())
			strReturn = m_sAPSede;

		CloseRecordset("CSediEsameSet::GetAPSede");
	}

	return strReturn;
}

CString CSediEsameSet::GetCodicePresidio(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CSediEsameSet::GetCodicePresidio"))
	{
		if (!IsEOF())
			strReturn = m_sCodicePresidioOspedaliero;

		CloseRecordset("CSediEsameSet::GetCodicePresidio");
	}

	return strReturn;
}

BOOL CSediEsameSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CSediEsameSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CSediEsameSet::DeleteRecordset");
	}
	return bReturn;
}

CString CSediEsameSet::SetBaseFilter(const CString &strFilter)
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
		
void CSediEsameSet::VerificaSedeDefault()
{
	if (OpenRecordset("CSediEsameSet::VerificaSedeDefault"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CSediEsameSet::VerificaSedeDefault"))
			{
				m_sDescrizione = "DEFAULT";
				m_sSiglaProgressivo = "D";
				m_sAPSede = "DEFAULT";
				m_sDicomSede = "DEFAULT";
				m_sCodicePresidioOspedaliero = "";

				UpdateRecordset("CSediEsameSet::VerificaSedeDefault");
			}
		}

		CloseRecordset("CSediEsameSet::VerificaSedeDefault");
	}
}

CString CSediEsameSet::GetCodice(long lID)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CSediEsameSet::GetCodice"))
	{
		if (!IsEOF())
			strReturn = m_sCodice;

		CloseRecordset("CSediEsameSet::GetCodice");
	}

	return strReturn;
}