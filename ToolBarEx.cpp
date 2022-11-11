#include "stdafx.h"
#include "Endox.h"
#include "ToolBarEx.h"

#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CToolBarEx, CToolBar)

CToolBarEx::CToolBarEx()
{
	m_rgbColorMask = RGB(192, 0, 192);
	m_pChildToolbarDlg = NULL;
}

CToolBarEx::~CToolBarEx()
{
	DestroyChildToolbar();
}

BEGIN_MESSAGE_MAP(CToolBarEx, CToolBar)
	ON_MESSAGE(WM_DESTROY_TOOLBAR_CHILD, OnDestroyToolbarChild)
	ON_MESSAGE(WM_TOOLBAR_PRESS_BUTTON, OnToolbarPressButton)
	ON_MESSAGE(WM_TOOLBAR_UPDATE_COMMAND_UI, OnUpdateCommandUI)
	ON_NOTIFY_EX(TTN_NEEDTEXTW, 0, OnToolTipNotify)
	ON_CONTROL_REFLECT(0, OnCommandUI)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CToolBarEx message handlers

void CToolBarEx::OnDestroy()
{
	CToolBar::OnDestroy();
}

void CToolBarEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (nFlags == MK_LBUTTON && !CreateChildToolbar(point))
		CToolBar::OnLButtonDown(nFlags, point);
}

void CToolBarEx::OnRButtonDown(UINT nFlags, CPoint point)
{
}

LRESULT CToolBarEx::OnDestroyToolbarChild(WPARAM wParam, LPARAM lParam)
{
	DestroyChildToolbar();
	return 0;
}

BOOL CToolBarEx::CreateChildToolbar(CPoint point)
{
	if (m_pChildToolbarDlg)
		return FALSE;

	int iButton = -1;
	for (int i = 0; i < GetToolBarCtrl().GetButtonCount(); i++)
	{
		CRect rc;
		GetItemRect(i, &rc);
		if (rc.PtInRect(point))
		{
			iButton = i;
			break;
		}
	}

	if (iButton == -1)
		return FALSE;

	UINT iButtonPressedID = GetItemID(iButton);
	if (iButtonPressedID == 0)
		return FALSE;

	if (!GetToolBarCtrl().IsButtonEnabled(iButtonPressedID))
		return FALSE;

	tagChildToolbar ChildToolbarInfo;
	ZeroMemory(&ChildToolbarInfo, sizeof(tagChildToolbar));
	for (POSITION pos = m_listChildToolbars.GetHeadPosition(); pos;)
	{
		tagChildToolbar ct = m_listChildToolbars.GetNext(pos);
		if (ct.iParentButtonID == iButtonPressedID)
			ChildToolbarInfo = ct;
	}

	if (ChildToolbarInfo.iToolbarChildID == 0)
		return FALSE;

	m_pChildToolbarDlg = new CToolbarChildDlg(ChildToolbarInfo.orientation, 
		                                      ChildToolbarInfo.iToolbarChildID, 
											  ChildToolbarInfo.iBitmapNormalID, 
											  ChildToolbarInfo.iBitmapDisabledID, 
											  this);
	if (!m_pChildToolbarDlg->Create())
	{
		delete m_pChildToolbarDlg;
		m_pChildToolbarDlg = NULL;
		return FALSE;
	}

	CRect rectToolbar;
	GetWindowRect(&rectToolbar);

	CRect rectButton;
	GetItemRect(iButton, &rectButton);

	POINT ptStartChildDlg;
	switch (ChildToolbarInfo.orientation)
	{
		case CToolbarChildDlg::left:
			// Rispetto al pulsante vertice basso sx
			if (rectToolbar.Width() > rectToolbar.Height())
			{
				ptStartChildDlg.x = rectToolbar.left + rectButton.left;
				ptStartChildDlg.y = rectToolbar.bottom;
			}
			else
			{
				ptStartChildDlg.x = rectToolbar.left;
				ptStartChildDlg.y = rectToolbar.top + rectButton.bottom;
			}
			break;

		case CToolbarChildDlg::top:
			// Rispetto al pulsante vertice alto sx
			if (rectToolbar.Width() > rectToolbar.Height())
			{
				ptStartChildDlg.x = rectToolbar.left + rectButton.left;
				ptStartChildDlg.y = rectToolbar.top;
			}
			else
			{
				ptStartChildDlg.x = rectToolbar.left;
				ptStartChildDlg.y = rectToolbar.top + rectButton.top;
			}
			break;

		case CToolbarChildDlg::right:
			// Rispetto al pulsante vertice alto dx
			if (rectToolbar.Width() > rectToolbar.Height())
			{
				ptStartChildDlg.x = rectToolbar.left + rectButton.right;
				ptStartChildDlg.y = rectToolbar.top;
			}
			else
			{
				ptStartChildDlg.x = rectToolbar.right;
				ptStartChildDlg.y = rectToolbar.top + rectButton.top;
			}
			break;

		case CToolbarChildDlg::bottom:
			// Rispetto al pulsante vertice basso sx
			if (rectToolbar.Width() > rectToolbar.Height())
			{
				ptStartChildDlg.x = rectToolbar.left + rectButton.left;
				ptStartChildDlg.y = rectToolbar.bottom;
			}
			else
			{
				ptStartChildDlg.x = rectToolbar.left;
				ptStartChildDlg.y = rectToolbar.top + rectButton.bottom;
			}
			break;
	}

	m_pChildToolbarDlg->ResizeDlg(&ptStartChildDlg);
	m_pChildToolbarDlg->ViewWithTransiction(100);
	return TRUE;
}

