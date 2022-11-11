#include "stdafx.h"
#include "Endox.h"
#include "RecordAddSP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRecordAddSP, CRecordset)

CRecordAddSP::CRecordAddSP()
	: CRecordset(&theApp.m_dbEndox)
{
	SetEmpty();
	m_nParams = 3;
}

void CRecordAddSP::DoFieldExchange(CFieldExchange* pFX)
{
	CRecordset::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::inputParam);

	RFX_Text(pFX,	"@strTableNameIN",	m_sTableNameIN);
	RFX_Text(pFX,	"@strFieldNameIN",	m_sFieldNameIN);

	pFX->SetFieldType(CFieldExchange::outputParam);

	RFX_Long(pFX,	"@nNewRecordOUT",	m_lNewRecordOUT);
}

void CRecordAddSP::SetEmpty()
{
	m_sTableNameIN = "";
	m_sFieldNameIN = "";
	m_lNewRecordOUT = 0;
}

long CRecordAddSP::Execute(const CString &sTableNameIN, const CString &sFieldNameIN)
{
	m_sTableNameIN = sTableNameIN;
	m_sFieldNameIN = sFieldNameIN;
	m_lNewRecordOUT = 0;

	try
	{
		Open(CRecordset::snapshot, "{CALL sp_RecordAdd(?,?,?)}", CRecordset::readOnly);

		/*
		Il valore di ritorno viene messo in @nNewRecordOUT e significa:
			>0: tutto OK, il valore corrisponde al record appena aggiunto
			0: errore non identificato
			-1: MinIdRange<=0 o non definito nella tabella 'Configurazioni'
			-2: MaxIdRange<=MinIdRange o non definito nella tabella 'Configurazioni'
			-3: errore durante il recupero del nuovo numero record dalla tabella indicata (@strTableNameIN)
			-4: finito lo spazio nel proprio range di inserimento della tabella indicata (@strTableNameIN)
			-5: errore durante l'inserimento del record nella tabella indicata (@strTableNameIN)
			-6: errore durante l'inserimento dell'operazione nella tabella di log (tb_NewEdtDelOperations)
		*/

		Close();
	}
	catch(CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		m_lNewRecordOUT = 0;
	}
	catch(CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		m_lNewRecordOUT = 0;
	}

	switch(m_lNewRecordOUT)
	{
		case 0:
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RECORDADDSP_ERROR0));
			break;
		}
		case -1:
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RECORDADDSP_ERROR1));
			break;
		}
		case -2:
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RECORDADDSP_ERROR2));
			break;
		}
		case -3:
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_RECORDADDSP_ERROR3), m_sTableNameIN);
			theApp.AfxMessageBoxEndo(strError);
			break;
		}
		case -4:
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_RECORDADDSP_ERROR4), m_sTableNameIN);
			theApp.AfxMessageBoxEndo(strError);
			break;
		}
		case -5:
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_RECORDADDSP_ERROR5), m_sTableNameIN);
			theApp.AfxMessageBoxEndo(strError);
			break;
		}
		case -6:
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RECORDADDSP_ERROR6));
			break;
		}
	}

	return m_lNewRecordOUT;
}