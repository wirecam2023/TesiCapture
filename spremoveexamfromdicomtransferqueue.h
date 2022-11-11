#pragma once

class CSPRemoveExamFromDicomTransferQueue : protected CRecordset
{
public:
	CSPRemoveExamFromDicomTransferQueue(CDatabase* pDatabase);
	long Exec(long lExamID);

protected:

	void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL() {return "{CALL sp_DicomRemoveExamFromQueue (?, ?)}";}
	void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE) {}

	LONG    m_examid;
	LONG    m_result;
};
