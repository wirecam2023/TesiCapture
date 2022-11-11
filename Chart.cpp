#include "stdafx.h"
#include "Endox.h"

#include <windowsx.h>
#include <math.h> 

#include "chart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CChart, CObject)

COLORREF CChart::colorTable[] =
{
	RGB(255,   0,   0),     // Red
	RGB(  0, 255,   0),     // Green
	RGB(  0,   0, 255),     // Blue
	RGB(255, 255,   0),     // Yellow
	RGB(255,   0, 255),     // Magenta
	RGB(  0, 255, 255),     // Cyan
	RGB(  0,   0,   0),     // Black
	RGB(255, 255, 255),     // White
	RGB(128, 128, 128),     // Grey
	RGB(128, 128,   0),     // Brown
	RGB(128,   0, 128),     // Purple
	RGB(  0, 128, 128),     // Aqua
	RGB(192, 192, 192),     // Gray (Sfondo finestra)
	RGB(  0,   0,   0),     // libero
	RGB(  0,   0,   0),     // libero
	RGB(  0,   0,   0)      // libero
};

CChart::CChart(int typeChart)
{
	m_PosMin = -1;
	m_PosMax = -1;
	m_OldMin = -1;
	m_OldMax = -1;    

	m_nMaxCoordinate = 0; // = 256;
	m_nMaxAscisse	 = 0; // = 127;
	m_nVertdiv		 = 0; // = 8;
	m_nHorzdiv		 = 0; // = 256;
	m_nVertLine		 = 0; // = 8;
	m_nHorzLine		 = 0; // = 8;
	m_ColChart		 = BLACK;
	m_ColLine		 = RED;
	
	m_bFirstTime		= TRUE;
	
	m_ptOrigin			= CPoint(0,0);
	m_nHeightChar		= 0;
	m_nMaxChartValueY	= 0;
	m_nMaxChartValueX	= 0;
	m_RectDimChart		= CRect(0,0,0,0);
	
	m_strMin = "";
	m_strMax = "";

    m_bStarting = TRUE;

	for(int i=0; i<MAX_EXT_Y; i++)
	{
		m_OldLineMin[i] = (COLORREF)0;
		m_OldLineMax[i] = (COLORREF)0;
	}  

	m_pData			= NULL;
	m_pRGBData		= NULL;
   	m_nTypeChart	= typeChart;
   	m_bChartValid	= FALSE;
   	
	m_bTraceI = FALSE;
	m_bTraceR = TRUE;
	m_bTraceG = TRUE;
	m_bTraceB = TRUE;
}

CChart::~CChart (void)
{
	if (m_pData)
	{
		GlobalFreePtr(m_pData);
		m_pData = NULL;
	}

	if (m_pRGBData)
	{
		GlobalFreePtr(m_pRGBData);
		m_pRGBData = NULL;
	}
}

void CChart::ReleaseContents ()
{
	if (m_pData)
	{
		GlobalFreePtr(m_pData);
		m_pData = NULL;
	}

	if (m_pRGBData)
	{
		GlobalFreePtr(m_pRGBData);
		m_pRGBData = NULL;
	}
}

int CChart::MCD (int Valx, int Valy)
{
	int x = max(Valx, Valy);
	int y = min(Valx, Valy);
	do {
		int resto = x % y;
		x = y;
		y = resto;
	} while (y!=0);
	return x;	
}

void CChart::InitializeRGBChart(BOOL bChart, BOOL bRed, BOOL bGreen, BOOL bBlue)
{
	m_bTraceI = bChart;
	m_bTraceR = bRed;
	m_bTraceG = bGreen;
	m_bTraceB = bBlue;
}

void CChart::InitializeColorChart(int ColChart, int ColLine)
{
	m_ColChart 		 = ColChart;
	m_ColLine  		 = ColLine;
}

void CChart::InitializeVChart(BOOL bValidData, int MaxY, int DivV, int GridV, DWORD MaxValueV)
{
	m_bChartValid = bValidData;
		
	MaxY = min (MaxY, MAX_EXT_Y);
	DivV = min (DivV, MaxY);
	GridV = min (GridV, MAX_EXT_Y/20);
	
	if ((DWORD)DivV > MaxValueV)
		DivV = (int)MaxValueV;
	if ((DWORD)GridV > MaxValueV)
		GridV = (int)MaxValueV;
		
	if (MaxValueV < 100)
		GridV = MCD(GridV, DivV);		
    
	m_nMaxAscisse    = MaxY;
	m_nVertdiv       = DivV;
	m_nVertLine      = GridV;
	m_nMaxChartValueY = MaxValueV;
}

