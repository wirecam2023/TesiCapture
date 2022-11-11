#include "stdafx.h"
#include "Endox.h"
#include "ImageDlg.h"

#include "DLL_Imaging\h\AmLogin.h"
#include "DLL_Imaging\h\ImgArchive.h"

#include <GdiPlus.h>
#include <io.h>

#include "AlbumForm.h"
#include "BrightnessDlg.h"
#include "Common.h"
#include "ContrastDlg.h"
#include "ContrastRGBDlg.h"
#include "CustomDate.h"
#include "Define.h"
#include "Dib.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "EspelliDlg.h"
#include "FileBmp.h"
#include "ImmaginiPuntiSet.h"
#include "LogFileWriter.h"
#include "MaximizeDlg.h"
#include "MmSystem.h"
#include "ObSelect.h"
#include "PuntiPazienteSet.h"
#include "PuntiSet.h"

#include "MonitorScreens.h" //Gabriel BUG 6225 - Lista DO FIX
#include "Monitor.h" //Gabriel BUG 6225 - Lista DO FIX

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CImageDlg::m_nShowMode = 2;

//Gabriel BUG 6225 - Lista DO
CImageDlg::CImageDlg(CWnd *pParent, BOOL bDoModal, long lPaziente, long lEsame, long lID, int iType, BOOL bIsReferto)
	: CEndoxResizableDlg(CImageDlg::IDD, pParent)
{
	m_bInit = FALSE;

	m_nBMPWidth = 0;
	m_nBMPHeight = 0;
	m_nTGAWidth = 0;
	m_nTGAHeight = 0;
	m_nDLGWidth = 0;
	m_nDLGHeight = 0;

	m_bIsAlbumGlobal = FALSE;

	m_bIsSelect = FALSE;

	m_lID = -1;
	m_iType = -1;

	m_pDib = new CDib;
	m_pDibUndo = new CDib;

	m_bRequeryImage = FALSE;
	m_bDeselectImage = FALSE;
	m_bSaveImage = FALSE;
	m_bSaveUndo = FALSE;
	m_pEsamiView = NULL;

	m_DibRectSource = CRect(0, 0, 0, 0);
	m_DibRectScreen = CRect(0, 0, 0, 0);
	m_bRedrawBack = TRUE;

	m_lPaziente = 0;
	m_lEsame = 0;

	XRClient_Play = NULL;
	XRClient_StopPlay = NULL;
	XRClient_EnableVideoOutput = NULL;
	XRClient_GetErrorOccurred = NULL;
	m_bError = FALSE;

	m_bIsMultipage = FALSE;
	m_lCurTiffPage = 0;
	m_lTotTiffPages = 0;
	m_bPrevTiff = FALSE;
	m_bNextTiff = FALSE;

	m_bMantieniImmagine = FALSE;

	//

	m_rectFrameSagoma = CRect(0, 0, 0, 0);
	m_rectPaintSagoma = CRect(0, 0, 0, 0);
	m_ptSagome = CPoint(-1, -1);
	m_lNumeroDermox = -1;

	m_bDoModal = bDoModal;
	SetIDs(lPaziente, lEsame, lID, iType);

	theApp.m_lInstanceCountCImageDlg = 1; //Gabriel BUG 6225 - Lista DO
	m_bIsReferto = bIsReferto;

	m_pParentWnd = pParent; //Gabriel - BUG Refresh álbum
	//
}
//Gabriel BUG 6225 - Lista DO
void CImageDlg::PostNcDestroy()
{
	if (m_pDib)
	{
		m_pDib->ReleaseContents();
		delete m_pDib;
		m_pDib = NULL;
	}

	if (m_pDibUndo)
	{
		m_pDibUndo->ReleaseContents();
		delete m_pDibUndo;
		m_pDibUndo = NULL;
	}

	m_dibSagome.ReleaseContents();
	m_dibSagome.Detach();

	if (m_hModule)
		FreeLibrary(m_hModule);

	theApp.m_lInstanceCountCImageDlg = 0;

	CEndoxResizableDlg::PostNcDestroy();
	//	delete this;
}

CImageDlg::~CImageDlg(void)
{
	if (m_pDib)
	{
		m_pDib->ReleaseContents();
		delete m_pDib;
		m_pDib = NULL;
	}

	if (m_pDibUndo)
	{
		m_pDibUndo->ReleaseContents();
		delete m_pDibUndo;
		m_pDibUndo = NULL;
	}

	m_dibSagome.ReleaseContents();
	m_dibSagome.Detach();

	if (m_hModule)
		FreeLibrary(m_hModule);

	theApp.m_lInstanceCountCImageDlg = 0; //Gabriel BUG 6225 - Lista DO
	m_pEsamiView->m_pImageDlg = NULL; //Gabriel BUG 6225 - Lista DO
}

BOOL CImageDlg::PreTranslateMessage(MSG* pMsg)
{
	BOOL bReturn = FALSE;

	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam == VK_LEFT) && m_bPrev)
		{
			OnButtonPrev();
			bReturn = TRUE;
		}
		if ((pMsg->wParam == VK_RIGHT) && m_bNext)
		{
			OnButtonNext();
			bReturn = TRUE;
		}

		if ((pMsg->wParam == VK_UP) && m_bPrevTiff)
		{
			OnButtonPrevTiff();
			bReturn = TRUE;
		}
		if ((pMsg->wParam == VK_DOWN) && m_bNextTiff)
		{
			OnButtonNextTiff();
			bReturn = TRUE;
		}
	}

	if (!bReturn)
		bReturn = CEndoxResizableDlg::PreTranslateMessage(pMsg);

	return bReturn;
}

