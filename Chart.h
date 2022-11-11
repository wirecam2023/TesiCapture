#ifndef _CHART_H_
	#define _CHART_H_

#define MAX_EXT_X		256
#define MAX_EXT_Y		256

#define LINEMAX			0
#define LINEMIN			1
#define LINEMAX_NONE	2
#define LINEMIN_NONE	3    
#define NO_LINE			4    

#define HORZ_HISTOGRAM	1
#define LINE_XY			2
#define POINT_XY		3
#define LINE_RGB_XY		4
#define LINE_XY_RGB		5

#define RED			0
#define GREEN		1
#define BLUE		2
#define YELLOW		3
#define MAGENTA		4
#define CYAN		5
#define BLACK		6
#define WHITE		7
#define GRAY		8
#define BROWN		9
#define PURPLE		10
#define AQUA		11
#define GRAY_BK		12

typedef struct RGBStruct
{   
	DWORD 	i;
	DWORD 	r;
	DWORD 	g;
	DWORD 	b;
	DWORD	qnt;
} STRUCT_RGB;

typedef struct NORMALStruct
{   
	DWORD 	value;
	DWORD	qnt;
} STRUCT_NORM;

class CChart : public CObject
{
	DECLARE_DYNCREATE(CChart)

public:

	CChart(int typechart = HORZ_HISTOGRAM);
	virtual ~CChart (void);

	int				m_PosMin;
	int				m_PosMax;
	int				m_nMaxCoordinate; 
    int				m_nMaxAscisse;
	int				m_nVertdiv;
	int				m_nHorzdiv; 
	STRUCT_NORM*	m_pData;
	STRUCT_RGB*		m_pRGBData;
	
	static COLORREF colorTable[16];
	static int MCD (int Valx, int Valy);

	BOOL	ResetData(int DimensionToCreate);

	void	ReleaseContents();

	void	PlotLineChart(CDC* pDC, BOOL bPlotUnderText, BOOL bDisabled, BOOL repaint, BOOL bPlotMinMax);
	void	PlotEnable(CDC* pDC, BOOL traceText);
	void	PlotDisable(CDC* pDC, BOOL traceText);
	void	InitializeRGBChart(BOOL bChart, BOOL bRed, BOOL bGreen, BOOL bBlue);
	void	InitializeColorChart(int ColChart, int ColLine);
	void	InitializeHChart(BOOL bValidData, int MaxX, int DivH, int GridH, float MinValueH, DWORD MaxValueH);
	void	InitializeVChart(BOOL bValidData, int MaxY, int DivV, int GridV, DWORD MaxValueV);
	void	InitializeHDiv(int DivH);
	void	InitializeMaxVValue(DWORD MaxValueV);

	void	SetDimensionFrame (CWnd* pParent, CWnd* pFrame);
    void	SetLabelChart(CString strBlack, CString strWhite);

	inline	CSize 	GetGraphDimension() {return CSize(m_nMaxCoordinate, m_nMaxAscisse);}
	inline	CPoint	GetOrigin() {return m_ptOrigin;}

private:

	CPoint		m_ptOrigin;
	int			m_nHeightChar;
    DWORD		m_nMaxChartValueX;
    DWORD		m_nMaxChartValueY;
	float		m_nMinChartValueX;
	int			m_nVertLine;
	int			m_nHorzLine; 
	BOOL		m_bFirstTime;
	int			m_OldMin;
	int			m_OldMax;
	COLORREF	m_OldLineMax[MAX_EXT_Y];
	COLORREF	m_OldLineMin[MAX_EXT_Y];
	CRect		m_RectDimChart;
	int			m_ColChart;
	int			m_ColLine;    
	CString		m_strMin;
	CString		m_strMax;
    BOOL		m_bStarting; 
    
    int			m_nTypeChart;
    BOOL		m_bChartValid;

    BOOL		m_bTraceI;
    BOOL		m_bTraceR;
    BOOL		m_bTraceG;
    BOOL		m_bTraceB;
	
	int		GetChartMetrics(CDC* pDC, int nHDiv, int nVDiv,	float& PixelsPerTickH, float& PixelsPerTickV);
	void	PlotCaptions(CDC* pDC);
	void	PlotAxes(CDC* pDC);
	void	PlotMaxMinLevel(CDC* pDC, BOOL traceText);
	void	LineNewLevel (int MaxOrMin, CDC* pDC, CPoint ptStart);
	void	LineOldLevel (int MaxOrMin, CDC* pDC, CPoint ptStart);
	void	PlotEnableDisable(CDC* pDC, CString strText);
};

#endif /* _CHART_H_ */