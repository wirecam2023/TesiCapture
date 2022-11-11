#include "stdafx.h"
#include "Endox.h"
#include "ReportStatic.h"
#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CReportStatic::CReportStatic(CReport* pReport)
{
	m_pReport = pReport;
}

BEGIN_MESSAGE_MAP(CReportStatic, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CReportStatic::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CReportStatic::OnPaint()
{
	CPaintDC dc1(this);

	CRect rectClient;
	GetClientRect(&rectClient);

	if (!m_Bitmap.m_hObject)
	{
		m_Bitmap.CreateCompatibleBitmap(&dc1, rectClient.Width(), rectClient.Height());
	}
	else
	{
		if (m_Bitmap.GetBitmapDimension().cx != rectClient.Width() || m_Bitmap.GetBitmapDimension().cy != rectClient.Height())
		{
			m_Bitmap.DeleteObject();
			m_Bitmap.CreateCompatibleBitmap(&dc1, rectClient.Width(), rectClient.Height());
		}
	}

	dc1.SetBkColor(RGB(255, 255, 255));
	CMemDC dc(&dc1, &m_Bitmap, &rectClient);

	m_pReport->Draw(&dc, this);
}
