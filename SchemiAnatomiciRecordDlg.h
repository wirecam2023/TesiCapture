// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury

#ifndef _SchemiAnatomiciRecordDlg_H_
#define _SchemiAnatomiciRecordDlg_H_

#include "EndoxResizableDlg.h"
#include "ListSortableCtrl.h"
#include "SchemiAnatomiciSet.h"
#include "SchemiAnatomiciEtichetteSet.h"
#include "DLL_Imaging\h\AMEditComboListCtrl.h"
#include "TipoEsameSet.h"
#include "UOSet.h"

#define MAX_FOTO_BMP 8

class CSchemiAnatomiciRecordDlg : public CDialog
{
	DECLARE_DYNAMIC(CSchemiAnatomiciRecordDlg)

public:
	CSchemiAnatomiciRecordDlg(CWnd* pParent, CEsamiView* pEsamiView);
	~CSchemiAnatomiciRecordDlg(void);

	enum { IDD = IDD_SCHEMI_ANATOMICI_RECORD };

	CEsamiView*		m_pEsamiView;

protected:
	// INICIALIZAÇÃO
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	// BOTOES SALVAR E FECHAR
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedClose();
	afx_msg void OnCancel();
	afx_msg void OnOK();

	// CLICKS NAS GRIDS
	afx_msg void OnNMClickListSchemiAnatomici(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSchemiAnatomici(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickListSchemiAnatomiciEtichette(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSchemiAnatomiciEtichette(NMHDR *pNMHDR, LRESULT *pResult);

	// LABELS (BOTOES ABAIXO DO GRID)
	afx_msg void OnBnClickedShowEtichette();
	afx_msg void OnBnClickedDelEtichette();

	// ESQUEMAS ANATOMICOS (BOTOES ABAIXO DO GRID)
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedClone();

	// CRIAÇÃO DE LABELS
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	// APRESENTAÇÃO DA TELA, IMAGEM, LABELS
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bAlteredSchemi;										// controla se houve alteração no forma, se sim precisa salvar ou senão as alterações serão perdidas
	BOOL m_bAlteredEtichette;									// controla se houve alteração no forma, se sim precisa salvar ou senão as alterações serão perdidas

	// USADOS PARA CONTROLAR OS RECORDSETS (DATABASE)
	CSchemiAnatomiciSet          m_setSchemiAnatomici;
	CSchemiAnatomiciEtichetteSet m_setSchemiAnatomiciEtichette;

	// USADO PARA INDICAR O ESQUEMA SELECIONADO (NO GRID) / A LABEL SELECIONADA (NO GRID)
	CSchemiAnatomici* m_pSchemiAnatomiciActual;   // CWnd Class Base
	CSchemiAnatomiciEtichette* m_pSchemiAnatomiciEtichetteActual;   // CWnd Class Base

	// USADOS PARA CONTROLAR OS GRIDS
	CAMEditComboListCtrl m_ctrlListGridSchemiAnatomici;           // Binded to [SCHEMI_ANATOMICI]
	CAMEditComboListCtrl m_ctrlListGridSchemiAnatomiciEtichette;  // Binded to [SCHEMI_ANATOMICI_ETICHETTE]

	long ListGridSchemiAnatomiciRiempi(int p_iActualRow=-1);
	int ListGridSchemiAnatomiciAddThisRegAsNewRow();
	void ListGridSchemiAnatomiciSetTemp(CSchemiAnatomiciSet* p_setTemp, int p_nRowNumber);
	CString ListGridSchemiAnatomiciGetAcao(long* p_lID, int p_nRowNumber);
	long ListGridSchemiAnatomiciGetIDSelected();
	void ListGridSchemiAnatomiciSaveAllToDatabase();
	void ListGridSchemiAnatomiciUpdateActual(long p_lIDSelected);
	BOOL ListGridSchemiAnatomiciValidaPossibilidadeDeEdicaoDaRowSelecionada();

	long ListGridSchemiAnatomiciEtichetteRiempi(long p_lID);
	int ListGridSchemiAnatomiciEtichetteAddThisRegAsNewRow();
	void ListGridSchemiAnatomiciEtichetteSetTemp(CSchemiAnatomiciEtichetteSet* p_setTemp, int p_nRowNumber);
	CString ListGridSchemiAnatomiciEtichetteGetAcao(long* p_lID, int p_nRowNumber);
	long ListGridSchemiAnatomiciEtichetteGetIDSelected();
	void ListGridSchemiAnatomiciEtichetteSaveAllToDatabase();
	void ListGridSchemiAnatomiciEtichetteUpdateActual(long p_lIDSelected);

	void ListGridSetDBControl(CAMEditComboListCtrl* p_pThisList, int p_iRow, CString p_strDBControl);
	int  ListGridGetColumnsCount(CAMEditComboListCtrl* p_pThisList);
	void ListGridSetItemFocus(CAMEditComboListCtrl* p_pThisList, int iRow);
	
	// USADO PARA TROCAR A LABEL DO BOTÃO: OMITIR / MOSTRAR 
	CButton m_ctrlButtonSHOW;	//CButtonLocalize
	BOOL bOnBnClickedShowEtichetteShowOrHide; // Show = FALSE, Hide = TRUE;

	// USADO PARA APRESENTAR A IMAGEM IMPORTADA
	CRect m_RectToShowImage;
	CDib  m_Dib;
	double m_dFactor;

	BOOL ImportImageFromDisk(CString p_sFullPathImg, CDib* p_Dib);
	void ImageOpenDlgImport();
	BOOL ImageShow(CString p_sFullPathImage);
	void ImageAndEtichetteShow();
	double ImageCalcZoomFactor(CRect* p_pRectClient, CDib* p_pDib);

	// USADOS PARA DELIMITAR O CANTO SUPERIOR ESQUERDO / CANTO INFERIOR DIREITO DAS LABELS
	COLORREF m_ColorPoint;
	CPoint m_ptFirst;
	CPoint m_ptSecond;
	BOOL m_bFirstDone;
	BOOL m_bSecondDone;

	// USADOS PARA DESENHAR FORMAS
	void DrawPoint(CPoint p_ptWhere, COLORREF p_color);
	void DrawRetangle(CPoint p_ptTopLeft, CPoint p_ptBottomRight, COLORREF p_color, BOOL p_bGhostColor=TRUE);
	void DrawRetangle(CRect p_Rect, COLORREF p_color, BOOL p_bGhostColor = TRUE);
	void DrawEtichette(int p_iRow, COLORREF p_cfCOLOR);
	void DrawEtichetteAll(COLORREF p_cfCOLOR, int p_iRedHighlighted = -1);
public:
	afx_msg void OnBnClickedHlp();
};

#endif /* _SchemiAnatomiciRecordDlg_H_ */