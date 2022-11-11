#pragma once

#include "Report.h"

class CReportStatic : public CStatic
{
public:

	CReportStatic(CReport* pReport);

protected:

	DECLARE_MESSAGE_MAP()
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnPaint();

	CReport* m_pReport;
	CBitmap m_Bitmap;
};