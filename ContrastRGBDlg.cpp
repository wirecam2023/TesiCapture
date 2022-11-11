#include "stdafx.h"
#include "Endox.h"
#include "ContrastRGBDlg.h"

#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CContrastRGBDlg::CContrastRGBDlg(CWnd* pParent, CDib* pDib, CDib* pRoi)
	: CDialog(CContrastRGBDlg::IDD, pParent)
{
	m_nIsRGB = 0;

	m_pView		= pParent;
	m_pDibReal	= NULL;
	m_pDib		= pDib;
	m_pDibRoi	= pRoi;

	m_bRedraw	= FALSE;	

	m_pChartR	= new CChart(HORZ_HISTOGRAM);
	m_pChartG	= new CChart(HORZ_HISTOGRAM);
	m_pChartB	= new CChart(HORZ_HISTOGRAM);
	m_pChartInt	= new CChart(LINE_XY_RGB);
	m_PosMinR	= &m_pChartR->m_PosMin;
	m_PosMaxR	= &m_pChartR->m_PosMax;
	m_PosMinG	= &m_pChartG->m_PosMin;
	m_PosMaxG	= &m_pChartG->m_PosMax;
	m_PosMinB	= &m_pChartB->m_PosMin;
	m_PosMaxB	= &m_pChartB->m_PosMax;
	m_PosMinInt = &m_pChartInt->m_PosMin;
	m_PosMaxInt = &m_pChartInt->m_PosMax;
}

CContrastRGBDlg::~CContrastRGBDlg()
{
	if (m_pDibReal)
	{
		m_pDibReal->ReleaseContents();
		delete m_pDibReal;
		m_pDibReal = NULL;
	}

	if (m_pChartR)
	{
		m_pChartR->ReleaseContents();
		delete m_pChartR;
		m_pChartR = NULL;
	}

	if (m_pChartG)
	{
		m_pChartG->ReleaseContents();
		delete m_pChartG;
		m_pChartG = NULL;
	}

	if (m_pChartB)
	{
		m_pChartB->ReleaseContents();
		delete m_pChartB;
		m_pChartB = NULL;
	}

	if (m_pChartInt)
	{
		m_pChartInt->ReleaseContents();
		delete m_pChartInt;
		m_pChartInt = NULL;
	}
}

void CContrastRGBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BLACK,					m_ctrlDark);
	DDX_Control(pDX, IDC_WHITE,					m_ctrlLigth);
	DDX_Control(pDX, IDC_R_D,					m_ctrlRDark);
	DDX_Control(pDX, IDC_R_L,					m_ctrlRLigth);
	DDX_Control(pDX, IDC_G_D,					m_ctrlGDark);
	DDX_Control(pDX, IDC_G_L,					m_ctrlGLigth);
	DDX_Control(pDX, IDC_B_D,					m_ctrlBDark);
	DDX_Control(pDX, IDC_B_L,					m_ctrlBLigth);
	DDX_Control(pDX, IDC_FRAME_CHART_RED,		m_ctrChartRed);
	DDX_Control(pDX, IDC_FRAME_CHART_GREEN,		m_ctrChartGreen);
	DDX_Control(pDX, IDC_FRAME_CHART_BLUE,		m_ctrChartBlue);
	DDX_Control(pDX, IDC_FRAME_CHART_INTENSITY, m_ctrChartIntensity);
	DDX_Control(pDX, IDC_LARGE_FRAME_RED,		m_ctrLargeFrameRed);
	DDX_Control(pDX, IDC_LARGE_FRAME_GREEN,		m_ctrLargeFrameGreen);
	DDX_Control(pDX, IDC_LARGE_FRAME_BLUE,		m_ctrLargeFrameBlue);
	DDX_Control(pDX, IDC_LARGE_FRAME_INTENSITY, m_ctrLargeFrameIntensity);
	DDX_Radio(pDX, IDC_RADIO_INT, m_nIsRGB);

	DDX_Control(pDX, IDC_RADIO_INT, m_ctrlButtonInt);
	DDX_Control(pDX, IDC_RADIO_RGB, m_ctrlButtonRGB);
	DDX_Control(pDX, IDCANCEL,      m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK,          m_ctrlButtonOK);

}

BEGIN_MESSAGE_MAP(CContrastRGBDlg, CDialog)
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_RADIO_RGB, OnRadioRGB)
	ON_BN_CLICKED(IDC_RADIO_INT, OnRadioInt)
END_MESSAGE_MAP()

