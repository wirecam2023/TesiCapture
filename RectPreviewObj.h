#ifndef _RECTPREVIEWOBJ_H_
	#define _RECTPREVIEWOBJ_H_

#include "RealRect.h"

class CRectPreviewObj : public CObject
{
	// DECLARE_SERIAL(CRectPreviewObj);

public:

	CRectPreviewObj(int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap);
	CRectPreviewObj(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap);
	
	virtual ~CRectPreviewObj();

	CPoint		m_ptLast;
	BOOL		m_bDrawInvert;
	CRealRect	m_PosObj;

	int 	m_nOffsetHandleParam;
	CSize	m_SizMinInPixel;
	CSize	m_SizMaxInPixel;

	int 	GetHandleCount() {return 4;}
	CPoint 	GetHandle(int nHandle);
	CRect 	GetHandleRect(int nHandleID, CWnd* pDlg);

	CRealRect* GetObj() { return &m_PosObj; }
	void SetObj(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap);

	void 	Invalidate(CWnd* pDlg);
	void 	AutoRedraw(CWnd* pDlg);
	void 	AutoRedraw(CDC* pDC);
	void 	Draw(CDC* pDC , CString strTitolo, int nAlignment, int nRotation, TrackerState nTrack, LOGFONT* plfFont);
	void 	DrawTracker(CDC* pDC, TrackerState state);
	CRect 	MoveTo(CRect positon, CWnd* pDlg);
	void 	MoveHandleTo(int nHandle, CPoint point, CWnd* pDlg);
	int  	HitTest(CPoint point, CWnd* pDlg);
	CRect	TextOnVideo(HDC hdc, int x, int y, CString strText, LPLOGFONT lpFont, long cColor);

	BOOL	ObjTest(CPoint point);
	void	MoveObjectTo(CPoint point, CWnd* pDlg, CRect rectFrame);

	BOOL	Intersects(const CRect& rect);

	CString m_strTitolo;
	int m_nAlignment;
	int m_nRotation;

private:

	double m_dRap;

};

#endif /* _RECTPREVIEWOBJ_H_ */