#include "stdafx.h"
#include "Endox.h"
#include "XmlViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CXmlViewerDlg, CEndoxResizableDlg)

CXmlViewerDlg::CXmlViewerDlg(CWnd* pParent, CString message, CString errorMessage, CStringList &warningList)
: CEndoxResizableDlg(CXmlViewerDlg::IDD, pParent)
{
	if (message != "")
	{
		m_sFileName = theApp.m_sDirProg + "\\temp.xml";

		HANDLE hFile = CreateFile(m_sFileName,
			GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_WRITE | FILE_SHARE_READ,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			theApp.AfxMessageBoxEndo("Impossibile creare il file!");
			return;
		}

		message.Replace("encoding=\"utf-16\"", "");
		DWORD dwBytesToWrite = message.GetLength();
		DWORD dwBytesWritten = 0;
		BOOL bResult = ::WriteFile(hFile, message, dwBytesToWrite, &dwBytesWritten, NULL);

		if (!bResult || (dwBytesToWrite != dwBytesWritten))
		{
			theApp.AfxMessageBoxEndo("Problemi di accesso al path");
			return;
		}

		CloseHandle(hFile);
	}
	else
		m_sFileName = "";

	m_sErrorMessage = errorMessage;

	POSITION pos = warningList.GetHeadPosition();
	while (pos)
	{
		CString temp = warningList.GetNext(pos);
		m_warningList.AddTail(temp);
	}

}

CXmlViewerDlg::~CXmlViewerDlg()
{
	::DeleteFile(m_sFileName);
}

BEGIN_MESSAGE_MAP(CXmlViewerDlg, CEndoxResizableDlg)
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CXmlViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);	

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnChiudi);
	DDX_Control(pDX, IDC_WEB_BROWSER, m_ctrlBrowser);
	DDX_Control(pDX, IDC_EDIT_ERRORS, m_ctrlErrors);
	DDX_Control(pDX, IDC_LIST_WARNINGS, m_ctrlWarningList);
}

BOOL CXmlViewerDlg::OnInitDialog()
{
	BOOL bReturn = CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_STATIC_2, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_1, CSize(0, 0), CSize(100, 50));
	AddAnchor(IDC_STATIC_3, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_EDIT_ERRORS, CSize(0, 50), CSize(100, 70));
	AddAnchor(IDC_STATIC_4, CSize(0, 70), CSize(100, 70));
	AddAnchor(IDC_LIST_WARNINGS, CSize(0, 70), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));	

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	if (m_sFileName != "")
		m_ctrlBrowser.Navigate(m_sFileName, NULL, NULL, NULL, NULL);

	m_ctrlErrors.SetWindowText(m_sErrorMessage);

	int iColumn = 0;
	m_ctrlWarningList.InsertColumn(iColumn++, "");
	m_ctrlWarningList.SetExtendedStyle(m_ctrlWarningList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);	

	POSITION pos = m_warningList.GetHeadPosition();
	while (pos)
	{
		CString temp = m_warningList.GetNext(pos);
		m_ctrlWarningList.InsertItem(m_ctrlWarningList.GetItemCount(), temp);
	}

	for (int h = 0; h<iColumn; h++)
		m_ctrlWarningList.SetColumnWidth(h, LVSCW_AUTOSIZE_USEHEADER);

	theApp.LocalizeDialog(this, CXmlViewerDlg::IDD, "XmlViewerDlg");
	return bReturn;
}

void CXmlViewerDlg::OnSize(UINT nType, int cx, int cy)
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	if (!m_ctrlBrowser.GetSafeHwnd())
		return;

	CRect rect;
	GetDlgItem(IDC_STATIC_1)->GetWindowRect(&rect);

	ScreenToClient(&rect);

	m_ctrlBrowser.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
}
