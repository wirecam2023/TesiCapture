#ifndef _ALBUMCONFRONTODERMOXDLG_H_
	#define _ALBUMCONFRONTODERMOXDLG_H_

#include "EndoxResizableDlg.h"

class CEsamiSet;

class CAlbumConfrontoDermoxDlg : public CEndoxResizableDlg
{

public:

	CAlbumConfrontoDermoxDlg(CWnd* pParent, CEsamiView* pEsamiView, CPoint ptSelPoint);
	virtual ~CAlbumConfrontoDermoxDlg();

	enum { IDD = IDD_ALBUM_CONFRONTO_DERMOX };

	CBitmapButtonEx	m_BtnImmFirst[2];
	CBitmapButtonEx	m_BtnImmPrev[2];
	CBitmapButtonEx	m_BtnImmNext[2];
	CBitmapButtonEx	m_BtnImmLast[2];

	CBitmapButtonEx	m_BtnFullScreen;
	CBitmapButtonEx	m_BtnPrintImages;
	
	CFileBmp*		m_pFileBmp[2];

	CEsamiView*		m_pEsamiView;

	int				m_nDiapoPage[2];
	int				m_nMaxDiapo[2];

	void	ResetVetDiapo(BOOL bReposition, int nEsame);
	int		FillDiapoIndex(int nEsame);
	void	MoveImage(int nEsame);
	void	EsamiMove(int nEsame);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnImmFirst1();
	afx_msg void OnImmFirst2();
	afx_msg void OnImmLast1();
	afx_msg void OnImmLast2();
	afx_msg void OnImmNext1();
	afx_msg void OnImmNext2();
	afx_msg void OnImmPrev1();
	afx_msg void OnImmPrev2();
	afx_msg void OnBnClickedFullScreen();
	afx_msg void OnPrintImages();

	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();

	DECLARE_MESSAGE_MAP()

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic08;

	CButtonLocalize m_ctrlButtonOK;

private:

	CImgListOrgani m_ImgListOrgani[2];
	CComboBox m_ctrlCombo[2];

	///

	void CaricaImmaginiPunto();
	CPoint ImageToScreen(CPoint ptPoint);
	CPoint ImageToScreenZoom(CPoint ptPoint, CRect rectImageZoom);
	CPoint ScreenToImage(CPoint ptPoint);
	void SelezionaPunto(CPoint ptPoint);
	int TrovaPunto(CPoint& ptPoint);

	CStatic m_ctrlFrameSagoma;
	CStatic m_ctrlStaticSede;
	CStatic m_ctrlFrameZoom;

	CRect m_rectFrameSagoma;
	CRect m_rectPaintSagoma;
	CRect m_rectFrameZoom;

	CDib m_dibSagome;
	CDib m_dibSedi;

	CImgList m_listImg;

	CList <tagPuntiDermox> m_listPunti;

	CList <tagSede> m_listSedi;
	long m_lIDSede;

	int m_iCurSelPointIndex;
	int m_iCurSelPointX;
	int m_iCurSelPointY;

	CPoint m_ptSelPoint;
};

#endif /* _ALBUMCONFRONTODERMOXDLG_H_ */