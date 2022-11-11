#include "stdafx.h"
#include "Endox.h"
#include "InsertLogAcquisizioneSPSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInsertLogAcquisizioneSPSet::CInsertLogAcquisizioneSPSet()
	: CRecordset(&theApp.m_dbEndox)
{
	m_lIDPaziente = 0;
	m_lIDEsame = 0;
	m_sUtente = "";
	m_sStazione = "";
	m_sOperazione = "";

	m_nParams = 5;
}

CInsertLogAcquisizioneSPSet::~CInsertLogAcquisizioneSPSet()
{
}

void CInsertLogAcquisizioneSPSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::inputParam);

	RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	RFX_Text(pFX, "Utente", m_sUtente, 50);
	RFX_Text(pFX, "Stazione", m_sStazione, 50);
	RFX_Text(pFX, "Operazione", m_sOperazione, 4000);
}

CString CInsertLogAcquisizioneSPSet::GetDefaultSQL()
{
	return "{CALL sp_InsertLogAcquisizione(?,?,?,?,?)}";
}

void CInsertLogAcquisizioneSPSet::Exec(long lIDPaziente, long lIDEsame, CString sUtente, CString sStazione, CString sOperazione)
{
	m_lIDPaziente = lIDPaziente;
	m_lIDEsame = lIDEsame;
	m_sUtente = sUtente;
	m_sStazione = sStazione;
	m_sOperazione = sOperazione;

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
