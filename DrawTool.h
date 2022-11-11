#ifndef _DRAWTOOL_H_
	#define _DRAWTOOL_H_

#include "RectPreview.h"

class CDrawTool : public CRectPreview
{
	DECLARE_SERIAL(CDrawTool);

public:

	CDrawTool();
	CDrawTool(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap);

	virtual void SetObj(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap);

	CString		m_strValue;
	CString		m_strType;

	int			m_nParam;
	BOOL		m_bCheck;
	LOGFONT		m_lfFont;
	COLORREF	m_rgbColor;

	BOOL m_bHeader;

	double m_dRap;
};

#endif /* _DRAWTOOL_H_ */