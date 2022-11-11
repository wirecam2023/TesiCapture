#ifndef _ASSOCIAIMMAGINI_H_
	#define _ASSOCIAIMMAGINI_H_

#include "EndoxResizableDlg.h"
#include "OrganiSet.h"

#define MAX_FOTO_BMP 8

class CAssociaImmagini : public CEndoxResizableDlg
{

public:
	
	CAssociaImmagini(CWnd* pParent, CEsamiView* pEsamiView);
	~CAssociaImmagini(void);

	enum { IDD = IDD_ASS_IMM };

	CButtonLocalize m_ctrlButtonOK;
	CBitmapButtonEx	m_BtnOrgFirst;
	CBitmapButtonEx	m_BtnOrgPrev;
	CBitmapButtonEx	m_BtnOrgNext;
	CBitmapButtonEx	m_BtnOrgLast;
	CBitmapButtonEx	m_BtnImmFirst;
	CBitmapButtonEx	m_BtnImmPrev;
	CBitmapButtonEx	m_BtnImmNext;
	CBitmapButtonEx	m_BtnImmLast;

	CFileBmp*		m_pFileFotoBmp[MAX_FOTO_BMP];

	CEsamiView*		m_pEsamiView;

	int				m_nMaxDiapo;
	int				m_nDiapoPage;

	void AfterMoveEsame(BOOL bIsSetValid, BOOL bRewind = TRUE);
	void AlbumRedraw();

	int  FillDiapoIndex();

	void MoveImageImm();

	void OnPageFirst();

	void RequeryPage();
	void ResetVetDiapo(BOOL bReposition);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnCancel();
	afx_msg void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnFrstOrg();
	afx_msg void OnPrevOrg();
	afx_msg void OnNextOrg();
	afx_msg void OnLastOrg();
	afx_msg void OnFrstImm();
	afx_msg void OnPrevImm();
	afx_msg void OnNextImm();
	afx_msg void OnLastImm();

	afx_msg LRESULT OnSelectBmp(WPARAM wParam, LPARAM lParam);

	afx_msg void OnNMDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:

	void MoveImageOrg();
	void ModificaInterfaccia(BOOL bShowAlbum);
	void RiempiListaImmagini();

	CListCtrl m_ctrlListImage;
	CImageList m_listImage;
	CImgListOrgani m_ImgListOrgani;

	COrganiSet m_setOrgani;

	long m_lPaziente;
	long m_lEsame;
	BOOL m_bConfirmed;
	CString m_strDvdLabel;

	/////

	void MillesimiPixel(long &lX, long &lY); // passo i millesimi mi torna i pixel //
	void PixelMillesimi(long &lX, long &lY); // passo i pixel mi ritorna i millesimi //

	int AggiungiPunto(long lIdPunto, long lIdOrgano, long lX, long lY);
	void EliminaPunto(long lIdOrgano, long lX, long lY);
	void ModificaPunto(long lX, long lY);
	void SelezionaPunto(long lIdOrgano, long lX, long lY);
	int TrovaPunto(long lIdOrgano, long lX, long lY);

	void CaricaPunti();
	void SalvaPunti();
	void SelezionaImmagini(BOOL bRedraw);

	CRect m_dstRect;
	int m_nCurSel;

	CList <tagPunti> listPunti;

	CDib m_Dib;

};

#endif /* _ASSOCIAIMMAGINI_H_ */