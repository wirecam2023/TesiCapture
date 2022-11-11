#pragma once
class CCommonCLR
{
public:
	static BOOL SaveHexToFile(LPCTSTR szHexa, LPCTSTR szPath);
	static CString GetHASHFromFile(LPCTSTR szPath);
	static CString ForceGC();
	static BOOL MoveFileSafe(LPCTSTR szCurLocation, LPCTSTR szNewLocation);
	static BOOL DeleteFileSafe(LPCTSTR szFile);
};