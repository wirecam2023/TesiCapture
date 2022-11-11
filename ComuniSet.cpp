#include "stdafx.h"
#include "Endox.h"
#include "ComuniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComuniSet, CBaseSet)

CComuniSet::CComuniSet()
	: CBaseSet(NULL, "VIEW") // faccio finta sia una vista //
{
	SetSortRecord("ID");

	SetEmpty();

	m_nFields = 6;
}

void CComuniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	RFX_Text(pFX, "Comune", m_sComune, 255);
	RFX_Text(pFX, "CAP", m_sCAP, 10);
	RFX_Text(pFX, "Provincia", m_sProvincia, 50);
	RFX_Text(pFX, "InizioValidita", m_sDataInizioValidita, 8);
	RFX_Text(pFX, "FineValidita", m_sDataFineValidita, 8);
}

CString CComuniSet::GetDefaultSQL()
{
	return "COMUNI";
}

void CComuniSet::SetEmpty()
{
	m_lID = 0;
	m_sComune = "";
	m_sCAP = "";
	m_sProvincia = "";
	m_sDataInizioValidita = "";
	m_sDataFineValidita = "";
}

void CComuniSet::GetFieldText(long lContatore, CString& strComune, CString& strCAP, CString& strProvincia)
{
	CString strFilter;
	strFilter.Format("ID=%li", lContatore);

	strComune = "";
	strCAP = "";
	strProvincia = "";

	SetOpenFilter(strFilter);
	SetSortRecord("ID");
	if (OpenRecordset("CComuniSet::GetFieldText"))
	{
		if (!IsEOF())
		{
			strComune = m_sComune;
			strCAP = m_sCAP;
			strProvincia = m_sProvincia;
		}

		CloseRecordset("CComuniSet::GetFieldText");
	}
}

CString CComuniSet::GetDataInizioValidita(long id)
{
	CString strFilter;
	strFilter.Format("ID=%li", id);

	CString strReturn = "";

	SetOpenFilter(strFilter);
	if (OpenRecordset("CComuniSet::GetDataInizioValidita"))
	{
		if (!IsEOF())
		{
			strReturn = m_sDataInizioValidita;
		}

		CloseRecordset("CComuniSet::GetDataInizioValidita");
	}

	return strReturn;
}

CString CComuniSet::GetDataFineValidita(long id)
{
	CString strFilter;
	strFilter.Format("ID=%li", id);

	CString strReturn = "";

	SetOpenFilter(strFilter);
	if (OpenRecordset("CComuniSet::GetDataInizioValidita"))
	{
		if (!IsEOF())
		{
			strReturn = m_sDataFineValidita;
		}

		CloseRecordset("CComuniSet::GetDataInizioValidita");
	}

	return strReturn;
}