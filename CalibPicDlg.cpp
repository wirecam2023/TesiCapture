#include "stdafx.h"
#include "Endox.h"
#include "CalibPicDlg.h"

#include <math.h>

#include "EsamiView.h"
#include "GetCalibDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCalibPicDlg::CCalibPicDlg(CWnd* pParent, CEsamiView* pEsamiView, CString sBitmapName)
	: CDialog(CCalibPicDlg::IDD, pParent)
{
	m_pEsamiView = pEsamiView;

	m_bCalibrating = FALSE;

	m_lfRappComp = 1;

	m_nImageX = 0;
	m_nImageY = 0;

	m_ptFirst = CPoint(0,0);
	m_ptLast = CPoint(0,0);

	// --- //

	m_strBitmapName = sBitmapName;
	m_strUser = "";
	m_strScreen = "";
}                             

CCalibPicDlg::~CCalibPicDlg()
{
	if (m_dib.IsValidDib())
	{
		m_dib.ReleaseContents();
		m_dib.Detach();
	}
}

BEGIN_MESSAGE_MAP(CCalibPicDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CCalibPicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CCalibPicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();   

	BOOL bOk = FALSE;
	HBITMAP hBit;
	if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(m_strBitmapName, &hBit) > 0)
	{
		if (hBit != INVALID_HANDLE_VALUE)
		{
			bOk = m_dib.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);

			// dimensione della bitmap //
			m_nImageX = m_dib.Width();
			m_nImageY = m_dib.Height();
		}

		DeleteObject(hBit);
	}

	if (!bOk)
	{
		m_dib.ReleaseContents();
		m_dib.Detach();
		EndDialog(IDCANCEL);
	}
	else
	{
		ResizeForImage();
		theApp.LocalizeDialog(this, CCalibPicDlg::IDD, "CalibPicDlg");
	}

	return TRUE; 
} 

void CCalibPicDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);

	//
	m_bCalibrating = TRUE;

	//
	m_ptFirst = point;
	m_ptLast = point; 
}

void CCalibPicDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);

	//
	if (m_bCalibrating)
	{
		m_bCalibrating = FALSE;

		CClientDC dc(this);   
		
		// cancello la riga precedente //
		PaintLine(&dc, m_ptFirst, m_ptLast);

		//
		float fValue = GetDist(m_ptFirst, point) * (float)m_lfRappComp;

		m_strScreen = "1";
		m_strUser   = "1"; 

		CGetCalibDlg dlg (this);
		dlg.m_scrMis = fValue;
		dlg.m_userMis = fValue;
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_userMis == 0.0)
				dlg.m_userMis = 1.0; 

			if (dlg.m_scrMis == 0.0)
				dlg.m_scrMis = 1.0; 
				
			m_strUser.Format("%.2f", dlg.m_userMis);
			m_strScreen.Format("%.2f", dlg.m_scrMis);
		
			PostMessage(WM_COMMAND, IDOK);
		}

		EndDialog(IDOK);
	}
}

void CCalibPicDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags, point);

	//
	if (m_bCalibrating)
	{
		CClientDC dc(this); 

		// cancello la riga precedente //
		PaintLine(&dc, m_ptFirst, m_ptLast);

		// disegno la riga attuale //
		PaintLine(&dc, m_ptFirst, point);

		// aggiorno la posizione del punto precedente //
		m_ptLast = point;	              
	}
}

void CCalibPicDlg::OnPaint()
{
	CPaintDC dc(this);

	CRect rectPaint(0, 0, m_nImageX, m_nImageY);
	if (!m_dib.IsValidDib())
	{
		// se la dib non è valida svuoto l'immagine //

		CBrush brushNull;
		brushNull.CreateSolidBrush(RGB(0, 0, 0));
		dc.FillRect(rectPaint, &brushNull);
		brushNull.DeleteObject();
	}
	else
	{
		// disegno la dib //

		m_dib.PaintDIB(&dc, rectPaint);
	}
}

void CCalibPicDlg::PaintLine(CDC* pDC, CPoint point1, CPoint point2)
{
	int x1 = point1.x;
	int x2 = point2.x;
	int y1 = point1.y;
	int y2 = point2.y;

    int  dx, dy;        
    int  e;             
    int a;                  
    int q;                  

	HDC hdc = NULL;
	if (pDC)
		hdc = pDC->GetSafeHdc();
	
	CPoint  	point;
	BOOL		bReverse = FALSE;   

	dx = x2 - x1;
    dy = y2 - y1;
    a = 1;

    /* draw all lines from bottom to top */
    if ((dy=y2-y1)<0) 
    {
		e=x1; x1=x2; x2=e;
		e=y1; y1=y2; y2=e;
		dy = -dy;
		bReverse = TRUE;
    }

    if ((dx=x2-x1) < 0) 
    {
		dx = -dx;
		a = -1;
    }

    if (dx >= dy)                  /* |slope| <= 1 */
    {
        dy <<= 1;
        q = dx << 1;
        e = dy - dx + 1;
        while (dx-- >= 0) 
        {
        	point.x = x1; 
        	point.y = y1;
        	
        	if (hdc)
            	PaintPixel(hdc, point);

			if (e>0) 
            {
                y1++;
                e -= q;
            }
            e += dy;
            x1 += a;        /* always move in x */
        }
    }
    else                            /* |slope| > 1 */
    {
        dx <<= 1;
        q = dy<<1;
        e = dx - dy;
        while (dy-- >= 0) 
        {
            point.x = x1; 
            point.y = y1;
            
            if (hdc)
            	PaintPixel(hdc, point);

			if (e>0) 
            {
                x1 += a;
                e -= q;
            }
            e += dx;
            y1++;           /* always move in y */
        }
    }
}

