#ifndef _CDIB_H_
	#define _CDIB_H_

#include <string.h>
#include <memory.h>

#define IS_WIN30_DIB(lpbi) ((*(LPDWORD) (lpbi)) == sizeof (BITMAPINFOHEADER))

class CDib : public CObject
{
	DECLARE_DYNCREATE(CDib)

public:

	CDib();
	CDib(HGLOBAL dib, BOOL freeOnDelete = FALSE);
	CDib(const CDib& rhs);
	virtual ~CDib();

	static HGLOBAL WINAPI BitmapToDIB(HBITMAP hBitmap, HPALETTE hPal);
	static WORD WINAPI DIBNumColors(LPSTR lpbi);
	static LPSTR WINAPI FindDIBBits(LPSTR lpbi);
	static void WINAPI InitBitmapInfoHeader(LPBITMAPINFOHEADER lpBmInfoHdr, long dwWidth, long dwHeight, short nBPP);
	static WORD WINAPI PaletteSize(LPSTR lpbi);
	void WINAPI ReleaseContents(void);
	static DWORD WidthBytes(DWORD bits) { return (((bits) + 31) / 32 * 4); }

	RECT WINAPI PaintDIB(CDC* dcp, CRect rectDest);
	BOOL WINAPI PaintDIB(HDC destDC, const int destX, const int destY, HPALETTE hPal = 0);
	BOOL WINAPI PaintDIB(HDC destDC, const RECT& destRect, const RECT& srcRect, HPALETTE hPal = 0);
	RECT WINAPI PaintDIBSagome(CDC* dcp, CRect rectDest);
	RECT WINAPI PaintDIBSagomeZoom(CDC* dcp, CRect rectDest, POINT ptToZoom);

	HBITMAP WINAPI BitmapFromDib(HDC hDC, HPALETTE hpal, WORD wUsage);
	
	// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	HBITMAP WINAPI DIBToDDB();								
	HANDLE WINAPI DDBToDIB(CBitmap& bitmap, DWORD dwCompression, CPalette* pPal);
	HANDLE WINAPI WriteWindowToDIB(CWnd *pWnd);
	void WriteBmpToFile(char* name, BITMAP *bmp, int* data);
	HANDLE m_hDIB_to_conversion;
	//

	LPLOGPALETTE WINAPI CreateLogPalette(BYTE entryFlags = 0) const;
	void WINAPI CopydaPalette(LPLOGPALETTE pPal);
  
	DWORD WINAPI GetSize(void) const;
	long	WINAPI Width (void) const;
	long	WINAPI Height (void) const;
	short	WINAPI PaletteSize (void) const;
	short	WINAPI PaletteSize (short numCol) const;
	short	WINAPI NumColors (void) const;
	BOOL	WINAPI IsValidDib(void) const {return (m_hDib != 0);}
	inline BOOL WINAPI Is256Index () {return (NumColors() == 256);}
	inline BOOL WINAPI IsRGB () {return (NumColors() == 0);}
	BYTE* WINAPI FindDIBBits (void) const;
	HGLOBAL WINAPI GetHandle(void) const {return m_hDib;}

	CDib& operator = (const CDib& rhs);
	HGLOBAL WINAPI Clone(void) const;
	BOOL WINAPI Attach(HGLOBAL dib, BOOL freeOnDelete = FALSE);
	HGLOBAL WINAPI Detach(void);
	BOOL WINAPI SetVetY();
	void WINAPI DeleteVetY();
	void WINAPI GetPixel(long x, long y, BYTE * ValPixel);
	void WINAPI GetPixel(long x, long y, BYTE * ValPixelR, BYTE * ValPixelG, BYTE * ValPixelB);

	enum { PVERSION = 0x300 };

	BYTE* m_pFDBits;
	DWORD m_nDimLine;
	BYTE** m_pVetY;

	// Sandro 26/06/2015 //
	void RotateSx();
	void RotateDx();

private:

	BOOL IsWin30(void) const { return ((*(LPDWORD)(m_lpbi)) == sizeof(BITMAPINFOHEADER)); }
	static HGLOBAL WINAPI CopyHandle (void);
	static HGLOBAL WINAPI CopyHandle (HGLOBAL h);

	HGLOBAL 		m_hDib;    // handle to block
	BOOL 			m_bAutoDelete;
	BYTE*			m_lpbi;    // points to base of memory

	BOOL WINAPI   DrawDIB (HDC destDC, const RECT& destRect, const RECT& srcRect, HPALETTE hPal = 0);
};

inline DWORD WINAPI CDib::GetSize(void) const
{
  DWORD result = *(LPDWORD)m_lpbi + PaletteSize();  // Partial Calculation
  LPBITMAPINFOHEADER lpBIH = LPBITMAPINFOHEADER(m_lpbi);
  // Now calculate the size of the image

  if ((lpBIH->biCompression == BI_RLE8) || (lpBIH->biCompression == BI_RLE4))
    result += lpBIH->biSizeImage;
  else
  {
    DWORD dwBmBitsSize;  // Size of Bitmap Bits only

    dwBmBitsSize = (DWORD)WidthBytes((lpBIH->biWidth)*(lpBIH->biBitCount)) * lpBIH->biHeight;

    result += dwBmBitsSize;

    // Now, since we have calculated the correct size, why don't we
    // fill in the biSizeImage field (this will fix any .BMP files which
    // have this field incorrect).

    lpBIH->biSizeImage = dwBmBitsSize;
  }

  return result;
  
}

