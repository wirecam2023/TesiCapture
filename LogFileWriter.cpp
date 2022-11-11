#include "stdafx.h"
#include "Endox.h"
#include "LogFileWriter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLogFileWriter CLogFileWriter::m_log;

CLogFileWriter::CLogFileWriter()
{
	 m_hLogFiles[0] = NULL;
	 m_hLogFiles[1] = NULL;
}

CLogFileWriter::~CLogFileWriter()
{
	if (m_hLogFiles[0] != NULL)
	{
		CloseHandle(m_hLogFiles[0]);
		m_hLogFiles[0] = NULL;
	}
	if (m_hLogFiles[1] != NULL)
	{
		CloseHandle(m_hLogFiles[1]);
		m_hLogFiles[1] = NULL;
	}
}

CLogFileWriter* CLogFileWriter::Get()
{
	return &CLogFileWriter::m_log;
}

BOOL CLogFileWriter::CloseLogFile(long lID)
{
	ASSERT((lID == 0) || (lID == 1));

	if (m_hLogFiles[lID] != NULL)
	{
		BOOL bResult = CloseHandle(m_hLogFiles[lID]);

		if (bResult == TRUE)
		{
			m_hLogFiles[lID] = NULL;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CLogFileWriter::CloseLogFile0()
{
	return CloseLogFile(0);
}

BOOL CLogFileWriter::CloseLogFile1()
{
	return CloseLogFile(1);
}

BOOL CLogFileWriter::OpenLogFile(long lID, const CString& strFileName)
{
	ASSERT((lID == 0) || (lID == 1));

	BOOL bReturn = FALSE;
	CTime tm = CTime::GetCurrentTime();

	CString strLogFileName = theApp.m_sDirProg + "\\" + strFileName;

	HANDLE hFile = CreateFile(strLogFileName,
							GENERIC_WRITE | GENERIC_READ,
							FILE_SHARE_WRITE | FILE_SHARE_READ,
							NULL,
							OPEN_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwFileSize = GetFileSize(hFile, NULL);

		m_hLogFiles[lID] = hFile;
		bReturn = TRUE;
	}

	return bReturn;
}

// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
BOOL CLogFileWriter::CreateLogFolderIfNotExists()
{
	CString logDir;
	logDir.Format("%s\\LOGCOMPLETO", theApp.m_sDirProg);
	
	try{
		BOOL bResp1 = CreateDirectory(logDir, NULL);
		BOOL bResp2 = ERROR_ALREADY_EXISTS == GetLastError();
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
BOOL CLogFileWriter::LogFolderExists() {
	CString logDir;
	logDir.Format("%s\\LOGCOMPLETO", theApp.m_sDirProg);

	DWORD attribs = ::GetFileAttributesA(logDir);
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	return (attribs & FILE_ATTRIBUTE_DIRECTORY);
}

BOOL CLogFileWriter::OpenLogFile0()
{
	CTime tm = CTime::GetCurrentTime();

	// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
	// if folder LOGCOMPLETO exists..... write log, otherwise do not log
	if (!LogFolderExists())
		return FALSE;

	// if (!CreateLogFolderIfNotExists())
	//	return FALSE;
	
	CString strFileName;
	strFileName.Format("LOGCOMPLETO\\%04d_%02d_%02d.log",
					tm.GetYear(), 
					tm.GetMonth(), 
					tm.GetDay());

	return OpenLogFile(0, strFileName);
}

BOOL CLogFileWriter::OpenLogFile1(const CString& strFileName)
{
	return OpenLogFile(1, strFileName);
}

BOOL CLogFileWriter::WriteFile(long lID, const CString& strLogLine)
{
	ASSERT((lID == 0) || (lID == 1));

	if (!m_hLogFiles[lID])
		return FALSE;

	//CTime tm = CTime::GetCurrentTime();
	SYSTEMTIME tm; GetLocalTime(&tm);

	CString strTime;
	if (lID == 0)
	{
		strTime.Format("%02d:%02d:%02d.%03d", 
						tm.wHour,
						tm.wMinute,
						tm.wSecond,
						tm.wMilliseconds);
	}
	else
	{
		strTime.Format("%04d/%02d/%02d %02d:%02d:%02d", 
						tm.wYear, 
						tm.wMonth, 
						tm.wDay,
						tm.wHour,
						tm.wMinute,
						tm.wSecond,
						tm.wMilliseconds);
	}
	
	CString sToWrite = strTime + " -> " + strLogLine + "\r\n";

	DWORD dwBytesToWrite = sToWrite.GetLength();
	DWORD dwBytesWritten = 0;

	::SetFilePointer(m_hLogFiles[lID], 0, NULL, FILE_END);
	BOOL bResult = ::WriteFile(m_hLogFiles[lID],
							   sToWrite,
							   dwBytesToWrite,
							   &dwBytesWritten,
							   NULL);

	return (bResult && (dwBytesToWrite == dwBytesWritten));
}

BOOL CLogFileWriter::WriteLogLine0(const CString& strLogLine)
{
	BOOL bReturn = FALSE;

	if (OpenLogFile0())
	{
		bReturn = WriteFile(0, strLogLine);
		CloseLogFile0();
	}

	return bReturn;
}

/* 
BOOL CLogFileWriter::WriteLogLine1(const CString& strLogLine)
{
	return WriteFile(1, strLogLine);
}
*/

BOOL CLogFileWriter::WriteLogLine_DB(long lID, DWORD dwMilliseconds, const CString& strSQL, const CString& strComment)
{
	ASSERT((lID == 0) || (lID == 1));

	// 1 - data, ora e numero operazione

	WriteFile(lID, strComment);

	// 2 - query //

	WriteFile(lID, "   " + strSQL);

	// 3 - tempo di esecuzione //

	CString str3;
	if (dwMilliseconds > (DWORD)theApp.m_lSaveCompleteLogThreshold)
		str3.Format("DB RESPONSE TIME: %li msec. !!!!!\r\n", dwMilliseconds);
	else
		str3.Format("DB RESPONSE TIME: %li msec.\r\n", dwMilliseconds);

	WriteFile(lID, str3);

	//

	return TRUE;
}

BOOL CLogFileWriter::WriteLogLine0_DB(DWORD dwMilliseconds, const CString& strSQL, const CString& strComment)
{
	BOOL bReturn = FALSE;

	if (OpenLogFile0())
	{
		bReturn = WriteLogLine_DB(0, dwMilliseconds, strSQL, strComment);
		CloseLogFile0();
	}

	return bReturn;
}

/* BOOL CLogFileWriter::WriteLogLine1_DB(DWORD dwMilliseconds, const CString& strSQL, const CString& strComment)
{
	return WriteLogLine_DB(1, dwMilliseconds, strSQL, strComment);
} */

BOOL CLogFileWriter::WriteLogLine_File(long lID, DWORD dwMilliseconds, const CString& strFile, const CString& strComment)
{
	ASSERT((lID == 0) || (lID == 1));

	// 1 - data, ora e numero operazione

	WriteFile(lID, strComment);

	// 2 - query //

	CFileStatus filestatus;
	CFile::GetStatus(strFile, filestatus);

	double lfMBytesFile = (double)(filestatus.m_size) / (double)(1024*1024);

	CString str2;
	str2.Format("%.2lf Mb", lfMBytesFile);

	WriteFile(lID, "   " + str2 + " - " + strFile);

	// 3 - tempo di esecuzione //

	CString str3;
	if (dwMilliseconds > (DWORD)theApp.m_lSaveCompleteLogThreshold)
		str3.Format("FILE RETRIEVE TIME: %li msec. !!!!!\r\n", dwMilliseconds);
	else
		str3.Format("FILE RETRIEVE TIME: %li msec.\r\n", dwMilliseconds);

	WriteFile(lID, str3);

	//

	return TRUE;
}

BOOL CLogFileWriter::WriteLogLine0_File(DWORD dwMilliseconds, const CString& strFile, const CString& strComment)
{
	BOOL bReturn = FALSE;

	if (OpenLogFile0())
	{
		bReturn = WriteLogLine_File(0, dwMilliseconds, strFile, strComment);
		CloseLogFile0();
	}

	return bReturn;
}

/* BOOL CLogFileWriter::WriteLogLine1_File(DWORD dwMilliseconds, const CString& strFile, const CString& strComment)
{
	return WriteLogLine_File(1, dwMilliseconds, strFile, strComment);
} */

BOOL CLogFileWriter::WriteLogLine_ImmRetrieve(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lImagesCount, const CString& strComment)
{
	ASSERT((lID == 0) || (lID == 1));

	// 1 - data, ora e numero operazione

	WriteFile(lID, strComment);

	// 2 - query //

	CString str2;
	str2.Format("caricamento %02li immagini/filmati paziente %08li esame %08li", lImagesCount, lIDPaziente, lIDEsame);

	WriteFile(lID, "   " + str2);

	// 3 - tempo di esecuzione //

	CString str3;
	if (dwMilliseconds > (DWORD)(theApp.m_lSaveCompleteLogThreshold * lImagesCount))
		str3.Format("IMM RETRIEVE TIME: %li msec. !!!!!\r\n", dwMilliseconds);
	else
		str3.Format("IMM RETRIEVE TIME: %li msec.\r\n", dwMilliseconds);

	WriteFile(lID, str3);

	//

	return TRUE;
}

BOOL CLogFileWriter::WriteLogLine0_ImmRetrieve(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lImagesCount, const CString& strComment)
{
	BOOL bReturn = FALSE;

	if (lImagesCount > 0)
	{
		if (OpenLogFile0())
		{
			bReturn = WriteLogLine_ImmRetrieve(0, dwMilliseconds, lIDPaziente, lIDEsame, lImagesCount, strComment);
			CloseLogFile0();
		}
	}

	return bReturn;
}

BOOL CLogFileWriter::WriteLogLine_ImmStore(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lImagesCount, const CString& strComment)
{
	ASSERT((lID == 0) || (lID == 1));

	// 1 - data, ora e numero operazione

	WriteFile(lID, strComment);

	// 2 - query //

	CString str2;
	str2.Format("salvataggio %02li immagini paziente %08li esame %08li", lImagesCount, lIDPaziente, lIDEsame);

	WriteFile(lID, "   " + str2);

	// 3 - tempo di esecuzione //

	CString str3;
	if (dwMilliseconds > (DWORD)(theApp.m_lSaveCompleteLogThreshold * lImagesCount))
		str3.Format("IMM STORE TIME: %li msec. !!!!!\r\n", dwMilliseconds);
	else
		str3.Format("IMM STORE TIME: %li msec.\r\n", dwMilliseconds);

	WriteFile(lID, str3);

	//

	return TRUE;
}

BOOL CLogFileWriter::WriteLogLine0_ImmStore(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lImagesCount, const CString& strComment)
{
	BOOL bReturn = FALSE;

	if (lImagesCount > 0)
	{
		if (OpenLogFile0())
		{
			bReturn = WriteLogLine_ImmStore(0, dwMilliseconds, lIDPaziente, lIDEsame, lImagesCount, strComment);
			CloseLogFile0();
		}
	}

	return bReturn;
}

BOOL CLogFileWriter::WriteLogLine_PdfRetrieve(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lPdfsCount, const CString& strComment)
{
	ASSERT((lID == 0) || (lID == 1));

	// 1 - data, ora e numero operazione

	WriteFile(lID, strComment);

	// 2 - query //

	CString str2;
	str2.Format("caricamento %02li PDF paziente %08li esame %08li", lPdfsCount, lIDPaziente, lIDEsame);

	WriteFile(lID, "   " + str2);

	// 3 - tempo di esecuzione //

	CString str3;
	if (dwMilliseconds > (DWORD)(theApp.m_lSaveCompleteLogThreshold * lPdfsCount))
		str3.Format("PDF RETRIEVE TIME: %li msec. !!!!!\r\n", dwMilliseconds);
	else
		str3.Format("PDF RETRIEVE TIME: %li msec.\r\n", dwMilliseconds);

	WriteFile(lID, str3);

	//

	return TRUE;
}

BOOL CLogFileWriter::WriteLogLine0_PdfRetrieve(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lPdfsCount, const CString& strComment)
{
	BOOL bReturn = FALSE;

	if (lPdfsCount > 0)
	{
		if (OpenLogFile0())
		{
			bReturn = WriteLogLine_PdfRetrieve(0, dwMilliseconds, lIDPaziente, lIDEsame, lPdfsCount, strComment);
			CloseLogFile0();
		}
	}

	return bReturn;
}

BOOL CLogFileWriter::WriteLogLine_PdfStore(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lPdfsCount, const CString& strComment)
{
	ASSERT((lID == 0) || (lID == 1));

	// 1 - data, ora e numero operazione

	WriteFile(lID, strComment);

	// 2 - query //

	CString str2;
	str2.Format("salvataggio %02li PDF paziente %08li esame %08li", lPdfsCount, lIDPaziente, lIDEsame);

	WriteFile(lID, "   " + str2);

	// 3 - tempo di esecuzione //

	CString str3;
	if (dwMilliseconds > (DWORD)(theApp.m_lSaveCompleteLogThreshold * lPdfsCount))
		str3.Format("PDF STORE TIME: %li msec. !!!!!\r\n", dwMilliseconds);
	else
		str3.Format("PDF STORE TIME: %li msec.\r\n", dwMilliseconds);

	WriteFile(lID, str3);

	//

	return TRUE;
}

BOOL CLogFileWriter::WriteLogLine0_PdfStore(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lPdfsCount, const CString& strComment)
{
	BOOL bReturn = FALSE;

	if (lPdfsCount > 0)
	{
		if (OpenLogFile0())
		{
			bReturn = WriteLogLine_PdfStore(0, dwMilliseconds, lIDPaziente, lIDEsame, lPdfsCount, strComment);
			CloseLogFile0();
		}
	}

	return bReturn;
}

BOOL CLogFileWriter::WriteLogLine_DocRetrieve(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lDocsCount, const CString& strComment)
{
	ASSERT((lID == 0) || (lID == 1));

	// 1 - data, ora e numero operazione

	WriteFile(lID, strComment);

	// 2 - query //

	CString str2;
	str2.Format("caricamento %02li allegati paziente %08li esame %08li", lDocsCount, lIDPaziente, lIDEsame);

	WriteFile(lID, "   " + str2);

	// 3 - tempo di esecuzione //

	CString str3;
	if (dwMilliseconds > (DWORD)(theApp.m_lSaveCompleteLogThreshold * lDocsCount))
		str3.Format("DOC RETRIEVE TIME: %li msec. !!!!!\r\n", dwMilliseconds);
	else
		str3.Format("DOC RETRIEVE TIME: %li msec.\r\n", dwMilliseconds);

	WriteFile(lID, str3);

	//

	return TRUE;
}

BOOL CLogFileWriter::WriteLogLine0_DocRetrieve(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lDocsCount, const CString& strComment)
{
	BOOL bReturn = FALSE;

	if (lDocsCount > 0)
	{
		if (OpenLogFile0())
		{
			bReturn = WriteLogLine_DocRetrieve(0, dwMilliseconds, lIDPaziente, lIDEsame, lDocsCount, strComment);
			CloseLogFile0();
		}
	}

	return bReturn;
}

BOOL CLogFileWriter::WriteLogLine_DocStore(long lID, DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lDocsCount, const CString& strComment)
{
	ASSERT((lID == 0) || (lID == 1));

	// 1 - data, ora e numero operazione

	WriteFile(lID, strComment);

	// 2 - query //

	CString str2;
	str2.Format("salvataggio %02li allegati paziente %08li esame %08li", lDocsCount, lIDPaziente, lIDEsame);

	WriteFile(lID, "   " + str2);

	// 3 - tempo di esecuzione //

	CString str3;
	if (dwMilliseconds > (DWORD)(theApp.m_lSaveCompleteLogThreshold * lDocsCount))
		str3.Format("DOC STORE TIME: %li msec. !!!!!\r\n", dwMilliseconds);
	else
		str3.Format("DOC STORE TIME: %li msec.\r\n", dwMilliseconds);

	WriteFile(lID, str3);

	//

	return TRUE;
}

BOOL CLogFileWriter::WriteLogLine0_DocStore(DWORD dwMilliseconds, long lIDPaziente, long lIDEsame, long lDocsCount, const CString& strComment)
{
	BOOL bReturn = FALSE;

	if (lDocsCount > 0)
	{
		if (OpenLogFile0())
		{
			bReturn = WriteLogLine_DocStore(0, dwMilliseconds, lIDPaziente, lIDEsame, lDocsCount, strComment);
			CloseLogFile0();
		}
	}

	return bReturn;
}

void CLogFileWriter::WriteLogLine0_Ping(const CString& strIpToPing)
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	// creo il pipe di output //
	HANDLE hChildStdoutRd, hChildStdoutWr;
	if (CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &sa, 10000000))
	{
		// creo il processo

		PROCESS_INFORMATION pi;
		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags    = STARTF_USESTDHANDLES;
		si.hStdInput  = NULL;
		si.hStdOutput = hChildStdoutWr;
		si.hStdError  = NULL;

		char szProcess[1024];
		sprintf_s(szProcess, "ping.exe -n 1 -l 2048 %s", strIpToPing);

		if (CreateProcess(NULL, szProcess, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
		{
			WaitForSingleObject(pi.hProcess, INFINITE);

			DWORD dwExitCode = 0;
			if (GetExitCodeProcess(pi.hProcess, &dwExitCode) && dwExitCode == 0)
			{
				DWORD dwTotalBytes = 0, dwReaded;
				if (PeekNamedPipe(hChildStdoutRd, NULL, 0, NULL, &dwTotalBytes, NULL) && dwTotalBytes > 0)
				{
					DWORD iBufferLength = 1024*1024;
				
					if (dwTotalBytes <= iBufferLength)
					{
						BYTE* pBufferTemp = new BYTE[iBufferLength];
						ZeroMemory(pBufferTemp, sizeof(BYTE)*iBufferLength);
						if (::ReadFile(hChildStdoutRd, pBufferTemp, dwTotalBytes, &dwReaded, NULL))
						{
							CString sResult(pBufferTemp);
							sResult.Replace('\r', ' ');
							sResult.Replace('\n', ' ');
							sResult.Trim();
							while(sResult.Find("  ") > 0)
								sResult.Replace("  ", " ");

							CLogFileWriter::Get()->WriteLogLine0(sResult + "\r\n");
						}
						delete pBufferTemp;
					}
				}
			}
		}
	}
}

/*
BOOL CLogFileWriter::Write(LPCTSTR szLog, ...)
{
	DWORD dwBufferLength = strlen(szLog) * 2 + 1024*1024;
	TCHAR* szLoglineComplete = new TCHAR[dwBufferLength];
	TCHAR* szLogline = new TCHAR[dwBufferLength];

    va_list argptr;
    va_start(argptr, szLog);
	_vsnprintf_s(szLogline, dwBufferLength, dwBufferLength, szLog, argptr);
    va_end(argptr);

	if (strlen(szLogline) > 0)
	{
		if (szLogline[strlen(szLogline) - 1] == '\n')
			szLogline[strlen(szLogline) - 1] = 0;
	}

	strcat_s(szLogline, dwBufferLength, "\r\n");
	OutputDebugString(szLogline);

	if (!m_hLogFile)
	{
		delete szLoglineComplete;
		delete szLogline;
		return FALSE;
	}

	SYSTEMTIME st;
	::GetSystemTime(&st);

	sprintf_s(szLoglineComplete, 
		    dwBufferLength,
	        "%04d/%02d/%02d %02d:%02d.%02d -> ", 
			st.wYear, 
			st.wMonth, 
			st.wDay,
			st.wHour,
			st.wMinute,
			st.wSecond);
	strcat_s(szLoglineComplete, dwBufferLength, szLogline);

	static OVERLAPPED o;
	o.Offset = 0xFFFFFFFF;
	o.OffsetHigh = 0xFFFFFFFF;

	::SetFilePointer(m_hLogFile, 0, NULL, FILE_END);
	BOOL bResult = ::WriteFileEx(m_hLogFile,
								 szLoglineComplete,
								 (DWORD)strlen(szLoglineComplete),
								 &o,
								 WriteCompletionRoutine);
	delete szLoglineComplete;
	delete szLogline;
	return bResult;
}
*/
