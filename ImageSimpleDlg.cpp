#include "stdafx.h"
#include "Endox.h"
#include "ImageSimpleDlg.h"

#include <GdiPlus.h>

#include "DLL_Imaging\h\AmLogin.h"

#include "EsamiView.h"
#include "MaximizeDlg.h"
#include "PdfStampaDlg.h"

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CImageSimpleDlg::m_nShowMode = 2;

CImageSimpleDlg::CImageSimpleDlg(CWnd *pParent, CEsamiView* pEsamiView, CString sImageFile)
	: CEndoxResizableDlg(CImageSimpleDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_sImageFile = sImageFile;

	//

	m_bInit = FALSE;
	m_bIsMultipage = FALSE;
	m_bNextTiff = FALSE;
	m_bPrevTiff = FALSE;
	m_bRedrawBack = TRUE;

	m_nDLGHeight = 0;
	m_nDLGWidth = 0;
	m_nTGAHeight = 0;
	m_nTGAWidth = 0;

	m_lCurTiffPage = 0;
	m_lTotTiffPages = 0;

	m_DibRectScreen = CRect(0,0,0,0);
	m_DibRectSource = CRect(0,0,0,0);
}

BOOL CImageSimpleDlg::PreTranslateMessage(MSG* pMsg) 
{
	BOOL bReturn = FALSE;

	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam == VK_UP) && m_bPrevTiff)
		{
			OnBnClickedButtonPrevTiff();
			bReturn = TRUE;
		}
		if ((pMsg->wParam == VK_DOWN) && m_bNextTiff)
		{
			OnBnClickedButtonNextTiff();
			bReturn = TRUE;
		}
	}

	if (!bReturn)
		bReturn = CEndoxResizableDlg::PreTranslateMessage(pMsg);

	return bReturn;
}

void CImageSimpleDlg::InitializeWindow()
{
	CRect	ImgRect;
	int		nDimX;
	int		nDimY;

	m_nTGAWidth   = 0;
	m_nTGAHeight  = 0;
	m_nDLGWidth   = 0;
	m_nDLGHeight  = 0;
    
	m_ctrlImage.GetWindowRect(&ImgRect);
	ScreenToClient(&ImgRect);

	if (m_dibImage.IsValidDib())
	{
		// sempre grande 768x576 con le scrollbar
    	m_nTGAWidth = m_dibImage.Width();
    	m_nTGAHeight = m_dibImage.Height();
		m_nDLGWidth = ImgRect.Width();   
	  	m_nDLGHeight = ImgRect.Height();
	}

	PrepareRectangle();

	switch(m_nShowMode)
	{
		case 0: // 1:1
		{
			nDimX = max(0, m_nTGAWidth  - m_nDLGWidth);
			nDimY = max(0, m_nTGAHeight - m_nDLGHeight);

			m_ctrlScrollH.SetScrollRange (0, nDimX);
			m_ctrlScrollV.SetScrollRange (0, nDimY);
			m_ctrlScrollH.SetScrollPos (0);
			m_ctrlScrollV.SetScrollPos (0);
			m_ctrlScrollH.EnableWindow (nDimX > 0);
			m_ctrlScrollV.EnableWindow (nDimY > 0);

			break;
		}
		case 1: // Fit in window
		{
			m_ctrlScrollH.SetScrollRange (0, 0);
			m_ctrlScrollV.SetScrollRange (0, 0);
			m_ctrlScrollH.SetScrollPos (0);
			m_ctrlScrollV.SetScrollPos (0);
			m_ctrlScrollH.EnableWindow (FALSE);
			m_ctrlScrollV.EnableWindow (FALSE);

			break;
		}
		default: // Sandro 16/01/2013 // se l'immagine è piccola viene mostrata "1:1", se l'immagine è grande viene fatto il "fit in window"
		{
			m_ctrlScrollH.SetScrollRange(0, 0);
			m_ctrlScrollV.SetScrollRange(0, 0);
			m_ctrlScrollH.SetScrollPos(0);
			m_ctrlScrollV.SetScrollPos(0);
			m_ctrlScrollH.EnableWindow(FALSE);
			m_ctrlScrollV.EnableWindow(FALSE);

			break;
		}
	}
}

