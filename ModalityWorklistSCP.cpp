#include "stdafx.h"
#include "Endox.h"
#include "ModalityWorklistSCP.h"
#include <io.h>
#include <psapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModalityWorklistSCP CModalityWorklistSCP::m_obj;

CModalityWorklistSCP::CModalityWorklistSCP(void)
{
	ZeroMemory(m_szAET, 1024 * sizeof(TCHAR));
	m_iPort = 0;
	m_bEnableLog = FALSE;
	m_hLogFile = NULL;
	m_hProcess = NULL;

	m_bStarted = FALSE;

	InitializeCriticalSection(&m_cs);
}

CModalityWorklistSCP::~CModalityWorklistSCP(void)
{
	DeleteCriticalSection(&m_cs);
}

BOOL CModalityWorklistSCP::Start(LPCTSTR szAET, UINT iPort, BOOL bEnableLog)
{
	strcpy_s(m_szAET, szAET);
	m_iPort = iPort;
	m_bEnableLog = bEnableLog;

	if (strlen(m_szAET) == 0)
		return FALSE;

	if (m_iPort >= 65536)
		return FALSE;

	TCHAR szApplicationDir[MAX_PATH];
	GetApplicationDir(szApplicationDir, MAX_PATH);
	strcat_s(szApplicationDir, "\\ModalityWorklistSCP");

	if (_access(szApplicationDir, 00) != 0)
		return FALSE;

	TCHAR szApplicationExe[MAX_PATH];
	strcpy_s(szApplicationExe, szApplicationDir);
	strcat_s(szApplicationExe, "\\wlmscpfs.exe");
	if (_access(szApplicationExe, 00) != 0)
		return FALSE;

	TCHAR szApplicationSubdirAE[MAX_PATH];
	strcpy_s(szApplicationSubdirAE, szApplicationDir);
	strcat_s(szApplicationSubdirAE, "\\");
	strcat_s(szApplicationSubdirAE, szAET);
	_strupr_s(szApplicationSubdirAE);
	if (_access(szApplicationSubdirAE, 00) != 0)
	{
		if (!CreateDirectory(szApplicationSubdirAE, NULL))
			return FALSE;
	}

	TCHAR szLockFile[MAX_PATH];
	strcpy_s(szLockFile, szApplicationSubdirAE);
	strcat_s(szLockFile, "\\lockfile");
	HANDLE hFile = ::CreateFile(szLockFile,
                                FILE_WRITE_DATA,
								FILE_SHARE_WRITE,
								NULL,
								CREATE_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	CloseHandle(hFile);

	// Creo file di test per verificare permessi lettura scrittura utente attuale
	TCHAR szTestFile[MAX_PATH];
	strcpy_s(szTestFile, szApplicationSubdirAE);
	strcat_s(szTestFile, "\\test");
	hFile = ::CreateFile(szTestFile,
                         FILE_WRITE_DATA,
						 FILE_SHARE_WRITE,
						 NULL,
						 CREATE_ALWAYS,
						 FILE_ATTRIBUTE_NORMAL,
						 NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	CloseHandle(hFile);

	if (!DeleteFile(szTestFile))
		return FALSE;

	if (m_bEnableLog)
	{
		TCHAR szLogFileName[MAX_PATH];
		sprintf_s(szLogFileName,
			      "%s\\wlmscpfs.log",
				  szApplicationDir);

		m_hLogFile = CreateFile(szLogFileName,
								GENERIC_WRITE | GENERIC_READ,
								FILE_SHARE_WRITE | FILE_SHARE_READ,
								NULL,
								CREATE_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	}

	KillProcess("wlmscpfs.exe");

	DWORD dwThreadId;
	HANDLE hThread = ::CreateThread(NULL, 
		                            0, 
									ThreadWorklistSCP, 
									(LPVOID)this, 
									0, 
									&dwThreadId);
	CloseHandle(hThread);

	Clear();
	m_bStarted = TRUE;
	return m_bStarted;
}

void CModalityWorklistSCP::Stop()
{
	if (m_hProcess != NULL)
		TerminateProcess(m_hProcess, 0);

	// wait thread finish...
	EnterCriticalSection(&m_cs);
	LeaveCriticalSection(&m_cs);

	if (m_hLogFile != INVALID_HANDLE_VALUE)
		CloseHandle(m_hLogFile);

	Clear();
	m_bStarted = FALSE;
}

void CModalityWorklistSCP::Clear()
{
	if (!m_bStarted)
		return;

	TCHAR szWorklistDump[MAX_PATH];
	GetWorklistDumpFile(szWorklistDump, MAX_PATH);
	if (_access(szWorklistDump, 00) == 0)
	{
		if (!DeleteFile(szWorklistDump))
		{
			//theApp.EcoMessageBox("", MB_ICONSTOP);
		}
	}

	TCHAR szWorklistDcm[MAX_PATH];
	GetWorklistDcmFile(szWorklistDcm, MAX_PATH);
	if (_access(szWorklistDcm, 00) == 0)
	{
		if (!DeleteFile(szWorklistDcm))
		{
			//theApp.EcoMessageBox("", MB_ICONSTOP);
		}
	}
}

BOOL CModalityWorklistSCP::SetPatient(LPCTSTR szPatientID,
		                              LPCTSTR szPatientFirstname,
					                  LPCTSTR szPatientLastname,
					                  TCHAR (&szPatientBirthDate)[9],
					                  TCHAR (&szPatientSex)[2],
									  UINT iExamType,
					                  LPCTSTR szExamDescription,
					                  TCHAR (&szExamDate)[15],
					                  LPCTSTR szAccessionNumber,
					                  LPCTSTR szPatientAltezza,
					                  LPCTSTR szPatientPeso,
									  LPCTSTR szPhysician,
									  LPCTSTR szPrestazioneDescription,
									  LPCTSTR szRequestingPhysician)
{
	if (!m_bStarted)
		return FALSE;

	Clear();

	TCHAR szWorklistDump[MAX_PATH];
	GetWorklistDumpFile(szWorklistDump, MAX_PATH);

	TCHAR szWorklistDcm[MAX_PATH];
	GetWorklistDcmFile(szWorklistDcm, MAX_PATH);

	HANDLE hFile = ::CreateFile(szWorklistDump,
		                        FILE_WRITE_DATA,
								FILE_SHARE_WRITE,
								NULL,
								CREATE_ALWAYS,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	TCHAR szComputerName[MAX_PATH];
	DWORD dwComputerNameLength = MAX_PATH;
	GetComputerName(szComputerName, &dwComputerNameLength);

	TCHAR szExamDateCopy[15];
	strcpy_s(szExamDateCopy, szExamDate);
	szExamDateCopy[8] = 0;

	TCHAR szName[MAX_PATH];
	strcpy_s(szName, szPatientFirstname);
	strcat_s(szName, "^");
	strcat_s(szName, szPatientLastname);

	TCHAR szStudyUID[MAX_PATH];
	strcpy_s(szStudyUID, "1.2.826.0.1.3680043.2.511.");
	strcat_s(szStudyUID, szAccessionNumber);

	TCHAR szExamType[MAX_PATH];
	sprintf_s(szExamType, "%li", iExamType);

	AddToDumpFile(hFile, "0008", "0005", "CS", "[ISO_IR 100]");        // [ISO_IR 100]                      specific character set
	AddToDumpFile(hFile, "0008", "0050", "SH", szAccessionNumber);     // 345345                            accession number
	AddToDumpFile(hFile, "0010", "0010", "PN", szName);                // VIVALDI^ANTONIO                   patient name
	AddToDumpFile(hFile, "0010", "0020", "LO", szPatientID);           // AV35674                           patient id
	AddToDumpFile(hFile, "0010", "0030", "DA", szPatientBirthDate);    // 16780304                          patient's birth date
	AddToDumpFile(hFile, "0010", "0040", "CS", szPatientSex);          // M                                 patient's sex

	// Sandro 07/10/2016 //
	AddToDumpFile(hFile, "0010", "1020", "DS", szPatientAltezza);      // altezza
	AddToDumpFile(hFile, "0010", "1030", "DS", szPatientPeso);         // peso

	//AddToDumpFile(hFile, "0010", "2000", "LO", "");                  // ABZESS                            medical alerts
	//AddToDumpFile(hFile, "0010", "2110", "LO", "");                  // BARIUMSULFAT                      contrast allergies
	AddToDumpFile(hFile, "0020", "000d", "UI", szStudyUID);            // 1.2.276.0.7230010.3.2.102         study instance uid
	AddToDumpFile(hFile, "0008", "0090", "PN", szRequestingPhysician); // NEWMAN                            requesting physician
	AddToDumpFile(hFile, "0032", "1060", "LO", szPrestazioneDescription);// EXAM5464                          requested procedure description
	AddToDumpFile(hFile, "0040", "1001", "SH", szExamType);            // RP488M9439                        requested procedure id
	AddToDumpFile(hFile, "0040", "1003", "SH", "NORMAL");              // HIGH                              requested procedure priority
	AddToDumpFile(hFile, "0040", "0100", "SQ", "");                    //                                   scheduled procedure step sequence
	AddToDumpFile(hFile, "fffe", "e000", "-" , "");                    //
	AddToDumpFile(hFile, "0008", "0060", "CS", "US");                  // CT                                modality
	//AddToDumpFile(hFile, "0032", "1070", "LO", "");                  //                                   requested contrast agent 
	AddToDumpFile(hFile, "0040", "0001", "AE", m_szAET);               // AB45                              scheduled station ae title
	AddToDumpFile(hFile, "0040", "0002", "DA", szExamDateCopy);        // 19960406                          scheduled procedure step start date
	AddToDumpFile(hFile, "0040", "0003", "TM", szExamDate + 8);        // 160700                            scheduled procedure step start time
	AddToDumpFile(hFile, "0040", "0006", "PN", szPhysician);           // ROSS                              scheduled performing physiscian's name
	AddToDumpFile(hFile, "0040", "0007", "LO", szExamDescription);     // EXAM04                            scheduled procedure step description
	AddToDumpFile(hFile, "0040", "0009", "SH", szExamType);            // SPD1342                           scheduled procedure step id
	AddToDumpFile(hFile, "0040", "0010", "SH", szComputerName);        // STNAB89                           scheduled station name
	AddToDumpFile(hFile, "0040", "0011", "SH", "");                    // B67F66                            scheduled procedure step location
	//AddToDumpFile(hFile, "0040", "0012", "LO", "");                  //                                   pre-medication
	//AddToDumpFile(hFile, "0040", "0400", "LT", "");                  //                                   comments on the scheduled procedure step
	AddToDumpFile(hFile, "fffe", "e00d", "-" , "");                    //
	AddToDumpFile(hFile, "fffe", "e0dd", "-" , "");                    //
	CloseHandle(hFile);

	return ConvertDumpToDcm(szWorklistDump, szWorklistDcm);
}

void CModalityWorklistSCP::GetApplicationDir(LPTSTR szModuleName, UINT iLength)
{
	::GetModuleFileName(NULL, szModuleName, iLength * sizeof(TCHAR));

	for (int i = strlen(szModuleName) - 1; i >= 0; i--)
	{
		if (szModuleName[i] == '\\')
		{
			szModuleName[i] = 0;
			break;
		}
	}
}

void CModalityWorklistSCP::AddToDumpFile(HANDLE hFile, LPCTSTR szGroup, LPCTSTR szElement, LPCTSTR szType, LPCTSTR szValue)
{
	TCHAR szLine[1024];
	strcpy_s(szLine, "(");
	strcat_s(szLine, szGroup);
	strcat_s(szLine, ",");
	strcat_s(szLine, szElement);
	strcat_s(szLine, ") ");
	strcat_s(szLine, szType);
	strcat_s(szLine, " ");
	strcat_s(szLine, szValue);
	strcat_s(szLine, "\n");
	
	DWORD dwWritten;
	WriteFile(hFile, szLine, strlen(szLine), &dwWritten, NULL);
}

void CModalityWorklistSCP::GetWorklistDumpFile(LPTSTR szFile, UINT iBufferSize)
{
	GetApplicationDir(szFile, iBufferSize);
	strcat_s(szFile, iBufferSize, "\\ModalityWorklistSCP\\");
	strcat_s(szFile, iBufferSize, m_szAET);
	strcat_s(szFile, iBufferSize, "\\wklist.dump");
}

void CModalityWorklistSCP::GetWorklistDcmFile(LPTSTR szFile, UINT iBufferSize)
{
	GetApplicationDir(szFile, iBufferSize);
	strcat_s(szFile, iBufferSize, "\\ModalityWorklistSCP\\");
	strcat_s(szFile, iBufferSize, m_szAET);
	strcat_s(szFile, iBufferSize, "\\wklist.wl");
}

BOOL CModalityWorklistSCP::ConvertDumpToDcm(LPCTSTR szFileDump, LPCTSTR szFileDcm)
{
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	TCHAR szApplicationDir[MAX_PATH];
	GetApplicationDir(szApplicationDir, MAX_PATH);

	TCHAR szCommandLine[1024];
	sprintf_s(szCommandLine, 
		      "%s\\ModalityWorklistSCP\\dump2dcm.exe \"%s\" \"%s\"",
			  szApplicationDir,
			  szFileDump,
			  szFileDcm);

	DWORD dwExitCode = 0xFFFFFFFF;

	// Start the child process. 
	if (CreateProcess(NULL,
					  szCommandLine,
					  NULL,
					  NULL,
					  FALSE,
					  CREATE_NO_WINDOW,
					  NULL,
					  NULL,
					  &si,
					  &pi))
	{
		WaitForSingleObject(pi.hProcess, INFINITE);

		GetExitCodeProcess(pi.hProcess, &dwExitCode);

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	return _access(szFileDcm, 00) == 0 && dwExitCode == 0;
}

DWORD WINAPI CModalityWorklistSCP::ThreadWorklistSCP(LPVOID lpParameter)
{
	CModalityWorklistSCP* pObj = (CModalityWorklistSCP*)lpParameter;

	EnterCriticalSection(&pObj->m_cs);

	DWORD dwError = 0, dwExitCode = 0;
	BOOL bResult = FALSE;

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

	HANDLE hChildStdoutRd, hChildStdoutWr;
	if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &sa, 10000000))
		return FALSE;

	HANDLE hChildStderrRd, hChildStderrWr;
	if (!CreatePipe(&hChildStderrRd, &hChildStderrWr, &sa, 10000000))
		return FALSE;

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
    si.dwFlags    = STARTF_USESTDHANDLES;
    si.hStdInput  = NULL;
    si.hStdOutput = hChildStdoutWr;
    si.hStdError  = hChildStderrWr;

	TCHAR szApplicationDir[MAX_PATH];
	pObj->GetApplicationDir(szApplicationDir, MAX_PATH);
	strcat_s(szApplicationDir, "\\ModalityWorklistSCP");

	TCHAR szCommandLine[1024];
	sprintf_s(szCommandLine, 
		      "%s\\wlmscpfs.exe %li -ll info -dfp \"%s\"",
			  szApplicationDir,
			  pObj->m_iPort,
			  szApplicationDir);

	// Start the child process. 
	if (CreateProcess(NULL,
					  szCommandLine,
					  &sa,
					  &sa,
					  TRUE,
					  CREATE_NO_WINDOW,
					  NULL,
					  NULL,
					  &si,
					  &pi))
	{
		pObj->m_hProcess = pi.hProcess;

		while (WaitForSingleObject(pi.hProcess, 500) != WAIT_OBJECT_0)
		{
			if (pObj->m_bEnableLog)
			{
				DWORD dwTotalBytes = 0, dwReaded, dwWritten;
				if (PeekNamedPipe(hChildStdoutRd, NULL, 0, NULL, &dwTotalBytes, NULL) && dwTotalBytes > 0)
				{
					BYTE* pBuffer = new BYTE[dwTotalBytes];
					if (ReadFile(hChildStdoutRd, pBuffer, dwTotalBytes, &dwReaded, NULL))
					{
						if (pObj->m_hLogFile != INVALID_HANDLE_VALUE)
							WriteFile(pObj->m_hLogFile, pBuffer, dwTotalBytes, &dwWritten, NULL);
					}

					delete pBuffer;
				}
			}
		}

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	CloseHandle(hChildStdoutRd);
	CloseHandle(hChildStdoutWr);
	CloseHandle(hChildStderrRd);
	CloseHandle(hChildStderrWr);

	LeaveCriticalSection(&pObj->m_cs);
	return 0;
}

BOOL CModalityWorklistSCP::KillProcess(LPCTSTR szProcess)
{
    DWORD dwProcesses[1024], dwNeededProcesses;
    if (!EnumProcesses(dwProcesses, sizeof(dwProcesses), &dwNeededProcesses))
        return FALSE;

	BOOL bReturn = FALSE;
	for (UINT i = 0; i < dwNeededProcesses / sizeof(DWORD); i++)
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE,
									  FALSE,
									  dwProcesses[i]);
		if (hProcess != NULL)
		{
			DWORD dwNeededModule;
			HMODULE hModule;
			if (EnumProcessModules(hProcess, 
				                   &hModule, 
								   sizeof(hModule), 
				                   &dwNeededModule))
			{
				TCHAR szProcessName[MAX_PATH];
				ZeroMemory(szProcessName, sizeof(TCHAR) * MAX_PATH);
				if (GetModuleFileNameEx(hProcess, hModule, szProcessName, MAX_PATH) > 0)
				{
					CString strProcessName(szProcessName);
					strProcessName.MakeUpper();
					
					CString strProcessToKill(szProcess);
					strProcessToKill.MakeUpper();

					if (strProcessName.Right(strProcessToKill.GetLength()) == strProcessToKill)
						bReturn = TerminateProcess(hProcess, 0);
				}
			}
	
			CloseHandle(hProcess);
		}
	}

	return bReturn;
}