void CImageDlg::InitializeWindow()
{
	CRect	ImgRect;
	int		nDimX;
	int		nDimY;

	m_nTGAWidth = 0;
	m_nTGAHeight = 0;
	m_nDLGWidth = 0;
	m_nDLGHeight = 0;

	m_ctrlImage.GetWindowRect(&ImgRect);
	ScreenToClient(&ImgRect);

	if (m_pDib && m_pDib->IsValidDib())
	{
		// sempre grande 768x576 con le scrollbar
		m_nTGAWidth = m_pDib->Width();
		m_nTGAHeight = m_pDib->Height();
		m_nDLGWidth = ImgRect.Width();
		m_nDLGHeight = ImgRect.Height();
	}

	PrepareRectangle();
	PrepareDataImage();

	switch (m_nShowMode)
	{
	case 0: // 1:1
	{
		nDimX = max(0, m_nTGAWidth - m_nDLGWidth);
		nDimY = max(0, m_nTGAHeight - m_nDLGHeight);

		m_ctrlScrollH.SetScrollRange(0, nDimX);
		m_ctrlScrollV.SetScrollRange(0, nDimY);
		m_ctrlScrollH.SetScrollPos(0);
		m_ctrlScrollV.SetScrollPos(0);
		m_ctrlScrollH.EnableWindow(nDimX > 0);
		m_ctrlScrollV.EnableWindow(nDimY > 0);

		break;
	}
	case 1: // Fit in window
	{
		m_ctrlScrollH.SetScrollRange(0, 0);
		m_ctrlScrollV.SetScrollRange(0, 0);
		m_ctrlScrollH.SetScrollPos(0);
		m_ctrlScrollV.SetScrollPos(0);
		m_ctrlScrollH.EnableWindow(FALSE);
		m_ctrlScrollV.EnableWindow(FALSE);

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

void CImageDlg::PrepareRectangle()
{
	CRect 	ScreenRect(0, 0, m_nDLGWidth, m_nDLGHeight);
	CRect 	DibRect(0, 0, m_nTGAWidth, m_nTGAHeight);
	CRect 	FitRect;

	CRect	ImgRect;
	m_ctrlImage.GetWindowRect(&ImgRect);
	ScreenToClient(&ImgRect);
	ScreenRect.OffsetRect(ImgRect.left, ImgRect.top);

	switch (m_nShowMode)
	{
	case 0: // 1:1
	{
		if (m_nDLGWidth > m_nTGAWidth)
		{
			// centraggio sull'asse x...
			ScreenRect.left += (ScreenRect.Width() - DibRect.Width()) / 2;
			ScreenRect.right = ScreenRect.left + DibRect.Width();
		}

		if (m_nDLGHeight > m_nTGAHeight)
		{
			// centraggio sull'asse y...
			ScreenRect.top += (ScreenRect.Height() - DibRect.Height()) / 2;
			ScreenRect.bottom = ScreenRect.top + DibRect.Height();
		}

		break;
	}
	case 1: // Fit in window
	{
		// in altezza in base alla larghezza
		FitRect.left = 0;
		FitRect.top = 0;
		FitRect.right = FitRect.left + m_nDLGWidth;
		FitRect.bottom = FitRect.top + (int)(((double)m_nTGAHeight * (double)m_nDLGWidth) / ((double)m_nTGAWidth));
		// se la proporzione è inversa....
		if (FitRect.Height() > m_nDLGHeight)
		{
			// in larghezza in base all'altezza
			FitRect.bottom = FitRect.top + m_nDLGHeight;
			FitRect.right = FitRect.left + (int)(((double)m_nTGAWidth * (double)m_nDLGHeight) / ((double)m_nTGAHeight));
		}

		// centraggio sulla pagina...
		ScreenRect.left += (ScreenRect.Width() - FitRect.Width()) / 2;
		ScreenRect.right = ScreenRect.left + FitRect.Width();
		ScreenRect.top += (ScreenRect.Height() - FitRect.Height()) / 2;
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

void CImageDlg::PrepareDataImage()
{
	m_bIsSelect = FALSE;

	POSITION pos = CFileBmp::GetFirstSelectedPos();
	while (pos != NULL)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos);

		if (pSel && (pSel->m_bIsGlobal == m_bIsAlbumGlobal) && (pSel->m_lID == m_lID))
		{
			m_bIsSelect = TRUE;
			break;
		}
	}
}

void CImageDlg::SelectThisImage()
{
	if (m_bIsAlbumGlobal == FALSE)
	{
		BOOL bFound = FALSE;

		POSITION pos = CFileBmp::GetFirstSelectedPos();
		while (pos != NULL)
		{
			POSITION posSel = pos;
			CObSelect* pSel = CFileBmp::GetNextSelected(pos);

			if ((pSel != NULL) && (pSel->m_bIsGlobal == m_bIsAlbumGlobal) && (pSel->m_lID == m_lID))
			{
				CFileBmp::DeletePrinter(pSel);

				CFileBmp::m_listSelected.RemoveAt(posSel);
				delete pSel;

				bFound = TRUE;
				break;
			}
		}

		m_bIsSelect = FALSE;

		if (bFound == FALSE)
		{
			CObSelect* pItem = new CObSelect(NULL);
			if (pItem != NULL)
			{
				pItem->m_lID = m_lID;
				pItem->m_bIsGlobal = m_bIsAlbumGlobal;
				pItem->m_iType = m_iType;
				pItem->m_strDescription = "";
				pItem->m_lPaziente = m_lPaziente;
				pItem->m_lEsame = m_lEsame;

				CFileBmp::m_listSelected.AddTail(pItem);

				m_bIsSelect = TRUE;
			}
		}
	}
}

void CImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_ctrlStaticView);
	DDX_Control(pDX, IDC_SHOW_1, m_ctrlButtonShow1);
	DDX_Control(pDX, IDC_SHOW_2, m_ctrlButtonShow2);
	DDX_Control(pDX, IDC_SHOW_3, m_ctrlButtonShow3);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDC_ENHANCE, m_ctrlButtonEnhance);

	DDX_Control(pDX, IDC_VSCROLL, m_ctrlScrollV);
	DDX_Control(pDX, IDC_HSCROLL, m_ctrlScrollH);
	DDX_Control(pDX, IDC_IMAGE, m_ctrlImage);
	DDX_Radio(pDX, IDC_SHOW_1, m_nShowMode);

	DDX_Control(pDX, IDC_STATIC_SAGOMA, m_ctrlFrameSagoma);
	DDX_Control(pDX, IDC_STATIC_SEDE1, m_ctrlFrameSede);
	DDX_Control(pDX, IDC_STATIC_SEDE2, m_ctrlStaticSede);

	DDX_Control(pDX, IDC_BUTTON_PRINTONE, m_PrintOneButton);
	DDX_Control(pDX, IDC_BUTTON_PRINTALL, m_PrintAllButton);
	DDX_Control(pDX, IDC_BUTTON_ESPORTAFRAME, m_ExportFrameButton);

	if (m_nTotPage > 0)
	{
		m_bPrev = (m_nNumPage > 0);
		m_bNext = (m_nNumPage < m_nTotPage);
	}
	else
	{
		m_bPrev = FALSE;
		m_bNext = FALSE;
	}

	m_bPrevTiff = ((m_lTotTiffPages > 1) && (m_lCurTiffPage > 0));
	m_bNextTiff = ((m_lTotTiffPages > 1) && (m_lCurTiffPage < m_lTotTiffPages - 1));

	m_FrstButton.EnableWindow(m_bPrev);
	m_PrevButton.EnableWindow(m_bPrev);
	m_NextButton.EnableWindow(m_bNext);
	m_LastButton.EnableWindow(m_bNext);

	m_PrevTiffButton.ShowWindow(m_bIsMultipage ? SW_SHOW : SW_HIDE);
	m_PrevTiffButton.EnableWindow(m_bPrevTiff);

	GetDlgItem(IDC_STATIC_FRAMES)->ShowWindow(m_bIsMultipage ? SW_SHOW : SW_HIDE);

	m_NextTiffButton.ShowWindow(m_bIsMultipage ? SW_SHOW : SW_HIDE);
	m_NextTiffButton.EnableWindow(m_bNextTiff);

	m_PrintOneButton.ShowWindow(m_bIsMultipage ? SW_SHOW : SW_HIDE);
	m_PrintAllButton.ShowWindow(m_bIsMultipage ? SW_SHOW : SW_HIDE);
	m_ExportFrameButton.ShowWindow(m_bIsMultipage ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDOK)->SetFocus();
}


BEGIN_MESSAGE_MAP(CImageDlg, CEndoxResizableDlg)

	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_HSCROLL()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_VSCROLL()

	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREV, OnButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_PREVTIFF, OnButtonPrevTiff)
	ON_BN_CLICKED(IDC_BUTTON_NEXTTIFF, OnButtonNextTiff)
	ON_BN_CLICKED(IDC_BUTTON_PRINTONE, OnButtonPrintOne)
	ON_BN_CLICKED(IDC_BUTTON_PRINTALL, OnButtonPrintAll)
	ON_BN_CLICKED(IDC_BUTTON_ESPORTAFRAME, OnButtonEsportaFrame)
	ON_BN_CLICKED(IDC_MANTIENI_IMMAGINE, OnButtonMantieniImmagine)

	ON_BN_CLICKED(IDC_PROGRAM, OnCallProgram)
	ON_BN_CLICKED(IDC_CONTRAST_MANUALE, OnContrastManuale)
	ON_BN_CLICKED(IDC_BRIGHT_MANUALE, OnBrightnessManuale)
	ON_BN_CLICKED(IDC_UNDO, OnUndo)
	ON_BN_CLICKED(IDC_SALVA, OnSalva)
	ON_BN_CLICKED(IDC_SALVA_NUOVO, OnSalvaNuovo)
	ON_BN_CLICKED(IDC_CANCELLA, OnCancella)
	ON_BN_CLICKED(IDC_ENHANCE, OnEnhance)
	ON_BN_CLICKED(IDC_SHOW_1, OnChangeShow)
	ON_BN_CLICKED(IDC_SHOW_2, OnChangeShow)
	ON_BN_CLICKED(IDC_SHOW_3, OnChangeShow)
	ON_BN_CLICKED(IDOK, OnCancel)

	ON_COMMAND(IDCANCEL, OnCancel) //Gabriel BUG 6225 - Lista DO
	ON_MESSAGE(EPM_EXAMCHANGED, OnExamChanged) //Gabriel BUG 6225 - Lista DO
