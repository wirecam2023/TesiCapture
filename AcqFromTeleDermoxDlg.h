#ifndef _ACQFROMTELEDERMOXDLG_H_
	#define _ACQFROMTELEDERMOXDLG_H_

#include <afxcmn.h>
#include <afxwin.h>

#include "EndoxResizableDlg.h"

#include "LibCap\LibCap.h"
#include "LibCap\xcapCOMCommon.h"

class CAcqFromTeleDermoxDlg : public CEndoxResizableDlg
{

	DECLARE_DYNAMIC(CAcqFromTeleDermoxDlg)

public:

	CAcqFromTeleDermoxDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CAcqFromTeleDermoxDlg();

	enum { IDD = IDD_ACQ_FROM_TELE_DERMOX };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnPhoto();
	afx_msg void OnBnClickedRadioPlay();
	afx_msg void OnBnClickedRadioPause();
	afx_msg void OnBnClickedRadioPreset();

	afx_msg void OnCbnSelchangeComboCalib();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLvnItemchangedListPoints(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNMDblClkListImages(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	LRESULT OnPressPedal1(WPARAM wParam, LPARAM lParam);
	LRESULT OnPressPedal2(WPARAM wParam, LPARAM lParam);

private:

	void LoadSettings();

	CPoint ImageToScreen(CPoint ptPoint);
	CPoint ImageToScreenZoom(CPoint ptPoint, CRect rectImageZoom);
	CPoint ScreenToImage(CPoint ptPoint);

	int AggiungiPunto(CString sSede, CPoint ptPoint);
	void CaricaDatiPunto();
	void CaricaImmaginiPunto();
	long ImportaImmagine(CString strFile);
	void SelezionaPunto(CPoint ptPoint);
	int TrovaPunto(CPoint& ptPoint);

	SETDEVICEPTR libcap_SetDevice;
	STARTLIVEPTR libcap_StartLive;
	SHOWLIVEPTR libcap_ShowLive;
	STOPLIVEPTR libcap_StopLive;
	FREEZELIVEPTR libcap_FreezeLive;
	PHOTOPTR libcap_Photo;
	SETFEATURE libcap_SetFeature;

	// --- //

	CButton m_ctrlBtnPhoto;
	CButtonLocalize m_ctrlRadioPlay;
	CButtonLocalize m_ctrlRadioPause;
	CButton m_ctrlRadioPreset01;
	CButton m_ctrlRadioPreset02;
	CButton m_ctrlRadioPreset03;
	CButton m_ctrlRadioPreset04;
	CButton m_ctrlRadioPreset05;
	CButton m_ctrlRadioPreset06;
	CButton m_ctrlRadioPreset07;
	CButton m_ctrlRadioPreset08;
	CButton m_ctrlRadioPreset09;
	CButton m_ctrlRadioPreset10;

	CButtonLocalize m_ctrlBtnExit;

	CComboBox m_ctrlComboCalib;

	CListCtrl m_ctrlListPoints;
	CImageList m_listImages;
	CListCtrl m_ctrlListImages;

	CSliderCtrl m_ctrlSliderL;
	CSliderCtrl m_ctrlSliderC;
	CSliderCtrl m_ctrlSliderG;
	CSliderCtrl m_ctrlSliderT;
	CSliderCtrl m_ctrlSliderS;
	CSliderCtrl m_ctrlSliderE;
	CSliderCtrl m_ctrlSliderRMin;
	CSliderCtrl m_ctrlSliderRMax;
	CSliderCtrl m_ctrlSliderGMin;
	CSliderCtrl m_ctrlSliderGMax;
	CSliderCtrl m_ctrlSliderBMin;
	CSliderCtrl m_ctrlSliderBMax;

	CStatic m_ctrlFrameSagoma;
	CStatic m_ctrlFrameLive;
	CStatic m_ctrlFrameZoom;
	CStatic m_ctrlFrameSede;

	CStatic m_ctrlStaticSede;
	CStatic m_ctrlStaticL;
	CStatic m_ctrlStaticC;
	CStatic m_ctrlStaticG;
	CStatic m_ctrlStaticT;
	CStatic m_ctrlStaticS;
	CStatic m_ctrlStaticE;
	CStatic m_ctrlStaticRMin;
	CStatic m_ctrlStaticRMax;
	CStatic m_ctrlStaticGMin;
	CStatic m_ctrlStaticGMax;
	CStatic m_ctrlStaticBMin;
	CStatic m_ctrlStaticBMax;

	CStaticLocalize m_ctrlStaticFrameL;
	CStaticLocalize m_ctrlStaticFrameC;
	CStaticLocalize m_ctrlStaticFrameG;
	CStaticLocalize m_ctrlStaticFrameT;
	CStaticLocalize m_ctrlStaticFrameS;
	CStaticLocalize m_ctrlStaticFrameE;
	CStaticLocalize m_ctrlStaticFrameCalib;
	CStaticLocalize m_ctrlStaticFrameRGB;

	// --- //

	CEsamiView* m_pEsamiView;

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

	int m_iRadioPlayPause;
	int m_iRadioPreset;

	int m_iLumin;
	int m_iContr;
	int m_iGamma;
	int m_iTonal;
	int m_iSatur;
	int m_iEspos;
	int m_iRMin;
	int m_iRMax;
	int m_iGMin;
	int m_iGMax;
	int m_iBMin;
	int m_iBMax;
	int m_iGain;
	CString m_sCalib;

	HMODULE m_hModule;

	// --- //

	BOOL m_bAcquisizioneInizializzata;
	BOOL m_bFillingList;

	xcapCOMStartListen_PTR xcapCOMStartListen;
	xcapCOMStopListen_PTR xcapCOMStopListen;
	HMODULE m_hModuleCOM;

	int m_iComPort;
	BOOL m_bComPortInv;
};

#endif /* _ACQFROMTELEDERMOXDLG_H_ */