void CImageSimpleDlg::PrepareRectangle()
{
	CRect 	ScreenRect(0, 0, m_nDLGWidth, m_nDLGHeight);
	CRect 	DibRect   (0, 0, m_nTGAWidth, m_nTGAHeight);
	CRect 	FitRect;
	
	CRect	ImgRect;
	m_ctrlImage.GetWindowRect(&ImgRect);
	ScreenToClient(&ImgRect);
	ScreenRect.OffsetRect(ImgRect.left, ImgRect.top);

	switch(m_nShowMode)
	{
		case 0: // 1:1
		{
			if (m_nDLGWidth > m_nTGAWidth)
			{
	    		// centraggio sull'asse x...
    			ScreenRect.left   += (ScreenRect.Width()-DibRect.Width()) / 2;
    			ScreenRect.right  = ScreenRect.left + DibRect.Width();
			}

			if (m_nDLGHeight > m_nTGAHeight)
			{
	    		// centraggio sull'asse y...
    			ScreenRect.top    += (ScreenRect.Height()-DibRect.Height()) / 2;
    			ScreenRect.bottom = ScreenRect.top + DibRect.Height();
			}

			break;
		}
		case 1: // Fit in window
		{
			// in altezza in base alla larghezza
			FitRect.left	= 0;
			FitRect.top		= 0;
			FitRect.right  	= FitRect.left + m_nDLGWidth;
			FitRect.bottom 	= FitRect.top  + (int)(((double)m_nTGAHeight * (double)m_nDLGWidth) / ((double)m_nTGAWidth));
			// se la proporzione è inversa....
			if (FitRect.Height() > m_nDLGHeight)
			{
				// in larghezza in base all'altezza
				FitRect.bottom 	= FitRect.top  + m_nDLGHeight;
				FitRect.right  	= FitRect.left + (int)(((double)m_nTGAWidth * (double)m_nDLGHeight) / ((double)m_nTGAHeight));
			}

    		// centraggio sulla pagina...
			ScreenRect.left   += (ScreenRect.Width()-FitRect.Width()) / 2;
    		ScreenRect.right  = ScreenRect.left + FitRect.Width();
    		ScreenRect.top    += (ScreenRect.Height()-FitRect.Height()) / 2;
    		ScreenRect.bottom = ScreenRect.top + FitRect.Height();

			break;
		}
		default: // Sandro 16/01/2013 // se l'immagine è piccola viene mostrata "1:1", se l'immagine è grande viene fatto il "fit in window"
		{
			if ((m_nTGAWidth < m_nDLGWidth) && (m_nTGAHeight < m_nDLGHeight))
			{
				// 1:1 //

    			// centraggio sull'asse x //
				ScreenRect.left += (ScreenRect.Width() - DibRect.Width()) / 2;
				ScreenRect.right = ScreenRect.left + DibRect.Width();

				// centraggio sull'asse y //
				ScreenRect.top += (ScreenRect.Height() - DibRect.Height()) / 2;
				ScreenRect.bottom = ScreenRect.top + DibRect.Height();
			}
			else
			{
				// fit in window //

				// in altezza in base alla larghezza //
				FitRect.left = 0;
				FitRect.top = 0;
				FitRect.right = FitRect.left + m_nDLGWidth;
				FitRect.bottom = FitRect.top + (int)(((double)m_nTGAHeight * (double)m_nDLGWidth) / ((double)m_nTGAWidth));

				// se la proporzione è inversa //
				if (FitRect.Height() > m_nDLGHeight)
				{
					// in larghezza in base all'altezza //
					FitRect.bottom = FitRect.top + m_nDLGHeight;
					FitRect.right = FitRect.left + (int)(((double)m_nTGAWidth * (double)m_nDLGHeight) / ((double)m_nTGAHeight));
				}

    			// centraggio sulla pagina //
				ScreenRect.left += (ScreenRect.Width() - FitRect.Width()) / 2;
    			ScreenRect.right = ScreenRect.left + FitRect.Width();
    			ScreenRect.top += (ScreenRect.Height() - FitRect.Height()) / 2;
    			ScreenRect.bottom = ScreenRect.top + FitRect.Height();
			}

			break;
		}
	}

	m_DibRectSource = DibRect;
	m_DibRectScreen = ScreenRect;
	m_bRedrawBack = TRUE;
}

void CImageSimpleDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_ESPORTA, m_ctrlBtnEsporta);
	DDX_Control(pDX, IDC_BUTTON_ESPORTA_FRAME, m_ctrlBtnEsportaFrame);
	DDX_Control(pDX, IDC_BUTTON_ESPORTA_TUTTI, m_ctrlBtnEsportaTutti);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
	DDX_Control(pDX, IDC_BUTTON_STAMPA, m_ctrlBtnStampa);
	DDX_Control(pDX, IDC_BUTTON_STAMPA_FRAME, m_ctrlBtnStampaFrame);
	DDX_Control(pDX, IDC_BUTTON_STAMPA_TUTTI, m_ctrlBtnStampaTutti);
	DDX_Control(pDX, IDC_SHOW_1, m_ctrlRadioShow1);
	DDX_Control(pDX, IDC_SHOW_2, m_ctrlRadioShow2);
	DDX_Control(pDX, IDC_SHOW_3, m_ctrlRadioShow3);

	DDX_Control(pDX, IDC_STATIC_VIEW, m_ctrlStaticView);

	DDX_Control(pDX, IDC_HSCROLL, m_ctrlScrollH);
	DDX_Control(pDX, IDC_VSCROLL, m_ctrlScrollV);
	DDX_Control(pDX, IDC_IMAGE, m_ctrlImage);
	DDX_Radio(pDX, IDC_SHOW_1, m_nShowMode);

	m_bPrevTiff = ((m_lTotTiffPages > 1) && (m_lCurTiffPage > 0));
	m_bNextTiff = ((m_lTotTiffPages > 1) && (m_lCurTiffPage < m_lTotTiffPages - 1));

	m_ctrlBtnPrevTiff.EnableWindow(m_bPrevTiff);
	m_ctrlBtnNextTiff.EnableWindow(m_bNextTiff);
}