END_MESSAGE_MAP()

BOOL CImageDlg::OnInitDialog()
{
	m_hModule = NULL;

	if (theApp.m_bVisAbilita)
	{
#ifdef _DEBUG
		m_hModule = ::LoadLibrary("xrclientd.dll");
#else
		m_hModule = ::LoadLibrary("xrclient.dll");
#endif
		GetDlgItem(IDC_MANTIENI_IMMAGINE)->ShowWindow(SW_SHOW);
	}

	if (m_hModule)
	{
		XRClient_Play = (PLAYPTR)GetProcAddress(m_hModule, "Play");
		XRClient_StopPlay = (STOPPLAYPTR)GetProcAddress(m_hModule, "StopPlay");
		XRClient_EnableVideoOutput = (ENABLEVIDEOOUTPUTPTR)GetProcAddress(m_hModule, "EnableVideoOutput");
		XRClient_GetErrorOccurred = (GETERROROCCURREDPTR)GetProcAddress(m_hModule, "GetErrorOccurred");
		XRClient_GetVideoInput = (GETVIDEOINPUTPTR)GetProcAddress(m_hModule, "GetVideoInput");
	}

	if (theApp.m_bVisAbilitaMonitor && XRClient_GetVideoInput)
		theApp.m_iPrevInput = XRClient_GetVideoInput(theApp.m_sVisPortaMonitor);

	//Sleep(1000);

	if (theApp.m_bVisAbilitaMonitor && XRClient_EnableVideoOutput && !XRClient_EnableVideoOutput(theApp.m_sVisPortaMonitor, _HD_SDI1))
	{
		TCHAR szError[2048];
		ZeroMemory(szError, sizeof(char) * 2048);
		XRClient_GetErrorOccurred(szError);
		CString sError;
		sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
		theApp.AfxMessageBoxEndo(sError);
	}

	m_FrstButton.AutoLoad(IDC_BUTTON_FIRST, this);
	m_PrevButton.AutoLoad(IDC_BUTTON_PREV, this);
	m_NextButton.AutoLoad(IDC_BUTTON_NEXT, this);
	m_LastButton.AutoLoad(IDC_BUTTON_LAST, this);
	m_PrevTiffButton.AutoLoad(IDC_BUTTON_PREVTIFF, this);
	m_NextTiffButton.AutoLoad(IDC_BUTTON_NEXTTIFF, this);
	// m_PrintOneButton.AutoLoad(IDC_BUTTON_PRINTONE, this);
	// m_PrintAllButton.AutoLoad(IDC_BUTTON_PRINTALL, this);
	// m_ExportFrameButton.AutoLoad(IDC_BUTTON_ESPORTAFRAME, this);

	m_btnUpdate.AutoLoad(IDC_SALVA, this);
	m_btnCancel.AutoLoad(IDC_CANCELLA, this);
	m_btnSalNuo.AutoLoad(IDC_SALVA_NUOVO, this);
	m_btnElabor.AutoLoad(IDC_PROGRAM, this);

	m_btnBright.AutoLoad(IDC_BRIGHT_MANUALE, this);
	m_btnContra.AutoLoad(IDC_CONTRAST_MANUALE, this);
	m_btnUndLas.AutoLoad(IDC_UNDO, this);

	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_STATIC_LINE1, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDOK, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_STATIC_LINE2, CSize(0, 0), CSize(0, 100));
	AddAnchor(IDC_IMAGE, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_VSCROLL, CSize(100, 0), CSize(100, 100));
	AddAnchor(IDC_HSCROLL, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_COMMENTO, CSize(0, 0), CSize(0, 100));
	AddAnchor(IDC_MANTIENI_IMMAGINE, CSize(0, 100), CSize(0, 100));

	if (theApp.m_nApplication == PRG_DERMOX)
	{
		AddAnchor(IDC_STATIC_SAGOMA, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDC_STATIC_SEDE1, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDC_STATIC_SEDE2, CSize(0, 100), CSize(0, 100));

		m_ctrlStaticSede.SetFont(&theApp.m_fontBold);

		m_ctrlFrameSagoma.ShowWindow(SW_SHOW);
		m_ctrlFrameSede.ShowWindow(SW_SHOW);
		m_ctrlStaticSede.ShowWindow(SW_SHOW);

		char szPathImm[MAX_PATH];
		char szPathMin[MAX_PATH];
		if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
		{
			CString sFileSagome;
			sFileSagome.Format("%s\\Organ\\sagome.org", szPathImm);

			if (_access(sFileSagome, 00) == 0)
			{
				HBITMAP hBit;

				if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(sFileSagome, &hBit) > 0)
				{
					if (hBit != INVALID_HANDLE_VALUE)
					{
						if (!m_dibSagome.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE))
						{
							m_dibSagome.ReleaseContents();
							m_dibSagome.Detach();
						}
					}
				}
				DeleteObject(hBit);
			}
			else
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_FILE_SAGOME_NON_TROVATO), sFileSagome);
				theApp.AfxMessageBoxEndo(strError);
				OnCancel();
			}
		}
		else
		{
			ASSERT(FALSE);
		}
	}

	theApp.LocalizeDialog(this, CImageDlg::IDD, "ImageDlg");

	BOOL bEnable = (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto;

	m_btnUpdate.EnableWindow(bEnable);
	m_btnCancel.EnableWindow(bEnable);
	m_btnSalNuo.EnableWindow(bEnable);
	m_btnElabor.EnableWindow(bEnable);

	m_btnBright.EnableWindow(bEnable);
	m_btnContra.EnableWindow(bEnable);
	m_btnUndLas.EnableWindow(bEnable);
	GetDlgItem(IDC_ENHANCE)->EnableWindow(bEnable);

	m_PrintOneButton.EnableWindow(bEnable);
	m_PrintAllButton.EnableWindow(bEnable);
	m_ExportFrameButton.EnableWindow(bEnable);

	EnableToolTips(TRUE);

	BOOL bResult = FALSE;

	CImgList listImg;

	m_nNumPage = -1;
	BeginWaitCursor();
	//m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);

	// Sandro 22/10/2007 per eliminare i filmati (non visualizzabili) dalla lista di documenti //

	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	int nImages = m_pEsamiView->m_pImgManager->GetImgList(&listImg);
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_lPaziente, m_lEsame, nImages, "CImageDlg::OnInitDialog");

	POSITION pos = listImg.GetHeadPosition();
	while (pos != NULL)
	{
		IMG imgTemp = listImg.GetAt(pos);
		if ((imgTemp.type != _image_) && (imgTemp.type != _mptiff_))
		{
			POSITION posTemp = pos;
			listImg.GetNext(pos);
			listImg.RemoveAt(posTemp);
		}
		else
		{
			listImg.GetNext(pos);
		}
	}
	m_nTotPage = listImg.GetCount() - 1;
	// fine Sandro 22/10/2007 //

	m_ImgListOrgani = listImg;


	CaricaPunti();
	EndWaitCursor();

	BOOL bFound = FALSE;
	if (m_pDib != NULL)
	{
		POSITION pos = m_ImgListOrgani.GetHeadPosition();

		while (pos != NULL)
		{
			m_nNumPage++;

			if (m_lID == m_ImgListOrgani.GetAt(pos).img.lID)
			{
				bFound = TRUE;
				break;
			}

			m_ImgListOrgani.GetNext(pos);
		}
	}

	// se não encontrou a imagem clicada, selecionada, abre a 1a delas
	if (!bFound)
	{
		m_nNumPage = 0;
		POSITION pos = m_ImgListOrgani.GetHeadPosition();
	}

	if ((m_nNumPage >= 0) && (m_nNumPage <= m_nTotPage))
	{
		bResult = CaricaImmagine();
	}

	if (bResult == FALSE)
	{
		EndDialog(IDCANCEL);

		//Gabriel BUG 6225 - Lista DO
		if (!theApp.m_bConfigFormRefertoBtnImgAutomated)
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_IMMAGINI_VUOTO), MB_ICONINFORMATION);

		return FALSE;
	}

	if (m_pDibUndo != NULL)
	{
		*m_pDibUndo = *m_pDib;
	}

	UpdateData(FALSE);

	//Gabriel BUG 6225 - Lista DO
	if (m_bIsReferto)
	{
		if (theApp.m_sConfigFormRefertoBtnImgOpenWhere == "MONITOR #02")	// 'DEFAULT' OU 'MONITOR #02'
			CenterWndInSecondScreen(this);
		else
			CenterWndInFirstScreen(this);
	}
	else
	{
		if (theApp.m_sConfigFormAlbumImgBtnImgOpenWhere == "MONITOR #02")	// 'DEFAULT' OU 'MONITOR #02'
			CenterWndInSecondScreen(this);
		else
			CenterWndInFirstScreen(this);
	}

	InitializeWindow();

	UpdateData(FALSE);

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_00)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_01)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_02)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_VIEW)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_03)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_FRAMES)->SetFont(&theApp.m_fontBold);

	m_bPrev = FALSE;
	m_bNext = FALSE;

	m_bInit = TRUE;

	//Gabriel BUG 6225 - Lista DO FIX
	if (theApp.m_bAbreImgTelaCheia && theApp.m_bAtivaListaDO)
		OpenImgFullscreen();

	return TRUE;
}