void CContrastRGBDlg::OnOK() 
{
	if (m_pDibReal)
		*m_pDib = *m_pDibReal;

	UpdateData(TRUE);

	g_nContrastMinLev[0]		= *m_PosMinInt;
	g_nContrastMaxLev[0]		= *m_PosMaxInt;
	g_nContrastMinLev[1]		= *m_PosMinR;
	g_nContrastMaxLev[1]		= *m_PosMaxR;
	g_nContrastMinLev[2]		= *m_PosMinG;
	g_nContrastMaxLev[2]		= *m_PosMaxG;
	g_nContrastMinLev[3]		= *m_PosMinB;
	g_nContrastMaxLev[3]		= *m_PosMaxB;

	CDialog::OnOK();
}

void CContrastRGBDlg::OnCancel() 
{
	if (m_pDibReal)
		*m_pDib = *m_pDibReal;

	m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW);
	
	CDialog::OnCancel();
}

BOOL CContrastRGBDlg::OnInitDialog()               
{
	CDialog::OnInitDialog();

	m_pDibReal = new CDib;

	if (m_pDibReal)
		*m_pDibReal = *m_pDib;

	m_nIsRGB = g_nLastUse;
	UpdateData(FALSE);

	m_ctrlDark.  SetScrollRange (0, 255);
	m_ctrlDark.  SetScrollPos   (max(g_nContrastMinLev[0], 0));
	m_ctrlLigth. SetScrollRange (0, 255);
	m_ctrlLigth. SetScrollPos   (min(g_nContrastMaxLev[0], 255));
	m_ctrlRDark. SetScrollRange (0, 255);
	m_ctrlRDark. SetScrollPos   (max(g_nContrastMinLev[1], 0));
	m_ctrlRLigth.SetScrollRange (0, 255);
	m_ctrlRLigth.SetScrollPos   (min(g_nContrastMaxLev[1], 255));
	m_ctrlGDark. SetScrollRange (0, 255);
	m_ctrlGDark. SetScrollPos   (max(g_nContrastMinLev[2], 0));
	m_ctrlGLigth.SetScrollRange (0, 255);
	m_ctrlGLigth.SetScrollPos   (min(g_nContrastMaxLev[2], 255));
	m_ctrlBDark. SetScrollRange (0, 255);
	m_ctrlBDark. SetScrollPos   (max(g_nContrastMinLev[3], 0));
	m_ctrlBLigth.SetScrollRange (0, 255);
	m_ctrlBLigth.SetScrollPos   (min(g_nContrastMaxLev[3], 255));

	*m_PosMinInt = max(g_nContrastMinLev[0], 0);
	*m_PosMaxInt = min(g_nContrastMaxLev[0], 255);
	*m_PosMinR	 = max(g_nContrastMinLev[1], 0);
	*m_PosMaxR	 = min(g_nContrastMaxLev[1], 255);
	*m_PosMinG	 = max(g_nContrastMinLev[2], 0);
	*m_PosMaxG	 = min(g_nContrastMaxLev[2], 255);
	*m_PosMinB	 = max(g_nContrastMinLev[3], 0);
	*m_PosMaxB	 = min(g_nContrastMaxLev[3], 255);
    
	GetDataFromImage();
	
	int iMax = 0;
	int iTmp;
	iTmp = GetMaxValue(0, 256);
	iMax = max(iTmp, iMax);
	iTmp = GetMaxValue(1, 256);
	iMax = max(iTmp, iMax);
	iTmp = GetMaxValue(2, 256);
	iMax = max(iTmp, iMax);
	iTmp = GetMaxValue(3, 256);
	iMax = max(iTmp, iMax);

	m_pChartInt->SetDimensionFrame(this, &m_ctrChartIntensity);
    m_pChartInt->SetLabelChart("Min:","Max:");
	m_pChartInt->InitializeRGBChart(TRUE, TRUE, TRUE, TRUE);
    m_pChartInt->InitializeColorChart(BLACK, YELLOW);
    m_pChartInt->InitializeHChart(TRUE, 256, 255, 4, 0, 255);
    m_pChartInt->InitializeVChart(TRUE,  64,   5, 3, iMax);

	m_pChartR->SetDimensionFrame(this, &m_ctrChartRed);
    m_pChartR->SetLabelChart("Min:","Max:");
    m_pChartR->InitializeColorChart(RED, YELLOW);
    m_pChartR->InitializeHChart(TRUE, 256, 255, 4, 0, 255);
    m_pChartR->InitializeVChart(TRUE,  64,   5, 3, iMax);

    m_pChartG->SetDimensionFrame(this, &m_ctrChartGreen);
    m_pChartG->SetLabelChart("Min:","Max:");
    m_pChartG->InitializeColorChart(GREEN, YELLOW);
    m_pChartG->InitializeHChart(TRUE, 256, 255, 4, 0, 255);
    m_pChartG->InitializeVChart(TRUE,  64,   5, 3, iMax);

    m_pChartB->SetDimensionFrame(this, &m_ctrChartBlue);
    m_pChartB->SetLabelChart("Min:","Max:");
    m_pChartB->InitializeColorChart(BLUE, YELLOW);
    m_pChartB->InitializeHChart(TRUE, 256, 255, 4, 0, 255);
    m_pChartB->InitializeVChart(TRUE,  64,   5, 3, iMax);

	UpdateData(TRUE);

	if (m_nIsRGB == 0)
		ContrastPreviewRGB(*m_PosMinInt, *m_PosMaxInt, m_pDibReal, m_pDib);
	else
		ContrastPreviewRGB(*m_PosMinR, *m_PosMaxR, *m_PosMinG, *m_PosMaxG, *m_PosMinB, *m_PosMaxB, m_pDibReal, m_pDib);

	m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW);
	theApp.LocalizeDialog(this, CContrastRGBDlg::IDD, "ContrastRGBDlg");
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CContrastRGBDlg message handlers

