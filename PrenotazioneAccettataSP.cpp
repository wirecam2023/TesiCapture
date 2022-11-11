#include "stdafx.h"
#include "Endox.h"
#include "PrenotazioneAccettataSP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPrenotazioneAccettataSP, CRecordset)

CPrenotazioneAccettataSP::CPrenotazioneAccettataSP()
	: CRecordset(&theApp.m_dbEndox)
{
	SetEmpty();
	m_nParams = 1;
}

void CPrenotazioneAccettataSP::DoFieldExchange(CFieldExchange* pFX)
{
	CRecordset::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::inputParam);

	RFX_Long(pFX,	"@IDPrenotazione", m_lIDPrenotazione);

	/*
	pFX->SetFieldType(CFieldExchange::outputParam);

	RFX_Long(pFX,	"@nRetValueOUT",	m_lReturnOUT);
	*/
}

void CPrenotazioneAccettataSP::SetEmpty()
{
	m_lIDPrenotazione = 0;
}

BOOL CPrenotazioneAccettataSP::Execute(long lIDPrenotazione)
{
	m_lIDPrenotazione = lIDPrenotazione;

	try
	{
		Open(CRecordset::snapshot, "{CALL sp_PrenotazioneAccettata(?)}", CRecordset::readOnly);
		Close();
	}
	catch(CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		return FALSE;
	}
	catch(CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		return FALSE;
	}

	return TRUE;
}