void CImageDlg::OnOK()
{
	if (m_bSaveImage)
	{
		int nResponse = theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMAGEDLG_IMAGE_MOD), MB_YESNOCANCEL);

		if (nResponse == IDCANCEL)
			return;

		if (nResponse == IDYES)
			if (m_bSaveImage)
				SalvaImmagine();
	}

	if (!m_bError && !m_bMantieniImmagine)
	{
		if (XRClient_StopPlay && !XRClient_StopPlay(theApp.m_sVisIp, theApp.m_lVisPorta))
		{
			TCHAR szError[2048];
			ZeroMemory(szError, sizeof(char) * 2048);
			XRClient_GetErrorOccurred(szError);
			CString sError;
			sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
			theApp.AfxMessageBoxEndo(sError);
		}

		if (theApp.m_bVisAbilitaMonitor && XRClient_EnableVideoOutput && !XRClient_EnableVideoOutput(theApp.m_sVisPortaMonitor, theApp.m_iPrevInput))
		{
			TCHAR szError[2048];
			ZeroMemory(szError, sizeof(char) * 2048);
			XRClient_GetErrorOccurred(szError);
			CString sError;
			sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
			theApp.AfxMessageBoxEndo(sError);
		}
	}

	//Gabriel BUG 6225 - Lista DO
	if (!m_bDoModal)
		DestroyWindow();
	else
		CEndoxResizableDlg::OnOK();
}

void CImageDlg::OnMove(int x, int y)
{
	m_bRedrawBack = TRUE;

	CEndoxResizableDlg::OnMove(x, y);
}

#define RAGGIO_PUNTO_2 3

void CImageDlg::OnPaint()
{
	CPaintDC dc(this);

	if (m_pDib && m_pDib->IsValidDib())
	{
		CPoint	ptOffset;
		CRect	rectSource;
		CRect	ImgRect;

		m_ctrlImage.GetWindowRect(&ImgRect);
		ScreenToClient(&ImgRect);

		switch (m_nShowMode)
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

			rectSource.left = ptOffset.x;
			rectSource.top = ptOffset.y;
			rectSource.right = min(rectSource.left + ImgRect.Width(), m_DibRectSource.Width());
			rectSource.bottom = min(rectSource.top + ImgRect.Height(), m_DibRectSource.Height());

			m_pDib->PaintDIB(dc.GetSafeHdc(), m_DibRectScreen, rectSource, 0);

			break;
		}
		case 1: // Fit in window
		{
			if (m_nDLGWidth != m_nTGAWidth || m_nDLGHeight != m_nTGAHeight)
			{
				::PatBlt(dc.GetSafeHdc(), ImgRect.left, ImgRect.top, m_nDLGWidth, m_nDLGHeight, BLACKNESS);

				m_bRedrawBack = FALSE;
			}

			m_pDib->PaintDIB(dc.GetSafeHdc(), m_DibRectScreen, m_DibRectSource, 0);

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

				m_pDib->PaintDIB(dc.GetSafeHdc(), m_DibRectScreen, rectSource, 0);
			}
			else
			{
				// fit in window //

				if ((m_nDLGWidth != m_nTGAWidth) || (m_nDLGHeight != m_nTGAHeight))
				{
					::PatBlt(dc.GetSafeHdc(), ImgRect.left, ImgRect.top, m_nDLGWidth, m_nDLGHeight, BLACKNESS);
					m_bRedrawBack = FALSE;
				}

				m_pDib->PaintDIB(dc.GetSafeHdc(), m_DibRectScreen, m_DibRectSource, 0);
			}

			break;
		}
		}

		if (m_bIsSelect)
		{
			HICON hIcon;

			hIcon = (HICON)::LoadImage(AfxGetResourceHandle(),
				MAKEINTRESOURCE(IDI_SELECT),
				IMAGE_ICON,
				48,
				48,
				LR_DEFAULTCOLOR);
			::DrawIconEx(dc.GetSafeHdc(),
				ImgRect.left,
				ImgRect.top,
				hIcon,
				48,
				48,
				1,
				NULL,
				DI_NORMAL);
		}
	}

	// disegno la dib //
	if (theApp.m_nApplication == PRG_DERMOX)
	{
		m_rectPaintSagoma = m_dibSagome.PaintDIBSagome(&dc, m_rectFrameSagoma);

		if ((m_ptSagome.x >= 0) && (m_ptSagome.y >= 0))
		{
			dc.SetBkMode(TRANSPARENT);

			CPen penSel(PS_SOLID, 1, RGB_RED);
			CPen* pOldPen = dc.SelectObject(&penSel);

			CBrush brushSel(RGB_RED);
			CBrush* pOldBrush = dc.SelectObject(&brushSel);

			COLORREF crOldColor = dc.SetTextColor(RGB_RED);

			CPoint ptToDraw = ImageToScreen(m_ptSagome);
			CRect rectTemp(ptToDraw.x - RAGGIO_PUNTO_2, ptToDraw.y - RAGGIO_PUNTO_2, ptToDraw.x + RAGGIO_PUNTO_2, ptToDraw.y + RAGGIO_PUNTO_2);

			dc.Ellipse(rectTemp);

			if (theApp.m_bNumeriSuImmagineSagoma && (m_lNumeroDermox > 0))
			{
				CString sTemp;
				sTemp.Format("%li", m_lNumeroDermox);

				CFont* pOldFont = dc.SelectObject(&theApp.m_fontBold);
				int nOldBkMode = dc.SetBkMode(OPAQUE);
				dc.TextOut(ptToDraw.x + 4, ptToDraw.y - 9, sTemp);
				dc.SetBkMode(nOldBkMode);
				dc.SelectObject(pOldFont);
			}

			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
			dc.SetTextColor(crOldColor);
		}
	}
}