void CContrastRGBDlg::OnRadioRGB()
{
	UpdateData(TRUE);

	PlotGraphics();

	ContrastPreviewRGB(*m_PosMinR, *m_PosMaxR, *m_PosMinG, *m_PosMaxG, *m_PosMinB, *m_PosMaxB, m_pDibReal, m_pDib);

	m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW);
}

void CContrastRGBDlg::OnRadioInt()
{
	UpdateData(TRUE);

	PlotGraphics();

	ContrastPreviewRGB(*m_PosMinInt, *m_PosMaxInt, m_pDibReal, m_pDib);

	m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW);
}

void CContrastRGBDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
	
	//Davide
	m_bRedraw = TRUE;
}

void CContrastRGBDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	PlotGraphics();
}

void CContrastRGBDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	int		Min, Max, OldPos, NewPos;
	BOOL	bContrast = FALSE;

	pScrollBar->GetScrollRange(&Min, &Max);
    OldPos = pScrollBar->GetScrollPos();

	switch (nSBCode)
	{
		case SB_LEFT :
			NewPos = max(Min, OldPos - 1);
			break;

		case SB_RIGHT :
			NewPos = min(Max, OldPos + 1);
			break;

		case SB_LINELEFT :
			NewPos = max(Min, OldPos - 1);
			break;

		case SB_LINERIGHT :
			NewPos = min(Max, OldPos + 1);
			break;

		case SB_PAGELEFT :
			NewPos = max(Min, OldPos - 10);
			break;

		case SB_PAGERIGHT :
			NewPos = min(Max, OldPos + 10);
			break;

		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			NewPos = nPos;
			break;
		
		default:
			NewPos = OldPos;
	}

	if (pScrollBar == &m_ctrlDark)
	{
		if (NewPos > *m_PosMaxInt)
			NewPos = *m_PosMaxInt;

		*m_PosMinInt = NewPos;
		m_ctrlDark.SetScrollPos(*m_PosMinInt);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		pScrollBar->SetScrollPos(NewPos);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		CRect rect;
		m_ctrLargeFrameIntensity.GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect -= CPoint(5, 5);
		InvalidateRect(rect, FALSE);
		m_bRedraw = FALSE;	
	}

	if (pScrollBar == &m_ctrlLigth)
	{
		if (NewPos < *m_PosMinInt)
			NewPos = *m_PosMinInt;

		*m_PosMaxInt = NewPos;
		m_ctrlLigth.SetScrollPos(*m_PosMaxInt);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		pScrollBar->SetScrollPos(NewPos);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		CRect rect;
		m_ctrLargeFrameIntensity.GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect -= CPoint(5, 5);
		InvalidateRect(rect, FALSE);
		m_bRedraw = FALSE;	
	}
		
	if (pScrollBar == &m_ctrlRDark)
	{
		if (NewPos > *m_PosMaxR)
			NewPos = *m_PosMaxR;

		*m_PosMinR = NewPos;
		m_ctrlRDark.SetScrollPos(*m_PosMinR);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		pScrollBar->SetScrollPos(NewPos);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		CRect rect;
		m_ctrLargeFrameRed.GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect -= CPoint(5, 5);
		InvalidateRect(rect, FALSE);
		m_bRedraw = FALSE;	
	}

	if (pScrollBar == &m_ctrlRLigth)
	{
		if (NewPos < *m_PosMinR)
			NewPos = *m_PosMinR;

		*m_PosMaxR = NewPos;
		m_ctrlRLigth.SetScrollPos(*m_PosMaxR);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		pScrollBar->SetScrollPos(NewPos);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		CRect rect;
		m_ctrLargeFrameRed.GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect -= CPoint(5, 5);
		InvalidateRect(rect, FALSE);
		m_bRedraw = FALSE;	
	}
		
	if (pScrollBar == &m_ctrlGDark)
	{
		if (NewPos > *m_PosMaxG)
			NewPos = *m_PosMaxG;

		*m_PosMinG = NewPos;
		m_ctrlGDark.SetScrollPos(*m_PosMinG);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		pScrollBar->SetScrollPos(NewPos);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		CRect rect;
		m_ctrLargeFrameGreen.GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect -= CPoint(5, 5);
		InvalidateRect(rect, FALSE);
		m_bRedraw = FALSE;	
	}

	if (pScrollBar == &m_ctrlGLigth)
	{
		if (NewPos < *m_PosMinG)
			NewPos = *m_PosMinG;

		*m_PosMaxG = NewPos;
		m_ctrlGLigth.SetScrollPos(*m_PosMaxG);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		pScrollBar->SetScrollPos(NewPos);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		CRect rect;
		m_ctrLargeFrameGreen.GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect -= CPoint(5, 5);
		InvalidateRect(rect, FALSE);
		m_bRedraw = FALSE;	
	}
		
	if (pScrollBar == &m_ctrlBDark)
	{
		if (NewPos > *m_PosMaxB)
			NewPos = *m_PosMaxB;

		*m_PosMinB = NewPos;
		m_ctrlBDark.SetScrollPos(*m_PosMinB);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		pScrollBar->SetScrollPos(NewPos);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		CRect rect;
		m_ctrLargeFrameBlue.GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect -= CPoint(5, 5);
		InvalidateRect(rect, FALSE);
		m_bRedraw = FALSE;	
	}

	if (pScrollBar == &m_ctrlBLigth)
	{
		if (NewPos < *m_PosMinB)
			NewPos = *m_PosMinB;

		*m_PosMaxB = NewPos;
		m_ctrlBLigth.SetScrollPos(*m_PosMaxB);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		pScrollBar->SetScrollPos(NewPos);

		if (nSBCode == SB_ENDSCROLL)
			bContrast = TRUE;

		CRect rect;
		m_ctrLargeFrameBlue.GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect -= CPoint(5, 5);
		InvalidateRect(rect, FALSE);
		m_bRedraw = FALSE;	
	}

	if (bContrast)
	{
		if (m_nIsRGB == 0)
			ContrastPreviewRGB(*m_PosMinInt, *m_PosMaxInt, m_pDibReal, m_pDib);
		else
			ContrastPreviewRGB(*m_PosMinR, *m_PosMaxR, *m_PosMinG, *m_PosMaxG, *m_PosMinB, *m_PosMaxB, m_pDibReal, m_pDib);

		m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW);
	}
}

