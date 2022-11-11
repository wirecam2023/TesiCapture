#include "stdafx.h"
#include "Endox.h"
#include <windowsx.h>
#include "Dib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDib, CObject)

CDib::CDib()
	: CObject()
{ 
	m_bAutoDelete	= FALSE; 
	m_hDib			= NULL; 
	m_lpbi			= NULL; 
	m_pFDBits		= NULL;
	m_pVetY			= NULL;
	m_nDimLine		= 0;
	m_hDIB_to_conversion = NULL;
}

CDib::CDib(HGLOBAL dib, BOOL freeOnDelete)
	: CObject()
{
	m_bAutoDelete	= freeOnDelete;
	m_hDib			= NULL; 
	m_lpbi			= NULL; 
	m_pFDBits		= NULL;
	m_pVetY			= NULL;
	m_nDimLine		= 0;
	m_hDIB_to_conversion = NULL;

	m_hDib = CopyHandle(dib);
	
	if (m_hDib)
		m_lpbi = (BYTE*)::GlobalLock(m_hDib);

	if (m_lpbi)
	{
		LPBITMAPINFOHEADER lpBIH = LPBITMAPINFOHEADER(m_lpbi);
		m_nDimLine = WidthBytes((lpBIH->biWidth)*(lpBIH->biBitCount));
		m_pFDBits  = FindDIBBits();
		if (!SetVetY())
			ReleaseContents();
	}
}

CDib::CDib(const CDib& rhs)
	: CObject()
{
	m_bAutoDelete	= TRUE;
	m_hDib			= NULL; 
	m_lpbi			= NULL; 
	m_pFDBits		= NULL;
	m_pVetY			= NULL;
	m_nDimLine		= 0;
	m_hDIB_to_conversion = NULL;

	m_hDib = CopyHandle(rhs.m_hDib);
	
	if (m_hDib)
		m_lpbi = (BYTE*)::GlobalLock(m_hDib);

	if (m_lpbi)
	{
		LPBITMAPINFOHEADER lpBIH = LPBITMAPINFOHEADER(m_lpbi);
		m_nDimLine = WidthBytes((lpBIH->biWidth)*(lpBIH->biBitCount));
		m_pFDBits  = FindDIBBits();
		if (!SetVetY())
			ReleaseContents();
	}
}

CDib::~CDib()
{
	ReleaseContents();
}

WORD WINAPI CDib::DIBNumColors(LPSTR lpbi)
{
   WORD wBitCount;
   if (IS_WIN30_DIB (lpbi))
	  {
	  DWORD dwClrUsed;
	
	  dwClrUsed = ((LPBITMAPINFOHEADER) lpbi)->biClrUsed;
	
	  if (dwClrUsed)
	     return (WORD) dwClrUsed;
	  }

   if (IS_WIN30_DIB (lpbi))
      wBitCount = ((LPBITMAPINFOHEADER) lpbi)->biBitCount;
   else
      wBitCount = ((LPBITMAPCOREHEADER) lpbi)->bcBitCount;

   switch (wBitCount)
      {
      case 1:
         return 2;

      case 4:
         return 16;

      case 8:
         return 256;

      default:
         return 0;
      }
}

WORD WINAPI CDib::PaletteSize(LPSTR lpbi)
{
   if (IS_WIN30_DIB (lpbi))
      return (DIBNumColors (lpbi) * sizeof (RGBQUAD));
   else
      return (DIBNumColors (lpbi) * sizeof (RGBTRIPLE));
}

LPSTR WINAPI CDib::FindDIBBits(LPSTR lpbi)
{
   return (lpbi + *(LPDWORD)lpbi + PaletteSize (lpbi));
}

RECT WINAPI CDib::PaintDIB(CDC* dcp, CRect rectDest /* BOOL bPaintBorder, COLORREF rgbColorBorder */)
{
	RECT dest;
	RECT source;

	double a = (double)rectDest.Width();
	double b = (double)Width();
	double i = (double)rectDest.Height();
	double j = (double)Height();

	double dFactorX = a  / b;
	double dFactorY = i / j;

	dest.left = rectDest.left;
	dest.top = rectDest.top;
	dest.right  = (LONG)(rectDest.left + min(dFactorX, dFactorY) * Width());
	dest.bottom = (LONG)(rectDest.top  + min(dFactorX, dFactorY) * Height());
	dest.left += (rectDest.right - dest.right) / 2;
	dest.top += (rectDest.bottom - dest.bottom) / 2;
	dest.right  += (rectDest.right - dest.right) / 2;
	dest.bottom += (rectDest.bottom - dest.bottom) / 2;

	source.left = 0;
	source.top = 0;
	source.right = Width();
	source.bottom = Height();

	// if (bPaintBorder)
	{
		float fImmRapp = (float)Width() / (float)Height();
		float fFrameRapp = (float)rectDest.Width() / (float)rectDest.Height();
		CBrush brush(RGB(0, 0, 0));
		if (fFrameRapp < fImmRapp) // il frame è più alto rispetto all'immagine - bande sopra e sotto //
		{
			dcp->FillRect(CRect(rectDest.left, rectDest.top, rectDest.right, dest.top), &brush);
			dcp->FillRect(CRect(rectDest.left, dest.bottom, rectDest.right, rectDest.bottom), &brush);
		}
		else // l'immagine è più alta rispetto al frame - bande laterali //
		{
			dcp->FillRect(CRect(rectDest.left, rectDest.top, dest.left, rectDest.bottom), &brush);
			dcp->FillRect(CRect(dest.right, rectDest.top, rectDest.right, rectDest.bottom), &brush);
		}
	}

	PaintDIB(dcp->GetSafeHdc(), dest, source);

	return dest;
}

