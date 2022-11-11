#ifndef _MAXIMIZEDLG_H_
	#define _MAXIMIZEDLG_H_

class CMaximizeDlg : public CDialog
{

public:

	CMaximizeDlg(CWnd* pParent = NULL, CDib* pDib = NULL, CEsamiView* pEsamiView = NULL, CImgListOrgani* pImgList = NULL, long lNumPage = 0, long lPaziente = 0, long lEsame = 0, long lTotPage = 0); //Gabriel BUG 6225 - Lista DO FIX

	enum { IDD = IDD_IMAGE_MAX };

	CDib*	m_pDib;

	void	InitializeWindow();

	CImgListOrgani* m_ImgList; //Gabriel BUG 6225 - Lista DO FIX

	BOOL CaricaImmagine(); //Gabriel BUG 6225 - Lista DO FIX

	long m_lID; //Gabriel BUG 6225 - Lista DO FIX
	
	long m_lNumPage; //Gabriel BUG 6225 - Lista DO FIX

	long m_lPaziente; //Gabriel BUG 6225 - Lista DO FIX

	long m_lEsame; //Gabriel BUG 6225 - Lista DO FIX

	CEsamiView* m_pEsamiView; //Gabriel BUG 6225 - Lista DO FIX

	long m_lTotPage; //Gabriel BUG 6225 - Lista DO FIX

	long GetCurrentPageNum(); //Gabriel BUG 6225 - Lista DO FIX

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	void AutoRedraw(); //Gabriel BUG 6225 - Lista DO FIX

	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt); //Gabriel BUG 6225 - Lista DO FIX
	virtual BOOL PreTranslateMessage(MSG* pMsg); //Gabriel BUG 6225 - Lista DO FIX

	DECLARE_MESSAGE_MAP()
};

#endif /* _MAXIMIZEDLG_H_ */