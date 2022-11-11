#include "stdafx.h"
#include "Endox.h"
#include "PazienteCronicoDxListCtrl.h"

#include "PazienteCronicoSnListCtrl.h"

#define RGB_HIGHLIGHT RGB(255, 255, 0)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPazienteCronicoDxListCtrl, CListCtrl)

CPazienteCronicoDxListCtrl::CPazienteCronicoDxListCtrl()
	: CListCtrl()
{
	m_pBindedListCtrl = NULL;
	m_iItemHeight = 0;
	m_bWheelNotify = TRUE;
}

CPazienteCronicoDxListCtrl::~CPazienteCronicoDxListCtrl()
{
	RemoveAllCellColor();
}

BEGIN_MESSAGE_MAP(CPazienteCronicoDxListCtrl, CListCtrl)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_VSCROLL()

	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()

void CPazienteCronicoDxListCtrl::SetBindedListCtrl(CPazienteCronicoSnListCtrl* pList)
{
	m_pBindedListCtrl = pList;
}

void CPazienteCronicoDxListCtrl::SetItemHeight(int iItemHeight)
{
	m_iItemHeight = iItemHeight;
}

void CPazienteCronicoDxListCtrl::OnDestroy()
{
	DeleteAllItems();
	CListCtrl::OnDestroy();
}

BOOL CPazienteCronicoDxListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
    HD_NOTIFY* pHDN = (HD_NOTIFY*)lParam;

    if ((pHDN->hdr.code == HDN_BEGINTRACKW || pHDN->hdr.code == HDN_BEGINTRACKA || pHDN->hdr.code == HDN_DIVIDERDBLCLICKA || pHDN->hdr.code == HDN_DIVIDERDBLCLICKW) && (pHDN->iItem == 0 || pHDN->iItem == 1)) // Prevent only first (col# 0) from resizing
    {
		*pResult = TRUE; // disable tracking
		return TRUE; // Processed message
    }

    return CListCtrl::OnNotify(wParam, lParam, pResult);
}

void CPazienteCronicoDxListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    switch(nChar)
	{
		case VK_UP:
        case VK_DOWN:
        case VK_LEFT:
        case VK_RIGHT:
        case VK_HOME:
        case VK_END:
        case VK_PRIOR:
        case VK_NEXT:
		{
            break;
		}
		default:
		{
			CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
			break;
		}
	}
}

BOOL CPazienteCronicoDxListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL bReturn = CListCtrl::OnMouseWheel(nFlags, zDelta, pt);

	if (m_pBindedListCtrl && m_bWheelNotify)
	{
		WPARAM wParam = MAKEWPARAM(nFlags, zDelta);
		LPARAM lParam = MAKELPARAM(pt.x, pt.y);
		m_pBindedListCtrl->SetWheelNotify(FALSE);
		m_pBindedListCtrl->SendMessage(WM_MOUSEWHEEL, wParam, lParam);
		m_pBindedListCtrl->SetWheelNotify(TRUE);
	}

	return bReturn;
}

void CPazienteCronicoDxListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if ((nSBCode / 256 == SB_THUMBTRACK) || ((nSBCode & 0xFF) == SB_THUMBTRACK) || (nSBCode / 256 == SB_THUMBPOSITION) || ((nSBCode & 0xFF) == SB_THUMBPOSITION))
	{
		SCROLLINFO sinfo;
        sinfo.cbSize=sizeof(sinfo);
        sinfo.fMask=SIF_TRACKPOS;
		::GetScrollInfo(m_hWnd, SB_VERT, &sinfo);
        nPos=sinfo.nTrackPos;
	}

	if (m_pBindedListCtrl)
	{
		CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);

		if (nSBCode == SB_THUMBTRACK)
		{
			m_pBindedListCtrl->RedirectVScroll(SB_THUMBTRACK, nPos, NULL);
			m_pBindedListCtrl->RedirectVScroll(SB_THUMBPOSITION, nPos, NULL);
			m_pBindedListCtrl->RedirectVScroll(SB_ENDSCROLL, 0, NULL);
		}
		else
		{
			m_pBindedListCtrl->RedirectVScroll(nSBCode, nPos, pScrollBar);
		}
	}
	else
	{
		CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	}
	
	// RedrawWindow(); // SANDRO //
}

