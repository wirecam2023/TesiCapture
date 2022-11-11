#pragma once

class CMemDC : public CDC 
{
public:
	CMemDC(CDC* pDC, CBitmap* pBitmap, const CRect* pRect = NULL);
	~CMemDC();

	CMemDC* operator->();
	operator CMemDC*() ;

private:
	CBitmap*	m_bitmap;		// Offscreen bitmap
	CBitmap*	m_oldBitmap;	// bitmap originally found in CMemDC
	CDC*		m_pDC;			// Saves CDC passed in constructor
	CRect		m_rect;			// Rectangle of drawing area.
	BOOL		m_bMemDC;		// TRUE if CDC really is a Memory DC.
};