BOOL CToolBarEx::CreateChildToolbar(UINT nParentID)
{
	if (m_pChildToolbarDlg)
		return FALSE;

	int iButton = -1;
	for (int i = 0; i < GetToolBarCtrl().GetButtonCount(); i++)
		if (GetItemID(i) == nParentID)
		{
			iButton = i;
			break;
		}

	if (iButton < 0)
		return FALSE;

	tagChildToolbar ChildToolbarInfo;
	ZeroMemory(&ChildToolbarInfo, sizeof(tagChildToolbar));
	for (POSITION pos = m_listChildToolbars.GetHeadPosition(); pos;)
	{
		tagChildToolbar ct = m_listChildToolbars.GetNext(pos);
		if (ct.iParentButtonID == nParentID)
			ChildToolbarInfo = ct;
	}

	if (ChildToolbarInfo.iToolbarChildID == 0)
		return FALSE;

	m_pChildToolbarDlg = new CToolbarChildDlg(ChildToolbarInfo.orientation, 
		                                      ChildToolbarInfo.iToolbarChildID, 
											  ChildToolbarInfo.iBitmapNormalID, 
											  ChildToolbarInfo.iBitmapDisabledID, 
											  this);
	if (!m_pChildToolbarDlg->Create())
	{
		delete m_pChildToolbarDlg;
		m_pChildToolbarDlg = NULL;
		return FALSE;
	}

	CRect rectToolbar;
	GetWindowRect(&rectToolbar);

	CRect rectButton;
	GetItemRect(iButton, &rectButton);

	POINT ptStartChildDlg;
	switch (ChildToolbarInfo.orientation)
	{
		case CToolbarChildDlg::left:
			// Rispetto al pulsante vertice basso sx
			if (rectToolbar.Width() > rectToolbar.Height())
			{
				ptStartChildDlg.x = rectToolbar.left + rectButton.left;
				ptStartChildDlg.y = rectToolbar.bottom;
			}
			else
			{
				ptStartChildDlg.x = rectToolbar.left;
				ptStartChildDlg.y = rectToolbar.top + rectButton.bottom;
			}
			break;

		case CToolbarChildDlg::top:
			// Rispetto al pulsante vertice alto sx
			if (rectToolbar.Width() > rectToolbar.Height())
			{
				ptStartChildDlg.x = rectToolbar.left + rectButton.left;
				ptStartChildDlg.y = rectToolbar.top;
			}
			else
			{
				ptStartChildDlg.x = rectToolbar.left;
				ptStartChildDlg.y = rectToolbar.top + rectButton.top;
			}
			break;

		case CToolbarChildDlg::right:
			// Rispetto al pulsante vertice alto dx
			if (rectToolbar.Width() > rectToolbar.Height())
			{
				ptStartChildDlg.x = rectToolbar.left + rectButton.right;
				ptStartChildDlg.y = rectToolbar.top;
			}
			else
			{
				ptStartChildDlg.x = rectToolbar.right;
				ptStartChildDlg.y = rectToolbar.top + rectButton.top;
			}
			break;

		case CToolbarChildDlg::bottom:
			// Rispetto al pulsante vertice basso sx
			if (rectToolbar.Width() > rectToolbar.Height())
			{
				ptStartChildDlg.x = rectToolbar.left + rectButton.left;
				ptStartChildDlg.y = rectToolbar.bottom;
			}
			else
			{
				ptStartChildDlg.x = rectToolbar.left;
				ptStartChildDlg.y = rectToolbar.top + rectButton.bottom;
			}
			break;
	}

	m_pChildToolbarDlg->ResizeDlg(&ptStartChildDlg);
	m_pChildToolbarDlg->ViewWithTransiction(70);

	return TRUE;
}