void CChart::InitializeHChart(BOOL bValidData, int MaxX, int DivH, int GridH, float MinValueH, DWORD MaxValueH)
{
	m_bChartValid = bValidData;
		
	MaxX = min (MaxX, MAX_EXT_X);
	DivH = min (DivH, MaxX);
	GridH = min (GridH, MAX_EXT_X/20);

	if ((DWORD)DivH > MaxValueH)
		DivH = (int)MaxValueH;
	if ((DWORD)GridH > MaxValueH)
		GridH = (int)MaxValueH;
    
	m_nMaxCoordinate  = MaxX;
	m_nHorzdiv        = DivH;
	m_nHorzLine       = GridH;
	m_nMaxChartValueX = MaxValueH;
	m_nMinChartValueX = MinValueH;
	
	m_OldMin = -1;
	m_OldMax = -1;    
}

void CChart::InitializeHDiv(int DivH)
{
	m_nHorzdiv       = DivH;

	m_OldMin = -1;
	m_OldMax = -1;    
}

void CChart::InitializeMaxVValue(DWORD MaxValueV)
{
	m_nVertLine = max (m_nVertLine, MAX_EXT_Y/20);
	m_nVertdiv = max (m_nVertdiv, m_nMaxAscisse);

	if ((DWORD)m_nVertdiv > MaxValueV)
		m_nVertdiv = (int)MaxValueV;

	if ((DWORD)m_nVertLine > MaxValueV)
		m_nVertLine = (int)MaxValueV;

	if (MaxValueV < 100)
		m_nVertLine = MCD(m_nVertLine, m_nVertdiv);		

	m_nMaxChartValueY = MaxValueV;
}

void CChart::SetDimensionFrame (CWnd* pParent, CWnd* pFrame)
{
	pFrame->GetWindowRect(&m_RectDimChart);
	
	pParent->ScreenToClient(&m_RectDimChart);
    
	m_RectDimChart -= CPoint(5, 5);
}

void CChart::SetLabelChart(CString strBlack, CString strWhite)
{
	m_strMin = strBlack;
	m_strMax = strWhite;
}

int CChart::GetChartMetrics(CDC* pDC, int nHDiv, int nVDiv,	float& PixelsPerTickH, float& PixelsPerTickV)
{
	CSize sizeText = pDC->GetTextExtent("0", 1);

	PixelsPerTickH = (float)m_nMaxCoordinate / (float)nHDiv;
	PixelsPerTickV = (float)m_nMaxAscisse    / (float)nVDiv;
    
	m_ptOrigin.x = m_RectDimChart.left + 5 * sizeText.cx;
	m_ptOrigin.y = m_RectDimChart.bottom - sizeText.cy;
	
	return sizeText.cy;
}

