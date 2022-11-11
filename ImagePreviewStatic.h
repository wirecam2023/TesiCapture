#pragma once

#include <GdiPlus.h>

using namespace Gdiplus;

class CImagePreviewStatic :	public CStatic
{

	DECLARE_DYNAMIC(CImagePreviewStatic)

public:

	CImagePreviewStatic();
	virtual ~CImagePreviewStatic();

	virtual	BOOL Create();
	
	void SetImage(HBITMAP theBitmap);
	void ReleaseResource();

	void DecreaseZoom();
	void IncreaseZoom();

	void DrawPicture(CPaintDC* pDC);

	void OnMouseClicked(UINT nFlags, CPoint point);
	void OnMouseReleased(UINT nFlags, CPoint point);
	void OnMouseMoved(UINT nFlags, CPoint point);

	void RotateImage(int nAngoloRotazione);

protected:

	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:

	void CalculateZoomAndFactors();
	
	enum 
	{
		NoPan,
		WaitForPan,
		DoPan
	} m_PanState;

	PointF m_PanStartPoint;
	PointF m_TopLeftPoint;
	PointF m_LastTopLeftPoint;
	RectF  m_ImageSize;
	CRect  m_MySize;

	PointF m_ThumbOffset;

	Graphics* m_graphics;
	Image* m_img;

	REAL m_rThumbZoomAct;
	REAL m_rThumbZoomMin;

	BOOL m_bNewImage;

	int m_nAngoloRotazione;

};