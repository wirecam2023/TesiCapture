#pragma once

class CSPInsertRemainingImgInDicomTransferQueue : protected CRecordset
{
public:
	CSPInsertRemainingImgInDicomTransferQueue(CDatabase* pDatabase);
	long Exec(long lExamID);

protected:

	void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL() {return "{CALL sp_DicomAddRemainingImgToQueue (?, ?)}";}
	void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE) {}

	LONG    m_examid;
	LONG    m_result;
};
