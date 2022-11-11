#ifndef _IMAGECOMPAREDLG_H_
	#define _IMAGECOMPAREDLG_H_

#include "EndoxResizableDlg.h"
#include "ImagePreviewStatic.h"
#include "afxwin.h"

class CImageCompareDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CImageCompareDlg)

public:

	CImageCompareDlg(CWnd* pParent, CEsamiView* pEsamiView, long lIDPaziente, long lIDEsameL, long lIDEsameR, CImgListOrgani* pImgListOrganiL, long lIndexL, CImgListOrgani* pImgListOrganiR, long lIndexR);
	virtual ~CImageCompareDlg();

	enum { IDD = IDD_IMAGE_COMPARE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnPaint();

private:

	CEsamiView* m_pEsamiView;

	CImagePreviewStatic m_ctrlStaticImageL;
	CImagePreviewStatic m_ctrlStaticImageR;

	CImgListOrgani* m_pImgListOrganiL;
	CImgListOrgani* m_pImgListOrganiR;

	CScrollBar m_ctrlScrollBarL;
	CScrollBar m_ctrlScrollBarR;

	long m_lIDPaziente;
	long m_lIDEsameL;
	long m_lIDEsameR;
	long m_lIndexL;
	long m_lIndexR;

};

#endif /* _IMAGECOMPAREDLG_H_ */