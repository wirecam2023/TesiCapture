#include "stdafx.h"
#include "Endox.h"
#include "PdfUtilInterface.h"

#include <io.h>
#include <mscoree.h>

#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPdfUtilInterface CPdfUtilInterface::m_obj;

CPdfUtilInterface::CPdfUtilInterface(void)
{
}

CPdfUtilInterface::~CPdfUtilInterface(void)
{
}

BOOL CPdfUtilInterface::DeleteAllPdf(LPCTSTR szDirectory)
{
	CFileFind finder;
	CString strFile, strWildcard;

	strWildcard.Format("%s\\*.pdf",
		szDirectory);
	BOOL bWorking = finder.FindFile(strWildcard);

	if (!bWorking)
		return TRUE;

	BOOL bReturn = TRUE;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (finder.IsDirectory() || finder.IsDots())
			continue;

		CString strFile = finder.GetFilePath();
		if (!DeleteFile(strFile))
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_PDFUTIL_ERROR_6), strFile, GetLastError());
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
			bReturn = FALSE;
			break;
		}
	}

	finder.Close();
	return bReturn;
}

BOOL CPdfUtilInterface::ExtractPage(LPCTSTR szPdfInputFile, LPCTSTR szPdfOutputFile, const UINT iPage)
{
	CString strArguments;
	strArguments.Format("\"%s\" \"%s\" %li",
		szPdfInputFile,
		szPdfOutputFile,
		iPage);

	if (_access(szPdfOutputFile, 00) == 0)
	{
		if (!DeleteFile(szPdfOutputFile))
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_PDFUTIL_ERROR_3), szPdfOutputFile);
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
			return FALSE;
		}
	}

	if (!LaunchProcess(theApp.m_sDirProg + "\\PdfUtils\\PdfPageExtractor.exe", strArguments))
	{
		CString strError;
		strError.Format(theApp.GetMessageString(IDS_PDFUTIL_ERROR_4), "PdfUtils\\PdfPageExtractor.exe");
		theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
		return FALSE;
	}

	return (_access(szPdfOutputFile, 00) == 0);
}

BOOL CPdfUtilInterface::Merge(const CStringList* pListPdfInputFiles, LPCTSTR szPdfOutputFile)
{
	CString strFiles;
	for (POSITION pos = pListPdfInputFiles->GetHeadPosition(); pos;)
		strFiles += pListPdfInputFiles->GetNext(pos) + ",";
	strFiles = strFiles.Left(strFiles.GetLength() - 1);

	CString strArguments;
	strArguments.Format("\"%s\" \"%s\"",
		strFiles,
		szPdfOutputFile);

	if (_access(szPdfOutputFile, 00) == 0)
	{
		if (!DeleteFile(szPdfOutputFile))
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_PDFUTIL_ERROR_3), szPdfOutputFile);
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
			return FALSE;
		}
	}

	if (!LaunchProcess(theApp.m_sDirProg + "\\PdfUtils\\PdfMerger.exe", strArguments))
	{
		CString strError;
		strError.Format(theApp.GetMessageString(IDS_PDFUTIL_ERROR_4), "PdfUtils\\PdfMerger.exe");
		theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
		return FALSE;
	}

	return (_access(szPdfOutputFile, 00) == 0);
}

BOOL CPdfUtilInterface::Verify()
{
	if (_access(theApp.m_sDirProg + "\\PdfUtils\\PdfMerger.exe", 00) != 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PDFUTIL_ERROR_1), MB_ICONSTOP);
		return FALSE;
	}

	if (_access(theApp.m_sDirProg + "\\PdfUtils\\PdfPageExtractor.exe", 00) != 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PDFUTIL_ERROR_1), MB_ICONSTOP);
		return FALSE;
	}

	if (!IsNetfx20Installed())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PDFUTIL_ERROR_2), MB_ICONSTOP);
		return FALSE;
	}

	return TRUE;
}