void CPazienteCronicoDxListCtrl::RedirectVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if ((nSBCode / 256 == SB_THUMBTRACK) || ((nSBCode & 0xFF) == SB_THUMBTRACK))
	{
  		int iY = ((int)nPos - (int)GetScrollPos(SB_VERT)) * m_iItemHeight; 
        Scroll(CSize(0, iY)); 
	}

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);

	// RedrawWindow(); // SANDRO //
}

int CPazienteCronicoDxListCtrl::InsertItem(int nItem, LPCTSTR lpszItem)
{
	int iReturn = CListCtrl::InsertItem(nItem, lpszItem);
	
	if (m_pBindedListCtrl)
	{
		m_pBindedListCtrl->InsertItem(iReturn, lpszItem);

		/*
		CRect rect;
		m_pBindedListCtrl->GetClientRect(&rect);
		m_pBindedListCtrl->SetColumnWidth(1, rect.right);

		m_pBindedListCtrl->Invalidate();
		*/
	}

	// Invalidate();

	return iReturn;
}

BOOL CPazienteCronicoDxListCtrl::DeleteItem(int nItem)
{
	BOOL bReturn = CListCtrl::DeleteItem(nItem);
	
	if (m_pBindedListCtrl)
		m_pBindedListCtrl->DeleteItem(nItem);

	if (m_pBindedListCtrl)
		m_pBindedListCtrl->Invalidate();

	Invalidate();
	return bReturn;
}

BOOL CPazienteCronicoDxListCtrl::DeleteAllItems()
{
	BOOL bReturn = CListCtrl::DeleteAllItems();
	
	if (m_pBindedListCtrl)
		m_pBindedListCtrl->DeleteAllItems();

	return bReturn;
}

BOOL CPazienteCronicoDxListCtrl::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText)
{
	BOOL bReturn = CListCtrl::SetItemText(nItem, nSubItem, lpszText);
	
	if (m_pBindedListCtrl && nSubItem == 1)
		m_pBindedListCtrl->SetItemText(nItem, nSubItem, lpszText);

	return bReturn;
}

BOOL CPazienteCronicoDxListCtrl::EnsureColumnVisible(int nColumn, BOOL bPartialOK)
{
	// CHeaderCtrl* pHeader = reinterpret_cast<CHeaderCtrl*>(GetDlgItem(0));
	// ASSERT(pHeader->IsKindOf(RUNTIME_CLASS(CHeaderCtrl)));

	CHeaderCtrl* pHeader = GetHeaderCtrl();
	// ASSERT(pHeader->IsKindOf(RUNTIME_CLASS(CHeaderCtrl)));

	CRect rcHeader;
	Header_GetItemRect(pHeader->m_hWnd, nColumn, &rcHeader);

	CRect rcClient;
	GetClientRect(&rcClient);

	int nOffset = GetScrollPos(SB_HORZ);
	if (bPartialOK)
		if ((rcHeader.left - nOffset < rcClient.right) && (rcHeader.right - nOffset > 0))
			return TRUE;

	int nScrollX = 0;
	if ((rcHeader.Width() > rcClient.Width()) || (rcHeader.left - nOffset < 0))
	{
		nScrollX = rcHeader.left - nOffset;
	}
	else if (rcHeader.right - nOffset > rcClient.right)
	{
		nScrollX = rcHeader.right - nOffset - rcClient.right;
	}
	if (nScrollX != 0)
	{
		CSize size(nScrollX, 0);
		Scroll(size);
	}

	return TRUE;
}

