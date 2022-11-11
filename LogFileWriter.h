#pragma once

class CLogFileWriter  
{

public:

	static CLogFileWriter* Get();
	
	// chiude il file di log //
	BOOL CloseLogFile1();

	// apre il file di log //
	BOOL OpenLogFile1(const CString& strFileName);

	// aggiunge una stringa "generica" nel file di log //
	BOOL WriteLogLine0(const CString& strLogLine);

	// aggiunge nel log una stringa relativa ad una query //
	BOOL WriteLogLine0_DB(DWORD dwMilliseconds, const CString& strSQL, const CString& strComment);

	// aggiunge nel log una stringa relativa all'apertura di un file //
	BOOL WriteLogLine0_File(DWORD dwMilliseconds, const CString& strFile, const CString& strComment);

	// aggiunge nel log una stringa relativa al retrieve delle immagini //
	BOOL WriteLogLine0_ImmRetrieve(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lImagesCount, const CString& strComment);

	// aggiunge nel log una stringa relativa al salvataggio delle immagini //
	BOOL WriteLogLine0_ImmStore(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lImagesCount, const CString& strComment);

	// aggiunge nel log una stringa relativa al retrieve dei PDF //
	BOOL WriteLogLine0_PdfRetrieve(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lPdfsCount, const CString& strComment);

	// aggiunge nel log una stringa relativa al salvataggio dei PDF //
	BOOL WriteLogLine0_PdfStore(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lPdfsCount, const CString& strComment);

	// aggiunge nel log una stringa relativa al retrieve degli allegati //
	BOOL WriteLogLine0_DocRetrieve(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lDocsCount, const CString& strComment);

	// aggiunge nel log una stringa relativa al salvataggio degli allegati //
	BOOL WriteLogLine0_DocStore(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lDocsCount, const CString& strComment);

	// aggiunge nel log una stringa relativa al ping dei server //
	void WriteLogLine0_Ping(const CString& strIpToPing);

	//
	// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
	BOOL CreateLogFolderIfNotExists();
	BOOL LogFolderExists();

private:

	CLogFileWriter();
	virtual ~CLogFileWriter();

	//

	BOOL CloseLogFile0();
	BOOL OpenLogFile0();

	BOOL CloseLogFile(long lID);
	BOOL OpenLogFile(long lID, const CString& strFileName);
	BOOL WriteFile(long lID, const CString& strLogLine);
	BOOL WriteLogLine_DB(long lID, DWORD dwMilliseconds, const CString& strSQL, const CString& strComment);
	BOOL WriteLogLine_File(long lID, DWORD dwMilliseconds, const CString& strFile, const CString& strComment);
	BOOL WriteLogLine_ImmRetrieve(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lImagesCount, const CString& strComment);
	BOOL WriteLogLine_ImmStore(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lImagesCount, const CString& strComment);
	BOOL WriteLogLine_PdfRetrieve(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lPdfsCount, const CString& strComment);
	BOOL WriteLogLine_PdfStore(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lPdfsCount, const CString& strComment);
	BOOL WriteLogLine_DocRetrieve(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lDocsCount, const CString& strComment);
	BOOL WriteLogLine_DocStore(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lDocsCount, const CString& strComment);

	//

	static CLogFileWriter m_log;
	HANDLE m_hLogFiles[2];

};