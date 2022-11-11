#include "stdafx.h"
#include "Endox.h"
#include "RectPreviewObj.h"

#include <math.h>
#include "RectPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RGB_REPORT_1 RGB(207, 207, 207)
#define RGB_REPORT_2 RGB(255, 255, 127)

// IMPLEMENT_SERIAL(CRectPreviewObj, CObject, 0)

CRectPreviewObj::CRectPreviewObj(int nOffsetHandleParam, CSize szMinPixel, CSize szMaxPixel, double dRap)
{
	//non è un rettangolo normale
	m_PosObj	= CRect(0,0,0,0);
	
	m_bDrawInvert	= FALSE;

	m_strTitolo		= "";
	m_nAlignment	= 0;
	m_nRotation		= 0;
	
	m_nOffsetHandleParam	= nOffsetHandleParam;
	m_SizMinInPixel			= szMinPixel;
	m_SizMaxInPixel			= szMaxPixel;

	m_dRap = dRap;
}

CRectPreviewObj::CRectPreviewObj(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMinMM, CSize szMaxMM, double dRap)
{
	m_PosObj	= *pPosObj;
	m_ptLast	= CPoint(0,0);

	// TRACE2("-> m_ptLast X=%04d Y=%04d\n", m_ptLast.x, m_ptLast.y);

	m_bDrawInvert	= FALSE;

	m_strTitolo		= "";
	m_nAlignment	= 0;
	m_nRotation		= 0;
	
	m_nOffsetHandleParam	= nOffsetHandleParam;

	m_SizMinInPixel.cx = (int)((double)m_PosObj.GetPageInPixel().Width ()*((double)szMinMM.cx / (double)m_PosObj.GetPageInMM().Width ()));
	m_SizMinInPixel.cy = (int)((double)m_PosObj.GetPageInPixel().Height()*((double)szMinMM.cy / (double)m_PosObj.GetPageInMM().Height()));

	m_SizMaxInPixel.cx = (int)((double)m_PosObj.GetPageInPixel().Width ()*((double)szMaxMM.cx / (double)m_PosObj.GetPageInMM().Width ()));
	m_SizMaxInPixel.cy = (int)((double)m_PosObj.GetPageInPixel().Height()*((double)szMaxMM.cy / (double)m_PosObj.GetPageInMM().Height()));

	m_dRap = dRap;
}

CRectPreviewObj::~CRectPreviewObj()
{
}

void CRectPreviewObj::SetObj(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMinMM, CSize szMaxMM, double dRap)
{
	m_PosObj	= *pPosObj;
	m_ptLast	= CPoint(0,0);

	// TRACE2("-> m_ptLast X=%04d Y=%04d\n", m_ptLast.x, m_ptLast.y);

	m_nOffsetHandleParam	= nOffsetHandleParam;

	m_SizMinInPixel.cx = (int)((double)m_PosObj.GetPageInPixel().Width ()*((double)szMinMM.cx / (double)m_PosObj.GetPageInMM().Width ()));
	m_SizMinInPixel.cy = (int)((double)m_PosObj.GetPageInPixel().Height()*((double)szMinMM.cy / (double)m_PosObj.GetPageInMM().Height()));

	m_SizMaxInPixel.cx = (int)((double)m_PosObj.GetPageInPixel().Width ()*((double)szMaxMM.cx / (double)m_PosObj.GetPageInMM().Width ()));
	m_SizMaxInPixel.cy = (int)((double)m_PosObj.GetPageInPixel().Height()*((double)szMaxMM.cy / (double)m_PosObj.GetPageInMM().Height()));

	m_dRap = dRap;
}