BEGIN_MESSAGE_MAP(CImageSimpleDlg, CEndoxResizableDlg)

	ON_WM_LBUTTONDBLCLK()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_VSCROLL()

	ON_BN_CLICKED(IDC_SHOW_1, OnChangeShow)
	ON_BN_CLICKED(IDC_SHOW_2, OnChangeShow)
	ON_BN_CLICKED(IDC_SHOW_3, OnChangeShow)

	ON_BN_CLICKED(IDC_BUTTON_PREVTIFF, OnBnClickedButtonPrevTiff)
	ON_BN_CLICKED(IDC_BUTTON_NEXTTIFF, OnBnClickedButtonNextTiff)
	ON_BN_CLICKED(IDC_BUTTON_STAMPA, OnBnClickedButtonStampa)
	ON_BN_CLICKED(IDC_BUTTON_STAMPA_FRAME, OnBnClickedButtonStampaFrame)
	ON_BN_CLICKED(IDC_BUTTON_STAMPA_TUTTI, OnBnClickedButtonStampaTutti)
	ON_BN_CLICKED(IDC_BUTTON_ESPORTA, OnBnClickedButtonEsporta)
	ON_BN_CLICKED(IDC_BUTTON_ESPORTA_FRAME, OnBnClickedButtonEsportaFrame)
	ON_BN_CLICKED(IDC_BUTTON_ESPORTA_TUTTI, OnBnClickedButtonEsportaTutti)

	ON_BN_CLICKED(IDC_BTN_ROTATESX, OnBnClickedBtnRotateSx)
	ON_BN_CLICKED(IDC_BTN_ROTATEDX, OnBnClickedBtnRotateDx)

END_MESSAGE_MAP()

BOOL CImageSimpleDlg::OnInitDialog() 
{
	m_ctrlBtnPrevTiff.AutoLoad(IDC_BUTTON_PREVTIFF, this);
	m_ctrlBtnNextTiff.AutoLoad(IDC_BUTTON_NEXTTIFF, this);
	m_ctrlBtnRotateSx.AutoLoad(IDC_BTN_ROTATESX, this);
	m_ctrlBtnRotateDx.AutoLoad(IDC_BTN_ROTATEDX, this);

	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_STATIC_LINE1, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDOK, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_STATIC_LINE2, CSize(0, 0), CSize(0, 100));
	AddAnchor(IDC_IMAGE, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_VSCROLL, CSize(100, 0), CSize(100, 100));
	AddAnchor(IDC_HSCROLL, CSize(0, 100), CSize(100, 100));

	m_ctrlBtnOK.SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_VIEW)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_FRAMES)->SetFont(&theApp.m_fontBold);

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	if (!CaricaImmagine())
	{
		EndDialog(IDCANCEL);
		return FALSE;
	}
	InitializeWindow();

	BOOL bEnable = (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image);
	m_ctrlBtnStampa.EnableWindow(bEnable);
	m_ctrlBtnStampaFrame.EnableWindow(bEnable);
	m_ctrlBtnStampaTutti.EnableWindow(bEnable);
	m_ctrlBtnEsporta.EnableWindow(bEnable);
	m_ctrlBtnEsportaFrame.EnableWindow(bEnable);
	m_ctrlBtnEsportaTutti.EnableWindow(bEnable);

	if (m_bIsMultipage)
	{
		m_ctrlBtnStampa.ShowWindow(SW_HIDE);
		m_ctrlBtnStampaFrame.ShowWindow(SW_SHOW);
		m_ctrlBtnStampaTutti.ShowWindow(SW_SHOW);
		m_ctrlBtnEsporta.ShowWindow(SW_HIDE);
		m_ctrlBtnEsportaFrame.ShowWindow(SW_SHOW);
		m_ctrlBtnEsportaTutti.ShowWindow(SW_SHOW);

		m_ctrlBtnPrevTiff.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_FRAMES)->ShowWindow(SW_SHOW);
		m_ctrlBtnNextTiff.ShowWindow(SW_SHOW);

		UpdateData(FALSE);
	}
	else
	{
		m_ctrlBtnStampa.ShowWindow(SW_SHOW);
		m_ctrlBtnStampaFrame.ShowWindow(SW_HIDE);
		m_ctrlBtnStampaTutti.ShowWindow(SW_HIDE);
		m_ctrlBtnEsporta.ShowWindow(SW_SHOW);
		m_ctrlBtnEsportaFrame.ShowWindow(SW_HIDE);
		m_ctrlBtnEsportaTutti.ShowWindow(SW_HIDE);

		m_ctrlBtnPrevTiff.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_FRAMES)->ShowWindow(SW_HIDE);
		m_ctrlBtnNextTiff.ShowWindow(SW_HIDE);

		UpdateData(FALSE);
	}

	EnableToolTips(TRUE);
	theApp.LocalizeDialog(this, CImageSimpleDlg::IDD, "ImageSimpleDlg");

	m_bInit = TRUE;
	return TRUE;
}

