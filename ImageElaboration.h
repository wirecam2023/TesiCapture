#pragma once

class CImageElaboration
{

public:

	CImageElaboration(HBITMAP hBitmap);
	~CImageElaboration(void);

	HBITMAP ApplyBrightnessContrast(int iBrightness, int iContrastRMin, int iContrastRMax, int iContrastGMin, int iContrastGMax, int iContrastBMin, int iContrastBMax);

protected:

	BYTE GetPixel(BYTE pixel, int iBrightness, int iContrastMin, int iContrastMax);

	HBITMAP m_hBitmap;

};
