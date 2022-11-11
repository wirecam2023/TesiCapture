#ifndef _ACQFROMDISKDERMOXDLG_H_
	#define _ACQFROMDISKDERMOXDLG_H_

#include <afxcmn.h>
#include <afxwin.h>

#include "EndoxResizableDlg.h"

class CAcqFromDiskDermoxDlg : public CEndoxResizableDlg
{

	DECLARE_DYNAMIC(CAcqFromDiskDermoxDlg)

public:

	CAcqFromDiskDermoxDlg(CWnd* pParent, CEsamiView* pEsamiView, CString sPhotoFile, BOOL bDeleteAfterAcquisition);
	virtual ~CAcqFromDiskDermoxDlg();

	enum { IDD = IDD_ACQ_FROM_DISK_DERMOX };

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
	afx_msg void OnNMDblClkListImages(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:

	void LoadSettings();

	CPoint ImageToScreen(CPoint ptPoint);
	CPoint ImageToScreenZoom(CPoint ptPoint, CRect rectImageZoom);
	CPoint ScreenToImage(CPoint ptPoint);

	int AggiungiPunto(CString sSede, CPoint ptPoint);
	void CaricaDatiPunto();
	void CaricaImmaginiPunto();
	long ImportaImmagine();
	void SelezionaPunto(CPoint ptPoint);
	int TrovaPunto(CPoint& ptPoint);

	// --- //

	CButton m_ctrlBtnPhoto;

	CButtonLocalize m_ctrlBtnExit;

	CComboBox m_ctrlComboCalib;

	CListCtrl m_ctrlListPoints;
	CImageList m_listImages;
	CListCtrl m_ctrlListImages;

	CStatic m_ctrlFrameSagoma;
	CStatic m_ctrlFrameLive;
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

	CString m_sPhotoFile;
	BOOL m_bDeleteAfterAcquisition;

	// --- //

	BOOL m_bFillingList;

};

#endif /* _ACQFROMTELEDERMOXDLG_H_ */