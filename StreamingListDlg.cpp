#include "stdafx.h"
#include "Endox.h"
#include "StreamingListDlg.h"

#include "DLL_Imaging\h\AmLogin.h"
#include "DLL_Imaging\h\AmStreaming.h"

#include "EsamiView.h"
#include "InsertLogStreamingSPSet.h"
#include "SorgentiStreamingSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CStreamingListDlg, CDialog)

CStreamingListDlg::CStreamingListDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CStreamingListDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CStreamingListDlg::~CStreamingListDlg()
{
}

BEGIN_MESSAGE_MAP(CStreamingListDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CMS, OnBnClickedBtnCms)
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBnClickedBtnOpen)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)	
END_MESSAGE_MAP()

void CStreamingListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_CMS, m_ctrlBtnCms);
	DDX_Control(pDX, IDC_BTN_OPEN, m_ctrlBtnOpen);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

BOOL CStreamingListDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, "Sorgente streaming", LVCFMT_LEFT);
	m_ctrlList.InsertColumn(1, "Paziente - Esame", LVCFMT_LEFT);
	m_ctrlList.InsertColumn(2, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(3, "", LVCFMT_LEFT, 0);
    
	if (theApp.m_iUseTCMS == 0)
		m_ctrlBtnCms.ShowWindow(SW_HIDE);
	else
		m_ctrlBtnCms.ShowWindow(SW_SHOW);

	RiempiLista();

	theApp.LocalizeDialog(this, CStreamingListDlg::IDD, "StreamingListDlg");
	return bReturn;
}

void CStreamingListDlg::OnBnClickedBtnOpen()
{
	if (theApp.m_iUseVLC == 0)
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nItem = m_ctrlList.GetNextSelectedItem(pos);
			if (nItem >= 0)
			{
				CString sTitle = m_ctrlList.GetItemText(nItem, 0);
				CString sURI = m_ctrlList.GetItemText(nItem, 2);
				CString sPazienteEsame = m_ctrlList.GetItemText(nItem, 3);

				if ((!sTitle.IsEmpty()) && (!sURI.IsEmpty()))
				{
					CInsertLogStreamingSPSet().Exec(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer.Left(50), sTitle, sPazienteEsame);
					AMStreaming_OpenDialog(this, sTitle, sPazienteEsame, sURI, theApp.GetMessageString(IDS_PLAY), theApp.GetMessageString(IDS_STOP), theApp.GetMessageString(IDS_DIMENSIONE_ORIGINALE), theApp.GetMessageString(IDS_DIMENSIONE_DOPPIA), theApp.GetMessageString(IDS_DIMENSIONE_PIENA));
				}
			}
		}
	}
	else
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nItem = m_ctrlList.GetNextSelectedItem(pos);
			if (nItem >= 0)
			{
				CString str = m_ctrlList.GetItemText(nItem, 1);
				VlcManager(str);
			}
		}
	}
}

void CStreamingListDlg::VlcManager(CString sSource)
{
		TCHAR szProcess[1024];
		sprintf_s(szProcess, "%s\\vlc.exe %s", theApp.m_sPathVLC, sSource);

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
		{
			LPVOID lpMsgBuf;
			if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
				theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
			else
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
			LocalFree(lpMsgBuf);

			return;
		}

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
}

void CStreamingListDlg::RiempiLista()
{
	BeginWaitCursor();

	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CSorgentiStreamingSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CStreamingListDlg::RiempiLista"))
	{
		int nItem = 0;
		while(!setTemp.IsEOF())
		{
			m_ctrlList.InsertItem(nItem, setTemp.m_sDescrizione);

			m_ctrlList.SetItemText(nItem, 3, setTemp.m_sPazienteEsame);

			setTemp.m_sPazienteEsame.Replace("\n\n", " - ");
			setTemp.m_sPazienteEsame.Replace("\n", " ");
			while(setTemp.m_sPazienteEsame.Find("  ") >= 0)
				setTemp.m_sPazienteEsame.Replace("  ", " ");

			m_ctrlList.SetItemText(nItem, 1, setTemp.m_sPazienteEsame);

			m_ctrlList.SetItemText(nItem, 2, setTemp.m_sIndirizzoCompleto);

			nItem++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CStreamingListDlg::RiempiLista");
	}

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);

	EndWaitCursor();
}

void CStreamingListDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedBtnOpen();

	*pResult = 0;
}

void CStreamingListDlg::OnBnClickedBtnCms()
{
	TCHAR szProcess[1024];
	strcpy_s(szProcess, theApp.m_sPathTCMS);		

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		LPVOID lpMsgBuf;
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
			theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
		else
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
		LocalFree(lpMsgBuf);

		return;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
