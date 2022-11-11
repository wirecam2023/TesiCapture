#include "stdafx.h"
#include "Endox.h"
#include "RectPreview.h"
#include "RectPreviewObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CRectPreview, CObject, 0)

CRectPreview::CRectPreview()
{
	m_pObj			= NULL;
	m_selectMode	= none;
	m_nDragHandle	= 0;
	m_bIsEnable		= FALSE;

	m_strTitolo		= "";
	m_nAlignment	= 0;
	m_nRotation		= 0;
}

CRectPreview::CRectPreview(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap)
{
	m_pObj = new CRectPreviewObj(pPosObj, nOffsetHandleParam, szMin, szMax, dRap);
	
	if (m_pObj)
		m_pObj->m_bDrawInvert	= TRUE;

	m_selectMode	= none;
	m_nDragHandle	= 0;
	m_bIsEnable		= FALSE;

	m_strTitolo		= "";
	m_nAlignment	= 0;
	m_nRotation		= 0;

	m_dRap = dRap;
}

CRectPreview::~CRectPreview()
{
	if (m_pObj)
		delete m_pObj;
}

void CRectPreview::SetObj(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap)
{
	if (m_pObj)
		m_pObj->SetObj(pPosObj, nOffsetHandleParam, szMin, szMax, dRap);
	else
		m_pObj = new CRectPreviewObj(pPosObj, nOffsetHandleParam, szMin, szMax, dRap);

	if (m_pObj)
		m_pObj->m_bDrawInvert	= TRUE;

	m_selectMode	= none;
	m_nDragHandle	= 0;
	m_bIsEnable		= FALSE;

	m_dRap = dRap;
}

void CRectPreview::SetObj(CString strTitolo, int nAlignment, int nRotation)
{
	m_strTitolo = strTitolo;
	m_nAlignment = nAlignment;
	m_nRotation = nRotation;
	
	if (m_pObj)
	{
		m_pObj->m_strTitolo = strTitolo;
		m_pObj->m_nAlignment = nAlignment;
		m_pObj->m_nRotation = nRotation;
	}
}

CRealRect*	CRectPreview::GetObj()
{ 
	if (m_pObj)
		return m_pObj->GetObj(); 

	return NULL;
}

CRect CRectPreview::GetRectInMM()
{
	if (m_pObj)
		return m_pObj->m_PosObj.GetRectMM();
	
	return CRect(0,0,0,0);
}

CRect CRectPreview::GetRectInPixel()
{
	if (m_pObj)
		return m_pObj->m_PosObj.GetRectPixel();
	
	return CRect(0,0,0,0);
}

void CRectPreview::SetRectInMM(CWnd* pWnd, CRect rectInMM)
{
	if (m_pObj)
	{
		CRect rectActual = m_pObj->m_PosObj.GetRectMM();
		
		if (rectActual != rectInMM)
		{
			if (m_bIsEnable)
			{
				if (m_pObj->m_bDrawInvert)
					AutoRedraw(pWnd);
				else
					Invalidate(pWnd);
			}

			m_pObj->m_PosObj.SetPosRectMM(rectInMM);
			//m_pObj->m_PosObj = rectInPixel;

			if (m_bIsEnable)
			{
				if (m_pObj->m_bDrawInvert)
					AutoRedraw(pWnd);
				else
					Invalidate(pWnd);
			}
		}
	}
}

void CRectPreview::SetRectInPixel(CWnd* pWnd, CRect rectInPixel)
{
	if (m_pObj)
	{
		CRect rectActual = m_pObj->m_PosObj.GetRectPixel();
		
		if (rectActual != rectInPixel)
		{
			if (m_bIsEnable)
			{
				if (m_pObj->m_bDrawInvert)
					AutoRedraw(pWnd);
				else
					Invalidate(pWnd);
			}

			m_pObj->m_PosObj.SetPosRectPixel(rectInPixel);
			//m_pObj->m_PosObj = rectInPixel;

			if (m_bIsEnable)
			{
				if (m_pObj->m_bDrawInvert)
					AutoRedraw(pWnd);
				else
					Invalidate(pWnd);
			}
		}
	}
}

void CRectPreview::Invalidate(CWnd* pDlg)
{
	if (m_pObj && m_bIsEnable)
		m_pObj->Invalidate(pDlg);
}

void CRectPreview::AutoRedraw(CWnd* pDlg)
{
	if (m_pObj && m_bIsEnable)
		m_pObj->AutoRedraw(pDlg);
}

void CRectPreview::AutoRedraw(CDC* pDC)
{
	if (m_pObj && m_bIsEnable)
		m_pObj->AutoRedraw(pDC);
}