void CChart::PlotCaptions(CDC* pDC)
{
	char	buf[80];
	float	jumpH,jumpV;
	float	label;
	float	intervalloH;	
	float	intervalloV;	
	float   i;
	
	jumpH = (float)m_nMaxCoordinate / (float)m_nHorzLine;   // griglia
	jumpV = (float)m_nMaxAscisse    / (float)m_nVertLine;   // griglia
	intervalloH = (float)(m_nMaxChartValueX - m_nMinChartValueX + 1) / (float)(m_nHorzLine);
	intervalloV = (float)(m_nMaxChartValueY) / (float)(m_nVertLine);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(colorTable[BLACK]);

	pDC->SetTextAlign(TA_CENTER);

    label = (float) m_nMinChartValueX;
    i = (float)0.0;
    while ((int)i < (m_nMaxCoordinate-1))
    {
		pDC->MoveTo(m_ptOrigin.x + (int)i, m_ptOrigin.y);
		pDC->LineTo(m_ptOrigin.x + (int)i, m_ptOrigin.y - m_nMaxAscisse - 1);
		DWORD lab = (DWORD)(ceil(label));
		if (lab>9999)
			wsprintf(buf, "%luk", lab/1000);
		else
			wsprintf(buf, "%lu", lab);
		pDC->TextOut(m_ptOrigin.x + (int)i, m_ptOrigin.y + m_nHeightChar/4 - 1, buf);
		label += intervalloH;                            
		i += jumpH;
	}

	pDC->SetTextAlign(TA_RIGHT);
	pDC->MoveTo(m_ptOrigin.x + m_nMaxCoordinate, m_ptOrigin.y);
	pDC->LineTo(m_ptOrigin.x + m_nMaxCoordinate, m_ptOrigin.y - m_nMaxAscisse - 1);
	wsprintf(buf, "%lu", m_nMaxChartValueX);
	pDC->TextOut(m_ptOrigin.x + m_nMaxCoordinate, m_ptOrigin.y + m_nHeightChar/4 - 1, buf);

	//Davide - In asse Y scrivo tutti i valori abbreviati se il valore max è > di 10000
	BOOL bPrintThousand = m_nMaxChartValueY < 10000;
    label = (float)0.0;
    i = (float)0.0;
	
	pDC->SetTextAlign(TA_RIGHT);

	while ((int)i < (m_nMaxAscisse - 1))
    {
		pDC->MoveTo(m_ptOrigin.x, m_ptOrigin.y - (int)i);
		pDC->LineTo(m_ptOrigin.x + m_nMaxCoordinate, m_ptOrigin.y - (int)i);
		DWORD dwLab = (DWORD)(intervalloV * label);
		
		if (bPrintThousand)
			wsprintf(buf, "%lu", dwLab);
		else
			sprintf_s(buf, "%5.1fk", (float)dwLab / (float)1000);
			//wsprintf(buf, "%luk", (float)dwLab / (float)1000);
		
		pDC->TextOut(m_ptOrigin.x-5, m_ptOrigin.y - (int)i - m_nHeightChar/2 + 1, buf);

		i += jumpV;
		label++;
	}
	
	pDC->MoveTo(m_ptOrigin.x, m_ptOrigin.y - m_nMaxAscisse);
	pDC->LineTo(m_ptOrigin.x + m_nMaxCoordinate, m_ptOrigin.y - m_nMaxAscisse);
	
	if (bPrintThousand)
		wsprintf(buf, "%lu", m_nMaxChartValueY);
	else
		sprintf_s(buf, "%5.1fk", (float)m_nMaxChartValueY / (float)1000);
		//wsprintf(buf, "%luk", (float)m_nMaxChartValueY / (float)1000);
	
	pDC->TextOut(m_ptOrigin.x-5, m_ptOrigin.y - m_nMaxAscisse - m_nHeightChar/2 + 1, buf);
}

void CChart::LineOldLevel (int MaxOrMin, CDC* pDC, CPoint ptStart)
{
	CPoint		point;
	COLORREF	OldColor = RGB(0,0,0);

	int posx = ptStart.x;
	int posy = ptStart.y;
	int y;
	
	for(y=0; y<=m_nMaxAscisse; y++)
	{
		point = CPoint(posx,posy-y);
		switch (MaxOrMin)
		{
			case LINEMIN:
				OldColor = m_OldLineMin[y];
				break;
			case LINEMAX:
				OldColor = m_OldLineMax[y];
				break;
		}	
		pDC->SetPixel(point , OldColor); 
	}
}

void CChart::LineNewLevel (int MaxOrMin, CDC* pDC, CPoint ptStart)
{
	COLORREF	OldColor;
	CPoint		point;

	int posx = ptStart.x;
	int posy = ptStart.y;
	int y;
	
	for(y=0; y<=m_nMaxAscisse; y++)
	{
		point = CPoint(posx,posy-y);
		OldColor = pDC->GetPixel(point);
		switch (MaxOrMin)
		{
			case LINEMIN:
				m_OldLineMin[y] = OldColor;
				break;
			case LINEMAX:
				m_OldLineMax[y] = OldColor;
				break;
			case LINEMIN_NONE:
				m_OldLineMin[y] = m_OldLineMax[y];
				break;
			case LINEMAX_NONE:
				m_OldLineMax[y] = m_OldLineMin[y];
				break;
		}	
		pDC->SetPixel(point , colorTable[m_ColLine]); 
	}
}       

void CChart::PlotEnable(CDC* pDC, BOOL traceText)
{
	if (traceText)
		PlotEnableDisable(pDC, "                                                          ");
	PlotMaxMinLevel(pDC, traceText);
}

void CChart::PlotDisable(CDC* pDC, BOOL traceText)
{
	if (traceText)
		PlotEnableDisable(pDC, "                          Disabled                        ");
	PlotMaxMinLevel(pDC, FALSE);
}