void CImageSimpleDlg::OnMove(int x, int y) 
{
	m_bRedrawBack = TRUE;
	
	CEndoxResizableDlg::OnMove(x, y);
}

void CImageSimpleDlg::OnPaint() 
{
	CPaintDC dc(this);
	
    if (m_dibImage.IsValidDib())
	{
    	CPoint	ptOffset;
    	CRect	rectSource;
		CRect	ImgRect;
		
		m_ctrlImage.GetWindowRect(&ImgRect);
		ScreenToClient(&ImgRect);
		
		switch(m_nShowMode)
		{
			case 0: // 1:1
			{
				if (m_nDLGWidth > m_nTGAWidth || m_nDLGHeight > m_nTGAHeight)
				{
					::PatBlt(dc.GetSafeHdc(), ImgRect.left, ImgRect.top, m_nDLGWidth, m_nDLGHeight, BLACKNESS);

					m_bRedrawBack = FALSE;
				}

				ptOffset.x = m_ctrlScrollH.GetScrollPos();
				ptOffset.y = m_ctrlScrollV.GetScrollPos();

				rectSource.left		= ptOffset.x;
				rectSource.top		= ptOffset.y;
				rectSource.right	= min(rectSource.left + ImgRect.Width(),  m_DibRectSource.Width ());
				rectSource.bottom	= min(rectSource.top  + ImgRect.Height(), m_DibRectSource.Height());

				m_dibImage.PaintDIB (dc.GetSafeHdc(), m_DibRectScreen, rectSource, 0);

				break;
			}
			case 1: // Fit in window
			{
				if (m_nDLGWidth != m_nTGAWidth || m_nDLGHeight != m_nTGAHeight)
				{
					::PatBlt(dc.GetSafeHdc(), ImgRect.left, ImgRect.top, m_nDLGWidth, m_nDLGHeight, BLACKNESS);

					m_bRedrawBack = FALSE;
				}

				m_dibImage.PaintDIB (dc.GetSafeHdc(), m_DibRectScreen, m_DibRectSource, 0);

				break;
			}
			default: // Sandro 16/01/2013 // se l'immagine è piccola viene mostrata "1:1", se l'immagine è grande viene fatto il "fit in window"
			{
				if ((m_nTGAWidth < m_nDLGWidth) && (m_nTGAHeight < m_nDLGHeight))
				{
					// 1:1 //

					::PatBlt(dc.GetSafeHdc(), ImgRect.left, ImgRect.top, m_nDLGWidth, m_nDLGHeight, BLACKNESS);
					m_bRedrawBack = FALSE;

					ptOffset.x = m_ctrlScrollH.GetScrollPos();
					ptOffset.y = m_ctrlScrollV.GetScrollPos();

					rectSource.left = ptOffset.x;
					rectSource.top = ptOffset.y;
					rectSource.right = min(rectSource.left + ImgRect.Width(), m_DibRectSource.Width());
					rectSource.bottom = min(rectSource.top + ImgRect.Height(), m_DibRectSource.Height());

					m_dibImage.PaintDIB(dc.GetSafeHdc(), m_DibRectScreen, rectSource, 0);
				}
				else
				{
					// fit in window //

					if ((m_nDLGWidth != m_nTGAWidth) || (m_nDLGHeight != m_nTGAHeight))
					{
						::PatBlt(dc.GetSafeHdc(), ImgRect.left, ImgRect.top, m_nDLGWidth, m_nDLGHeight, BLACKNESS);
						m_bRedrawBack = FALSE;
					}

					m_dibImage.PaintDIB(dc.GetSafeHdc(), m_DibRectScreen, m_DibRectSource, 0);
				}

				break;
			}
		}
	}
}

void CImageSimpleDlg::AutoRedraw()
{
	CRect ImgRect;

	m_ctrlImage.GetWindowRect(&ImgRect);
	ScreenToClient(&ImgRect);

	RedrawWindow(&ImgRect, NULL, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW);
}

