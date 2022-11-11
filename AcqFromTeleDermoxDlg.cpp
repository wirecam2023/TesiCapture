#include "stdafx.h"
#include "Endox.h"
#include "AcqFromTeleDermoxDlg.h"

#include <io.h>
#include <math.h>

#include "DLL_Imaging\h\ImgArchive.h"

#include "MisureConfig\SerializerDLL.h"

#include "Calib.h"
#include "CalibList.h"
#include "Common.h"
#include "EditStringDlg.h"
#include "EsamiView.h"
#include "LogFileWriter.h"
#include "MaximizeDlg.h"
#include "MmSystem.h"
#include "PuntiPazienteSet.h"
#include "PuntiSediSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RAGGIO_PUNTO_1 3
#define RAGGIO_PUNTO_2 6

#define VIO_LUMIN_MIN 0
#define VIO_LUMIN_DEF 50
#define VIO_LUMIN_MAX 100
#define VIO_CONTR_MIN 0
#define VIO_CONTR_DEF 50
#define VIO_CONTR_MAX 100
#define VIO_TONAL_MIN 0
#define VIO_TONAL_DEF 50
#define VIO_TONAL_MAX 100
#define VIO_SATUR_MIN 0
#define VIO_SATUR_DEF 50
#define VIO_SATUR_MAX 100

#define VIO_0_BLACK_MIN 0
#define VIO_0_BLACK_DEF 15
#define VIO_0_BLACK_MAX 255
#define VIO_0_WHITE_MIN 0
#define VIO_0_WHITE_DEF 69
#define VIO_0_WHITE_MAX 255
#define VIO_1_BLACK_MIN 0
#define VIO_1_BLACK_DEF 127
#define VIO_1_BLACK_MAX 255
#define VIO_1_WHITE_MIN 0
#define VIO_1_WHITE_DEF 69
#define VIO_1_WHITE_MAX 255
#define VIO_2_BLACK_MIN 0
#define VIO_2_BLACK_DEF 127
#define VIO_2_BLACK_MAX 255
#define VIO_2_WHITE_MIN 0
#define VIO_2_WHITE_DEF 69
#define VIO_2_WHITE_MAX 255

IMPLEMENT_DYNAMIC(CAcqFromTeleDermoxDlg, CEndoxResizableDlg)

UINT uiControlsUSB[] = { IDC_STATIC_FRAME_L, IDC_SLIDER_L, IDC_STATIC_L, IDC_STATIC_FRAME_G, IDC_SLIDER_G, IDC_STATIC_G, IDC_STATIC_FRAME_T, IDC_SLIDER_T, IDC_STATIC_T, IDC_STATIC_FRAME_S, IDC_SLIDER_S, IDC_STATIC_S, IDC_STATIC_FRAME_E, IDC_SLIDER_E, IDC_STATIC_E };
UINT uiControlsCmp[] = { IDC_STATIC_FRAME_L, IDC_SLIDER_L, IDC_STATIC_L, IDC_STATIC_FRAME_C, IDC_SLIDER_C, IDC_STATIC_C, IDC_STATIC_FRAME_T, IDC_SLIDER_T, IDC_STATIC_T, IDC_STATIC_FRAME_S, IDC_SLIDER_S, IDC_STATIC_S };
UINT uiControlsRGB[] = { IDC_STATIC_FRAME_RGB, IDC_SLIDER_R_MIN, IDC_STATIC_R_MIN, IDC_SLIDER_R_MAX, IDC_STATIC_R_MAX, IDC_SLIDER_G_MIN, IDC_STATIC_G_MIN, IDC_SLIDER_G_MAX, IDC_STATIC_G_MAX, IDC_SLIDER_B_MIN, IDC_STATIC_B_MIN, IDC_SLIDER_B_MAX, IDC_STATIC_B_MAX };

CAcqFromTeleDermoxDlg::CAcqFromTeleDermoxDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CAcqFromTeleDermoxDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

	m_rectFrameLive = CRect(0, 0, 0, 0);
	m_rectFrameSagoma = CRect(0, 0, 0, 0);
	m_rectPaintSagoma = CRect(0, 0, 0, 0);
	m_rectFrameZoom = CRect(0, 0, 0, 0);

	m_iCurSelPointIndex = -1;
	m_iCurSelPointX = -1;
	m_iCurSelPointY = -1;

	m_lIDSede = 0;

	m_iRadioPlayPause = 0;
	m_iRadioPreset = GetPrivateProfileInt("xCap", "Current Preset", 0, theApp.m_sFileConfig);

	m_iLumin = -100;
	m_iContr = -100;
	m_iGamma = -100;
	m_iTonal = -100;
	m_iSatur = -100;
	m_iEspos = -100;
	m_iRMin = -100;
	m_iRMax = -100;
	m_iGMin = -100;
	m_iGMax = -100;
	m_iBMin = -100;
	m_iBMax = -100;
	m_iGain = -100;
	m_sCalib = "";

	m_hModule = NULL;
	m_hModuleCOM = NULL;

	// --- //

	m_bAcquisizioneInizializzata = FALSE;
	m_bFillingList = TRUE;

	xcapCOMStartListen = NULL;
	xcapCOMStopListen = NULL;

	m_iComPort = GetPrivateProfileInt("xcap", "ComPortPhoto", 0, theApp.m_sFileConfig);
	m_iComPort = max(0, m_iComPort);

	m_bComPortInv = (GetPrivateProfileInt("xcap", "invertpedalsphoto", 0, theApp.m_sFileConfig) == 0) ? FALSE : TRUE;	

}

CAcqFromTeleDermoxDlg::~CAcqFromTeleDermoxDlg()
{
	if (xcapCOMStopListen)
		xcapCOMStopListen();

	if (m_hModule)
		FreeLibrary(m_hModule);

	if (m_hModuleCOM)
		FreeLibrary(m_hModuleCOM);
}

BEGIN_MESSAGE_MAP(CAcqFromTeleDermoxDlg, CEndoxResizableDlg)

	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	
	ON_BN_CLICKED(IDC_BTN_PHOTO, OnBnClickedBtnPhoto)
	ON_BN_CLICKED(IDC_RADIO_PLAY, OnBnClickedRadioPlay)
	ON_BN_CLICKED(IDC_RADIO_PAUSE, OnBnClickedRadioPause)
	ON_BN_CLICKED(IDC_RADIO_PRESET01, OnBnClickedRadioPreset)
	ON_BN_CLICKED(IDC_RADIO_PRESET02, OnBnClickedRadioPreset)
	ON_BN_CLICKED(IDC_RADIO_PRESET03, OnBnClickedRadioPreset)
	ON_BN_CLICKED(IDC_RADIO_PRESET04, OnBnClickedRadioPreset)
	ON_BN_CLICKED(IDC_RADIO_PRESET05, OnBnClickedRadioPreset)
	ON_BN_CLICKED(IDC_RADIO_PRESET06, OnBnClickedRadioPreset)
	ON_BN_CLICKED(IDC_RADIO_PRESET07, OnBnClickedRadioPreset)
	ON_BN_CLICKED(IDC_RADIO_PRESET08, OnBnClickedRadioPreset)
	ON_BN_CLICKED(IDC_RADIO_PRESET09, OnBnClickedRadioPreset)
	ON_BN_CLICKED(IDC_RADIO_PRESET10, OnBnClickedRadioPreset)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBnClickedBtnExit)

	ON_CBN_SELCHANGE(IDC_COMBO_CALIB, OnCbnSelchangeComboCalib)

	ON_MESSAGE(WM_PRESS_PEDAL_1, OnPressPedal1)
	ON_MESSAGE(WM_PRESS_PEDAL_2, OnPressPedal2)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_POINTS, OnLvnItemchangedListPoints)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IMAGES, OnNMDblClkListImages)

END_MESSAGE_MAP()

void CAcqFromTeleDermoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_PHOTO, m_ctrlBtnPhoto);
	DDX_Control(pDX, IDC_RADIO_PLAY, m_ctrlRadioPlay);
	DDX_Control(pDX, IDC_RADIO_PAUSE, m_ctrlRadioPause);
	DDX_Control(pDX, IDC_RADIO_PRESET01, m_ctrlRadioPreset01);
	DDX_Control(pDX, IDC_RADIO_PRESET02, m_ctrlRadioPreset02);
	DDX_Control(pDX, IDC_RADIO_PRESET03, m_ctrlRadioPreset03);
	DDX_Control(pDX, IDC_RADIO_PRESET04, m_ctrlRadioPreset04);
	DDX_Control(pDX, IDC_RADIO_PRESET05, m_ctrlRadioPreset05);
	DDX_Control(pDX, IDC_RADIO_PRESET06, m_ctrlRadioPreset06);
	DDX_Control(pDX, IDC_RADIO_PRESET07, m_ctrlRadioPreset07);
	DDX_Control(pDX, IDC_RADIO_PRESET08, m_ctrlRadioPreset08);
	DDX_Control(pDX, IDC_RADIO_PRESET09, m_ctrlRadioPreset09);
	DDX_Control(pDX, IDC_RADIO_PRESET10, m_ctrlRadioPreset10);

	DDX_Control(pDX, IDC_BTN_EXIT, m_ctrlBtnExit);

	DDX_Control(pDX, IDC_COMBO_CALIB, m_ctrlComboCalib);

	DDX_Control(pDX, IDC_LIST_POINTS, m_ctrlListPoints);
	DDX_Control(pDX, IDC_LIST_IMAGES, m_ctrlListImages);

	DDX_Control(pDX, IDC_SLIDER_L, m_ctrlSliderL);
	DDX_Control(pDX, IDC_SLIDER_C, m_ctrlSliderC);
	DDX_Control(pDX, IDC_SLIDER_G, m_ctrlSliderG);
	DDX_Control(pDX, IDC_SLIDER_T, m_ctrlSliderT);
	DDX_Control(pDX, IDC_SLIDER_S, m_ctrlSliderS);
	DDX_Control(pDX, IDC_SLIDER_E, m_ctrlSliderE);
	DDX_Control(pDX, IDC_SLIDER_R_MIN, m_ctrlSliderRMin);
	DDX_Control(pDX, IDC_SLIDER_R_MAX, m_ctrlSliderRMax);
	DDX_Control(pDX, IDC_SLIDER_G_MIN, m_ctrlSliderGMin);
	DDX_Control(pDX, IDC_SLIDER_G_MAX, m_ctrlSliderGMax);
	DDX_Control(pDX, IDC_SLIDER_B_MIN, m_ctrlSliderBMin);
	DDX_Control(pDX, IDC_SLIDER_B_MAX, m_ctrlSliderBMax);

	DDX_Control(pDX, IDC_STATIC_SAGOMA, m_ctrlFrameSagoma);
	DDX_Control(pDX, IDC_STATIC_LIVE, m_ctrlFrameLive);
	DDX_Control(pDX, IDC_STATIC_ZOOM, m_ctrlFrameZoom);
	DDX_Control(pDX, IDC_STATIC_SEDE1, m_ctrlFrameSede);

	DDX_Control(pDX, IDC_STATIC_SEDE2, m_ctrlStaticSede);
	DDX_Control(pDX, IDC_STATIC_L, m_ctrlStaticL);
	DDX_Control(pDX, IDC_STATIC_C, m_ctrlStaticC);
	DDX_Control(pDX, IDC_STATIC_G, m_ctrlStaticG);
	DDX_Control(pDX, IDC_STATIC_T, m_ctrlStaticT);
	DDX_Control(pDX, IDC_STATIC_S, m_ctrlStaticS);
	DDX_Control(pDX, IDC_STATIC_E, m_ctrlStaticE);
	DDX_Control(pDX, IDC_STATIC_R_MIN, m_ctrlStaticRMin);
	DDX_Control(pDX, IDC_STATIC_R_MAX, m_ctrlStaticRMax);
	DDX_Control(pDX, IDC_STATIC_G_MIN, m_ctrlStaticGMin);
	DDX_Control(pDX, IDC_STATIC_G_MAX, m_ctrlStaticGMax);
	DDX_Control(pDX, IDC_STATIC_B_MIN, m_ctrlStaticBMin);
	DDX_Control(pDX, IDC_STATIC_B_MAX, m_ctrlStaticBMax);

	DDX_Control(pDX, IDC_STATIC_FRAME_L, m_ctrlStaticFrameL);
	DDX_Control(pDX, IDC_STATIC_FRAME_C, m_ctrlStaticFrameC);
	DDX_Control(pDX, IDC_STATIC_FRAME_G, m_ctrlStaticFrameG);
	DDX_Control(pDX, IDC_STATIC_FRAME_T, m_ctrlStaticFrameT);
	DDX_Control(pDX, IDC_STATIC_FRAME_S, m_ctrlStaticFrameS);
	DDX_Control(pDX, IDC_STATIC_FRAME_E, m_ctrlStaticFrameE);
	DDX_Control(pDX, IDC_STATIC_FRAME_CALIB, m_ctrlStaticFrameCalib);
	DDX_Control(pDX, IDC_STATIC_FRAME_RGB, m_ctrlStaticFrameRGB);

	// --- //

	DDX_Radio(pDX, IDC_RADIO_PLAY, m_iRadioPlayPause);
	DDX_Radio(pDX, IDC_RADIO_PRESET01, m_iRadioPreset);

}

void CAcqFromTeleDermoxDlg::OnCancel()
{
}

BOOL CAcqFromTeleDermoxDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	BOOL bOk = FALSE;

	CString strLibCap = "LibCap.dll";
	m_hModule = LoadLibrary(strLibCap);
	if (m_hModule == NULL)
	{
		CString strError;
		strError.Format(theApp.GetMessageString(IDS_LIBCAP_LOAD_ERROR1), strLibCap);
		theApp.AfxMessageBoxEndo(strError);
	}
	else
	{
		libcap_SetDevice = (SETDEVICEPTR)GetProcAddress(m_hModule, "libCap_SetDevice");
		libcap_StartLive = (STARTLIVEPTR)GetProcAddress(m_hModule, "libCap_StartLive");
		libcap_ShowLive = (SHOWLIVEPTR)GetProcAddress(m_hModule, "libCap_ShowLive");
		libcap_StopLive = (STOPLIVEPTR)GetProcAddress(m_hModule, "libCap_StopLive");
		libcap_FreezeLive = (FREEZELIVEPTR)GetProcAddress(m_hModule, "libCap_FreezeLive");
		libcap_Photo = (PHOTOPTR)GetProcAddress(m_hModule, "libCap_Photo");
		libcap_SetFeature = (SETFEATURE)GetProcAddress(m_hModule, "libCap_SetFeature");

		char szPathImm[MAX_PATH];
		char szPathMin[MAX_PATH];
		if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
		{
			CString fileSagomeName = "sagome.reg";

			CString sFileSagome;
			sFileSagome.Format("%s\\Organ\\sagome.org", szPathImm);

			CString sFileSedi;
			sFileSedi.Format("%s\\Organ\\%s", szPathImm, fileSagomeName);

			if (_access(sFileSagome, 00) == 0)
			{
				if (_access(sFileSedi, 00) == 0)
				{
					HBITMAP hBit;

					if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(sFileSagome, &hBit) > 0)
						if (hBit != INVALID_HANDLE_VALUE)
							bOk = m_dibSagome.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);
					DeleteObject(hBit);

					if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(sFileSedi, &hBit) > 0)
						if (hBit != INVALID_HANDLE_VALUE)
							bOk = m_dibSedi.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);
					DeleteObject(hBit);
				}
				else
				{
					CString strError;
					strError.Format(theApp.GetMessageString(IDS_FILE_SAGOME_NON_TROVATO), sFileSedi);
					theApp.AfxMessageBoxEndo(strError);
				}
			}
			else
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_FILE_SAGOME_NON_TROVATO), sFileSagome);
				theApp.AfxMessageBoxEndo(strError);
			}
		}
		else
		{
			ASSERT(FALSE);
		}

		if ((libcap_SetDevice == NULL) || (libcap_StartLive == NULL) || (libcap_ShowLive == NULL) || (libcap_StopLive == NULL) || (libcap_FreezeLive == NULL) || (libcap_Photo == NULL) || (libcap_SetFeature == NULL))
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_LIBCAP_LOAD_ERROR2), strLibCap);
			theApp.AfxMessageBoxEndo(strError);

			bOk = FALSE;
		}
	}

	if (bOk)
	{
		AddAnchor(IDC_RADIO_PRESET01, CSize(50, 100), CSize(60, 100));
		AddAnchor(IDC_RADIO_PRESET02, CSize(60, 100), CSize(70, 100));
		AddAnchor(IDC_RADIO_PRESET03, CSize(70, 100), CSize(80, 100));
		AddAnchor(IDC_RADIO_PRESET04, CSize(80, 100), CSize(90, 100));
		AddAnchor(IDC_RADIO_PRESET05, CSize(90, 100), CSize(100, 100));
		AddAnchor(IDC_RADIO_PRESET06, CSize(50, 100), CSize(60, 100));
		AddAnchor(IDC_RADIO_PRESET07, CSize(60, 100), CSize(70, 100));
		AddAnchor(IDC_RADIO_PRESET08, CSize(70, 100), CSize(80, 100));
		AddAnchor(IDC_RADIO_PRESET09, CSize(80, 100), CSize(90, 100));
		AddAnchor(IDC_RADIO_PRESET10, CSize(90, 100), CSize(100, 100));

		AddAnchor(IDC_BTN_EXIT, CSize(0, 100), CSize(100, 100));
		AddAnchor(IDC_BTN_PHOTO, CSize(50, 100), CSize(80, 100));
		AddAnchor(IDC_RADIO_PLAY, CSize(80, 100), CSize(90, 100));
		AddAnchor(IDC_RADIO_PAUSE, CSize(90, 100), CSize(100, 100));

		AddAnchor(IDC_COMBO_CALIB, CSize(75, 100), CSize(100, 100));

		AddAnchor(IDC_LIST_POINTS, CSize(0, 0), CSize(50, 0));
		AddAnchor(IDC_LIST_IMAGES, CSize(0, 100), CSize(50, 100));

		AddAnchor(IDC_SLIDER_L, CSize(50, 100), CSize(70, 100));
		AddAnchor(IDC_SLIDER_C, CSize(75, 100), CSize(95, 100));
		AddAnchor(IDC_SLIDER_G, CSize(75, 100), CSize(95, 100));
		AddAnchor(IDC_SLIDER_T, CSize(50, 100), CSize(70, 100));
		AddAnchor(IDC_SLIDER_S, CSize(75, 100), CSize(95, 100));
		AddAnchor(IDC_SLIDER_E, CSize(50, 100), CSize(70, 100));
		AddAnchor(IDC_SLIDER_R_MIN, CSize(50, 100), CSize(70, 100));
		AddAnchor(IDC_SLIDER_R_MAX, CSize(80, 100), CSize(100, 100));
		AddAnchor(IDC_SLIDER_G_MIN, CSize(50, 100), CSize(70, 100));
		AddAnchor(IDC_SLIDER_G_MAX, CSize(80, 100), CSize(100, 100));
		AddAnchor(IDC_SLIDER_B_MIN, CSize(50, 100), CSize(70, 100));
		AddAnchor(IDC_SLIDER_B_MAX, CSize(80, 100), CSize(100, 100));

		AddAnchor(IDC_STATIC_SAGOMA, CSize(0, 0), CSize(50, 100));
		AddAnchor(IDC_STATIC_LIVE, CSize(50, 0), CSize(100, 100));
		AddAnchor(IDC_STATIC_ZOOM, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDC_STATIC_SEDE1, CSize(0, 100), CSize(0, 100));

		AddAnchor(IDC_STATIC_SEDE2, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDC_STATIC_L, CSize(70, 100), CSize(75, 100));
		AddAnchor(IDC_STATIC_C, CSize(95, 100), CSize(100, 100));
		AddAnchor(IDC_STATIC_G, CSize(95, 100), CSize(100, 100));
		AddAnchor(IDC_STATIC_T, CSize(70, 100), CSize(75, 100));
		AddAnchor(IDC_STATIC_S, CSize(95, 100), CSize(100, 100));
		AddAnchor(IDC_STATIC_E, CSize(70, 100), CSize(75, 100));
		AddAnchor(IDC_STATIC_R_MIN, CSize(70, 100), CSize(75, 100));
		AddAnchor(IDC_STATIC_R_MAX, CSize(75, 100), CSize(80, 100));
		AddAnchor(IDC_STATIC_G_MIN, CSize(70, 100), CSize(75, 100));
		AddAnchor(IDC_STATIC_G_MAX, CSize(75, 100), CSize(80, 100));
		AddAnchor(IDC_STATIC_B_MIN, CSize(70, 100), CSize(75, 100));
		AddAnchor(IDC_STATIC_B_MAX, CSize(75, 100), CSize(80, 100));

		AddAnchor(IDC_STATIC_FRAME_L, CSize(50, 100), CSize(75, 100));
		AddAnchor(IDC_STATIC_FRAME_C, CSize(75, 100), CSize(100, 100));
		AddAnchor(IDC_STATIC_FRAME_G, CSize(75, 100), CSize(100, 100));
		AddAnchor(IDC_STATIC_FRAME_T, CSize(50, 100), CSize(75, 100));
		AddAnchor(IDC_STATIC_FRAME_S, CSize(75, 100), CSize(100, 100));
		AddAnchor(IDC_STATIC_FRAME_E, CSize(50, 100), CSize(75, 100));
		AddAnchor(IDC_STATIC_FRAME_CALIB, CSize(75, 100), CSize(100, 100));
		AddAnchor(IDC_STATIC_FRAME_RGB, CSize(50, 100), CSize(100, 100));

		//

		m_ctrlStaticSede.SetFont(&theApp.m_fontBold);
		m_ctrlBtnPhoto.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPlay.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPause.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPreset01.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPreset02.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPreset03.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPreset04.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPreset05.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPreset06.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPreset07.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPreset08.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPreset09.SetFont(&theApp.m_fontBold);
		m_ctrlRadioPreset10.SetFont(&theApp.m_fontBold);
		m_ctrlStaticFrameL.SetFont(&theApp.m_fontBold);
		m_ctrlStaticL.SetFont(&theApp.m_fontBold);
		m_ctrlStaticFrameC.SetFont(&theApp.m_fontBold);
		m_ctrlStaticC.SetFont(&theApp.m_fontBold);
		m_ctrlStaticFrameG.SetFont(&theApp.m_fontBold);
		m_ctrlStaticG.SetFont(&theApp.m_fontBold);
		m_ctrlStaticFrameT.SetFont(&theApp.m_fontBold);
		m_ctrlStaticT.SetFont(&theApp.m_fontBold);
		m_ctrlStaticFrameS.SetFont(&theApp.m_fontBold);
		m_ctrlStaticS.SetFont(&theApp.m_fontBold);
		m_ctrlStaticFrameE.SetFont(&theApp.m_fontBold);
		m_ctrlStaticE.SetFont(&theApp.m_fontBold);
		m_ctrlStaticFrameRGB.SetFont(&theApp.m_fontBold);
		m_ctrlStaticRMin.SetFont(&theApp.m_fontBold);
		m_ctrlStaticRMax.SetFont(&theApp.m_fontBold);
		m_ctrlStaticGMin.SetFont(&theApp.m_fontBold);
		m_ctrlStaticGMax.SetFont(&theApp.m_fontBold);
		m_ctrlStaticBMin.SetFont(&theApp.m_fontBold);
		m_ctrlStaticBMax.SetFont(&theApp.m_fontBold);
		m_ctrlStaticFrameCalib.SetFont(&theApp.m_fontBold);
		m_ctrlComboCalib.SetFont(&theApp.m_fontBold);
		m_ctrlBtnExit.SetFont(&theApp.m_fontBold);

		//

		//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
		SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

		//

		m_ctrlListPoints.SetExtendedStyle(m_ctrlListPoints.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
		m_ctrlListPoints.InsertColumn(0, "", LVCFMT_LEFT, 0); // empty //
		m_ctrlListPoints.InsertColumn(1, "", LVCFMT_RIGHT, 0); // numero //
		m_ctrlListPoints.InsertColumn(2, "Sede", LVCFMT_LEFT, 0); // sede //
		m_ctrlListPoints.InsertColumn(3, "Pattern", LVCFMT_LEFT, 0); // pattern //
		m_ctrlListPoints.InsertColumn(4, "Asportazione", LVCFMT_LEFT, 0); // asportazione //
		m_ctrlListPoints.InsertColumn(5, "", LVCFMT_LEFT, 0); // empty //

		//

		m_listImages.Create(HSIZE_PAL_4, VSIZE_PAL_4, ILC_COLOR32, 0, 1);
		m_ctrlListImages.SetExtendedStyle(m_ctrlListImages.GetExtendedStyle() | LVS_EX_BORDERSELECT);
		m_ctrlListImages.SetImageList(&m_listImages, LVSIL_NORMAL);
		m_ctrlListImages.SetIconSpacing(HSIZE_PAL_4 + 5, VSIZE_PAL_4 + 5);

		//

		m_ctrlSliderL.SetRange(VIO_LUMIN_MIN, VIO_LUMIN_MAX);
		m_ctrlSliderC.SetRange(VIO_CONTR_MIN, VIO_CONTR_MAX);
		m_ctrlSliderG.SetRange(1, 500);
		m_ctrlSliderT.SetRange(VIO_TONAL_MIN, VIO_TONAL_MAX);
		m_ctrlSliderS.SetRange(VIO_SATUR_MIN, VIO_SATUR_MAX);
		m_ctrlSliderE.SetRange(-14, 1);
		m_ctrlSliderRMin.SetRange(VIO_0_BLACK_MIN, VIO_0_BLACK_MAX);
		m_ctrlSliderRMax.SetRange(VIO_0_WHITE_MIN, VIO_0_WHITE_MAX);
		m_ctrlSliderGMin.SetRange(VIO_1_BLACK_MIN, VIO_1_BLACK_MAX);
		m_ctrlSliderGMax.SetRange(VIO_1_WHITE_MIN, VIO_1_WHITE_MAX);
		m_ctrlSliderBMin.SetRange(VIO_2_BLACK_MIN, VIO_2_BLACK_MAX);
		m_ctrlSliderBMax.SetRange(VIO_2_WHITE_MIN, VIO_2_WHITE_MAX);

		int nIndex = 0;
		POSITION pos1 = theApp.m_pListCalib->GetFirstCalibPos();
		while(pos1 != NULL)
		{
			CCalib* pCalib = theApp.m_pListCalib->GetNextCalib(pos1);

			m_ctrlComboCalib.InsertString(nIndex, pCalib->m_strName);
			m_ctrlComboCalib.SetItemDataPtr(nIndex, pCalib);

			nIndex++;
		}

		//
		LoadSettings();

		//
		CString strFilter;
		strFilter.Format("IDPaziente=%li", m_pEsamiView->m_pPazientiSet->m_lContatore);

		CPuntiPazienteSet setPunti;
		setPunti.SetOpenFilter(strFilter);
		if (setPunti.OpenRecordset("CAcqFromTeleDermoxDlg::OnInitDialog"))
		{
			while(!setPunti.IsEOF())
			{
				tagPuntiDermox tagTemp;
				tagTemp.lIDPunto = setPunti.m_lID;
				tagTemp.ptPunto.x = setPunti.m_lX;
				tagTemp.ptPunto.y = setPunti.m_lY;
				tagTemp.lNumeroDermox = setPunti.m_lNumeroDermox;
				sprintf_s(tagTemp.szSede, 255, "%s", setPunti.m_sSede);
				sprintf_s(tagTemp.szPattern, 255, "%s", GetTextPattern(setPunti.m_lPattern));
				tagTemp.bAsportazione = setPunti.m_bAsportazione;

				m_listPunti.AddTail(tagTemp);

				setPunti.MoveNext();
			}

			setPunti.CloseRecordset("CAcqFromTeleDermoxDlg::OnInitDialog");
		}

		//
		CPuntiSediSet setSedi;
		if (setSedi.OpenRecordset("CAcqFromTeleDermoxDlg::OnInitDialog"))
		{
			while(!setSedi.IsEOF())
			{
				tagSede tagTemp;

				tagTemp.m_lID = setSedi.m_lID;
				tagTemp.m_sSede = setSedi.m_sSede;
				tagTemp.m_sSede.MakeUpper();

				m_listSedi.AddTail(tagTemp);

				setSedi.MoveNext();
			}

			setSedi.CloseRecordset("CAcqFromTeleDermoxDlg::OnInitDialog");
		}

		//
		m_ctrlListPoints.SetRedraw(FALSE);
		m_ctrlListPoints.DeleteAllItems();

		int nItem = 0;
		POSITION pos2 = m_listPunti.GetHeadPosition();
		while(pos2 != NULL)
		{
			CString strTemp;
			tagPuntiDermox tagTemp = m_listPunti.GetAt(pos2);

			m_ctrlListPoints.InsertItem(nItem, "");
			m_ctrlListPoints.SetItemData(nItem, (DWORD)tagTemp.lIDPunto);

			strTemp.Format("%li", tagTemp.lNumeroDermox);
			m_ctrlListPoints.SetItemText(nItem, 1, strTemp);

			m_ctrlListPoints.SetItemText(nItem, 2, tagTemp.szSede);

			m_ctrlListPoints.SetItemText(nItem, 3, tagTemp.szPattern);

			m_ctrlListPoints.SetItemText(nItem, 4, tagTemp.bAsportazione ? theApp.GetMessageString(IDS_YES) : theApp.GetMessageString(IDS_NO));

			nItem++;
			m_listPunti.GetNext(pos2);
		}

		m_ctrlListPoints.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPoints.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPoints.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPoints.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPoints.SetRedraw(TRUE);

		m_bFillingList = FALSE;

		if (m_iCurSelPointIndex >= 0)
		{
			m_ctrlListPoints.SetItemState(m_iCurSelPointIndex, LVIS_SELECTED, LVIS_SELECTED);
			m_ctrlListPoints.EnsureVisible(m_iCurSelPointIndex, FALSE);
		}

		//
		CString strPortCom = "xcapCOMInterface.dll";
		m_hModuleCOM = LoadLibrary(strPortCom);
		if (m_hModuleCOM != NULL)
		{
			xcapCOMStartListen = (xcapCOMStartListen_PTR)GetProcAddress(m_hModuleCOM, _XCAP_COM_START_FUNCTION);
			xcapCOMStopListen = (xcapCOMStopListen_PTR)GetProcAddress(m_hModuleCOM, _XCAP_COM_STOP_FUNCTION);

			if ((xcapCOMStartListen == NULL) || (xcapCOMStopListen == NULL))
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_LIBCAP_LOAD_ERROR2), strPortCom);
				theApp.AfxMessageBoxEndo(strError);
			}
			else
			{
				if (m_iComPort > 0)
					if (!xcapCOMStartListen(m_iComPort, 0, 0, GetSafeHwnd(), WM_PRESS_PEDAL_1, WM_PRESS_PEDAL_2, WM_PRESS_PEDAL_3, WM_PRESS_PEDAL_4, 200, 1000))
						theApp.MessageBoxEndo(theApp.GetMessageString(IDS_ERROR_OPENING_COM), theApp.GetMessageString(IDS_ACHTUNG));
			}
		}
		else
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_LIBCAP_LOAD_ERROR1), strPortCom);
			theApp.AfxMessageBoxEndo(strError);
		}

		//
		theApp.LocalizeDialog(this, CAcqFromTeleDermoxDlg::IDD, "AcqFromTeleDermoxDlg");
	}
	else
	{
		m_dibSagome.ReleaseContents();
		m_dibSagome.Detach();

		m_dibSedi.ReleaseContents();
		m_dibSedi.Detach();

		EndDialog(IDCANCEL);
	}

	return TRUE;
}