void CChart::PlotEnableDisable(CDC* pDC, CString strText)
{
	char	buf[80];
	CPoint	NewPoint;

	pDC->SetBkMode(OPAQUE);
	pDC->SetBkColor(::GetSysColor(COLOR_BTNFACE));
	pDC->SetTextColor(colorTable[BLACK]);
    
	pDC->SetTextAlign(TA_CENTER);
	wsprintf(buf, strText.GetBuffer(strText.GetLength()));
	pDC->TextOut(m_ptOrigin.x -1 + m_nMaxCoordinate/2, m_ptOrigin.y+m_nHeightChar*3/2, buf);
}   

void CChart::PlotMaxMinLevel(CDC* pDC, BOOL traceText)
{
	char	buf[80];
	CPoint	NewPoint;

	if (traceText)
	{
		pDC->SetBkMode(OPAQUE);
		pDC->SetBkColor(::GetSysColor(COLOR_BTNFACE));
		pDC->SetTextColor(colorTable[BLACK]);
	    
		pDC->SetTextAlign(TA_LEFT);
		wsprintf(buf, "%s %d    ", m_strMin.GetBuffer(m_strMin.GetLength()), m_PosMin);
		pDC->TextOut(m_ptOrigin.x, m_ptOrigin.y+m_nHeightChar*3/2, buf);
	
		pDC->SetTextAlign(TA_RIGHT);
		wsprintf(buf, "    %s %d", m_strMax.GetBuffer(m_strMax.GetLength()), m_PosMax);
		pDC->TextOut(m_ptOrigin.x + m_nMaxCoordinate, m_ptOrigin.y+m_nHeightChar*3/2, buf);
	}
	
    if (m_OldMin != -1 && m_OldMin != m_PosMin)
    {
		NewPoint = CPoint(m_OldMin + m_ptOrigin.x, m_ptOrigin.y);
		LineOldLevel(LINEMIN, pDC, NewPoint);
	}

    if (m_OldMax != -1 && m_OldMax != m_PosMax)
    {
		NewPoint = CPoint(m_OldMax + m_ptOrigin.x, m_ptOrigin.y);
		LineOldLevel(LINEMAX, pDC, NewPoint);
	}

	NewPoint = CPoint(m_PosMin + m_ptOrigin.x, m_ptOrigin.y);
	if ( (m_OldMin != m_PosMin && m_PosMin != m_PosMax) || m_bStarting )
	{
		LineNewLevel(LINEMIN, pDC, NewPoint);
		m_OldMin = m_PosMin;
	}
	else
		if (m_PosMin == m_PosMax)
		{
			LineNewLevel(LINEMIN_NONE, pDC, NewPoint);
			m_OldMin = m_PosMin;
		}
		else
			LineNewLevel(NO_LINE, pDC, NewPoint);

	NewPoint = CPoint(m_PosMax + m_ptOrigin.x, m_ptOrigin.y);
	if (m_OldMax != m_PosMax && m_PosMin != m_PosMax)
	{
		LineNewLevel(LINEMAX, pDC, NewPoint);
		m_OldMax = m_PosMax;
	}
	else
		if (m_PosMin == m_PosMax)
		{
			LineNewLevel(LINEMAX_NONE, pDC, NewPoint);
			m_OldMin = m_PosMin;
		}		
		else
			LineNewLevel(NO_LINE, pDC, NewPoint);

    m_bStarting = FALSE;
}

void CChart::PlotAxes(CDC* pDC)
{
	CPoint ptTmp;
	ptTmp.x = m_ptOrigin.x;
	ptTmp.y = m_ptOrigin.y + 1;

	// Draw Axes
	pDC->MoveTo(ptTmp);
	pDC->LineTo(ptTmp.x, (ptTmp.y - m_nMaxAscisse) - 1);
	pDC->MoveTo(ptTmp);
	pDC->LineTo(ptTmp.x + m_nMaxCoordinate, ptTmp.y);
}