DWORD CContrastRGBDlg::GetMaxValue(int Type, int numV)
{
	STRUCT_NORM		*pData;
	STRUCT_RGB		*pRGBData;
	
	switch (Type)
	{
		case 0:
			pRGBData = m_pChartInt->m_pRGBData;  
			break;
		case 1:
			pData = m_pChartR->m_pData;  
			break;
		case 2:
			pData = m_pChartG->m_pData;  
			break;
		case 3:
			pData = m_pChartB->m_pData;  
			break;
		default:
			break;
	}
	
	DWORD 			nMax1	   = 1; // Primo massimo
	DWORD 			nMax2	   = 1; // Secondo massimo
	DWORD           nVal;
	DWORD           nIndexMax1 = 1;
		
	if (pData)
	{
		if (Type == 0)
		{
			for(int i = 0; i < numV; i++)
			{
				nVal = pRGBData[i].i;
				if (nMax1 < nVal)
				{
					nMax1 = nVal;
				}
				else
				{
					if ((nMax2 < nVal) && (nMax2 < nMax1)) 
						nMax2 = nVal;
				}
			}
		}
		else
		{
			for(int i = 0; i < numV; i++)
			{
				nVal = pData[i].value;
				if (nMax1 < nVal)
				{
					nMax1 = nVal;
				}
				else
				{
					if ((nMax2 < nVal) && (nMax2 < nMax1)) 
						nMax2 = nVal;
				}
			}
		}
	}
	
	float fUpVis = float(0.2);
	DWORD nMaxVis = DWORD((1 + fUpVis) * nMax2);
	if (Type == 0)
	{
		for(int i = 0; i < numV; i++)
		{
			if (pRGBData[i].i > nMaxVis)
			{
				pRGBData[i].i = nMaxVis;
			}
		}
	}
	else
	{
		for(int i = 0; i < numV; i++)
		{
			if (pData[i].value > nMaxVis)
			{
				pData[i].value = nMaxVis;
			}
		}
	}

	return nMaxVis ;
}