BOOL WINAPI CDib::PaintDIB(HDC destDC, const int destX, const int destY, HPALETTE hPal)
{
	RECT dest, source;           
	
	source.left		= 0;
	source.top		= 0;
	source.right	= Width();
	source.bottom	= Height();
	dest.left		= destX;
	dest.top		= destY;
	dest.right		= destX + source.right;
	dest.bottom		= destY + source.bottom;
	
	return PaintDIB(destDC, dest, source, hPal);
}

BOOL WINAPI CDib::PaintDIB(HDC destDC, const RECT& destRect, const RECT& srcRect, HPALETTE hPal)
{
	BOOL bResult = FALSE;

	if (IsRGB())
	{
		bResult = DrawDIB(destDC, destRect, srcRect, hPal);
	}
	else
	{
		LPLOGPALETTE	pPalette;
		HPALETTE		hpalGray;
		
	    pPalette = CreateLogPalette();

		if (pPalette)
		{
			hpalGray = ::CreatePalette(pPalette);
		
			bResult = DrawDIB(destDC, destRect, srcRect, hpalGray);
		
			::DeleteObject(hpalGray);

			GlobalFreePtr(pPalette);
		}
	}

	return bResult;
}

RECT WINAPI CDib::PaintDIBSagome(CDC* dcp, CRect rectDest)
{
	RECT dest;
	RECT source;

	double dFactorX = (double)rectDest.Width()  / (double)Width();
	double dFactorY = (double)rectDest.Height() / (double)Height();
	double dFactorMin = min(dFactorX, dFactorY);

	dest.left = rectDest.left;
	dest.top = rectDest.top;
	dest.right  = (LONG)((dFactorMin * (double)Width()) + (double)rectDest.left);
	dest.bottom = (LONG)((dFactorMin * (double)Height()) + (double)rectDest.top);
	dest.left += (rectDest.right - dest.right) / 2;
	dest.top += (rectDest.bottom - dest.bottom) / 2;
	dest.right += (rectDest.right - dest.right) / 2;
	dest.bottom += (rectDest.bottom - dest.bottom) / 2;

	source.left = 0;
	source.top = 0;
	source.right = Width();
	source.bottom = Height();

	double dImmRapp = (double)Width() / (double)Height();
	double dFrameRapp = (double)rectDest.Width() / (double)rectDest.Height();

	CBrush brush(RGB_BLACK);
	if (dFrameRapp < dImmRapp)
	{
		// il frame è più alto rispetto all'immagine - bande sopra e sotto //

		dcp->FillRect(CRect(rectDest.left, rectDest.top, rectDest.right, dest.top), &brush);
		dcp->FillRect(CRect(rectDest.left, dest.bottom, rectDest.right, rectDest.bottom), &brush);
	}
	else
	{
		// l'immagine è più alta rispetto al frame - bande laterali //

		dcp->FillRect(CRect(rectDest.left, rectDest.top, dest.left, rectDest.bottom), &brush);
		dcp->FillRect(CRect(dest.right, rectDest.top, rectDest.right, rectDest.bottom), &brush);
	}

	PaintDIB(dcp->GetSafeHdc(), dest, source);

	return dest;
}

RECT WINAPI CDib::PaintDIBSagomeZoom(CDC* dcp, CRect rectDest, POINT ptToZoom)
{
	// prendo una piccola porzione della DIB e la mostro a schermo zoomata al 200% //

	RECT dest;
	dest.left = rectDest.left;
	dest.top = rectDest.top;
	dest.right = rectDest.right;
	dest.bottom = rectDest.bottom;

	RECT source;
	source.left = ptToZoom.x - (rectDest.Width() / 4);
	source.top = ptToZoom.y - (rectDest.Height() / 4);
	source.right = ptToZoom.x + (rectDest.Width() / 4);
	source.bottom = ptToZoom.y + (rectDest.Height() / 4);

	PaintDIB(dcp->GetSafeHdc(), dest, source);

	// disegno il "mirino" del cursore //

	CPen penTemp(PS_SOLID, 5, RGB_GREEN);
	CPen* p_PenPrev = dcp->SelectObject(&penTemp);

	dcp->MoveTo(((rectDest.left + rectDest.right) / 2) - 28, (rectDest.top + rectDest.bottom) / 2);
	dcp->LineTo(((rectDest.left + rectDest.right) / 2) -  8, (rectDest.top + rectDest.bottom) / 2);

	dcp->MoveTo(((rectDest.left + rectDest.right) / 2) + 28, (rectDest.top + rectDest.bottom) / 2);
	dcp->LineTo(((rectDest.left + rectDest.right) / 2) +  8, (rectDest.top + rectDest.bottom) / 2);

	dcp->MoveTo((rectDest.left + rectDest.right) / 2, ((rectDest.top + rectDest.bottom) / 2) - 28);
	dcp->LineTo((rectDest.left + rectDest.right) / 2, ((rectDest.top + rectDest.bottom) / 2) -  8);

	dcp->MoveTo((rectDest.left + rectDest.right) / 2, ((rectDest.top + rectDest.bottom) / 2) + 28);
	dcp->LineTo((rectDest.left + rectDest.right) / 2, ((rectDest.top + rectDest.bottom) / 2) +  8);

	dcp->SelectObject(p_PenPrev);

	return source;
}

