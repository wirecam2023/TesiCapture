#include "stdafx.h"
#include "Endox.h"
#include "spinsertexamindicomtransferqueue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSPInsertExamInDicomTransferQueue::CSPInsertExamInDicomTransferQueue(CDatabase* pDatabase) : CRecordset(pDatabase)
{
	m_examid = 0;
	m_result = 0;
	// 
	m_nFields = 0;
	m_nParams = 2;
}

void CSPInsertExamInDicomTransferQueue::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputParam);
	RFX_Long(pFX, "@RESULT", m_result);
	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Long(pFX, "@EXAMID", m_examid);	
}

long CSPInsertExamInDicomTransferQueue::Exec(long lExamID)
{
	m_examid = lExamID;

	try
	{
		Open(CRecordset::snapshot, NULL, CRecordset::readOnly);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		m_result = -1;
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		m_result = -1;
	}

	if (IsOpen())
		Close();

	return m_result;
}