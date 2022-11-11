#include "stdafx.h"
#include "Endox.h"
#include "ImagePreviewStatic.h"

#include <io.h>

IMPLEMENT_DYNAMIC(CImagePreviewStatic, CStatic)

CImagePreviewStatic::CImagePreviewStatic()
	: CStatic()
{
	TRACE0("--> CImagePreviewStatic::CImagePreviewStatic\n");

	m_img = NULL;
	m_graphics = NULL;
	m_PanState = NoPan;
	m_TopLeftPoint.X = 0;
	m_TopLeftPoint.Y = 0;
	m_LastTopLeftPoint.X = 0;
	m_LastTopLeftPoint.Y = 0;

	m_rThumbZoomAct = 1;
	m_rThumbZoomMin = 1;

	m_bNewImage = TRUE;

	m_nAngoloRotazione = 0;
}

CImagePreviewStatic::~CImagePreviewStatic()
{
	TRACE0("--> CImagePreviewStatic::~CImagePreviewStatic\n");

	if (m_img != NULL)
		delete m_img;
	
	if (m_graphics != NULL)
		delete m_graphics;
}

BEGIN_MESSAGE_MAP(CImagePreviewStatic, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CImagePreviewStatic::Create()
{
	TRACE0("--> CImagePreviewStatic::Create\n");

	if (GetSafeHwnd())
	{
		m_graphics = new Graphics(GetSafeHwnd());

		GetClientRect(&m_MySize);

		CRect rect;
		GetWindowRect(&rect);

		// m_wndSelect.Create(CSelectWnd::IDD, this);
		// m_wndSelect.SetWindowPos(&wndTop, rect.left, rect.top, 0, 0, SWP_NOSIZE);
		// m_wndSelect.ShowWindow(SW_HIDE);

		return TRUE;
	}

	return FALSE;
}

void CImagePreviewStatic::OnDestroy()
{
	TRACE0("--> CImagePreviewStatic::OnDestroy\n");

	ReleaseResource();

	CStatic::OnDestroy();
}

BOOL CImagePreviewStatic::OnEraseBkgnd(CDC* pDC)
{
	TRACE0("--> CImagePreviewStatic::OnEraseBkgnd\n");

	return TRUE;
}

void CImagePreviewStatic::SetImage(HBITMAP theBitmap)
{
	TRACE0("--> CImagePreviewStatic::SetImage\n");

	Unit  units;

	ReleaseResource();

	m_bNewImage = TRUE;

	m_img =	(Image*)Gdiplus::Bitmap::FromHBITMAP(theBitmap,0);
	m_img->GetBounds(&m_ImageSize, &units);
	m_graphics->Clear(Color());
	CalculateZoomAndFactors();
}

void CImagePreviewStatic::ReleaseResource()
{
	TRACE0("--> CImagePreviewStatic::ReleaseResource\n");

	if (m_img != NULL)
	{
		delete m_img;
		m_img = NULL;
	}
}

void CImagePreviewStatic::DrawPicture(CPaintDC* pDC)
{
	TRACE0("--> CImagePreviewStatic::DrawPicture ");

	if (m_img == NULL)
		return;

	RectF destRect(REAL(m_MySize.left),	REAL(m_MySize.top),	REAL(m_MySize.Width()),	REAL(m_MySize.Height()));
	
	if (pDC)
	{
		CRect rect;
		GetWindowRect(&rect);
		pDC->GetWindow()->ScreenToClient(&rect);
		pDC->FillRect(&rect, &CBrush(RGB(0,0,0)));
	}

	REAL rWidth = (REAL)(destRect.Width / m_rThumbZoomAct);
	REAL rHeight = (REAL)(destRect.Height / m_rThumbZoomAct);

	// Sandro 14/03/2012 // provo la rotazione //
	PointF pCenter(destRect.X + (destRect.Width / 2), destRect.Y + (destRect.Height / 2));

	Matrix mRotation;
	mRotation.RotateAt((REAL)m_nAngoloRotazione, pCenter);

	m_graphics->SetTransform(&mRotation);

	//
	m_graphics->DrawImage(m_img, destRect, m_TopLeftPoint.X, m_TopLeftPoint.Y, rWidth, rHeight, UnitPixel, NULL);
}

void CImagePreviewStatic::DecreaseZoom() 
{ 
	TRACE0("--> CImagePreviewStatic::DecreaseZoom\n");

	if (m_img == NULL)
		return;

	REAL rThumbZoomPrev = m_rThumbZoomAct;

	m_rThumbZoomAct /= (REAL)1.1;
	if (m_rThumbZoomAct < m_rThumbZoomMin)
		m_rThumbZoomAct = m_rThumbZoomMin;

	if ((rThumbZoomPrev != m_rThumbZoomAct) || m_bNewImage)
	{
		if (m_bNewImage)
		{
			m_bNewImage = FALSE;

			m_LastTopLeftPoint.X = (m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct)) / 2;
			m_LastTopLeftPoint.Y = (m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct)) / 2;
			m_TopLeftPoint.X = m_LastTopLeftPoint.X;
			m_TopLeftPoint.Y = m_LastTopLeftPoint.Y;
		}
		else
		{
			REAL rShiftX = (m_ImageSize.Width - (m_MySize.Width() / rThumbZoomPrev)) - (m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct));
			REAL rShiftY = (m_ImageSize.Height - (m_MySize.Height() / rThumbZoomPrev)) - (m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct));

			m_LastTopLeftPoint.X -= rShiftX / 2;
			m_LastTopLeftPoint.Y -= rShiftY / 2;
			m_TopLeftPoint.X = m_LastTopLeftPoint.X;
			m_TopLeftPoint.Y = m_LastTopLeftPoint.Y;

			if (m_TopLeftPoint.X < 0) 
				m_TopLeftPoint.X = 0;
			
			if (m_TopLeftPoint.Y < 0) 
				m_TopLeftPoint.Y = 0;

			if (m_ImageSize.Width < m_MySize.Width() / m_rThumbZoomAct)
			{
				if (m_TopLeftPoint.X > ((m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct)) / 2)) 
					m_TopLeftPoint.X = ((m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct)) / 2);
			}
			else
			{
				if (m_TopLeftPoint.X > ((m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct)))) 
					m_TopLeftPoint.X = ((m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct)));
			}

			if (m_ImageSize.Height < m_MySize.Height() / m_rThumbZoomAct)
			{
				if (m_TopLeftPoint.Y > ((m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct)) / 2)) 
					m_TopLeftPoint.Y = ((m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct)) / 2);
			}
			else
			{
				if (m_TopLeftPoint.Y > ((m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct)))) 
					m_TopLeftPoint.Y = ((m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct)));
			}

			m_LastTopLeftPoint.X = m_TopLeftPoint.X;
			m_LastTopLeftPoint.Y = m_TopLeftPoint.Y;
		}

		m_graphics->Clear(Color());
		DrawPicture(0);
	}
}

