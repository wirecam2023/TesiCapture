#include "stdafx.h"
#include "Endox.h"
#include "RGL.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRGL, CDialog) 

CRGL::CRGL(CWnd* pParentWnd)
	: CDialog(CRGL::IDD, pParentWnd)
{
}

CRGL::~CRGL()
{
	if (GetSafeHwnd())
		DestroyWindow();
}

void CRGL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPGEN, m_rgl);
}

BEGIN_MESSAGE_MAP(CRGL, CDialog)
END_MESSAGE_MAP()

BOOL CRGL::Create()
{
	if (!CDialog::Create(CRGL::IDD))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_REPGEN), MB_ICONSTOP);
		return FALSE;
	}

	ShowWindow(SW_HIDE);
	return TRUE;
}

void CRGL::ExecutePrint(CString strFileRgf, BOOL bLandscape, CString strPrinter)
{
	if (strPrinter.IsEmpty())
	{
		CPrintDialog dlg(FALSE);
		if (dlg.DoModal() != IDOK)
			return;

		strPrinter = dlg.GetDeviceName();
	}
	
	TCHAR szProgram[1024];

#ifdef _DEBUG
	if (theApp.AfxMessageBoxEndo("Vuoi stampare direttamente?", MB_YESNO) == IDYES)
		sprintf_s(szProgram, "%s\\RGL\\winrg.exe %s/pt %s \"%s\"", theApp.m_sDirProg, bLandscape ? "/landscape " : "", strFileRgf, strPrinter);
	else
		sprintf_s(szProgram, "%s\\RGL\\winrg.exe %s/preview /pt %s \"%s\"", theApp.m_sDirProg, bLandscape ? "/landscape " : "", strFileRgf, strPrinter);
#else
	sprintf_s(szProgram, "%s\\RGL\\winrg.exe %s/pt %s \"%s\"", theApp.m_sDirProg, bLandscape ? "/landscape " : "", strFileRgf, strPrinter);
#endif
	
	/*
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, szProgram, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	*/

	WinExec(szProgram, SW_SHOW);
}

void CRGL::ExecutePrint(CStringList* pListFiles, CString strPrinter)
{
	for(int i = 0; i < pListFiles->GetCount(); i++)
	{
		POSITION pos = pListFiles->FindIndex(i);
		if (_access(pListFiles->GetAt(pos), 00) != 0)
		{
			pListFiles->RemoveAt(pos);
			i--;
		}
	}

	if (pListFiles->GetCount() == 0)
		return;

	if (strPrinter.IsEmpty())
	{
		CPrintDialog dlg(FALSE);
		if (dlg.DoModal() != IDOK)
			return;

		strPrinter = dlg.GetDeviceName();
	}

	CString strListFile = theApp.m_sDirProg + "\\RGL\\ReportList.lst";
	HANDLE hFile = ::CreateFile(strListFile,
		                        FILE_WRITE_DATA,
								FILE_SHARE_WRITE,
								NULL,
								CREATE_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,
								NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		for(POSITION pos = pListFiles->GetHeadPosition(); pos;)
		{
			CString strFile = pListFiles->GetNext(pos);
			strFile += "\r\n";
			
			DWORD dwWritten;
			WriteFile(hFile, 
				      strFile.GetBuffer(strFile.GetLength()),
					  strFile.GetLength(),
					  &dwWritten,
					  NULL);
			
			strFile.ReleaseBuffer();
		}

		CloseHandle(hFile);
	}

	TCHAR szProgram[1024];
#ifdef _DEBUG
	if (theApp.AfxMessageBoxEndo("Vuoi stampare direttamente?", MB_YESNO) == IDYES)
		sprintf_s(szProgram, "%s\\RGL\\winrg.exe /pt @%s \"%s\"", theApp.m_sDirProg, strListFile, strPrinter);
	else
		sprintf_s(szProgram, "%s\\RGL\\winrg.exe /preview /pt @%s \"%s\"", theApp.m_sDirProg, strListFile, strPrinter);
#else
	sprintf_s(szProgram, "%s\\RGL\\winrg.exe /pt @%s \"%s\"", theApp.m_sDirProg, strListFile, strPrinter);
#endif

	/*
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, szProgram, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);*/

	WinExec(szProgram, SW_SHOW);
}