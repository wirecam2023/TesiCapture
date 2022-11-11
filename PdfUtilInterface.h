#pragma once

class CPdfUtilInterface
{

public:

	static CPdfUtilInterface* Get() { return &m_obj; }

	BOOL DeleteAllPdf(LPCTSTR szDirectory);
	BOOL ExtractPage(LPCTSTR szPdfInputFile, LPCTSTR szPdfOutputFile, const UINT iPage);
	BOOL Merge(const CStringList* pListPdfInputFiles, LPCTSTR szPdfOutputFile);
	BOOL Verify();

private:

	static CPdfUtilInterface m_obj;

	//

	CPdfUtilInterface();
	~CPdfUtilInterface();

	BOOL LaunchProcess(LPCTSTR szExe, LPCTSTR szArguments);

	BOOL CheckNetfxVersionUsingMscoree(const TCHAR *pszNetfxVersionToCheck);
	DWORD GetProcessorArchitectureFlag();
	BOOL IsNetfx20Installed();
	

};