void CAcqFromTeleDermoxDlg::OnOK()
{
}

void CAcqFromTeleDermoxDlg::OnBnClickedBtnExit()
{
	CResizableDialog::OnOK();
}

void CAcqFromTeleDermoxDlg::OnBnClickedBtnPhoto()
{
	//
	BeginWaitCursor();

	// prendo data e ora //
	SYSTEMTIME timeLocal;
	::GetLocalTime(&timeLocal);

	// compongo il nome del file della nuova foto //
	CString strPhotoFile;
	strPhotoFile.Format("%s\\%08d_%08d_%04d%02d%02d%02d%02d%02d.bmp", theApp.m_sDirTemp, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond);

	// lancio l'acquisizione e aspetto un secondo per sicurezza //
	try
	{
		libcap_Photo(strPhotoFile);
		Sleep(1000);
	}
	catch(...)
	{
		theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_Photo");
	}

	// creo il relativo file della calibrazione //
	int nIndex = m_ctrlComboCalib.GetCurSel();
	if (nIndex >= 0)
	{
		CCalib* pCalib = (CCalib*)m_ctrlComboCalib.GetItemDataPtr(nIndex);

		if (pCalib != NULL)
			SetCalib(strPhotoFile, pCalib);
	}

	// importo il tutto //
	long lIDImmagineImportata = ImportaImmagine(strPhotoFile);

	// aggiorno la finestra delle immagini //
	if (lIDImmagineImportata > 0)
		CaricaImmaginiPunto();

	//
	EndWaitCursor();
}

void CAcqFromTeleDermoxDlg::OnBnClickedRadioPlay()
{
	int iOldRadioPlayPause = m_iRadioPlayPause;

	UpdateData(TRUE);

	if (iOldRadioPlayPause != m_iRadioPlayPause)
		libcap_FreezeLive(FALSE);
}

void CAcqFromTeleDermoxDlg::OnBnClickedRadioPause()
{
	int iOldRadioPlayPause = m_iRadioPlayPause;

	UpdateData(TRUE);

	if (iOldRadioPlayPause != m_iRadioPlayPause)
		libcap_FreezeLive(TRUE);
}

void CAcqFromTeleDermoxDlg::OnBnClickedRadioPreset()
{
	TRACE0("CAcqFromTeleDermoxDlg::OnBnClickedRadioPreset\n");

	int iOldRadioPreset = m_iRadioPreset;

	UpdateData(TRUE);

	if (iOldRadioPreset != m_iRadioPreset)
	{
		WritePrivateProfileInt("xCap", "Current Preset", m_iRadioPreset, theApp.m_sFileConfig);
		LoadSettings();
	}
}

void CAcqFromTeleDermoxDlg::OnCbnSelchangeComboCalib()
{
	CString sSection;
	sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

	int nTemp = m_ctrlComboCalib.GetCurSel();
	if (nTemp >= 0)
	{
		CString sTemp;
		m_ctrlComboCalib.GetLBText(nTemp, sTemp);
		WritePrivateProfileString(sSection, "Calib", sTemp, theApp.m_sFileConfig);
	}
}

LRESULT CAcqFromTeleDermoxDlg::OnPressPedal1(WPARAM wParam, LPARAM lParam)
{
	if (m_bComPortInv)
	{
		// play & pause //

		UpdateData(TRUE);
		m_iRadioPlayPause = 1 - m_iRadioPlayPause;
		UpdateData(FALSE);

		libcap_FreezeLive(m_iRadioPlayPause != 0);
	}
	else
	{
		// acquisizione foto //

		if (m_ctrlBtnPhoto.IsWindowEnabled())
			OnBnClickedBtnPhoto();
	}

	return 0;
}

LRESULT CAcqFromTeleDermoxDlg::OnPressPedal2(WPARAM wParam, LPARAM lParam)
{
	if (m_bComPortInv)
	{
		// acquisizione foto //

		if (m_ctrlBtnPhoto.IsWindowEnabled())
			OnBnClickedBtnPhoto();
	}
	else
	{
		// play & pause //

		UpdateData(TRUE);
		m_iRadioPlayPause = 1 - m_iRadioPlayPause;
		UpdateData(FALSE);

		libcap_FreezeLive(m_iRadioPlayPause != 0);
	}

	return 0;
}
HBRUSH CAcqFromTeleDermoxDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_R_MIN:
		case IDC_STATIC_R_MAX:
		{
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}
		case IDC_STATIC_G_MIN:
		case IDC_STATIC_G_MAX:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
		case IDC_STATIC_B_MIN:
		case IDC_STATIC_B_MAX:
		{
			pDC->SetTextColor(theApp.m_color[4]);
			break;
		}
	}

	return hBrush;
}

void CAcqFromTeleDermoxDlg::OnDestroy()
{
	try
	{
		libcap_StopLive();
	}
	catch(...)
	{
		theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_StopLive");
	}

	CEndoxResizableDlg::OnDestroy();
}

void CAcqFromTeleDermoxDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	if (pScrollBar->GetSafeHwnd() == m_ctrlSliderL.GetSafeHwnd())
	{
		if (m_iLumin != m_ctrlSliderL.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iLumin = m_ctrlSliderL.GetPos();
			WritePrivateProfileInt(sSection, "Lumin", m_iLumin, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iLumin);
			m_ctrlStaticL.SetWindowText(strTemp);

			int iMin = m_ctrlSliderL.GetRangeMin();
			double lfLumin = (double)(m_iLumin - iMin) / (double)(m_ctrlSliderL.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(Brightness, lfLumin);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(Brightness)");
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderC.GetSafeHwnd())
	{
		if (m_iContr != m_ctrlSliderC.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iContr = m_ctrlSliderC.GetPos();
			WritePrivateProfileInt(sSection, "Contr", m_iContr, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iContr);
			m_ctrlStaticC.SetWindowText(strTemp);

			int iMin = m_ctrlSliderC.GetRangeMin();
			double lfContr = (double)(m_iContr - iMin) / (double)(m_ctrlSliderC.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(Contrast, lfContr);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(Contrast)");
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderG.GetSafeHwnd())
	{
		if (m_iGamma != m_ctrlSliderG.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iGamma = m_ctrlSliderG.GetPos();
			WritePrivateProfileInt(sSection, "Gamma", m_iGamma, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iGamma);
			m_ctrlStaticG.SetWindowText(strTemp);

			int iMin = m_ctrlSliderG.GetRangeMin();
			double lfGamma = (double)(m_iGamma - iMin) / (double)(m_ctrlSliderG.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(Gamma, lfGamma);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(Gamma)");
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderT.GetSafeHwnd())
	{
		if (m_iTonal != m_ctrlSliderT.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iTonal = m_ctrlSliderT.GetPos();
			WritePrivateProfileInt(sSection, "Tonal", m_iTonal, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iTonal);
			m_ctrlStaticT.SetWindowText(strTemp);

			int iMin = m_ctrlSliderT.GetRangeMin();
			double lfTonal = (double)(m_iTonal - iMin) / (double)(m_ctrlSliderT.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(Hue, lfTonal);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(Hue)");
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderS.GetSafeHwnd())
	{
		if (m_iSatur != m_ctrlSliderS.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iSatur = m_ctrlSliderS.GetPos();
			WritePrivateProfileInt(sSection, "Satur", m_iSatur, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iSatur);
			m_ctrlStaticS.SetWindowText(strTemp);

			int iMin = m_ctrlSliderS.GetRangeMin();
			double lfSatur = (double)(m_iSatur - iMin) / (double)(m_ctrlSliderS.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(Saturation, lfSatur);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(Saturation)");
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderE.GetSafeHwnd())
	{
		if (m_iEspos != m_ctrlSliderE.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iEspos = m_ctrlSliderE.GetPos();
			WritePrivateProfileInt(sSection, "Espos", m_iEspos, theApp.m_sFileConfig);

			if (m_iEspos == 1)
			{
				m_ctrlStaticE.SetWindowText("AUTO");

				try
				{
					libcap_SetFeature(ExposureAuto, 1);
				}
				catch(...)
				{
					theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(ExposureAuto)");
				}
			}
			else
			{
				CString strTemp;
				strTemp.Format("%d", m_iEspos);
				m_ctrlStaticE.SetWindowText(strTemp);

				int iMin = m_ctrlSliderE.GetRangeMin();
				int iMax = m_ctrlSliderE.GetRangeMax() - 1;
				double lfEspos = (double)(m_iEspos - iMin) / (double)(iMax - iMin);

				try
				{
					libcap_SetFeature(Exposure, lfEspos);
				}
				catch(...)
				{
					theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(Exposure)");
				}
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderRMin.GetSafeHwnd())
	{
		if (m_iRMin != m_ctrlSliderRMin.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iRMin = m_ctrlSliderRMin.GetPos();
			WritePrivateProfileInt(sSection, "RMin", m_iRMin, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iRMin);
			m_ctrlStaticRMin.SetWindowText(strTemp);

			int iMin = m_ctrlSliderRMin.GetRangeMin();
			double lfRMin = (double)(m_iRMin - iMin) / (double)(m_ctrlSliderRMin.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(RedMin, lfRMin);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(RedMin)");
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderRMax.GetSafeHwnd())
	{
		if (m_iRMax != m_ctrlSliderRMax.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iRMax = m_ctrlSliderRMax.GetPos();
			WritePrivateProfileInt(sSection, "RMax", m_iRMax, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iRMax);
			m_ctrlStaticRMax.SetWindowText(strTemp);

			int iMin = m_ctrlSliderRMax.GetRangeMin();
			double lfRMax = (double)(m_iRMax - iMin) / (double)(m_ctrlSliderRMax.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(RedMax, lfRMax);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(RedMax)");
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderGMin.GetSafeHwnd())
	{
		if (m_iGMin != m_ctrlSliderGMin.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iGMin = m_ctrlSliderGMin.GetPos();
			WritePrivateProfileInt(sSection, "GMin", m_iGMin, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iGMin);
			m_ctrlStaticGMin.SetWindowText(strTemp);

			int iMin = m_ctrlSliderGMin.GetRangeMin();
			double lfGMin = (double)(m_iGMin - iMin) / (double)(m_ctrlSliderGMin.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(GreenMin, lfGMin);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(GreenMin)");
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderGMax.GetSafeHwnd())
	{
		if (m_iGMax != m_ctrlSliderGMax.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iGMax = m_ctrlSliderGMax.GetPos();
			WritePrivateProfileInt(sSection, "GMax", m_iGMax, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iGMax);
			m_ctrlStaticGMax.SetWindowText(strTemp);

			int iMin = m_ctrlSliderGMax.GetRangeMin();
			double lfGMax = (double)(m_iGMax - iMin) / (double)(m_ctrlSliderGMax.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(GreenMax, lfGMax);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(GreenMax)");
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderBMin.GetSafeHwnd())
	{
		if (m_iBMin != m_ctrlSliderBMin.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iBMin = m_ctrlSliderBMin.GetPos();
			WritePrivateProfileInt(sSection, "BMin", m_iBMin, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iBMin);
			m_ctrlStaticBMin.SetWindowText(strTemp);

			int iMin = m_ctrlSliderBMin.GetRangeMin();
			double lfBMin = (double)(m_iBMin - iMin) / (double)(m_ctrlSliderBMin.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(BlueMin, lfBMin);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(BlueMin)");
			}
		}
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderBMax.GetSafeHwnd())
	{
		if (m_iBMax != m_ctrlSliderBMax.GetPos())
		{
			CString sSection;
			sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

			m_iBMax = m_ctrlSliderBMax.GetPos();
			WritePrivateProfileInt(sSection, "BMax", m_iBMax, theApp.m_sFileConfig);

			CString strTemp;
			strTemp.Format("%d", m_iBMax);
			m_ctrlStaticBMax.SetWindowText(strTemp);

			int iMin = m_ctrlSliderBMax.GetRangeMin();
			double lfBMax = (double)(m_iBMax - iMin) / (double)(m_ctrlSliderBMax.GetRangeMax() - iMin);

			try
			{
				libcap_SetFeature(BlueMax, lfBMax);
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap_SetFeature(BlueMax)");
			}
		}
	}
}

void CAcqFromTeleDermoxDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	point.x++;
	point.y++;
	if (m_rectPaintSagoma.PtInRect(point))
	{
		point = ScreenToImage(point);
		SelezionaPunto(point);
	}
}

void CAcqFromTeleDermoxDlg::OnLvnItemchangedListPoints(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!m_bFillingList)
	{
		BeginWaitCursor();

		POSITION pos1 = m_ctrlListPoints.GetFirstSelectedItemPosition();
		if (pos1 != NULL)
		{
			m_iCurSelPointIndex = m_ctrlListPoints.GetNextSelectedItem(pos1);

			POSITION pos2 = m_listPunti.FindIndex(m_iCurSelPointIndex);
			m_iCurSelPointX = m_listPunti.GetAt(pos2).ptPunto.x;
			m_iCurSelPointY = m_listPunti.GetAt(pos2).ptPunto.y;

			InvalidateRect(m_rectFrameSagoma, FALSE);
			InvalidateRect(m_rectFrameZoom, FALSE);
		}
		else
		{
			m_iCurSelPointIndex = -1;
			m_iCurSelPointX = -1;
			m_iCurSelPointY = -1;

			m_lIDSede = 0;

			InvalidateRect(m_rectFrameSagoma, FALSE);
			InvalidateRect(m_rectFrameZoom, FALSE);
		}

		CaricaDatiPunto();
		CaricaImmaginiPunto();

		EndWaitCursor();
	}
}

void CAcqFromTeleDermoxDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CEndoxResizableDlg::OnMouseMove(nFlags, point);

	// calcolo l'area del rect di zoom //
	InvalidateRect(m_rectFrameZoom, FALSE);
}

void CAcqFromTeleDermoxDlg::OnNMDblClkListImages(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListImages.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlListImages.GetNextSelectedItem(pos);
		long lIDImmagine = (long)m_ctrlListImages.GetItemData(iCurSel);

		if (lIDImmagine > 0)
		{
			BeginWaitCursor();
			HBITMAP hTemp = m_pEsamiView->m_pImgManager->GetImg(lIDImmagine, FALSE, FALSE, FALSE);
			EndWaitCursor();

			if (hTemp != NULL)
			{
				CDib dibTemp;
				dibTemp.Attach(CDib::BitmapToDIB(hTemp, NULL), TRUE);

				CMaximizeDlg dlgTemp(this, &dibTemp);
				dlgTemp.DoModal();

				DeleteObject(hTemp);
			}
		}
	}
}

void CAcqFromTeleDermoxDlg::OnPaint() 
{
	CPaintDC dc(this);

	///////////////////
	// SAGOMA GRANDE //
	///////////////////

	// disegno la dib //
	m_rectPaintSagoma = m_dibSagome.PaintDIBSagome(&dc, m_rectFrameSagoma);
	// TRACE("   SAGOME IN L%04li R%04li T%04li B%04li\n", m_rectSagoma.left, m_rectSagoma.right, m_rectSagoma.top, m_rectSagoma.bottom);

	/////////////////////////
	// PUNTI SAGOMA GRANDE //
	/////////////////////////

	CPen penSel(PS_SOLID, 1, RGB_RED);
	CBrush brushSel(RGB_RED);
	CPen penNormal(PS_SOLID, 1, RGB_BLUE);
	CBrush brushNormal(RGB_BLUE);
	CPen penAsportaz(PS_SOLID, 1, RGB_BLACK);
	CBrush brushAsportaz(RGB_BLACK);
	COLORREF crOldColor;

	dc.SetBkMode(TRANSPARENT);

	int i = 0;
	POSITION pos = m_listPunti.GetHeadPosition();
	while(pos != NULL)
	{
		CPen* pOldPen;
		CBrush* pOldBrush;
		if (i == m_iCurSelPointIndex)
		{
			pOldPen = dc.SelectObject(&penSel);
			pOldBrush = dc.SelectObject(&brushSel);
			crOldColor = dc.SetTextColor(RGB_RED);
		}
		else
		{
			if (m_listPunti.GetAt(pos).bAsportazione)
			{
				pOldPen = dc.SelectObject(&penAsportaz);
				pOldBrush = dc.SelectObject(&brushAsportaz);
				crOldColor = dc.SetTextColor(RGB_BLACK);
			}
			else
			{
				pOldPen = dc.SelectObject(&penNormal);
				pOldBrush = dc.SelectObject(&brushNormal);
				crOldColor = dc.SetTextColor(RGB_BLUE);
			}
		}

		CPoint ptToPaint = m_listPunti.GetAt(pos).ptPunto;
		ptToPaint = ImageToScreen(ptToPaint);

		CRect rectTemp(ptToPaint.x - RAGGIO_PUNTO_1, ptToPaint.y - RAGGIO_PUNTO_1, ptToPaint.x + RAGGIO_PUNTO_1, ptToPaint.y + RAGGIO_PUNTO_1);

		dc.Ellipse(rectTemp);

		if (theApp.m_bNumeriSuImmagineSagoma)
		{
			CString sTemp;
			sTemp.Format("%li", m_listPunti.GetAt(pos).lNumeroDermox);

			CFont* pOldFont = dc.SelectObject(&theApp.m_fontBold);
			int nOldBkMode = dc.SetBkMode(OPAQUE);
			dc.TextOut(ptToPaint.x + 4, ptToPaint.y - 9, sTemp);
			dc.SetBkMode(nOldBkMode);
			dc.SelectObject(pOldFont);
		}

		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);
		dc.SetTextColor(crOldColor);

		m_listPunti.GetNext(pos);
		i++;
	}

	/////////////////////////
	// FINESTRELLA DI ZOOM //
	/////////////////////////

	// disegno	nella finestra di zoom //
	RECT rectPaintZoom = { 0, 0, 0, 0 };
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(&ptMouse);
	ptMouse.x++;
	ptMouse.y++;
	if (m_rectPaintSagoma.PtInRect(ptMouse))
	{
		// se sono sulla sagoma faccio lo zoom intorno al cursore //

		// TRACE2("   CURSOR IN    X%04li       Y%04li\n", ptMouse.x, ptMouse.y);
		POINT ptToZoom;
		ptToZoom.x = ptMouse.x - m_rectPaintSagoma.left;
		ptToZoom.x = ptToZoom.x * m_dibSagome.Width() / m_rectPaintSagoma.Width();
		ptToZoom.y = ptMouse.y - m_rectPaintSagoma.top;
		ptToZoom.y = ptToZoom.y * m_dibSagome.Height() / m_rectPaintSagoma.Height();
		ptToZoom.y = m_dibSagome.Height() - ptToZoom.y;
		// TRACE2("   CURSOR IN   (X%04li)     (Y%04li)\n", ptToZoom.x, ptToZoom.y);

		rectPaintZoom = m_dibSagome.PaintDIBSagomeZoom(&dc, m_rectFrameZoom, ptToZoom);
		LONG lTeeemp = rectPaintZoom.top;
		rectPaintZoom.top = m_dibSagome.Height() - rectPaintZoom.bottom;
		rectPaintZoom.bottom = m_dibSagome.Height() - lTeeemp;
		// TRACE("    ZOOM  IN L%04li R%04li T%04li B%04li\n\n", rectPaintZoom.left, rectPaintZoom.right, rectPaintZoom.top, rectPaintZoom.bottom);

		///////////////////
		// TESTO REGIONE //
		///////////////////

		BYTE bytePixel;
		m_dibSedi.GetPixel(ptToZoom.x, ptToZoom.y, &bytePixel);
		//TRACE("   GETPIX IN X%04li %04li) --> %li \n", ptToZoom.x, ptToZoom.y, (int)bytePixel);

		if ((long)bytePixel != m_lIDSede)
		{
			CString strSede = "";
			m_lIDSede = (long)bytePixel;

			if ((m_lIDSede > 0) && (m_lIDSede < 255))
			{
				POSITION pos = m_listSedi.GetHeadPosition();

				while(pos != NULL)
				{
					tagSede tagTemp = m_listSedi.GetNext(pos);

					if (tagTemp.m_lID == m_lIDSede)
					{
						strSede = tagTemp.m_sSede;
						break;
					}
				}
			}

			m_ctrlStaticSede.SetWindowText(strSede);
		}
	}
	else
	{
		if ((m_iCurSelPointIndex >= 0) && (m_iCurSelPointX >= 0) && (m_iCurSelPointY >= 0))
		{
			// se sono fuori dalla sagoma ma c'è un punto selezionato ci faccio lo zoom attorno //

			POINT ptToZoom;
			ptToZoom.x = m_iCurSelPointX;
			ptToZoom.y = m_iCurSelPointY;
			ptToZoom.y = m_dibSagome.Height() - ptToZoom.y;

			rectPaintZoom = m_dibSagome.PaintDIBSagomeZoom(&dc, m_rectFrameZoom, ptToZoom);
			LONG lTeeemp = rectPaintZoom.top;
			rectPaintZoom.top = m_dibSagome.Height() - rectPaintZoom.bottom;
			rectPaintZoom.bottom = m_dibSagome.Height() - lTeeemp;
			// TRACE("    ZOOM  IN L%04li R%04li T%04li B%04li\n\n", rectPaintZoom.left, rectPaintZoom.right, rectPaintZoom.top, rectPaintZoom.bottom);

			///////////////////
			// TESTO REGIONE //
			///////////////////

			BYTE bytePixel;
			m_dibSedi.GetPixel(ptToZoom.x, ptToZoom.y, &bytePixel);
			// TRACE3("   GETPIX IN X%04li %04li) --> \n", ptToZoom.x, ptToZoom.y);

			if ((long)bytePixel != m_lIDSede)
			{
				CString strSede = "";
				m_lIDSede = (long)bytePixel;

				if ((m_lIDSede > 0) && (m_lIDSede < 255))
				{
					POSITION pos = m_listSedi.GetHeadPosition();

					while(pos != NULL)
					{
						tagSede tagTemp = m_listSedi.GetNext(pos);

						if (tagTemp.m_lID == m_lIDSede)
						{
							strSede = tagTemp.m_sSede;
							break;
						}
					}
				}

				m_ctrlStaticSede.SetWindowText(strSede);
			}
		}
		else
		{
			// se sono fuori dalla sagoma e non c'è un punto selezionato svuoto la finestra di zoom //

			CBrush brushNull;
			brushNull.CreateSolidBrush(RGB_BLACK);
			dc.FillRect(m_rectFrameZoom, &brushNull);
			brushNull.DeleteObject();

			///////////////////
			// TESTO REGIONE //
			///////////////////

			m_lIDSede = 0;
			m_ctrlStaticSede.SetWindowText("");
		}
	}

	///////////////////////////////
	// PUNTI FINESTRELLA DI ZOOM //
	///////////////////////////////

	dc.SetBkMode(TRANSPARENT);

	i = 0;
	pos = m_listPunti.GetHeadPosition();
	while(pos != NULL)
	{
		CPoint ptToPaint = m_listPunti.GetAt(pos).ptPunto;
		if (CRect(rectPaintZoom).PtInRect(ptToPaint))
		{
			CPen* pOldPen;
			CBrush* pOldBrush;
			if (i == m_iCurSelPointIndex)
			{
				pOldPen = dc.SelectObject(&penSel);
				pOldBrush = dc.SelectObject(&brushSel);
				crOldColor = dc.SetTextColor(RGB_RED);
			}
			else
			{
				if (m_listPunti.GetAt(pos).bAsportazione)
				{
					pOldPen = dc.SelectObject(&penAsportaz);
					pOldBrush = dc.SelectObject(&brushAsportaz);
					crOldColor = dc.SetTextColor(RGB_BLACK);
				}
				else
				{
					pOldPen = dc.SelectObject(&penNormal);
					pOldBrush = dc.SelectObject(&brushNormal);
					crOldColor = dc.SetTextColor(RGB_BLUE);
				}
			}

			ptToPaint = ImageToScreenZoom(ptToPaint, rectPaintZoom);

			CRect rectTemp(ptToPaint.x - RAGGIO_PUNTO_2, ptToPaint.y - RAGGIO_PUNTO_2, ptToPaint.x + RAGGIO_PUNTO_2, ptToPaint.y + RAGGIO_PUNTO_2);

			dc.Ellipse(rectTemp);

			if (theApp.m_bNumeriSuImmagineSagoma)
			{
				CString sTemp;
				sTemp.Format("%li", m_listPunti.GetAt(pos).lNumeroDermox);

				CFont* pOldFont = dc.SelectObject(&theApp.m_fontBigBig);
				int nOldBkMode = dc.SetBkMode(TRANSPARENT);
				dc.TextOut(ptToPaint.x + 6, ptToPaint.y - 13, sTemp);
				dc.SetBkMode(nOldBkMode);
				dc.SelectObject(pOldFont);
			}

			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
			dc.SetTextColor(crOldColor);
		}

		m_listPunti.GetNext(pos);
		i++;
	}
	penSel.DeleteObject();
	brushSel.DeleteObject();
	penNormal.DeleteObject();
	brushNormal.DeleteObject();
}

void CAcqFromTeleDermoxDlg::OnSize(UINT nType, int cx, int cy) 
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);
	
	if (IsWindow(m_ctrlFrameLive))
	{
		m_ctrlFrameLive.GetWindowRect(&m_rectFrameLive);
		ScreenToClient(&m_rectFrameLive);

		if (m_bAcquisizioneInizializzata)
		{
			try
			{
				libcap_StopLive();
				libcap_StartLive(m_ctrlFrameLive.GetSafeHwnd());
				libcap_ShowLive();
			}
			catch(...)
			{
				theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap (CAcqFromTeleDermoxDlg::OnSize)");
			}
		}
	}

	if (IsWindow(m_ctrlFrameSagoma))
	{
		m_ctrlFrameSagoma.GetWindowRect(&m_rectFrameSagoma);
		ScreenToClient(&m_rectFrameSagoma);
	}

	if (IsWindow(m_ctrlFrameZoom))
	{
		m_ctrlFrameZoom.GetWindowRect(&m_rectFrameZoom);
		ScreenToClient(&m_rectFrameZoom);
	}
}

void CAcqFromTeleDermoxDlg::LoadSettings()
{
	CString sSection;
	int iTemp;

	CButton* pButtonPresets[10] = { &m_ctrlRadioPreset01, &m_ctrlRadioPreset02, &m_ctrlRadioPreset03, &m_ctrlRadioPreset04, &m_ctrlRadioPreset05, &m_ctrlRadioPreset06, &m_ctrlRadioPreset07, &m_ctrlRadioPreset08, &m_ctrlRadioPreset09, &m_ctrlRadioPreset10 };
	for(int i = 0; i < 10; i++)
	{
		sSection.Format("SorgenteDermox%02d", i);

		CString strTemp;
		strTemp.Format("Preset %02d", i + 1);
		strTemp = GetPrivateProfileString(sSection, "Nome", strTemp, theApp.m_sFileConfig);
		WritePrivateProfileString(sSection, "Nome", strTemp, theApp.m_sFileConfig);

		if (strTemp.IsEmpty())
			pButtonPresets[i]->ShowWindow(SW_HIDE);
		else
			pButtonPresets[i]->SetWindowText(strTemp);
	}

	sSection.Format("SorgenteDermox%02d", m_iRadioPreset);

	//
	libCapDevice iDevice = (libCapDevice)GetPrivateProfileInt(sSection, "Device", DeviceUnknown, theApp.m_sFileConfig);
	libCapFormat iFormat = (libCapFormat)GetPrivateProfileInt(sSection, "Format", FormatUnknown, theApp.m_sFileConfig);
	try
	{
		if (m_bAcquisizioneInizializzata)
			libcap_StopLive();

		libcap_SetDevice(iDevice, iFormat);
		libcap_StartLive(m_ctrlFrameLive.GetSafeHwnd());
		libcap_ShowLive();

		m_bAcquisizioneInizializzata = TRUE;
	}
	catch(...)
	{
		theApp.AfxMessageBoxEndo("Si è verificata una eccezione in libcap (CAcqFromTeleDermoxDlg::LoadSettings)");
		m_bAcquisizioneInizializzata = FALSE;
	}

	switch(iFormat)
	{
		case Composite_PAL:
		case Composite_NTSC:
		{
			for(int i = 0; i < sizeof(uiControlsUSB) / sizeof(UINT); i++)
				GetDlgItem(uiControlsUSB[i])->ShowWindow(SW_HIDE);

			for(int i = 0; i < sizeof(uiControlsRGB) / sizeof(UINT); i++)
				GetDlgItem(uiControlsRGB[i])->ShowWindow(SW_HIDE);

			for(int i = 0; i < sizeof(uiControlsCmp) / sizeof(UINT); i++)
				GetDlgItem(uiControlsCmp[i])->ShowWindow(SW_SHOW);

			iTemp = GetPrivateProfileInt(sSection, "Lumin", VIO_LUMIN_DEF, theApp.m_sFileConfig);
			m_ctrlSliderL.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderL);

			iTemp = GetPrivateProfileInt(sSection, "Contr", VIO_CONTR_DEF, theApp.m_sFileConfig);
			m_ctrlSliderC.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderC);

			iTemp = GetPrivateProfileInt(sSection, "Tonal", VIO_TONAL_DEF, theApp.m_sFileConfig);
			m_ctrlSliderT.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderT);

			iTemp = GetPrivateProfileInt(sSection, "Satur", VIO_SATUR_DEF, theApp.m_sFileConfig);
			m_ctrlSliderS.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderS);

			break;
		}
		case RGB_PAL:
		case RGB_NTSC:
		{
			for(int i = 0; i < sizeof(uiControlsUSB) / sizeof(UINT); i++)
				GetDlgItem(uiControlsUSB[i])->ShowWindow(SW_HIDE);

			for(int i = 0; i < sizeof(uiControlsCmp) / sizeof(UINT); i++)
				GetDlgItem(uiControlsCmp[i])->ShowWindow(SW_HIDE);

			for(int i = 0; i < sizeof(uiControlsRGB) / sizeof(UINT); i++)
				GetDlgItem(uiControlsRGB[i])->ShowWindow(SW_SHOW);

			iTemp = GetPrivateProfileInt(sSection, "RMin", VIO_0_BLACK_DEF, theApp.m_sFileConfig);
			m_ctrlSliderRMin.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderRMin);

			iTemp = GetPrivateProfileInt(sSection, "RMax", VIO_0_WHITE_DEF, theApp.m_sFileConfig);
			m_ctrlSliderRMax.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderRMax);

			iTemp = GetPrivateProfileInt(sSection, "GMin", VIO_1_BLACK_DEF, theApp.m_sFileConfig);
			m_ctrlSliderGMin.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderGMin);

			iTemp = GetPrivateProfileInt(sSection, "GMax", VIO_1_WHITE_DEF, theApp.m_sFileConfig);
			m_ctrlSliderGMax.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderGMax);

			iTemp = GetPrivateProfileInt(sSection, "BMin", VIO_2_BLACK_DEF, theApp.m_sFileConfig);
			m_ctrlSliderBMin.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderBMin);

			iTemp = GetPrivateProfileInt(sSection, "BMax", VIO_2_WHITE_DEF, theApp.m_sFileConfig);
			m_ctrlSliderBMax.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderBMax);

			break;
		}
		default:
		{
			for(int i = 0; i < sizeof(uiControlsCmp) / sizeof(UINT); i++)
				GetDlgItem(uiControlsCmp[i])->ShowWindow(SW_HIDE);

			for(int i = 0; i < sizeof(uiControlsRGB) / sizeof(UINT); i++)
				GetDlgItem(uiControlsRGB[i])->ShowWindow(SW_HIDE);

			for(int i = 0; i < sizeof(uiControlsUSB) / sizeof(UINT); i++)
				GetDlgItem(uiControlsUSB[i])->ShowWindow(SW_SHOW);

			iTemp = GetPrivateProfileInt(sSection, "Lumin", 0, theApp.m_sFileConfig);
			m_ctrlSliderL.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderL);

			iTemp = GetPrivateProfileInt(sSection, "Gamma", 100, theApp.m_sFileConfig);
			m_ctrlSliderG.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderG);

			iTemp = GetPrivateProfileInt(sSection, "Tonal", 180, theApp.m_sFileConfig);
			m_ctrlSliderT.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderT);

			iTemp = GetPrivateProfileInt(sSection, "Satur", 128, theApp.m_sFileConfig);
			m_ctrlSliderS.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderS);

			iTemp = GetPrivateProfileInt(sSection, "Espos", 1, theApp.m_sFileConfig);
			m_ctrlSliderE.SetPos(iTemp);
			OnHScroll(SB_ENDSCROLL, iTemp, (CScrollBar*)&m_ctrlSliderE);

			break;
		}
	}

	m_sCalib = GetPrivateProfileString(sSection, "Calib", "", theApp.m_sFileConfig);
	m_ctrlComboCalib.SetCurSel(m_ctrlComboCalib.FindStringExact(-1, m_sCalib));
}

