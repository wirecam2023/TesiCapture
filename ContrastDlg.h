#ifndef _CONTRASTDLG_H_
	#define _CONTRASTDLG_H_

#include <AfxWin.h>
#include <WindowsX.h>
#include "Dib.h"
#include "Chart.h"
// #include "Common.h"

class CContrastDlg : public CDialog
{

public:

	CContrastDlg(CWnd* pParent = NULL, CDib* pDib = NULL, CDib* pRoi = NULL);
	virtual ~CContrastDlg(void);

	enum { IDD = IDD_CONTRAST };
	CScrollBar		m_ctrlLigth;
	CScrollBar		m_ctrlDark;
	CStatic			m_ctrChart;
	CStatic			m_ctrFrame;

	int*			m_pDarkLev;
	int*			m_pLigthLev;

	LPLOGPALETTE	m_pLogPal;
	LPLOGPALETTE	m_pOldPal;
	CDib*			m_pDib;
	CDib*			m_pDibRoi;
	CDib*			m_pDibReal;

	CWnd*			m_pView;

	BOOL			m_bRedraw;
	CChart*			m_pChart;

protected:

	DWORD	GetMaxValue(int numV);
	void	GetDataFromImage();

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonOK, m_ctrlButtonCancel;
};

#endif /* _CONTRASTDLG_H_ */