#ifndef _IMAGESIMPLEDLG_H_
	#define _IMAGESIMPLEDLG_H_

#include "EndoxResizableDlg.h"

class CImageSimpleDlg : public CEndoxResizableDlg
{

public:

	CImageSimpleDlg(CWnd *pParent, CEsamiView* pEsamiView, CString sImageFile);

	enum { IDD = IDD_IMAGE_SIMPLE };

	static int m_nShowMode;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnChangeShow();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnBnClickedButtonPrevTiff();
	afx_msg void OnBnClickedButtonNextTiff();
	afx_msg void OnBnClickedButtonStampa();
	afx_msg void OnBnClickedButtonStampaFrame();
	afx_msg void OnBnClickedButtonStampaTutti();
	afx_msg void OnBnClickedButtonEsporta();
	afx_msg void OnBnClickedButtonEsportaFrame();
	afx_msg void OnBnClickedButtonEsportaTutti();

	afx_msg void OnBnClickedBtnRotateSx();
	afx_msg void OnBnClickedBtnRotateDx();

private:

	void AutoRedraw();
	BOOL CaricaImmagine();
	void InitializeWindow();
	void PrepareRectangle();

	//

	CBitmapButtonEx m_ctrlBtnNextTiff;
	CBitmapButtonEx m_ctrlBtnPrevTiff;
	CBitmapButton m_ctrlBtnRotateSx;
	CBitmapButton m_ctrlBtnRotateDx;

	CButtonLocalize m_ctrlBtnEsporta;
	CButtonLocalize m_ctrlBtnEsportaFrame;
	CButtonLocalize m_ctrlBtnEsportaTutti;
	CButtonLocalize m_ctrlBtnOK;
	CButtonLocalize m_ctrlBtnStampa;
	CButtonLocalize m_ctrlBtnStampaFrame;
	CButtonLocalize m_ctrlBtnStampaTutti;
	CButtonLocalize m_ctrlRadioShow1;
	CButtonLocalize m_ctrlRadioShow2;
	CButtonLocalize m_ctrlRadioShow3;

	CScrollBar m_ctrlScrollH;
	CScrollBar m_ctrlScrollV;

	CStatic m_ctrlImage;

	CStaticLocalize m_ctrlStaticView;

	//

	CEsamiView* m_pEsamiView;
	CString m_sImageFile;

	//

	BOOL m_bInit;
	BOOL m_bIsMultipage;
	BOOL m_bNextTiff;
	BOOL m_bPrevTiff;
	BOOL m_bRedrawBack;

	CDib m_dibImage;

	int m_nDLGHeight;
	int m_nDLGWidth;
	int m_nTGAHeight;
	int m_nTGAWidth;

	long m_lCurTiffPage;
	long m_lTotTiffPages;

	CRect m_DibRectScreen;
	CRect m_DibRectSource;

};

#endif /* _IMAGESIMPLEDLG_H_ */