/*
void CPazienteCronicoDxListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CListCtrl::DrawItem(lpDrawItemStruct);
	if (lpDrawItemStruct->itemData == 0)
		return;

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	for(int i = 0; i < m_listSymbol.GetCount(); i++)
	{
		tagSYMBOL symbol = m_listSymbol.GetAt(m_listSymbol.FindIndex(i));
		if (symbol.lItem == lpDrawItemStruct->itemID)
		{
			CRect rect;
			if (GetSubItemRect(symbol.lItem, symbol.lSubItem, LVIR_BOUNDS, rect))
			{
				CString str;
				str.Format("*%li", i + 1);
				
				int iMode = dc.SetBkMode(OPAQUE);
				COLORREF cl = dc.SetTextColor(RGB(255, 0, 0));
				COLORREF cl2 = dc.SetBkColor(RGB(255, 255, 0));
				dc.DrawText(str, str.GetLength(), &rect, DT_RIGHT | DT_SINGLELINE | DT_TOP);
				dc.SetTextColor(cl);
				dc.SetBkColor(cl2);
				dc.SetBkMode(iMode);
			}
		}
	}

	dc.Detach();
}
*/

void CPazienteCronicoDxListCtrl::AddCellColor(int nItem, int nSubItem, COLORREF crBackColor)
{
	STRUCT_CELLCOLOR scc;
	scc.nItem = nItem;
	scc.nSubItem = nSubItem;
	scc.crBackColor = crBackColor;

	m_ctrlListCellColor.AddHead(scc);
}

void CPazienteCronicoDxListCtrl::HighlightCell(int nItem, int nSubItem)
{
	// prima rimuovo l'evidenziazione precedente //

	POSITION pos = m_ctrlListCellColor.GetHeadPosition();
	while(pos != NULL)
	{
		STRUCT_CELLCOLOR sccTemp = m_ctrlListCellColor.GetAt(pos);

		if (sccTemp.crBackColor == RGB_HIGHLIGHT)
		{
			m_ctrlListCellColor.RemoveAt(pos);
			break;
		}

		m_ctrlListCellColor.GetNext(pos);
	}

	// poi aggiungo la cella attuale //

	if ((nItem >= 0) && (nSubItem >= 0))
	{
		STRUCT_CELLCOLOR scc;
		scc.nItem = nItem;
		scc.nSubItem = nSubItem;
		scc.crBackColor = RGB_HIGHLIGHT;

		m_ctrlListCellColor.AddHead(scc);
	}
}

void CPazienteCronicoDxListCtrl::RemoveAllCellColor()
{
	m_ctrlListCellColor.RemoveAll();
}

void CPazienteCronicoDxListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
    NMLVCUSTOMDRAW *pCD = (NMLVCUSTOMDRAW*)pNMHDR;

    // By default set the return value to do the default behavior.
    *pResult = CDRF_DODEFAULT ;     

    // obtain row and column of item
    int nItem = pCD->nmcd.dwItemSpec;
    int nSubItem = pCD->iSubItem;
   
    // Remove standard highlighting of selected (sub)item.
    pCD->nmcd.uItemState = CDIS_DEFAULT;
			
	switch(pCD->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT: // First stage (for the whole control)
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;
		}
		case CDDS_ITEMPREPAINT:
		{
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
			break;
		}
		case  CDDS_ITEMPREPAINT | CDDS_SUBITEM : // Stage three 
		{
			// if (sub)item is of interest, set custom text/background color

			BOOL bFound = FALSE;

			POSITION pos = m_ctrlListCellColor.GetHeadPosition();
			while(pos != NULL)
			{
				STRUCT_CELLCOLOR sccTemp = m_ctrlListCellColor.GetAt(pos);

				if ((nItem == sccTemp.nItem) && (nSubItem == sccTemp.nSubItem))
				{
					// TRACE3("!!!   nItem=%02d   -   nSubItem=%02d   -   color=%li\n", sccTemp.nItem, sccTemp.nSubItem, sccTemp.crBackColor);

					bFound = TRUE;
					pCD->clrTextBk = sccTemp.crBackColor;
					break;
				}

				m_ctrlListCellColor.GetNext(pos);
			}

			if (!bFound)
				pCD->clrTextBk = RGB_WHITE;
	  
			*pResult = CDRF_NOTIFYPOSTPAINT;
			break;
		}
		case CDDS_ITEMPOSTPAINT | CDDS_SUBITEM: // Stage four (called for each subitem of the focused item)
		{
			break;
		}
		default:// it wasn't a notification that was interesting to us.
		{
			*pResult = CDRF_DODEFAULT;
			break;
		}
	}
}