void CToolBarEx::CToolCmdUI::Enable(BOOL bOn)
{
	m_bEnableChanged = TRUE;
	CToolBar* pToolBar = (CToolBar*)m_pOther;
	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CToolBar, pToolBar);
	ASSERT(m_nIndex < m_nIndexMax);

	UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) & ~TBBS_DISABLED;
	if (!bOn)
	{
		nNewStyle |= TBBS_DISABLED;
		// WINBUG: If a button is currently pressed and then is disabled
		// COMCTL32.DLL does not unpress the button, even after the mouse
		// button goes up!  We work around this bug by forcing TBBS_PRESSED
		// off when a button is disabled.
		nNewStyle &= ~TBBS_PRESSED;
	}
	ASSERT(!(nNewStyle & TBBS_SEPARATOR));
	pToolBar->SetButtonStyle(m_nIndex, nNewStyle);
}

void CToolBarEx::CToolCmdUI::SetCheck(int nCheck)
{
	ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate
	CToolBar* pToolBar = (CToolBar*)m_pOther;
	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CToolBar, pToolBar);
	ASSERT(m_nIndex < m_nIndexMax);

	UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
				~(TBBS_CHECKED | TBBS_INDETERMINATE);
	if (nCheck == 1)
		nNewStyle |= TBBS_CHECKED;
	else if (nCheck == 2)
		nNewStyle |= TBBS_INDETERMINATE;
	ASSERT(!(nNewStyle & TBBS_SEPARATOR));
	pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);
}

void CToolBarEx::CToolCmdUI::SetText(LPCTSTR)
{
	// ignore it
}

void CToolBarEx::OnCommandUI()
{
	SendMessage(WM_TOOLBAR_PRESS_BUTTON, GetCurrentMessage()->wParam);
}

void CToolBarEx::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	if (m_pChildToolbarDlg && m_pChildToolbarDlg->GetSafeHwnd())
		m_pChildToolbarDlg->SendMessageToDescendants(WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0, TRUE, TRUE);

	CToolCmdUI state;
	state.m_pOther = this;

	state.m_nIndexMax = (UINT)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++)
	{
		// get buttons state
		TBBUTTON button;
		VERIFY(DefWindowProc(TB_GETBUTTON, state.m_nIndex, (LPARAM)&button));
		button.fsState ^= TBSTATE_ENABLED;
		state.m_nID = button.idCommand;

		// ignore separators
		if (!(button.fsStyle & TBSTYLE_SEP))
		{
			// allow reflections
			if (CWnd::OnCmdMsg(0, 
				               MAKELONG(CN_UPDATE_COMMAND_UI&0xff, WM_COMMAND+WM_REFLECT_BASE), 
				               &state, 
				               NULL))
				continue;

			// allow the toolbar itself to have update handlers
			if (OnCmdMsg(state.m_nID, CN_UPDATE_COMMAND_UI, &state, NULL))
				continue;

			// allow the owner to process the update
			state.DoUpdate(pTarget, bDisableIfNoHndler);
		}
	}

	// update the dialog controls added to the toolbar
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