#undef RAGGIO_PUNTO_2

void CImageDlg::OnCallProgram()
{
	if (m_bSaveImage)
	{
		int nResponse = theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMAGEDLG_IMAGE_MOD), MB_YESNOCANCEL);

		if (nResponse == IDCANCEL)
			return;

		if (nResponse == IDYES)
			if (m_bSaveImage)
				SalvaImmagine();
	}

	if (m_pDib && m_pDib->IsValidDib())
	{
		CString strBuffer;
		strBuffer.Format("%s\\MicroImage\\MicroImage.exe %s", theApp.m_sDirProg, m_pEsamiView->m_pImgManager->GetFullPath(m_lID));

		// Utilizziamo createProcess così funziona sia con Microimage che con paint.net - Simone 08/04/2010
		// nResult = WinExec(strBuffer, SW_SHOW);

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (!CreateProcess(NULL, strBuffer.GetBuffer(MAX_PATH), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			LPVOID lpMsgBuf;
			if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
				theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
			else
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
			LocalFree(lpMsgBuf);
			strBuffer.ReleaseBuffer();

			return;
		}

		strBuffer.ReleaseBuffer();

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		//if (nResult >= 32)
		//{
		if (m_pDib)
		{
			m_pDib->ReleaseContents();
			delete m_pDib;
			m_pDib = NULL;
		}

		if (m_pDibUndo)
		{
			m_pDibUndo->ReleaseContents();
			delete m_pDibUndo;
			m_pDibUndo = NULL;
		}

		MSG	 msg;
		BOOL bContinue = TRUE;
		while (bContinue)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == MSG_ELABOR_BMP)
					bContinue = FALSE;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
				Sleep(25);
			}
		}

		CImgIDList IdList;
		IdList.AddTail(m_lID);
		m_pEsamiView->m_pImgManager->RebuildThumb(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, &IdList, FORM_MINI);
		SalvaImmagine(); //Gabriel - BUG Refresh álbum
		m_bRequeryImage = TRUE;

		OnCancel(); //Gabriel - BUG Refresh álbum
		//EndDialog(IDOK);
		/*}
		else
		{
		CString strError;

		switch (nResult)
		{
		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
		strError = theApp.GetMessageString(IDS_IMAGEDLG_FILE_NOT_FOUND);
		break;
		default:
		strError.Format(theApp.GetMessageString(IDS_IMAGEDLG_GENERIC_ERR), nResult);
		}

		theApp.AfxMessageBoxEndo(strError);
		}*/
	}
}

void CImageDlg::AutoRedraw()
{
	CRect ImgRect;

	m_ctrlImage.GetWindowRect(&ImgRect);
	ScreenToClient(&ImgRect);

	RedrawWindow(&ImgRect, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW);
}

BOOL CImageDlg::GoFirst()
{
	BOOL bResult = TRUE;

	m_nNumPage = 0;
	m_lCurTiffPage = 0;

	bResult = CaricaImmagine();

	if (bResult == TRUE)
	{
		if (m_pDibUndo)
			*m_pDibUndo = *m_pDib;

		InitializeWindow();

		AutoRedraw();
	}

	UpdateData(FALSE);

	m_bSaveImage = FALSE;
	m_bSaveUndo = FALSE;

	return bResult;
}

BOOL CImageDlg::GoPrev()
{
	BOOL bResult = TRUE;

	m_nNumPage--;
	m_lCurTiffPage = 0;

	bResult = CaricaImmagine();

	if (bResult)
	{
		if (m_pDibUndo)
			*m_pDibUndo = *m_pDib;

		InitializeWindow();

		AutoRedraw();
	}
	else
	{
		UpdateData(FALSE);

		if (m_bPrev)
			return GoPrev();

		return FALSE;
	}

	UpdateData(FALSE);

	m_bSaveImage = FALSE;
	m_bSaveUndo = FALSE;

	return bResult;
}

BOOL CImageDlg::GoNext()
{
	BOOL bResult = TRUE;

	m_nNumPage++;
	m_lCurTiffPage = 0;

	bResult = CaricaImmagine();

	if (bResult)
	{
		if (m_pDibUndo)
			*m_pDibUndo = *m_pDib;

		InitializeWindow();

		AutoRedraw();
	}
	else
	{
		UpdateData(FALSE);

		if (m_bNext)
			return GoNext();

		return FALSE;
	}

	UpdateData(FALSE);

	m_bSaveImage = FALSE;
	m_bSaveUndo = FALSE;

	return bResult;
}

BOOL CImageDlg::GoLast()
{
	BOOL bResult = TRUE;

	m_nNumPage = m_nTotPage;
	m_lCurTiffPage = 0;

	bResult = CaricaImmagine();

	if (bResult == TRUE)
	{
		if (m_pDibUndo)
			*m_pDibUndo = *m_pDib;

		InitializeWindow();

		AutoRedraw();
	}

	UpdateData(FALSE);

	m_bSaveImage = FALSE;
	m_bSaveUndo = FALSE;

	return bResult;
}

void CImageDlg::OnButtonFirst()
{
	BeginWaitCursor();

	if (m_bSaveImage)
	{
		int nResponse = theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMAGEDLG_IMAGE_MOD), MB_YESNOCANCEL);

		if (nResponse == IDCANCEL)
			return;

		if (nResponse == IDYES)
			if (m_bSaveImage)
				SalvaImmagine();
	}
	GoFirst();

	EndWaitCursor();
}

void CImageDlg::OnButtonPrev()
{
	BeginWaitCursor();

	if (m_bSaveImage)
	{
		int nResponse = theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMAGEDLG_IMAGE_MOD), MB_YESNOCANCEL);

		if (nResponse == IDCANCEL)
			return;

		if (nResponse == IDYES)
			if (m_bSaveImage)
				SalvaImmagine();
	}
	GoPrev();

	EndWaitCursor();
}

void CImageDlg::OnButtonNext()
{
	BeginWaitCursor();

	if (m_bSaveImage)
	{
		int nResponse = theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMAGEDLG_IMAGE_MOD), MB_YESNOCANCEL);

		if (nResponse == IDCANCEL)
			return;

		if (nResponse == IDYES)
			if (m_bSaveImage)
				SalvaImmagine();
	}
	GoNext();

	EndWaitCursor();
}

void CImageDlg::OnButtonLast()
{
	BeginWaitCursor();

	if (m_bSaveImage)
	{
		int nResponse = theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMAGEDLG_IMAGE_MOD), MB_YESNOCANCEL);

		if (nResponse == IDCANCEL)
			return;

		if (nResponse == IDYES)
			if (m_bSaveImage)
				SalvaImmagine();
	}
	GoLast();

	EndWaitCursor();
}

