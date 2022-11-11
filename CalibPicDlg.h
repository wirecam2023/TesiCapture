#ifndef _CALIBPICDLG_H_
	#define _CALIBPICDLG_H_

class CCalibPicDlg : public CDialog
{

public:     

	CCalibPicDlg(CWnd* pParent, CEsamiView* pEsamiView, CString sBitmapName);
	~CCalibPicDlg();

	enum { IDD = IDD_CALIBPIC };

	CString GetScreen();
	CString GetUser();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog(); 

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

private:

	float GetDist(CPoint pt1, CPoint pt2);

	void PaintLine(CDC* pDC, CPoint point1, CPoint point2);
	void PaintPixel(HDC hdc, CPoint point);

	void ResizeDibWindow();
	void ResizeForImage();

	// --- //

	CEsamiView* m_pEsamiView;

	BOOL m_bCalibrating;

	double m_lfRappComp;

	int m_nImageX;
	int m_nImageY;

	CDib m_dib;

    CPoint m_ptFirst;
	CPoint m_ptLast;

	CString	m_strBitmapName;
	CString	m_strScreen;
	CString	m_strUser;

};

#endif /* _CALIBPICDLG_H_ */