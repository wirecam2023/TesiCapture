#include "stdafx.h"
#include "Endox.h"
#include "ImageElaboration.h"

#include <GdiPlus.h>

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImageElaboration::CImageElaboration(HBITMAP hBitmap)
{
	m_hBitmap = hBitmap;
}

CImageElaboration::~CImageElaboration(void)
{
}

HBITMAP CImageElaboration::ApplyBrightnessContrast(int iBrightness, int iContrastRMin, int iContrastRMax, int iContrastGMin, int iContrastGMax, int iContrastBMin, int iContrastBMax)
{
	ASSERT(iContrastRMin >= 0 && iContrastRMax <= 255 && iContrastRMax > iContrastRMin);
	ASSERT(iContrastGMin >= 0 && iContrastGMax <= 255 && iContrastGMax > iContrastGMin);
	ASSERT(iContrastBMin >= 0 && iContrastBMax <= 255 && iContrastBMax > iContrastBMin);
	ASSERT(iBrightness >= -255 && iBrightness <= 255);

	Bitmap* pBitmap = Bitmap::FromHBITMAP(m_hBitmap, NULL);
	if (!pBitmap)
		return NULL;

	if (pBitmap->GetLastStatus() != Gdiplus::Ok)
	{
		delete pBitmap;
		return NULL;
	}

	PixelFormat PixelFormat = pBitmap->GetPixelFormat();

	int iPixelSize = 0;
	switch (PixelFormat)
	{
		case PixelFormat8bppIndexed:
			iPixelSize = 1;
			break;

		case PixelFormat16bppARGB1555:
		case PixelFormat16bppGrayScale:
		case PixelFormat16bppRGB555:
		case PixelFormat16bppRGB565:
			iPixelSize = 2;
			break;

		case PixelFormat24bppRGB:
			iPixelSize = 3;
			break;

		case PixelFormat32bppARGB:
		case PixelFormat32bppPARGB: 
		case PixelFormat32bppRGB:
			iPixelSize = 4;
			break;
	}
	
	if (iPixelSize != 1 && iPixelSize != 3 && iPixelSize != 4)
		return NULL;

	theApp.BeginWaitCursor();
	BitmapData bitmapData;
	if (pBitmap->LockBits(&Rect(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()), 
					      ImageLockModeRead | ImageLockModeWrite,
					      PixelFormat,
						  &bitmapData) == Gdiplus::Ok)
	{
		for(UINT y = 0; y < bitmapData.Height; y++)
		{
			BYTE* row = ((BYTE*)bitmapData.Scan0) + (y * bitmapData.Stride);
			for(UINT x = 0; x < bitmapData.Width; x++)
			{
				if (iPixelSize == 1)
				{
					row[x] = GetPixel(row[x], iBrightness, iContrastRMin, iContrastRMax);
				}
				else if (iPixelSize == 3 || iPixelSize == 4)
				{
					row[x * iPixelSize + 2] = GetPixel(row[x * iPixelSize + 2], iBrightness, iContrastRMin, iContrastRMax);
					row[x * iPixelSize + 1] = GetPixel(row[x * iPixelSize + 1], iBrightness, iContrastGMin, iContrastGMax);
					row[x * iPixelSize + 0] = GetPixel(row[x * iPixelSize + 0], iBrightness, iContrastBMin, iContrastBMax);
				}
			}
		}

		pBitmap->UnlockBits(&bitmapData);
	}

	HBITMAP hBitmap = NULL;
	pBitmap->GetHBITMAP(Color(0, 0, 0), &hBitmap);
	delete pBitmap;

	theApp.EndWaitCursor();
	return hBitmap;
}

BYTE CImageElaboration::GetPixel(BYTE pixel, int iBrightness, int iContrastMin, int iContrastMax)
{
	int iPixel = pixel;

	BOOL bExternValue = FALSE;

	if (iPixel < iContrastMin)
	{
		iPixel = 0;
		bExternValue = TRUE;
	}
	if (iPixel > iContrastMax)
	{
		iPixel = 255;
		bExternValue = TRUE;
	}
	
	if (!bExternValue) 
		iPixel = (int)((((float)255) / (float)(iContrastMax - iContrastMin)) * ((float)iPixel) + (((float)(-255 * iContrastMin)) / ((float)(iContrastMax - iContrastMin))));

	iPixel += iBrightness;

	if (iPixel < 0)
		iPixel = 0;
	if (iPixel > 255)
		iPixel = 255;

	return (BYTE)iPixel;
}