void CContrastRGBDlg::GetDataFromImage()
{
	DWORD*	pnData;
	int		row, col, MaxX, MaxY;     
	BYTE	colorR, colorG, colorB;
	int		color;
	double  colorTmp;
	
	if (!m_pChartR->ResetData(256) || !m_pChartG->ResetData(256) || !m_pChartB->ResetData(256) || !m_pChartInt->ResetData(256))
		return;

	if (m_pDib && m_pDib->IsValidDib())
	{
		MaxX = (int)m_pDib->Width();
		MaxY = (int)m_pDib->Height();
		
		for(row = 0; row < MaxY; row++)
		{
			BYTE* offset = (BYTE*)m_pDib->m_pVetY[row];

			for(col = 0; col < MaxX; col++)
			{   
				colorB = *offset++;
				colorG = *offset++;
				colorR = *offset++;

				colorTmp = ((double)colorR * 0.212671) + ((double)colorG * 0.715160) + ((double)colorR * 0.072169);
				color = (int)colorTmp;
				if (color < 0)
					color = 0;
				if (color > 255)
					color = 255;

				pnData = &(m_pChartR->m_pData + colorR)->value;
				*pnData = *pnData + 1;
				pnData = &(m_pChartG->m_pData + colorG)->value;
				*pnData = *pnData + 1;
				pnData = &(m_pChartB->m_pData + colorB)->value;
				*pnData = *pnData + 1;

				pnData = &(m_pChartInt->m_pRGBData + color)->i;
				*pnData = *pnData + 1;
				pnData = &(m_pChartInt->m_pRGBData + colorR)->r;
				*pnData = *pnData + 1;
				pnData = &(m_pChartInt->m_pRGBData + colorG)->g;
				*pnData = *pnData + 1;
				pnData = &(m_pChartInt->m_pRGBData + colorB)->b;
				*pnData = *pnData + 1;
			}
		}
	}
}

void CContrastRGBDlg::PlotGraphics()
{
	CClientDC dc(this);
	BOOL bIsIntensity = (m_nIsRGB == 0);

	m_pChartInt->PlotLineChart	(&dc, TRUE, !bIsIntensity,  m_bRedraw, TRUE);
	m_pChartR->PlotLineChart	(&dc, TRUE, bIsIntensity,  m_bRedraw, TRUE);
	m_pChartG->PlotLineChart	(&dc, TRUE, bIsIntensity,  m_bRedraw, TRUE);
	m_pChartB->PlotLineChart	(&dc, TRUE, bIsIntensity,  m_bRedraw, TRUE);

	if (bIsIntensity == TRUE)
	{
		m_pChartInt->PlotEnable(&dc, TRUE);   
		m_pChartR->PlotDisable(&dc, TRUE);   
		m_pChartG->PlotDisable(&dc, TRUE);   
		m_pChartB->PlotDisable(&dc, TRUE);   
	}
	else
	{
		m_pChartInt->PlotDisable(&dc, TRUE);   
		m_pChartR->PlotEnable(&dc, TRUE);   
		m_pChartG->PlotEnable(&dc, TRUE);   
		m_pChartB->PlotEnable(&dc, TRUE);   
	}

	m_ctrlDark.ShowWindow(bIsIntensity);
	m_ctrlLigth.ShowWindow(bIsIntensity);

	m_ctrlRDark.ShowWindow(!bIsIntensity);
	m_ctrlRLigth.ShowWindow(!bIsIntensity);

	m_ctrlGDark.ShowWindow(!bIsIntensity);
	m_ctrlGLigth.ShowWindow(!bIsIntensity);

	m_ctrlBDark.ShowWindow(!bIsIntensity);
	m_ctrlBLigth.ShowWindow(!bIsIntensity);

	m_bRedraw = TRUE;
}