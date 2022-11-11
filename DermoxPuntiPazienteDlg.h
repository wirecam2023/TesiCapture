#ifndef _DERMOXPUNTIPAZIENTEDLG_H_
	#define _DERMOXPUNTIPAZIENTEDLG_H_

#include "EndoxResizableDlg.h"

class CDermoxPuntiPazienteDlg : public CEndoxResizableDlg
{

	DECLARE_DYNAMIC(CDermoxPuntiPazienteDlg)

public:

	CDermoxPuntiPazienteDlg(CWnd* pParent, CEsamiView* pEsamiView, int iCurSelPointIndex);
	virtual ~CDermoxPuntiPazienteDlg();

	enum { IDD = IDD_DERMOX_PUNTIPAZIENTE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnExit();
	// afx_msg void OnBnClickedRadioSel();
	afx_msg void OnBnClickedRadioMov();
	afx_msg void OnBnClickedRadioDel();
	afx_msg void OnBnClickedBtnConfronto();

	afx_msg void OnBnClickedCheck();
	afx_msg void OnBnClickedRadio();

	afx_msg void OnCbnSelchangeCombo();

	afx_msg void OnEnChangeEdit();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnLvnItemchangedListPoints(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangingListPoints(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnNMDblClkListImages(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnPaint();

	afx_msg void OnSize(UINT nType, int cx, int cy);

private:

	CPoint ImageToScreen(CPoint ptPoint);
	CPoint ImageToScreenZoom(CPoint ptPoint, CRect rectImageZoom);
	CPoint ScreenToImage(CPoint ptPoint);

	void CaricaDatiPunto();
	void CaricaImmaginiPunto();
	void EliminaPunto();
	void RiempiCombo09();
	void SalvaDatiPunto();
	void SelezionaPunto(CPoint ptPoint);
	void SpostaPunto(CPoint ptPoint);
	int TrovaPunto(CPoint& ptPoint);

	// --- //

	CButtonLocalize m_ctrlBtnExit;

	CListCtrl m_ctrlListPoints;
	CImageList m_listImages;
	CListCtrl m_ctrlListImages;

	CStatic m_ctrlFrameSagoma;
	CStatic m_ctrlFrameZoom;
	CStatic m_ctrlFrameSede;
	CStatic m_ctrlStaticSede;

	CStatic m_ctrlStatic56;
	CStaticLocalize m_ctrlStatic57;
	CStaticLocalize m_ctrlStatic58;
	CButtonLocalize m_ctrlRadioSel;
	CButtonLocalize m_ctrlRadioMov;
	CButtonLocalize m_ctrlRadioDel;
	CButtonLocalize m_ctrlBtnConfronto;


	CStaticLocalize m_ctrlStatic00;
	CComboBox m_ctrlCombo00;

	CStaticLocalize m_ctrlStatic01;
	CButtonLocalize m_ctrlCheck00;
	CButtonLocalize m_ctrlCheck01;
	CButtonLocalize m_ctrlCheck02;
	CButtonLocalize m_ctrlCheck03;

	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CButton m_ctrlCheck04;
	CStaticLocalize m_ctrlStatic04;
	CButtonLocalize m_ctrlRadio00;
	CButtonLocalize m_ctrlRadio01;
	CStaticLocalize m_ctrlStatic05;
	CButtonLocalize m_ctrlRadio02;
	CButtonLocalize m_ctrlRadio03;
	CStaticLocalize m_ctrlStatic06;
	CButtonLocalize m_ctrlRadio04;
	CButtonLocalize m_ctrlRadio05;

	CStaticLocalize m_ctrlStatic07;
	CButton m_ctrlCheck05;

	CStaticLocalize m_ctrlStatic08;
	CButton m_ctrlCheck06;
	CStaticLocalize m_ctrlStatic09;
	CButtonLocalize m_ctrlRadio06;
	CButtonLocalize m_ctrlRadio07;

	CStaticLocalize m_ctrlStatic10;
	CButton m_ctrlCheck07;
	CStaticLocalize m_ctrlStatic11;
	CButtonLocalize m_ctrlRadio08;
	CButtonLocalize m_ctrlRadio09;
	CStaticLocalize m_ctrlStatic12;
	CButtonLocalize m_ctrlRadio10;
	CButtonLocalize m_ctrlRadio11;
	CButtonLocalize m_ctrlRadio12;

	CStaticLocalize m_ctrlStatic13;
	CButton m_ctrlCheck08;

	CStaticLocalize m_ctrlStatic14;
	CButton m_ctrlCheck09;
	CStaticLocalize m_ctrlStatic15;
	CButtonLocalize m_ctrlRadio13;
	CButtonLocalize m_ctrlRadio14;
	CStaticLocalize m_ctrlStatic16;
	CButtonLocalize m_ctrlRadio15;
	CButtonLocalize m_ctrlRadio16;
	CButtonLocalize m_ctrlRadio17;
	CStaticLocalize m_ctrlStatic17;
	CButtonLocalize m_ctrlRadio18;
	CButtonLocalize m_ctrlRadio19;

	CStaticLocalize m_ctrlStatic18;
	CButton m_ctrlCheck10;

	CStaticLocalize m_ctrlStatic19;
	CButton m_ctrlCheck11;
	CStaticLocalize m_ctrlStatic20;
	CButtonLocalize m_ctrlRadio20;
	CButtonLocalize m_ctrlRadio21;
	CStaticLocalize m_ctrlStatic21;
	CButtonLocalize m_ctrlRadio22;
	CButtonLocalize m_ctrlRadio23;
	CButtonLocalize m_ctrlRadio24;

	CStaticLocalize m_ctrlStatic22;
	CButton m_ctrlCheck12;
	CStaticLocalize m_ctrlStatic23;
	CButton m_ctrlCheck13;

	CStaticLocalize m_ctrlStatic24;
	CButton m_ctrlCheck14;
	CStaticLocalize m_ctrlStatic25;
	CButton m_ctrlCheck15;

	CStaticLocalize m_ctrlStatic26;
	CButton m_ctrlCheck16;
	CStaticLocalize m_ctrlStatic27;
	CButton m_ctrlCheck17;

	CStaticLocalize m_ctrlStatic28;
	CButton m_ctrlCheck18;
	CStaticLocalize m_ctrlStatic29;
	CButton m_ctrlCheck19;

	CStaticLocalize m_ctrlStatic30;
	CButton m_ctrlCheck20;
	CStaticLocalize m_ctrlStatic31;
	CButton m_ctrlCheck21;

	CEdit m_ctrlEdit00;

	CStaticLocalize m_ctrlStatic59;
	CButton m_ctrlCheck23;
	CStaticLocalize m_ctrlStatic60;
	CComboBox m_ctrlCombo09;
	CStaticLocalize m_ctrlStatic61;
	CEdit m_ctrlEdit08;


	CStaticLocalize m_ctrlStatic32;

	CStaticLocalize m_ctrlStatic33;
	CStaticLocalize m_ctrlStatic34;
	CComboBox m_ctrlCombo01;
	CStaticLocalize m_ctrlStatic35;
	CComboBox m_ctrlCombo02;

	CStaticLocalize m_ctrlStatic36;
	CStaticLocalize m_ctrlStatic37;
	CComboBox m_ctrlCombo03;
	CStaticLocalize m_ctrlStatic38;
	CComboBox m_ctrlCombo04;

	CStaticLocalize m_ctrlStatic39;
	CEdit m_ctrlEdit01;
	CStaticLocalize m_ctrlStatic40;
	CButton m_ctrlCheck22;
	CStaticLocalize m_ctrlStatic41;
	CEdit m_ctrlEdit02;
	CStaticLocalize m_ctrlStatic42;
	CEdit m_ctrlEdit03;

	CStaticLocalize m_ctrlStatic43;

	CStaticLocalize m_ctrlStatic44;
	CStaticLocalize m_ctrlStatic45;
	CComboBox m_ctrlCombo05;

	CStaticLocalize m_ctrlStatic46;
	CEdit m_ctrlEdit04;
	CStaticLocalize m_ctrlStatic47;
	CComboBox m_ctrlCombo06;
	CStaticLocalize m_ctrlStatic48;
	CEdit m_ctrlEdit05;
	CStaticLocalize m_ctrlStatic49;
	CButtonLocalize m_ctrlRadio25;
	CButtonLocalize m_ctrlRadio26;
	CButtonLocalize m_ctrlRadio27;
	CButtonLocalize m_ctrlRadio28;
	CButtonLocalize m_ctrlRadio29;

	CStaticLocalize m_ctrlStatic51;
	CEdit m_ctrlEdit06;

	CStaticLocalize m_ctrlStatic52;
	CStaticLocalize m_ctrlStatic53;
	CComboBox m_ctrlCombo07;
	CStaticLocalize m_ctrlStatic54;
	CComboBox m_ctrlCombo08;

	CStaticLocalize m_ctrlStatic55;
	CEdit m_ctrlEdit07;

	// --- //

	CEsamiView* m_pEsamiView;

	CDib m_dibSagome;
	CDib m_dibSedi;
	CRect m_rectFrameSagoma;
	CRect m_rectPaintSagoma;
	CRect m_rectFrameZoom;
	int m_iCurSelPointIndex;
	int m_iCurSelPointX;
	int m_iCurSelPointY;

	CList <tagSede> m_listSedi;
	long m_lIDSede;

	// --- //

	int m_nOperazione;
	int m_nReticoloPigmentarioColore;
	int m_nReticoloPigmentarioDistanza;
	int m_nReticoloPigmentarioSpessore;
	int m_nPigmentazioneDiffusaDistrib;
	int m_nGlobuliMarroniForma;
	int m_nGlobuliMarroniSede;
	int m_nPuntiNeriDistribuzione;
	int m_nPuntiNeriSede;
	int m_nPuntiNeriCalibro;
	int m_nDepigmentazioneDistribuzione;
	int m_nDepigmentazioneSede;
	int m_nLivelloDiClark;

	// --- //

	BOOL m_bFillingList;
	BOOL m_bLoadingData;
	BOOL m_bModified;

	// --- //

	CList <tagPuntiDermox> m_listPunti;
	CRect m_rectOriginalClip;

	CString m_sSedeOld;
	CString m_sSedeNew;

	int m_nCurHeight;
	int m_nScrollPos;
	CRect m_rect;

public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult);
};

#endif /* _DERMOXPUNTIPAZIENTEDLG_H_ */