BOOL CPdfUtilInterface::LaunchProcess(LPCTSTR szExe, LPCTSTR szArguments)
{
	TCHAR szCommandLine[1024];
	sprintf_s(szCommandLine, "%s %s", szExe, szArguments);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	BOOL bReturn = FALSE;
	if (CreateProcess(NULL,			            // No module name (use command line). 
					  szCommandLine,	        // Command line. 
					  NULL,				        // Process handle not inheritable. 
					  NULL,				        // Thread handle not inheritable. 
					  FALSE,			        // Set handle inheritance to FALSE. 
					  CREATE_NO_WINDOW,         // No creation flags. 
					  NULL,				        // Use parent's environment block. 
					  NULL,				        // Use parent's starting directory. 
					  &si,				        // Pointer to STARTUPINFO structure.
					  &pi))				        // Pointer to PROCESS_INFORMATION structure.
	{
		WaitForSingleObject(pi.hProcess, INFINITE);

		DWORD dwExitCode;
		if (GetExitCodeProcess(pi.hProcess, &dwExitCode))
			bReturn = (dwExitCode == 1);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	return bReturn;
}

BOOL CPdfUtilInterface::CheckNetfxVersionUsingMscoree(const TCHAR *pszNetfxVersionToCheck)
{
	const TCHAR* szNetfx10VersionString = "v1.0.3705";
	USES_CONVERSION;

	BOOL bFoundRequestedNetfxVersion = FALSE;
	HRESULT hr = S_OK;

	// Check input parameter
	if (NULL == pszNetfxVersionToCheck)
		return FALSE;

	HMODULE hmodMscoree = LoadLibraryEx("mscoree.dll", NULL, 0);
	if (NULL != hmodMscoree)
	{
		typedef HRESULT(STDAPICALLTYPE *GETCORVERSION)(LPWSTR szBuffer, DWORD cchBuffer, DWORD* dwLength);
		GETCORVERSION pfnGETCORVERSION = (GETCORVERSION)GetProcAddress(hmodMscoree, "GetCORVersion");

		// Some OSs shipped with a placeholder copy of mscoree.dll. The existence of mscoree.dll
		// therefore does NOT mean that a version of the .NET Framework is installed.
		// If this copy of mscoree.dll does not have an exported function named GetCORVersion
		// then we know it is a placeholder DLL.
		if (NULL == pfnGETCORVERSION)
			goto Finish;

		typedef HRESULT(STDAPICALLTYPE *CORBINDTORUNTIME)(LPCWSTR pwszVersion, LPCWSTR pwszBuildFlavor, REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv);
		CORBINDTORUNTIME pfnCORBINDTORUNTIME = (CORBINDTORUNTIME)GetProcAddress(hmodMscoree, "CorBindToRuntime");

		typedef HRESULT(STDAPICALLTYPE *GETREQUESTEDRUNTIMEINFO)(LPCWSTR pExe, LPCWSTR pwszVersion, LPCWSTR pConfigurationFile, DWORD startupFlags, DWORD runtimeInfoFlags, LPWSTR pDirectory, DWORD dwDirectory, DWORD *dwDirectoryLength, LPWSTR pVersion, DWORD cchBuffer, DWORD* dwlength);
		GETREQUESTEDRUNTIMEINFO pfnGETREQUESTEDRUNTIMEINFO = (GETREQUESTEDRUNTIMEINFO)GetProcAddress(hmodMscoree, "GetRequestedRuntimeInfo");

		if (NULL != pfnCORBINDTORUNTIME)
		{
			TCHAR szRetrievedVersion[50];
			DWORD dwLength = _countof(szRetrievedVersion);

			if (NULL == pfnGETREQUESTEDRUNTIMEINFO)
			{
				// Having CorBindToRuntimeHost but not having GetRequestedRuntimeInfo means that
				// this machine contains no higher than .NET Framework 1.0, but the only way to
				// 100% guarantee that the .NET Framework 1.0 is installed is to call a function
				// to exercise its functionality
				if (0 == _tcscmp(pszNetfxVersionToCheck, szNetfx10VersionString))
				{
					hr = pfnGETCORVERSION(T2W(szRetrievedVersion), dwLength, &dwLength);

					if (SUCCEEDED(hr))
					{
						if (0 == _tcscmp(szRetrievedVersion, szNetfx10VersionString))
							bFoundRequestedNetfxVersion = true;
					}

					goto Finish;
				}
			}

			// Set error mode to prevent the .NET Framework from displaying
			// unfriendly error dialogs
			UINT uOldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);

			TCHAR szDirectory[MAX_PATH];
			DWORD dwDirectoryLength = 0;
			DWORD dwRuntimeInfoFlags = RUNTIME_INFO_DONT_RETURN_DIRECTORY | GetProcessorArchitectureFlag();

			// Check for the requested .NET Framework version
			hr = pfnGETREQUESTEDRUNTIMEINFO(NULL,
				T2W(pszNetfxVersionToCheck),
				NULL,
				STARTUP_LOADER_OPTIMIZATION_MULTI_DOMAIN_HOST,
				NULL,
				T2W(szDirectory),
				_countof(szDirectory),
				&dwDirectoryLength,
				T2W(szRetrievedVersion),
				_countof(szRetrievedVersion),
				&dwLength);

			if (SUCCEEDED(hr))
				bFoundRequestedNetfxVersion = true;

			// Restore the previous error mode
			SetErrorMode(uOldErrorMode);
		}
	}

Finish:
	if (hmodMscoree)
	{
		FreeLibrary(hmodMscoree);
	}

	return bFoundRequestedNetfxVersion;
}

