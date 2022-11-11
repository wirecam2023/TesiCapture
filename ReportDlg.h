#ifndef _REPORTDLG_H_
	#define _REPORTDLG_H_

#include "IntestazioneNewDlg.h"
#include "afxwin.h"

class CDrawTool;

#define RECT_HEIGHT_RICERCA 150

#define ORIENT_REPORT_HORZ 0
#define ORIENT_REPORT_VERT 1

#define TIPO_REPORT_NORMALE 0
#define TIPO_REPORT_RICERCA 1

class CReportDlg : public CResizableDialog
{

public:

	CReportDlg(CWnd* pParent, CEsamiView* pEsamiView); 
	virtual ~CReportDlg(void);

	enum { IDD = IDD_REPORT };

	CSpinButtonCtrl	m_ctrlSpin;
	CStatic m_ctrPage;
	int		m_nFormato;
	BOOL	m_bCopiaPDF;
	BOOL	m_bFitToPage;
	int		m_nTipoReport;
	int		m_nOrientamento;

	int			 m_nMode;
	CRect		 m_rectPage;
	CSize		 m_szPage;
	CDrawObjList m_selection;
	CDrawObjList m_objects;

	HCURSOR	 	 m_hCursorAdd;
    HCURSOR	 	 m_hCursorArrow; 
	
	BOOL         m_bTipoChanged;
	BOOL         m_bCambiaAltezza;
	BOOL         m_bReportSearch;

	int          m_nAltezzaRiga;

	CSize        m_szFoglioA4;
	CSize        m_szFoglioLegal;
	CSize        m_szFoglioLetter;
	CSize        m_szFoglioExclusive;
	
protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg void OnSaveAs();
	afx_msg void OnNew();
	afx_msg void OnDelete();
	afx_msg void OnBnClickedPreview();
	afx_msg void OnBtnChiudi();
	afx_msg void OnCambiaPagina();
	afx_msg void OnCambiaTipoReport();
	afx_msg void OnCambiaImpostazioni();
	afx_msg void OnCambiaControllo();

	afx_msg void OnCbnSelchangeComboStampante();
	afx_msg void OnCbnSelchangeComboHeader1();
	afx_msg void OnCbnSelchangeComboHeader2();
	afx_msg void OnCbnSelchangeComboFooter1();
	afx_msg void OnCbnSelchangeComboFooter2();

	afx_msg void OnEnChangeEdtHeight();

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void		Add(CDrawTool* pObj);
	void		Remove(CDrawTool* pObj);
	CDrawTool*	ObjectAt(const CPoint& point);
	BOOL		IsSelected(CDrawTool* pObj);
	void		Select(CDrawTool* pObj, BOOL bAdd = FALSE);
	void		SelectWithinRect(CRect rect, BOOL bAdd = FALSE);
	void		Deselect(CDrawTool* pObj);
	CDrawTool*	GetSelect();

	void		CaricaReport(CString strFileReport);
	void		SalvaReport(CString strFileReport);
	void		NuovoReport();

	void		RidimensionaPagina();
	void        RiposizionaOggetti();
	int         GetCurrentWidth();
	int         GetCurrentHeight();

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonCtrl1;
	CButtonLocalize m_ctrlButtonCtrl2;
	CButtonLocalize m_ctrlButtonCtrl3;
	CButtonLocalize m_ctrlButtonCtrl4;
	CButtonLocalize m_ctrlButtonCtrl5;
	CButtonLocalize m_ctrlButtonCtrl6;
	CButtonLocalize m_ctrlButtonCtrl7;
	CButtonLocalize m_ctrlButtonCtrl10;
	CButtonLocalize m_ctrlButtonCtrl11;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonLoad;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonSaveAs;
	CButtonLocalize m_ctrlButtonPreview;
	CButtonLocalize m_ctrlButtonChiudi;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CStaticLocalize m_ctrlStatic7;
	CStaticLocalize m_ctrlStatic8;
	CStaticLocalize m_ctrlStatic9;
	CStaticLocalize m_ctrlStatic10;
	CStaticLocalize m_ctrlStatic11;
	CStaticLocalize m_ctrlStatic12;
	CStaticLocalize m_ctrlStatic13;
	CStaticLocalize m_ctrlStatic14;
	CStaticLocalize m_ctrlStatic15;

private:

	void RiempiCombo();

	CEsamiView* m_pEsamiView;

	int nDiffDialogFrame;
	int nHeightDialog;
	int nHeightFrame;

	long m_lIDStampante;
	long m_lIDHeader1;
	long m_lIDHeader2;
	long m_lIDFooter1;
	long m_lIDFooter2;
	int m_nDimHeader;
	int m_nDimFooter;

	CComboBox m_ctrlComboStampante;
	CComboBox m_ctrlComboHeader1;
	CComboBox m_ctrlComboHeader2;
	CComboBox m_ctrlComboFooter1;
	CComboBox m_ctrlComboFooter2;

};

#endif /* _REPORTDLG_H_ */