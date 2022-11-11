#ifndef _CONTRASTRGBDLG_H_
	#define _CONTRASTRGBDLG_H_

#include <AfxWin.h>
#include "Dib.h"
#include "Chart.h"
#include "Common.h"

class CContrastRGBDlg : public CDialog
{

public:

	CContrastRGBDlg(CWnd* pParent = NULL, CDib* pDib = NULL, CDib* pRoi = NULL);
	virtual ~CContrastRGBDlg(void);

	void PlotGraphics();

	enum { IDD = IDD_CONTRAST_RGB };

	CScrollBar		m_ctrlDark;
	CScrollBar		m_ctrlLigth;
	CScrollBar		m_ctrlRDark;
	CScrollBar		m_ctrlRLigth;
	CScrollBar		m_ctrlGDark;
	CScrollBar		m_ctrlGLigth;
	CScrollBar		m_ctrlBDark;
	CScrollBar		m_ctrlBLigth;
	CStatic			m_ctrChartRed;
	CStatic			m_ctrChartGreen;
	CStatic			m_ctrChartBlue;
	CStatic			m_ctrChartIntensity;
	CStatic			m_ctrLargeFrameRed;
	CStatic			m_ctrLargeFrameGreen;
	CStatic			m_ctrLargeFrameBlue;
	CStatic			m_ctrLargeFrameIntensity;
	int				m_nIsRGB;

	int*			m_PosMinR;
	int*			m_PosMaxR;
	int*			m_PosMinG;
	int*			m_PosMaxG;
	int*			m_PosMinB;
	int*			m_PosMaxB;
	int*			m_PosMinInt;
	int*			m_PosMaxInt;

	CDib*			m_pDib;
	CDib*			m_pDibRoi;
	CDib*			m_pDibReal;

	CWnd*			m_pView;

	BOOL			m_bRedraw;
	CChart*			m_pChartR;
	CChart*			m_pChartG;
	CChart*			m_pChartB;
	CChart*			m_pChartInt;

protected:

	DWORD	GetMaxValue(int Type, int numV);
	void	GetDataFromImage();

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRadioRGB();
	afx_msg void OnRadioInt();

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonInt, m_ctrlButtonRGB, m_ctrlButtonCancel, m_ctrlButtonOK;
};

#endif /* _CONTRASTRGBDLG_H_ */