BOOL WINAPI CDib::DrawDIB (HDC destDC, const RECT& destRect, const RECT& srcRect, HPALETTE hPal)
{
	BOOL	result		= FALSE;
	short	modePalette = DIB_RGB_COLORS;

	if (m_hDib)
	{
		//LPBYTE lpbits = FindDIBBits();
		HPALETTE hOldPal = NULL;

		if (hPal)
		{
			hOldPal = ::SelectPalette(destDC, hPal, TRUE);
			::RealizePalette(destDC);
		}

		// Determine whether to call StretchDIBits() or SetDIBitsToDevice() 
		if (((destRect.right - destRect.left) == (srcRect.right-srcRect.left)) &&
			((destRect.bottom - destRect.top) == (srcRect.bottom - srcRect.top)))
		{
			result = ::SetDIBitsToDevice(destDC,         
										 destRect.left,                  
										 destRect.top,                   
										 destRect.right - destRect.left, 
										 destRect.bottom - destRect.top, 
										 srcRect.left,
										 Height() - srcRect.bottom, 
										 0,             
										 (UINT)Height(),
										 m_pFDBits, //FindDIBBits(), 
										 (LPBITMAPINFO)m_lpbi,
										 modePalette);
		}
		else
		{
			POINT ptOrg;

			::SetStretchBltMode(destDC, HALFTONE);
			//::SetStretchBltMode(destDC, COLORONCOLOR);

			//int iScannedLines = ::StretchDIBits(hDC,    dstRect.left,  dstRect.top,  dstRect.Width(),                dstRect.Height(),               srcRect.left, srcRect.top, srcRect.Width(),              srcRect.Height(),             pCurrentPos, pBitmapInfo,        DIB_RGB_COLORS, SRCCOPY);
			result =			  ::StretchDIBits(destDC, destRect.left, destRect.top, destRect.right - destRect.left, destRect.bottom - destRect.top, srcRect.left, srcRect.top, srcRect.right - srcRect.left, srcRect.bottom - srcRect.top, m_pFDBits, (LPBITMAPINFO)m_lpbi, modePalette,    SRCCOPY);

			//solo se uso HALFTONE...
			::SetBrushOrgEx(destDC, 0, 0, &ptOrg);
		}

		// Reselect old palette 
		if (hOldPal)
		{
			::SelectPalette(destDC, hOldPal, TRUE);
		}
	}

	return result;
}     


void WINAPI   
CDib::CopydaPalette(LPLOGPALETTE pPal)
{
	if (m_hDib && NumColors())
	{
		short	numcol = NumColors();
		
		if (IsWin30())
		{
			for(short i = 0; i < numcol; i++)
			{
				LPBITMAPINFO(m_lpbi)->bmiColors[i].rgbRed   = pPal->palPalEntry[i].peRed;
				LPBITMAPINFO(m_lpbi)->bmiColors[i].rgbGreen = pPal->palPalEntry[i].peGreen;
				LPBITMAPINFO(m_lpbi)->bmiColors[i].rgbBlue  = pPal->palPalEntry[i].peBlue;
			}
		}
		else // OS2
		{
			for(short i = 0; i < numcol; i++)
			{
				LPBITMAPCOREINFO(m_lpbi)->bmciColors[i].rgbtRed   = pPal->palPalEntry[i].peRed;
				LPBITMAPCOREINFO(m_lpbi)->bmciColors[i].rgbtGreen = pPal->palPalEntry[i].peGreen;
				LPBITMAPCOREINFO(m_lpbi)->bmciColors[i].rgbtBlue  = pPal->palPalEntry[i].peBlue;
			}
		}
	}
}


