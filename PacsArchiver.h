#pragma once

class CPacsArchiver
{
public:
	CPacsArchiver(void);
	~CPacsArchiver(void);

	void Archive(long lPatientID, long lExamID, long lPdfID);

protected:
	void SendToPacs();

private:
	class CSPInsertImgInDicomTransferQueue : protected CRecordset
	{
	public:
		CSPInsertImgInDicomTransferQueue(CDatabase* pDatabase);

		long Exec(long lImageID);

	protected:
		void DoFieldExchange(CFieldExchange* pFX);
		CString GetDefaultSQL() {return "{CALL sp_DicomAddImgToQueue (?, ?)}";}

		void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE) {}

		LONG    m_imageid;
		LONG    m_result;
	};

	class CSPInsertPdfInDicomTransferQueue : protected CRecordset
	{
	public:
		CSPInsertPdfInDicomTransferQueue(CDatabase* pDatabase);

		long Exec(long lPdfID);

	protected:
		void DoFieldExchange(CFieldExchange* pFX);
		CString GetDefaultSQL() {return "{CALL sp_DicomAddPdfToQueue (?, ?)}";}

		void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE) {}

		LONG    m_pdfid;
		LONG    m_result;
	};
};
