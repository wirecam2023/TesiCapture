#include "stdafx.h"
#include "Endox.h"
#include "DrawTool.h"

#include "RectPreviewObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CDrawTool, CObject, 0)

CDrawTool::CDrawTool()
	:CRectPreview()
{
	m_strValue	= "";
	m_strType	= "";
	m_bCheck	= FALSE;
	m_nParam	= 0;
	m_rgbColor	= RGB(0,0,0);

	m_lfFont.lfHeight 			= -13;
	m_lfFont.lfWidth			= 0;
	m_lfFont.lfWeight 			= 400;
	m_lfFont.lfItalic 			= 0;
	m_lfFont.lfUnderline 		= 0;
	m_lfFont.lfEscapement		= 0;
	m_lfFont.lfOrientation		= 0;
	m_lfFont.lfStrikeOut		= 0;
	m_lfFont.lfCharSet			= 0;
	m_lfFont.lfOutPrecision		= 1;
	m_lfFont.lfClipPrecision	= 2;
	m_lfFont.lfQuality			= 1;
	m_lfFont.lfPitchAndFamily	= 34;
	strcpy_s(m_lfFont.lfFaceName, "MS Sans Serif");
}

CDrawTool::CDrawTool(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap)
	:CRectPreview(pPosObj, nOffsetHandleParam, szMin, szMax, dRap)
{
	m_strValue	= "";
	m_strType	= "";

	if (m_pObj)
		m_pObj->m_bDrawInvert = FALSE;

	m_dRap = dRap;
}

void CDrawTool::SetObj(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap)
{
	CRectPreview::SetObj(pPosObj, nOffsetHandleParam, szMin,  szMax, dRap);
	
	if (m_pObj)
		m_pObj->m_bDrawInvert = FALSE;

	m_dRap = dRap;
}