#include "stdafx.h"
#include "Endox.h"
#include "MaximizeDlg.h"
#include "EsamiView.h" //Gabriel BUG 6225 - Lista DO FIX
#include "MonitorScreens.h" //Gabriel BUG 6225 - Lista DO FIX
#include "Monitor.h" //Gabriel BUG 6225 - Lista DO FIX

#include "dib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Gabriel BUG 6225 - Lista DO FIX
CMaximizeDlg::CMaximizeDlg(CWnd* pParent, CDib* pDib, CEsamiView* pEsamiView, CImgListOrgani* pImgList, long lNumPage, long lPaziente, long lEsame, long lTotPage)
	: CDialog(CMaximizeDlg::IDD, pParent)
{
	m_pDib = pDib;
	//Gabriel BUG 6225 - Lista DO FIX
	m_ImgList = pImgList; 
	m_lNumPage = lNumPage;
	m_lPaziente = lPaziente;
	m_lEsame = lEsame;
	m_pEsamiView = pEsamiView;
	m_lTotPage = lTotPage;
}

void CMaximizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CMaximizeDlg::InitializeWindow()
{
    if (m_pDib && m_pDib->IsValidDib())
	{
		int		full_ysize, full_xsize;
		//Gabriel BUG 6225 - Lista DO FIX
		if (theApp.m_bAtivaListaDO && theApp.m_sConfigFormAlbumImgBtnImgOpenWhere == "MONITOR #02")
		{
			CMonitor monitorII;
			CMonitorScreens monitors;
			monitorII = monitors.GetMonitor(1);	// 0=MainScreen; 1=SecondScreen

			MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
			GetMonitorInfo(monitorII, &monitorInfo);

			full_xsize = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
			full_ysize = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
		}
		else
		{
			full_xsize 	= GetSystemMetrics(SM_CXSCREEN);
			full_ysize 	= GetSystemMetrics(SM_CYSCREEN);
		}

		//rapporto		= (float)m_pDib->Width() / (float)m_pDib->Height();
		//full_ysize 	= GetSystemMetrics(SM_CYSCREEN);
		//full_xsize 	= (int)((float)full_ysize * rapporto);
		
		SetWindowPos(&wndTopMost, 0, 0, full_xsize , full_ysize, SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);
	}
}


BEGIN_MESSAGE_MAP(CMaximizeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL() //Gabriel BUG 6225 - Lista DO FIX
	ON_WM_KEYDOWN() //Gabriel BUG 6225 - Lista DO FIX
END_MESSAGE_MAP()

BOOL CMaximizeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitializeWindow();

	CenterWindow();

	return TRUE;
}

void CMaximizeDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

    if (m_pDib)
	{
		CRect 	DibRect (0,0,m_pDib->Width(), m_pDib->Height());
		CRect 	ScreenRect;
		CRect 	FitRect;

		GetClientRect(&ScreenRect);

		//in altezza in base alla larghezza
		FitRect.left	= 0;
		FitRect.top		= 0;
		FitRect.right  	= FitRect.left + ScreenRect.Width();
		FitRect.bottom 	= FitRect.top  + (int)(((double)DibRect.Height() * (double)ScreenRect.Width()) / ((double)DibRect.Width()));
		//se la proporzione è inversa....
		if (FitRect.Height() > ScreenRect.Height())
		{
			//in larghezza in base all'altezza
			FitRect.bottom 	= FitRect.top  + ScreenRect.Height();
			FitRect.right  	= FitRect.left + (int)(((double)DibRect.Width() * (double)ScreenRect.Height()) / ((double)DibRect.Height()));
		}

		//fondo nero....
		::PatBlt(dc.GetSafeHdc(), ScreenRect.left, ScreenRect.top, ScreenRect.Width(), ScreenRect.Height(), BLACKNESS);

    	//centraggio sulla pagina...
		ScreenRect.left   += (ScreenRect.Width()-FitRect.Width()) / 2;
    	ScreenRect.right  = ScreenRect.left + FitRect.Width();
    	ScreenRect.top    += (ScreenRect.Height()-FitRect.Height()) / 2;
    	ScreenRect.bottom = ScreenRect.top + FitRect.Height();
		
		m_pDib->PaintDIB (dc.GetSafeHdc(), ScreenRect, DibRect, 0);
	}
}

void CMaximizeDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
}

void CMaximizeDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonDown(nFlags, point);

	OnCancel();
}

//Gabriel BUG 6225 - Lista DO FIX
BOOL CMaximizeDlg::CaricaImmagine()
{
	BOOL bReturn = FALSE;
	POSITION pos = m_ImgList->FindIndex(m_lNumPage);
	long lTemp0;
	long lTemp1;

	if (pos != NULL)
	{
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
		long id = m_ImgList->GetAt(pos).img.lID;
		HBITMAP hBitmap = m_pEsamiView->m_pImgManager->GetImgMP(m_ImgList->GetAt(pos).img.lID, FALSE, FALSE, FALSE, lTemp0, lTemp1);
		if (hBitmap != NULL)
		{
			BeginWaitCursor();

			m_pDib->Attach(CDib::BitmapToDIB(hBitmap, NULL), TRUE);

			DeleteObject(hBitmap);

			EndWaitCursor();

			bReturn = TRUE;
		}
	}

	return bReturn;
}

//Gabriel BUG 6225 - Lista DO FIX
BOOL CMaximizeDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (theApp.m_bAtivaListaDO)
	{
		if (zDelta < 0) // DOWN
		{
			BOOL bResult = TRUE;

			if (m_lNumPage != m_lTotPage)
			{
				m_lNumPage++;

				bResult = CaricaImmagine();

				if (bResult)
				{
					InitializeWindow();
					AutoRedraw();
				}
			}
			
			return bResult;

		}
		else // UP
		{
			BOOL bResult = TRUE;

			if (m_lNumPage != 0)
			{
				m_lNumPage--;

				bResult = CaricaImmagine();

				if (bResult)
				{
					InitializeWindow();
					AutoRedraw();
				}
			}

			return bResult;
		}
	}
	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

//Gabriel BUG 6225 - Lista DO FIX
BOOL CMaximizeDlg::PreTranslateMessage(MSG* pMsg)
{
	BOOL bReturn = FALSE;

	if (theApp.m_bAtivaListaDO)
	{
		if (pMsg->message == WM_KEYDOWN)
		{
			if ((pMsg->wParam == VK_LEFT) || (pMsg->wParam == VK_UP))
			{
				BOOL bResult = TRUE;

				if (m_lNumPage != 0)
				{
					m_lNumPage--;

					bResult = CaricaImmagine();

					if (bResult)
					{
						InitializeWindow();
						AutoRedraw();
					}
				}
				bReturn = TRUE;
			}
			if ((pMsg->wParam == VK_RIGHT) || (pMsg->wParam == VK_DOWN))
			{
				BOOL bResult = TRUE;

				if (m_lNumPage != m_lTotPage)
				{
					m_lNumPage++;

					bResult = CaricaImmagine();

					if (bResult)
					{
						InitializeWindow();
						AutoRedraw();
					}
				}
				bReturn = TRUE;
			}
		}
	}
	
	return bReturn;
}

//Gabriel BUG 6225 - Lista DO FIX
void CMaximizeDlg::AutoRedraw()
{
	CRect ImgRect;

	GetClientRect(&ImgRect);

	RedrawWindow(&ImgRect, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW);
}

//Gabriel BUG 6225 - Lista DO FIX
long CMaximizeDlg::GetCurrentPageNum()
{
	return m_lNumPage;
}