CPoint CAcqFromTeleDermoxDlg::ImageToScreen(CPoint ptPoint)
{
	CPoint ptReturn;

	ptReturn.x = ptPoint.x * m_rectPaintSagoma.Width() / m_dibSagome.Width();
	ptReturn.x = ptReturn.x + m_rectPaintSagoma.left;
	ptReturn.y = ptPoint.y * m_rectPaintSagoma.Height() / m_dibSagome.Height();
	ptReturn.y = ptReturn.y + m_rectPaintSagoma.top;

	return ptReturn;
}

CPoint CAcqFromTeleDermoxDlg::ImageToScreenZoom(CPoint ptPoint, CRect rectImageZoom)
{
	CPoint ptReturn;

	ptReturn.x = ((ptPoint.x - rectImageZoom.left) * m_rectFrameZoom.Width() / rectImageZoom.Width()) + m_rectFrameZoom.left;
	ptReturn.y = ((ptPoint.y - rectImageZoom.top) * m_rectFrameZoom.Height() / rectImageZoom.Height()) + m_rectFrameZoom.top;

	return ptReturn;
}

CPoint CAcqFromTeleDermoxDlg::ScreenToImage(CPoint ptPoint)
{
	CPoint ptReturn;

	ptReturn.x = ptPoint.x - m_rectPaintSagoma.left;
	ptReturn.x = ptReturn.x * m_dibSagome.Width() / m_rectPaintSagoma.Width();
	ptReturn.y = ptPoint.y - m_rectPaintSagoma.top;
	ptReturn.y = ptReturn.y * m_dibSagome.Height() / m_rectPaintSagoma.Height();

	return ptReturn;
}