void CImagePreviewStatic::IncreaseZoom() 
{ 
	TRACE0("--> CImagePreviewStatic::IncreaseZoom\n");

	if (m_img == NULL)
		return;

	REAL rThumbZoomPrev = m_rThumbZoomAct;

	m_rThumbZoomAct *= (REAL)1.1;

	REAL rShiftX = (m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct)) - (m_ImageSize.Width - (m_MySize.Width() / rThumbZoomPrev));
	REAL rShiftY = (m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct)) - (m_ImageSize.Height - (m_MySize.Height() / rThumbZoomPrev));

	m_LastTopLeftPoint.X += rShiftX / 2;
	m_LastTopLeftPoint.Y += rShiftY / 2;
	m_TopLeftPoint.X = m_LastTopLeftPoint.X;
	m_TopLeftPoint.Y = m_LastTopLeftPoint.Y;

	// m_graphics->Clear(Color());
	DrawPicture(0);
}

void CImagePreviewStatic::OnMouseClicked(UINT nFlags, CPoint point)
{
	TRACE0("--> CImagePreviewStatic::OnMouseClicked\n");

	if (m_img == NULL)
		return;
	
	// if (m_bZoomMode)
	{
		if (m_PanState==NoPan)
		{
			m_PanState = WaitForPan;
			m_PanStartPoint.X = (REAL)point.x;
			m_PanStartPoint.Y = (REAL)point.y;
		}
	}
}

void CImagePreviewStatic::OnMouseReleased(UINT nFlags, CPoint point)
{
	TRACE0("--> CImagePreviewStatic::OnMouseReleased\n");

	if (m_img == NULL)
		return;
	
	// if (m_bZoomMode)
	{
		m_PanState = NoPan;
		m_LastTopLeftPoint.X = m_TopLeftPoint.X;
		m_LastTopLeftPoint.Y = m_TopLeftPoint.Y;
	}
}