/*
void CImageSimpleDlg::OnButtonPrevTiff()
{
	BeginWaitCursor();

	m_lCurTiffPage--;
	if (CaricaImmagine())
	{
		InitializeWindow();
		AutoRedraw();
	}
	UpdateData(FALSE);

	EndWaitCursor();
}

void CImageSimpleDlg::OnButtonNextTiff()
{
	BeginWaitCursor();

	m_lCurTiffPage++;
	if (CaricaImmagine())
	{
		InitializeWindow();
		AutoRedraw();
	}
	UpdateData(FALSE);

	EndWaitCursor();
}
*/

/*
void CImageSimpleDlg::OnButtonPrintOne()
{
	// cancello la lista delle immagini selezionate //
	CFileBmp::DeleteListSelected(m_bIsAlbumGlobal);

	// seleziono SOLO questa immagine //
	SelectThisImage();

	// cambio il numero di immagini per pagina, impostandolo ad 1 //
	int nOldTypePrintImage = theApp.m_nTypePrintImage;
	theApp.m_nTypePrintImage = 0; // <-- una immagine per pagina //

	// imposto la stampa di un singolo frame //
	theApp.m_lOnlyThisFrame = m_lCurTiffPage;

	// lancio la stampa //
	m_pEsamiView->SendMessage(WM_COMMAND, ID_FILE_STAMPAIMMAGINI, NULL);

	// azzero la stampa di un singolo frame //
	theApp.m_lOnlyThisFrame = -1;

	// ripristino il numero di immagini per pagina //
	theApp.m_nTypePrintImage = nOldTypePrintImage;

	// deseleziono tutte le immagini //
	CFileBmp::DeleteListSelected(m_bIsAlbumGlobal);

	// riaggiorno l'immagine //
	m_bRequeryImage = TRUE;
	m_bRedrawBack = TRUE;
	AutoRedraw();
}

void CImageSimpleDlg::OnButtonPrintAll()
{
	// cancello la lista delle immagini selezionate //
	CFileBmp::DeleteListSelected(m_bIsAlbumGlobal);

	// seleziono SOLO questa immagine //
	SelectThisImage();

	// lancio la stampa //
	m_pEsamiView->SendMessage(WM_COMMAND, ID_FILE_STAMPAIMMAGINI, NULL);

	// deseleziono tutte le immagini //
	CFileBmp::DeleteListSelected(m_bIsAlbumGlobal);

	// riaggiorno l'immagine //
	m_bRequeryImage = TRUE;
	m_bRedrawBack = TRUE;
	AutoRedraw();
}

void CImageSimpleDlg::OnButtonEsportaFrame()
{
	BeginWaitCursor();

	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_1);
	CFolderDialog dlg(strTitle, theApp.m_sExportFolder, 0x0040, this);
	if (dlg.DoModal() == IDOK)
	{
		CString strTemp = dlg.GetSelectedFolder();
		if (strTemp.Right(1) != "\\")
			strTemp += "\\";

		if (strTemp != theApp.m_sExportFolder)
		{
			theApp.m_sExportFolder = strTemp;
			WritePrivateProfileString(szPercorsi, szExportFolder, theApp.m_sExportFolder, theApp.m_sFileConfig);
		}

		strTemp.Format("%s%s %s", theApp.m_sExportFolder, m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome);
		if (VerificaPercorso(strTemp))
		{
			CString sPrefisso = "";
			if (theApp.m_bNominativoSuExportImmagini)
				sPrefisso = m_pEsamiView->m_pPazientiSet->m_sCognome + " " + m_pEsamiView->m_pPazientiSet->m_sNome;

			m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
			m_pEsamiView->m_pImgManager->ExportImgSingleFrame(strTemp, sPrefisso, m_ImgListOrgani.GetAt(pos).img.lID, m_lCurTiffPage, (imageformat)(theApp.m_nExpFormat + 1));
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_EXPORT_PATH), MB_ICONSTOP);
		}
	}

	EndWaitCursor();
}
*/

void CImageSimpleDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CEndoxResizableDlg::OnHScroll(nSBCode, nPos, pScrollBar);

    ////MOVIMENTO EFFETTIVO
	int Min, Max, OldPos, NewPos;

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
	
	pScrollBar->SetScrollPos(NewPos);

	if (pScrollBar == &m_ctrlScrollH)
		AutoRedraw();
}

void CImageSimpleDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CEndoxResizableDlg::OnVScroll(nSBCode, nPos, pScrollBar);

    ////MOVIMENTO EFFETTIVO
	int Min, Max, OldPos, NewPos;

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
			//if ((int)nPos <= Max && (int)nPos >= Min)
				NewPos = nPos;
			break;
		
		default:
			NewPos = OldPos;
	}
	
	pScrollBar->SetScrollPos(NewPos);

 
    ////TEST dei valori
	if (pScrollBar == &m_ctrlScrollV)
	{
		AutoRedraw();
	}
}

void CImageSimpleDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CEndoxResizableDlg::OnLButtonDblClk(nFlags, point);

	if (m_dibImage.IsValidDib())
	{
		CRect ImgRect;
		
		m_ctrlImage.GetWindowRect(&ImgRect);
		ScreenToClient(&ImgRect);
		
		if (ImgRect.PtInRect(point))
		{
			CMaximizeDlg dlg(this, &m_dibImage);

			dlg.DoModal();
		
			m_bRedrawBack = TRUE;
			AutoRedraw();
		}
	}
}

// Sandro Gallina - 14/07/2004 //
BOOL CImageSimpleDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta < 0)
	{
		// girata in giù //

		// if (m_bNextTiff)
			// OnButtonNextTiff();
	}
	else
	{
		// girata in su //

		// if (m_bPrevTiff)
			// OnButtonPrevTiff();
	}

	return CEndoxResizableDlg::OnMouseWheel(nFlags, zDelta, pt);
}

void CImageSimpleDlg::OnChangeShow() 
{
	UpdateData(TRUE);

	InitializeWindow();

	AutoRedraw();
}

BOOL CImageSimpleDlg::CaricaImmagine()
{
	BOOL bReturn = FALSE;

	SetDlgItemText(IDC_STATIC_FRAMES, "");

	HBITMAP hBitmap = NULL;
	m_lTotTiffPages = m_pEsamiView->m_pImgManager->LoadLocalImageEx(m_sImageFile, &hBitmap, NULL, 0, 0, m_lCurTiffPage);

	m_bIsMultipage = (m_lTotTiffPages > 1);

	if (hBitmap != NULL)
	{
		BeginWaitCursor();

		CString strFrame;
		strFrame.Format("%li / %li", m_lCurTiffPage + 1, m_lTotTiffPages);
		SetDlgItemText(IDC_STATIC_FRAMES, strFrame);

		m_dibImage.Attach(CDib::BitmapToDIB(hBitmap, NULL), TRUE);

		DeleteObject(hBitmap);

		EndWaitCursor();		                    

		bReturn = TRUE;
	}

	return bReturn;
}

void CImageSimpleDlg::OnSize(UINT nType, int cx, int cy) 
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	if (m_bInit)
	{
		InitializeWindow();
		AutoRedraw();
	}
}

void CImageSimpleDlg::OnBnClickedButtonStampa()
{
	//
	BeginWaitCursor();

	// creo il PDF //
	CList<CDib*> listImmagini;
	listImmagini.AddTail(&m_dibImage);
	CString strPdfFile = m_pEsamiView->CreateHaruPdfImageFileFromDib(&listImmagini);
	if (!strPdfFile.IsEmpty())
	{
		CPdfStampaDlg(this, theApp.GetMessageString(IDS_STAMPA_IMMAGINI), strPdfFile, FALSE, theApp.m_lIDStampanteImmagini, 0, TRUE).DoModal();
		DeleteFile(strPdfFile);
	}

	//
	EndWaitCursor();
}

void CImageSimpleDlg::OnBnClickedButtonStampaFrame()
{
	//
	BeginWaitCursor();

	// creo il PDF //
	CList<CDib*> listImmagini;
	listImmagini.AddTail(&m_dibImage);
	CString strPdfFile = m_pEsamiView->CreateHaruPdfImageFileFromDib(&listImmagini);
	{
		CPdfStampaDlg(this, theApp.GetMessageString(IDS_STAMPA_IMMAGINI), strPdfFile, FALSE, theApp.m_lIDStampanteImmagini, 0, TRUE).DoModal();
		DeleteFile(strPdfFile);
	}

	//
	EndWaitCursor();
}

void CImageSimpleDlg::OnBnClickedButtonStampaTutti()
{
	//
	BeginWaitCursor();

	//

	CList<CDib*> listImmagini;

	// carico tutte le pagine del TIFF nella lista delle DIB da stampare //

	HBITMAP hBitmap = NULL;
	long lTotTiffPages = m_pEsamiView->m_pImgManager->LoadLocalImageEx(m_sImageFile, &hBitmap, NULL, 0, 0, 0);
	if (hBitmap != NULL)
	{
		for(int i = 0; i < lTotTiffPages; i++)
		{
			if (i > 0)
				m_pEsamiView->m_pImgManager->LoadLocalImageEx(m_sImageFile, &hBitmap, NULL, 0, 0, i); // carico frame successivo //

			CDib* pDibImage = new CDib;
			pDibImage->Attach(CDib::BitmapToDIB(hBitmap, NULL), TRUE);
			DeleteObject(hBitmap);

			//

			listImmagini.AddTail(pDibImage);
		}
	}

	// procedo con la stampa delle DIB che poi vado ad eliminare //

	CString strPdfFile = m_pEsamiView->CreateHaruPdfImageFileFromDib(&listImmagini);
	if (!strPdfFile.IsEmpty())
	{
		CPdfStampaDlg(this, theApp.GetMessageString(IDS_STAMPA_IMMAGINI), strPdfFile, FALSE, theApp.m_lIDStampanteImmagini, 0, TRUE).DoModal();
		DeleteFile(strPdfFile);

		//

		POSITION pos = listImmagini.GetHeadPosition();
		while(pos != NULL)
		{
			delete listImmagini.GetAt(pos);
			listImmagini.GetNext(pos);
		}
	}

	//

	EndWaitCursor();
}