int CAcqFromTeleDermoxDlg::AggiungiPunto(CString sSede, CPoint ptPoint)
{
	int nReturn = -1;

	CPuntiPazienteSet setTemp;
	setTemp.SetOpenFilter("ID=0");
	if (setTemp.OpenRecordset("CAcqFromTeleDermoxDlg::AggiungiPunto"))
	{
		if (setTemp.AddNewRecordset("CAcqFromTeleDermoxDlg::AggiungiPunto"))
		{
			setTemp.m_lIDPaziente = m_pEsamiView->m_pPazientiSet->m_lContatore;
			setTemp.m_sSede = sSede;
			setTemp.m_lX = ptPoint.x;
			setTemp.m_lY = ptPoint.y;

			if (setTemp.UpdateRecordset("CAcqFromTeleDermoxDlg::AggiungiPunto"))
			{
				CString strFilter;
				strFilter.Format("ID=%li", setTemp.GetLastAdd());

				setTemp.CloseRecordset("CAcqFromTeleDermoxDlg::AggiungiPunto");
				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CAcqFromTeleDermoxDlg::AggiungiPunto"))
				{
					if (!setTemp.IsEOF())
					{
						tagPuntiDermox puntoTemp;
						puntoTemp.lIDPunto = setTemp.m_lID;
						puntoTemp.ptPunto = ptPoint;
						puntoTemp.lNumeroDermox = setTemp.m_lNumeroDermox;
						sprintf_s(puntoTemp.szSede, 255, "%s", sSede);
						sprintf_s(puntoTemp.szPattern, 255, "%s", "");
						puntoTemp.bAsportazione = setTemp.m_bAsportazione;

						m_listPunti.AddTail(puntoTemp);

						nReturn = m_listPunti.GetCount() - 1;
					}
				}
			}
		}

		setTemp.CloseRecordset("CAcqFromTeleDermoxDlg::AggiungiPunto");
	}

	return nReturn;
}