LPLOGPALETTE WINAPI   
CDib::CreateLogPalette(BYTE entryFlags) const
{
	LPLOGPALETTE result = 0;      // pointer to a logical palette
	
	if (m_hDib)
	{
		if (NumColors() > 0)
			result = (LPLOGPALETTE)GlobalAllocPtr(GHND, sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * NumColors());

		if (result)
		{
			result->palVersion 		= PVERSION;
			result->palNumEntries 	= (WORD)NumColors();

			if (IsWin30())
			{
				for(WORD i = 0; i < result->palNumEntries; i++)
				{
					result->palPalEntry[i].peRed   = LPBITMAPINFO(m_lpbi)->bmiColors[i].rgbRed;
					result->palPalEntry[i].peGreen = LPBITMAPINFO(m_lpbi)->bmiColors[i].rgbGreen;
					result->palPalEntry[i].peBlue  = LPBITMAPINFO(m_lpbi)->bmiColors[i].rgbBlue;
					result->palPalEntry[i].peFlags = entryFlags;
				}
			}
			else // OS2
			{
				for(WORD i = 0; i < result->palNumEntries; i++)
				{
					result->palPalEntry[i].peRed   = LPBITMAPCOREINFO(m_lpbi)->bmciColors[i].rgbtRed;
					result->palPalEntry[i].peGreen = LPBITMAPCOREINFO(m_lpbi)->bmciColors[i].rgbtGreen;
					result->palPalEntry[i].peBlue  = LPBITMAPCOREINFO(m_lpbi)->bmciColors[i].rgbtBlue;
					result->palPalEntry[i].peFlags = entryFlags;
				}
			}
		}
		else
		{
			BYTE	red, green, blue;
							
			result = (LPLOGPALETTE)GlobalAllocPtr(GHND, sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256);
				
			if (result)
			{
				result->palVersion 		= PVERSION;
				result->palNumEntries 	= 256;
				red = green = blue = 0;
					
				for(WORD i = 0; i < result->palNumEntries; i++)
				{
					result->palPalEntry[i].peRed   = red;
					result->palPalEntry[i].peGreen = green;
					result->palPalEntry[i].peBlue  = blue;
					result->palPalEntry[i].peFlags = entryFlags;
									    
					//red++; green++; blue++;
					if (!(red += 32))
						if (!(green += 32))
							blue += 64;
				}
	    	}
		}
	}
	return result;
}

HGLOBAL WINAPI CDib::CopyHandle (HGLOBAL h)
{
	BYTE *lpCopy;
	BYTE *lp;
	HGLOBAL     hCopy;
	DWORD      dwLen;

	if (h == NULL)
		return NULL;

	dwLen = ::GlobalSize((HGLOBAL) h);
	
	DWORD 	nBlock = (DWORD)dwLen / 65535;
	DWORD	nBytes = (DWORD)nBlock * 65535;
	DWORD 	nResto = dwLen - nBytes;

	if ((hCopy = (HGLOBAL) ::GlobalAlloc (GHND, dwLen)) != NULL)
	{
		lpCopy = (BYTE *) ::GlobalLock((HGLOBAL) hCopy);
		lp     = (BYTE *) ::GlobalLock((HGLOBAL) h);
		
		for(DWORD i=0; i<nBlock; i++)
  			memmove((BYTE *)(lpCopy+(DWORD)i*65535), (BYTE *)(lp+(DWORD)i*65535), (size_t)65535);
		
		if (nResto)
 			memmove((BYTE *)(lpCopy+nBytes), (BYTE *)(lp+nBytes), (size_t)nResto);
		
		/*
		while (dwLen--)
			*lpCopy++ = *lp++;
        **/
		
		::GlobalUnlock((HGLOBAL) hCopy);
		::GlobalUnlock((HGLOBAL) h);
	}
	return hCopy;
}

