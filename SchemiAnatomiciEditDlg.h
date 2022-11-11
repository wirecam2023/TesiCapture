// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury

#ifndef _SCHEMIANATOMICIEDITDLG_H_
#define _SCHEMIANATOMICIEDITDLG_H_

#include "EndoxResizableDlg.h"
#include "ListSortableCtrl.h"
#include "SchemiAnatomiciSet.h"
#include "SchemiAnatomiciEtichetteSet.h"
#include "SchemiAnatomiciAggiuntoSet.h"
#include "SchemiAnatomiciAggiuntoEtichetteSet.h"
#include "DLL_Imaging\h\AMEditComboListCtrl.h"
#include "TipoEsameSet.h"
#include "UOSet.h"

#define MAX_FOTO_BMP 8

class CSchemiAnatomiciEditDlg : public CEndoxResizableDlg
{

public:
	CSchemiAnatomiciEditDlg(CWnd* pParent, CEsamiView* pEsamiView, long p_lContatoreSchemiAggiuntoToEdit, long p_lIDSchemiAnatomici);
	~CSchemiAnatomiciEditDlg(void);

	enum { IDD = IDD_SCHEMI_ANATOMICI_EDIT };

	class CEtichetteAggiunta {
	public:
		long m_lCONTATORE;							// da nova etiqueta adicionada
		long m_lID_SCHEMI_ANATOMICI_AGGIUNTO;				// 
		long m_lID_SCHEMI_ANATOMICI_ETICHETTE;
		CString m_sDESCRIZIONE;
		CRect m_pRectPUNTI;
		COLORREF m_lCOLORE;
		CString m_sAcao;					// Database action [NEW,SAME,ALTERED,DELETED,FORGET]
	};

	CEsamiView*		m_pEsamiView;

	long m_lContatoreSchemiAggiuntoToEdit;	// from to [dbo].[SCHEMI_ANATOMICI_AGGIUNTO].[CONTATORE]
	long m_lIDSchemiAnatomici;				// from to [dbo].[SCHEMI_ANATOMICI_ETICHETTE].[ID_SCHEMI_ANATOMICI]

	// Preparação do registro para ser adicionado a lista de labels
	// SCHEMI_ANATOMICI_ETICHETTE >>> SCHEMI_ANATOMICI_[AGGIUNTO]_ETICHETTE
	CEtichetteAggiunta m_pCurrentEtichetteToInsert;	
													
	BOOL ImageMergeLayersAndExportToAlbum();
	void ListSchemiAnatomiciEtichetteAggiuntoRiempi(long p_lContatoreSchemiAggiuntoToEdit);

	CList <CEtichetteAggiunta> m_lstEtichetteAggiunta;
	BOOL m_bAltered;										// controla se houve alteração no forma, se sim precisa salvar ou senão as alterações serão perdidas

protected:
	// INICIALIZAÇÃO
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	// BOTOES SALVAR E FECHAR
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedClose();
	//afx_msg void OnCancel();
	//afx_msg void OnOK();


	// ESQUEMAS ANATOMICOS (BOTOES ABAIXO DO GRID)
	//afx_msg void OnBnClickedDel();
	//afx_msg void OnBnClickedNew();
	//afx_msg void OnBnClickedClone();

	// CRIAÇÃO DE LABELS
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	// APRESENTAÇÃO DA TELA, IMAGEM, LABELS
	afx_msg void OnPaint();
	void DrawLabels();
	//void CaptureScreen(HWND hCaptureWnd);

	BOOL bOnBnClickedShowEtichetteShowOrHide; // Show = FALSE, Hide = TRUE;

	DECLARE_MESSAGE_MAP()

private:
	// USADOS PARA CONTROLAR OS RECORDSETS (DATABASE)
	CSchemiAnatomiciSet          m_setSchemiAnatomici;
	CSchemiAnatomiciEtichetteSet m_setSchemiAnatomiciEtichette;

	// USADO PARA INDICAR O ESQUEMA SELECIONADO (NO GRID) / A LABEL SELECIONADA (NO GRID)
	CSchemiAnatomici* m_pSchemiAnatomiciActual;   // CWnd Class Base
	CSchemiAnatomiciEtichette* m_pSchemiAnatomiciEtichetteActual;   // CWnd Class Base

	// USADO PARA APRESENTAR A IMAGEM IMPORTADA
	CRect m_RectToShowImage;
	CDib  m_Dib;
	double m_dFactor;
	
	//void GetAndOpenImage(long p_lID);
	BOOL ImportImageFromDisk(CString p_sFullPathImg, CDib* p_Dib);
	void ImageOpenDlgImport();
	BOOL ImageShow(CString p_sFullPathImage);
	void ImageAndEtichetteShow(long p_lID);
	double ImageCalcZoomFactor(CRect* p_pRectClient, CDib* p_pDib);
	void FillSemiTransparentRegion();

	// USADOS PARA DESENHAR FORMAS
	void DrawPoint(CPoint p_ptWhere, COLORREF p_color);
	void DrawRetangle(CPoint p_ptTopLeft, CPoint p_ptBottomRight, COLORREF p_color, BOOL p_bGhostColor = TRUE);
	void DrawRetangle( CRect p_Rect, COLORREF p_color, BOOL p_bGhostColor = TRUE);
	void DrawEtichette(COLORREF p_cfCOLOR);
	void DrawEtichetteAll(long p_lID, COLORREF p_cfCOLOR, int p_iRedHighlighted = -1);

	const int m_diff = 268;   // diferença entre a tela que cadastra e a tela que apresenta as etiquetes....

	int m_iRetunState;

public:
	afx_msg void OnBnClickedExp();
	afx_msg void OnBnClickedHlp();
};

#endif /* _SCHEMIANATOMICIEDITDLG_H_ */