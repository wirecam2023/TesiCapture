#ifndef _INTESTAZIONENEWDLG_H_
	#define _INTESTAZIONENEWDLG_H_
#include "afxwin.h"

class CDrawTool;
class CElemReportSet;

#define CTRL_NOTHING	0
#define CTRL_TEXT		1
#define CTRL_BMP		2
#define CTRL_LINE       3
#define CTRL_FIELD		4
#define CTRL_PAGENUM	5
#define CTRL_PAGETOT	6
#define CTRL_PARAM		7

typedef CTypedPtrList<CObList, CDrawTool*> CDrawObjList;

class CIntestazioneNewDlg : public CDialog
{

public:

	CIntestazioneNewDlg(CWnd* pParent, CEsamiView* pEsamiView);
	~CIntestazioneNewDlg();
	
	enum { IDD = IDD_INTESTAZIONE_REPORT };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnCbnSelchangeComboDimensione();
	afx_msg void OnCbnSelchangeComboHeader();
	afx_msg void OnCbnSelchangeComboFooter();

	afx_msg void OnChangeAltezzaInt();
	afx_msg void OnBnClickedNuovoInt();
	afx_msg void OnBnClickedModificaInt();
	afx_msg void OnBnClickedEliminaInt();
	afx_msg void OnBnClickedSalvaInt();
	afx_msg void OnBnClickedAnnullaInt();

	afx_msg void OnChangeAltezzaCoda();
	afx_msg void OnBnClickedNuovoCoda();
	afx_msg void OnBnClickedModificaCoda();
	afx_msg void OnBnClickedEliminaCoda();
	afx_msg void OnBnClickedSalvaCoda();
	afx_msg void OnBnClickedAnnullaCoda();

	afx_msg void OnClickControllo();
	afx_msg void OnRimuovi();

	afx_msg void OnCentraH();
	afx_msg void OnCentraV();

	afx_msg void OnAnteprima();
	afx_msg void OnEsci();

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonControl1;
	CButtonLocalize m_ctrlButtonControl2;
	CButtonLocalize m_ctrlButtonControl3;
	CButtonLocalize m_ctrlButtonControl4;
	CButtonLocalize m_ctrlButtonControl5;
	CButtonLocalize m_ctrlButtonControl6;
	CButtonLocalize m_ctrlButtonControl7;
	CButtonLocalize m_ctrlButtonControl8;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonCentraH;
	CButtonLocalize m_ctrlButtonCentraV;
	CButtonLocalize m_ctrlButtonAnteprima;
	CButtonLocalize m_ctrlButtonNewInt;
	CButtonLocalize m_ctrlButtonEdtInt;
	CButtonLocalize m_ctrlButtonDelInt;
	CButtonLocalize m_ctrlButtonSaveInt;
	CButtonLocalize m_ctrlButtonUndoInt;
	CButtonLocalize m_ctrlButtonNewCoda;
	CButtonLocalize m_ctrlButtonEdtCoda;
	CButtonLocalize m_ctrlButtonDelCoda;
	CButtonLocalize m_ctrlButtonSaveCoda;
	CButtonLocalize m_ctrlButtonUndoCoda;
	CButtonLocalize m_ctrlButtonEsci;
	CComboBox		m_ctrlComboHeader;
	CComboBox		m_ctrlComboFooter;
	CStatic			m_ctrlFrameTotal;
	CStatic			m_ctrlFrameHeader;
	CStatic			m_ctrlFrameFooter;
	CSpinButtonCtrl	m_ctrlSpinInt;
	CSpinButtonCtrl	m_ctrlSpinCoda;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;

private:

	HCURSOR m_hCursorAdd;
    HCURSOR m_hCursorArrow; 
	
	int m_nMode;
	
	CRect m_rectTotal;
	CRect m_rectHeader;
	CRect m_rectFooter;
	CRect m_rectPage;

	CSize m_szPageHeader;
	CSize m_szPageFooter;

	void RiposizionaOggettiHeader();
	void RiposizionaOggettiFooter();

	void BuildDCForPreview(CDC* pOutDC, CDC* pDC);
	
	int m_nFormatoPagina; // formato della pagina --> 0 è A4 etc etc... //
	int m_nAltezzaHeader; // altezza header in mm //
	int m_nAltezzaFooter; // altezza footer in mm //

	int GetCurrentWidth();
	int GetCurrentHeight();

	CSize m_szFoglioA4;
	CSize m_szFoglioLegal;
	CSize m_szFoglioLetter;
	CSize m_szFoglioExclusive;
	CSize m_szFoglioA4Landscape;//Gabriel BUG 6303

	CEsamiView*	m_pEsamiView;

	float fMult;

	BOOL m_bInitializing;

	CDrawObjList m_ObjectsHeader;
	CDrawObjList m_ObjectsFooter;
	CDrawObjList m_selection;

	/////
	void		Add(CDrawTool* pObj);
	void		Remove(CDrawTool* pObj);
	CDrawTool*	ObjectAt(const CPoint& point);
	BOOL		IsSelected(CDrawTool* pObj);
	void		Select(CDrawTool* pObj, BOOL bAdd = FALSE);
	void		SelectWithinRect(CRect rect, BOOL bAdd = FALSE);
	void		Deselect(CDrawTool* pObj);
	CDrawTool*	GetSelect();
	void		CentraOrizz(CDrawTool* pObj);
	void		CentraVert(CDrawTool* pObj);
	/////

	void ModifyHeader(BOOL bHeaderModified);
	void ModifyFooter(BOOL bFooterModified);

	BOOL m_bHeaderModified;
	BOOL m_bFooterModified;

	long m_lIDHeader;
	long m_lIDFooter;

};

#endif