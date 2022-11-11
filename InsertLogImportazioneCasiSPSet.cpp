#include "stdafx.h"
#include "Endox.h"
#include "InsertLogImportazioneCasiSPSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInsertLogImportazioneCasiSPSet::CInsertLogImportazioneCasiSPSet()
	: CRecordset(&theApp.m_dbEndox)
{
	m_lIDPaziente = 0;
	m_lIDEsameOrigine = 0;
	m_lIDEsameDestinazione = 0;
	m_sUtente = "";
	m_sStazione = "";

	m_nParams = 5;
}

CInsertLogImportazioneCasiSPSet::~CInsertLogImportazioneCasiSPSet()
{
}

void CInsertLogImportazioneCasiSPSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::inputParam);

	RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
	RFX_Long(pFX, "IDEsameOrigine", m_lIDEsameOrigine);
	RFX_Long(pFX, "IDEsameDestinazione", m_lIDEsameDestinazione);
	RFX_Text(pFX, "Utente", m_sUtente, 50);
	RFX_Text(pFX, "Stazione", m_sStazione, 50);
}

CString CInsertLogImportazioneCasiSPSet::GetDefaultSQL()
{
	return "{CALL sp_InsertLogImportazioneCasi(?,?,?,?,?)}";
}

void CInsertLogImportazioneCasiSPSet::Exec(long lIDPaziente, long lIDEsameOrigine, long lIDEsameDestinazione, CString sUtente, CString sStazione)
{
	m_lIDPaziente = lIDPaziente;
	m_lIDEsameOrigine = lIDEsameOrigine;
	m_lIDEsameDestinazione = lIDEsameDestinazione;
	m_sUtente = sUtente;
	m_sStazione = sStazione;

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