inline long WINAPI CDib::Width (void) const
{
  if (IsWin30())
    return (long)LPBITMAPINFOHEADER(m_lpbi)->biWidth;
  else
    return (long)LPBITMAPCOREHEADER(m_lpbi)->bcWidth;
}

inline long WINAPI CDib::Height (void) const
{
  if (IsWin30())
    return (long)LPBITMAPINFOHEADER(m_lpbi)->biHeight;
  else
    return (long)LPBITMAPCOREHEADER(m_lpbi)->bcHeight;
}

inline short WINAPI CDib::PaletteSize (void) const
{
  if (IsWin30())
    return (short)(NumColors() * sizeof(RGBQUAD));
  else
    return (short)(NumColors() * sizeof(RGBTRIPLE));
}

inline short WINAPI CDib::PaletteSize (short numCol) const
{
  if (IsWin30())
    return (short)(numCol * sizeof(RGBQUAD));
  else
    return (short)(numCol * sizeof(RGBTRIPLE));
}

inline short WINAPI CDib::NumColors (void) const
{
  short colorCount = (short)(((LPBITMAPINFOHEADER)m_lpbi)->biClrUsed);

  if (!IsWin30() || !colorCount)
  {
	  short wBitCount;  // CDib bit count

	  if (IsWin30())
		  wBitCount = (short)((LPBITMAPINFOHEADER)m_lpbi)->biBitCount;
	  else
		  wBitCount = (short)((LPBITMAPCOREHEADER)m_lpbi)->bcBitCount;

	  if (wBitCount == 1 || wBitCount == 4 || wBitCount == 8)
		  colorCount = 1 << wBitCount;
  }

  return colorCount;
}

inline BYTE* WINAPI CDib::FindDIBBits (void) const
{
  return (BYTE*)m_lpbi + *(LPDWORD)m_lpbi + PaletteSize();
}
         
inline CDib& CDib::operator = (const CDib& rhs)
{
  if (&rhs != this)
    {
		ReleaseContents();	
		
		if (m_hDib = rhs.Clone())
		{
			m_bAutoDelete = TRUE;
			m_lpbi = (BYTE*)(::GlobalLock(m_hDib));
			LPBITMAPINFOHEADER lpBIH = LPBITMAPINFOHEADER(m_lpbi);
			m_nDimLine = WidthBytes((lpBIH->biWidth)*(lpBIH->biBitCount));
			m_pFDBits  = FindDIBBits();
			if (!SetVetY())
				ReleaseContents();
		}
    }
  return *this;
}

inline HGLOBAL CDib::Clone(void) const
{
  return CopyHandle(m_hDib);
}

inline void WINAPI CDib::ReleaseContents(void)
{
	if (m_hDIB_to_conversion)
	{
		GlobalFree(m_hDIB_to_conversion);
	}

  if (m_hDib)
    {
      ::GlobalUnlock(m_hDib);
      if (m_bAutoDelete)
        ::GlobalFree(m_hDib);
      Detach(); 
    }
}

inline BOOL WINAPI CDib::Attach(HGLOBAL dib, BOOL freeOnDelete)
{
	BOOL bReturn = FALSE;

	ReleaseContents();
	if (m_hDib = dib)
	{
		m_lpbi = (BYTE*)(::GlobalLock(m_hDib));
		m_bAutoDelete = freeOnDelete;
		LPBITMAPINFOHEADER lpBIH = LPBITMAPINFOHEADER(m_lpbi);
		m_nDimLine = WidthBytes((lpBIH->biWidth)*(lpBIH->biBitCount));
		m_pFDBits  = FindDIBBits();
		if (!SetVetY())
			ReleaseContents();

		bReturn = TRUE;
	}

	return bReturn;
}

inline HGLOBAL WINAPI CDib::Detach(void)
{
  HGLOBAL result;
  
  result	 = m_hDib;
  m_hDib 	 = NULL;
  m_lpbi	 = NULL;   
  m_pFDBits	 = NULL;
  m_nDimLine = 0;
  DeleteVetY();
  return result;
}

inline void WINAPI CDib::GetPixel(long x, long y, BYTE * ValPixel)
{
  *ValPixel = *(m_pVetY[y] + x);  
}
 
inline void WINAPI CDib::GetPixel(long x, long y, BYTE * ValPixelR, BYTE * ValPixelG, BYTE * ValPixelB)
{
  BYTE*	offset = (BYTE*)m_pVetY[y] + (DWORD)x * 3;
   
  *ValPixelB = *(offset++);
  *ValPixelG = *(offset++);
  *ValPixelR = *(offset);
}

#endif /* _CDIB_H_ */