/*
BOOL DIBFileHandle::ReadHuge(void FAR *buf, DWORD byteCount)
{
  BOOL result = FALSE;

#ifdef _WIN32
  DWORD bytesRead;
  if (ReadFile(hFile, buf, byteCount, &bytesRead, NULL))
    result = (bytesRead == byteCount);
#else
  result = ((DWORD)_hread((HFILE)hFile, buf, byteCount) == byteCount);
#endif  

  return result;
}

BOOL DIBFileHandle::WriteHuge(const void FAR *buf, DWORD byteCount)
{
  BOOL result = FALSE;

#ifdef _WIN32
  DWORD bytesWritten;
  if (WriteFile(hFile, buf, byteCount, &bytesWritten, NULL))
    result = (bytesWritten == byteCount);
#else
  result = ((DWORD)_hwrite((HFILE)hFile, buf, byteCount) == byteCount);
#endif  

  return result;
}

BOOL CDib::FileBase::WriteDIB(const CDib& dib)
{
  BOOL result = FALSE;
  HGLOBAL m_hDib = dib.GetHandle();

  if (m_hDib)
    {
      LPBITMAPINFOHEADER m_lpbi = (LPBITMAPINFOHEADER) ::GlobalLock(m_hDib);
      BITMAPFILEHEADER bmfHdr; 

      bmfHdr.bfType = BM_MARK;  
      bmfHdr.bfSize = dib.GetSize() + sizeof(BITMAPFILEHEADER);
      bmfHdr.bfReserved1 = 0;
      bmfHdr.bfReserved2 = 0;

      bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + m_lpbi->biSize + dib.PaletteSize();
      result = WriteHuge(&bmfHdr, sizeof(BITMAPFILEHEADER)) && WriteHuge(m_lpbi, dib.GetSize());
      ::GlobalUnlock(dib.GetHandle());
    }
  
  return result;
}

BOOL CDib::FileBase::ReadDIB(CDib& dib)
{
  BOOL result = FALSE;
  BOOL os2 = FALSE;
  BITMAPFILEHEADER bmfHeader;
  BITMAPINFOHEADER bi;


  if (ReadHuge(&bmfHeader, sizeof(bmfHeader)) && (bmfHeader.bfType == BM_MARK))
    {
      BOOL goOn = ReadHuge(&bi, sizeof(DWORD));
      if (goOn)
        {
          switch (bi.biSize)
            {
              case sizeof(BITMAPINFOHEADER):
                goOn = ReadHuge(&bi.biWidth, sizeof(bi) - sizeof(DWORD));
                break;
              case sizeof(BITMAPCOREHEADER):
                {
                  BITMAPCOREHEADER bci;
                  goOn = ReadHuge(&bci.bcWidth, sizeof(BITMAPCOREHEADER) - sizeof(DWORD));
                  bi.biSize               = sizeof(BITMAPINFOHEADER);
                  bi.biWidth              = bci.bcWidth;
                  bi.biHeight             = bci.bcHeight;
                  bi.biPlanes             = bci.bcPlanes;
                  bi.biBitCount           = bci.bcBitCount;

                  bi.biCompression        = BI_RGB;
                  bi.biSizeImage          = 0;
                  bi.biXPelsPerMeter      = 96;
                  bi.biYPelsPerMeter      = 96;
                  bi.biClrUsed            = 0;
                  bi.biClrImportant       = 0;
                  os2 = TRUE;
                           
                }
            }
        }      
      
      if (goOn)
        {
          // fill in values      
          if (!bi.biSizeImage)
            bi.biSizeImage = (DWORD)bi.biHeight * CDib::WidthBytes (bi.biWidth * bi.biBitCount);

          if (!bi.biClrUsed)
            if (bi.biBitCount == 1 || bi.biBitCount == 4 || bi.biBitCount == 8)
              bi.biClrUsed = 1 << bi.biBitCount;
            
          const DWORD allocSize = sizeof (bi) + bi.biClrUsed * sizeof(RGBQUAD) + bi.biSizeImage;
          HGLOBAL m_hDib = ::GlobalAlloc(GHND, allocSize);
          if (m_hDib)
            {
              LPBYTE base = (LPBYTE)GlobalLock(m_hDib);
              LPBITMAPINFOHEADER m_lpbi = LPBITMAPINFOHEADER(base);
              *m_lpbi = bi;
              base += sizeof(BITMAPINFOHEADER);
              RGBQUAD FAR *pRGB4 = (RGBQUAD FAR *)base;
              base += bi.biClrUsed * sizeof(RGBQUAD);

              if (os2 && bi.biClrUsed)
                {
                  RGBTRIPLE FAR* pRGB3 = (RGBTRIPLE FAR*)
                                          GlobalAllocPtr(GHND, bi.biClrUsed * sizeof(RGBTRIPLE));

                  ReadHuge(pRGB3,bi.biClrUsed * sizeof(RGBTRIPLE)); 
        
                  for(DWORD i = 0; i < bi.biClrUsed; i++)
                    {
                      pRGB4[i].rgbRed = pRGB3[i].rgbtRed;
                      pRGB4[i].rgbGreen = pRGB3[i].rgbtGreen;
                      pRGB4[i].rgbBlue = pRGB3[i].rgbtBlue;
                    }  
                }
              else
                ReadHuge(pRGB4, bi.biClrUsed * sizeof(RGBQUAD));



              if (ReadHuge(base, bi.biSizeImage))
                {
                  // success!!
                  GlobalUnlock(m_hDib);
                  dib.Attach(m_hDib, TRUE); // yes delete please...
                }
              else
                {
                  // read failed, free memory
                  GlobalUnlock(m_hDib);
                  GlobalFree(m_hDib);
                }
            }
        }
    }
  return result;
}
*/

BOOL CDib::SetVetY()
{
	long lMaxY = Height();
	
	m_pVetY = (BYTE **)GlobalAllocPtr(GHND, (DWORD)(lMaxY + 1) * sizeof(BYTE*));

	if (m_pVetY == NULL)
		return FALSE;
	
	for (long y = 0; y <= lMaxY; y++)
		m_pVetY[y] = (BYTE *)m_pFDBits + (DWORD)y * m_nDimLine;
	
	return TRUE;
}

void CDib::DeleteVetY()
{   
	if (m_pVetY)
	{
		//_ffree(m_pVetY);
		GlobalFreePtr(m_pVetY);
		m_pVetY = NULL;
	}
}

// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
HBITMAP WINAPI CDib::BitmapFromDib(HDC hDC, HPALETTE hpal, WORD wUsage)
{
    HPALETTE    	hpalT = NULL;
    HBITMAP     	hBmp  = NULL;
    LPLOGPALETTE 	pLogPalette = NULL;
    
    if (!hpal)
    {
   		pLogPalette = CreateLogPalette();
    
		hpal = CreatePalette(pLogPalette);
	}
    
	hpalT = SelectPalette(hDC,hpal,FALSE);
	RealizePalette(hDC);

    hBmp = CreateDIBitmap(hDC,
                          (LPBITMAPINFOHEADER)m_lpbi,
                          CBM_INIT,
                          m_pFDBits, //FindDIBBits(),
                          (LPBITMAPINFO)m_lpbi,
                          wUsage);
    if (hpalT)
        SelectPalette(hDC,hpalT,FALSE);
        
   	if (pLogPalette)
   	{
   		GlobalFreePtr(pLogPalette);
   		DeleteObject(hpal);
   	}

    return hBmp;
}