void CImageSimpleDlg::OnBnClickedButtonEsporta()
{
	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_1);
	CFolderDialog dlg(strTitle, theApp.m_sExportFolder, 0x0040, this);
	if (dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();

		CString strTemp = dlg.GetSelectedFolder();
		if (strTemp.Right(1) != "\\")
			strTemp += "\\";

		if (strTemp != theApp.m_sExportFolder)
		{
			theApp.m_sExportFolder = strTemp;
			WritePrivateProfileString(szPercorsi, szExportFolder, theApp.m_sExportFolder, theApp.m_sFileConfig);
		}

		strTemp.Format("%s%s %s\\", theApp.m_sExportFolder, m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome);
		if (VerificaPercorso(strTemp))
		{
			if (theApp.m_bNominativoSuExportImmagini)
				strTemp += m_pEsamiView->m_pPazientiSet->m_sCognome + " " + m_pEsamiView->m_pPazientiSet->m_sNome + " ";

			SYSTEMTIME timeLocal;
			::GetLocalTime(&timeLocal);
			CString strExportFile;
			strExportFile.Format("%s%04d%02d%02d%02d%02d%02d", strTemp, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond);

			HBITMAP hBitmap = m_dibImage.BitmapFromDib(GetDC()->m_hDC, NULL, DIB_PAL_COLORS);
			if (hBitmap != NULL)
			{
				m_pEsamiView->m_pImgManager->ExportImgFromHBITMAP(strExportFile, hBitmap, (imageformat)(theApp.m_nExpFormat + 1));
				DeleteObject(hBitmap);
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_EXPORT_PATH), MB_ICONSTOP);
		}

		EndWaitCursor();
	}
}

void CImageSimpleDlg::OnBnClickedButtonEsportaFrame()
{
	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_1);
	CFolderDialog dlg(strTitle, theApp.m_sExportFolder, 0x0040, this);
	if (dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();

		CString strTemp = dlg.GetSelectedFolder();
		if (strTemp.Right(1) != "\\")
			strTemp += "\\";

		if (strTemp != theApp.m_sExportFolder)
		{
			theApp.m_sExportFolder = strTemp;
			WritePrivateProfileString(szPercorsi, szExportFolder, theApp.m_sExportFolder, theApp.m_sFileConfig);
		}

		strTemp.Format("%s%s %s\\", theApp.m_sExportFolder, m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome);
		if (VerificaPercorso(strTemp))
		{
			if (theApp.m_bNominativoSuExportImmagini)
				strTemp += m_pEsamiView->m_pPazientiSet->m_sCognome + " " + m_pEsamiView->m_pPazientiSet->m_sNome + " ";

			SYSTEMTIME timeLocal;
			::GetLocalTime(&timeLocal);
			CString strExportFile;
			strExportFile.Format("%s%04d%02d%02d%02d%02d%02d", strTemp, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond);

			HBITMAP hBitmap = m_dibImage.BitmapFromDib(GetDC()->m_hDC, NULL, DIB_PAL_COLORS);
			if (hBitmap != NULL)
			{
				m_pEsamiView->m_pImgManager->ExportImgFromHBITMAP(strExportFile, hBitmap, (imageformat)(theApp.m_nExpFormat + 1));
				DeleteObject(hBitmap);
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_EXPORT_PATH), MB_ICONSTOP);
		}

		EndWaitCursor();
	}
}

void CImageSimpleDlg::OnBnClickedButtonEsportaTutti()
{
	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_1);
	CFolderDialog dlg(strTitle, theApp.m_sExportFolder, 0x0040, this);
	if (dlg.DoModal() == IDOK)
	{
		BeginWaitCursor();

		CString strTemp = dlg.GetSelectedFolder();
		if (strTemp.Right(1) != "\\")
			strTemp += "\\";

		if (strTemp != theApp.m_sExportFolder)
		{
			theApp.m_sExportFolder = strTemp;
			WritePrivateProfileString(szPercorsi, szExportFolder, theApp.m_sExportFolder, theApp.m_sFileConfig);
		}

		strTemp.Format("%s%s %s\\", theApp.m_sExportFolder, m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome);
		if (VerificaPercorso(strTemp))
		{
			if (theApp.m_bNominativoSuExportImmagini)
				strTemp += m_pEsamiView->m_pPazientiSet->m_sCognome + " " + m_pEsamiView->m_pPazientiSet->m_sNome + " ";

			SYSTEMTIME timeLocal;
			::GetLocalTime(&timeLocal);
			CString strExportFile;
			strExportFile.Format("%s%04d%02d%02d%02d%02d%02d.TIFF", strTemp, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond);

			CopyFile(m_sImageFile, strExportFile, FALSE);
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_EXPORT_PATH), MB_ICONSTOP);
		}

		EndWaitCursor();
	}
}

