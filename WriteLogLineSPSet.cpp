#include "stdafx.h"
#include "Endox.h"
#include "WriteLogLineSPSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWriteLogLineSPSet::CWriteLogLineSPSet()
	: CRecordset(&theApp.m_dbEndox)
{
	m_lIDPaziente = 0;
	m_lIDEsame = 0;
	m_sImpianto = "";
	m_sUtente = "";
	m_sStazione = "";
	m_sTabella = "";
	m_lOperazione = 0;
	m_sNomeChiave = "";
	m_lValoreChiave = 0;
	m_sCampo = "";
	m_sValoreOld = "";
	m_sValoreNew = "";
	m_sCommento = "";

	m_nParams = 13;
}

CWriteLogLineSPSet::~CWriteLogLineSPSet()
{
}

void CWriteLogLineSPSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::inputParam);

	RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	RFX_Text(pFX, "Impianto", m_sImpianto, 50);
	RFX_Text(pFX, "Utente", m_sUtente, 50);
	RFX_Text(pFX, "Stazione", m_sStazione, 50);
	RFX_Text(pFX, "Tabella", m_sTabella, 50);
	RFX_Long(pFX, "Operazione", m_lOperazione);
	RFX_Text(pFX, "NomeChiave", m_sNomeChiave, 50);
	RFX_Long(pFX, "ValoreChiave", m_lValoreChiave);
	RFX_Text(pFX, "Campo", m_sCampo, 50);
	RFX_Text(pFX, "ValoreOld", m_sValoreOld, 4000);
	RFX_Text(pFX, "ValoreNew", m_sValoreNew, 4000);
	RFX_Text(pFX, "Commento", m_sCommento, 255);
}

CString CWriteLogLineSPSet::GetDefaultSQL()
{
	return "{CALL sp_InsertLog(?,?,?,?,?,?,?,?,?,?,?,?,?)}";
}

void CWriteLogLineSPSet::Exec(const long lIDPaziente, const long lIDEsame, const CString &sUtente, const CString &sStazione, const CString &sImpianto, const CString &sTabella, long lOperazione, const CString &sNomeChiave, long lValoreChiave, const CString &sCampo, const CString &sValoreOld, const CString &sValoreNew, const CString &sCommento)
{
	m_lIDPaziente = lIDPaziente;    
	m_lIDEsame = lIDEsame;       
	m_sUtente = sUtente;    
	m_sStazione = sStazione;  
	m_sImpianto = sImpianto;  
	m_sTabella = sTabella;   
	m_lOperazione = lOperazione;  
	m_sNomeChiave = sNomeChiave;
	m_lValoreChiave = lValoreChiave;  
	m_sCampo = sCampo;     
	m_sValoreOld = sValoreOld; 
	m_sValoreNew = sValoreNew; 
	m_sCommento = sCommento;

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
