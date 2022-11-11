#include "stdafx.h"
#include "Endox.h"
#include "BrowserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CBrowserDlg, CResizableDialog)

CBrowserDlg::CBrowserDlg(CString strURL, CWnd* pParentWnd)
	: CResizableDialog(CBrowserDlg::IDD, pParentWnd)
{
	m_strURL = strURL;
}

BEGIN_MESSAGE_MAP(CBrowserDlg, CResizableDialog)

	ON_WM_SIZE()

END_MESSAGE_MAP()

void CBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_ctrlBrowser);
	DDX_Control(pDX, IDC_BROWSER_CTRL, m_ctrlBrowserCtrl);
}

BOOL CBrowserDlg::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	AddAnchor(IDC_BROWSER_CTRL, CSize(0,0), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(100,100), CSize(100, 100));

	m_ctrlBrowser.Navigate(m_strURL, NULL, NULL, NULL, NULL);
	// m_ctrlBrowser.get_Busy();

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	return TRUE;
}

void CBrowserDlg::OnSize(UINT nType, int cx, int cy)
{
	CResizableDialog::OnSize(nType, cx, cy);

	if (m_ctrlBrowserCtrl.GetSafeHwnd())
	{
		CRect rect;
		m_ctrlBrowserCtrl.GetWindowRect(&rect);
		ScreenToClient(&rect);
		m_ctrlBrowser.SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	}
}

UINT CBrowserDlg::Thread(LPVOID lpParam)
{
	CBrowserCtrl* pBrowser = (CBrowserCtrl*)lpParam;
	while(pBrowser->get_Busy())
		Sleep(10);
	pBrowser->GetParent()->PostMessage(WM_CLOSE);
	return 0;
}