void CImageSimpleDlg::OnBnClickedButtonPrevTiff()
{
	BeginWaitCursor();

	m_lCurTiffPage--;
	if (CaricaImmagine())
	{
		InitializeWindow();
		AutoRedraw();
	}
	UpdateData(FALSE);

	EndWaitCursor();
}

void CImageSimpleDlg::OnBnClickedButtonNextTiff()
{
	BeginWaitCursor();

	m_lCurTiffPage++;
	if (CaricaImmagine())
	{
		InitializeWindow();
		AutoRedraw();
	}
	UpdateData(FALSE);

	EndWaitCursor();
}

/*
void CImageSimpleDlg::OnBnClickedButtonEsportaFrame()
{
	POSITION pos = m_ImgListOrgani.FindIndex(m_nNumPage);

	if (pos != NULL)
	{
		BeginWaitCursor();

		CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_1);
		CFolderDialog dlg(strTitle, theApp.m_sExportFolder, 0x0040, this);
		if (dlg.DoModal() == IDOK)
		{
			CString strTemp = dlg.GetSelectedFolder();
			if (strTemp.Right(1) != "\\")
				strTemp += "\\";

			if (strTemp != theApp.m_sExportFolder)
			{
				theApp.m_sExportFolder = strTemp;
				WritePrivateProfileString(szPercorsi, szExportFolder, theApp.m_sExportFolder, theApp.m_sFileConfig);
			}

			strTemp.Format("%s%s %s", theApp.m_sExportFolder, m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome);
			if (VerificaPercorso(strTemp))
			{
				CString sPrefisso = "";
				if (theApp.m_bNominativoSuExportImmagini)
					sPrefisso = m_pEsamiView->m_pPazientiSet->m_sCognome + " " + m_pEsamiView->m_pPazientiSet->m_sNome;

				m_pEsamiView->m_pImgManager->ExportImgSingleFrame(strTemp, sPrefisso, m_ImgListOrgani.GetAt(pos).img.lID, m_lCurTiffPage, (imageformat)(theApp.m_nExpFormat + 1));
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_EXPORT_PATH), MB_ICONSTOP);
			}
		}

		EndWaitCursor();
	}
}
*/

void CImageSimpleDlg::OnBnClickedBtnRotateSx()
{
	CDC* pDC = GetDC();
	if (pDC != NULL)
	{
		HBITMAP hBitOrig = m_dibImage.BitmapFromDib(pDC->GetSafeHdc(), NULL, DIB_RGB_COLORS); // DIB_PAL_COLORS);
		Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromHBITMAP(hBitOrig, NULL);

		if (pBitmap->GetLastStatus() == Gdiplus::Ok)
		{
			pBitmap->RotateFlip(Rotate270FlipNone);

			HBITMAP hBitRot;
			pBitmap->GetHBITMAP(Gdiplus::Color(0, 0, 0), &hBitRot);

			m_dibImage.Attach(CDib::BitmapToDIB(hBitRot, NULL), TRUE);

			DeleteObject(hBitRot);
		}

		//

		DeleteObject(hBitOrig);

		delete pBitmap;

		ReleaseDC(pDC);

		//

		m_nTGAWidth = m_dibImage.Width();
		m_nTGAHeight = m_dibImage.Height();

		PrepareRectangle();

		Invalidate(FALSE);
	}
}

void CImageSimpleDlg::OnBnClickedBtnRotateDx()
{
	CDC* pDC = GetDC();
	if (pDC != NULL)
	{
		HBITMAP hBitOrig = m_dibImage.BitmapFromDib(pDC->GetSafeHdc(), NULL, DIB_RGB_COLORS); // DIB_PAL_COLORS);
		Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromHBITMAP(hBitOrig, NULL);

		if (pBitmap->GetLastStatus() == Gdiplus::Ok)
		{
			pBitmap->RotateFlip(Rotate90FlipNone);

			HBITMAP hBitRot;
			pBitmap->GetHBITMAP(Gdiplus::Color(0, 0, 0), &hBitRot);

			m_dibImage.Attach(CDib::BitmapToDIB(hBitRot, NULL), TRUE);

			DeleteObject(hBitRot);
		}

		//

		DeleteObject(hBitOrig);

		delete pBitmap;

		ReleaseDC(pDC);

		//

		m_nTGAWidth = m_dibImage.Width();
		m_nTGAHeight = m_dibImage.Height();

		PrepareRectangle();

		Invalidate(FALSE);
	}
}
