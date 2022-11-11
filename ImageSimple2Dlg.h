#pragma once
#include "afxres.h"			// Marvel Carvalho - Bug 4269 Dialog ImageSimple2Dlg ignora album com 1 imagem
#include "EsamiView.h"
#include "MaximizeDlg.h"

// CImageSimple2Dlg dialog

class CImageSimple2Dlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CImageSimple2Dlg)

public:
	CImageSimple2Dlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bAjustToParent = FALSE, BOOL bIsReferto = FALSE);   // standard constructor
	virtual ~CImageSimple2Dlg();

// Dialog Data
	enum { IDD = IDD_IMAGE_SIMPLE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy(); //Gabriel BUG 6225 - Lista DO
	BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	DECLARE_MESSAGE_MAP()
private:	
	BOOL CaricaImmagine();
	void UpdateButtonsEnabling();
	void AjustToParent();	
	void PrepareRectangle();
	void AutoRedraw();

	CEsamiView* m_pEsamiView;
	long m_lPaziente;
	long m_lEsame;
	
	int m_nNumPage;
	int m_nTotPage;

	BOOL m_bAjustToParent;
	int m_iParentX;
	int m_iParentY;
	int m_iParentWidth;
	int m_iParentHeight;

	BOOL m_bReloadFrame;	

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;
	
	CBitmapButtonEx m_ctrlButtonFirst;
	CBitmapButtonEx m_ctrlButtonPrev;
	CBitmapButtonEx m_ctrlButtonNext;
	CBitmapButtonEx m_ctrlButtonLast;

	CStatic m_ctrlImageFrame;
	CImgListOrgani m_ImgList;

	CDib* m_pDib;	
	int m_nTGAWidth;
	int m_nTGAHeight;
	int m_nDLGWidth;
	int m_nDLGHeight;
	CRect m_DibRectScreen;
	CRect m_DibRectSource;

	BOOL m_bIsReferto;

public:
	afx_msg void OnBnClickedButtonFirst();
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonLast();
	afx_msg void OnStnDblclickImagebox();
	afx_msg void OnPaint();

	CString m_sCurImgPath; //Julio - BUG 4392 Enriquecimento da ferramenta de edição de laudo 
	afx_msg void OnOk(); //Gabriel BUG 6225 - Lista DO
	afx_msg void OnCancel(); //Gabriel BUG 6225 - Lista DO
};