#include "stdafx.h"
#include "Endox.h"
#include "RealRect.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRealRect, CObject)

CRealRect::CRealRect()
{
	m_RectInPixel	= CRect(0,0,0,0);
	m_RectInMM		= CRect(0,0,0,0);
	
	m_PageInPixel	= CRect(0,0,0,0);
	m_PageInMM		= CRect(0,0,0,0);

	m_nStepMM		= 1;
}
  
CRealRect::CRealRect(int l, int t, int r, int b)
{
	m_RectInPixel	= CRect(l, t, r, b);
	m_RectInMM		= CRect(l, t, r, b);

	m_PageInPixel	= CRect(l, t, r, b);
	m_PageInMM		= CRect(l, t, r, b);
	
	m_nStepMM		= 1;
}
  
CRealRect::CRealRect(const RECT& srcRect)
{
	m_RectInPixel	= CRect(srcRect);
	m_RectInMM		= CRect(srcRect);

	m_PageInPixel	= CRect(srcRect);
	m_PageInMM		= CRect(srcRect);
	
	m_nStepMM		= 1;
}
  
CRealRect::CRealRect(LPCRECT lpSrcRect)
{
	m_RectInPixel	= CRect(lpSrcRect);
	m_RectInMM		= CRect(lpSrcRect);

	m_PageInPixel	= CRect(lpSrcRect);
	m_PageInMM		= CRect(lpSrcRect);
	
	m_nStepMM		= 1;
}
  
CRealRect::CRealRect(POINT point, SIZE size)
{
	m_RectInPixel	= CRect(point, size);
	m_RectInMM		= CRect(point, size);

	m_PageInPixel	= CRect(point, size);
	m_PageInMM		= CRect(point, size);
	
	m_nStepMM		= 1;
}
  
CRealRect::CRealRect(POINT topLeft, POINT bottomRight)
{
	m_RectInPixel	= CRect(topLeft, bottomRight);
	m_RectInMM		= CRect(topLeft, bottomRight);

	m_PageInPixel	= CRect(topLeft, bottomRight);
	m_PageInMM		= CRect(topLeft, bottomRight);

	m_nStepMM		= 1;
}

void CRealRect::SetParam(CRect PageInPixel, CRect PageInMM, int nStepMM)
{
	m_PageInPixel	= PageInPixel;
	m_PageInMM		= PageInMM;
	m_nStepMM		= nStepMM;

	GetRectPixel();
}

void CRealRect::NormalizeRect()
{
	m_RectInMM.	  NormalizeRect();
	m_RectInPixel.NormalizeRect();
}

BOOL CRealRect::IsRectNull()
{
	return m_RectInPixel.IsRectNull();
}

BOOL CRealRect::PtInRect(CPoint point)
{
	//conversione rettangolo in coordinate valide per il device contest
	CRect rectDC(m_RectInPixel);

	rectDC.OffsetRect(m_PageInPixel.left, m_PageInPixel.top);

	return rectDC.PtInRect(point);
}

CRect CRealRect::GetPageInMM()
{
	return m_PageInMM;
}

CRect CRealRect::GetPageInPixel()
{
	return m_PageInPixel;
}

CRect CRealRect::GetRectMM()
{
	return m_RectInMM;
}

CRect CRealRect::GetRectPixel()
{
	if (m_PageInMM.Width() && m_PageInMM.Height())
	{
		m_RectInPixel.left   = (int)(((double)m_PageInPixel.Width () * (double)m_RectInMM.left)  / (double)m_PageInMM.Width ());
		m_RectInPixel.right  = (int)(((double)m_PageInPixel.Width () * (double)m_RectInMM.right) / (double)m_PageInMM.Width ());
		m_RectInPixel.top	 = (int)(((double)m_PageInPixel.Height() * (double)m_RectInMM.top)   / (double)m_PageInMM.Height());
		m_RectInPixel.bottom = (int)(((double)m_PageInPixel.Height() * (double)m_RectInMM.bottom)/ (double)m_PageInMM.Height());
	}
	else
	{
		m_RectInPixel = m_RectInMM;
	}

	//conversione rettangolo in coordinate valide per il device contest
	CRect rectDC(m_RectInPixel);

	rectDC.OffsetRect(m_PageInPixel.left, m_PageInPixel.top);

	return rectDC;
}

CRect CRealRect::ShiftRectMM(int nDxInMM, int nDyInMM)
{
	m_RectInMM.OffsetRect(nDxInMM, nDyInMM);
	
	return GetRectPixel();
}

CRect CRealRect::SetPosRectMM(CRect RectInMM)
{
	m_RectInMM = RectInMM;

	return GetRectPixel();
}

CRect CRealRect::ShiftRectPixel(int nDxInPixel, int nDyInPixel)
{
	int nDxInMM = (int)(((double)m_PageInMM.Width () * (double)nDxInPixel) / (double)m_PageInPixel.Width ());
	int nDyInMM = (int)(((double)m_PageInMM.Height() * (double)nDyInPixel) / (double)m_PageInPixel.Height());
	
	if (nDxInPixel)
	{
		if (abs(nDxInMM) < m_nStepMM)
			if (nDxInPixel < 0)
				nDxInMM = -m_nStepMM;
			else
				nDxInMM = +m_nStepMM;
	}

	if (nDyInPixel)
	{
		if (abs(nDyInMM) < m_nStepMM)
			if (nDyInPixel < 0)
				nDyInMM = -m_nStepMM;
			else
				nDyInMM = +m_nStepMM;
	}

	return ShiftRectMM(nDxInMM, nDyInMM);
}

CRect CRealRect::SetPosRectPixel(CRect RectInPixel)
{
	CRect	RectInMM;
	int		nCxInMM;
	int		nCyInMM;

	//conversione rettangolo da coordinate valide per il device contest
	//a coordinate relative all rettangolo di pagina
	RectInPixel.OffsetRect(-m_PageInPixel.left, -m_PageInPixel.top);
	
	RectInMM.left = (int)floor(((double)m_PageInMM.Width () * (double)RectInPixel.left) / (double)m_PageInPixel.Width () + 0.5);
	RectInMM.top  = (int)floor(((double)m_PageInMM.Height() * (double)RectInPixel.top ) / (double)m_PageInPixel.Height() + 0.5);
	
	nCxInMM = (int)floor(((double)m_PageInMM.Width () * (double)RectInPixel.Width ()) / (double)m_PageInPixel.Width () + 0.5);
	nCyInMM = (int)floor(((double)m_PageInMM.Height() * (double)RectInPixel.Height()) / (double)m_PageInPixel.Height() + 0.5);


	if (RectInPixel.Width())
	{
		if (abs(nCxInMM) < m_nStepMM)
			nCxInMM = m_nStepMM;
	}

	if (RectInPixel.Height())
	{
		if (abs(nCyInMM) < m_nStepMM)
			nCyInMM = m_nStepMM;
	}

	RectInMM.right  = RectInMM.left + nCxInMM;
	RectInMM.bottom = RectInMM.top  + nCyInMM;
	
	return SetPosRectMM(RectInMM);
}