void CChart::PlotLineChart(CDC* pDC, BOOL bPlotUnderText, BOOL bDisabled, BOOL repaint, BOOL bPlotMinMax)
{
	double	nTick;
	CSize	sizeGraph;
	float	PixelsPerTickV, PixelsPerTickH;
	CPen	penAxes;
	CPen	penChart;
	CPen	penCaption;
	CPen	penLevel;
	CPen*	pOldPen;
	float 	dato = 0; 
	int 	nVPos;
	float 	nHPos;
	int 	SizePen = 1;	
	float	vPos;
	BOOL	bFirstPoint = TRUE;
	
	if (m_bChartValid)
	{
		if (m_bFirstTime || repaint)
		{
			m_bFirstTime = FALSE;  
			m_nHeightChar = GetChartMetrics(pDC, m_nHorzdiv, m_nVertdiv, PixelsPerTickH, PixelsPerTickV);
			nTick = (float)m_nMaxAscisse / (float)m_nMaxChartValueY;
	
			penAxes.CreatePen(PS_SOLID, 2, colorTable[GRAY_BK]);    // colore degli assi
			pOldPen = pDC->SelectObject(&penAxes);
			PlotAxes(pDC);
		    
			penCaption.CreatePen(PS_SOLID, 1, colorTable[GRAY_BK]); // colore della griglia
			pDC->SelectObject(&penCaption);
			PlotCaptions(pDC);
		
			if ((m_nTypeChart == LINE_RGB_XY) || (m_nTypeChart == LINE_XY_RGB))
			{
				if (m_nTypeChart == LINE_RGB_XY)
				{
		    		if (m_pRGBData)
		    		{
						int 	nOldVPos[4], nOldHPos;
						CPen	penRed,	penGreen, penBlue, penChart;
						BOOL 	bTrace = FALSE;
						
						nOldVPos[0] = 0; // Red
						nOldVPos[1] = 0; // Green
						nOldVPos[2] = 0; // Blue      
						nOldVPos[3] = 0; // Intensity      
						
						nOldHPos = m_ptOrigin.x;
						
						nHPos = (float)m_ptOrigin.x;
				
						penRed.CreatePen(PS_SOLID, 1, colorTable[RED]);
						penGreen.CreatePen(PS_SOLID, 1, colorTable[GREEN]);
						penBlue.CreatePen(PS_SOLID, 1, colorTable[BLUE]);
						penChart.CreatePen(PS_SOLID, 1, colorTable[m_ColChart]);
						
			    		for(int nCol = 0; nCol < m_nHorzdiv; nCol++)
						{   
							for(int rgb = 0; rgb < 4; rgb++)
							{
								switch (rgb)
								{
									case 0:
										dato = (float) (*(m_pRGBData + nCol)).r;
										pDC->SelectObject(&penRed);
										bTrace = m_bTraceR;
										break;
									case 1:
										dato = (float) (*(m_pRGBData + nCol)).g;
										pDC->SelectObject(&penGreen);
										bTrace = m_bTraceG;
										break;
									case 2:
										dato = (float) (*(m_pRGBData + nCol)).b;
										pDC->SelectObject(&penBlue);
										bTrace = m_bTraceB;
										break;
									case 3:
										dato = (float) (*(m_pRGBData + nCol)).i;
										pDC->SelectObject(&penChart);
										bTrace = m_bTraceI;
										break;
								}
								
								if (bTrace)
								{
									vPos = (float)nTick * (float)dato;
									nVPos = (int)(vPos);
		
									pDC->MoveTo((int)nOldHPos, m_ptOrigin.y - nOldVPos[rgb]);
									pDC->LineTo((int)nHPos, m_ptOrigin.y - nVPos);
									
									nOldVPos[rgb] = nVPos;
								}
							}
							nOldHPos = (int)nHPos;
							nHPos += PixelsPerTickH;
						}
		    		}
				}
				else	// m_nTypeChart == LINE_XY_RGB
				{
		    		if (m_pRGBData)
		    		{
						int 	nOldVPos[4], nOldHPos;
						CPen	penRed,	penGreen, penBlue, penChart;
						BOOL 	bTrace = FALSE;
						
						nOldVPos[0] = 0; // Red
						nOldVPos[1] = 0; // Green
						nOldVPos[2] = 0; // Blue      
						nOldVPos[3] = 0; // Intensity      
						
						nOldHPos = m_ptOrigin.x;
						
						nHPos = (float)m_ptOrigin.x;
				
						penRed.CreatePen(PS_SOLID, 1, colorTable[RED]);
						penGreen.CreatePen(PS_SOLID, 1, colorTable[GREEN]);
						penBlue.CreatePen(PS_SOLID, 1, colorTable[BLUE]);
						penChart.CreatePen(PS_SOLID, 1, colorTable[m_ColChart]);
						
			    		for(int nCol = 0; nCol < m_nHorzdiv; nCol++)
						{   
							for(int rgb = 0; rgb < 4; rgb++)
							{
								switch (rgb)
								{
									case 0:
										dato = (float) (*(m_pRGBData + nCol)).r;
										pDC->SelectObject(&penRed);
										bTrace = m_bTraceR;
										break;
									case 1:
										dato = (float) (*(m_pRGBData + nCol)).g;
										pDC->SelectObject(&penGreen);
										bTrace = m_bTraceG;
										break;
									case 2:
										dato = (float) (*(m_pRGBData + nCol)).b;
										pDC->SelectObject(&penBlue);
										bTrace = m_bTraceB;
										break;
									case 3:
										dato = (float) (*(m_pRGBData + nCol)).i;
										pDC->SelectObject(&penChart);
										bTrace = m_bTraceI;
										break;
								}
								
								if (rgb == 3)
								{
									if (bTrace)
									{
										vPos = (float)nTick * (float)dato;
										nVPos = (int)(vPos);
			
										pDC->MoveTo((int)nHPos, m_ptOrigin.y);
										pDC->LineTo((int)nHPos, m_ptOrigin.y - nVPos);
										
										nOldVPos[rgb] = nVPos;
									}
								}
								else
								{
									if (bTrace)
									{
										vPos = (float)nTick * (float)dato;
										nVPos = (int)(vPos);
			
										pDC->MoveTo((int)nOldHPos, m_ptOrigin.y - nOldVPos[rgb]);
										pDC->LineTo((int)nHPos, m_ptOrigin.y - nVPos);
										
										nOldVPos[rgb] = nVPos;
									}
								}
							}
							nOldHPos = (int)nHPos;
							nHPos += PixelsPerTickH;
						}
		    		}
				}
			}
			else
			{
				penChart.CreatePen(PS_SOLID, 1, colorTable[m_ColChart]);
				pDC->SelectObject(&penChart);
		
		    	if (m_pData)
		    	{
					nHPos = (float)m_ptOrigin.x;
			
					if (PixelsPerTickH > 2.0)
						SizePen = (int)PixelsPerTickH - 1;
		
			    	for(int nCol = 0; nCol < m_nHorzdiv; nCol++)
					{   
						int i;
						double dTmp;
						
						dTmp = (nCol * (double)256.0 / m_nHorzdiv);
						dato = (float) (*(m_pData + (int)dTmp)).value;
//						dato = (float) (*(m_pData + nCol)).value;
						vPos = (float)nTick * (float)dato;
						nVPos = (int)(vPos);
					
				    	switch (m_nTypeChart)
				    	{
				    		case HORZ_HISTOGRAM:
						    	for(i = 0; i < SizePen; i++)
								{
									pDC->MoveTo((int)nHPos + i, m_ptOrigin.y);
									pDC->LineTo((int)nHPos + i, m_ptOrigin.y - nVPos);
								}
								break;
				    		case LINE_XY:
									if (bFirstPoint)
									{
										bFirstPoint = FALSE;
										pDC->MoveTo((int)nHPos, m_ptOrigin.y - nVPos);
									}
									else
										pDC->LineTo((int)nHPos, m_ptOrigin.y - nVPos);
								break;
				    		case POINT_XY:
									pDC->SetPixel((int)nHPos, m_ptOrigin.y - nVPos, colorTable[m_ColChart]);
								break;
				    		default:
								break;
				    		
				    	}
						nHPos += PixelsPerTickH;
					}
				}
			}
	
			pDC->SelectObject(pOldPen);
		}
		if (bPlotMinMax)
		{
			if (bDisabled)
				PlotDisable(pDC, bPlotUnderText);
			else
				PlotEnable(pDC, bPlotUnderText);
		}
	}
}

BOOL CChart::ResetData(int DimensionToCreate)
{
	if ((m_nTypeChart == LINE_RGB_XY) || (m_nTypeChart == LINE_XY_RGB))
	{
		if (m_pRGBData)
		{
			GlobalFreePtr(m_pRGBData);
			m_pRGBData = NULL;
		}

      	m_pRGBData = (STRUCT_RGB*)GlobalAllocPtr(GPTR, sizeof(STRUCT_RGB) * DimensionToCreate);
	
		if (!m_pRGBData)
			return FALSE;
	}
	else
	{
		if (m_pData)
		{
			GlobalFreePtr(m_pData);
			m_pData = NULL;
		}
	
      	m_pData = (STRUCT_NORM*)GlobalAllocPtr(GPTR, sizeof(STRUCT_NORM) * DimensionToCreate);
		
		if (!m_pData)
			return FALSE;
	}
	return TRUE;
}