void CImageDlg::OnButtonPrevTiff()
{
	BeginWaitCursor();

	m_lCurTiffPage--;
	if (CaricaImmagine())
	{
		if (m_pDibUndo)
			*m_pDibUndo = *m_pDib;

		InitializeWindow();

		AutoRedraw();
	}
	UpdateData(FALSE);

	EndWaitCursor();
}

void CImageDlg::OnButtonNextTiff()
{
	BeginWaitCursor();

	m_lCurTiffPage++;
	if (CaricaImmagine())
	{
		if (m_pDibUndo)
			*m_pDibUndo = *m_pDib;

		InitializeWindow();

		AutoRedraw();
	}
	UpdateData(FALSE);

	EndWaitCursor();
}

void CImageDlg::OnButtonPrintOne()
{
	// cancello la lista delle immagini selezionate //
	CFileBmp::DeleteListSelected(m_bIsAlbumGlobal);

	// seleziono SOLO questa immagine //
	SelectThisImage();

	// cambio il numero di immagini per pagina, impostandolo ad 1 //
	int nOldTypePrintImage = theApp.m_nStampaImmaginiTipoDiStampa;
	theApp.m_nStampaImmaginiTipoDiStampa = 0; // <-- una immagine per pagina //

	// imposto la stampa di un singolo frame //
	theApp.m_lOnlyThisFrame = m_lCurTiffPage;

	// lancio la stampa //
	m_pEsamiView->SendMessage(WM_COMMAND, ID_FILE_STAMPAIMMAGINI, NULL);

	// azzero la stampa di un singolo frame //
	theApp.m_lOnlyThisFrame = -1;

	// ripristino il numero di immagini per pagina //
	theApp.m_nStampaImmaginiTipoDiStampa = nOldTypePrintImage;

	// deseleziono tutte le immagini //
	CFileBmp::DeleteListSelected(m_bIsAlbumGlobal);

	// riaggiorno l'immagine //
	m_bRequeryImage = TRUE;
	m_bRedrawBack = TRUE;
	AutoRedraw();
}

void CImageDlg::OnButtonPrintAll()
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

void CImageDlg::OnButtonEsportaFrame()
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

			CCustomDate dataTemp(m_pEsamiView->m_pEsamiSet->m_lData);

			strTemp.Format("%s%s %s %02d.%02d.%d", theApp.m_sExportFolder, m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome, dataTemp.GetDay(), dataTemp.GetMonth(), dataTemp.GetYear());
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
}

// Marvel Carvalho - Bug 4269 Dialog ImageSimple2Dlg ignora album com 1 imagem
void CImageDlg::UpdateWindowTitle(CString p_sTitle)
{
	CString sWindowTitle;
	sWindowTitle.Format("Imagem (%d / %d) %s", m_nNumPage + 1, m_nTotPage + 1, p_sTitle); // Marvel Carvalho - Bug 4269 Dialog ImageSimple2Dlg ignora album com 1 imagem
	SetWindowText(sWindowTitle);
}

void CImageDlg::OnButtonMantieniImmagine()
{
	POSITION pos = m_ImgListOrgani.FindIndex(m_nNumPage);

	if (pos && m_bMantieniImmagine)
	{
		CString sFullPath = m_pEsamiView->m_pImgManager->GetFullPath(m_ImgListOrgani.GetAt(pos).img.lID);
		UpdateWindowTitle(sFullPath); // Marvel Carvalho - Bug 4269 Dialog ImageSimple2Dlg ignora album com 1 imagem

		if (XRClient_Play)
		{
			sFullPath.Replace("\\", ":");

			if (!XRClient_Play(sFullPath, theApp.m_sVisIp, theApp.m_lVisPorta))
			{
				TCHAR szError[2048];
				ZeroMemory(szError, sizeof(char) * 2048);
				XRClient_GetErrorOccurred(szError);
				CString sError;
				sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
				theApp.AfxMessageBoxEndo(sError);
				m_bError = TRUE;
			}
		}
	}

	m_bMantieniImmagine = TRUE;
}

void CImageDlg::OnEnhance()
{
	if (m_pDib && m_pDib->IsValidDib())
	{
		if (m_pDib->IsRGB() || m_pDib->Is256Index())
		{
			*m_pDibUndo = *m_pDib;

			Enhance(&m_pDib);

			m_bSaveUndo = m_bSaveImage;
			m_bSaveImage = TRUE;

			AutoRedraw();
		}
	}
}

void CImageDlg::OnContrastManuale()
{
	if (m_pDib && m_pDib->IsValidDib())
	{
		if (m_pDib->Is256Index())
		{
			CContrastDlg	dlg(this, m_pDib, NULL);

			if (dlg.DoModal() == IDOK)
			{
				CRect rect(0, 0, m_pDib->Width() - 1, m_pDib->Height() - 1);

				BeginWaitCursor();
				ScambiaDib(&m_pDib, &m_pDibUndo);

				DoContrast(g_nBlackLev, g_nWhiteLev, rect, m_pDibUndo, m_pDib, NULL);

				EndWaitCursor();

				m_bSaveUndo = m_bSaveImage;
				m_bSaveImage = TRUE;
			}
		}
		else
		{
			if (m_pDib->IsRGB())
			{
				CContrastRGBDlg	dlg(this, m_pDib, NULL);

				if (dlg.DoModal() == IDOK)
				{
					CRect rect(0, 0, m_pDib->Width() - 1, m_pDib->Height() - 1);

					BeginWaitCursor();
					ScambiaDib(&m_pDib, &m_pDibUndo);

					g_nLastUse = dlg.m_nIsRGB;
					if (dlg.m_nIsRGB == 0)
						DoContrastRGB(g_nContrastMinLev[0], g_nContrastMaxLev[0], rect, m_pDibUndo, m_pDib, NULL);
					else
						DoContrastRGB(g_nContrastMinLev[1], g_nContrastMaxLev[1],
						g_nContrastMinLev[2], g_nContrastMaxLev[2],
						g_nContrastMinLev[3], g_nContrastMaxLev[3],
						rect, m_pDibUndo, m_pDib, NULL);
					EndWaitCursor();

					m_bSaveUndo = m_bSaveImage;
					m_bSaveImage = TRUE;
				}
			}
		}
		m_bRedrawBack = TRUE;
		AutoRedraw();
	}
}

void CImageDlg::OnBrightnessManuale()
{
	if (m_pDib && m_pDib->IsValidDib())
	{
		CBrightnessDlg	dlg(this, &m_pDib, &m_pDibUndo);

		if (dlg.DoModal() == IDOK)
		{
			m_bSaveUndo = m_bSaveImage;
			m_bSaveImage = TRUE;
		}

		m_bRedrawBack = TRUE;
		AutoRedraw();
	}
}

void CImageDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CEndoxResizableDlg::OnHScroll(nSBCode, nPos, pScrollBar);

	////MOVIMENTO EFFETTIVO
	int Min, Max, OldPos, NewPos;

	pScrollBar->GetScrollRange(&Min, &Max);
	OldPos = pScrollBar->GetScrollPos();

	switch (nSBCode)
	{
	case SB_LEFT:
		NewPos = max(Min, OldPos - 1);
		break;

	case SB_RIGHT:
		NewPos = min(Max, OldPos + 1);
		break;

	case SB_LINELEFT:
		NewPos = max(Min, OldPos - 1);
		break;

	case SB_LINERIGHT:
		NewPos = min(Max, OldPos + 1);
		break;

	case SB_PAGELEFT:
		NewPos = max(Min, OldPos - 10);
		break;

	case SB_PAGERIGHT:
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

void CImageDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CEndoxResizableDlg::OnVScroll(nSBCode, nPos, pScrollBar);

	////MOVIMENTO EFFETTIVO
	int Min, Max, OldPos, NewPos;

	pScrollBar->GetScrollRange(&Min, &Max);
	OldPos = pScrollBar->GetScrollPos();

	switch (nSBCode)
	{
	case SB_LEFT:
		NewPos = max(Min, OldPos - 1);
		break;

	case SB_RIGHT:
		NewPos = min(Max, OldPos + 1);
		break;

	case SB_LINELEFT:
		NewPos = max(Min, OldPos - 1);
		break;

	case SB_LINERIGHT:
		NewPos = min(Max, OldPos + 1);
		break;

	case SB_PAGELEFT:
		NewPos = max(Min, OldPos - 10);
		break;

	case SB_PAGERIGHT:
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
		AutoRedraw();
}

void CImageDlg::OnUndo()
{
	if (m_pDib && m_pDib->IsValidDib())
	{
		BOOL bTemp = m_bSaveUndo;
		m_bSaveUndo = m_bSaveImage;
		m_bSaveImage = bTemp;

		ScambiaDib(&m_pDib, &m_pDibUndo);

		AutoRedraw();
	}
}

void CImageDlg::OnSalva()
{
	SalvaImmagine();
}

void CImageDlg::OnCommentoUpdate()
{
	m_bSaveImage = TRUE;
}

void CImageDlg::SalvaImmagine()
{
	if (m_bSaveImage)
	{
		if (m_pDib && m_pDib->IsValidDib())
		{
			UpdateData(TRUE);

			HBITMAP hBitmap;

			BeginWaitCursor();

			hBitmap = m_pDib->BitmapFromDib(GetDC()->m_hDC, NULL, DIB_PAL_COLORS);
			if (hBitmap != NULL)
			{
				if (m_pEsamiView->m_pImgManager->UpdateImg(m_lID, hBitmap, FORM_IMM) == TRUE)
				{
					CImgIDList IdList;
					IdList.AddTail(m_lID);

					m_pEsamiView->m_pImgManager->RebuildThumb(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, &IdList, FORM_MINI);

					m_bSaveImage = FALSE;
					m_bSaveUndo = FALSE;
					m_bRequeryImage = TRUE;
				}

				DeleteObject(hBitmap);
			}

			EndWaitCursor();
		}
	}

	m_pParentWnd->SendMessage(MSG_REFRESH_ALBUM); //Gabriel - BUG Refresh álbum
}

void CImageDlg::OnSalvaNuovo()
{
	if (m_pDib && m_pDib->IsValidDib())
	{
		UpdateData(TRUE);

		BeginWaitCursor();

		HBITMAP hBitmap = m_pDib->BitmapFromDib(GetDC()->m_hDC, NULL, DIB_PAL_COLORS);
		if (hBitmap != NULL)
		{
			m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);

			if (m_pEsamiView->m_pImgManager->ImportImg(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, hBitmap, FORM_IMM, FORM_MINI, FALSE) == TRUE)
			{
				m_bSaveImage = FALSE;
				m_bSaveUndo = FALSE;
				m_bRequeryImage = TRUE;

				m_ImgListOrgani.RemoveAll();

				if (m_pDibUndo)
					*m_pDibUndo = *m_pDib;

				CImgList listImg;
				m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);

				DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
				m_nTotPage = m_pEsamiView->m_pImgManager->GetImgList(&listImg) - 1;
				if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
					CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_lPaziente, m_lEsame, m_nTotPage + 1, "CImageDlg::OnSalvaNuovo");

				m_ImgListOrgani = listImg;
				CaricaPunti();
				OnButtonLast();
			}

			DeleteObject(hBitmap);
		}

		EndWaitCursor();
	}

	m_pParentWnd->SendMessage(MSG_REFRESH_ALBUM); //Gabriel - BUG Refresh álbum
}

void CImageDlg::OnCancella()
{
	if (m_pDib && m_pDib->IsValidDib())
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMAGEDLG_CONFIRM), MB_YESNO) == IDYES)
		{
			BOOL bConfirmed;
			CString strDvdLabel;

			m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
			bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);

			if (!bConfirmed)
			{
				CImgIDList ImgIdList;

				ImgIdList.AddHead(m_lID);
				m_pEsamiView->m_pImgManager->DelImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, &ImgIdList);
				ImgIdList.RemoveAll();

				POSITION pos = m_ImgListOrgani.GetHeadPosition();
				while (pos != NULL)
				{
					DeleteObject(m_ImgListOrgani.GetAt(pos).img.hBmp);

					m_ImgListOrgani.GetNext(pos);
				}
				m_ImgListOrgani.RemoveAll();

				if (m_pDibUndo)
					*m_pDibUndo = *m_pDib;

				m_bRequeryImage = TRUE;
				m_bDeselectImage = FALSE;

				if (m_bIsSelect)
					SelectThisImage();

				CImgList listImg;

				BeginWaitCursor();
				m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);

				DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
				m_nTotPage = m_pEsamiView->m_pImgManager->GetImgList(&listImg) - 1;
				if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
					CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_lPaziente, m_lEsame, m_nTotPage + 1, "CImageDlg::OnCancella");

				m_ImgListOrgani = listImg;
				EndWaitCursor();

				GoPrev();
			}
		}
	}
}

void CImageDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CEndoxResizableDlg::OnRButtonDown(nFlags, point);

	if (m_pDib && m_pDib->IsValidDib())
	{
		if (!m_bIsAlbumGlobal)
		{
			SelectThisImage();
			m_bRequeryImage = TRUE;

			m_bRedrawBack = TRUE;
			AutoRedraw();
		}
	}
}

void CImageDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CEndoxResizableDlg::OnLButtonDblClk(nFlags, point);

	if (m_pDib && m_pDib->IsValidDib())
	{
		CRect ImgRect;

		m_ctrlImage.GetWindowRect(&ImgRect);
		ScreenToClient(&ImgRect);

		if (ImgRect.PtInRect(point))
		{
			OpenImgFullscreen(); //Gabriel BUG 6225 - Lista DO FIX
		}
	}
}

// Sandro Gallina - 14/07/2004 //
BOOL CImageDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta < 0) // DOWN
	{
		// girata in giù //
		if (m_bNextTiff)
			OnButtonNextTiff();
		else //if (m_bNext)
			OnButtonNext();

		/*
		if (m_NextButton.IsWindowEnabled() && m_LastButton.IsWindowEnabled())
		OnButtonNext();
		*/
	}
	else // UP
	{
		// girata in su //
		if (m_bPrevTiff)
			OnButtonPrevTiff();
		else //if (m_bPrev)
			OnButtonPrev();

		/*
		if (m_FrstButton.IsWindowEnabled() && m_PrevButton.IsWindowEnabled())
		OnButtonPrev();
		*/
	}

	return CEndoxResizableDlg::OnMouseWheel(nFlags, zDelta, pt);
}

void CImageDlg::OnChangeShow()
{
	UpdateData(TRUE);

	InitializeWindow();

	AutoRedraw();
}

void CImageDlg::SetIDs(long lPaziente, long lEsame, long lID, int iType)
{
	m_lPaziente = lPaziente;
	m_lEsame = lEsame;
	m_lID = lID;
	m_iType = iType;
}

