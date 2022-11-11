#ifndef _PDFANTEPRIMADLG_H_
	#define _PDFANTEPRIMADLG_H_

#include "EndoxResizableDlg.h"

class CPdfAnteprimaDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CPdfAnteprimaDlg)

public:

	CPdfAnteprimaDlg(CWnd* pParent, CEsamiView* pEsamiView, CString sPdfFile, long lModalita);
	virtual ~CPdfAnteprimaDlg();

	enum { IDD = IDD_PDF_ANTEPRIMA };

	static long m_lDefaultZoomValue;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel() { }
	virtual BOOL OnInitDialog();
	virtual void OnOK() { }

	DECLARE_MESSAGE_MAP()

	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedBtnPrint();
	afx_msg void OnBnClickedBtnFirma();
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnZoomIn();
	afx_msg void OnBnClickedBtnZoomOut();
	afx_msg void OnBnClickedBtnImmagini();
	afx_msg void OnBnClickedBtnExit();

private:

	CButtonLocalize m_ctrlBtnPrint;
	CButtonLocalize m_ctrlBtnFirma;
	CButtonLocalize m_ctrlChkStampa;
	CButtonLocalize m_ctrlBtnPrev;
	CButtonLocalize m_ctrlBtnNext;
	CButtonLocalize m_ctrlBtnZoomIn;
	CButtonLocalize m_ctrlBtnZoomOut;
	CButtonLocalize m_ctrlBtnImmagini;
	CButtonLocalize m_ctrlBtnExit;

	CEsamiView* m_pEsamiView;
	CString m_sPdfFile;
	long m_lModalita;

	UINT m_uiTemp;
};

#endif /* _PDFANTEPRIMADLG_H_ */