void CImagePreviewStatic::OnMouseMoved(UINT nFlags, CPoint point)
{
	if (m_img == NULL)
		return;
	
	if (nFlags & MK_LBUTTON)
	{
		// se il tasto sinistro del mouse è premuto... //

		if (m_PanState == WaitForPan)
		{
			PointF diff = m_PanStartPoint - PointF((REAL)point.x, (REAL)point.y);
			if (abs((int)diff.X) > 5 || abs((int)diff.Y) > 5)
				m_PanState = DoPan;
		}
		else if (m_PanState == DoPan)
		{
			m_TopLeftPoint = m_LastTopLeftPoint + m_PanStartPoint - PointF((REAL)point.x, (REAL)point.y);

			if (m_TopLeftPoint.X < 0) 
				m_TopLeftPoint.X = 0;
			
			if (m_TopLeftPoint.Y < 0) 
				m_TopLeftPoint.Y = 0;

			if (m_ImageSize.Width < m_MySize.Width() / m_rThumbZoomAct)
			{
				if (m_TopLeftPoint.X > ((m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct)) / 2)) 
					m_TopLeftPoint.X = ((m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct)) / 2);
			}
			else
			{
				if (m_TopLeftPoint.X > ((m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct)))) 
					m_TopLeftPoint.X = ((m_ImageSize.Width - (m_MySize.Width() / m_rThumbZoomAct)));
			}

			if (m_ImageSize.Height < m_MySize.Height() / m_rThumbZoomAct)
			{
				if (m_TopLeftPoint.Y > ((m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct)) / 2)) 
					m_TopLeftPoint.Y = ((m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct)) / 2);
			}
			else
			{
				if (m_TopLeftPoint.Y > ((m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct)))) 
					m_TopLeftPoint.Y = ((m_ImageSize.Height - (m_MySize.Height() / m_rThumbZoomAct)));
			}

			DrawPicture(0);
		}
	}
	else
	{
		// se il tasto sinistro del mouse non è premuto... //
		m_PanState = NoPan;
		m_LastTopLeftPoint.X = m_TopLeftPoint.X;
		m_LastTopLeftPoint.Y = m_TopLeftPoint.Y;
	}
}

void CImagePreviewStatic::RotateImage(int nAngoloRotazione)
{
	TRACE0("--> CImagePreviewStatic::RotateImage\n");

	if (m_img == NULL)
		return;

	m_nAngoloRotazione = nAngoloRotazione;

	m_graphics->Clear(Color());
	DrawPicture(0);
}

void CImagePreviewStatic::OnSize(UINT nType, int cx, int cy)
{
	TRACE0("--> CImagePreviewStatic::OnSize\n");

	CStatic::OnSize(nType, cx, cy);

	if (GetSafeHwnd())
	{
		m_graphics = new Graphics(GetSafeHwnd());
		GetClientRect(&m_MySize);
	}
	
	// AmXPlay_Repos(m_iVideoPlayerID);
	// AmdcmViewer_Repos(m_iDicomViewerID);
	CalculateZoomAndFactors();
}

void CImagePreviewStatic::CalculateZoomAndFactors()
{
	TRACE0("--> CImagePreviewStatic::CalculateZoomAndFactors\n");

	m_LastTopLeftPoint.X = (m_ImageSize.Width - m_MySize.Width() / m_rThumbZoomAct) / 2;
	m_LastTopLeftPoint.Y = (m_ImageSize.Height - m_MySize.Height() / m_rThumbZoomAct) / 2;
	m_TopLeftPoint.X = m_LastTopLeftPoint.X;
	m_TopLeftPoint.Y = m_LastTopLeftPoint.Y;

	REAL rZoomFactorX = m_MySize.Width()/m_ImageSize.Width;
	REAL rZoomFactorY = m_MySize.Height()/m_ImageSize.Height;
	m_rThumbZoomAct = (rZoomFactorX < rZoomFactorY) ? rZoomFactorX : rZoomFactorY;
	if (m_rThumbZoomAct > 1) 
		m_rThumbZoomAct = 1;
	m_rThumbZoomMin = m_rThumbZoomAct;
	m_ThumbOffset.X = (m_ImageSize.Width - m_MySize.Width() / m_rThumbZoomAct) / 2;
	m_ThumbOffset.Y = (m_ImageSize.Height - m_MySize.Height() / m_rThumbZoomAct) / 2;
}