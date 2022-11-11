#include "stdafx.h"
#include "Endox.h"
#include "ToolbarChildDlg.h"
#include "ToolBarChild.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CToolbarChildDlg::CToolbarChildDlg(ToolbarChild_Orientation orientation, UINT iToolbarID, UINT iBitmapNormalID, UINT iBitmapDisabledID, CWnd* pParentWnd)
	: CDialog((UINT)0, pParentWnd)
{
	m_DialogTemplate.style				= WS_POPUP | WS_BORDER | DS_SETFONT; // 
	m_DialogTemplate.dwExtendedStyle    = WS_EX_DLGMODALFRAME;
	m_DialogTemplate.x					= 0;
	m_DialogTemplate.y					= 0;
	m_DialogTemplate.cx					= 0; // 4 horizontal units are the width of one character
	m_DialogTemplate.cy					= 0; // 8 vertical units are the height of one character
	m_DialogTemplate.cdit				= 0;  // nr of dialog items in the dialog

	m_pToolbar = new CToolBarChild(pParentWnd);
	
	m_orientation = orientation;
	m_iToolbarID = iToolbarID;
	m_iBitmapNormalID = iBitmapNormalID;
	m_iBitmapDisabledID = iBitmapDisabledID;

	m_bToolbarDestroying = FALSE;
}

CToolbarChildDlg::~CToolbarChildDlg(void)
{
	if (m_pToolbar)
		delete m_pToolbar;
}

BEGIN_MESSAGE_MAP(CToolbarChildDlg, CDialog)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

BOOL CToolbarChildDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_pToolbar->CreateEx(this, 
							   TBSTYLE_FLAT | TBSTYLE_TOOLTIPS | TBSTYLE_WRAPABLE, 
							   WS_CHILD | CBRS_ALIGN_TOP, 
							   CRect(0,0,0,0), 
							   m_iToolbarID))
		return FALSE;

	m_pToolbar->LoadToolBar(m_iToolbarID);
	m_pToolbar->LoadTCToolBar(m_iBitmapNormalID, m_iBitmapDisabledID);

	return TRUE;
}

void CToolbarChildDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if (nState == WA_INACTIVE && !m_bToolbarDestroying)
		m_pParentWnd->SendMessage(WM_DESTROY_TOOLBAR_CHILD);
}

BOOL CToolbarChildDlg::Create()
{
	// Get font info from mainwindow of the application
	CFont* pParentFont = m_pParentWnd->GetFont();
	if (pParentFont == NULL && AfxGetApp()->m_pActiveWnd != NULL) 
		pParentFont = AfxGetApp()->m_pActiveWnd->GetFont();

	LOGFONT LogFont;
	memset(&LogFont, 0x00, sizeof(LogFont));
	if (pParentFont == NULL) 
	{
		strcpy_s(LogFont.lfFaceName, "MS Sans Serif");
		LogFont.lfHeight = 8;
	}
	else 
		pParentFont->GetLogFont(&LogFont);

	//Prework for setting font in dialog...
	int cWC = MultiByteToWideChar(CP_ACP, 0, LogFont.lfFaceName, -1, NULL, 0);
	int nFontNameLen = cWC + 1;
	WCHAR *szFontName = new WCHAR[nFontNameLen];
	// Copy the string
	MultiByteToWideChar(CP_ACP, 0, LogFont.lfFaceName, -1, (LPWSTR) szFontName, cWC);
	szFontName[cWC] = 0;
	nFontNameLen = (cWC) * sizeof(WCHAR);

	m_wFontSize = (unsigned short)LogFont.lfHeight;
	
	//Prework for setting caption in dialog...
	cWC = MultiByteToWideChar(CP_ACP, 0, m_strCaption, -1, NULL, 0);
	int szBoxLen = cWC + 1;
	WCHAR *szBoxCaption = new WCHAR[szBoxLen];
	// Copy the string
	MultiByteToWideChar(CP_ACP, 0, m_strCaption, -1, (LPWSTR) szBoxCaption, cWC);
	szBoxCaption[cWC] = 0;
	szBoxLen = (cWC) * sizeof(WCHAR);

	int nBufferSize =  sizeof(DLGTEMPLATE) + (2 * sizeof(WORD)) + szBoxLen + sizeof(WORD) + nFontNameLen;

	HLOCAL hLocal = LocalAlloc(LHND, nBufferSize);
	if (hLocal == NULL) 
	{
		AfxMessageBox("CDynDialogEx::DoModal() : LocalAllock Failed");
		return FALSE;
	}

	BYTE* pBuffer = (BYTE*)LocalLock(hLocal);
	if (pBuffer == NULL) 
	{
		LocalFree(hLocal);
		AfxMessageBox("CDynDialogEx::DoModal() : LocalLock Failed");
	}

	BYTE *pdest = pBuffer;
	// transfer DLGTEMPLATE structure to the buffer
	memcpy(pdest, &m_DialogTemplate, sizeof(DLGTEMPLATE));	// DLGTemplate

	pdest += sizeof(DLGTEMPLATE);
	*(WORD*)pdest = 0;	     // no menu
	pdest += sizeof(WORD);	 // Increment
	*(WORD*)(pdest + 1) = 0; // use default window class
	pdest += sizeof(WORD);	 // Increment

	memcpy(pdest, szBoxCaption, szBoxLen);	// Caption
	pdest += szBoxLen;

	*(WORD*)pdest = m_wFontSize; // font size
	pdest += sizeof(WORD);
	memcpy(pdest, szFontName, nFontNameLen); // font name
	pdest += nFontNameLen;

	ASSERT(pdest - pBuffer == nBufferSize);

	//Next lines to make sure that MFC makes no ASSERTION when PREVIOUS/NEXT is pressed:)
	if (m_lpDialogTemplate != NULL) 
		m_lpDialogTemplate = NULL;

	BOOL bRet = CreateIndirect((LPDLGTEMPLATE)pBuffer, m_pParentWnd);

	LocalUnlock(hLocal);
	LocalFree(hLocal);

	delete [] szBoxCaption;
	delete [] szFontName;
	return bRet;
}