void CAcqFromTeleDermoxDlg::CaricaDatiPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	CString strSede = "";

	//
	if (m_iCurSelPointIndex >= 0)
	{
		tagPuntiDermox tagTemp = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex));
		lIDPunto = tagTemp.lIDPunto;
		strSede = tagTemp.szSede;
	}

	//
	CString strButton = "";
	if (lIDPunto > 0)
	{
		if (strSede.IsEmpty())
			strButton.Format(theApp.GetMessageString(IDS_ACQUISIZIONE_IMMAGINE1));
		else
			strButton.Format(theApp.GetMessageString(IDS_ACQUISIZIONE_IMMAGINE2), strSede);

		m_ctrlBtnPhoto.EnableWindow(TRUE);
	}
	else
	{
		m_ctrlBtnPhoto.EnableWindow(FALSE);
	}
	m_ctrlBtnPhoto.SetWindowText(strButton);
}

void CAcqFromTeleDermoxDlg::CaricaImmaginiPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	if (m_iCurSelPointIndex >= 0)
		lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

	if (lIDPunto > 0)
	{
		// lista delle immagini di quel punto //
		CImgList listImg;
		int nImageCount = m_pEsamiView->m_pImgManager->GetImgListByPoint(m_pEsamiView->m_pEsamiSet->m_lPaziente, lIDPunto, &listImg);

		// reimposto la lista di immagini ed il relativo controllo //
		m_listImages.SetImageCount(nImageCount);
		m_ctrlListImages.DeleteAllItems();

		// riempio di nuovo tutto //
		for(int i = 0; i < nImageCount; i++)
		{
			IMG img = listImg.GetAt(listImg.FindIndex(i));

			m_listImages.Replace(i, CBitmap::FromHandle(img.hBmp), RGB(0, 0, 0));
			m_ctrlListImages.InsertItem(i, CEsamiSet().GetDataEsame(img.lIDEsame), i);
			m_ctrlListImages.SetItemData(i, (DWORD)img.lID);

			DeleteObject(img.hBmp);
			DeleteObject(img.hBmpSelected);
		}
	}
	else
	{
		m_listImages.SetImageCount(0);
		m_ctrlListImages.DeleteAllItems();
	}
}

long CAcqFromTeleDermoxDlg::ImportaImmagine(CString strFile)
{
	long lReturn = 0;

	if (_access(strFile, 0) == 0)
	{
		if ((strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0))
		{
			CStringList listPath;

			// controllo che la dimensione del file sia maggiore di 0 (capita per certi filmati e si blocca tutto) //

			HANDLE hFile = CreateFile(strFile, STANDARD_RIGHTS_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
			{
				LARGE_INTEGER llTemp;
				if (GetFileSizeEx(hFile, &llTemp))
				{
					if (llTemp.QuadPart > 0)
						listPath.AddHead(strFile);
					else
						DeleteFile(strFile);
				}
			}
			CloseHandle(hFile);

			BOOL bExportToPacs = FALSE;
			// In modalità 2 devo avviare il trasferimento automatico su PACS
			if (theApp.m_lDcmStoreMode == 2)
				bExportToPacs = TRUE;

			// ID del punto //
			long lIDPunto = 0;
			if (m_iCurSelPointIndex >= 0)
				lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

			//
			CImgIDList listIDImageImported;
			m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

			DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
			if (m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, lIDPunto, &listPath, FORM_IMM, FORM_MINI, &listIDImageImported, bExportToPacs, FALSE, FALSE) > 0)
			{
				if (listIDImageImported.GetCount() > 0)
					lReturn = listIDImageImported.GetHead();

				// importo anche il file .MIS associato //
				if (lReturn > 0)
				{
					CString strLastFile = m_pEsamiView->m_pImgManager->GetFullPath(lReturn);

					CString strOrigMis = strFile.Left(strFile.GetLength() - 4) + ".MIS";
					CString strDestMis = strLastFile.Left(strLastFile.GetLength() - 4) + ".MIS";

					MoveFile(strOrigMis, strDestMis);
				}
				// --- //

				DeleteFile(strFile);
			}
			if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
				CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, listIDImageImported.GetCount(), "CAcqFromTeleDermoxDlg::ImportaImmagine");

			listPath.RemoveAll();
		}
	}

	return lReturn;
}

void CAcqFromTeleDermoxDlg::SelezionaPunto(CPoint ptPoint)
{
	BeginWaitCursor();

	int nIndex = TrovaPunto(ptPoint);
	if (nIndex >= 0)
	{
		if (nIndex != m_iCurSelPointIndex)
		{
			m_iCurSelPointIndex = nIndex; // il punto esiste già, mi basta soltanto selezionarlo //
			m_iCurSelPointX = ptPoint.x;
			m_iCurSelPointY = ptPoint.y;

			InvalidateRect(m_rectFrameSagoma, FALSE);
			InvalidateRect(m_rectFrameZoom, FALSE);

			//
			for(int i = 0; i < m_ctrlListPoints.GetItemCount(); i++)
			{
				if (i == nIndex)
				{
					m_ctrlListPoints.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
					m_ctrlListPoints.EnsureVisible(i, FALSE);
				}
				else
				{
					m_ctrlListPoints.SetItemState(i, 0, LVIS_SELECTED);
				}
			}
			// OnLvnItemchangedListPoints(NULL, NULL);
		}
	}
	else
	{
		CString strSede;
		m_ctrlStaticSede.GetWindowText(strSede);
		strSede.Trim();

		CString strMessage;
		if (strSede.IsEmpty())
			strMessage.Format(theApp.GetMessageString(IDS_QUESTION_ADD_PUNTO1));
		else
			strMessage.Format(theApp.GetMessageString(IDS_QUESTION_ADD_PUNTO2), strSede);

		if (theApp.AfxMessageBoxEndo(strMessage, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			int nTemp = AggiungiPunto(strSede, ptPoint); // il punto non esiste, lo aggiungo //

			// se tutto è andato bene seleziono il nuovo punto aggiunto //
			if (nTemp >= 0)
			{
				m_iCurSelPointIndex = nTemp;
				m_iCurSelPointX = ptPoint.x;
				m_iCurSelPointY = ptPoint.y;

				InvalidateRect(m_rectFrameSagoma, FALSE);
				InvalidateRect(m_rectFrameZoom, FALSE);

				// --- //

				int nItem = m_ctrlListPoints.GetItemCount();

				CString strTemp;
				tagPuntiDermox tagTemp = m_listPunti.GetTail();

				m_ctrlListPoints.InsertItem(nItem, "");
				m_ctrlListPoints.SetItemData(nItem, (DWORD)tagTemp.lIDPunto);

				strTemp.Format("%li", tagTemp.lNumeroDermox);
				m_ctrlListPoints.SetItemText(nItem, 1, strTemp);

				m_ctrlListPoints.SetItemText(nItem, 2, tagTemp.szSede);

				m_ctrlListPoints.SetItemText(nItem, 3, tagTemp.szPattern);

				m_ctrlListPoints.SetItemText(nItem, 4, tagTemp.bAsportazione ? theApp.GetMessageString(IDS_YES) : theApp.GetMessageString(IDS_NO));

				m_ctrlListPoints.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
				m_ctrlListPoints.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
				m_ctrlListPoints.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
				m_ctrlListPoints.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);

				//
				for(int i = 0; i < m_ctrlListPoints.GetItemCount(); i++)
				{
					if (i == nItem)
					{
						m_ctrlListPoints.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
						m_ctrlListPoints.EnsureVisible(i, FALSE);
					}
					else
					{
						m_ctrlListPoints.SetItemState(i, 0, LVIS_SELECTED);
					}
				}
				// OnLvnItemchangedListPoints(NULL, NULL);
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_ADD_PUNTO), MB_ICONSTOP);
			}
		}
	}

	// CaricaDatiPunto();
	// CaricaImmaginiPunto();

	EndWaitCursor();
}

int CAcqFromTeleDermoxDlg::TrovaPunto(CPoint& ptPoint)
{
	int nIndex = 0;

	POSITION pos = m_listPunti.GetHeadPosition();
	while(pos != NULL)
	{
		CPoint ptTemp = m_listPunti.GetAt(pos).ptPunto;

		if (sqrt(pow((double)(ptPoint.x - ptTemp.x), 2) + pow((double)(ptPoint.y - ptTemp.y), 2)) <= RAGGIO_PUNTO_1)
		{
			ptPoint = ptTemp;
			return nIndex;
		}

		m_listPunti.GetNext(pos);
		nIndex++;
	}

	return -1;
}