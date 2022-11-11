#include "stdafx.h"
#include "Endox.h"
#include "ContrastDlg.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CContrastDlg::CContrastDlg(CWnd* pParent, CDib* pDib, CDib* pRoi)
	: CDialog(CContrastDlg::IDD, pParent)
{
	m_pView		= pParent;

	m_pDibReal	= NULL;
	m_pOldPal	= NULL;
	m_pLogPal	= NULL;
	m_pDib		= pDib;
	m_pDibRoi	= pRoi;
	
	m_pChart	= new CChart(HORZ_HISTOGRAM);
	m_pDarkLev	= &m_pChart->m_PosMin; //g_nBlackLev;
	m_pLigthLev = &m_pChart->m_PosMax; //g_nWhiteLev;

	m_bRedraw	= FALSE;	
}

CContrastDlg::~CContrastDlg()
{	
	if (m_pDibReal)
	{
		m_pDibReal->ReleaseContents();
		delete m_pDibReal;
		m_pDibReal = NULL;
	}

	if (m_pLogPal)
	{
		GlobalFreePtr(m_pLogPal);
		m_pLogPal = NULL;
	}

	if (m_pOldPal)
	{
		GlobalFreePtr(m_pOldPal);
		m_pOldPal = NULL;
	}

	if (m_pChart)
	{
		m_pChart->ReleaseContents();
		delete m_pChart;
	}
}

void CContrastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BLACK, m_ctrlDark);
	DDX_Control(pDX, IDC_WHITE, m_ctrlLigth);
	DDX_Control(pDX, IDC_CHART_FRAME, m_ctrChart);
	DDX_Control(pDX, IDC_LARGE_FRAME, m_ctrFrame);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
}


BEGIN_MESSAGE_MAP(CContrastDlg, CDialog)
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_WM_MOVE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContrastDlg message handlers

BOOL CContrastDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pLogPal = m_pDib->CreateLogPalette();
	m_pOldPal = m_pDib->CreateLogPalette();

	m_ctrlDark. SetScrollRange (0, 255);
	m_ctrlLigth.SetScrollRange (0, 255);
	m_ctrlDark. SetScrollPos (g_nBlackLev);
	m_ctrlLigth.SetScrollPos (g_nWhiteLev);

	SetDlgItemInt(IDC_NUM_DARK,	 g_nBlackLev, FALSE);
	SetDlgItemInt(IDC_NUM_LIGTH, g_nWhiteLev, FALSE);

	*m_pDarkLev	 = m_ctrlDark.GetScrollPos();
	*m_pLigthLev = m_ctrlLigth.GetScrollPos();

	GetDataFromImage();

    m_pChart->SetDimensionFrame(this, &m_ctrChart);
    m_pChart->SetLabelChart("Min:","Max:");
    m_pChart->InitializeColorChart(BLACK, YELLOW);
    m_pChart->InitializeHChart(TRUE, 256, 256, 4, (float)0.0, 255);
    m_pChart->InitializeVChart(TRUE, 128,   5, 4, GetMaxValue(256));

	if (m_pDib->IsRGB())
		ContrastPreviewRGB(*m_pDarkLev, *m_pLigthLev, m_pDibReal, m_pDib);
	else
		ContrastPreview(*m_pDarkLev, *m_pLigthLev, m_pDib, m_pOldPal, m_pLogPal);

	m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW);
	theApp.LocalizeDialog(this, CContrastDlg::IDD, "ContrastDlg");

	return TRUE;
}

void CContrastDlg::OnOK() 
{
	if (m_pOldPal)
		m_pDib->CopydaPalette(m_pOldPal);

	if (m_pDibReal)
		*m_pDib = *m_pDibReal;

	UpdateData(TRUE);

	g_nBlackLev = *m_pDarkLev;
	g_nWhiteLev = *m_pLigthLev;

	CDialog::OnOK();

}

void CContrastDlg::OnCancel() 
{
	if (m_pOldPal)
		m_pDib->CopydaPalette(m_pOldPal);

	if (m_pDibReal)
		*m_pDib = *m_pDibReal;

	m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW);
	
	CDialog::OnCancel();
}

void CContrastDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
	
	m_bRedraw = TRUE;	
}

void CContrastDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	m_pChart->PlotLineChart	(&dc, TRUE, FALSE, m_bRedraw, TRUE);

	m_bRedraw = TRUE;
}

void CContrastDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

    //// MOVIMENTO EFFETTIVO
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
		if (NewPos <= *m_pLigthLev)
		{
			*m_pDarkLev = NewPos;
			
			pScrollBar->SetScrollPos(NewPos);
			SetDlgItemInt(IDC_NUM_DARK, NewPos, FALSE);

			if (nSBCode == SB_ENDSCROLL)
				bContrast = TRUE;
		}
		else
		{
			m_ctrlDark.SetScrollPos(*m_pDarkLev);
		}
	}

	if (pScrollBar == &m_ctrlLigth)
	{
		if (NewPos >= *m_pDarkLev)
		{
			*m_pLigthLev = NewPos;

			pScrollBar->SetScrollPos(NewPos);
			SetDlgItemInt(IDC_NUM_LIGTH, NewPos, FALSE);

			if (nSBCode == SB_ENDSCROLL)
				bContrast = TRUE;
		}
		else
		{
			m_ctrlLigth.SetScrollPos(*m_pLigthLev);
		}
	}

	//ridisegno del chart
	CRect rect;
	m_ctrFrame.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect -= CPoint(5, 5);
	InvalidateRect(rect, FALSE);
	m_bRedraw = FALSE;	
	///////////////////

	if (bContrast)
	{
		if (m_pDib->IsRGB())
			ContrastPreviewRGB(*m_pDarkLev, *m_pLigthLev, m_pDibReal, m_pDib);
		else
			ContrastPreview(*m_pDarkLev, *m_pLigthLev, m_pDib, m_pOldPal, m_pLogPal);

		m_pView->RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW);
	}
}

DWORD CContrastDlg::GetMaxValue(int numV)
{
	DWORD 			nMax	= 1;
	STRUCT_NORM*	pData	= m_pChart->m_pData;
	
	if (pData)
		for(int i=0; i<numV; i++)
			if (nMax < (*(pData+i)).value)
				nMax = (*(pData+i)).value;		

	return nMax ;
}

void CContrastDlg::GetDataFromImage()
{
	DWORD*	pnData;
	int		row, col, MaxX, MaxY;     
	int		color;
	
	if (!m_pChart->ResetData(256))
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
				color = *offset++;

				pnData = &(m_pChart->m_pData + color)->value;
				*pnData = *pnData + 1;
			}
		}
	}
}