void CRectPreviewObj::DrawTracker(CDC* pDC, TrackerState state)
{
	ASSERT_VALID(this);

	switch (state)
	{
		case normal:
			break;

		case selected:
		case active:
			{
				int nHandleCount = GetHandleCount();
				for(int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
				{
					CPoint handle = GetHandle(nHandle);
					pDC->PatBlt(handle.x - 3, handle.y - 3, 7, 7, DSTINVERT);
				}
			}
			break;
	}
}

void CRectPreviewObj::AutoRedraw(CWnd* pDlg)
{
	CClientDC dc(pDlg);

	AutoRedraw(&dc);
}

void CRectPreviewObj::AutoRedraw(CDC* pDC)
{
	if (m_PosObj.IsRectNull())
		return;

	Draw(pDC, m_strTitolo, m_nAlignment, m_nRotation, normal, NULL);
}

void CRectPreviewObj::Invalidate(CWnd* pDlg)
{
	CRect posRect = m_PosObj.GetRectPixel();

	posRect.InflateRect(9, 9);
	
	pDlg->InvalidateRect(posRect, TRUE);
	//pDlg->RedrawWindow(posRect, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

CRect CRectPreviewObj::TextOnVideo(HDC hdc, int x, int y, CString strText, LPLOGFONT lpFont, long cColor)
{
	HFONT	hFont 			= NULL;
	HFONT	hOldFont 		= NULL;
	HFONT	hMemFont 		= NULL;
	HFONT	hOldMemFont 	= NULL;
	HBITMAP hMemBmp			= NULL;
	HBITMAP hOldMemBmp		= NULL;
	CSize	size;
	HDC		hdcMem;

	if (lpFont)
	{
		hFont 		= ::CreateFontIndirect(lpFont);
		hOldFont 	= (HFONT)::SelectObject(hdc, hFont);
	}

	size		= ::GetTabbedTextExtent(hdc, (LPCSTR)strText, strText.GetLength(), 0, NULL);
	hdcMem		= ::CreateCompatibleDC(hdc);
	hMemBmp  	= ::CreateCompatibleBitmap(hdc, size.cx, size.cy);
	hOldMemBmp  = (HBITMAP)::SelectObject(hdcMem, hMemBmp);

	::PatBlt(hdcMem, 0, 0, size.cx, size.cy, WHITENESS);
	::SetBkMode(hdcMem, TRANSPARENT);
	::SetTextColor(hdcMem, RGB(0, 0, 0));
	
	if (lpFont)
	{
		hMemFont 	= ::CreateFontIndirect(lpFont);
		hOldMemFont = (HFONT)::SelectObject(hdcMem, hMemFont);
	}

	::TabbedTextOut(hdcMem, 0, 0, strText, strText.GetLength(), 0, NULL, 0);
		
	if (cColor < 0)
	{
		//Operazioni BitBlt...
		::BitBlt(hdc, x, y, size.cx, size.cy, hdcMem, 0, 0, 0x00990066); //inversione
	}
	else
	{
		HBRUSH 	hBrush 		= ::CreateSolidBrush((COLORREF)cColor);
		HBRUSH 	hOldBrush	= (HBRUSH)::SelectObject(hdc, hBrush);
		
		//Operazioni BitBlt...
		::BitBlt(hdc, x, y, size.cx, size.cy, hdcMem, 0, 0, 0x00B8074A);
		//PAT. 1 1 1 1 0 0 0 0
		//SORG 1 1 0 0 1 1 0 0
		//DEST 1 0 1 0 1 0 1 0
		//---------------------
		//DEST 1 0 1 1 1 0 0 0 == B8
		//ovvero:
		//dove SORG=nero(0) DEST=PAT 
		//dove SORG=bianco(1) DEST=DEST 

		::SelectObject(hdc, hOldBrush);

		::DeleteObject(hBrush);
	}
	
	if (hOldFont)
		::SelectObject(hdc, hOldFont);

	if (hFont)
		::DeleteObject(hFont);

	::SelectObject(hdcMem, hOldMemBmp);
	if (hOldMemFont)
		::SelectObject(hdcMem, hOldMemFont);

	::DeleteObject(hMemBmp);
	if (hMemFont)
		::DeleteObject(hMemFont);

	::DeleteDC(hdcMem);
	
	return CRect (x ,y, x + size.cx + 1, y + size.cy + 1);
}

#define _ROUND(x) (x<0?ceil((x)-0.5):floor((x)+0.5))

void CRectPreviewObj::Draw(CDC* pDC, CString strTitolo, int nAlignment, int nRotation, TrackerState nTrack, LOGFONT* plfFont)
{
	// TRACE("-> CRectPreviewObj::Draw(%s)\n", strTitolo);

	int Aligments[] = { DT_LEFT, DT_CENTER, DT_RIGHT };

	CRect posRect = m_PosObj.GetRectPixel();
	
	posRect.NormalizeRect();

	if (m_bDrawInvert)
	{
		pDC->DrawFocusRect(posRect);
		
		DrawTracker(pDC, active);
	}
	else
	{
		CBrush		brush;
		CPen		pen;
		LOGPEN		logpen;
		LOGBRUSH	logbrush;

		logbrush.lbStyle = BS_SOLID;

		if ((strTitolo.Left(3) == "(F)") || (strTitolo.Left(6) == "Param."))
			logbrush.lbColor = RGB_REPORT_2;
		else
			logbrush.lbColor = RGB_REPORT_1;

		logbrush.lbHatch	= HS_HORIZONTAL;

		logpen.lopnStyle	= PS_INSIDEFRAME;
		logpen.lopnWidth.x	= 1;
		logpen.lopnWidth.y	= 1;
		logpen.lopnColor	= RGB(0, 0, 0);

		if (!brush.CreateBrushIndirect(&logbrush))
			return;

		if (!pen.CreatePenIndirect(&logpen))
			return;

		CBrush* pOldBrush	= pDC->SelectObject(&brush);
		CPen*	pOldPen		= pDC->SelectObject(&pen);

		pDC->Rectangle(posRect);

		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);

		DrawTracker(pDC, nTrack);
	}

	if (strTitolo != "")
	{
		LOGFONT lFont;
		LOGFONT lSmallFont;

		lSmallFont.lfHeight 		= -7;
		lSmallFont.lfWeight 		= 100;
		lSmallFont.lfWidth			= 0;
		lSmallFont.lfEscapement		= 0;
		lSmallFont.lfOrientation	= 0;
		lSmallFont.lfWeight			= 0;
		lSmallFont.lfItalic			= 0;
		lSmallFont.lfUnderline		= 0;
		lSmallFont.lfStrikeOut		= 0;
		lSmallFont.lfCharSet		= 0;
		lSmallFont.lfOutPrecision	= 1;
		lSmallFont.lfClipPrecision	= 2;
		lSmallFont.lfQuality		= 1;
		lSmallFont.lfPitchAndFamily = 34;
		strcpy_s(lSmallFont.lfFaceName, "Small Font");
		
		if (plfFont)
		{
			double d1 = (double)plfFont->lfHeight * m_dRap;
			double d2 = (double)plfFont->lfWidth * m_dRap;

			lFont.lfHeight 			= (LONG)-_ROUND(-d1);
			lFont.lfWidth			= (LONG)-_ROUND(-d2);

			lFont.lfEscapement		= plfFont->lfEscapement;
			lFont.lfOrientation		= plfFont->lfOrientation;
			lFont.lfWeight			= plfFont->lfWeight;
			lFont.lfItalic			= plfFont->lfItalic;
			lFont.lfUnderline		= plfFont->lfUnderline;
			lFont.lfStrikeOut		= plfFont->lfStrikeOut;
			lFont.lfCharSet			= plfFont->lfCharSet;
			lFont.lfOutPrecision	= plfFont->lfOutPrecision;
			lFont.lfClipPrecision	= plfFont->lfClipPrecision;
			lFont.lfQuality			= plfFont->lfQuality;
			lFont.lfPitchAndFamily 	= plfFont->lfPitchAndFamily;
			strcpy_s(lFont.lfFaceName, plfFont->lfFaceName);
		}
		else
		{
			lFont.lfHeight 			= -8;
			lFont.lfWeight 			= 100;
			lFont.lfWidth			= 0;
			lFont.lfEscapement		= 0;
			lFont.lfOrientation		= 0;
			lFont.lfWeight			= 0;
			lFont.lfItalic			= 0;
			lFont.lfUnderline		= 0;
			lFont.lfStrikeOut		= 0;
			lFont.lfCharSet			= 0;
			lFont.lfOutPrecision	= 1;
			lFont.lfClipPrecision	= 2;
			lFont.lfQuality			= 1;
			lFont.lfPitchAndFamily = 34;
			strcpy_s(lFont.lfFaceName, "Small Font");
		}

		if (m_bDrawInvert)
		{
			if (m_nOffsetHandleParam < 0)
				TextOnVideo(pDC->GetSafeHdc(), posRect.left, posRect.top, strTitolo, &lFont, -1);
			else	
				TextOnVideo(pDC->GetSafeHdc(), posRect.left, posRect.top + lFont.lfHeight, strTitolo, &lFont, -1);
		}
		else
		{
			CFont	Font;
			CFont	FontSmall;
			CFont*	pOldFont;
			CRect	rectText = posRect;
			CRect	rectDim  = m_PosObj.GetRectMM();
			CString	strDim;

			rectText.InflateRect(-1, -1);
			
			Font.	  CreateFontIndirect(&lFont);
			FontSmall.CreateFontIndirect(&lSmallFont);
			
			pOldFont = (CFont*) pDC->SelectObject(&FontSmall);

			//////////////////////////////
			strDim.Format("(%ix%i)", rectDim.Width(), rectDim.Height());
			pDC->SetTextColor(RGB(255,0,0));
			pDC->SetBkColor  (RGB(208,208,208));
			pDC->SetBkMode   (TRANSPARENT);
			// pDC->DrawText(strDim, rectText, DT_SINGLELINE|DT_RIGHT|DT_BOTTOM);

			pDC->SelectObject(&Font);

			//////////////////////////////
			if (strTitolo.Left(3) == "(F)")
			{
				pDC->SetTextColor(RGB(0, 0, 0));
				pDC->SetBkColor  (RGB_REPORT_2);
				strTitolo = strTitolo.Right(strTitolo.GetLength() - 3);
			}
			else
			{
				if (strTitolo.Left(6) == "Param.")
				{
					pDC->SetTextColor(RGB(0, 0, 0));
					pDC->SetBkColor  (RGB_REPORT_2);
				}
				else
				{
					pDC->SetTextColor(RGB(0, 0, 0));
					pDC->SetBkColor  (RGB_REPORT_1);
				}
			}
			pDC->SetBkMode(OPAQUE);

			// TRACE("-> %d %s\n", m_nAlignment, strTitolo); 
			pDC->DrawText(strTitolo, rectText, DT_SINGLELINE|Aligments[nAlignment%3]|DT_TOP);

			pDC->SelectObject(pOldFont);

			Font.	  DeleteObject();
			FontSmall.DeleteObject();
		}
	}
}

// position is in logical
CRect CRectPreviewObj::MoveTo(CRect position, CWnd* pDlg)
{
	CRect posActual = m_PosObj.GetRectPixel();

	if (position == posActual)
		return posActual;
		
	if (m_bDrawInvert)
		AutoRedraw(pDlg);
	else
		Invalidate(pDlg);

	position = m_PosObj.SetPosRectPixel(position);
	//m_PosObj = position;

	if (m_bDrawInvert)
		AutoRedraw(pDlg);
	else
		Invalidate(pDlg);

	return position;
}

int CRectPreviewObj::HitTest(CPoint point, CWnd* pDlg)
{
	ASSERT_VALID(this);
	ASSERT(pDlg != NULL);

	int nHandleCount = GetHandleCount();

	for(int nHandle = 1; nHandle <= nHandleCount; nHandle++)
	{
		// GetHandleRect returns in logical coords
		CRect rc = GetHandleRect(nHandle,pDlg);
		if (point.x >= rc.left && point.x < rc.right &&
			point.y >= rc.top && point.y < rc.bottom)
		{
			m_ptLast.x = (rc.left+rc.right) / 2;
			m_ptLast.y = (rc.top+rc.bottom) / 2;

			// TRACE2("-> m_ptLast X=%04d Y=%04d\n", m_ptLast.x, m_ptLast.y);

			return nHandle;
		}
	}

	return 0;
}

BOOL CRectPreviewObj::ObjTest(CPoint point)
{
	ASSERT_VALID(this);

	if (m_PosObj.PtInRect(point))
	{
		m_ptLast = point;
		// TRACE2("-> m_ptLast X=%04d Y=%04d\n", m_ptLast.x, m_ptLast.y);

		return TRUE;
	}

	return FALSE;
}

// returns logical coords of center of handle
CPoint CRectPreviewObj::GetHandle(int nHandle)
{
	ASSERT_VALID(this);

	int		x, y, xCenter, yCenter;
	CRect	posActual = m_PosObj.GetRectPixel();

	// this gets the center regardless of left/right and top/bottom ordering
	xCenter = posActual.left + posActual.Width()  / 2;
	yCenter = posActual.top  + posActual.Height() / 2;

	switch (nHandle)
	{
		default:
			ASSERT(FALSE);
	
		case 1:
			x = xCenter;
			y = posActual.top - m_nOffsetHandleParam;
			break;
	
		case 2:
			x = posActual.right + m_nOffsetHandleParam - 1;
			y = yCenter;
			break;
	
		case 3:
			x = xCenter;
			y = posActual.bottom + m_nOffsetHandleParam - 1;
			break;
	
		case 4:
			x = posActual.left - m_nOffsetHandleParam;
			y = yCenter;
			break;
	}

	return CPoint(x, y);
}

// return rectange of handle in logical coords
CRect CRectPreviewObj::GetHandleRect(int nHandleID, CWnd* pDlg)
{
	ASSERT_VALID(this);
	ASSERT(pDlg != NULL);

	CRect rect;
	// get the center of the handle in logical coords
	CPoint point = GetHandle(nHandleID);
	// convert to client/device coords
	
	CRectPreview::DocToClient(pDlg, point);
	
	// return CRect of handle in device coords
	rect.SetRect(point.x-3, point.y-3, point.x+3, point.y+3);
	
	CRectPreview::ClientToDoc(pDlg, rect);

	return rect;
}

// point must be in logical
void CRectPreviewObj::MoveHandleTo(int nHandle, CPoint point, CWnd* pDlg)
{
	ASSERT_VALID(this);

	CRect	posActual = m_PosObj.GetRectPixel();
	
	switch (nHandle)
	{
		default:
			ASSERT(FALSE);

		case 1:
			if (posActual.bottom - point.y > m_SizMinInPixel.cy)
				if (posActual.bottom - point.y < m_SizMaxInPixel.cy)
					posActual.top = point.y;
			break;

		case 2:
			if (point.x - posActual.left > m_SizMinInPixel.cx)
				if (point.x - posActual.left < m_SizMaxInPixel.cx)
					posActual.right = point.x;
			break;
	
		case 3:
			if (point.y - posActual.top > m_SizMinInPixel.cy)
				if (point.y - posActual.top < m_SizMaxInPixel.cy)
				posActual.bottom = point.y;
			break;
	
		case 4:
			if (posActual.right - point.x > m_SizMinInPixel.cx)
				if (posActual.right - point.x < m_SizMaxInPixel.cx)
					posActual.left = point.x;
			break;
	}

	MoveTo(posActual, pDlg);
}

// point must be in logical
void CRectPreviewObj::MoveObjectTo(CPoint point, CWnd* pDlg, CRect rectFrame)
{
	ASSERT_VALID(this);

	int		nDx = point.x-m_ptLast.x;
	int		nDy	= point.y-m_ptLast.y;
	CRect	posPrev = m_PosObj.GetRectPixel();
	CRect	posNew;

	posPrev.OffsetRect(nDx, nDy);

	if (posPrev.top  < rectFrame.top)
	{
		posPrev.bottom = rectFrame.top + posPrev.Height();
		posPrev.top    = rectFrame.top;
	}
	if (posPrev.bottom  > rectFrame.bottom)
	{
		posPrev.top    = rectFrame.bottom - posPrev.Height();
		posPrev.bottom = rectFrame.bottom;
	}
	if (posPrev.left  < rectFrame.left)
	{
		posPrev.right = rectFrame.left + posPrev.Width();
		posPrev.left  = rectFrame.left;
	}
	if (posPrev.right  > rectFrame.right)
	{
		posPrev.left  = rectFrame.right - posPrev.Width();
		posPrev.right = rectFrame.right;
	}

	posNew = MoveTo(posPrev, pDlg);

	nDx = posNew.left - posPrev.left;
	nDy	= posNew.top  - posPrev.top;
	
	m_ptLast.x = point.x + nDx;
	m_ptLast.y = point.y + nDy;
	// TRACE2("-> m_ptLast X=%04d Y=%04d\n", m_ptLast.x, m_ptLast.y);
}

// rect must be in logical coordinates
BOOL CRectPreviewObj::Intersects(const CRect& rect)
{
	ASSERT_VALID(this);

	CRect fixed = m_PosObj.GetRectPixel();
	CRect rectT = rect;
	
	fixed.NormalizeRect();
	rectT.NormalizeRect();

	return !(rectT & fixed).IsRectEmpty();
}