DWORD CPdfUtilInterface::GetProcessorArchitectureFlag()
{
	HMODULE hmodKernel32 = NULL;
	typedef void (WINAPI *PFnGetNativeSystemInfo) (LPSYSTEM_INFO);
	PFnGetNativeSystemInfo pfnGetNativeSystemInfo;

	SYSTEM_INFO sSystemInfo;
	memset(&sSystemInfo, 0, sizeof(sSystemInfo));

	bool bRetrievedSystemInfo = false;

	// Attempt to load kernel32.dll
	hmodKernel32 = LoadLibrary("Kernel32.dll");
	if (NULL != hmodKernel32)
	{
		// If the DLL loaded correctly, get the proc address for GetNativeSystemInfo
		pfnGetNativeSystemInfo = (PFnGetNativeSystemInfo)GetProcAddress(hmodKernel32, "GetNativeSystemInfo");
		if (NULL != pfnGetNativeSystemInfo)
		{
			// Call GetNativeSystemInfo if it exists
			(*pfnGetNativeSystemInfo)(&sSystemInfo);
			bRetrievedSystemInfo = true;
		}
		FreeLibrary(hmodKernel32);
	}

	if (!bRetrievedSystemInfo)
	{
		// Fallback to calling GetSystemInfo if the above failed
		GetSystemInfo(&sSystemInfo);
		bRetrievedSystemInfo = true;
	}

	if (bRetrievedSystemInfo)
	{
		switch (sSystemInfo.wProcessorArchitecture)
		{
		case PROCESSOR_ARCHITECTURE_INTEL:
			return RUNTIME_INFO_REQUEST_X86;
		case PROCESSOR_ARCHITECTURE_IA64:
			return RUNTIME_INFO_REQUEST_IA64;
		case PROCESSOR_ARCHITECTURE_AMD64:
			return RUNTIME_INFO_REQUEST_AMD64;
		default:
			return 0;
		}
	}

	return 0;
}

BOOL CPdfUtilInterface::IsNetfx20Installed()
{
	BOOL bRetValue = FALSE;

	try
	{
		const TCHAR* szNetfx20RegKeyName = "Software\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727";
		const TCHAR* szNetfxStandardRegValueName = "Install";
		const TCHAR* szNetfx20VersionString = "v2.0.50727";

		DWORD dwRegValue = 0;
		if (RegistryGetValue(HKEY_LOCAL_MACHINE, szNetfx20RegKeyName, szNetfxStandardRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		{
			if (dwRegValue == 1)
				bRetValue = CheckNetfxVersionUsingMscoree(szNetfx20VersionString);
		}
	}
	catch (...)
	{
	}

	return bRetValue;
}
