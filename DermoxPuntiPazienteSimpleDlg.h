#ifndef _DERMOXPUNTIPAZIENTESIMPLEDLG_H_
#define _DERMOXPUNTIPAZIENTESIMPLEDLG_H_

#include "EndoxResizableDlg.h"

class CDermoxPuntiPazienteSimpleDlg : public CEndoxResizableDlg
{

	DECLARE_DYNAMIC(CDermoxPuntiPazienteSimpleDlg)

public:

	CDermoxPuntiPazienteSimpleDlg(CWnd* pParent, CEsamiView* pEsamiView, int iCurSelPointIndex);
	virtual ~CDermoxPuntiPazienteSimpleDlg();

	enum { IDD = IDD_DERMOX_PUNTIPAZIENTE_SIMPLE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnExit();
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

	CStaticLocalize m_ctrlStatic59;
	CButton m_ctrlCheck23;
	CStaticLocalize m_ctrlStatic60;
	CComboBox m_ctrlCombo09;
	CStaticLocalize m_ctrlStatic61;
	CEdit m_ctrlEdit08;

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
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#endif /* _DERMOXPUNTIPAZIENTESIMPLEDLG_H_ */