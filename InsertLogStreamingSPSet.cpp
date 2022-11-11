#include "stdafx.h"
#include "Endox.h"
#include "InsertLogStreamingSPSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInsertLogStreamingSPSet::CInsertLogStreamingSPSet()
	: CRecordset(&theApp.m_dbEndox)
{
	m_strUtente = "";
	m_strStazione = "";
	m_strStreamingDescrizione = "";
	m_strStreamingPazienteEsame = "";

	m_nParams = 4;
}

CInsertLogStreamingSPSet::~CInsertLogStreamingSPSet()
{
}

void CInsertLogStreamingSPSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::inputParam);

	RFX_Text(pFX, "Utente", m_strUtente, 50);
	RFX_Text(pFX, "Stazione", m_strStazione, 50);
	RFX_Text(pFX, "StreamingDescrizione", m_strStreamingDescrizione, 255);
	RFX_Text(pFX, "StreamingPazienteEsame", m_strStreamingPazienteEsame, 4000);
}

CString CInsertLogStreamingSPSet::GetDefaultSQL()
{
	return "{CALL sp_InsertLogStreaming(?,?,?,?)}";
}

void CInsertLogStreamingSPSet::Exec(CString strUtente, CString strStazione, CString strStreamingDescrizione, CString strStreamingPazienteEsame)
{
	m_strUtente = strUtente;
	m_strStazione = strStazione;
	m_strStreamingDescrizione = strStreamingDescrizione;
	m_strStreamingPazienteEsame = strStreamingPazienteEsame;

	try
	{
		Open(CRecordset::snapshot, NULL, CRecordset::readOnly);
	}
	catch(CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
	catch(CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
}
