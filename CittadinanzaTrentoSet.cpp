#include "stdafx.h"
#include "Endox.h"
#include "CittadinanzaTrentoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCittadinanzaTrentoSet, CBaseSet)

CCittadinanzaTrentoSet::CCittadinanzaTrentoSet()
	: CBaseSet(NULL, "") // non è una tabella nostra //
{
	SetEmpty();

	m_nFields = 8;
}

void CCittadinanzaTrentoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "UE", m_sUE, 255);
	RFX_Text(pFX, "CONVENZIONE", m_sCONVENZIONE, 255);
	RFX_Text(pFX, "STP", m_sSTP, 255);
	RFX_Long(pFX, "COD_VER", m_lCOD_VER);
	RFX_Text(pFX, "COD_CITTADINANZA", m_sCOD_CITTADINANZA, 50);
	RFX_Text(pFX, "CITTADINANZA", m_sCITTADINANZA, 255);
	RFX_Text(pFX, "NOTE", m_sNOTE, 255);
	RFX_Text(pFX, "NAZIONE", m_sNAZIONE, 255);
}

void CCittadinanzaTrentoSet::SetEmpty()
{
	m_sUE = "";
	m_sCONVENZIONE = "";
	m_sSTP = "";
	m_lCOD_VER = 0;
	m_sCOD_CITTADINANZA = "";
	m_sCITTADINANZA = "";
	m_sNOTE = "";
	m_sNAZIONE = "";
}

CString CCittadinanzaTrentoSet::GetDefaultSQL()
{
	return "TD_CITTADINANZA";
}

CString CCittadinanzaTrentoSet::GetCittadinanza(CString strCodCittadinanza)
{
	CString strReturn = "";

	if ((strCodCittadinanza.GetLength() > 0) && (strCodCittadinanza != " "))
	{
		SetOpenFilter("COD_CITTADINANZA='" + strCodCittadinanza + "'");
		if (OpenRecordset("CCittadinanzaTrentoSet::GetCittadinanza"))
		{
			if (!IsEOF())
				strReturn = m_sCITTADINANZA;

			CloseRecordset("CCittadinanzaTrentoSet::GetCittadinanza");
		}
	}

	return strReturn;
}

CString CCittadinanzaTrentoSet::GetCodCittadinanza(CString strCittadinanza)
{
	CString strReturn = "";

	strCittadinanza.TrimLeft();
	strCittadinanza.TrimRight();
	strCittadinanza.Replace("'", "''");

	if (strCittadinanza.GetLength() > 0)
	{
		SetOpenFilter("CITTADINANZA='" + strCittadinanza + "'");
		if (OpenRecordset("CCittadinanzaTrentoSet::GetCodCittadinanza"))
		{
			if (!IsEOF())
				strReturn = m_sCOD_CITTADINANZA;

			CloseRecordset("CCittadinanzaTrentoSet::GetCodCittadinanza");
		}
	}

	return strReturn;
}