BOOL CImageDlg::CaricaImmagine()
{
	BOOL bReturn = FALSE;
	POSITION pos = m_ImgListOrgani.FindIndex(m_nNumPage);

	m_bError = FALSE;
	m_bIsMultipage = FALSE;

	SetDlgItemText(IDC_STATIC_FRAMES, "");
	m_ctrlStaticSede.SetWindowText("");
	m_ptSagome = CPoint(-1, -1);
	m_lNumeroDermox = -1;

	if (pos != NULL)
	{
		m_bIsMultipage = (m_ImgListOrgani.GetAt(pos).img.type == _mptiff_);

		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
		HBITMAP hBitmap = m_pEsamiView->m_pImgManager->GetImgMP(m_ImgListOrgani.GetAt(pos).img.lID, FALSE, FALSE, FALSE, m_lCurTiffPage, m_lTotTiffPages);
		// TRACE3("-> Immagine %li -> Pagina %li di %li\n", m_ImgListOrgani.GetAt(pos).img.lID, m_lCurTiffPage + 1, m_lTotTiffPages);

		if (theApp.m_nApplication == PRG_DERMOX)
		{
			m_ctrlStaticSede.SetWindowText(m_ImgListOrgani.GetAt(pos).sSedeDermox);
			CPuntiPazienteSet().GetXYNumero(m_ImgListOrgani.GetAt(pos).img.lIDPunto, m_ptSagome, m_lNumeroDermox);
			InvalidateRect(m_rectFrameSagoma, FALSE);
		}

		if (hBitmap != NULL)
		{
			BeginWaitCursor();

			CString strFrame;
			strFrame.Format("%li / %li", m_lCurTiffPage + 1, m_lTotTiffPages);
			SetDlgItemText(IDC_STATIC_FRAMES, strFrame);

			m_pDib->Attach(CDib::BitmapToDIB(hBitmap, NULL), TRUE);

			m_lID = m_ImgListOrgani.GetAt(pos).img.lID;
			m_iType = m_ImgListOrgani.GetAt(pos).img.type;

			// Sandro 27/07/2012 //
			SetDlgItemText(IDC_COMMENTO, m_ImgListOrgani.GetAt(pos).img.szDescription);

			CString sFullPath = m_pEsamiView->m_pImgManager->GetFullPath(m_ImgListOrgani.GetAt(pos).img.lID);
			UpdateWindowTitle(sFullPath); // Marvel Carvalho - Bug 4269 Dialog ImageSimple2Dlg ignora album com 1 imagem

			if (XRClient_Play && !m_bMantieniImmagine)
			{
				sFullPath.Replace("\\", ":");

				if (!XRClient_Play(sFullPath, theApp.m_sVisIp, theApp.m_lVisPorta))
				{
					TCHAR szError[2048];
					ZeroMemory(szError, sizeof(char) * 2048);
					XRClient_GetErrorOccurred(szError);
					CString sError;
					sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
					theApp.AfxMessageBoxEndo(sError);
					m_bError = TRUE;
				}
			}

			DeleteObject(hBitmap);

			EndWaitCursor();

			bReturn = TRUE;
		}
	}

	GetDlgItem(IDC_STATIC_01)->ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);
	m_btnUpdate.ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);
	m_btnCancel.ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);
	m_btnSalNuo.ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);
	m_btnElabor.ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);
	GetDlgItem(IDC_STATIC_LINE)->ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);
	GetDlgItem(IDC_STATIC_02)->ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);
	m_btnBright.ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);
	m_btnContra.ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);
	m_btnUndLas.ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);
	GetDlgItem(IDC_ENHANCE)->ShowWindow(m_bIsMultipage ? SW_HIDE : SW_SHOW);

	return bReturn;
}

long CImageDlg::GetId(int nPos)
{
	POSITION pos = m_ImgListOrgani.FindIndex(nPos);

	if (pos != NULL)
		return m_ImgListOrgani.GetAt(pos).img.lID;

	return 0;
}

void CImageDlg::CaricaPunti()
{
	long lIdPunto;
	long lIdOrgano;
	long lX;
	long lY;
	IMG_ORGANI img_organi;

	BOOL bFindIndex;

	POSITION pos1 = m_ImgListOrgani.GetHeadPosition();
	POSITION pos2;

	m_listPunti.RemoveAll();
	while (pos1 != NULL)
	{
		lIdPunto = CImmaginiPuntiSet().GetIDPunto(m_ImgListOrgani.GetAt(pos1).img.lID);
		if (lIdPunto > 0)
		{
			if (CPuntiSet().GetDatiPunto(lIdPunto, lIdOrgano, lX, lY) == TRUE)
			{
				img_organi = m_ImgListOrgani.GetAt(pos1);
				img_organi.iPunto = 0;

				bFindIndex = FALSE;
				pos2 = m_listPunti.GetHeadPosition();
				while (pos2 != NULL)
				{
					if (m_listPunti.GetAt(pos2).lIdOrgano == lIdOrgano)
					{
						if ((lX == m_listPunti.GetAt(pos2).lX) && (lY == m_listPunti.GetAt(pos2).lY))
						{
							bFindIndex = TRUE;
							break;
						}
					}

					m_listPunti.GetNext(pos2);
					img_organi.iPunto++;
				}

				if (bFindIndex == FALSE)
				{
					tagPunti puntoTemp;

					puntoTemp.lIdPunto = lIdPunto;
					puntoTemp.lIdOrgano = lIdOrgano;
					puntoTemp.lX = lX;
					puntoTemp.lY = lY;

					m_listPunti.AddTail(puntoTemp);

					img_organi.iPunto = m_listPunti.GetCount() - 1;
				}

				m_ImgListOrgani.SetAt(pos1, img_organi);
			}
		}
		m_ImgListOrgani.GetNext(pos1);
	}
}

void CImageDlg::OnSize(UINT nType, int cx, int cy)
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	if (IsWindow(m_ctrlFrameSagoma))
	{
		m_ctrlFrameSagoma.GetWindowRect(&m_rectFrameSagoma);
		ScreenToClient(&m_rectFrameSagoma);
	}

	if (m_bInit)
	{
		InitializeWindow();
		AutoRedraw();
	}
}

CPoint CImageDlg::ImageToScreen(CPoint ptPoint)
{
	CPoint ptReturn(-1, -1);

	if ((ptPoint.x >= 0) && (ptPoint.y >= 0) && (m_rectPaintSagoma.Width() > 0) && (m_rectPaintSagoma.Height() > 0))
	{
		ptReturn.x = (ptPoint.x * m_rectPaintSagoma.Width() / m_dibSagome.Width()) + m_rectPaintSagoma.left;
		ptReturn.y = (ptPoint.y * m_rectPaintSagoma.Height() / m_dibSagome.Height()) + m_rectPaintSagoma.top;
	}

	return ptReturn;
}

void CImageDlg::OnCancel()
{
	//Gabriel BUG 6225 - Lista DO
	if (!m_bDoModal)
		DestroyWindow();
	else
		CEndoxResizableDlg::OnCancel();
}

//Gabriel BUG 6225 - Lista DO
LRESULT CImageDlg::OnExamChanged(WPARAM wParam, LPARAM lParam)
{
	OnCancel();
	return 0;
}

//Gabriel BUG 6225 - Lista DO FIX
void CImageDlg::OpenImgFullscreen()
{
	if (theApp.m_bAtivaListaDO)
	{
		CMaximizeDlg dlg(this, m_pDib, m_pEsamiView, &m_ImgListOrgani, m_nNumPage, m_lPaziente, m_lEsame, m_nTotPage);

		dlg.DoModal();
		m_nNumPage = dlg.GetCurrentPageNum();

		m_bRedrawBack = TRUE;
		AutoRedraw();
	}
	else
	{
		CMaximizeDlg dlg(this, m_pDib);

		dlg.DoModal();

		m_bRedrawBack = TRUE;
		AutoRedraw();
	}
}