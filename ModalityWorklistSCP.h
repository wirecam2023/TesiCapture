#pragma once

class CModalityWorklistSCP
{

public:

	static CModalityWorklistSCP* Get() { return &m_obj; }

	BOOL Start(LPCTSTR szAET, UINT iPort, BOOL bEnableLog);
	void Stop();
	
	void Clear();
	BOOL SetPatient(LPCTSTR szPatientID,
					LPCTSTR szPatientFirstname,
					LPCTSTR szPatientLastname,
					TCHAR(&szPatientBirthDate)[9],
					TCHAR(&szPatientSex)[2],
					UINT iExamType,
					LPCTSTR szExamDescription,
					TCHAR(&szExamDate)[15],
					LPCTSTR szAccessionNumber,
					LPCTSTR szPatientAltezza,
					LPCTSTR szPatientPeso,
					LPCTSTR szPhysician,
					LPCTSTR szPrestazioneDescription,
					LPCTSTR szRequestingPhysician);

	BOOL IsStarted() { return m_bStarted; }

protected:

	CModalityWorklistSCP(void);
	~CModalityWorklistSCP(void);

	void GetApplicationDir(LPTSTR szModuleName, UINT iLength);
	void GetWorklistDumpFile(LPTSTR szFile, UINT iBufferSize);
	void GetWorklistDcmFile(LPTSTR szFile, UINT iBufferSize);

	BOOL ConvertDumpToDcm(LPCTSTR szFileDump, LPCTSTR szFileDcm);

	void AddToDumpFile(HANDLE hFile, LPCTSTR szGroup, LPCTSTR szElement, LPCTSTR szType, LPCTSTR szValue);

	BOOL KillProcess(LPCTSTR szProcess);

	static DWORD WINAPI ThreadWorklistSCP(LPVOID lpParameter);

	static CModalityWorklistSCP m_obj;

	HANDLE m_hLogFile, m_hProcess;

	CRITICAL_SECTION m_cs;

	TCHAR m_szAET[1024];
	UINT m_iPort;
	BOOL m_bEnableLog;

	BOOL m_bStarted;

};
