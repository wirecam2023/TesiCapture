#include "stdafx.h"
#include "Endox.h"
#include "AcquisitionWaiterDlg.h"

#include <tlhelp32.h>

#include "DLL_Imaging\h\AmLogin.h"
#include "DLL_Imaging\h\AmRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_APERTURA 0x987
#define TIMER_CHIUSURA 0x654

IMPLEMENT_DYNAMIC(CAcquisitionWaiterDlg, CDialog)

CAcquisitionWaiterDlg::CAcquisitionWaiterDlg(CWnd* pParent)
	: CDialog(CAcquisitionWaiterDlg::IDD, pParent)
{
}

CAcquisitionWaiterDlg::~CAcquisitionWaiterDlg()
{
}

void CAcquisitionWaiterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ANIM, m_ctrlAnim);

	DDX_Control(pDX, IDC_PROGRESS_LABEL, m_ctrlStaticLabel);
}

BEGIN_MESSAGE_MAP(CAcquisitionWaiterDlg, CDialog)

	ON_WM_TIMER()

END_MESSAGE_MAP()

BOOL CAcquisitionWaiterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (HMODULE hModule = ::LoadLibrary("Amres.dll"))
	{
		HINSTANCE hInstance = AfxGetResourceHandle();
		AfxSetResourceHandle(hModule);
		m_ctrlAnim.Open(Amres_waiting);
		m_ctrlAnim.Play(0, -1, -1);
		AfxSetResourceHandle(hInstance);
	}

	SetTimer(TIMER_APERTURA, 100, NULL);

	theApp.LocalizeDialog(this, CAcquisitionWaiterDlg::IDD, "AcquisitionWaiterDlg");
	return TRUE;
}

void CAcquisitionWaiterDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	switch(nIDEvent)
	{
		case TIMER_APERTURA:
		{
			KillTimer(TIMER_APERTURA);

			// --- //

			char szProcess[1024];
#ifdef _DEBUG
			sprintf_s(szProcess, "%s\\xCapDebug.exe", theApp.m_sDirProg);
#else
			sprintf_s(szProcess, "%s\\xCap\\xCap.exe %s", theApp.m_sDirProg, theApp.m_sFileConfig);
#endif

			/* Sandro 04/10/2013
			if (theApp.m_bPersonalizzazioniBrasileEintein)
			{
				if (!(theApp.m_dwPrivileges & AMLogin_Permissions::configurations))
					sprintf_s(szProcess, "%s\\xCap\\xCap.exe %s -lockedcontrols", theApp.m_sDirProg, theApp.m_sFileConfig);
			}
			*/

			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));

			if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
			{
				LPVOID lpMsgBuf;
				if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
					theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
				else
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
				LocalFree(lpMsgBuf);
			}
			else
			{
				// Davide // aspetto che xcap si apra veramente altrimenti, in alcuni computer, Endox non aspetta l'acquisizione delle immagini //

				int iIndex = 0;

#ifdef _DEBUG
				while(!FindProc("xCapDebug.exe") && iIndex++ < 20)
					Sleep(1000);
#else
				while(!FindProc("xcap.exe") && iIndex++ < 20)
					Sleep(1000);
#endif

				if (iIndex >= 20)
					theApp.AfxMessageBoxEndo("Timeout waiting xcap!");
			}

			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			// --- //

			SetTimer(TIMER_CHIUSURA, 1000, NULL);

			// --- //

			break;
		}
		case TIMER_CHIUSURA:
		{	
#ifdef _DEBUG
			if (!FindProc("xCapDebug.exe"))
			{
				m_pParentWnd->SendMessage(WM_ACQUISITIONWAITER_CLOSING);
				CDialog::OnOK(); // PostQuitMessage(-1); // Sandro 14/07/2014 // in alcuni casi piantava tutto... //
			}
#else
			if (!FindProc("xcap.exe"))
			{
				m_pParentWnd->SendMessage(WM_ACQUISITIONWAITER_CLOSING);
				CDialog::OnOK(); // PostQuitMessage(-1); // Sandro 14/07/2014 // in alcuni casi piantava tutto... //				
			}

#endif

			break;
		}
	}
}

BOOL CAcquisitionWaiterDlg::FindProc(LPTSTR szProcName)
{
	CString strProcessName(szProcName);
	strProcessName.MakeUpper();

	BOOL bResult = FALSE;

	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		theApp.AfxMessageBoxEndo("error 1");
		return FALSE;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		theApp.AfxMessageBoxEndo("error 2");
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	do
	{
		// Davide // per sicurezza confronto le due stringhe maiuscole //

		_strupr_s(pe32.szExeFile);
		if (strcmp(strProcessName, pe32.szExeFile) == 0)
		{
			bResult = TRUE;
			break;
		}
			
	} while(Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);

	return bResult;
}