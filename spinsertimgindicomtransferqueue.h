#pragma once

class CSPInsertImgInDicomTransferQueue : protected CRecordset
{
public:
	CSPInsertImgInDicomTransferQueue(CDatabase* pDatabase);
	long Exec(long lExamID);

protected:

	void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL() {return "{CALL sp_DicomAddImgToQueue (?, ?)}";}
	void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE) {}

	LONG    m_imageid;
	LONG    m_result;
};
