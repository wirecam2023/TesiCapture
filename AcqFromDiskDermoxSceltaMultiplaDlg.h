#pragma once

#include <afxcmn.h>
#include <afxwin.h>

#include "EndoxResizableDlg.h"
#include "ThumbCtrl.h"

class CAcqFromDiskDermoxSceltaMultiplaDlg : public CEndoxResizableDlg
{

	DECLARE_DYNAMIC(CAcqFromDiskDermoxSceltaMultiplaDlg)

public:

	CAcqFromDiskDermoxSceltaMultiplaDlg(CWnd* pParent, CEsamiView* pEsamiView, CStringList *photoFileList, BOOL bDeleteAfterAcquisition);
	virtual ~CAcqFromDiskDermoxSceltaMultiplaDlg();

	enum { IDD = IDD_ACQ_FROM_DISK_DERMOX_SCELTAMULTIPLA };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnPhoto();

	afx_msg void OnCbnSelchangeComboCalib();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLvnItemchangedListPoints(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	LRESULT OnImageSel(WPARAM wParam, LPARAM lParam);
	LRESULT OnNMDblClkListImages(WPARAM wParam, LPARAM lParam);

private:

	CPoint ImageToScreen(CPoint ptPoint);
	CPoint ImageToScreenZoom(CPoint ptPoint, CRect rectImageZoom);
	CPoint ScreenToImage(CPoint ptPoint);

	int AggiungiPunto(CString sSede, CPoint ptPoint);
	void CaricaDatiPunto();
	void CaricaImmaginiPunto();
	long ImportaImmagini();
	void SelezionaPunto(CPoint ptPoint);
	int TrovaPunto(CPoint& ptPoint);

	void LoadSettings();

	void RefreshPoints();

	// --- //

	CComboBox m_ctrlComboCalib;

	CButton m_ctrlBtnPhoto;

	CButtonLocalize m_ctrlBtnExit;
	CButtonLocalize m_ctrlBtnDelete;

	CListCtrl m_ctrlListPoints;
	CImageList m_listImages;
	CImgList m_listImagesTemp;
	CListCtrl m_ctrlListImages;
	CThumbCtrl m_ctrlListImagesTemp;

	CStatic m_ctrlFrameSagoma;	
	CStatic m_ctrlFrameZoom;
	CStatic m_ctrlFrameSede;

	CStatic m_ctrlStaticSede;
	CStaticLocalize m_ctrlStaticFrameCalib;

	// --- //

	CEsamiView* m_pEsamiView;

	CDib m_dibImageFile;
	CDib m_dibSagome;
	CDib m_dibSedi;
	CRect m_rectFrameLive;
	CRect m_rectFrameSagoma;
	CRect m_rectPaintSagoma;
	CRect m_rectFrameZoom;
	CList <tagPuntiDermox> m_listPunti;
	int m_iCurSelPointIndex;
	int m_iCurSelPointX;
	int m_iCurSelPointY;

	CList <tagSede> m_listSedi;
	long m_lIDSede;

	CString m_sCalib;

	//

	CStringList *m_photoFileList;
	BOOL m_bDeleteAfterAcquisition;

	// --- //

	BOOL m_bFillingList;

public:
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnSelDeselAll();
};