BOOL CToolBarEx::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (nCode == CN_UPDATE_COMMAND_UI)
	{
		SendMessage(WM_TOOLBAR_UPDATE_COMMAND_UI, 0, (LPARAM)pExtra);
		return TRUE;
	}
	return CToolBar::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CToolBarEx::OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
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
            lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
        }
        else
        {
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

void CToolBarEx::Attach(UINT id, CWnd* pParentWnd)
{	
	WINDOWPLACEMENT wpl;
	wpl.length = sizeof(WINDOWPLACEMENT);
	pParentWnd->GetDlgItem(id)->GetWindowPlacement(&wpl);
	
	CRect rect(wpl.rcNormalPosition);

	//Calculate the size of new layout
	CSize size = CalcFixedLayout(FALSE, rect.Width() > rect.Height());

	// wpl.rcNormalPosition.bottom = wpl.rcNormalPosition.top + size.cy;
	// wpl.rcNormalPosition.right  = wpl.rcNormalPosition.left + size.cx;

	wpl.rcNormalPosition.top = 0;
	wpl.rcNormalPosition.bottom = size.cy;
	wpl.rcNormalPosition.left = 0;
	wpl.rcNormalPosition.right  = size.cx;

	SetWindowPlacement(&wpl);

	pParentWnd->GetDlgItem(id)->ShowWindow(SW_HIDE);
	ShowWindow(SW_SHOW);
}

void CToolBarEx::AttachEx(UINT id, CWnd* pParentWnd)
{
	CRect rect;
	pParentWnd->GetDlgItem(id)->GetWindowRect(&rect);
	pParentWnd->ScreenToClient(&rect);

	CSize size = CalcDynamicLayout(rect.Width(), LM_HORZ | LM_COMMIT);

	if (rect.Width() > rect.Height())
		SetWindowPos(NULL, rect.left, rect.top, size.cx, size.cy, SWP_NOZORDER | SWP_SHOWWINDOW);
	else
		SetWindowPos(NULL, rect.left, rect.top, size.cy + 1, size.cx, SWP_NOZORDER | SWP_SHOWWINDOW);
}

BOOL CToolBarEx::LoadTCToolBar(UINT iBitmapNormalID, UINT iBitmapDisabledID)
{
	//Set the normal bitmap of the toolbar
	if (iBitmapNormalID && !SetTCToolBar(TB_SETIMAGELIST, iBitmapNormalID))
		return FALSE;
	
	//Set the disabled bitmap of the toolbar
	if (iBitmapDisabledID && !SetTCToolBar(TB_SETDISABLEDIMAGELIST, iBitmapDisabledID))
		return FALSE;

	return TRUE;
}

struct CToolBarData
{
	WORD wVersion;
	WORD wWidth;
	WORD wHeight;
	WORD wItemCount;
	//WORD aItems[wItemCount]

	WORD* items()
		{ return (WORD*)(this+1); }
};

BOOL CToolBarEx::LoadToolBar(UINT iResourceName)
{
	return LoadToolBar(MAKEINTRESOURCE(iResourceName));
}

BOOL CToolBarEx::LoadToolBar(LPCTSTR lpszResourceName)
{
	ASSERT_VALID(this);
	ASSERT(lpszResourceName != NULL);

	// determine location of the bitmap in resource fork
	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, RT_TOOLBAR);
	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
	if (hRsrc == NULL)
		return FALSE;

	HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
		return FALSE;

	CToolBarData* pData = (CToolBarData*)LockResource(hGlobal);
	if (pData == NULL)
		return FALSE;
	ASSERT(pData->wVersion == 1);

	UINT* pItems = new UINT[pData->wItemCount];
	for (int i = 0; i < pData->wItemCount; i++)
		pItems[i] = pData->items()[i];
	BOOL bResult = SetButtons(pItems, pData->wItemCount);
	delete[] pItems;

	if (bResult)
	{
		// set new sizes of the buttons
		CSize sizeImage(pData->wWidth, pData->wHeight);
		CSize sizeButton(pData->wWidth + 7, pData->wHeight + 7);
		SetSizes(sizeButton, sizeImage);

		// load bitmap now that sizes are known by the toolbar control
		bResult = TRUE; //LoadBitmap(lpszResourceName);
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return bResult;
}

BOOL CToolBarEx::SetTCToolBar(UINT uToolBarType, UINT uToolBar)
{
	CBitmap		bitmap;
	BITMAP		bmBitmap;
	
	//Create bitmap image from resource integer, whith 
	//background color set by [0,0] pixel of bitmap

	HANDLE hImage = LoadImage(AfxGetInstanceHandle(),
							  MAKEINTRESOURCE(uToolBar),
							  IMAGE_BITMAP, 0, 0,
		                      LR_DEFAULTSIZE | LR_CREATEDIBSECTION);

	if (!bitmap.Attach(hImage))
		return FALSE;
	
	if (!bitmap.GetBitmap(&bmBitmap))
		return FALSE;
	
	CSize size(bmBitmap.bmWidth, bmBitmap.bmHeight);
	if (size.cy == 0)
		return FALSE;
	
	//Calculate button amount, escluiding separator buttons
	int nBtnCount = 0;
	for(int nBtn = 0; nBtn < GetToolBarCtrl().GetButtonCount(); nBtn++)
		if((GetButtonStyle(nBtn) & TBBS_SEPARATOR) == 0)
			nBtnCount++;

	if(nBtnCount == 0)
		return FALSE;
	
	CImageList*	pImageList = NULL;
	if (uToolBarType == TB_SETIMAGELIST)
		pImageList = &m_ImageList;
	else if (uToolBarType == TB_SETHOTIMAGELIST)
		pImageList = &m_HotImageList;
	else if (uToolBarType == TB_SETDISABLEDIMAGELIST)
		pImageList = &m_DisabledImageList;
	else
		ASSERT(FALSE);

	ASSERT(pImageList->GetSafeHandle() == NULL);

	//calculate button width. Button height is the height 
	//of bitmap
	int nBtnWidth = size.cx / nBtnCount;
	if (!pImageList->Create(nBtnWidth, size.cy, ILC_COLOR24 | ILC_MASK, nBtnCount, 0))
		return FALSE;
	
	//Create image list whith white mask
	if (pImageList->Add(&bitmap, m_rgbColorMask) == -1)
		return FALSE;
	
	//pImageList->SetBkColor(GetSysColor(COLOR_3DFACE));

	//Set image list
	if (uToolBarType == TB_SETIMAGELIST)
		GetToolBarCtrl().SetImageList(pImageList);
	else if (uToolBarType == TB_SETHOTIMAGELIST)
		GetToolBarCtrl().SetHotImageList(pImageList);
	else if (uToolBarType == TB_SETDISABLEDIMAGELIST)
		GetToolBarCtrl().SetDisabledImageList(pImageList);
	else 
		return FALSE;
	
	//Detach image list and bitmap. If you not remove theese
	//image is not created becuse image list is destroyed 
	//before is it displayed

	HGDIOBJ hBitmap = bitmap.Detach();
	DeleteObject(hBitmap);
	return TRUE;
}

void CToolBarEx::DeleteButton(UINT id, BOOL bDeleteSeparatorAfter)
{
	if (!GetSafeHwnd())
		return;

	for (int i = 0; i < GetToolBarCtrl().GetButtonCount(); i++)
	{
		TBBUTTON button;
		if (GetToolBarCtrl().GetButton(i, &button) && button.idCommand == id)
		{
			GetToolBarCtrl().DeleteButton(i);
			if (bDeleteSeparatorAfter)
			{
				if (GetToolBarCtrl().GetButton(i, &button) && button.idCommand == 0)
					GetToolBarCtrl().DeleteButton(i);
			}
			break;
		}
	}
}

void CToolBarEx::DestroyChildToolbar()
{
	if (m_pChildToolbarDlg)
	{
		m_pChildToolbarDlg->m_bToolbarDestroying = TRUE;
		if (m_pChildToolbarDlg->GetSafeHwnd())
			m_pChildToolbarDlg->DestroyWindow();
		delete m_pChildToolbarDlg;
		m_pChildToolbarDlg = NULL;
	}
}

void CToolBarEx::AddChildToolbar(UINT iParentButtonID, CToolbarChildDlg::ToolbarChild_Orientation orientation, UINT iToolbarChildID, UINT iBitmapNormalID, UINT iBitmapDisabledID)
{
	tagChildToolbar ct;
	ct.iParentButtonID   = iParentButtonID;
	ct.orientation       = orientation;
	ct.iToolbarChildID   = iToolbarChildID;
	ct.iBitmapNormalID   = iBitmapNormalID;
	ct.iBitmapDisabledID = iBitmapDisabledID;
	m_listChildToolbars.AddTail(ct);
}
