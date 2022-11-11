#include "stdafx.h"
#include "Endox.h"
#include "CheckListTreeCtrl.h"
#include "CheckListCheckedElementSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCheckListTreeCtrl, CTreeCtrl)

CCheckListTreeCtrl::CCheckListTreeCtrl()
{
	m_lIDEsame = 0;

	m_xRClick = 0;
	m_yRClick = 0;
}

CCheckListTreeCtrl::~CCheckListTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(CCheckListTreeCtrl, CTreeCtrl)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CCheckListTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// classe nata appositamente per inibire l'uso della tastiera //

	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
		CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCheckListTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	ASSERT(m_lIDEsame > 0);

	m_xRClick = point.x;
	m_yRClick = point.y;

	HTREEITEM hTemp = HitTest(point);
	if (hTemp)
	{
		long lValue = GetItemData(hTemp);
		POSITION pos = m_listSelectedItem.Find(lValue);
		if (pos)
		{
			if (CCheckListCheckedElementSet().DelCheck(m_lIDEsame, lValue))
				m_listSelectedItem.RemoveAt(pos);
		}
		else
		{
			if (CCheckListCheckedElementSet().AddCheck(m_lIDEsame, lValue))
				m_listSelectedItem.AddTail(lValue);
		}

		Invalidate();

#define TIMER_RICARICAFRASE 1001
		GetParent()->SetTimer(TIMER_RICARICAFRASE, 100, NULL);
#undef TIMER_RICARICAFRASE
	}

	CTreeCtrl::OnRButtonDown(nFlags, point);
}

void CCheckListTreeCtrl::OnPaint()
{
	CPaintDC dc(this);

	// Create a memory DC compatible with the paint DC
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rcClip, rcClient;
	dc.GetClipBox( &rcClip );
	GetClientRect(&rcClient);

	// Select a compatible bitmap into the memory DC
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() );
	memDC.SelectObject( &bitmap );
	
	// Set clip region to be same as that in paint DC
	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcClip );
	memDC.SelectClipRgn(&rgn);
	rgn.DeleteObject();
	
	// First let the control do its default drawing.
	CWnd::DefWindowProc(WM_PAINT, (WPARAM)memDC.m_hDC, 0);
	
	// Ridisegno del dialogo
	HTREEITEM hItem = GetFirstVisibleItem();

	int iItemCount = GetVisibleCount() + 1;
	while(hItem && iItemCount--)
	{		
		CRect rect;

		// Do not meddle with selected items or drop highlighted items
		UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;
		Color_Font cf;
	
		// if ( !(GetTreeCtrl().GetItemState( hItem, selflag ) & selflag ) 
		//	&& m_mapColorFont.Lookup( hItem, cf ))

		GetItemRect(hItem, &rect, TRUE);
		//memDC.SetBkColor( GetSysColor(COLOR_WINDOW));
		POSITION pos = m_listSelectedItem.GetHeadPosition();

		while(pos)
		{
			long lValue = m_listSelectedItem.GetNext(pos);
			if (lValue == GetItemData(hItem))
			{
				CString sItem = GetItemText(hItem);

				LOGBRUSH logBrush;
				COLORREF yellow = RGB(255,127,0);
				logBrush.lbColor = yellow;
				
				CBrush brush;
				brush.CreateBrushIndirect(&logBrush);
				memDC.FillRect(&rect, &brush);
				memDC.SetBkColor(yellow);
				CFont* oldFont = (CFont*) memDC.SelectObject(GetFont());
				memDC.TextOut(rect.left + 2, rect.top + 1, sItem);
				memDC.SelectObject(oldFont);
			}
		}
		
		if ((GetItemState(hItem, selflag) & selflag) && ::GetFocus() == m_hWnd)
		{
		}
		else if (m_mapColorFont.Lookup(hItem, cf))
		{
			CFont *pFontDC;
			CFont fontDC;
			LOGFONT logfont;

			if (cf.logfont.lfFaceName[0] != '\0') 
				logfont = cf.logfont;
			else {
				// No font specified, so use window font
				CFont *pFont = GetFont();
				pFont->GetLogFont( &logfont );
			}

			//if (GetItemBold(hItem))
				logfont.lfWeight = 700;

			fontDC.CreateFontIndirect(&logfont);
			pFontDC = memDC.SelectObject(&fontDC );

			if (cf.color != (COLORREF) - 1)
				memDC.SetTextColor(cf.color);
			else
				memDC.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));


			CString sItem = GetItemText(hItem);

			GetItemRect(hItem, &rect, TRUE);
			//memDC.SetBkColor( GetSysColor(COLOR_WINDOW));
			
			memDC.SelectObject(pFontDC);
		}
		hItem = GetNextVisibleItem(hItem);
	}

	dc.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC, rcClip.left, rcClip.top, SRCCOPY);

	memDC.DeleteDC();
}

BOOL CCheckListTreeCtrl::SetCheck(HTREEITEM hItem, BOOL bCheck)
{
	return CTreeCtrl::SetCheck(hItem, bCheck);
}

BOOL CCheckListTreeCtrl::SetMyCheck(HTREEITEM hItem, BOOL bCheck)
{
	return SetCheck(hItem, bCheck);
}

void CCheckListTreeCtrl::LoadSelectedItems(long lIDEsame)
{
	m_lIDEsame = lIDEsame;

	CString strFilter;
	strFilter.Format("IDEsame=%li", m_lIDEsame);

	CCheckListCheckedElementSet setTemp;
	setTemp.SetOpenFilter(strFilter);
	if (setTemp.OpenRecordset("CCheckListTreeCtrl::LoadSelectedItems"))
	{
		while(!setTemp.IsEOF())
		{
			m_listSelectedItem.AddTail(setTemp.m_lIDItem);
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CCheckListTreeCtrl::LoadSelectedItems");
	}

	Invalidate();
}