void WINAPI CDib::InitBitmapInfoHeader (LPBITMAPINFOHEADER lpBmInfoHdr, long dwWidth, long dwHeight, short nBPP)
{
	if (nBPP <= 1)
		nBPP = 1;
	else
		if (nBPP <= 4)
			nBPP = 4;
		else 
			if (nBPP <= 8)
				nBPP = 8;
			else
				nBPP = 24;

	_fmemset (lpBmInfoHdr, 0, sizeof (BITMAPINFOHEADER));
	
	lpBmInfoHdr->biSize			= sizeof (BITMAPINFOHEADER);
	lpBmInfoHdr->biWidth		= dwWidth;
	lpBmInfoHdr->biHeight 		= dwHeight;
	lpBmInfoHdr->biPlanes		= 1;
	lpBmInfoHdr->biCompression 	= BI_RGB;
	lpBmInfoHdr->biXPelsPerMeter=96;
	lpBmInfoHdr->biYPelsPerMeter=96;
	lpBmInfoHdr->biClrUsed   	= 0;
	lpBmInfoHdr->biClrImportant = 0;
	lpBmInfoHdr->biBitCount  	= nBPP;
	lpBmInfoHdr->biSizeImage 	= dwHeight * CDib::WidthBytes(dwWidth * nBPP);
}

// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
//ref page: https://www.codeguru.com/cpp/g-m/bitmap/article.php/c1757/Converting-DIB-to-DDB.htm
HBITMAP WINAPI CDib::DIBToDDB()
{
	HANDLE hDIB = m_hDib;

	LPBITMAPINFOHEADER	lpbi;
	HBITMAP 		hbm;
	CPalette		pal;
	CPalette*		pOldPal;
	CClientDC		dc(NULL);

	if (hDIB == NULL)
		return NULL;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	int nColors = lpbi->biClrUsed ? lpbi->biClrUsed :
		1 << lpbi->biBitCount;

	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB;
	LPVOID lpDIBBits;
	if (bmInfo.bmiHeader.biBitCount > 8)
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors +
		bmInfo.bmiHeader.biClrUsed) +
		((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);

	// Create and select a logical palette if needed
	if (nColors <= 256 && dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;

		for (int i = 0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
			pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}

		pal.CreatePalette(pLP);

		delete[] pLP;

		// Select and realize the palette
		pOldPal = dc.SelectPalette(&pal, FALSE);
		dc.RealizePalette();
	}


	hbm = CreateDIBitmap(dc.GetSafeHdc(),		// handle to device context
		(LPBITMAPINFOHEADER)lpbi,	// pointer to bitmap info header 
		(LONG)CBM_INIT,			// initialization flag
		lpDIBBits,			// pointer to initialization data 
		(LPBITMAPINFO)lpbi,		// pointer to bitmap info
		DIB_RGB_COLORS);		// color-data usage 

	if (pal.GetSafeHandle())
		dc.SelectPalette(pOldPal, FALSE);

	return hbm;
}

// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
// ref page: https://www.codeguru.com/cpp/g-m/bitmap/article.php/c1765/Converting-DDB-to-DIB.htm
// DDBToDIB		- Creates a DIB from a DDB
// bitmap		- Device dependent bitmap
// dwCompression	- Type of compression - see BITMAPINFOHEADER
// pPal			- Logical palette
// ATENÇÃO:
// Necessário manter o Objeto CDib vivo para usar o HANDLE objtido
// após o ~CDib... o espaço do HANDLE será desalocado
HANDLE CDib::DDBToDIB(CBitmap& bitmap, DWORD dwCompression, CPalette* pPal)
{
	BITMAP			bm;
	BITMAPINFOHEADER	bi;
	LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	
	HANDLE			handle;
	HDC 			hDC;
	HPALETTE		hPal;

	ASSERT(bitmap.GetSafeHandle());

	// The function has no arg for bitfields
	if (dwCompression == BI_BITFIELDS)
		return NULL;

	// If a palette has not been supplied use defaul palette
	hPal = (HPALETTE)pPal->GetSafeHandle();
	if (hPal == NULL)
		hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	bitmap.GetObject(sizeof(bm), (LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bm.bmWidth;
	bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression = dwCompression;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if (nColors > 256)
		nColors = 0;
	dwLen = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC = GetDC(NULL);
	hPal = SelectPalette(hDC, hPal, FALSE);
	RealizePalette(hDC);

	// Allocate enough memory to hold bitmapinfoheader and color table
	m_hDIB_to_conversion = GlobalAlloc(GMEM_FIXED, dwLen);

	if (!m_hDIB_to_conversion){
		SelectPalette(hDC, hPal, FALSE);
		ReleaseDC(NULL, hDC);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)m_hDIB_to_conversion;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
		(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8)
			* bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(m_hDIB_to_conversion, dwLen, GMEM_MOVEABLE))
		m_hDIB_to_conversion = handle;
	else
	{
		GlobalFree(m_hDIB_to_conversion);
		m_hDIB_to_conversion = NULL;

		// Reselect the original palette
		SelectPalette(hDC, hPal, FALSE);
		ReleaseDC(NULL, hDC);
		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)m_hDIB_to_conversion;

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(),
		0L,				// Start scan line
		(DWORD)bi.biHeight,		// # of scan lines
		(LPBYTE)lpbi 			// address for bitmap bits
		+ (bi.biSize + nColors * sizeof(RGBQUAD)),
		(LPBITMAPINFO)lpbi,		// address of bitmapinfo
		(DWORD)DIB_RGB_COLORS);		// Use RGB for color table

	if (!bGotBits)
	{
		GlobalFree(m_hDIB_to_conversion);
		m_hDIB_to_conversion = NULL;

		SelectPalette(hDC, hPal, FALSE);
		ReleaseDC(NULL, hDC);
		return NULL;
	}

	SelectPalette(hDC, hPal, FALSE);
	ReleaseDC(NULL, hDC);
	return m_hDIB_to_conversion;
}


// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
// ref page: https://www.codeguru.com/cpp/g-m/bitmap/article.php/c1741/Writing-a-window-image-to-a-BMP-file.htm
// ATENÇÃO:
// Necessário manter o Objeto CDib vivo para usar o HANDLE objtido
// após o ~CDib... o espaço do HANDLE será desalocado
HANDLE WINAPI CDib::WriteWindowToDIB(CWnd *pWnd)
{
	CBitmap     bitmap;
	CWindowDC   dc(pWnd);
	CDC         memDC;
	CRect       rect;

	memDC.CreateCompatibleDC(&dc);

	pWnd->GetWindowRect(rect);

	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);

	// Create logical palette if device support a palette
	CPalette pal;
	if (dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
		pLP->palVersion = 0x300;

		pLP->palNumEntries =
			GetSystemPaletteEntries(dc, 0, 255, pLP->palPalEntry);

		// Create the palette
		pal.CreatePalette(pLP);

		delete[] pLP;
	}

	memDC.SelectObject(pOldBitmap);

	// Convert the bitmap to a DIB
	HANDLE hDIB = DDBToDIB(bitmap, BI_RGB, &pal);
	return hDIB;
}

void CDib::WriteBmpToFile(char* name, BITMAP *bmp, int* data)
{
	BITMAPINFO Bmi;
	memset(&Bmi, 0, sizeof(BITMAPINFO));
	Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Bmi.bmiHeader.biWidth = bmp->bmWidth;
	Bmi.bmiHeader.biHeight = bmp->bmHeight;
	Bmi.bmiHeader.biPlanes = 1;
	Bmi.bmiHeader.biBitCount = bmp->bmBitsPixel;
	Bmi.bmiHeader.biCompression = BI_RGB;
	Bmi.bmiHeader.biSizeImage = bmp->bmHeight*bmp->bmWidth*bmp->bmBitsPixel / 8;

	FILE* fileDest = fopen(name, "wb");
	if (fileDest == 0)
		return;
	int h = abs(Bmi.bmiHeader.biHeight);
	int w = abs(Bmi.bmiHeader.biWidth);
	Bmi.bmiHeader.biHeight = h;
	Bmi.bmiHeader.biWidth = w;
	int sz = Bmi.bmiHeader.biSizeImage;

	BITMAPFILEHEADER bfh;
	bfh.bfType = ('M' << 8) + 'B';
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bfh.bfSize = sz + bfh.bfOffBits;
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	fwrite(&bfh, sizeof(bfh), 1, fileDest);
	fwrite(&Bmi.bmiHeader, sizeof(BITMAPINFOHEADER), 1, fileDest);
	fwrite(data, sz, 1, fileDest);
	fclose(fileDest);
}

HGLOBAL WINAPI CDib::BitmapToDIB (HBITMAP hBitmap, HPALETTE hPal)
{
	BITMAP             Bitmap;
	BITMAPINFOHEADER   bmInfoHdr;
	LPBITMAPINFOHEADER lpbmInfoHdr;
	LPSTR              lpBits;
	HDC                hMemDC;
	HGLOBAL            hDIB;
	HPALETTE           hOldPal = NULL;

	// Do some setup -- make sure the Bitmap passed in is valid,
	//  get info on the bitmap (like its height, width, etc.),
	//  then setup a BITMAPINFOHEADER.

   if (!hBitmap)
      return NULL;

   if (!GetObject (hBitmap, sizeof (Bitmap), (LPSTR) &Bitmap))
      return NULL;

   InitBitmapInfoHeader (&bmInfoHdr,
                         Bitmap.bmWidth,
                         Bitmap.bmHeight,
                         Bitmap.bmPlanes * Bitmap.bmBitsPixel);

	// Now allocate memory for the DIB.  Then, set the BITMAPINFOHEADER
	//  into this memory, and find out where the bitmap bits go.

	hDIB = GlobalAlloc (GHND, sizeof (BITMAPINFOHEADER) +
						PaletteSize ((LPSTR) &bmInfoHdr) + bmInfoHdr.biSizeImage);
	
	if (!hDIB)
		return NULL;

	lpbmInfoHdr  = (LPBITMAPINFOHEADER) GlobalLock (hDIB);
	*lpbmInfoHdr = bmInfoHdr;
	lpBits       = FindDIBBits ((LPSTR) lpbmInfoHdr);
	
	
	// Now, we need a DC to hold our bitmap.  If the app passed us
	//  a palette, it should be selected into the DC.
	
	hMemDC = GetDC (NULL);
	
	if (hPal)
	{
		hOldPal = SelectPalette (hMemDC, hPal, FALSE);
		RealizePalette (hMemDC);
	}

	// We're finally ready to get the DIB.  Call the driver and let
	//  it party on our bitmap.  It will fill in the color table,
	//  and bitmap bits of our global memory block.

	if (!GetDIBits (hMemDC,
					hBitmap,
					0,
					Bitmap.bmHeight,
					lpBits,
					(LPBITMAPINFO) lpbmInfoHdr,
					DIB_RGB_COLORS))
	{
		GlobalUnlock (hDIB);
		GlobalFree (hDIB);
		hDIB = NULL;
	}
	else
	{
		GlobalUnlock (hDIB);
	}

	// Finally, clean up and return.
	
	if (hOldPal)
		SelectPalette (hMemDC, hOldPal, FALSE);
	
	ReleaseDC (NULL, hMemDC);
	
	return hDIB;
}