void CCalibPicDlg::PaintPixel(HDC hdc, CPoint point)
{
	COLORREF OldColor;
	
	OldColor = GetPixel(hdc, point.x, point.y);
	SetPixel(hdc, point.x, point.y, (~OldColor) & 0x00ffffff); 
}       

float CCalibPicDlg::GetDist(CPoint pt1, CPoint pt2)
{
	return sqrt(pow((float)(pt1.x - pt2.x), (int)2) + pow((float)(pt1.y - pt2.y), (int)2));
}

void CCalibPicDlg::ResizeDibWindow()
{
	int iHeight;
	int iWidth;
	int iWndSizeX,iWndSizeY;
	int	iScreenSizeX;
	int	iScreenSizeY;
	CRect rect;
	CDC* pDC;
	
	// Screen size
	pDC = GetDC();
  	iScreenSizeX = (unsigned)pDC->GetDeviceCaps(HORZRES);
  	iScreenSizeY = (unsigned)pDC->GetDeviceCaps(VERTRES);
	ReleaseDC(pDC);
	
	// Bitmap sizes
	iWidth  = m_dib.Width();
	iHeight = m_dib.Height();

	// Window sizes to paint entire bitmap
    iWndSizeX = iWidth + (GetSystemMetrics(SM_CXDLGFRAME) * 2);
    iWndSizeY = iHeight + (GetSystemMetrics(SM_CYDLGFRAME) * 2) + GetSystemMetrics(SM_CYCAPTION);

    if (iWndSizeX > iScreenSizeX)
        iWndSizeX = m_nImageX + (GetSystemMetrics(SM_CXDLGFRAME) * 2);

    if (iWndSizeY > iScreenSizeY)
        iWndSizeY = m_nImageY + (GetSystemMetrics(SM_CYDLGFRAME) * 2) + GetSystemMetrics(SM_CYCAPTION);
	
	// Actual window sizes
	GetWindowRect(&rect);

	// Modify sizes
    MoveWindow(rect.left, 
			   rect.top,
			   iWndSizeX,
			   iWndSizeY,
			   TRUE); 
	CenterWindow();
	InvalidateRect(NULL, FALSE);	
}

void CCalibPicDlg::ResizeForImage()
{
	CDC* pDC;
	int iWidth;
	int iHeight;
	int	iScreenSizeX;
	int	iScreenSizeY;
	int iClientFullSizeX;
	int iClientFullSizeY; 
		
	// Bitmap sizes
	iWidth  = m_dib.Width();
	iHeight = m_dib.Height();

	pDC = GetDC();
   	iScreenSizeX = (unsigned)pDC->GetDeviceCaps(HORZRES);
   	iScreenSizeY = (unsigned)pDC->GetDeviceCaps(VERTRES);
    iClientFullSizeX = iScreenSizeX - (GetSystemMetrics(SM_CXDLGFRAME) *2);
    iClientFullSizeY = iScreenSizeY - (GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION));
	ReleaseDC(pDC);
                
	if (iWidth > iClientFullSizeX || iHeight > iClientFullSizeY)
	{
  		m_nImageY = (int)(((float)iHeight * (float)iClientFullSizeX) / (float)iWidth);
		if (m_nImageY > iClientFullSizeY)
  		{
			m_nImageX = (int)(((float)iWidth * (float)iClientFullSizeY) / (float)iHeight);
			m_nImageY = iClientFullSizeY;
		}
		else
			m_nImageX = iClientFullSizeX;   
	}
	else
	{
		m_nImageX = iWidth;
   		m_nImageY = iHeight;
	}

	double rappCompX = (double) iWidth / (double) m_nImageX;
	double rappCompY = (double) iHeight / (double) m_nImageY;

	m_lfRappComp = (rappCompX + rappCompY) / 2;

	ResizeDibWindow();	
}

CString CCalibPicDlg::GetScreen()
{
	return m_strScreen;
}

CString CCalibPicDlg::GetUser()
{
	return m_strUser;
}