void CRectPreview::Draw(CWnd* pDlg, CString strTitolo, int nAlignment, int nRotation, TrackerState nTrack, LOGFONT* plfFont)
{
	if (m_pObj && m_bIsEnable)
	{
		CClientDC dc(pDlg); 

		Draw(&dc, strTitolo, nAlignment, nRotation, nTrack, plfFont);
	}
}

void CRectPreview::Draw(CDC* pDC, CString strTitolo, int nAlignment, int nRotation, TrackerState nTrack, LOGFONT* plfFont)
{
	// TRACE("-> CRectPreview::Draw(%s)\n", strTitolo);

	if (m_pObj && m_bIsEnable)
		m_pObj->Draw(pDC, strTitolo, nAlignment, nRotation, nTrack, plfFont);
}

void CRectPreview::OnLButtonDown(CWnd* pDlg, CRect rectFrame, UINT, CPoint& point)
{
	CPoint local = point;

	if (m_pObj && m_bIsEnable)
	{
		ClientToDoc(pDlg, rectFrame, local, FALSE);
	
		m_nDragHandle = m_pObj->HitTest(local, pDlg);
		
		if (m_nDragHandle)
			m_selectMode = size;
		else
			if (m_pObj->ObjTest(local))
				m_selectMode = move;
			else
				m_selectMode = none;
	}
}

void CRectPreview::OnLButtonUp(CWnd*, CRect, UINT, CPoint&)
{
	if (m_pObj && m_bIsEnable)
		ReleaseCapture();
}

void CRectPreview::OnMouseMove(CWnd* pDlg, CRect rectFrame, CPoint& point)
{
	if (m_pObj && m_bIsEnable)
	{
		if (pDlg->GetCapture() != pDlg)
			return;

		CPoint local = point;
		ClientToDoc(pDlg, rectFrame, local, TRUE);

		TRACE2("--- CRectPreview::OnMouseMove(%03li %03li)\n", local.x, local.y);

		if (m_selectMode == size && m_nDragHandle != 0)
			m_pObj->MoveHandleTo(m_nDragHandle, local, pDlg);

		if (m_selectMode == move)
			m_pObj->MoveObjectTo(local, pDlg, rectFrame);
	}
}

void CRectPreview::ClientToDoc(CWnd* pWnd, CRect rectFrame, CPoint& point, BOOL bMove)
{
	CClientDC dc(pWnd);
	dc.DPtoLP(&point);

	if (bMove)                     
	{
		if (!rectFrame.PtInRect(point))
		{
			point.x = min(point.x, rectFrame.right);
			point.y = min(point.y, rectFrame.bottom);
			point.x = max(point.x, rectFrame.left);
			point.y = max(point.y, rectFrame.top);
		}
	}
}

void CRectPreview::ClientToDoc(CWnd* pWnd, CRect& rect)
{
	CClientDC dc(pWnd);
	dc.DPtoLP(rect); 
}

void CRectPreview::DocToClient(CWnd* pWnd, CPoint& point)
{
	CClientDC dc(pWnd);
	dc.LPtoDP(&point);
}

void CRectPreview::DocToClient(CWnd* pWnd, CRect& rect)
{
	CClientDC dc(pWnd);
	dc.LPtoDP(rect);
	rect.NormalizeRect();
}

BYTE CRectPreview::RecalcIntensity(CWnd* pWnd)
{
	CClientDC dc(pWnd);
	
	HDC		hdc		= dc.GetSafeHdc();
	CRect	rect	= GetRectInPixel();
	DWORD	somma	= 0;
		
	for(int y = rect.top + 1; y < rect.bottom - 1 ; y++)
	{
		for(int x = rect.left + 1; x < rect.right - 1; x++)
		{
			COLORREF color = ::GetPixel(hdc, x, y);
			int red   = (int)GetRValue(color);
			int green = (int)GetGValue(color);
			int blue  = (int)GetBValue(color);
			int intensity = (red + green + blue) / 3;
			somma += intensity;
		}
	}
		
	DWORD totPixel = (DWORD)(rect.Width() - 2);
		
	totPixel *= (DWORD)(rect.Height() - 2);
		
	return (BYTE)((DWORD)somma / totPixel);
}

// rect must be in logical coordinates
BOOL CRectPreview::Intersects(const CRect& rect)
{
	ASSERT_VALID(this);

	if (m_pObj)
	{
		CRect rectT = rect;
		CRect fixed = GetRectInPixel();

		rectT.NormalizeRect();
		fixed.NormalizeRect();

		if ((rectT & fixed).IsRectEmpty())
			return FALSE;

		return TRUE;
	}
	
	return  FALSE;
}