// Sandro 26/06/2015 //
void CDib::RotateSx()
{
	long lRows = Width();
	long lCols = Height(); 

	// calcolo quanti byte servono per ciascun pixel //

	long lBytePerPixel = 0;
	switch (NumColors())
	{
		case 0: // truecolor //
		{
			lBytePerPixel = 3;
			break;
		}
		case 256:
		{
			lBytePerPixel = 1;
			break;
		}
		default:
		{
			ASSERT(FALSE);
			return;
		}
	}

	// faccio una copia del buffer originale girandolo già (e svuotandolo) //

	BYTE* pOriginalBuffer = new BYTE[lRows * lCols * lBytePerPixel];
	for (long x = 0; x < lCols; x++)
	{
		for (long y = 0; y < lRows; y++)
		{
			for (long z = 0; z < lBytePerPixel; z++)
			{
				// pOriginalBuffer[(y * lCols * lBytePerPixel) + (x * lBytePerPixel) + z] = m_pFDBits[(x * m_nDimLine) + (((lCols - 1) - y) * lBytePerPixel) + z];
				m_pFDBits[(x * m_nDimLine) + (((lCols - 1) - y) * lBytePerPixel) + z] = 0;
			}
		}
	}


	/*
	for (long x = 0; x < lOriginalHeight; x++)
	{
		for (long y = 0; y < lHeight; y++)
		{
			for (long z = 0; z < lBytePerPixel; z++)
			{
				pOriginalBuffer[(lWidth * y * lBytePerPixel) + (x * lBytePerPixel) + z] = m_pFDBits[(m_nDimLine * y) + (x * lBytePerPixel) + z];
				m_pFDBits[(m_nDimLine * y) + (x * lBytePerPixel) + z] = 0;
			}
		}
	}
	*/

	// cancello m_pVetY //

	DeleteVetY();

	/*
	// scambio le dimensioni "larghezza" e "altezza" //

	if (IsWin30())
	{
		LONG lTemp = LPBITMAPINFOHEADER(m_lpbi)->biWidth;
		LPBITMAPINFOHEADER(m_lpbi)->biWidth = LPBITMAPINFOHEADER(m_lpbi)->biHeight;
		LPBITMAPINFOHEADER(m_lpbi)->biHeight = lTemp;

		m_nDimLine = WidthBytes((LPBITMAPINFOHEADER(m_lpbi)->biWidth)*(LPBITMAPINFOHEADER(m_lpbi)->biBitCount));
	}
	else
	{
		WORD wTemp = LPBITMAPCOREHEADER(m_lpbi)->bcWidth;
		LPBITMAPCOREHEADER(m_lpbi)->bcWidth = LPBITMAPCOREHEADER(m_lpbi)->bcHeight;
		LPBITMAPCOREHEADER(m_lpbi)->bcHeight = wTemp;

		m_nDimLine = WidthBytes((LPBITMAPCOREHEADER(m_lpbi)->bcWidth)*(LPBITMAPCOREHEADER(m_lpbi)->bcBitCount));
	}

	// ricopio di nuovo dal buffer temporaneo al buffer originale, cambiando la posizione dei pixel //

	for (long x = 0; x < lHeight; x++) // lHeight e lWidth adesso sono invertiti //
		for (long y = 0; y < lWidth; y++) // lHeight e lWidth adesso sono invertiti //
			for (long z = 0; z < lBytePerPixel; z++)
				m_pFDBits[(m_nDimLine * y) + (x * lBytePerPixel) + z] = pOriginalBuffer[(lWidth * x * lBytePerPixel) + ((lWidth - y) * lBytePerPixel) + z];
	*/

	// cancello il buffer temporaneo //

	delete pOriginalBuffer;

	// ricreo m_pVetY //

	SetVetY();
}

// Sandro 26/06/2015 //
void CDib::RotateDx()
{
	// scambio le dimensioni "larghezza" e "altezza" //

	if (IsWin30())
	{
		LONG lTemp = LPBITMAPINFOHEADER(m_lpbi)->biWidth;
		LPBITMAPINFOHEADER(m_lpbi)->biWidth = LPBITMAPINFOHEADER(m_lpbi)->biHeight;
		LPBITMAPINFOHEADER(m_lpbi)->biHeight = lTemp;
	}
	else
	{
		WORD wTemp = LPBITMAPCOREHEADER(m_lpbi)->bcWidth;
		LPBITMAPCOREHEADER(m_lpbi)->bcWidth = LPBITMAPCOREHEADER(m_lpbi)->bcHeight;
		LPBITMAPCOREHEADER(m_lpbi)->bcHeight = wTemp;
	}
}
