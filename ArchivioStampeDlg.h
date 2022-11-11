#pragma once

#include "DLL_Imaging\h\AmPdfManager.h"

#include "EndoxResizableDlg.h"

class CArchivioStampeDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CArchivioStampeDlg)

public:

	struct tagPDFVIEW
	{
		long lID;
		char szData[20];
		pdftype ptTipo;
		char szNote[256];
		BOOL bFirmato;
		BOOL bSospeso;
		BOOL bAnnullato;
		BOOL bFitToPage;
		BOOL bCriptato;
		char szDisco[2];
		char szPercorsoFileRemoto[256];

		char szFile[MAX_PATH];
	};

	CArchivioStampeDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, CList<tagPDFVIEW>* pPdfView, LPCTSTR szTitle, BOOL bShowLeftList);
	virtual ~CArchivioStampeDlg();

	enum { IDD = IDD_ARCHIVIO_STAMPE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK(){}

	DECLARE_MESSAGE_MAP()

	afx_msg void OnButtonAnnullaPDF();
	afx_msg void OnButtonDel();
	afx_msg void OnButtonExport();
	afx_msg void OnButtonMail();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonFirmaSelezionato();
	afx_msg void OnButtonFirmaTutti();

	afx_msg void OnButtonPagePrec();
	afx_msg void OnButtonPageSucc();
	afx_msg void OnButtonZoomIn();
	afx_msg void OnButtonZoomOut();

	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnListSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:

	void ViewPdf();

	//

	CButtonLocalize m_ctrlBtnPagePrec;
	CButtonLocalize m_ctrlBtnPagePrecFull;
	CButtonLocalize m_ctrlBtnPageSucc;
	CButtonLocalize m_ctrlBtnPageSuccFull;
	CButtonLocalize m_ctrlBtnZoomIn;
	CButtonLocalize m_ctrlBtnZoomInFull;
	CButtonLocalize m_ctrlBtnZoomOut;
	CButtonLocalize m_ctrlBtnZoomOutFull;
	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnAnnullaPDF;
	CButtonLocalize m_ctrlBtnEliminaPdf;
	CButtonLocalize m_ctrlBtnExport;
	CButtonLocalize m_ctrlBtnMail;
	CButtonLocalize m_ctrlBtnModificaNoteVS;
	CButtonLocalize m_ctrlBtnPrint;
	CButtonLocalize m_ctrlBtnFirmaSelezionato;
	CButtonLocalize m_ctrlBtnFirmaTutti;

	CListCtrl m_ctrlList;

	//

	CEsamiView* m_pEsamiView;
	CList<tagPDFVIEW>* m_pListPDF;
	CString m_strTitle;
	BOOL m_bShowLeftList;

	//

	BYTE* m_pBufferPdf;
	UINT m_uiTemp;

public:
	afx_msg void OnBnClickedBtnModificanoteVs();
};
