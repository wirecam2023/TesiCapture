#include "stdafx.h"
#include "Endox.h"
#include "ShowDbQueriesDlg.h"

#include <io.h>

#include "MmSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CShowDbQueriesDlg::CShowDbQueriesDlg(CWnd* pParent)
    : CResizableDialog(CShowDbQueriesDlg::IDD, pParent)
{
	m_lCounter = 0;
	m_dwLast = timeGetTime();
}

BEGIN_MESSAGE_MAP(CShowDbQueriesDlg, CResizableDialog)
	ON_BN_CLICKED(IDC_BTN_FIND1, OnBnClickedBtnFind1)
	ON_BN_CLICKED(IDC_BTN_FIND2, OnBnClickedBtnFind2)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
END_MESSAGE_MAP()

void CShowDbQueriesDlg::CreateModelessDialog(CWnd* pParent)
{	
	Create(CShowDbQueriesDlg::IDD, pParent);
}

void CShowDbQueriesDlg::DoDataExchange(CDataExchange* pDX)
{
    CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT, m_ctrlEdit);
	DDX_Control(pDX, IDC_BTN_FIND1, m_ctrlBtnFind1);
	DDX_Control(pDX, IDC_BTN_FIND2, m_ctrlBtnFind2);
	DDX_Control(pDX, IDC_BTN_RESET, m_ctrlBtnReset);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlBtnSave);
}

BOOL CShowDbQueriesDlg::OnInitDialog() 
{
    CResizableDialog::OnInitDialog();

	//
	AddAnchor(IDC_EDIT, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_BTN_FIND1, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_BTN_FIND2, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_BTN_RESET, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_BTN_SAVE, CSize(0, 100), CSize(0, 100));
	
	//
	//CRect rectMonitor;
	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectMonitor, 0);

	//
	CRect rectWindow;
	GetWindowRect(rectWindow);

	//
	SetWindowPos(&wndTopMost, theApp.m_rectDesk.right - rectWindow.Width(), theApp.m_rectDesk.bottom - rectWindow.Height(), 0, 0, SWP_NOSIZE);

	//SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	//
	m_ctrlEdit.SetLimitText(UINT_MAX);

	//
	theApp.LocalizeDialog(this, CShowDbQueriesDlg::IDD, "ShowDbQueriesDlg");

	//
	ShowWindow(SW_SHOW);
	return TRUE;
}

void CShowDbQueriesDlg::OnBnClickedBtnFind1()
{
	m_ctrlBtnFind1.SetCheck(BST_UNCHECKED);

	int nStartChar;
	int nEndChar;
	m_ctrlEdit.GetSel(nStartChar, nEndChar);

	CString strText;
	GetDlgItemText(IDC_EDIT, strText);

	int nFound = strText.Find("*****", nEndChar);
	if (nFound < 0)
		nFound = strText.Find("*****", 0);
	if (nFound >= 0)
		m_ctrlEdit.SetSel(nFound, nFound + 5);
}

void CShowDbQueriesDlg::OnBnClickedBtnFind2()
{
	m_ctrlBtnFind2.SetCheck(BST_UNCHECKED);

	int nStartChar;
	int nEndChar;
	m_ctrlEdit.GetSel(nStartChar, nEndChar);

	CString strText;
	GetDlgItemText(IDC_EDIT, strText);

	int nFound = strText.Find("!!!!!", nEndChar);
	if (nFound < 0)
		nFound = strText.Find("!!!!!", 0);
	if (nFound >= 0)
		m_ctrlEdit.SetSel(nFound, nFound + 5);
}

void CShowDbQueriesDlg::OnBnClickedBtnReset()
{
	m_ctrlBtnReset.SetCheck(BST_UNCHECKED);

	m_ctrlEdit.SetWindowText("");
	m_lCounter = 0;
}

void CShowDbQueriesDlg::OnBnClickedBtnSave()
{
	BeginWaitCursor();

	m_ctrlBtnSave.SetCheck(BST_UNCHECKED);

	CString strFilter;
	strFilter = "Text file (*.txt)|*.txt|";

	CFileDialog FileDlg(FALSE, NULL, NULL, OFN_READONLY |OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, strFilter, this, 0, FALSE);
	if (FileDlg.DoModal() == IDOK)
	{
		CString strPathName = FileDlg.GetPathName();
		if (strPathName.Right(4).CompareNoCase(".txt") != 0)
			strPathName += ".txt";

		if (_access(strPathName, 00) == 0)
		{
			EndWaitCursor();

			CString strMessage;
			strMessage.Format(theApp.GetMessageString(IDS_FILE_ALREADY_EXISTS), strPathName);
			theApp.AfxMessageBoxEndo(strMessage);
			return;
		}

		HANDLE hFile = CreateFile(strPathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE) 
		{
			CString strText;
			GetDlgItemText(IDC_EDIT, strText);

			char* pBuffer = (char*)strText.GetBuffer();

			DWORD dwBytesToWrite = (DWORD)strlen(pBuffer);
			DWORD dwBytesWritten = 0;

			while(dwBytesWritten < dwBytesToWrite)
			{
				if (!WriteFile(hFile, pBuffer + dwBytesWritten, dwBytesToWrite - dwBytesWritten, &dwBytesWritten, NULL))
					break;
			}

			strText.ReleaseBuffer();

			CloseHandle(hFile);
		}
	}

	EndWaitCursor();
}

void CShowDbQueriesDlg::WriteLine(DWORD dwMilliseconds, CString strSQL, CString strComment)
{
	DWORD dwDiff = timeGetTime() - m_dwLast;

	if (m_lCounter > 0)
	{
		m_ctrlEdit.SetSel(0, 0);
		m_ctrlEdit.ReplaceSel("\r\n");
	}

	// 3 - tempo di esecuzione //
	CString str3;
	if (dwMilliseconds > (DWORD)theApp.m_lShowDbQueriesThreshold)
		str3.Format("-- QUERY EXECUTION TIME: %li msec. !!!!!\r\n", dwMilliseconds);
	else
		str3.Format("-- QUERY EXECUTION TIME: %li msec.\r\n", dwMilliseconds);

	m_ctrlEdit.SetSel(0, 0);
	m_ctrlEdit.ReplaceSel(str3);

	// 2 - query //
	m_ctrlEdit.SetSel(0, 0);
	m_ctrlEdit.ReplaceSel("   " + strSQL + ";\r\n");

	// 1 - data, ora e numero operazione

	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);

	CString str1;
	if (dwDiff > (DWORD)theApp.m_lShowDbQueriesThreshold)
		str1.Format("-- %06li -- %02li/%02li/%04li %02li:%02li:%02li (%li msec. *****) -- %s --\r\n", m_lCounter + 1, SystemTime.wDay, SystemTime.wMonth, SystemTime.wYear, SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond, dwDiff, strComment);
	else
		str1.Format("-- %06li -- %02li/%02li/%04li %02li:%02li:%02li (%li msec.) -- %s --\r\n", m_lCounter + 1, SystemTime.wDay, SystemTime.wMonth, SystemTime.wYear, SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond, dwDiff, strComment);

	m_ctrlEdit.SetSel(0, 0);
	m_ctrlEdit.ReplaceSel(str1);

	//

	m_ctrlEdit.SetSel(0, 0);

	//

	m_lCounter++;
	m_dwLast = timeGetTime();
}