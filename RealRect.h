#ifndef _REALRECT_H_
	#define _REALRECT_H_

class CRealRect : public CObject
{
	DECLARE_DYNAMIC(CRealRect);

public:

	CRect	m_RectInPixel;
	CRect	m_RectInMM;
	
	CRect	m_PageInPixel;
	CRect	m_PageInMM;

	int		m_nStepMM;

public:
	CRealRect();
	CRealRect(int l, int t, int r, int b);
	CRealRect(const RECT& srcRect);
	CRealRect(LPCRECT lpSrcRect);
	CRealRect(POINT point, SIZE size);
	CRealRect(POINT topLeft, POINT bottomRight);
	
// Operations
	void SetParam(CRect PageInPixel, CRect PageInMM, int nStepMM = 1);
	void NormalizeRect();
	BOOL IsRectNull();
	BOOL PtInRect(CPoint point);
	CRect GetPageInMM();
	CRect GetPageInPixel();
	CRect GetRectMM();
	CRect GetRectPixel();
	CRect ShiftRectMM(int nDxInMM, int nDyInMM);
	CRect SetPosRectMM(CRect RectInMM);
	CRect ShiftRectPixel(int nDxInPixel, int nDyInPixel);
	CRect SetPosRectPixel(CRect RectInPixel);
	CRealRect& operator = (const CRealRect& rhs);
};

inline CRealRect& 
CRealRect::operator = (const CRealRect& rhs)
{
	if (&rhs != this)
	{
		m_RectInPixel	= rhs.m_RectInPixel;
		m_RectInMM		= rhs.m_RectInMM;
	
		m_PageInPixel	= rhs.m_PageInPixel;
		m_PageInMM		= rhs.m_PageInMM;

		m_nStepMM		= rhs.m_nStepMM;
	}
	
	return *this;
}

#endif /* _REALRECT_H_ */