VOID CToolbarChildDlg::ResizeDlg(POINT* pPoint)
{
	CSize szToolbarSpace = m_pToolbar->CalcDynamicLayout(1600, LM_HORZ | LM_COMMIT);

	CRect rectBorders;
	GetWindowRect(&rectBorders);

	CRect rectWnd;
	CSize szToolbar;
	
	switch (m_orientation)
	{
		case left:
			rectWnd.left   = pPoint->x - szToolbarSpace.cx - rectBorders.Width();
			rectWnd.top    = pPoint->y - szToolbarSpace.cy - rectBorders.Height();
			rectWnd.right  = pPoint->x;
			rectWnd.bottom = pPoint->y;
			szToolbar = szToolbarSpace;
			break;

		case top:
			rectWnd.left   = pPoint->x;
			rectWnd.top    = pPoint->y - szToolbarSpace.cx - rectBorders.Height();
			rectWnd.right  = pPoint->x + szToolbarSpace.cy + rectBorders.Width();
			rectWnd.bottom = pPoint->y;
			szToolbar.cx = szToolbarSpace.cy;
			szToolbar.cy = szToolbarSpace.cx;
			break;

		case right:
			rectWnd.left   = pPoint->x;
			rectWnd.top    = pPoint->y;
			rectWnd.right  = rectWnd.left + szToolbarSpace.cx + rectBorders.Width();
			rectWnd.bottom = rectWnd.top + szToolbarSpace.cy + rectBorders.Height();
			szToolbar = szToolbarSpace;
			break;

		case bottom:
			rectWnd.left   = pPoint->x;
			rectWnd.top    = pPoint->y;
			rectWnd.right  = rectWnd.left + szToolbarSpace.cy + rectBorders.Width();
			rectWnd.bottom = rectWnd.top + szToolbarSpace.cx + rectBorders.Height();
			szToolbar.cx = szToolbarSpace.cy;
			szToolbar.cy = szToolbarSpace.cx;
			break;
	}
	
	SetWindowPos(NULL, 
			     rectWnd.left, 
				 rectWnd.top, 
				 rectWnd.Width(), 
				 rectWnd.Height(), 
				 SWP_NOZORDER);

	m_pToolbar->SetWindowPos(NULL, 
			                 0, 
							 0, 
							 szToolbar.cx, 
							 szToolbar.cy, 
							 SWP_NOZORDER);

	m_pToolbar->ShowWindow(SW_SHOW);
}

VOID CToolbarChildDlg::ViewWithTransiction(UINT percTransparency)
{
	SetTransparency(percTransparency);
	StartTransitionEffect();
	SetFocus();
}

VOID CToolbarChildDlg::StartTransitionEffect()
{
	DWORD dwFlags = AW_SLIDE;
	switch (m_orientation)
	{
		case left:
		case top : 
			dwFlags |= AW_VER_NEGATIVE; 
			break;

		case right:
		case bottom:
			dwFlags |= AW_HOR_POSITIVE; 
			break;
	}

	::AnimateWindow(GetSafeHwnd(), 100, dwFlags);
}

VOID CToolbarChildDlg::SetTransparency(UINT percentage)
{
	#ifndef WS_EX_LAYERED
	#define WS_EX_LAYERED           0x00080000
	#endif 

	// Set WS_EX_LAYERED on this window
	SetWindowLong(GetSafeHwnd(),
				  GWL_EXSTYLE,
				  GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);

	::SetLayeredWindowAttributes(GetSafeHwnd(), 
							     0, 
								 (255 * percentage) / 100,
							     LWA_ALPHA);
}