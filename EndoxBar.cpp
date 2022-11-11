#include "stdafx.h"
#include "Endox.h"
#include "EndoxBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoxBar, CToolBar)

CEndoxBar::CEndoxBar()
{
}

CEndoxBar::~CEndoxBar()
{
}

BEGIN_MESSAGE_MAP(CEndoxBar, CToolBar)
	ON_NOTIFY_EX(TTN_NEEDTEXTW, 0, OnToolTipNotify)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

void CEndoxBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (nFlags == MK_LBUTTON)
		CToolBar::OnLButtonDown(nFlags, point);
}

void CEndoxBar::OnRButtonDown(UINT nFlags, CPoint point)
{
}

BOOL CEndoxBar::OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
    ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

    // if there is a top level routing frame then let it handle the message
    if (GetRoutingFrame() != NULL) return FALSE;

    // to be thorough we will need to handle UNICODE versions of the message also !!
    TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
    TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
    CString strTipText;
    UINT nID = UINT(pNMHDR->idFrom);

    if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
        pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
    {
        // idFrom is actually the HWND of the tool 
		nID = ::GetDlgCtrlID(pNMHDR->hwndFrom);
    }

    if (nID != 0) // will be zero on a separator
    {
		strTipText = theApp.GetMessageString(nID);

#ifndef _UNICODE
        if (pNMHDR->code == TTN_NEEDTEXTA)
        {
			strTipText = strTipText.Left(sizeof(pTTTA->szText) - 1);
			lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
        }
        else
        {
			strTipText = strTipText.Left((sizeof(pTTTW->szText) / 2) - 1);
            _mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
        }
#else
        if (pNMHDR->code == TTN_NEEDTEXTA)
        {
            _wcstombsz(pTTTA->szText, strTipText,sizeof(pTTTA->szText));
        }
        else
        {
            lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
        }
#endif

        *pResult = 0;

        // bring the tooltip window above other popup windows
        ::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
            SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER);
        
        return TRUE;
    }

    return FALSE;
}


BOOL CEndoxBar::Attach(WINDOWPLACEMENT& wpl)
{	
	CRect rect(wpl.rcNormalPosition);

	// Calculate the size of new layout
	CSize size = CalcFixedLayout(FALSE, rect.Width() > rect.Height());

	wpl.rcNormalPosition.bottom = wpl.rcNormalPosition.top + size.cy;
	wpl.rcNormalPosition.right  = wpl.rcNormalPosition.left + size.cx;

	return SetWindowPlacement(&wpl);
}

BOOL CEndoxBar::CreateEx(CWnd* pParentWnd, CWnd* pFrameWnd, UINT uiToolBar, UINT uiBitmapNormal, UINT uiBitmapHot, UINT uiBitmapDisabled)
{
	DWORD dwCtrlStyle = TBSTYLE_FLAT | TBSTYLE_TOOLTIPS;

	WINDOWPLACEMENT wpl;
	wpl.length = sizeof(WINDOWPLACEMENT);

	CRect rectFrame;
	pFrameWnd->GetWindowRect(rectFrame);

	if (rectFrame.Height() > rectFrame.Width())
		dwCtrlStyle = (dwCtrlStyle | TBSTYLE_WRAPABLE);

	if (CToolBar::CreateEx(pParentWnd, dwCtrlStyle, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, CRect(0, 0, 0, 0), AFX_IDW_TOOLBAR) == FALSE)
		return FALSE;

	if (LoadToolBar(uiToolBar) == FALSE)
		return FALSE;

	if (LoadTCToolBar(uiBitmapNormal, uiBitmapHot, uiBitmapDisabled) == FALSE)
		return FALSE;

	pFrameWnd->GetWindowPlacement(&wpl);
	Attach(wpl);

	ShowWindow(SW_SHOW);

	return TRUE;
}

BOOL CEndoxBar::LoadTCToolBar(UINT uToolBar,
							UINT uToolBarHot,
							UINT uToolBarDisabled)
{
	//Set the normal bitmap of the toolbar
	if (uToolBar && !SetTCToolBar(TB_SETIMAGELIST, uToolBar))
		return FALSE;
	
	//Set the evidence bitmap of the toolbar
	if (uToolBarHot && !SetTCToolBar(TB_SETHOTIMAGELIST, uToolBarHot))
		return FALSE;
	
	//Set the disabled bitmap of the toolbar
	if (uToolBarDisabled && !SetTCToolBar(TB_SETDISABLEDIMAGELIST, uToolBarDisabled))
		return FALSE;

	return TRUE;
}

BOOL CEndoxBar::SetTCToolBar(UINT uToolBarType,
						   UINT uToolBar)
{
	CImageList	imageList;
	CBitmap		bitmap;
	BITMAP		bmBitmap;
	
	//Create bitmap image from resource integer, whith 
	//background color set by [0,0] pixel of bitmap
	if (!bitmap.Attach(LoadImage(AfxGetInstanceHandle(),
								 MAKEINTRESOURCE(uToolBar),
								 IMAGE_BITMAP, 0, 0,
		                         LR_LOADTRANSPARENT | LR_DEFAULTSIZE | LR_CREATEDIBSECTION)) ||
		!bitmap.GetBitmap(&bmBitmap))
		return FALSE;
	
	CSize size(bmBitmap.bmWidth, bmBitmap.bmHeight);
	if (size.cy == 0)
		return FALSE;
	
	//Calculate button amount, escluiding separator buttons
	int nBtnCount = 0;
	for(int nBtn = 0; nBtn < GetToolBarCtrl().GetButtonCount(); nBtn++)
		if ((GetButtonStyle(nBtn) & TBBS_SEPARATOR) == 0)
			nBtnCount++;

	if (nBtnCount == 0)
		return FALSE;
	
	//calculate button width. Button height is the height 
	//of bitmap
	int nBtnWidth = size.cx / nBtnCount;
	if (!imageList.Create(nBtnWidth, size.cy, ILC_COLOR32 | ILC_MASK, nBtnCount, 0))
		return FALSE;
	RGBTRIPLE* pTriple = (RGBTRIPLE*)bmBitmap.bmBits;
	//Create image list with white mask
	if (imageList.Add(&bitmap, RGB(pTriple[0].rgbtRed, pTriple[0].rgbtGreen, pTriple[0].rgbtBlue)) == -1)
		return FALSE;
	
	//Set image list
	if (uToolBarType == TB_SETIMAGELIST)
		GetToolBarCtrl().SetImageList(&imageList);
	else if (uToolBarType == TB_SETHOTIMAGELIST)
		GetToolBarCtrl().SetHotImageList(&imageList);
	else if (uToolBarType == TB_SETDISABLEDIMAGELIST)
		GetToolBarCtrl().SetDisabledImageList(&imageList);
	else 
		return FALSE;
	
	//Detach image list and bitmap. If you not remove theese
	//image is not created becuse image list is destroyed 
	//before is it displayed
	imageList.Detach(); 
	bitmap.Detach();	
	return TRUE;
}

void CEndoxBar::DeleteButton(UINT id)
{
	if (!GetSafeHwnd())
		return;

	for(int i = 0; i < GetToolBarCtrl().GetButtonCount(); i++)
	{
		TBBUTTON button;
		if (GetToolBarCtrl().GetButton(i, &button) && button.idCommand == id)
			GetToolBarCtrl().DeleteButton(i);
	}
}