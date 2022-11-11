#ifndef _ABOUTBOXDLG_H_
	#define _ABOUTBOXDLG_H_

#include "MyHyperLink.h"

class CAboutBoxDlg : public CDialog
{

public:

	CAboutBoxDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_ABOUTBOX };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

private:

	CMyHyperLink m_ctrlStaticMail;
	CMyHyperLink m_ctrlStaticWeb;

	HBITMAP m_hCertificateBitmap;

};

#endif /* _ABOUTBOXDLG_H_ */