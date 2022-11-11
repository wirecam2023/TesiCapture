#include "stdafx.h"
#include "Endox.h"
#include "DermoxPuntiPazienteDlg.h"

#include <io.h>
#include <math.h>

#include "DLL_Imaging\h\ImgArchive.h"

#include "AlbumConfrontoDermoxDlg.h"
#include "DiagnosiIstologicheSet.h"
#include "EsamiView.h"
#include "MaximizeDlg.h"
#include "PuntiPazienteSet.h"
#include "PuntiSediSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RAGGIO_PUNTO_1 3
#define RAGGIO_PUNTO_2 6

IMPLEMENT_DYNAMIC(CDermoxPuntiPazienteDlg, CEndoxResizableDlg)

CDermoxPuntiPazienteDlg::CDermoxPuntiPazienteDlg(CWnd* pParent, CEsamiView* pEsamiView, int iCurSelPointIndex)
	: CEndoxResizableDlg(CDermoxPuntiPazienteDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

	m_rectFrameSagoma = CRect(0, 0, 0, 0);
	m_rectPaintSagoma = CRect(0, 0, 0, 0);
	m_rectFrameZoom = CRect(0, 0, 0, 0);

	m_iCurSelPointIndex = iCurSelPointIndex;
	m_iCurSelPointX = -1;
	m_iCurSelPointY = -1;

	m_lIDSede = 0;

	// --- //

	m_nOperazione = 0;
	m_nReticoloPigmentarioColore = 0;
	m_nReticoloPigmentarioDistanza = 0;
	m_nReticoloPigmentarioSpessore = 0;
	m_nPigmentazioneDiffusaDistrib = 0;
	m_nGlobuliMarroniForma = 0;
	m_nGlobuliMarroniSede = 0;
	m_nPuntiNeriDistribuzione = 0;
	m_nPuntiNeriSede = 0;
	m_nPuntiNeriCalibro = 0;
	m_nDepigmentazioneDistribuzione = 0;
	m_nDepigmentazioneSede = 0;
	m_nLivelloDiClark = 0;

	// --- //

	m_bFillingList = TRUE;
	m_bLoadingData = FALSE;
	m_bModified = FALSE;

	// --- //

	GetClipCursor(&m_rectOriginalClip); 
}

CDermoxPuntiPazienteDlg::~CDermoxPuntiPazienteDlg()
{
}

BEGIN_MESSAGE_MAP(CDermoxPuntiPazienteDlg, CEndoxResizableDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBnClickedBtnExit)
	// ON_BN_CLICKED(IDC_RADIO_SEL, OnBnClickedRadioSel)
	ON_BN_CLICKED(IDC_RADIO_MOV, OnBnClickedRadioMov)
	ON_BN_CLICKED(IDC_RADIO_DEL, OnBnClickedRadioDel)
	ON_BN_CLICKED(IDC_BTN_CONFRONTO, OnBnClickedBtnConfronto)
	ON_BN_CLICKED(IDC_CHECK_00, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_01, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_02, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_03, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_04, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_05, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_06, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_07, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_08, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_09, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_10, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_11, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_12, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_13, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_14, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_15, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_16, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_17, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_18, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_19, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_20, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_21, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_22, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_23, OnBnClickedCheck)
	ON_BN_CLICKED(IDC_RADIO_00, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_01, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_02, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_03, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_04, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_05, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_06, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_07, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_08, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_09, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_10, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_11, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_12, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_13, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_14, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_15, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_16, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_17, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_18, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_19, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_20, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_21, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_22, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_23, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_24, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_25, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_26, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_27, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_28, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_29, OnBnClickedRadio)

	ON_CBN_SELCHANGE(IDC_COMBO_00, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_01, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_02, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_03, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_04, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_05, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_06, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_07, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_08, OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO_09, OnCbnSelchangeCombo)

	ON_EN_CHANGE(IDC_EDIT_00, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_01, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_02, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_03, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_04, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_05, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_06, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_07, OnEnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_08, OnEnChangeEdit)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_POINTS, OnLvnItemchangedListPoints)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_POINTS, OnLvnItemchangingListPoints)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IMAGES, OnNMDblClkListImages)
	ON_WM_MOUSEWHEEL()
	ON_WM_VSCROLL()	
END_MESSAGE_MAP()

void CDermoxPuntiPazienteDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	// --- //
	//theApp.m_bPersonalizzazioniBrasileCamargo = TRUE;
	
	DDX_Control(pDX, IDC_BTN_EXIT, m_ctrlBtnExit);

	DDX_Control(pDX, IDC_LIST_POINTS, m_ctrlListPoints);
	DDX_Control(pDX, IDC_LIST_IMAGES, m_ctrlListImages);

	DDX_Control(pDX, IDC_STATIC_SAGOMA, m_ctrlFrameSagoma);
	DDX_Control(pDX, IDC_STATIC_ZOOM, m_ctrlFrameZoom);
	DDX_Control(pDX, IDC_STATIC_SEDE1, m_ctrlFrameSede);
	DDX_Control(pDX, IDC_STATIC_SEDE2, m_ctrlStaticSede);

	DDX_Control(pDX, IDC_STATIC_56, m_ctrlStatic56);
	DDX_Control(pDX, IDC_STATIC_57, m_ctrlStatic57);
	DDX_Control(pDX, IDC_STATIC_58, m_ctrlStatic58);
	DDX_Control(pDX, IDC_RADIO_SEL, m_ctrlRadioSel);
	DDX_Control(pDX, IDC_RADIO_MOV, m_ctrlRadioMov);
	DDX_Control(pDX, IDC_RADIO_DEL, m_ctrlRadioDel);
	DDX_Control(pDX, IDC_BTN_CONFRONTO, m_ctrlBtnConfronto);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_COMBO_00, m_ctrlCombo00);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_CHECK_00, m_ctrlCheck00);
	DDX_Control(pDX, IDC_CHECK_01, m_ctrlCheck01);
	DDX_Control(pDX, IDC_CHECK_02, m_ctrlCheck02);
	DDX_Control(pDX, IDC_CHECK_03, m_ctrlCheck03);

	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_CHECK_04, m_ctrlCheck04);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_RADIO_00, m_ctrlRadio00);
	DDX_Control(pDX, IDC_RADIO_01, m_ctrlRadio01);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_RADIO_02, m_ctrlRadio02);
	DDX_Control(pDX, IDC_RADIO_03, m_ctrlRadio03);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_RADIO_04, m_ctrlRadio04);
	DDX_Control(pDX, IDC_RADIO_05, m_ctrlRadio05);

	DDX_Control(pDX, IDC_STATIC_07, m_ctrlStatic07);
	DDX_Control(pDX, IDC_CHECK_05, m_ctrlCheck05);

	DDX_Control(pDX, IDC_STATIC_08, m_ctrlStatic08);
	DDX_Control(pDX, IDC_CHECK_06, m_ctrlCheck06);
	DDX_Control(pDX, IDC_STATIC_09, m_ctrlStatic09);
	DDX_Control(pDX, IDC_RADIO_06, m_ctrlRadio06);
	DDX_Control(pDX, IDC_RADIO_07, m_ctrlRadio07);

	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic10);
	DDX_Control(pDX, IDC_CHECK_07, m_ctrlCheck07);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
	DDX_Control(pDX, IDC_RADIO_08, m_ctrlRadio08);
	DDX_Control(pDX, IDC_RADIO_09, m_ctrlRadio09);
	DDX_Control(pDX, IDC_STATIC_12, m_ctrlStatic12);
	DDX_Control(pDX, IDC_RADIO_10, m_ctrlRadio10);
	DDX_Control(pDX, IDC_RADIO_11, m_ctrlRadio11);
	DDX_Control(pDX, IDC_RADIO_12, m_ctrlRadio12);

	DDX_Control(pDX, IDC_STATIC_13, m_ctrlStatic13);
	DDX_Control(pDX, IDC_CHECK_08, m_ctrlCheck08);

	DDX_Control(pDX, IDC_STATIC_14, m_ctrlStatic14);
	DDX_Control(pDX, IDC_CHECK_09, m_ctrlCheck09);
	DDX_Control(pDX, IDC_STATIC_15, m_ctrlStatic15);
	DDX_Control(pDX, IDC_RADIO_13, m_ctrlRadio13);
	DDX_Control(pDX, IDC_RADIO_14, m_ctrlRadio14);
	DDX_Control(pDX, IDC_STATIC_16, m_ctrlStatic16);
	DDX_Control(pDX, IDC_RADIO_15, m_ctrlRadio15);
	DDX_Control(pDX, IDC_RADIO_16, m_ctrlRadio16);
	DDX_Control(pDX, IDC_RADIO_17, m_ctrlRadio17);
	DDX_Control(pDX, IDC_STATIC_17, m_ctrlStatic17);
	DDX_Control(pDX, IDC_RADIO_18, m_ctrlRadio18);
	DDX_Control(pDX, IDC_RADIO_19, m_ctrlRadio19);

	DDX_Control(pDX, IDC_STATIC_18, m_ctrlStatic18);
	DDX_Control(pDX, IDC_CHECK_10, m_ctrlCheck10);

	DDX_Control(pDX, IDC_STATIC_19, m_ctrlStatic19);
	DDX_Control(pDX, IDC_CHECK_11, m_ctrlCheck11);
	DDX_Control(pDX, IDC_STATIC_20, m_ctrlStatic20);
	DDX_Control(pDX, IDC_RADIO_20, m_ctrlRadio20);
	DDX_Control(pDX, IDC_RADIO_21, m_ctrlRadio21);
	DDX_Control(pDX, IDC_STATIC_21, m_ctrlStatic21);
	DDX_Control(pDX, IDC_RADIO_22, m_ctrlRadio22);
	DDX_Control(pDX, IDC_RADIO_23, m_ctrlRadio23);
	DDX_Control(pDX, IDC_RADIO_24, m_ctrlRadio24);

	DDX_Control(pDX, IDC_STATIC_22, m_ctrlStatic22);
	DDX_Control(pDX, IDC_CHECK_12, m_ctrlCheck12);
	DDX_Control(pDX, IDC_STATIC_23, m_ctrlStatic23);
	DDX_Control(pDX, IDC_CHECK_13, m_ctrlCheck13);

	DDX_Control(pDX, IDC_STATIC_24, m_ctrlStatic24);
	DDX_Control(pDX, IDC_CHECK_14, m_ctrlCheck14);
	DDX_Control(pDX, IDC_STATIC_25, m_ctrlStatic25);
	DDX_Control(pDX, IDC_CHECK_15, m_ctrlCheck15);

	DDX_Control(pDX, IDC_STATIC_26, m_ctrlStatic26);
	DDX_Control(pDX, IDC_CHECK_16, m_ctrlCheck16);
	DDX_Control(pDX, IDC_STATIC_27, m_ctrlStatic27);
	DDX_Control(pDX, IDC_CHECK_17, m_ctrlCheck17);

	DDX_Control(pDX, IDC_STATIC_28, m_ctrlStatic28);
	DDX_Control(pDX, IDC_CHECK_18, m_ctrlCheck18);
	DDX_Control(pDX, IDC_STATIC_29, m_ctrlStatic29);
	DDX_Control(pDX, IDC_CHECK_19, m_ctrlCheck19);

	DDX_Control(pDX, IDC_STATIC_30, m_ctrlStatic30);
	DDX_Control(pDX, IDC_CHECK_20, m_ctrlCheck20);
	DDX_Control(pDX, IDC_STATIC_31, m_ctrlStatic31);
	DDX_Control(pDX, IDC_CHECK_21, m_ctrlCheck21);

	DDX_Control(pDX, IDC_EDIT_00, m_ctrlEdit00);

	DDX_Control(pDX, IDC_STATIC_59, m_ctrlStatic59);
	DDX_Control(pDX, IDC_CHECK_23, m_ctrlCheck23);
	DDX_Control(pDX, IDC_STATIC_60, m_ctrlStatic60);
	DDX_Control(pDX, IDC_COMBO_09, m_ctrlCombo09);
	DDX_Control(pDX, IDC_STATIC_61, m_ctrlStatic61);
	DDX_Control(pDX, IDC_EDIT_08, m_ctrlEdit08);


	DDX_Control(pDX, IDC_STATIC_32, m_ctrlStatic32);

	DDX_Control(pDX, IDC_STATIC_33, m_ctrlStatic33);
	DDX_Control(pDX, IDC_STATIC_34, m_ctrlStatic34);
	DDX_Control(pDX, IDC_COMBO_01, m_ctrlCombo01);
	DDX_Control(pDX, IDC_STATIC_35, m_ctrlStatic35);
	DDX_Control(pDX, IDC_COMBO_02, m_ctrlCombo02);

	DDX_Control(pDX, IDC_STATIC_36, m_ctrlStatic36);
	DDX_Control(pDX, IDC_STATIC_37, m_ctrlStatic37);
	DDX_Control(pDX, IDC_COMBO_03, m_ctrlCombo03);
	DDX_Control(pDX, IDC_STATIC_38, m_ctrlStatic38);
	DDX_Control(pDX, IDC_COMBO_04, m_ctrlCombo04);

	DDX_Control(pDX, IDC_STATIC_39, m_ctrlStatic39);
	DDX_Control(pDX, IDC_EDIT_01, m_ctrlEdit01);
	DDX_Control(pDX, IDC_STATIC_40, m_ctrlStatic40);
	DDX_Control(pDX, IDC_CHECK_22, m_ctrlCheck22);
	DDX_Control(pDX, IDC_STATIC_41, m_ctrlStatic41);
	DDX_Control(pDX, IDC_EDIT_02, m_ctrlEdit02);
	DDX_Control(pDX, IDC_STATIC_42, m_ctrlStatic42);
	DDX_Control(pDX, IDC_EDIT_03, m_ctrlEdit03);

	DDX_Control(pDX, IDC_STATIC_43, m_ctrlStatic43);

	DDX_Control(pDX, IDC_STATIC_44, m_ctrlStatic44);
	DDX_Control(pDX, IDC_STATIC_45, m_ctrlStatic45);
	DDX_Control(pDX, IDC_COMBO_05, m_ctrlCombo05);

	DDX_Control(pDX, IDC_STATIC_46, m_ctrlStatic46);
	DDX_Control(pDX, IDC_EDIT_04, m_ctrlEdit04);
	DDX_Control(pDX, IDC_STATIC_47, m_ctrlStatic47);
	DDX_Control(pDX, IDC_COMBO_06, m_ctrlCombo06);
	DDX_Control(pDX, IDC_STATIC_48, m_ctrlStatic48);
	DDX_Control(pDX, IDC_EDIT_05, m_ctrlEdit05);
	DDX_Control(pDX, IDC_STATIC_49, m_ctrlStatic49);
	DDX_Control(pDX, IDC_RADIO_25, m_ctrlRadio25);
	DDX_Control(pDX, IDC_RADIO_26, m_ctrlRadio26);
	DDX_Control(pDX, IDC_RADIO_27, m_ctrlRadio27);
	DDX_Control(pDX, IDC_RADIO_28, m_ctrlRadio28);
	DDX_Control(pDX, IDC_RADIO_29, m_ctrlRadio29);

	DDX_Control(pDX, IDC_STATIC_51, m_ctrlStatic51);
	DDX_Control(pDX, IDC_EDIT_06, m_ctrlEdit06);

	DDX_Control(pDX, IDC_STATIC_52, m_ctrlStatic52);
	DDX_Control(pDX, IDC_STATIC_53, m_ctrlStatic53);
	DDX_Control(pDX, IDC_COMBO_07, m_ctrlCombo07);
	DDX_Control(pDX, IDC_STATIC_54, m_ctrlStatic54);
	DDX_Control(pDX, IDC_COMBO_08, m_ctrlCombo08);

	DDX_Control(pDX, IDC_STATIC_55, m_ctrlStatic55);
	DDX_Control(pDX, IDC_EDIT_07, m_ctrlEdit07);

	// --- //

	DDX_Radio(pDX, IDC_RADIO_SEL, m_nOperazione);
	DDX_Radio(pDX, IDC_RADIO_00, m_nReticoloPigmentarioColore);
	DDX_Radio(pDX, IDC_RADIO_02, m_nReticoloPigmentarioDistanza);
	DDX_Radio(pDX, IDC_RADIO_04, m_nReticoloPigmentarioSpessore);
	DDX_Radio(pDX, IDC_RADIO_06, m_nPigmentazioneDiffusaDistrib);
	DDX_Radio(pDX, IDC_RADIO_08, m_nGlobuliMarroniForma);
	DDX_Radio(pDX, IDC_RADIO_10, m_nGlobuliMarroniSede);
	DDX_Radio(pDX, IDC_RADIO_13, m_nPuntiNeriDistribuzione);
	DDX_Radio(pDX, IDC_RADIO_15, m_nPuntiNeriSede);
	DDX_Radio(pDX, IDC_RADIO_18, m_nPuntiNeriCalibro);
	DDX_Radio(pDX, IDC_RADIO_20, m_nDepigmentazioneDistribuzione);
	DDX_Radio(pDX, IDC_RADIO_22, m_nDepigmentazioneSede);
	DDX_Radio(pDX, IDC_RADIO_25, m_nLivelloDiClark);

	// --- // Sandro 10/11/20115 //

	m_ctrlStatic00.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCombo00.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic01.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck00.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck01.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck02.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck03.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic02.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic03.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck04.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic07.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck05.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic08.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck06.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic10.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck07.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic13.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck08.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic14.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck09.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic18.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck10.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic19.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck11.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic22.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck12.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic23.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck13.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic24.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck14.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic25.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck15.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic26.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck16.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic27.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck17.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic28.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck18.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic29.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck19.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic30.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck20.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic31.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck21.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlEdit00.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic32.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic33.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlStatic34.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCombo01.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlStatic35.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCombo02.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic36.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlStatic37.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCombo03.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlStatic38.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCombo04.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic39.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlEdit01.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic40.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck22.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic43.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic44.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlStatic45.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCombo05.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic46.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlEdit04.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlStatic47.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCombo06.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic48.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlEdit05.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic49.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlRadio25.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlRadio26.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlRadio27.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlRadio28.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlRadio29.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic51.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlEdit06.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic52.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlStatic53.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCombo07.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlStatic54.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCombo08.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic55.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlEdit07.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	m_ctrlStatic59.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);
	m_ctrlCheck23.ShowWindow(m_iCurSelPointIndex >= 0 ? SW_SHOW : SW_HIDE);

	// --- //

	m_ctrlCheck04.SetWindowText(m_ctrlCheck04.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTE) : theApp.GetMessageString(IDS_ASSENTE));
	m_ctrlStatic04.ShowWindow(m_ctrlCheck04.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio00.ShowWindow(m_ctrlCheck04.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio01.ShowWindow(m_ctrlCheck04.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlStatic05.ShowWindow(m_ctrlCheck04.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio02.ShowWindow(m_ctrlCheck04.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio03.ShowWindow(m_ctrlCheck04.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlStatic06.ShowWindow(m_ctrlCheck04.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio04.ShowWindow(m_ctrlCheck04.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio05.ShowWindow(m_ctrlCheck04.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);

	m_ctrlCheck05.SetWindowText(m_ctrlCheck05.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));

	m_ctrlCheck06.SetWindowText(m_ctrlCheck06.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTE) : theApp.GetMessageString(IDS_ASSENTE));
	m_ctrlStatic09.ShowWindow(m_ctrlCheck06.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio06.ShowWindow(m_ctrlCheck06.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio07.ShowWindow(m_ctrlCheck06.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);

	m_ctrlCheck07.SetWindowText(m_ctrlCheck07.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));
	m_ctrlStatic11.ShowWindow(m_ctrlCheck07.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio08.ShowWindow(m_ctrlCheck07.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio09.ShowWindow(m_ctrlCheck07.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlStatic12.ShowWindow(m_ctrlCheck07.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio10.ShowWindow(m_ctrlCheck07.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio11.ShowWindow(m_ctrlCheck07.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio12.ShowWindow(m_ctrlCheck07.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);

	m_ctrlCheck08.SetWindowText(m_ctrlCheck08.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));

	m_ctrlCheck09.SetWindowText(m_ctrlCheck09.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));
	m_ctrlStatic15.ShowWindow(m_ctrlCheck09.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio13.ShowWindow(m_ctrlCheck09.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio14.ShowWindow(m_ctrlCheck09.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlStatic16.ShowWindow(m_ctrlCheck09.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio15.ShowWindow(m_ctrlCheck09.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio16.ShowWindow(m_ctrlCheck09.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio17.ShowWindow(m_ctrlCheck09.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlStatic17.ShowWindow(m_ctrlCheck09.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio18.ShowWindow(m_ctrlCheck09.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio19.ShowWindow(m_ctrlCheck09.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);

	m_ctrlCheck10.SetWindowText(m_ctrlCheck10.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTE) : theApp.GetMessageString(IDS_ASSENTE));

	m_ctrlCheck11.SetWindowText(m_ctrlCheck11.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTE) : theApp.GetMessageString(IDS_ASSENTE));
	m_ctrlStatic20.ShowWindow(m_ctrlCheck11.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio20.ShowWindow(m_ctrlCheck11.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio21.ShowWindow(m_ctrlCheck11.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlStatic21.ShowWindow(m_ctrlCheck11.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio22.ShowWindow(m_ctrlCheck11.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio23.ShowWindow(m_ctrlCheck11.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlRadio24.ShowWindow(m_ctrlCheck11.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);

	m_ctrlCheck12.SetWindowText(m_ctrlCheck12.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTE) : theApp.GetMessageString(IDS_ASSENTE));

	m_ctrlCheck13.SetWindowText(m_ctrlCheck13.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));

	m_ctrlCheck14.SetWindowText(m_ctrlCheck14.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));

	m_ctrlCheck15.SetWindowText(m_ctrlCheck15.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));

	m_ctrlCheck16.SetWindowText(m_ctrlCheck16.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));

	m_ctrlCheck17.SetWindowText(m_ctrlCheck17.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));

	m_ctrlCheck18.SetWindowText(m_ctrlCheck18.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));

	m_ctrlCheck19.SetWindowText(m_ctrlCheck19.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTE) : theApp.GetMessageString(IDS_ASSENTE));

	m_ctrlCheck20.SetWindowText(m_ctrlCheck20.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTE) : theApp.GetMessageString(IDS_ASSENTE));

	m_ctrlCheck21.SetWindowText(m_ctrlCheck21.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTI) : theApp.GetMessageString(IDS_ASSENTI));

	m_ctrlCheck22.SetWindowText(m_ctrlCheck22.GetCheck() == BST_CHECKED ? theApp.GetMessageString(IDS_PRESENTE) : theApp.GetMessageString(IDS_ASSENTE));
	m_ctrlStatic41.ShowWindow(m_ctrlCheck22.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlEdit02.ShowWindow(m_ctrlCheck22.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlStatic42.ShowWindow(m_ctrlCheck22.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlEdit03.ShowWindow(m_ctrlCheck22.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);

	CString sSi = theApp.GetMessageString(IDS_YES);
	CString sNo = theApp.GetMessageString(IDS_NO);
	sSi.MakeUpper();
	sNo.MakeUpper();
	m_ctrlCheck23.SetWindowText(m_ctrlCheck23.GetCheck() == BST_CHECKED ? sSi : sNo);
	m_ctrlStatic60.ShowWindow(m_ctrlCheck23.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlCombo09.ShowWindow(m_ctrlCheck23.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlStatic61.ShowWindow(m_ctrlCheck23.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	m_ctrlEdit08.ShowWindow(m_ctrlCheck23.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
}

void CDermoxPuntiPazienteDlg::OnCancel()
{
	if (m_nOperazione == 1)
	{
		//
		m_nOperazione = 0;
		UpdateData(FALSE);

		// sblocco il cursore //
		ClipCursor(&m_rectOriginalClip);

		// mostro la lista dei punti //
		m_ctrlListPoints.ShowWindow(SW_SHOW);

		// nascondo le etichette con le istruzioni //
		m_ctrlStatic58.ShowWindow(SW_HIDE);
	}
}

BOOL CDermoxPuntiPazienteDlg::OnInitDialog()
{
	//Julio: Scrollbar, under developtment
	//GetWindowRect(m_rect);
	//m_nScrollPos = 0;

	//
	//int nScrollMax;
	//if (m_nCurHeight < m_rect.Height())
	//{
	//	nScrollMax = m_rect.Height() - m_nCurHeight;
	//}
	//else
	//	nScrollMax = 0;

	//SCROLLINFO si;
	//si.cbSize = sizeof(SCROLLINFO);
	//si.fMask = SIF_ALL; // SIF_ALL = SIF_PAGE | SIF_RANGE | SIF_POS;
	//si.nMin = 0;
	//si.nMax = nScrollMax;
	//si.nPage = si.nMax / 10;
	//si.nPos = 0;
	//SetScrollInfo(SB_VERT, &si, TRUE);

	CEndoxResizableDlg::OnInitDialog();

	BOOL bOk = FALSE;

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

	if (bOk)
	{
		//Add screen resolution condition
		//if (0 == 0)
		//{
		AddAnchor(IDC_BTN_EXIT, CSize(50, 0), CSize(50, 0));

		AddAnchor(IDC_LIST_POINTS, CSize(0, 0), CSize(50, 0));
		AddAnchor(IDC_LIST_IMAGES, CSize(0, 100), CSize(50, 100));

		AddAnchor(IDC_STATIC_SAGOMA, CSize(0, 0), CSize(50, 100));
		AddAnchor(IDC_STATIC_ZOOM, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDC_STATIC_SEDE1, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDC_STATIC_SEDE2, CSize(0, 100), CSize(0, 100));

		AddAnchor(IDC_STATIC_56, CSize(50, 0), CSize(50, 0));
		AddAnchor(IDC_STATIC_57, CSize(50, 0), CSize(50, 0));
		AddAnchor(IDC_STATIC_58, CSize(0, 0), CSize(50, 0));
		AddAnchor(IDC_RADIO_SEL, CSize(50, 0), CSize(50, 0));
		AddAnchor(IDC_RADIO_MOV, CSize(50, 0), CSize(50, 0));
		AddAnchor(IDC_RADIO_DEL, CSize(50, 0), CSize(50, 0));
		AddAnchor(IDC_BTN_CONFRONTO, CSize(50, 100), CSize(50, 100));
		//}


		AddAnchor(IDC_STATIC_00, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_COMBO_00, CSize(50, 0), CSize(67, 0));

		AddAnchor(IDC_STATIC_01, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_CHECK_00, CSize(67, 0), CSize(71, 0));
		AddAnchor(IDC_CHECK_01, CSize(71, 0), CSize(75, 0));
		AddAnchor(IDC_CHECK_02, CSize(75, 0), CSize(79, 0));
		AddAnchor(IDC_CHECK_03, CSize(79, 0), CSize(83, 0));

		AddAnchor(IDC_STATIC_02, CSize(50, 0), CSize(83, 50));
		AddAnchor(IDC_STATIC_03, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_CHECK_04, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_STATIC_04, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_00, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_01, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_STATIC_05, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_02, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_03, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_STATIC_06, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_04, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_05, CSize(50, 0), CSize(67, 0));

		AddAnchor(IDC_STATIC_07, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_CHECK_05, CSize(50, 0), CSize(67, 0));

		AddAnchor(IDC_STATIC_08, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_CHECK_06, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_STATIC_09, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_06, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_07, CSize(50, 0), CSize(67, 0));

		AddAnchor(IDC_STATIC_10, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_CHECK_07, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_STATIC_11, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_08, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_09, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_STATIC_12, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_10, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_11, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_RADIO_12, CSize(50, 0), CSize(67, 0));

		AddAnchor(IDC_STATIC_13, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_CHECK_08, CSize(50, 0), CSize(67, 0));

		AddAnchor(IDC_STATIC_14, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_CHECK_09, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_STATIC_15, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_13, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_14, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_STATIC_16, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_15, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_16, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_17, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_STATIC_17, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_18, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_19, CSize(67, 0), CSize(83, 0));

		AddAnchor(IDC_STATIC_18, CSize(50, 0), CSize(67, 0));
		AddAnchor(IDC_CHECK_10, CSize(50, 0), CSize(67, 0));

		AddAnchor(IDC_STATIC_19, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_CHECK_11, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_STATIC_20, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_20, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_21, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_STATIC_21, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_22, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_23, CSize(67, 0), CSize(83, 0));
		AddAnchor(IDC_RADIO_24, CSize(67, 0), CSize(83, 0));

		AddAnchor(IDC_STATIC_22, CSize(67, 0), CSize(75, 0));
		AddAnchor(IDC_CHECK_12, CSize(67, 0), CSize(75, 0));
		AddAnchor(IDC_STATIC_23, CSize(75, 0), CSize(83, 0));
		AddAnchor(IDC_CHECK_13, CSize(75, 0), CSize(83, 0));

		AddAnchor(IDC_STATIC_24, CSize(67, 0), CSize(75, 0));
		AddAnchor(IDC_CHECK_14, CSize(67, 0), CSize(75, 0));
		AddAnchor(IDC_STATIC_25, CSize(75, 0), CSize(83, 0));
		AddAnchor(IDC_CHECK_15, CSize(75, 0), CSize(83, 0));

		AddAnchor(IDC_STATIC_26, CSize(67, 0), CSize(75, 0));
		AddAnchor(IDC_CHECK_16, CSize(67, 0), CSize(75, 0));
		AddAnchor(IDC_STATIC_27, CSize(75, 0), CSize(83, 0));
		AddAnchor(IDC_CHECK_17, CSize(75, 0), CSize(83, 0));

		AddAnchor(IDC_STATIC_28, CSize(67, 0), CSize(75, 0));
		AddAnchor(IDC_CHECK_18, CSize(67, 0), CSize(75, 0));
		AddAnchor(IDC_STATIC_29, CSize(75, 0), CSize(83, 0));
		AddAnchor(IDC_CHECK_19, CSize(75, 0), CSize(83, 0));

		AddAnchor(IDC_STATIC_30, CSize(67, 0), CSize(75, 0));
		AddAnchor(IDC_CHECK_20, CSize(67, 0), CSize(75, 0));
		AddAnchor(IDC_STATIC_31, CSize(75, 0), CSize(83, 0));
		AddAnchor(IDC_CHECK_21, CSize(75, 0), CSize(83, 0));

		AddAnchor(IDC_EDIT_00, CSize(50, 0), CSize(83, 50));

		AddAnchor(IDC_STATIC_59, CSize(50, 50), CSize(83, 100));
		AddAnchor(IDC_CHECK_23, CSize(50, 50), CSize(83, 50));
		AddAnchor(IDC_STATIC_60, CSize(50, 50), CSize(83, 50));
		AddAnchor(IDC_COMBO_09, CSize(50, 50), CSize(83, 50));
		AddAnchor(IDC_STATIC_61, CSize(50, 50), CSize(83, 50));
		AddAnchor(IDC_EDIT_08, CSize(50, 50), CSize(83, 100));


		AddAnchor(IDC_STATIC_32, CSize(83, 0), CSize(100, 25));

		AddAnchor(IDC_STATIC_33, CSize(83, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_34, CSize(83, 0), CSize(100, 0));
		AddAnchor(IDC_COMBO_01, CSize(83, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_35, CSize(83, 0), CSize(100, 0));
		AddAnchor(IDC_COMBO_02, CSize(83, 0), CSize(100, 0));

		AddAnchor(IDC_STATIC_36, CSize(83, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_37, CSize(83, 0), CSize(100, 0));
		AddAnchor(IDC_COMBO_03, CSize(83, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_38, CSize(83, 0), CSize(100, 0));
		AddAnchor(IDC_COMBO_04, CSize(83, 0), CSize(100, 0));

		AddAnchor(IDC_STATIC_39, CSize(83, 0), CSize(100, 25));
		AddAnchor(IDC_EDIT_01, CSize(83, 0), CSize(100, 25));
		AddAnchor(IDC_STATIC_40, CSize(83, 25), CSize(100, 25));
		AddAnchor(IDC_CHECK_22, CSize(83, 25), CSize(100, 25));
		AddAnchor(IDC_STATIC_41, CSize(83, 25), CSize(83, 25));
		AddAnchor(IDC_EDIT_02, CSize(83, 25), CSize(100, 25));
		AddAnchor(IDC_STATIC_42, CSize(83, 25), CSize(83, 25));
		AddAnchor(IDC_EDIT_03, CSize(83, 25), CSize(100, 25));

		AddAnchor(IDC_STATIC_43, CSize(83, 25), CSize(100, 100));

		AddAnchor(IDC_STATIC_44, CSize(83, 25), CSize(100, 25));
		AddAnchor(IDC_STATIC_45, CSize(83, 25), CSize(100, 25));
		AddAnchor(IDC_COMBO_05, CSize(83, 25), CSize(100, 25));

		AddAnchor(IDC_STATIC_46, CSize(83, 25), CSize(100, 50));
		AddAnchor(IDC_EDIT_04, CSize(83, 25), CSize(100, 50));
		AddAnchor(IDC_STATIC_47, CSize(83, 50), CSize(100, 50));
		AddAnchor(IDC_COMBO_06, CSize(83, 50), CSize(100, 50));
		AddAnchor(IDC_STATIC_48, CSize(83, 50), CSize(100, 50));
		AddAnchor(IDC_EDIT_05, CSize(83, 50), CSize(100, 50));
		AddAnchor(IDC_STATIC_49, CSize(83, 50), CSize(100, 50));
		AddAnchor(IDC_RADIO_25, CSize(86, 50), CSize(86, 50));
		AddAnchor(IDC_RADIO_26, CSize(89, 50), CSize(89, 50));
		AddAnchor(IDC_RADIO_27, CSize(92, 50), CSize(92, 50));
		AddAnchor(IDC_RADIO_28, CSize(95, 50), CSize(95, 50));
		AddAnchor(IDC_RADIO_29, CSize(98, 50), CSize(98, 50));

		AddAnchor(IDC_STATIC_51, CSize(83, 50), CSize(100, 75));
		AddAnchor(IDC_EDIT_06, CSize(83, 50), CSize(100, 75));

		AddAnchor(IDC_STATIC_52, CSize(83, 75), CSize(100, 100));
		AddAnchor(IDC_STATIC_53, CSize(83, 75), CSize(100, 75));
		AddAnchor(IDC_COMBO_07, CSize(83, 75), CSize(100, 75));
		AddAnchor(IDC_STATIC_54, CSize(83, 75), CSize(100, 75));
		AddAnchor(IDC_COMBO_08, CSize(83, 75), CSize(100, 75));

		AddAnchor(IDC_STATIC_55, CSize(83, 75), CSize(100, 100));
		AddAnchor(IDC_EDIT_07, CSize(83, 75), CSize(100, 100));

		//

		m_ctrlStaticSede.SetFont(&theApp.m_fontBold);
		m_ctrlBtnExit.SetFont(&theApp.m_fontBold);

		m_ctrlStatic00.SetFont(&theApp.m_fontBig);
		m_ctrlStatic01.SetFont(&theApp.m_fontBig);
		m_ctrlStatic02.SetFont(&theApp.m_fontBig);
		m_ctrlStatic03.SetFont(&theApp.m_fontBold);
		m_ctrlStatic04.SetFont(&theApp.m_fontBold);
		m_ctrlStatic05.SetFont(&theApp.m_fontBold);
		m_ctrlStatic06.SetFont(&theApp.m_fontBold);
		m_ctrlStatic07.SetFont(&theApp.m_fontBold);
		m_ctrlStatic08.SetFont(&theApp.m_fontBold);
		m_ctrlStatic09.SetFont(&theApp.m_fontBold);
		m_ctrlStatic10.SetFont(&theApp.m_fontBold);
		m_ctrlStatic11.SetFont(&theApp.m_fontBold);
		m_ctrlStatic12.SetFont(&theApp.m_fontBold);
		m_ctrlStatic13.SetFont(&theApp.m_fontBold);
		m_ctrlStatic14.SetFont(&theApp.m_fontBold);
		m_ctrlStatic15.SetFont(&theApp.m_fontBold);
		m_ctrlStatic16.SetFont(&theApp.m_fontBold);
		m_ctrlStatic17.SetFont(&theApp.m_fontBold);
		m_ctrlStatic18.SetFont(&theApp.m_fontBold);
		m_ctrlStatic19.SetFont(&theApp.m_fontBold);
		m_ctrlStatic20.SetFont(&theApp.m_fontBold);
		m_ctrlStatic21.SetFont(&theApp.m_fontBold);
		m_ctrlStatic22.SetFont(&theApp.m_fontBold);
		m_ctrlStatic23.SetFont(&theApp.m_fontBold);
		m_ctrlStatic24.SetFont(&theApp.m_fontBold);
		m_ctrlStatic25.SetFont(&theApp.m_fontBold);
		m_ctrlStatic26.SetFont(&theApp.m_fontBold);
		m_ctrlStatic27.SetFont(&theApp.m_fontBold);
		m_ctrlStatic28.SetFont(&theApp.m_fontBold);
		m_ctrlStatic29.SetFont(&theApp.m_fontBold);
		m_ctrlStatic30.SetFont(&theApp.m_fontBold);
		m_ctrlStatic31.SetFont(&theApp.m_fontBold);
		m_ctrlStatic32.SetFont(&theApp.m_fontBig);
		m_ctrlStatic33.SetFont(&theApp.m_fontBold);
		m_ctrlStatic36.SetFont(&theApp.m_fontBold);
		m_ctrlStatic39.SetFont(&theApp.m_fontBold);
		m_ctrlStatic40.SetFont(&theApp.m_fontBold);
		m_ctrlStatic43.SetFont(&theApp.m_fontBig);
		m_ctrlStatic44.SetFont(&theApp.m_fontBold);
		m_ctrlStatic46.SetFont(&theApp.m_fontBold);
		m_ctrlStatic51.SetFont(&theApp.m_fontBold);
		m_ctrlStatic52.SetFont(&theApp.m_fontBold);
		m_ctrlStatic55.SetFont(&theApp.m_fontBold);
		m_ctrlStatic57.SetFont(&theApp.m_fontBold);
		m_ctrlStatic58.SetFont(&theApp.m_fontBold);
		m_ctrlStatic59.SetFont(&theApp.m_fontBold);

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
		CString strFilter;
		strFilter.Format("IDPaziente=%li", m_pEsamiView->m_pPazientiSet->m_lContatore);

		CPuntiPazienteSet setPunti;
		setPunti.SetOpenFilter(strFilter);
		if (setPunti.OpenRecordset("CDermoxPuntiPazienteDlg::OnInitDialog"))
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

			setPunti.CloseRecordset("CDermoxPuntiPazienteDlg::OnInitDialog");
		}

		//
		CPuntiSediSet setSedi;
		if (setSedi.OpenRecordset("CDermoxPuntiPazienteDlg::OnInitDialog"))
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

			setSedi.CloseRecordset("CDermoxPuntiPazienteDlg::OnInitDialog");
		}

		//
		for(int i = 0; i <= 10; i++)
			m_ctrlCombo00.InsertString(i, GetTextPattern(i));

		for(int i = 0; i <= 17; i++)
			m_ctrlCombo01.InsertString(i, GetTextTumoriMelanociticiBenigni1(i));

		for(int i = 0; i <= 4; i++)
			m_ctrlCombo02.InsertString(i, GetTextTumoriMelanociticiMaligni1(i));

		for(int i = 0; i <= 6; i++)
			m_ctrlCombo03.InsertString(i, GetTextTumoriNonMelanociticiLesioniEpiteliali(i));

		for(int i = 0; i <= 5; i++)
			m_ctrlCombo04.InsertString(i, GetTextTumoriNonMelanociticiLesioniVascolari(i));

		for(int i = 0; i <= 18; i++)
			m_ctrlCombo05.InsertString(i, GetTextTumoriMelanociticiBenigni2(i));

		for(int i = 0; i <= 5; i++)
			m_ctrlCombo06.InsertString(i, GetTextTumoriMelanociticiMaligni2(i));

		for(int i = 0; i <= 6; i++)
			m_ctrlCombo07.InsertString(i, GetTextTumoriNonMelanociticiLesioniEpiteliali(i));

		for(int i = 0; i <= 5; i++)
			m_ctrlCombo08.InsertString(i, GetTextTumoriNonMelanociticiLesioniVascolari(i));

		RiempiCombo09();

		//
		m_ctrlListPoints.SetRedraw(FALSE);
		m_ctrlListPoints.DeleteAllItems();

		int nItem = 0;
		POSITION pos = m_listPunti.GetHeadPosition();
		while(pos != NULL)
		{
			CString strTemp;
			tagPuntiDermox tagTemp = m_listPunti.GetAt(pos);

			m_ctrlListPoints.InsertItem(nItem, "");
			m_ctrlListPoints.SetItemData(nItem, (DWORD)tagTemp.lIDPunto);

			strTemp.Format("%li", tagTemp.lNumeroDermox);
			m_ctrlListPoints.SetItemText(nItem, 1, strTemp);

			m_ctrlListPoints.SetItemText(nItem, 2, tagTemp.szSede);

			m_ctrlListPoints.SetItemText(nItem, 3, tagTemp.szPattern);

			m_ctrlListPoints.SetItemText(nItem, 4, tagTemp.bAsportazione ? theApp.GetMessageString(IDS_YES) : theApp.GetMessageString(IDS_NO));

			nItem++;
			m_listPunti.GetNext(pos);
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
		theApp.LocalizeDialog(this, CDermoxPuntiPazienteDlg::IDD, "DermoxPuntiPazienteDlg");
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

void CDermoxPuntiPazienteDlg::OnOK()
{
}

void CDermoxPuntiPazienteDlg::OnBnClickedBtnExit()
{
	if (m_bModified)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SALVARE_NEVO), MB_YESNO | MB_ICONQUESTION) == IDYES)
			SalvaDatiPunto();

		m_bModified = FALSE;
	}

	CResizableDialog::OnOK();
}

/*
void CDermoxPuntiPazienteDlg::OnBnClickedRadioSel()
{
	UpdateData(TRUE);

	ClipCursor(&m_rectOriginalClip);

	m_ctrlListPoints.EnableWindow(TRUE);
}
*/

void CDermoxPuntiPazienteDlg::OnBnClickedRadioMov()
{
	UpdateData(TRUE);

	// sposto il cursore sopra al punto attualmente selezionato //
	CPoint ptTemp = ImageToScreen(CPoint(m_iCurSelPointX, m_iCurSelPointY));
	ClientToScreen(&ptTemp);
	SetCursorPos(ptTemp.x, ptTemp.y);

	// blocco il cursore nella finestra della sagoma //
	CRect rectTemp = m_rectPaintSagoma;
	ClientToScreen(&rectTemp);
	rectTemp.right--;
	rectTemp.bottom--;
	ClipCursor(&rectTemp);

	// nascondo la lista dei punti //
	m_ctrlListPoints.ShowWindow(SW_HIDE);

	// mostro le etichette con le istruzioni //
	m_ctrlStatic58.ShowWindow(SW_SHOW);

	// salvo la "vecchia" sede del punto //
	m_ctrlStaticSede.GetWindowText(m_sSedeOld);
	m_sSedeOld.Trim();
}

void CDermoxPuntiPazienteDlg::OnBnClickedRadioDel()
{
	UpdateData(TRUE);

	CString strMessage;

	CString strRegione = m_ctrlListPoints.GetItemText(m_iCurSelPointIndex, 2);
	if (strRegione.IsEmpty())
		strMessage = theApp.GetMessageString(IDS_ELIMINAPUNTO_1);
	else
		strMessage.Format(theApp.GetMessageString(IDS_ELIMINAPUNTO_2), strRegione);

	if (theApp.MessageBoxEndo(strMessage, theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		//
		EliminaPunto();

		// ridisegno le due dib //
		InvalidateRect(m_rectFrameSagoma, FALSE);
		InvalidateRect(m_rectFrameZoom, FALSE);

		// riaggiorno l'interfaccia //
		OnLvnItemchangedListPoints(NULL, NULL);
	}

	// rimetto in modalità "selezione" //
	UpdateData(TRUE);
	m_nOperazione = 0;
	UpdateData(FALSE);
}

void CDermoxPuntiPazienteDlg::OnBnClickedBtnConfronto()
{
	CAlbumConfrontoDermoxDlg dlg(this, m_pEsamiView, CPoint(m_iCurSelPointX, m_iCurSelPointY));
	dlg.DoModal();
}

void CDermoxPuntiPazienteDlg::OnBnClickedCheck()
{
	TRACE0("OnBnClickedCheck\n");

	if (!m_bLoadingData)
	{
		m_bModified = TRUE;
		UpdateData(TRUE);
	}
}

void CDermoxPuntiPazienteDlg::OnBnClickedRadio()
{
	TRACE0("OnBnClickedRadio\n");

	if (!m_bLoadingData)
		m_bModified = TRUE;
}

void CDermoxPuntiPazienteDlg::OnCbnSelchangeCombo()
{
	TRACE0("OnCbnSelchangeCombo\n");

	if (!m_bLoadingData)
		m_bModified = TRUE;
}

void CDermoxPuntiPazienteDlg::OnEnChangeEdit()
{
	TRACE0("OnEnChangeEdit\n");

	if (!m_bLoadingData)
		m_bModified = TRUE;
}

void CDermoxPuntiPazienteDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	point.x++;
	point.y++;
	if (m_rectPaintSagoma.PtInRect(point))
	{
		point = ScreenToImage(point);

		switch(m_nOperazione)
		{
			case 1:
			{
				SpostaPunto(point);
				break;
			}
			case 2:
			{
				// eliminazione //
				break;
			}
			default:
			{
				SelezionaPunto(point);
				break;
			}
		}
	}
}

void CDermoxPuntiPazienteDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CEndoxResizableDlg::OnMouseMove(nFlags, point);

	// calcolo l'area del rect di zoom //
	InvalidateRect(m_rectFrameZoom, FALSE);
}

void CDermoxPuntiPazienteDlg::OnLvnItemchangedListPoints(NMHDR *pNMHDR, LRESULT *pResult)
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

			m_ctrlRadioMov.EnableWindow(TRUE);
			m_ctrlRadioDel.EnableWindow(TRUE);
		}
		else
		{
			m_iCurSelPointIndex = -1;

			m_iCurSelPointX = -1;
			m_iCurSelPointY = -1;

			InvalidateRect(m_rectFrameSagoma, FALSE);
			InvalidateRect(m_rectFrameZoom, FALSE);

			m_ctrlRadioMov.EnableWindow(FALSE);
			m_ctrlRadioDel.EnableWindow(FALSE);
		}

		CaricaDatiPunto();
		CaricaImmaginiPunto();

		EndWaitCursor();
	}
}

void CDermoxPuntiPazienteDlg::OnLvnItemchangingListPoints(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if ((m_iCurSelPointIndex >= 0) && m_bModified)
	{
		if (((pNMLV->uOldState == LVIS_FOCUSED || pNMLV->uOldState == LVIS_SELECTED)) && (pNMLV->uNewState != pNMLV->uOldState))
		{
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SALVARE_NEVO), MB_YESNO | MB_ICONQUESTION) == IDYES)
				SalvaDatiPunto();
		}
	}
	m_bModified = FALSE;

	*pResult = 0;
}

void CDermoxPuntiPazienteDlg::OnNMDblClkListImages(NMHDR *pNMHDR, LRESULT *pResult)
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

void CDermoxPuntiPazienteDlg::OnPaint() 
{
	CPaintDC dc(this);

	///////////////////
	// SAGOMA GRANDE //
	///////////////////

	// disegno la dib //

	/*if (m_nScrollPos != 0)
		return;*/
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
	if (m_rectPaintSagoma.PtInRect(ptMouse)/* && m_nScrollPos == 0*/)
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

void CDermoxPuntiPazienteDlg::OnSize(UINT nType, int cx, int cy) 
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	//m_nCurHeight = cy;

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

CPoint CDermoxPuntiPazienteDlg::ImageToScreen(CPoint ptPoint)
{
	CPoint ptReturn;

	ptReturn.x = ptPoint.x * m_rectPaintSagoma.Width() / m_dibSagome.Width();
	ptReturn.x = ptReturn.x + m_rectPaintSagoma.left;
	ptReturn.y = ptPoint.y * m_rectPaintSagoma.Height() / m_dibSagome.Height();
	ptReturn.y = ptReturn.y + m_rectPaintSagoma.top;

	return ptReturn;
}

CPoint CDermoxPuntiPazienteDlg::ImageToScreenZoom(CPoint ptPoint, CRect rectImageZoom)
{
	CPoint ptReturn;

	ptReturn.x = ((ptPoint.x - rectImageZoom.left) * m_rectFrameZoom.Width() / rectImageZoom.Width()) + m_rectFrameZoom.left;
	ptReturn.y = ((ptPoint.y - rectImageZoom.top) * m_rectFrameZoom.Height() / rectImageZoom.Height()) + m_rectFrameZoom.top;

	return ptReturn;
}

CPoint CDermoxPuntiPazienteDlg::ScreenToImage(CPoint ptPoint)
{
	CPoint ptReturn;

	ptReturn.x = ptPoint.x - m_rectPaintSagoma.left;
	ptReturn.x = ptReturn.x * m_dibSagome.Width() / m_rectPaintSagoma.Width();
	ptReturn.y = ptPoint.y - m_rectPaintSagoma.top;
	ptReturn.y = ptReturn.y * m_dibSagome.Height() / m_rectPaintSagoma.Height();

	return ptReturn;
}

void CDermoxPuntiPazienteDlg::CaricaDatiPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	if (m_iCurSelPointIndex >= 0)
		lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

	BOOL bResetData = TRUE;
	if (lIDPunto > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", lIDPunto);

		CPuntiPazienteSet setPP;
		setPP.SetOpenFilter(strFilter);
		if (setPP.OpenRecordset("CDermoxPuntiPazienteDlg::CaricaDatiPunto"))
		{
			if (!setPP.IsEOF())
			{
				m_bLoadingData = TRUE;

				m_ctrlCombo00.SetCurSel(setPP.m_lPattern);

				m_ctrlCheck00.SetCheck(setPP.m_bSemioticaA ? BST_CHECKED : BST_UNCHECKED);
				m_ctrlCheck01.SetCheck(setPP.m_bSemioticaB ? BST_CHECKED : BST_UNCHECKED);
				m_ctrlCheck02.SetCheck(setPP.m_bSemioticaC ? BST_CHECKED : BST_UNCHECKED);
				m_ctrlCheck03.SetCheck(setPP.m_bSemioticaD ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck04.SetCheck(setPP.m_bReticoloPigmentario ? BST_CHECKED : BST_UNCHECKED);
				m_nReticoloPigmentarioColore = setPP.m_lReticoloPigmentarioColore;
				m_nReticoloPigmentarioDistanza = setPP.m_lReticoloPigmentarioDistanza;
				m_nReticoloPigmentarioSpessore = setPP.m_lReticoloPigmentarioSpessore;

				m_ctrlCheck05.SetCheck(setPP.m_bVenatureRamificate ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck06.SetCheck(setPP.m_bPigmentazioneDiffusa ? BST_CHECKED : BST_UNCHECKED);
				m_nPigmentazioneDiffusaDistrib = setPP.m_lPigmentazioneDiffusaDistrib;

				m_ctrlCheck07.SetCheck(setPP.m_bGlobuliMarroni ? BST_CHECKED : BST_UNCHECKED);
				m_nGlobuliMarroniForma = setPP.m_lGlobuliMarroniForma;
				m_nGlobuliMarroniSede = setPP.m_lGlobuliMarroniSede;

				m_ctrlCheck08.SetCheck(setPP.m_bPuntiPigmentati ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck09.SetCheck(setPP.m_bPuntiNeri ? BST_CHECKED : BST_UNCHECKED);
				m_nPuntiNeriDistribuzione = setPP.m_lPuntiNeriDistribuzione;
				m_nPuntiNeriSede = setPP.m_lPuntiNeriSede;
				m_nPuntiNeriCalibro = setPP.m_lPuntiNeriCalibro;

				m_ctrlCheck10.SetCheck(setPP.m_bVeloBiancastro ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck11.SetCheck(setPP.m_bDepigmentazione ? BST_CHECKED : BST_UNCHECKED);
				m_nDepigmentazioneDistribuzione = setPP.m_lDepigmentazioneDistribuzione;
				m_nDepigmentazioneSede = setPP.m_lDepigmentazioneSede;

				m_ctrlCheck12.SetCheck(setPP.m_bDepigmentazioneReticolare ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck13.SetCheck(setPP.m_bAreeDepigmentate ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck14.SetCheck(setPP.m_bAreeGrigieBlu ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck15.SetCheck(setPP.m_bFlussiRadiali ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck16.SetCheck(setPP.m_bPseudopodi ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck17.SetCheck(setPP.m_bBlocchiNeri ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck18.SetCheck(setPP.m_bCistiMiliaLike ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck19.SetCheck(setPP.m_bPeppering ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck20.SetCheck(setPP.m_bAreaFogliaAcero ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlCheck21.SetCheck(setPP.m_bLaghiVascolari ? BST_CHECKED : BST_UNCHECKED);

				m_ctrlEdit00.SetWindowText(setPP.m_sDiagnosiEpimicroscopica);

				m_ctrlCheck23.SetCheck(setPP.m_bAsportazione? BST_CHECKED : BST_UNCHECKED);
				m_ctrlCombo09.SetCurSel(0);
				if (setPP.m_lDiagnosiIstologica > 0)
				{
					for(int i = 1; i < m_ctrlCombo09.GetCount(); i++)
					{
						if (m_ctrlCombo09.GetItemData(i) == setPP.m_lDiagnosiIstologica)
						{
							m_ctrlCombo09.SetCurSel(i);
							break;
						}
					}
				}
				m_ctrlEdit08.SetWindowText(setPP.m_sNotizieAccessorie);

				m_ctrlCombo01.SetCurSel(setPP.m_lTumoriMelanociticiBenigni1);

				m_ctrlCombo02.SetCurSel(setPP.m_lTumoriMelanociticiMaligni1);

				m_ctrlCombo03.SetCurSel(setPP.m_lTumoriNonMelanociticiEpitel1);

				m_ctrlCombo04.SetCurSel(setPP.m_lTumoriNonMelanociticiVascol1);

				m_ctrlEdit01.SetWindowText(setPP.m_sDiagnosiClinicaAltre);

				m_ctrlCheck22.SetCheck(setPP.m_bEsameIstologico ? BST_CHECKED : BST_UNCHECKED);
				m_ctrlEdit02.SetWindowText(setPP.m_sRefertoNumero);
				m_ctrlEdit03.SetWindowText(setPP.m_sRefertoData);

				m_ctrlCombo05.SetCurSel(setPP.m_lTumoriMelanociticiBenigni2);

				m_ctrlEdit04.SetWindowText(setPP.m_sDiagnosiIstologicaAltro1);
				m_ctrlCombo06.SetCurSel(setPP.m_lTumoriMelanociticiMaligni2);
				m_ctrlEdit05.SetWindowText(setPP.m_sSpessoreDiBreslow);
				m_nLivelloDiClark = setPP.m_lLivelloDiClark;
				m_ctrlEdit06.SetWindowText(setPP.m_sDiagnosiIstologicaAltro2);
				m_ctrlCombo07.SetCurSel(setPP.m_lTumoriNonMelanociticiEpitel2);
				m_ctrlCombo08.SetCurSel(setPP.m_lTumoriNonMelanociticiVascol2);
				m_ctrlEdit07.SetWindowText(setPP.m_sDiagnosiIstologicaAltro3);

				bResetData = FALSE;

				m_bLoadingData = FALSE;
			}

			setPP.CloseRecordset("CDermoxPuntiPazienteDlg::CaricaDatiPunto");
		}
	}

	if (bResetData)
	{
		m_bLoadingData = TRUE;

		m_ctrlCombo00.SetCurSel(0);

		m_ctrlCheck00.SetCheck(BST_UNCHECKED);
		m_ctrlCheck01.SetCheck(BST_UNCHECKED);
		m_ctrlCheck02.SetCheck(BST_UNCHECKED);
		m_ctrlCheck03.SetCheck(BST_UNCHECKED);
	
		m_ctrlCheck04.SetCheck(BST_UNCHECKED);
		m_nReticoloPigmentarioColore = 0;
		m_nReticoloPigmentarioDistanza = 0;
		m_nReticoloPigmentarioSpessore = 0;

		m_ctrlCheck05.SetCheck(BST_UNCHECKED);

		m_ctrlCheck06.SetCheck(BST_UNCHECKED);
		m_nPigmentazioneDiffusaDistrib = 0;

		m_ctrlCheck07.SetCheck(BST_UNCHECKED);
		m_nGlobuliMarroniForma = 0;
		m_nGlobuliMarroniSede = 0;

		m_ctrlCheck08.SetCheck(BST_UNCHECKED);

		m_ctrlCheck09.SetCheck(BST_UNCHECKED);
		m_nPuntiNeriDistribuzione = 0;
		m_nPuntiNeriSede = 0;
		m_nPuntiNeriCalibro = 0;

		m_ctrlCheck10.SetCheck(BST_UNCHECKED);

		m_ctrlCheck11.SetCheck(BST_UNCHECKED);
		m_nDepigmentazioneDistribuzione = 0;
		m_nDepigmentazioneSede = 0;

		m_ctrlCheck12.SetCheck(BST_UNCHECKED);

		m_ctrlCheck13.SetCheck(BST_UNCHECKED);

		m_ctrlCheck14.SetCheck(BST_UNCHECKED);

		m_ctrlCheck15.SetCheck(BST_UNCHECKED);

		m_ctrlCheck16.SetCheck(BST_UNCHECKED);

		m_ctrlCheck17.SetCheck(BST_UNCHECKED);

		m_ctrlCheck18.SetCheck(BST_UNCHECKED);

		m_ctrlCheck19.SetCheck(BST_UNCHECKED);

		m_ctrlCheck20.SetCheck(BST_UNCHECKED);

		m_ctrlCheck21.SetCheck(BST_UNCHECKED);

		m_ctrlEdit00.SetWindowText("");

		m_ctrlCheck23.SetCheck(BST_UNCHECKED);
		m_ctrlCombo09.SetCurSel(0);
		m_ctrlEdit08.SetWindowText("");

		m_ctrlCombo01.SetCurSel(0);

		m_ctrlCombo02.SetCurSel(0);

		m_ctrlCombo03.SetCurSel(0);

		m_ctrlCombo04.SetCurSel(0);

		m_ctrlEdit01.SetWindowText("");

		m_ctrlCheck22.SetCheck(BST_UNCHECKED);
		m_ctrlEdit02.SetWindowText("");
		m_ctrlEdit03.SetWindowText("");

		m_ctrlCombo05.SetCurSel(0);

		m_ctrlEdit04.SetWindowText("");
		m_ctrlCombo06.SetCurSel(0);
		m_ctrlEdit05.SetWindowText("");
		m_nLivelloDiClark = 0;
		m_ctrlEdit06.SetWindowText("");
		m_ctrlCombo07.SetCurSel(0);
		m_ctrlCombo08.SetCurSel(0);
		m_ctrlEdit07.SetWindowText("");

		m_bLoadingData = FALSE;
	}

	UpdateData(FALSE);
}

void CDermoxPuntiPazienteDlg::CaricaImmaginiPunto()
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

	m_ctrlBtnConfronto.EnableWindow(m_ctrlListImages.GetItemCount() > 1);
}

void CDermoxPuntiPazienteDlg::EliminaPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	if (m_iCurSelPointIndex >= 0)
		lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

	if (lIDPunto > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", lIDPunto);

		CPuntiPazienteSet setPP;
		setPP.SetOpenFilter(strFilter);
		if (setPP.OpenRecordset("CDermoxPuntiPazienteDlg::EliminaPunto"))
		{
			if (!setPP.IsEOF())
			{
				if (setPP.DeleteRecordset("CDermoxPuntiPazienteDlg::EliminaPunto"))
				{
					int iTempCSPI = m_iCurSelPointIndex;

					// deseleziono tutti i punti //
					m_iCurSelPointIndex = -1;

					// rimuovo il punto dalla lista //
					m_listPunti.RemoveAt(m_listPunti.FindIndex(iTempCSPI));

					// rimuovo l'item dal controllo //
					m_ctrlListPoints.DeleteItem(iTempCSPI);
				}
			}

			setPP.CloseRecordset("CDermoxPuntiPazienteDlg::EliminaPunto");
		}
	}
}

void CDermoxPuntiPazienteDlg::RiempiCombo09()
{
	m_ctrlCombo09.ResetContent();

	m_ctrlCombo09.InsertString(0, "");
	m_ctrlCombo09.SetItemData(0, 0);

	int nIndex = 1;

	CDiagnosiIstologicheSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CDermoxPuntiPazienteDlg::RiempiCombo09"))
	{
		while(!setTemp.IsEOF())
		{
			m_ctrlCombo09.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlCombo09.SetItemData(nIndex, setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CDermoxPuntiPazienteDlg::RiempiCombo09");
	}

	m_ctrlCombo09.SetCurSel(0);
}

void CDermoxPuntiPazienteDlg::SalvaDatiPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	if (m_iCurSelPointIndex >= 0)
		lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

	BOOL bResetData = TRUE;
	if (lIDPunto > 0)
	{
		UpdateData(TRUE);

		CString strFilter;
		strFilter.Format("ID=%li", lIDPunto);

		CPuntiPazienteSet setPP;
		setPP.SetOpenFilter(strFilter);
		if (setPP.OpenRecordset("CDermoxPuntiPazienteDlg::CaricaDatiPunto"))
		{
			if (!setPP.IsEOF())
			{
				if (setPP.EditRecordset("CDermoxPuntiPazienteDlg::CaricaDatiPunto"))
				{
					setPP.m_lPattern = m_ctrlCombo00.GetCurSel();

					setPP.m_bSemioticaA = (m_ctrlCheck00.GetCheck() == BST_CHECKED);
					setPP.m_bSemioticaB = (m_ctrlCheck01.GetCheck() == BST_CHECKED);
					setPP.m_bSemioticaC = (m_ctrlCheck02.GetCheck() == BST_CHECKED);
					setPP.m_bSemioticaD = (m_ctrlCheck03.GetCheck() == BST_CHECKED);

					setPP.m_bReticoloPigmentario = (m_ctrlCheck04.GetCheck() == BST_CHECKED);
					setPP.m_lReticoloPigmentarioColore = m_nReticoloPigmentarioColore;
					setPP.m_lReticoloPigmentarioDistanza = m_nReticoloPigmentarioDistanza;
					setPP.m_lReticoloPigmentarioSpessore = m_nReticoloPigmentarioSpessore;

					setPP.m_bVenatureRamificate = (m_ctrlCheck05.GetCheck() == BST_CHECKED);

					setPP.m_bPigmentazioneDiffusa = (m_ctrlCheck06.GetCheck() == BST_CHECKED);
					setPP.m_lPigmentazioneDiffusaDistrib = m_nPigmentazioneDiffusaDistrib;

					setPP.m_bGlobuliMarroni = (m_ctrlCheck07.GetCheck() == BST_CHECKED);
					setPP.m_lGlobuliMarroniForma = m_nGlobuliMarroniForma;
					setPP.m_lGlobuliMarroniSede = m_nGlobuliMarroniSede;

					setPP.m_bPuntiPigmentati = (m_ctrlCheck08.GetCheck() == BST_CHECKED);

					setPP.m_bPuntiNeri = (m_ctrlCheck09.GetCheck() == BST_CHECKED);
					setPP.m_lPuntiNeriDistribuzione = m_nPuntiNeriDistribuzione;
					setPP.m_lPuntiNeriSede = m_nPuntiNeriSede;
					setPP.m_lPuntiNeriCalibro = m_nPuntiNeriCalibro;

					setPP.m_bVeloBiancastro = (m_ctrlCheck10.GetCheck() == BST_CHECKED);

					setPP.m_bDepigmentazione = (m_ctrlCheck11.GetCheck() == BST_CHECKED);
					setPP.m_lDepigmentazioneDistribuzione = m_nDepigmentazioneDistribuzione;
					setPP.m_lDepigmentazioneSede = m_nDepigmentazioneSede;

					setPP.m_bDepigmentazioneReticolare = (m_ctrlCheck12.GetCheck() == BST_CHECKED);

					setPP.m_bAreeDepigmentate = (m_ctrlCheck13.GetCheck() == BST_CHECKED);

					setPP.m_bAreeGrigieBlu = (m_ctrlCheck14.GetCheck() == BST_CHECKED);

					setPP.m_bFlussiRadiali = (m_ctrlCheck15.GetCheck() == BST_CHECKED);

					setPP.m_bPseudopodi = (m_ctrlCheck16.GetCheck() == BST_CHECKED);

					setPP.m_bBlocchiNeri = (m_ctrlCheck17.GetCheck() == BST_CHECKED);

					setPP.m_bCistiMiliaLike = (m_ctrlCheck18.GetCheck() == BST_CHECKED);

					setPP.m_bPeppering = (m_ctrlCheck19.GetCheck() == BST_CHECKED);

					setPP.m_bAreaFogliaAcero = (m_ctrlCheck20.GetCheck() == BST_CHECKED);

					setPP.m_bLaghiVascolari = (m_ctrlCheck21.GetCheck() == BST_CHECKED);

					m_ctrlEdit00.GetWindowText(setPP.m_sDiagnosiEpimicroscopica);

					setPP.m_bAsportazione = (m_ctrlCheck23.GetCheck() == BST_CHECKED);
					if (m_ctrlCombo09.GetCurSel() > 0)
						setPP.m_lDiagnosiIstologica = m_ctrlCombo09.GetItemData(m_ctrlCombo09.GetCurSel());
					else
						setPP.m_lDiagnosiIstologica = 0;
					m_ctrlEdit08.GetWindowText(setPP.m_sNotizieAccessorie);

					setPP.m_lTumoriMelanociticiBenigni1 = m_ctrlCombo01.GetCurSel();

					setPP.m_lTumoriMelanociticiMaligni1 = m_ctrlCombo02.GetCurSel();

					setPP.m_lTumoriNonMelanociticiEpitel1 = m_ctrlCombo03.GetCurSel();

					setPP.m_lTumoriNonMelanociticiVascol1 = m_ctrlCombo04.GetCurSel();

					m_ctrlEdit01.GetWindowText(setPP.m_sDiagnosiClinicaAltre);

					setPP.m_bEsameIstologico = (m_ctrlCheck22.GetCheck() == BST_CHECKED);
					m_ctrlEdit02.GetWindowText(setPP.m_sRefertoNumero);
					m_ctrlEdit03.GetWindowText(setPP.m_sRefertoData);

					setPP.m_lTumoriMelanociticiBenigni2 = m_ctrlCombo05.GetCurSel();

					m_ctrlEdit04.GetWindowText(setPP.m_sDiagnosiIstologicaAltro1);
					setPP.m_lTumoriMelanociticiMaligni2 = m_ctrlCombo06.GetCurSel();
					m_ctrlEdit05.GetWindowText(setPP.m_sSpessoreDiBreslow);
					setPP.m_lLivelloDiClark = m_nLivelloDiClark;
					m_ctrlEdit06.GetWindowText(setPP.m_sDiagnosiIstologicaAltro2);
					setPP.m_lTumoriNonMelanociticiEpitel2 = m_ctrlCombo07.GetCurSel();
					setPP.m_lTumoriNonMelanociticiVascol2 = m_ctrlCombo08.GetCurSel();
					m_ctrlEdit07.GetWindowText(setPP.m_sDiagnosiIstologicaAltro3);

					if (setPP.UpdateRecordset("CDermoxPuntiPazienteDlg::CaricaDatiPunto"))
					{
						CString strTemp;
						m_ctrlCombo00.GetLBText(m_ctrlCombo00.GetCurSel(), strTemp);

						//
						tagPuntiDermox tagTemp = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex));
						sprintf_s(tagTemp.szPattern, 255, "%s", strTemp);
						tagTemp.bAsportazione = (m_ctrlCheck23.GetCheck() == BST_CHECKED);
						m_listPunti.SetAt(m_listPunti.FindIndex(m_iCurSelPointIndex), tagTemp);

						//
						m_ctrlListPoints.SetItemText(m_iCurSelPointIndex, 3, strTemp);
						m_ctrlListPoints.SetItemText(m_iCurSelPointIndex, 4, tagTemp.bAsportazione ? theApp.GetMessageString(IDS_YES) : theApp.GetMessageString(IDS_NO));
					}
				}
			}

			setPP.CloseRecordset("CDermoxPuntiPazienteDlg::CaricaDatiPunto");
		}
	}
}

void CDermoxPuntiPazienteDlg::SelezionaPunto(CPoint ptPoint)
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

	EndWaitCursor();
}

void CDermoxPuntiPazienteDlg::SpostaPunto(CPoint ptPoint)
{
	BeginWaitCursor();

	int nIndex = TrovaPunto(ptPoint);
	if (nIndex < 0)
	{
		// significa che NON ho cliccato sopra ad un altro punto, altrimenti poi i due punti si confonderebbero //

		// salvo la "nuova" sede del punto //
		m_ctrlStaticSede.GetWindowText(m_sSedeNew);
		m_sSedeNew.Trim();

		// chiedo conferma prima di spostare per davvero //
		CString strMessage;
		strMessage = theApp.GetMessageString(IDS_SPOSTARE_LA_NEOFORMAZIONE);
		if (!m_sSedeOld.IsEmpty())
		{
			strMessage += " " + theApp.GetMessageString(IDS_DALLA_REGIONE) + " " + m_sSedeOld;

			if (!m_sSedeNew.IsEmpty())
				strMessage += " " + theApp.GetMessageString(IDS_ALLA_REGIONE) + " " + m_sSedeNew;
			else
				strMessage += " " + theApp.GetMessageString(IDS_ALLA_NUOVA_POSIZIONE);
		}
		else
		{
			if (!m_sSedeNew.IsEmpty())
				strMessage += " " + theApp.GetMessageString(IDS_NELLA_REGIONE) + " " + m_sSedeNew;
		}
		strMessage += "?";

		// sblocco il cursore //
		ClipCursor(&m_rectOriginalClip);

		//
		if (theApp.AfxMessageBoxEndo(strMessage, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			// ID del punto //
			long lIDPunto = 0;
			if (m_iCurSelPointIndex >= 0)
				lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

			if (lIDPunto > 0)
			{
				CString strFilter;
				strFilter.Format("ID=%li", lIDPunto);

				CPuntiPazienteSet setPP;
				setPP.SetOpenFilter(strFilter);
				if (setPP.OpenRecordset("CDermoxPuntiPazienteDlg::SpostaPunto"))
				{
					if (!setPP.IsEOF())
					{
						if (setPP.EditRecordset("CDermoxPuntiPazienteDlg::SpostaPunto"))
						{
							setPP.m_lX = ptPoint.x;
							setPP.m_lY = ptPoint.y;
							setPP.m_sSede = m_sSedeNew;
							
							if (setPP.UpdateRecordset("CDermoxPuntiPazienteDlg::SpostaPunto"))
							{
								// modifico il punto nella lista //
								POSITION posTemp = m_listPunti.FindIndex(m_iCurSelPointIndex);
								if (posTemp != NULL)
								{
									tagPuntiDermox tagTemp = m_listPunti.GetAt(posTemp);

									tagTemp.ptPunto = ptPoint;
									sprintf_s(tagTemp.szSede, 255, "%s", m_sSedeNew);

									m_listPunti.SetAt(posTemp, tagTemp);
								}

								// modifico l'item nel controllo //
								m_ctrlListPoints.SetItemText(m_iCurSelPointIndex, 2, m_sSedeNew);
								m_ctrlListPoints.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
								m_ctrlListPoints.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
								m_ctrlListPoints.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
								m_ctrlListPoints.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);

								//
								m_iCurSelPointX = ptPoint.x;
								m_iCurSelPointY = ptPoint.y;

								//
								InvalidateRect(m_rectFrameSagoma, FALSE);
								InvalidateRect(m_rectFrameZoom, FALSE);

								//
								OnCancel();
							}
						}

					}

					setPP.CloseRecordset("CDermoxPuntiPazienteDlg::SpostaPunto");
				}
			}
		}
		else
		{
			// blocco il cursore nella finestra della sagoma //
			CRect rectTemp = m_rectPaintSagoma;
			ClientToScreen(&rectTemp);
			rectTemp.right--;
			rectTemp.bottom--;
			ClipCursor(&rectTemp);
		}
	}
	else
	{
		// sblocco il cursore //
		ClipCursor(&m_rectOriginalClip);

		//
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PUNTO_SOPRA_PUNTO));

		// blocco il cursore nella finestra della sagoma //
		CRect rectTemp = m_rectPaintSagoma;
		ClientToScreen(&rectTemp);
		rectTemp.right--;
		rectTemp.bottom--;
		ClipCursor(&rectTemp);
	}

	EndWaitCursor();
}

int CDermoxPuntiPazienteDlg::TrovaPunto(CPoint& ptPoint)
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

BOOL CDermoxPuntiPazienteDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta == -120)
	{
		CDermoxPuntiPazienteDlg::OnVScroll(SB_PAGEDOWN, 0, NULL);
		return TRUE;
	}
	else if (zDelta == 120)
	{
		CDermoxPuntiPazienteDlg::OnVScroll(SB_PAGEUP, 0, NULL);
		return TRUE;
	}
	else
		return TRUE;

	CDialog::OnMouseWheel(nFlags, zDelta, pt);
}


void CDermoxPuntiPazienteDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//Add screen resolution condition

	/*int nDelta;
	int nMaxPos = m_rect.Height() - m_nCurHeight;
	switch (nSBCode)
	{
		case SB_LINEDOWN: case SB_PAGEDOWN:
			if (m_nScrollPos >= nMaxPos)
				nDelta = min(nMaxPos / 5, nMaxPos - m_nScrollPos) + 150;
			else
				nDelta = min(nMaxPos / 5, nMaxPos - m_nScrollPos);
			break;

		case SB_LINEUP: case SB_PAGEUP:
			if (m_nScrollPos >= nMaxPos)
				nDelta = -min(nMaxPos / 5, m_nScrollPos) - 150;
			else
				nDelta = -min(nMaxPos / 5, m_nScrollPos);

			break;
	
		case SB_THUMBPOSITION:
			nDelta = (int)nPos - m_nScrollPos;
			break;

		default:
			return;
	}
	m_nScrollPos += nDelta;
	SetScrollPos(SB_VERT, m_nScrollPos, TRUE);

	ScrollWindow(0, -nDelta);*/

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	//CEndoxResizableDlg::OnVScroll(nSBCode, nPos, pScrollBar);

}