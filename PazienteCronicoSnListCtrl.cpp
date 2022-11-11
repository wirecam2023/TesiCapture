#include "stdafx.h"
#include "Endox.h"
#include "PazienteCronicoSnListCtrl.h"

#include "PazienteCronicoDxListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPazienteCronicoSnListCtrl, CListCtrl)

CPazienteCronicoSnListCtrl::CPazienteCronicoSnListCtrl()
	: CListCtrl()
{
	m_pBindedListCtrl = NULL;
	m_bWheelNotify = TRUE;
}

CPazienteCronicoSnListCtrl::~CPazienteCronicoSnListCtrl()
{
}

BEGIN_MESSAGE_MAP(CPazienteCronicoSnListCtrl, CListCtrl)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_VSCROLL()

	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
END_MESSAGE_MAP()

void CPazienteCronicoSnListCtrl::SetBindedListCtrl(CPazienteCronicoDxListCtrl* pList)
{
	m_pBindedListCtrl = pList;
}

BOOL CPazienteCronicoSnListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
    HD_NOTIFY* pHDN = (HD_NOTIFY*)lParam;

    if ((pHDN->hdr.code == HDN_BEGINTRACKW || pHDN->hdr.code == HDN_BEGINTRACKA || pHDN->hdr.code == HDN_DIVIDERDBLCLICKA || pHDN->hdr.code == HDN_DIVIDERDBLCLICKW) && (pHDN->iItem == 0 || pHDN->iItem == 1))
    {
		*pResult = TRUE; // disable tracking
		return TRUE; // Processed message
    }

	static UINT a = 0;
	TRACE("%li. CPazienteCronicoSnListCtrl::OnNotify %li %li\n", ++a, wParam, pHDN->hdr.code);
    return CListCtrl::OnNotify(wParam, lParam, pResult);
}

BOOL CPazienteCronicoSnListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL bReturn = CListCtrl::OnMouseWheel(nFlags, zDelta, pt);

	static UINT a = 0;
	TRACE("%li. CPazienteCronicoSnListCtrl::OnMouseWheel %li %li %li %li\n", ++a, nFlags, zDelta, pt.x, pt.y);

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

void CPazienteCronicoSnListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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

void CPazienteCronicoSnListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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

	static UINT a = 0;
	TRACE("%li. CPazienteCronicoSnListCtrl::OnVScroll %li %li %li\n", ++a, nSBCode, nPos);

	// RedrawWindow(); // SANDRO //
}

void CPazienteCronicoSnListCtrl::RedirectVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if ((nSBCode / 256 == SB_THUMBTRACK) || ((nSBCode & 0xFF) == SB_THUMBTRACK))
	{
  		int iY = ((int)nPos - (int)GetScrollPos(SB_VERT)) * GetItemHeight(); 
        Scroll(CSize(0, iY)); 
	}

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);

	// RedrawWindow(); // SANDRO //
}

int CPazienteCronicoSnListCtrl::GetItemHeight()
{
	CRect ItemRect;
	GetSubItemRect(0, 0, LVIR_BOUNDS, ItemRect);
	return ItemRect.bottom - ItemRect.top;
}

void CPazienteCronicoSnListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
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
			/*
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
			*/
	  
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
