#ifndef __MOSAICDLG_H__
	#define __MOSAICDLG_H__

#include "EndoxResizableDlg.h"
#include "RigheList.h"
#include "PazientiSet.h"
#include "EsamiSet.h"

class CExportDlg;
class CQueryDlg;
class CShowEsameForm;

class CMosaicDlg : public CEndoxResizableDlg
{
	DECLARE_DYNCREATE(CMosaicDlg)

public:

	CMosaicDlg(CWnd* pParent = NULL, CEsamiView* pEsamiView = NULL);
	virtual ~CMosaicDlg(void);

	enum { IDD = IDD_ALBUM_TOTALE };

	CBitmapButtonEx	m_BtnEsaFirst;
	CBitmapButtonEx m_BtnEsaPrevP;
	CBitmapButtonEx m_BtnEsaPrev;
	CBitmapButtonEx m_BtnEsaNext;
	CBitmapButtonEx m_BtnEsaNextP;
	CBitmapButtonEx m_BtnEsaLast;
	CBitmapButtonEx m_BtnVista;
	CBitmapButtonEx m_btnExp;
	CBitmapButtonEx m_btnEsci;

	int				m_nDiapoPerEsame;
	int				m_nEsamiPerPage;

	CRigheList		m_ListRighe;

	CPazientiSet	m_PazientiSet;
	CEsamiSet		m_EsamiSet;
	CEsamiView*		m_pEsamiView;
	structEsame		m_RigaEsame[NUM_ESAMI_MAX];

	CShowEsameForm*	m_pShowEsame[NUM_ESAMI_MAX];

	CExportDlg*		m_pWndExport;

	int				m_ArrayPosition;
	CQueryDlg*		m_pQueryDlg;
	CDWordArray		m_ArrayCode;

	void	AfterMoveEsame(BOOL bFound);
	void	DeleteSelection();
	void	DeleteSelection(long nCodEsame, long lID);

	void	GoPageFirst(int nEsame); 
	void	GoPagePrev(int nEsame);
	void	GoPageNext(int nEsame);
	void	GoPageLast(int nEsame);
	void	SelectAllImages(int nEsame);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnEsamiFirst();
	afx_msg void OnEsamiPrevPage();
	afx_msg void OnEsamiPrev();
	afx_msg void OnEsamiNext();
	afx_msg void OnEsamiNextPage();
	afx_msg void OnEsamiLast();
	afx_msg void OnExport();
	afx_msg void OnDestroy();
	afx_msg void OnCambiaVista();
	afx_msg LONG OnSelectBmp(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnSelectAllBmp(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT AfterElabImage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	BOOL	FiltraPazienti();
	void	ResetVetDiapo(BOOL bBmp);
	int		FillDiapoIndex(int nEsame);
	void	GoToPage(int nEsame, int nPage);
	void	MoveImage(int nEsame);

	void	RepositionPages();
	void	RegisterPages();
	void	SetDiapoPerPage(int nDiapoPerPage);
	void	CreateFormEsami();

private:

	void CaricaPunti(int nEsame);

	static UINT uiFrameEsami[NUM_ESAMI_MAX];
	static UINT uiFrameImmagini[NUM_ESAMI_MAX][NUM_MOSAIC_MAX];

	void UpdateFramesPos();

	BOOL m_bInizializzato;
};

#endif  /* __MOSAICDLG_H__ */