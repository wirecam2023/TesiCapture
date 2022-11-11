#ifndef _RECTPREVIEW_H_
	#define _RECTPREVIEW_H_

class CRealRect;
class CRectPreviewObj;

class CRectPreview : public CObject
{
	DECLARE_SERIAL(CRectPreview);

public:

	CRectPreview();
	CRectPreview(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap);
	virtual ~CRectPreview(void);

	virtual void OnLButtonDown(CWnd* pDlg, CRect rectFrame, UINT nFlags, CPoint& point);
	virtual void OnLButtonUp(CWnd* pDlg, CRect rectFrame, UINT nFlags, CPoint& point);
	virtual void OnMouseMove(CWnd* pDlg, CRect rectFrame, CPoint& point);

	virtual CRealRect*	GetObj();
	virtual void		SetObj(CRealRect* pPosObj, int nOffsetHandleParam, CSize szMin, CSize szMax, double dRap);
	virtual void		SetObj(CString strTitolo, int nAlignment, int nRotation);

	CRect	GetRectInMM();
	CRect	GetRectInPixel();
	void	SetRectInMM   (CWnd* pWnd, CRect RectInMM);
	void	SetRectInPixel(CWnd* pWnd, CRect RectInPixel);
	void 	Invalidate(CWnd* pDlg);
	void 	AutoRedraw(CWnd* pDlg);
	void 	AutoRedraw(CDC* pDC);
	void	Draw(CWnd* pDlg, CString strTitolo, int nAlignment, int nRotation, TrackerState nTrack, LOGFONT* plfFont);
	void	Draw(CDC* pDC, CString strTitolo, int nAlignment, int nRotation, TrackerState nTrack, LOGFONT* plfFont);

	BOOL	Intersects(const CRect& rect);

	static void 	DocToClient(CWnd* pWnd, CRect& rect);
	static void 	DocToClient(CWnd* pWnd, CPoint& point);
	static void 	ClientToDoc(CWnd* pWnd, CRect rectFrame, CPoint& point, BOOL bMove);
	static void 	ClientToDoc(CWnd* pWnd, CRect& rect);

	BYTE	RecalcIntensity(CWnd* pWnd);
	
	CRectPreviewObj* 	m_pObj;
	SelectModeDlg 		m_selectMode;
	int 				m_nDragHandle;
	BOOL				m_bIsEnable;

	CString m_strTitolo;
	int m_nAlignment;
	int m_nRotation;

private:

	double m_dRap;

};

#endif /* _RECTPREVIEW_H_ */