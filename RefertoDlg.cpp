#include "stdafx.h"
#include "Endox.h"
#include "RefertoDlg.h"

#include <io.h>

#include "DLL_Imaging\h\AmBase64.h"
#include "DLL_Imaging\h\AmLogin.h"
#include "DLL_Imaging\h\AmSumatraPdfViewer.h"
#include "DLL_Imaging\h\ImgManager.h"
#include "DLL_Imaging\h\GetPatientExamDataService.h"

#include "AlbumForm.h"
#include "AnatomiaPatologicaForm.h"
#include "AnatomiaPatologicaPrestForm.h"
#include "BaseTreeObject.h"
#include "CardioDopoDynForm.h"
#include "CardioDuranteDynForm.h"
#include "CardioPrimaDynForm.h"
#include "CustomDate.h"
#include "EditDynForm2.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "FrasiRtfSet.h"
#include "FrasiTreeObject.h"
#include "ImageDicomDlg.h"
#include "ListaOsservazioniDlg.h"
#include "LogFileWriter.h"
#include "MaximizeDlg.h"
#include "MediciSet.h"
#include "MielogrammaDynForm.h"
#include "MmSystem.h"
#include "PazientiSet.h"
#include "PdfAnteprimaDlg.h"
#include "ReportsDefaultSet.h"
#include "SediEsameSet.h"
#include "TabellaStruttureSet.h"
#include "TabellaForm.h"
#include "UOSet.h"
#include "TipoEsameSet.h"
#include "MeasurementsSet.h"
#include "MeasurementsAliasMappingSet.h"
#include "EditMeasurementDlg.h"
#include "KeyboardMonitor.h" //Julio BUG 3457 - Texter
#include "MeasurementsSet.h" //Julio - correcao lista biometria
#include "ComboBoxSet.h"	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnesi)
#include "MeasurementsCalculationSet.h" //Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
#include "MeasurementsRulesSet.h" //Gabriel - BUG 5533 V2 - Regras medidas biométricas

// Marvel Carvalho - Bug 5511 Modifica envio anamnese DO via TXT no lugar de RTF
// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnesi)
#define _RTFLINESEPARATOR _T("{\\rtf1 \\pard \\brdrb \\brdrs\\brdrw10\\brsp20 {\\fs4\\~}\\par \\pard }")
#define _RTFLINEBLANK     _T("{\\rtf1 {\\pard \\par} }")
#define _TXTLINESEPARATOR _T("\r\n- - - - - - - - - - - - - - - - - - - -\r\n\r\n")
#define _TXTLINEBLANK     _T("\r\n")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSpellCheckerDlg CRefertoExDlg::m_WSpellChecker;

enum
{
	id_frasi,
	id_risposte,
	id_anomalie,
	id_immaginifilmati,
	id_altrireferti,
	id_frasirtf,
	id_tabella,
	id_checklist,
	id_anteprimastampa,
	id_pdf,
	id_measurements,
	id_references,
	id_anamnesi			// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
};

CRefertoExDlg::CRefertoExDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CRefertoExDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_bImClosing = FALSE;

	m_strFrase = "";

	m_nSelStart = 0;
	m_nSelLength = 0;
	m_nScrollx = 0;
	m_nScrolly = 0;

	m_pEsamiView = pEsamiView;
	m_pEsamiSet = pEsamiView->m_pEsamiSet;
	m_pDocManager = pEsamiView->m_pDocManager;

	m_lFamiglia = 0;

	m_sTipoEsame.Format("TipoEsame=%li", m_pEsamiSet->m_lIDEsame);

	m_FrasiSet.SetBaseFilter(m_sTipoEsame);

	m_pChecklistForm = NULL;
	m_pTabellaForm = NULL;

	m_bMeasurementUpdated = FALSE;
	m_bSpermChartMeasurementUpdated = FALSE; //Gabriel BUG 5533

	m_sConcentracao = ""; //Gabriel BUG 5533
	m_sMotilidadeProgressiva = ""; //Gabriel BUG 5533
	m_sMorfologia = ""; //Gabriel BUG 5533

	//

	m_brushSolidWhite.CreateSolidBrush(RGB_WHITE);

	m_lNumRefertiAct = 0;
	m_lNumRefertiTot = 0;

	CString sFilter;
	sFilter.Format("IDPaziente = %li AND IDEsame <> %li", m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);
	m_setVistaRefertiPaziente.SetOpenFilter(sFilter);
	if (m_setVistaRefertiPaziente.OpenRecordset("CRefertoExDlg::CRefertoExDlg"))
	{
		while (!m_setVistaRefertiPaziente.IsEOF())
		{
			m_lNumRefertiAct++;
			m_lNumRefertiTot++;

			m_setVistaRefertiPaziente.MoveNext();
		}
	}

	///////////////////////
	// Sandro 13/04/2017 //
	///////////////////////

	m_sReportDefault = CReportsDefaultSet().GetDefaultReport(m_pEsamiSet->m_lIDEsame);

	//

	m_bIsTextChanged = FALSE;
	m_sRTFSelText = "";

	m_hPdfPageCountThread = NULL;
	m_hEventExitPdfPageCountThread = ::CreateEvent(NULL, TRUE, FALSE, "EventExitPdfPageCountThread");

	m_uiPreview = -1;

	m_pPdfBuffer = NULL;

	m_bCheckBoxChecked = FALSE;

	m_bProcessOnEnChange = FALSE;	// Marvel Carvalho - Bug 3457 (FIX) TEXTER

	m_sArrayPdf = NULL;

	m_ToolTipLaudoAnterior = new CToolTipCtrl();

}

CRefertoExDlg::~CRefertoExDlg()
{
	if (m_sArrayPdf != NULL)
	{
		delete[] m_sArrayPdf;
		m_sArrayPdf = NULL;
	}

	if (m_ToolTipLaudoAnterior != NULL)
	{
		delete m_ToolTipLaudoAnterior;
		m_ToolTipLaudoAnterior = NULL;
	}

	if (m_pPdfBuffer != NULL)
	{
		delete m_pPdfBuffer;
		m_pPdfBuffer = NULL;
	}

	DistruggiListaFrasi();	// same as delete m_ctrlTreeListFrasi (plineaInfo)

	POSITION pos = m_ImgListOrgani.GetHeadPosition();

	while (pos != NULL)
	{
		DeleteObject(m_ImgListOrgani.GetAt(pos).img.hBmp);
		m_ImgListOrgani.GetNext(pos);
	}

	m_ImgListOrgani.RemoveAll();

	if (m_listImage != NULL)
	{
		int iCount = m_listImage.GetImageCount();
		int iCurr = 0;
		while (iCurr < iCount)
		{
			m_listImage.Remove(iCurr);
			iCurr++;
		}

		m_listImage.DeleteImageList();
		m_listImage.DeleteTempMap();
	}

	if (m_pChecklistForm != NULL)
	{
		m_pChecklistForm->DestroyWindow();

		delete m_pChecklistForm;
		m_pChecklistForm = NULL;
	}

	if (m_pTabellaForm != NULL)
	{
		m_pTabellaForm->DestroyWindow();

		delete m_pTabellaForm;
		m_pTabellaForm = NULL;
	}

	m_brushSolidWhite.DeleteObject();
	m_setVistaRefertiPaziente.CloseRecordset("CRefertoExDlg::~CRefertoExDlg");

	m_ctrlButtonBar.DestroyWindow();
	delete m_ctrlButtonBar;

	m_ctrlText.DestroyWindow();
	delete m_ctrlText;

	m_ctrlTextAltriReferti.DestroyWindow();
	delete m_ctrlTextAltriReferti;

	m_ctrlTextReferences.DestroyWindow();
	delete m_ctrlTextReferences;

	m_ctrlTextTabAnamnesi.DestroyWindow();
	delete m_ctrlTextTabAnamnesi;

}

BEGIN_MESSAGE_MAP(CRefertoExDlg, CEndoxResizableDlg)

	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_SIZE()

	ON_COMMAND(IDC_RTF_TABLE, OnBnClickedBtnInsertTable)
	ON_COMMAND(IDC_RTF_MAKEUPPER, OnBnClickedBtnMakeUpper)
	ON_COMMAND(IDC_RTF_MAKENORMAL, OnBnClickedBtnMakeNormal)
	ON_COMMAND(IDC_RTF_MAKELOWER, OnBnClickedBtnMakeLower)
	ON_COMMAND(IDC_RTF_FONT, OnBnClickedBtnRtfFont) //Julio - BUG 4392 Edicao de texto

	ON_BN_CLICKED(IDC_BTN_COPYPREVREF, OnBtnCopyPrevRef)
	ON_BN_CLICKED(IDC_BTN_SPEAK, OnBtnSpeak)
	ON_BN_CLICKED(IDC_BTN_SFORZO, OnBtnSforzo)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBtnPreview)
	ON_LBN_DBLCLK(IDC_ALBERO_FRASI, OnDblclkListaFrasi)
	ON_BN_CLICKED(IDC_INSERT_FRASI, OnInsertFrasi)
	ON_LBN_SELCHANGE(IDC_ALBERO_FRASI, OnSelchangeListaFrasi)
	ON_NOTIFY(TCN_SELCHANGE, IDC_FAMIGLIE, OnSelchangeFamiglia)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FRASIRTF, OnNMDblclkListFrasiRtf)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IMAGE, OnNMDblclkListImage)

	ON_BN_CLICKED(IDC_BTN_PREV, OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_NEXT, OnBnClickedBtnNext)

	ON_EN_CHANGE(IDC_EDIT_RTF_CODICE, OnEnChangeEditRtfCodiceFrase)
	ON_EN_CHANGE(IDC_EDIT_RTF_FRASE, OnEnChangeEditRtfCodiceFrase)

	ON_MESSAGE(WM_ADD_RTFTEXT_TO_REPORT, OnAddRtfTextToReport)
	ON_MESSAGE(WM_ADD_TXTTEXT_TO_REPORT, OnAddTxtTextToReport)

	ON_MESSAGE(EPM_THREAD_PDF_COUNT_PAGES_UPDATE, OnThreadPdfCountPagesUpdate)
	// ON_MESSAGE(EPM_THREAD_PDF_COUNT_PAGES_END, OnThreadPdfCountPagesEnd)

	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)

	ON_BN_CLICKED(IDC_BTN_PREV2, OnBnClickedBtnPrev2)
	ON_BN_CLICKED(IDC_BTN_NEXT2, OnBnClickedBtnNext2)
	ON_BN_CLICKED(IDC_BTN_ZOOMOUT, OnBnClickedBtnZoomOut)
	ON_BN_CLICKED(IDC_BTN_ZOOMIN, OnBnClickedBtnZoomIn)

	ON_BN_CLICKED(IDC_BTN_COPY, &CRefertoExDlg::OnBnClickedBtnCopy)
	ON_BN_CLICKED(IDC_BTN_GET_LAUDO_ANTERIOR, &CRefertoExDlg::OnBnClickedBtnGetLaudoAnterior)
	ON_BN_CLICKED(IDC_BTN_CONSULTA_RESULTADO, &CRefertoExDlg::OnBnClickedBtnConsultaResultado)
	ON_BN_CLICKED(IDC_CHECK1, &CRefertoExDlg::OnBnClickedCheck1)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PDF, &CRefertoExDlg::OnNMDblclkListPdf)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MEASUREMENTS, &CRefertoExDlg::OnNMDblclkListMeasurements)

	ON_MESSAGE(EPM_KEYBOARD_PRESS, OnKeyboardPress) //Julio BUG 3457 - Texter

	ON_EN_SETFOCUS(IDC_EDIT_RTF_CODICE, &CRefertoExDlg::OnEnSetfocusEditRtfCodice) // Marvel Carvalho - Bug 3457 (FIX) TEXTER
	ON_EN_SETFOCUS(IDC_EDIT_RTF_FRASE, &CRefertoExDlg::OnEnSetfocusEditRtfFrase)   // Marvel Carvalho - Bug 3457 (FIX) TEXTER	

	//ON_MESSAGE(WM_REFERTO_END_EDIT, SaveEditedMeasurement) //Julio - correcao lista biometria
	ON_BN_CLICKED(IDC_BTN_SAVEMEASUREMENTS, &CRefertoExDlg::SaveEditedMeasurement) //Julio - correcao lista biometria

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MEASUREMENTS, OnItemChangedList) //Gabriel - BUG 5533 V2
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CRefertoExDlg, CEndoxResizableDlg)
	ON_EVENT(CRefertoExDlg, IDC_TEXTCONTROL, 1, OnTextControlChange, VTS_NONE)
	ON_EVENT(CRefertoExDlg, IDC_TEXTCONTROL, DISPID_MOUSEDOWN, OnTextControlMouseDown, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

void CRefertoExDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTONBAR, m_ctrlButtonBar);
	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlText);
	m_ctrlText.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
	DDX_Control(pDX, IDC_FAMIGLIE, m_ctrlFamiglia);
	DDX_Text(pDX, IDC_FRASE, m_strFrase);
	DDX_Control(pDX, IDC_LIST_IMAGE, m_ctrlListImage);

	DDX_Control(pDX, IDC_INSERT_FRASI, m_ctrlButtonFrasi);
	DDX_Control(pDX, IDC_BTN_SPEAK, m_ctrlButtonSpeak);
	DDX_Control(pDX, IDC_BTN_SFORZO, m_ctrlButtonSforzo);
	DDX_Control(pDX, IDC_BTN_PREVIEW, m_ctrlButtonPreview);
	DDX_Control(pDX, IDC_BTN_COPYPREVREF, m_ctrlButtonCopyReport);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlButtonOK);

	DDX_Control(pDX, IDC_STATIC_CHECKLIST, m_ctrlStaticChecklistForm);
	DDX_Control(pDX, IDC_STATIC_TABELLA, m_ctrlStaticTabellaForm);

	// id_altrireferti //
	DDX_Control(pDX, IDC_EDIT_INFO_LAUDOANTERIOR, m_ctrlEditInfoLaudoAnterior);
	DDX_Control(pDX, IDC_TEXTCONTROL_ALTRIREFERTI, m_ctrlTextAltriReferti);
	m_ctrlTextAltriReferti.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
	DDX_Control(pDX, IDC_BTN_PREV, m_ctrlBtnPrev);
	DDX_Control(pDX, IDC_BTN_NEXT, m_ctrlBtnNext);
	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_BTN_COPY, m_ctrlBtnCopy);
	DDX_Control(pDX, IDC_BTN_GET_LAUDO_ANTERIOR, m_ctrlBtnGetLaudoAnterior);
	DDX_Control(pDX, IDC_BTN_CONSULTA_RESULTADO, m_ctrlBtnConsultaResultado);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade);
	//

	// id_frasirtf //
	DDX_Control(pDX, IDC_EDIT_RTF_CODICE, m_ctrlEditRtfCodice);
	DDX_Control(pDX, IDC_EDIT_RTF_FRASE, m_ctrlEditRtfFrase);
	DDX_Control(pDX, IDC_LIST_FRASIRTF, m_ctrlListFrasiRTF);
	//

	// id_pdf
	DDX_Control(pDX, IDC_LIST_PDF, m_ctrlListPdf);
	//

	// id_measurements
	DDX_Control(pDX, IDC_LIST_MEASUREMENTS, m_ctrlListMeasurements);
	DDX_Control(pDX, IDC_BTN_SAVEMEASUREMENTS, m_ctrlBtnSaveMeasurements); //Julio - correcao lista biometria
	//

	// id_references	
	DDX_Control(pDX, IDC_TEXTCONTROL_REFERENCES, m_ctrlTextReferences);
	m_ctrlTextReferences.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
	//

	// id_anamnesi
	DDX_Control(pDX, IDC_TEXTCONTROL_ANAMNESI, m_ctrlTextTabAnamnesi);
	m_ctrlTextTabAnamnesi.SendMessage(WM_USER + 1013, 1, 0); // Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
	//

	DDX_Control(pDX, IDC_BTN_PREV2, m_ctrlBtnPrevPdfPage);
	DDX_Control(pDX, IDC_BTN_NEXT2, m_ctrlBtnNextPdfPage);
	DDX_Control(pDX, IDC_BTN_ZOOMIN, m_ctrlBtnZoomIn);
	DDX_Control(pDX, IDC_BTN_ZOOMOUT, m_ctrlBtnZoomOut);
}

HBRUSH CRefertoExDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CEndoxResizableDlg::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_00:
	case IDC_STATIC_01:
	case IDC_STATIC_02:
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_brushSolidWhite;
	}
	case IDC_STATIC_PAGECOUNT:
	{
		pDC->SetTextColor(RGB_RED);
		break;
	}
	}

	return hBrush;
}

void CRefertoExDlg::OnDestroy()
{
	if (CSpellCheckerDlg* pWSpell = GetWSpell())
		pWSpell->SetTextControl(NULL);

	//

	SetEvent(m_hEventExitPdfPageCountThread);
	WaitForSingleObject(m_hPdfPageCountThread, INFINITE);

	CloseHandle(m_hEventExitPdfPageCountThread);
	CloseHandle(m_hPdfPageCountThread);

	m_hEventExitPdfPageCountThread = NULL;
	m_hPdfPageCountThread = NULL;

	//

	PdfViewer_Close(m_uiPreview);
	PdfViewer_Finalize(m_uiPreview);

	if (m_pPdfBuffer != NULL)
	{
		delete m_pPdfBuffer;
		m_pPdfBuffer = NULL;
	}

	//

	CEndoxResizableDlg::OnDestroy();
}

BOOL CRefertoExDlg::OnInitDialog()
{
	VERIFY(m_ctrlTreeListFrasi.SubclassDlgItem(IDC_ALBERO_FRASI, this));

	CEndoxResizableDlg::OnInitDialog();
	m_ctrlToolbar.Create(IDC_STATIC_FRAME4, this);

	CKeyboardMonitor::Get()->Start(this->GetSafeHwnd(), EPM_KEYBOARD_PRESS); //Julio BUG 3457 - Texter

	m_uiPreview = PdfViewer_Initialize(GetDlgItem(IDC_PDF_PLACE)->GetSafeHwnd());

	HKEY hKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\GST\\PhonemA", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
		m_ctrlButtonSpeak.ShowWindow(SW_SHOW);

	// Sandro 13/10/2016 //

	if ((m_pEsamiView->m_pDynForm[sub_cardio_prima] != NULL) || (m_pEsamiView->m_pDynForm[sub_cardio_durante] != NULL) || (m_pEsamiView->m_pDynForm[sub_cardio_dopo] != NULL) || (m_pEsamiView->m_pDynForm[sub_mielogramma] != NULL))
		m_ctrlButtonSforzo.ShowWindow(SW_SHOW);

	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
		m_ctrlButtonPreview.ShowWindow(SW_SHOW);

	//

	AddAnchor(IDC_FAMIGLIE, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_ALBERO_FRASI, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_STATIC_CHECKLIST, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_STATIC_TABELLA, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_FRASE, CSize(0, 100), CSize(50, 100));
	AddAnchor(IDC_INSERT_FRASI, CSize(0, 100), CSize(50, 100));
	AddAnchor(IDC_LIST_IMAGE, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_STATIC_LINE1, CSize(50, 0), CSize(50, 100));
	AddAnchor(IDC_STATIC_FRAME1, CSize(50, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_FRAME4, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_FRAME2, CSize(50, 0), CSize(100, 100));
	AddAnchor(IDC_STATIC_PAGECOUNT, CSize(50, 100), CSize(100, 100));
	AddAnchor(IDC_STATIC_LINE2, CSize(50, 100), CSize(100, 100));
	AddAnchor(IDC_BTN_COPYPREVREF, CSize(50, 100), CSize(60, 100));
	AddAnchor(IDC_BTN_SPEAK, CSize(60, 100), CSize(70, 100));
	AddAnchor(IDC_BTN_SFORZO, CSize(60, 100), CSize(70, 100));
	AddAnchor(IDC_BTN_PREVIEW, CSize(70, 100), CSize(80, 100));
	AddAnchor(IDC_BTN_UNDO, CSize(80, 100), CSize(90, 100));
	AddAnchor(IDC_BTN_SAVE, CSize(90, 100), CSize(100, 100));

	// id_altrireferti //

	AddAnchor(IDC_STATIC_FRAME3, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_BTN_PREV, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_NEXT, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_STATIC_00, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_STATIC_01, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_STATIC_02, CSize(0, 100), CSize(50, 100));
	AddAnchor(IDC_BTN_COPY, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_BTN_GET_LAUDO_ANTERIOR, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_BTN_CONSULTA_RESULTADO, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_EDIT_INFO_LAUDOANTERIOR, CSize(0, 0), CSize(50, 0));
	AddAnchor(IDC_CHECK1, CSize(0, 100), CSize(0, 100));

	// id_frasirtf //

	AddAnchor(IDC_EDIT_RTF_CODICE, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_EDIT_RTF_FRASE, CSize(0, 0), CSize(50, 0));
	AddAnchor(IDC_LIST_FRASIRTF, CSize(0, 0), CSize(50, 100));

	// id_anteprimastampa //

	AddAnchor(IDC_PDF_PLACE, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_BTN_PREV2, CSize(20, 100), CSize(20, 100));
	AddAnchor(IDC_STATIC_PAGE, CSize(20, 100), CSize(20, 100));
	AddAnchor(IDC_BTN_NEXT2, CSize(20, 100), CSize(20, 100));
	AddAnchor(IDC_BTN_ZOOMOUT, CSize(30, 100), CSize(30, 100));
	AddAnchor(IDC_STATIC_ZOOM, CSize(30, 100), CSize(30, 100));
	AddAnchor(IDC_BTN_ZOOMIN, CSize(30, 100), CSize(30, 100));

	// id_pdf //
	AddAnchor(IDC_LIST_PDF, CSize(0, 0), CSize(50, 100));

	// id_measurements //
	AddAnchor(IDC_LIST_MEASUREMENTS, CSize(0, 0), CSize(50, 100));
	AddAnchor(IDC_BTN_SAVEMEASUREMENTS, CSize(50, 100), CSize(50, 100)); //Julio - correcao lista biometria

	// id_references //
	AddAnchor(IDC_STATIC_FRAME5, CSize(0, 0), CSize(50, 100));

	// id_anamnesi //
	AddAnchor(IDC_STATIC_FRAME6, CSize(0, 0), CSize(50, 100));	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)

	// --- //

	m_ctrlButtonFrasi.SetFont(&theApp.m_fontBold);
	m_ctrlStatic00.SetFont(&theApp.m_fontBold);
	m_ctrlStatic01.SetFont(&theApp.m_fontBold);
	m_ctrlStatic02.SetFont(&theApp.m_fontBold);
	m_ctrlEditInfoLaudoAnterior.SetFont(&theApp.m_fontBig);

	m_ctrlEditInfoLaudoAnterior.EnableWindow(FALSE);

	GetDlgItem(IDC_STATIC_PAGECOUNT)->SetFont(&theApp.m_fontBig);

	m_ctrlTextReferences.SetFont(&theApp.m_fontNormal);

	m_ctrlTextTabAnamnesi.SetFont(&theApp.m_fontNormal);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
	// --- //

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	///

	m_ctrlListFrasiRTF.SetExtendedStyle(m_ctrlListFrasiRTF.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListFrasiRTF.InsertColumn(0, "", LVCFMT_CENTER, 0);
	m_ctrlListFrasiRTF.InsertColumn(1, theApp.GetMessageString(IDS_CODICE), LVCFMT_LEFT, 133);
	m_ctrlListFrasiRTF.InsertColumn(2, theApp.GetMessageString(IDS_FRASE), LVCFMT_LEFT, 133);
	m_ctrlListFrasiRTF.InsertColumn(3, "", LVCFMT_CENTER, 0);

	///

	int nItem = 0;
	CString sTextTemp;
	TC_ITEM TabCtrlItem;

	/// Julio - BUG 3706 - Modifica ordine campi referto dlg

	//1- Checklist
	if (theApp.m_bRefertazioneUsaChecklist)
	{
		sTextTemp = theApp.GetMessageString(IDS_CHECKLIST);
		TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
		TabCtrlItem.lParam = id_checklist;
		TabCtrlItem.pszText = sTextTemp.GetBuffer();
		m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
		sTextTemp.ReleaseBuffer();
		nItem++;

		CChecklistForm::CreateFormEx(this, &m_ctrlStaticChecklistForm, m_pEsamiView, &m_pChecklistForm);
	}

	m_ctrlEditRtfFrase.SetWindowText(_T("pesquisar...")); // Marvel Carvalho - Bug 3457 (FIX) TEXTER
	m_ctrlEditRtfCodice.SetWindowText(_T("pesquisar...")); // Marvel Carvalho - Bug 3457 (FIX) TEXTER

	//2- Frases
	if (theApp.m_bRefertazioneUsaFrasiStandard)
	{
		sTextTemp = theApp.GetMessageString(IDS_FRASI);
		TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
		TabCtrlItem.lParam = id_frasi;
		TabCtrlItem.pszText = sTextTemp.GetBuffer();
		m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
		sTextTemp.ReleaseBuffer();
		nItem++;

		sTextTemp = theApp.GetMessageString(IDS_RISPOSTE);
		TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
		TabCtrlItem.lParam = id_risposte;
		TabCtrlItem.pszText = sTextTemp.GetBuffer();
		m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
		sTextTemp.ReleaseBuffer();
		nItem++;

		sTextTemp = theApp.GetMessageString(IDS_ANOMALIE);
		TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
		TabCtrlItem.lParam = id_anomalie;
		TabCtrlItem.pszText = sTextTemp.GetBuffer();
		m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
		sTextTemp.ReleaseBuffer();
		nItem++;
	}

	//2- Frases
	if (theApp.m_bRefertazioneUsaFrasiRTF)
	{
		sTextTemp = theApp.GetMessageString(IDS_FRASI);
		TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
		TabCtrlItem.lParam = id_frasirtf;
		TabCtrlItem.pszText = sTextTemp.GetBuffer();
		m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
		sTextTemp.ReleaseBuffer();
		nItem++;

		PreparaListaFrasi();
	}

	//3- Laudos anteriores
	sTextTemp = theApp.GetMessageString(IDS_ALTRIREFERTI);
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_altrireferti;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	m_ctrlBtnConsultaResultado.EnableWindow(FALSE);

	CWnd* pWndLaudoAnterior = GetDlgItem(IDC_BTN_GET_LAUDO_ANTERIOR);
	m_ToolTipLaudoAnterior->Create(this);
	m_ToolTipLaudoAnterior->AddTool(pWndLaudoAnterior, "Último laudo da Mesma Sigla de qualquer unidade do Grupo Fleury");
	m_ToolTipLaudoAnterior->Activate(TRUE);

	//4- Medidas biometricas
	m_ctrlListMeasurements.SetExtendedStyle(m_ctrlListPdf.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListMeasurements.InsertColumn(0, "ALIAS", LVCFMT_LEFT,133);
	m_ctrlListMeasurements.InsertColumn(1, "MEDIDA", LVCFMT_LEFT, 133);
	m_ctrlListMeasurements.InsertColumn(2, "VALOR", LVCFMT_RIGHT, 133);
	m_ctrlListMeasurements.InsertColumn(3, "UNIDADE", LVCFMT_CENTER, 133);
	m_ctrlListMeasurements.InsertColumn(4, "", LVCFMT_CENTER, 0);
	if (theApp.m_bAtivaEspermograma) m_ctrlListMeasurements.InsertColumn(5, "", LVCFMT_CENTER, 0); //Gabriel - BUG 5533 V2

	m_ctrlListMeasurements.SetNotificationChangeValueMessage(WM_REFERTO_END_EDIT); //Julio - correcao lista biometria

	sTextTemp = theApp.GetMessageString(IDS_LIST_MISURI);
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_measurements;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	//RiempiListaMeasurements();

	m_ctrlListMeasurements.SetColumnWidth(0, LVSCW_AUTOSIZE);
	m_ctrlListMeasurements.SetColumnWidth(1, LVSCW_AUTOSIZE);
	m_ctrlListMeasurements.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListMeasurements.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListMeasurements.SetColumnWidth(4, 0);
	if (theApp.m_bAtivaEspermograma) m_ctrlListMeasurements.SetColumnWidth(5, 0); //Gabriel - BUG 5533 V2

	//5- Preview impressao
	sTextTemp = theApp.GetMessageString(IDS_ANTEPRIMASTAMPA);
	TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
	TabCtrlItem.lParam = id_anteprimastampa;
	TabCtrlItem.pszText = sTextTemp.GetBuffer();
	m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
	sTextTemp.ReleaseBuffer();
	nItem++;

	//6- Tabela de medidas
	if (CTabellaStruttureSet().GetCount(m_pEsamiSet->m_lIDEsame) > 0)
	{
		sTextTemp = theApp.GetMessageString(IDS_MISURE);
		TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
		TabCtrlItem.lParam = id_tabella;
		TabCtrlItem.pszText = sTextTemp.GetBuffer();
		m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
		sTextTemp.ReleaseBuffer();
		nItem++;

		CTabellaForm::CreateFormEx(this, &m_ctrlStaticTabellaForm, m_pEsamiView, &m_ctrlText, &m_pTabellaForm);
	}

	//7- Valores de referencia	
	if (!theApp.m_sPathValoresReferencia.IsEmpty())
	{
		sTextTemp = theApp.GetMessageString(IDS_VALORESREFERENCIA);
		TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
		TabCtrlItem.lParam = id_references;
		TabCtrlItem.pszText = sTextTemp.GetBuffer();
		m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
		sTextTemp.ReleaseBuffer();
		nItem++;

		CaricaTestoReferences();
	}

	//8- PDFs anexados		
	m_ctrlListPdf.SetExtendedStyle(m_ctrlListPdf.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListPdf.InsertColumn(0, "", LVCFMT_CENTER, 0);
	m_ctrlListPdf.InsertColumn(1, "NOME", LVCFMT_LEFT, 133);
	m_ctrlListPdf.InsertColumn(2, "DATA", LVCFMT_LEFT, 133);
	m_ctrlListPdf.InsertColumn(3, "", LVCFMT_CENTER, 0);

	if (m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, DOCUMENTS_NOT_EXPORT) > 0 ||
		m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, DOCUMENTS_ONLY_EXPORT) > 0)
	{
		sTextTemp = theApp.GetMessageString(IDS_LIST_PDF);
		TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
		TabCtrlItem.lParam = id_pdf;
		TabCtrlItem.pszText = sTextTemp.GetBuffer();
		m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
		sTextTemp.ReleaseBuffer();
		nItem++;

		RiempiListaPdf();
	}

	//9- Imagens		
	CImgList listImgCount;
	if (FALSE)
		//if (m_pEsamiView->m_pImgManager->GetImgList(&listImgCount) > 0)
	{
		sTextTemp = theApp.GetMessageString(IDS_IMMAGINIFILMATI);
		TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
		TabCtrlItem.lParam = id_immaginifilmati;
		TabCtrlItem.pszText = sTextTemp.GetBuffer();
		m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
		sTextTemp.ReleaseBuffer();
		nItem++;

		// Sandro Gallina - 08/07/2004 --> //
		m_listImage.Create(HSIZE_PAL_4, VSIZE_PAL_4, ILC_COLOR32, 0, 1);
		m_ctrlListImage.SetExtendedStyle(m_ctrlListImage.GetExtendedStyle() | LVS_EX_BORDERSELECT);
		m_ctrlListImage.SetImageList(&m_listImage, LVSIL_NORMAL);

		int iHSpace;
		int iVSpace;
		CRect rectTemp;
		m_ctrlListImage.GetClientRect(&rectTemp);
		m_ctrlListImage.ScreenToClient(&rectTemp);
		iHSpace = (rectTemp.Width() - 17) / 2;
		iVSpace = iHSpace - HSIZE_PAL_4 + VSIZE_PAL_4;
		m_ctrlListImage.SetIconSpacing(iHSpace, iVSpace);
		// <-- Sandro Gallina - 08/07/2004 //

		RiempiListaImmagini();
	}
	listImgCount.RemoveAll();

	//10- Anamnesi
#ifdef _BETA	
	if (CaricaTestoAnamnesi(TRUE))
#else 
	if (CaricaTestoAnamnesi(FALSE))
#endif
	{
		sTextTemp = theApp.GetMessageString(IDS_REFERTO_TAB_ANAMNESI);
		TabCtrlItem.mask = TCIF_PARAM | TCIF_TEXT;
		TabCtrlItem.lParam = id_anamnesi;
		TabCtrlItem.pszText = sTextTemp.GetBuffer();
		m_ctrlFamiglia.InsertItem(nItem, &TabCtrlItem);
		sTextTemp.ReleaseBuffer();
		nItem++;
	}

	///

	m_ctrlTreeListFrasi.SetFamily(m_lFamiglia);

	m_ctrlText.SetButtonBarHandle((long)m_ctrlButtonBar.GetSafeHwnd());
	m_ctrlText.SetFontName(g_sReportFaceName);
	m_ctrlText.SetFontSize(g_nReportSize);
	m_ctrlText.SetFontBold(g_bReportBold);
	m_ctrlText.SetFontItalic(g_bReportItalic);
	m_ctrlText.SetFontUnderline(g_bReportUnderline);

	if (!m_pEsamiSet->IsEOF())
	{
		if (m_pEsamiSet->m_sConclusioni.IsEmpty() == FALSE)
			SetReferto(m_pEsamiSet->m_sConclusioni);
		else
			SetReferto(m_pEsamiSet->m_sRefertoTestoRtf);
	}

	//
	CString sRefertoTemp = m_ctrlText.GetText();
	sRefertoTemp.Trim();
	if (sRefertoTemp.IsEmpty())
	{
		if ((theApp.m_lRefertoAllineamentoTestoDefault < 0) || (theApp.m_lRefertoAllineamentoTestoDefault > 2))
			m_ctrlText.SetAlignment(3); // testo giustificato //
		else
			m_ctrlText.SetAlignment((short)theApp.m_lRefertoAllineamentoTestoDefault);
		m_ctrlText.SendMessage(WM_LBUTTONUP);
	}

	// localizzo il dialogo //
	theApp.LocalizeDialog(this, CRefertoExDlg::IDD, "RefertoExDlg");

	// ricambio il titolo dopo la localizzazione //
	CString strTmp;

	//Gabriel BUG 6225 - Lista DO
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
	{
		if (theApp.m_bRefertoMostraEtaPazienteTitolo)
			strTmp.Format(theApp.GetMessageString(IDS_REFERTOEXDLG_TITLE) + " - " + GetStringEta(m_pEsamiView->m_pPazientiSet->m_lNatoIlCustom, m_pEsamiSet->m_lData, FormatoEta::AnnoMese) + " - " + m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto001, m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome);
		else
			strTmp.Format(theApp.GetMessageString(IDS_REFERTOEXDLG_TITLE) + " - " + m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto001, m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome);
	}
	else
	{
		strTmp.Format(theApp.GetMessageString(IDS_REFERTOEXDLG_TITLE), m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome);
	}
	SetWindowText(strTmp);

	// 4 //

	if (m_lNumRefertiTot > 0)
	{
		m_setVistaRefertiPaziente.MoveLast();
		CaricaTestoAltroReferto();

		if (m_lNumRefertiTot > 1)
			m_ctrlBtnPrev.EnableWindow(TRUE);
	}

	// Sandro 06/05/2015 //	
	OnSelchangeFamiglia(NULL, NULL);

	// Sandro 13/04/2017 // creo thread per il calcolo dinamico del numero di pagine in stampa //

	if (!m_sReportDefault.IsEmpty())
	{
		if (_access(theApp.m_sDirProg + "\\EndoxReportMaker\\EndoxReportMaker.exe", 06) == 00)
		{
			m_hPdfPageCountThread = ::CreateThread(NULL, 0, ThreadPdfPageCount, this, 0, NULL);
		}
		else
		{
			m_sReportDefault = "";
#ifdef _DEBUG
			//theApp.AfxMessageBoxEndo(IDS_REPORT_MAKER_NON_PRESENTE);
#else
			theApp.AfxMessageBoxEndo(IDS_REPORT_MAKER_NON_PRESENTE);
#endif
		}
	}
	else
	{
		m_sReportDefault = "";
		theApp.AfxMessageBoxEndo(IDS_NESSUN_REPORT_DEFAULT_DEFINITO);
	}

	return TRUE;
}

void CRefertoExDlg::RiempiListaMeasurements()
{
	m_ctrlListMeasurements.SetRedraw(FALSE);
	m_ctrlListMeasurements.DeleteAllItems();
	long nItem = 0;

	//Gabriel - BUG 5533 V2 - Filtro por UOm_listRules
	CString sFilterUO;
	sFilterUO.Format("UO = %li", theApp.m_lUO);

	CString sFilterCalc = "";
	CString sFilterRules = "";
	m_listCalcId.RemoveAll();
	m_listCalc.RemoveAll();
	m_listRulesId.RemoveAll();
	m_listRules.RemoveAll();

	//adicionar todas as medidas mesmo que sem valor
	CMeasurementsAliasMappingSet mapSet;
	mapSet.SetOpenFilter(sFilterUO);
	mapSet.SetSortRecord("NOMEPARAMETRO");
	if (mapSet.OpenRecordset("CRefertoExDlg::RiempiListaMeasurements"))
	{
		while (!mapSet.IsEOF())
		{
			//m_ctrlListMeasurements.InsertItem(nItem, mapSet.m_sAlias); //Julio - correcao lista biometria
			
			m_ctrlListMeasurements.InsertItem(nItem, "");
			m_ctrlListMeasurements.SetItemData(nItem, -1);
			m_ctrlListMeasurements.SetItemText(nItem, 0, mapSet.m_sAlias);
			m_ctrlListMeasurements.SetItemText(nItem, 1, mapSet.m_sNomeParametro);
			m_ctrlListMeasurements.SetItemText(nItem, 2, "");
			m_ctrlListMeasurements.SetItemText(nItem, 3, "");
			m_ctrlListMeasurements.SetItemText(nItem, 4, "");
			
			if (theApp.m_bAtivaEspermograma)
			{
				CString sId;
				sId.Format("%li", mapSet.m_lID);
				m_ctrlListMeasurements.SetItemText(nItem, 5, sId);

				sFilterCalc = sFilterCalc + sId + ",";
				sFilterRules = sFilterRules + sId + ",";
			}

			m_ctrlListMeasurements.SetColumnWidth(0, LVSCW_AUTOSIZE);
			//verificar se a medida adicionada tem um valor populado
			CString sFilter;
			sFilter.Format("IDESAME = %li AND ALIAS = '%s'", m_pEsamiSet->m_lContatore, mapSet.m_sAlias);

			CMeasurementsSet set;
			set.SetBaseFilter(sFilter);

			if (set.OpenRecordset("CRefertoExDlg::RiempiListaMeasurements"))
			{
				if (!set.IsEOF())
				{
					CString sValue = set.m_sNumericValue;
					sValue.Replace(",", ".");
					float fValue = (float)atof(sValue);
					CString sNumericValue = CMeasurementsAliasMappingSet().IsNumeric(mapSet.m_lID) == TRUE ? FormatNumber(mapSet.m_lID, set.m_sNumericValue, fValue) : set.m_sNumericValue;
					m_ctrlListMeasurements.SetItemData(nItem, set.m_lID);
					m_ctrlListMeasurements.SetItemText(nItem, 2, sNumericValue);
					m_ctrlListMeasurements.SetItemText(nItem, 3, set.m_sCodeValue);
					m_ctrlListMeasurements.SetItemText(nItem, 4, "");
					//Gabriel BUG 5533
					if (set.m_sAlias == "CONCENTRACAO TOTAL DA AMOSTRA")
					{
						m_sConcentracao = set.m_sNumericValue;
					}
					if (set.m_sAlias == "ESP PROGRES PR")
					{
						//CheckVitalityMeasurement(set.m_sNumericValue);
						m_sMotilidadeProgressiva = set.m_sNumericValue;

					}
					if (set.m_sAlias == "MORF ESTRITA")
					{
						m_sMorfologia = set.m_sNumericValue;
					}
				}
				set.CloseRecordset("CRefertoExDlg::RiempiListaMeasurements");
			}
			//
			nItem++;
			mapSet.MoveNext();
		}
		mapSet.CloseRecordset("CRefertoExDlg::RiempiListaMeasurements");
	}

	//Gabriel - BUG 5533 V2
	if (theApp.m_bAtivaEspermograma && !sFilterCalc.Trim().IsEmpty())
	{
		sFilterCalc = "MEASUREMENT1 IN (" + sFilterCalc + ")";
		sFilterCalc.Delete(sFilterCalc.GetLength() - 2, 1);

		CMeasurementsCalculationSet setCalc;
		setCalc.SetBaseFilter(sFilterCalc);

		if (setCalc.OpenRecordset("CRefertoExDlg::RiempiListaMeasurements"))
		{
			while (!setCalc.IsEOF())
			{
				tagFIELDCALC tag;
				tag.lMeasurement1 = setCalc.m_lMeasurement1;
				tag.lMeasurement2 = setCalc.m_lMeasurement2;
				tag.lMeasurement3 = setCalc.m_lMeasurement3;
				tag.lMeasurement4 = setCalc.m_lMeasurement4;
				tag.lIDCalc = setCalc.m_lIDCalc;
				tag.fValue1 = setCalc.m_fValue1;

				m_listCalcId.AddTail(setCalc.m_lMeasurement1);
				m_listCalc.AddTail(tag);
				setCalc.MoveNext();
			}
			setCalc.CloseRecordset("CRefertoExDlg::RiempiListaMeasurements");
		}

		sFilterRules = "MEASUREMENTCONDITION IN (" + sFilterRules + ")";
		sFilterRules.Delete(sFilterRules.GetLength() - 2, 1);

		CMeasurementsRulesSet setRule;
		setRule.SetBaseFilter(sFilterRules);

		if (setRule.OpenRecordset("CRefertoExDlg::RiempiListaMeasurements"))
		{
			while (!setRule.IsEOF())
			{
				tagFIELDRULE tag;
				tag.lMeasurementCondition = setRule.m_lMeasurementCondition;
				tag.lMeasurementRule = setRule.m_lMeasurementRule;
				tag.lIDCondition = setRule.m_lIDCondition;
				tag.lIDRule = setRule.m_lIDRule;
				strcpy_s(tag.szValueCondition1, setRule.m_sValueCondition1);
				strcpy_s(tag.szValueCondition2, setRule.m_sValueCondition2);

				m_listRulesId.AddTail(setRule.m_lMeasurementRule);
				m_listRules.AddTail(tag);
				setRule.MoveNext();
			}
			setRule.CloseRecordset("CRefertoExDlg::RiempiListaMeasurements");
		}
	}

	//--//

	m_ctrlListMeasurements.SetColumnWidth(0, LVSCW_AUTOSIZE);
	m_ctrlListMeasurements.SetColumnWidth(1, LVSCW_AUTOSIZE);
	m_ctrlListMeasurements.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListMeasurements.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListMeasurements.SetColumnWidth(4, LVSCW_AUTOSIZE);
	if (theApp.m_bAtivaEspermograma)
	{
		m_ctrlListMeasurements.SetColumnWidth(5, LVSCW_AUTOSIZE);
		Recalculate();
	}


	m_ctrlListMeasurements.SetRedraw(TRUE);
}

void CRefertoExDlg::OnNMDblclkListMeasurements(NMHDR *pNMHDR, LRESULT *pResult)
{
	//Julio - correcao lista biometria							
	POSITION pos = m_ctrlListMeasurements.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		//Habilita edicao das colunas

		CRect rect;
		int iCurSel = m_ctrlListMeasurements.GetNextSelectedItem(pos);

		long lIDMeasurement;
		if (theApp.m_bAtivaEspermograma)
			lIDMeasurement = atol(m_ctrlListMeasurements.GetItemText(iCurSel, 5));
		if (CanEdit(lIDMeasurement))
		{
			//Gabriel BUG 5533
			CString sAlias = m_ctrlListMeasurements.GetItemText(iCurSel, 0);

			/*if (sAlias == "VITALIDADE" && m_bSpermMeasurementVitalityAllowEdit == FALSE){
			return;
			}*/

			m_ctrlListMeasurements.SetSubItemEdit(iCurSel, 2, FALSE, 255);
			m_ctrlListMeasurements.GetSubItemRect(iCurSel, 2, LVIR_LABEL, rect);
			m_ctrlListMeasurements.PostMessage(WM_LBUTTONDOWN, 0, MAKELPARAM((rect.right + rect.left) / 2, (rect.bottom + rect.top) / 2));

			m_ctrlListMeasurements.SetSubItemEdit(iCurSel, 3, FALSE, 255);
			m_ctrlListMeasurements.GetSubItemRect(iCurSel, 3, LVIR_LABEL, rect);
			m_ctrlListMeasurements.PostMessage(WM_LBUTTONDOWN, 0, MAKELPARAM((rect.right + rect.left) / 2, (rect.bottom + rect.top) / 2));

			m_bMeasurementUpdated = TRUE;

			//Gabriel BUG 5533
			if (sAlias == "CONCENTRACAO TOTAL DA AMOSTRA" || sAlias == "ESP PROGRES PR" || sAlias == "MORF ESTRITA")
				m_bSpermChartMeasurementUpdated = TRUE;
		}


	}
	/*else //adicionando uma nova medida ao exame
	{
	long lID = m_pEsamiSet->m_lContatore; //id do exame
	CEditMeasurementDlg editDlg(this, lID, TRUE);
	editDlg.DoModal();
	}*/
	*pResult = 0;
}

void CRefertoExDlg::RiempiListaPdf()
{
	/*m_ctrlListPdf.SetExtendedStyle(m_ctrlListPdf.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListPdf.InsertColumn(0, "", LVCFMT_CENTER, 0);
	m_ctrlListPdf.InsertColumn(1, "NOME", LVCFMT_LEFT, 133);
	m_ctrlListPdf.InsertColumn(2, "DATA", LVCFMT_LEFT, 133);
	m_ctrlListPdf.InsertColumn(3, "", LVCFMT_CENTER, 0);*/

	m_ctrlListPdf.SetRedraw(FALSE);

	//--//	
	int iCountDoc1 = m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, TRUE);
	int iCountDoc2 = m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, FALSE);
	int iCountDoc = iCountDoc1 + iCountDoc2;

	if (m_sArrayPdf != NULL)
	{
		delete[] m_sArrayPdf;
		m_sArrayPdf = NULL;
	}

	if (iCountDoc > 0)
	{
		m_sArrayPdf = new CString[iCountDoc];
		int nItem = 0;

		CList<DOC> lstDoc1;
		m_pDocManager->GetAttachedDocListExam(m_pEsamiSet->m_lContatore, TRUE, &lstDoc1);
		for (int i = 0; i < lstDoc1.GetCount(); i++)
		{
			DOC doc = lstDoc1.GetAt(lstDoc1.FindIndex(i));
			if ((CString(doc.szDisco).CompareNoCase("R") == 0) && !CString(doc.szPercorsoFileRemoto).IsEmpty())
			{
				if (m_pEsamiView->m_pDocManager->CopyToLocal(doc.lID))
				{
					sprintf(doc.szDisco, "H");
					lstDoc1.SetAt(lstDoc1.FindIndex(i), doc);
				}
				else
				{
					sprintf(doc.szFile, doc.szPercorsoFileRemoto);
				}
			}
			switch (doc.dtTipo)
			{
			case doctype_pdf:
			{

				CString sNome = doc.szFileOriginalName;
				if (!CString(doc.szDescrizione).IsEmpty())
					sNome += " (" + CString(doc.szDescrizione) + ")";
				sNome.MakeUpper();

				CString sData;
				sData.Format("%s/%s/%s %s.%s.%s",
					CString(doc.szData).Mid(6, 2),
					CString(doc.szData).Mid(4, 2),
					CString(doc.szData).Mid(0, 4),
					CString(doc.szData).Mid(8, 2),
					CString(doc.szData).Mid(10, 2),
					CString(doc.szData).Mid(12, 2));

				m_sArrayPdf[nItem] = doc.szFile;
				m_ctrlListPdf.InsertItem(nItem, "");
				m_ctrlListPdf.SetItemData(nItem, nItem);
				m_ctrlListPdf.SetItemText(nItem, 1, sNome);
				m_ctrlListPdf.SetItemText(nItem, 2, sData);

				nItem++;
				break;
			}
			}
		}

		CList<DOC> lstDoc2;
		m_pDocManager->GetAttachedDocListExam(m_pEsamiSet->m_lContatore, FALSE, &lstDoc2);
		for (int i = 0; i < lstDoc2.GetCount(); i++)
		{
			DOC doc = lstDoc2.GetAt(lstDoc2.FindIndex(i));
			if ((CString(doc.szDisco).CompareNoCase("R") == 0) && !CString(doc.szPercorsoFileRemoto).IsEmpty())
			{
				if (m_pEsamiView->m_pDocManager->CopyToLocal(doc.lID))
				{
					sprintf(doc.szDisco, "H");
					lstDoc2.SetAt(lstDoc2.FindIndex(i), doc);
				}
				else
				{
					sprintf(doc.szFile, doc.szPercorsoFileRemoto);
				}
			}
			switch (doc.dtTipo)
			{
			case doctype_pdf:
			{
				CString sNome = doc.szFileOriginalName;
				if (!CString(doc.szDescrizione).IsEmpty())
					sNome += " (" + CString(doc.szDescrizione) + ")";
				sNome.MakeUpper();

				CString sData;
				sData.Format("%s/%s/%s %s.%s.%s",
					CString(doc.szData).Mid(6, 2),
					CString(doc.szData).Mid(4, 2),
					CString(doc.szData).Mid(0, 4),
					CString(doc.szData).Mid(8, 2),
					CString(doc.szData).Mid(10, 2),
					CString(doc.szData).Mid(12, 2));

				m_sArrayPdf[nItem] = doc.szFile;
				m_ctrlListPdf.InsertItem(nItem, "");
				m_ctrlListPdf.SetItemData(nItem, nItem);
				m_ctrlListPdf.SetItemText(nItem, 1, sNome);
				m_ctrlListPdf.SetItemText(nItem, 2, sData);

				nItem++;
				break;
			}
			}
		}
	}
	//--//

	m_ctrlListPdf.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListPdf.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListPdf.SetRedraw(TRUE);
}

void CRefertoExDlg::OnNMDblclkListPdf(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iCurSel;

	POSITION pos = m_ctrlListPdf.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		iCurSel = m_ctrlListPdf.GetNextSelectedItem(pos);

		CString sPdfPath = m_sArrayPdf[iCurSel];
		//apri il file								
		if (!sPdfPath.IsEmpty())
		{
			CString action = "open";
			ShellExecute(NULL, action, sPdfPath, NULL, NULL, SW_SHOW);
			getchar();
		}
		else
		{
			//sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_022);
		}
	}
	*pResult = 0;
}

short CRefertoExDlg::RicercaFigli(long lCodice)
{
	CString strFiltro;
	CFrasiExSet setTemp;
	setTemp.SetBaseFilter(m_sTipoEsame);

	strFiltro.Format("Padre=%li AND Famiglia=%li", lCodice, m_lFamiglia);
	setTemp.SetOpenFilter(strFiltro);
	setTemp.OpenRecordset("");

	if (setTemp.IsEOF() == TRUE)
	{
		setTemp.CloseRecordset("");
		return 0;
	}

	setTemp.CloseRecordset("");
	return 1;
}

void CRefertoExDlg::DistruggiListaFrasi()
{
	if (!m_ctrlTreeListFrasi)
		return;

	int counter = m_ctrlTreeListFrasi.GetCount();

	if (counter == LB_ERR)
		return;

	m_ctrlTreeListFrasi.SetCurSel(-1);

	for (int i = 0; i < counter; i++)
	{
		CBaseTreeObject* plineaInfo = m_ctrlTreeListFrasi.GetTreeItemDataPtr(i);

		if (plineaInfo)
			delete plineaInfo;
	}

	m_ctrlTreeListFrasi.ResetContent();
}

void CRefertoExDlg::PreparaListaFrasi()
{
	CString strTemp;
	CFrasiExSet	setTemp;

	strTemp.Format("TipoEsame=%li", m_pEsamiSet->m_lIDEsame);
	setTemp.SetBaseFilter(strTemp);

	strTemp.Format("Padre=0 AND Famiglia=%li", m_lFamiglia);
	setTemp.SetOpenFilter(strTemp);

	setTemp.SetSortRecord("Contatore");
	setTemp.OpenRecordset("Archivio Frasi Standard");

	while (setTemp.IsEOF() == FALSE)
	{
		CFrasiTreeObject* plineaInfo = new CFrasiTreeObject;
		//delete plineaInfo in DistruggiListaFrasi()

		if (!plineaInfo)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTOEXDLG_MEMORY));
			break;
		}

		plineaInfo->livello = 0;
		plineaInfo->codice = setTemp.m_lContatore;
		plineaInfo->padre = 0;
		plineaInfo->figli = RicercaFigli(plineaInfo->codice);
		plineaInfo->titolo = setTemp.m_sTitolo;
		plineaInfo->descrizione = setTemp.m_sDescrizione;
		plineaInfo->flag = 0;

		int posiz = m_ctrlTreeListFrasi.AddTreeItem(plineaInfo);

		if (posiz == LB_ERR)
		{
			delete plineaInfo;
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTOEXDLG_ERR_ADD_ITEM));
			break;
		}

		setTemp.MoveNext();
	}

	m_ctrlTreeListFrasi.SetCurSel(0);
}

void CRefertoExDlg::OnDblclkListaFrasi()
{
	BOOL			bError;
	CString			strFiltro;
	CFrasiExSet		TempFrasiSet;

	TempFrasiSet.SetBaseFilter(m_sTipoEsame);

	UpdateData(TRUE);

	int posiz = m_ctrlTreeListFrasi.GetCurSel();

	if (posiz == LB_ERR)
		return;

	CFrasiTreeObject* info = (CFrasiTreeObject*)m_ctrlTreeListFrasi.GetTreeItemDataPtr(posiz);

	if (info == NULL)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTOEXDLG_ERR_RETRIEVE));
		return;
	}

	if (info->figli)	// Ci sono sottoalberi ?
	{
		if (info->figli & 0x8000)		// É espanso ?
		{		// comprimi

			info->figli &= 0x7FFF;	// imposta MSB a 0 = sottoalbero compresso
			info->strToShow.SetAt(info->strToShow.Find('[') + 1, '+');

			int count = 0;

			CFrasiTreeObject* toBeDeleted = (CFrasiTreeObject*)m_ctrlTreeListFrasi.GetTreeItemDataPtr(posiz + 1);

			while (toBeDeleted &&
				count != posiz + 1 &&
				(toBeDeleted->livello > info->livello))
			{
				count = m_ctrlTreeListFrasi.DelTreeItem(posiz + 1);

				if (count == LB_ERR)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTOEXDLG_ERR_DELETE));
					return;
				}

				if (count != posiz + 1)
					toBeDeleted = (CFrasiTreeObject*)m_ctrlTreeListFrasi.GetTreeItemDataPtr(posiz + 1);
			}
		}
		else
		{		// espandi
			info->figli |= 0x8000;	// imposta MSB a 1 = sottoalbero espanso

			TempFrasiSet.SetSortRecord("Famiglia, Padre, Contatore");
			strFiltro.Format("Famiglia=%li AND Padre=%li", m_lFamiglia, info->codice);
			m_FrasiSet.RecordsetReOpen(bError, strFiltro, "", "CRefertoExDlg::OnDblclkListaFrasi");

			while (m_FrasiSet.IsEOF() == FALSE)
			{
				CFrasiTreeObject* plineaInfo = new CFrasiTreeObject;
				//delete plineaInfo in DistruggiListaFrasi()

				if (!plineaInfo)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTOEXDLG_MEMORY));
					break;
				}

				plineaInfo->livello = info->livello + 1;
				plineaInfo->codice = m_FrasiSet.m_lContatore;
				plineaInfo->padre = m_FrasiSet.m_lPadre;
				plineaInfo->figli = RicercaFigli(plineaInfo->codice);
				plineaInfo->titolo = m_FrasiSet.m_sTitolo;
				plineaInfo->descrizione = m_FrasiSet.m_sDescrizione;
				plineaInfo->flag = 0;

				posiz = m_ctrlTreeListFrasi.InsTreeItem(posiz + 1, plineaInfo);
				if (posiz == LB_ERR)
				{
					delete plineaInfo;
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTOEXDLG_ERR_INSERT));
					break;
				}

				m_FrasiSet.MoveNext();
			}

			TempFrasiSet.CloseRecordset("Archivio Frasi Standard Temp");
		}
	}
}

void CRefertoExDlg::OnSelchangeListaFrasi()
{
	UpdateData(TRUE);

	m_strFrase = m_ctrlTreeListFrasi.GetCurDataPathSel();
	GetDlgItem(IDC_FRASE)->SetFocus();

	UpdateData(FALSE);
}

void CRefertoExDlg::OnSelchangeFamiglia(NMHDR* pNMHDR, LRESULT* pResult)
{
	int nCurSel = m_ctrlFamiglia.GetCurSel();
	if (nCurSel >= 0)
	{
		TCITEM tcTemp;
		tcTemp.mask = TCIF_PARAM;
		m_ctrlFamiglia.GetItem(nCurSel, &tcTemp);

		m_lFamiglia = tcTemp.lParam;

		if (m_lFamiglia == id_measurements)
			RiempiListaMeasurements();
		else
			SaveEditedMeasurement(); //Julio - correcao lista biometria

		switch (m_lFamiglia)
		{
		case id_frasi:
		case id_risposte:
		case id_anomalie:
		{
			m_ctrlTreeListFrasi.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_SHOW);
			m_ctrlListImage.ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			DistruggiListaFrasi();
			m_ctrlTreeListFrasi.SetFamily(m_lFamiglia);
			PreparaListaFrasi();

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}
		case id_immaginifilmati:
		{
			m_ctrlListImage.ShowWindow(SW_SHOW);
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}
		case id_altrireferti:
		{
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);
			m_ctrlListImage.ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_SHOW);
			m_ctrlBtnPrev.ShowWindow(SW_SHOW);
			m_ctrlBtnNext.ShowWindow(SW_SHOW);
			m_ctrlStatic00.ShowWindow(SW_SHOW);
			m_ctrlStatic01.ShowWindow(SW_SHOW);
			m_ctrlStatic02.ShowWindow(SW_SHOW);
			m_ctrlBtnCopy.ShowWindow(SW_SHOW);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_SHOW);
			if (theApp.m_bPersonalizzazioniBrasileFleury)
			{
				m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_SHOW);
				m_ctrlBtnConsultaResultado.ShowWindow(SW_SHOW);
				m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_SHOW);
			}
			else
			{
				m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
				m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
				m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			}

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}
		case id_frasirtf:
		{
			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			m_ctrlListImage.ShowWindow(SW_HIDE);
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_SHOW);
			m_ctrlEditRtfFrase.ShowWindow(SW_SHOW);
			m_ctrlListFrasiRTF.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_FRASE)->SetFocus();

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}
		case id_tabella:
		{
			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_SHOW);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_SHOW);

			m_ctrlListImage.ShowWindow(SW_HIDE);
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}
		case id_checklist:
		{
			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_SHOW);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			m_ctrlListImage.ShowWindow(SW_HIDE);
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}
		case id_anteprimastampa:
		{
			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			m_ctrlListImage.ShowWindow(SW_HIDE);
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_SHOW);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}
		case id_pdf:
		{
			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			m_ctrlListImage.ShowWindow(SW_HIDE);
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_SHOW);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}
		case id_measurements:
		{
			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			m_ctrlListImage.ShowWindow(SW_HIDE);
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_SHOW);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_SHOW); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}
		case id_references:
		{
			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			m_ctrlListImage.ShowWindow(SW_HIDE);
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_SHOW);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}

		case id_anamnesi:
		{
			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			m_ctrlListImage.ShowWindow(SW_HIDE);
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			m_ctrlListPdf.ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references //
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_SHOW);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}

		default:
		{
			ASSERT(FALSE);

			//

			GetDlgItem(IDC_STATIC_CHECKLIST)->ShowWindow(SW_HIDE);
			if (m_pChecklistForm)
				m_pChecklistForm->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_TABELLA)->ShowWindow(SW_HIDE);
			if (m_pTabellaForm)
				m_pTabellaForm->ShowWindow(SW_HIDE);

			m_ctrlListImage.ShowWindow(SW_HIDE);
			m_ctrlTreeListFrasi.ShowWindow(SW_HIDE);
			GetDlgItem(IDC_FRASE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_INSERT_FRASI)->ShowWindow(SW_HIDE);

			// id_altrireferti //

			m_ctrlTextAltriReferti.ShowWindow(SW_HIDE);
			m_ctrlBtnPrev.ShowWindow(SW_HIDE);
			m_ctrlBtnNext.ShowWindow(SW_HIDE);
			m_ctrlStatic00.ShowWindow(SW_HIDE);
			m_ctrlStatic01.ShowWindow(SW_HIDE);
			m_ctrlStatic02.ShowWindow(SW_HIDE);
			m_ctrlBtnCopy.ShowWindow(SW_HIDE);
			m_ctrlBtnGetLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlBtnConsultaResultado.ShowWindow(SW_HIDE);
			m_ctrlEditInfoLaudoAnterior.ShowWindow(SW_HIDE);
			m_ctrlCheckLaudoAnteriorLocalMesmaEspecialidade.ShowWindow(SW_HIDE);

			// id_frasirtf //

			m_ctrlEditRtfCodice.ShowWindow(SW_HIDE);
			m_ctrlEditRtfFrase.ShowWindow(SW_HIDE);
			m_ctrlListFrasiRTF.ShowWindow(SW_HIDE);

			// id_anteprimastampa //

			GetDlgItem(IDC_PDF_PLACE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_PREV2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_NEXT2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMOUT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_ZOOMIN)->ShowWindow(SW_HIDE);

			// id_pdf //
			GetDlgItem(IDC_LIST_PDF)->ShowWindow(SW_HIDE);

			// id_measurements //
			m_ctrlListMeasurements.ShowWindow(SW_HIDE);
			m_ctrlBtnSaveMeasurements.ShowWindow(SW_HIDE); //Julio - correcao lista biometria

			// id_references // Luiz - 17/07/2019 - P3 - Desbloqueia scroll na aba valores de referencia 
			m_ctrlTextReferences.ShowWindow(SW_HIDE);

			// id_anamnesi //
			m_ctrlTextTabAnamnesi.ShowWindow(SW_HIDE);	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
			//

			break;
		}
		}
	}

	// Marvel BUG 4092 - concorrência na edição de laudos
	if (!m_pEsamiView->m_sMsgGotRefertoRefreshWithUpdate.IsEmpty())
	{
		if (theApp.m_bShowAlertaEdicaoConcorrente)
		{
			theApp.AfxMessageBoxEndo(m_pEsamiView->m_sMsgGotRefertoRefreshWithUpdate);
		}
		m_pEsamiView->m_sMsgGotRefertoRefreshWithUpdate = "";
	}
}

void CRefertoExDlg::OnInsertFrasi()
{
	m_ctrlText.SetSelText(m_strFrase);
	//GetDlgItem(IDC_FRASE)->SetFocus();
}

void CRefertoExDlg::OnOK()
{
}

void CRefertoExDlg::OnCancel()
{
}

void CRefertoExDlg::SetReferto(CString strText)
{
	m_ctrlText.ResetContents();

	if (!strText.IsEmpty())
	{
		try
		{
			m_ctrlText.SetRTFSelText(strText);
		}
		catch (CException* e)
		{
			e->Delete();
			m_ctrlText.SetSelText(strText);
		}
	}
}

void CRefertoExDlg::OnBtnSpeak()
{
	HKEY hKey;
	unsigned char szProductType[80];
	DWORD dwBufLen;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\GST\\PhonemA", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, "PathExe", NULL, NULL, szProductType, &dwBufLen);
		RegQueryValueEx(hKey, "PathExe", NULL, NULL, szProductType, &dwBufLen);
		RegCloseKey(hKey);
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTOEXDLG_ERR_VOCAL_REPORT));
		return;
	}

	CString strFold = szProductType;
	CString strPass = strFold + "Report\\Pass.txt";
	CString strUser = strFold + "Phuser.ini";
	CString strTool = strFold + "Toolkit.exe";
	CString strEndP = strFold + "EndPh";
	CString strRepo = strFold + "Report\\Report.txt";

	DeleteFile(strEndP);

	WritePrivateProfileInt("dati utente", "Stato", 9, strUser);

	if (WinExec(strTool, SW_SHOWNORMAL) > 31)
	{
		while (_taccess((LPCTSTR)strEndP, 00) != 0)
		{
			MSG mMsg;

			while (PeekMessage(&mMsg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&mMsg);
				DispatchMessage(&mMsg);
			}
		}

		int iTmp = GetPrivateProfileInt("dati utente", "Stato", 1, strUser);

		if (iTmp == 2)
		{
			char szRisultato[16 * 1024];
			CString strRisultato;
			CFile fileRepo;

			fileRepo.Open(strRepo, CFile::modeRead);
			int i = fileRepo.Read(szRisultato, 16 * 1024);
			fileRepo.Close();

			szRisultato[i] = '\0';
			strRisultato = CString(szRisultato);

			m_ctrlText.SetSelText(strRisultato);

			UpdateData(FALSE);
		}
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTOEXDLG_ERR_VOCAL_REPORT));
	}
}

void CRefertoExDlg::OnBtnSforzo()
{
	m_ctrlText.SetFormatSelection(TRUE);

	if (m_ctrlText.GetTableAtInputPos() == 0)
	{
		if (m_ctrlText.GetTableCanInsert())
		{
			srand((unsigned)time(NULL));
			rand();	rand();	rand(); rand();

			short shAlig = m_ctrlText.GetAlignment();

			if (m_pEsamiView->m_pDynForm[sub_cardio_prima] != NULL)
			{
				CCardioPrimaDynForm* pForm = (CCardioPrimaDynForm*)m_pEsamiView->m_pDynForm[sub_cardio_prima];

				//Julio 13/08/2018
				//CCardioDuranteDynForm* pFormDurante = (CCardioDuranteDynForm*)m_pEsamiView->m_pDynForm[sub_cardio_durante];
				//if (pFormDurante->GetNomeProtocollo() != "CINTADENO" && pFormDurante->GetNomeProtocollo() != "DIPI")
				//{
				m_ctrlText.SetSelText("\r\n");
				m_ctrlText.SetAlignment(0);

				VARIANT varTemp1;
				varTemp1.vt = VT_I2;
				varTemp1.iVal = (rand() % (32767 - 10)) + 10;

				short shTableIdInserted = m_ctrlText.TableInsert(2, 2, -1, varTemp1);
				if (shTableIdInserted > 0)
				{
					VARIANT varTemp2;
					varTemp2.vt = VT_I2;

					varTemp2.iVal = 0;
					m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellBorderWidth, varTemp2);

					varTemp2.iVal = 2000;
					m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellHorizontalExt, varTemp2);

					//

					m_ctrlText.put_TableCellText(shTableIdInserted, 1, 1, pForm->GetMassimaTitle());
					m_ctrlText.put_TableCellText(shTableIdInserted, 1, 2, pForm->GetMassimaBpm());

					m_ctrlText.put_TableCellText(shTableIdInserted, 2, 1, pForm->GetSubmassimaTitle());
					m_ctrlText.put_TableCellText(shTableIdInserted, 2, 2, pForm->GetSubmassimaBpm());
				}
				//
				//}

				m_ctrlText.SetAlignment(shAlig);
				m_ctrlText.SetSelText("\r\n");

				//

				if ((pForm->GetColNumber() > 0) && (pForm->GetRowNumber() > 0))
				{
					m_ctrlText.SetAlignment(2);

					m_ctrlText.SetFontBold(1);
					m_ctrlText.SetSelText(pForm->GetTitle());
					m_ctrlText.SetFontBold(0);

					m_ctrlText.SetSelText("\r\n");

					VARIANT varTemp1;
					varTemp1.vt = VT_I2;
					varTemp1.iVal = (rand() % (32767 - 10)) + 10;

					//Julio 13/08/2018
					//short shRowNumber = pForm->GetRowNumber();
					//if (pFormDurante->GetNomeProtocollo() == "CINTADENO" && pFormDurante->GetNomeProtocollo() == "DIPI" &&
					//pFormDurante->GetNomeProtocollo() == "DOBUTAMINA")
					//shRowNumber = shRowNumber - 2;

					//short shTableIdInserted = m_ctrlText.TableInsert(shRowNumber, pForm->GetColNumber(), -1, varTemp1);
					short shTableIdInserted = m_ctrlText.TableInsert(pForm->GetRowNumber(), pForm->GetColNumber(), -1, varTemp1);

					if (shTableIdInserted > 0)
					{
						VARIANT varTemp2;
						varTemp2.vt = VT_I2;

						varTemp2.iVal = 5;
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellBorderWidth, varTemp2);

						varTemp2.iVal = 10000 / pForm->GetColNumber();
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellHorizontalExt, varTemp2);

						varTemp2.iVal = 10000 - ((pForm->GetColNumber() - 1) * varTemp2.iVal);
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, pForm->GetColNumber() /* ultima colonna */, m_ctrlText.txTableCellHorizontalExt, varTemp2);

						varTemp2.iVal = 1;
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellVertAlign, varTemp2);

						//

						//Julio 13/08/2018					
						//short shYSentado = -1;											
						//short shYOrtostatico = -1;

						for (short shX = 0; shX < pForm->GetColNumber(); shX++)
							//{
							for (short shY = 0; shY < pForm->GetRowNumber(); shY++)
								//{
								//CString text = pForm->GetTableCellText(shX, shY);
								//if (text == "Sentado")								
								//shYSentado = shY;								
								//if (text == "Ortostático")
								//shYOrtostatico = shY;

								//if (pFormDurante->GetNomeProtocollo() != "CINTADENO" && pFormDurante->GetNomeProtocollo() != "DIPI" &&
								//pFormDurante->GetNomeProtocollo() != "DOBUTAMINA")
								m_ctrlText.put_TableCellText(shTableIdInserted, shY + 1, shX + 1, pForm->GetTableCellText(shX, shY));
						//else
						//{
						//if (shY != shYSentado && shY != shYOrtostatico)
						//m_ctrlText.put_TableCellText(shTableIdInserted, shY + 1, shX + 1, pForm->GetTableCellText(shX, shY));
						//}
						//}
						//}
					}

					m_ctrlText.SetAlignment(shAlig);
					m_ctrlText.SetSelText("\r\n");
				}
			}

			if (m_pEsamiView->m_pDynForm[sub_cardio_durante] != NULL)
			{
				CCardioDuranteDynForm* pForm = (CCardioDuranteDynForm*)m_pEsamiView->m_pDynForm[sub_cardio_durante];

				if ((pForm->GetColNumber() > 0) && (pForm->GetRowNumber() > 0))
				{
					m_ctrlText.SetAlignment(2);

					m_ctrlText.SetFontBold(1);
					m_ctrlText.SetSelText(pForm->GetTitle());
					m_ctrlText.SetFontBold(0);

					m_ctrlText.SetSelText("\r\n");

					VARIANT varTemp1;
					varTemp1.vt = VT_I2;
					varTemp1.iVal = (rand() % (32767 - 10)) + 10;

					short shTableIdInserted = m_ctrlText.TableInsert(pForm->GetRowNumber(), pForm->GetColNumber(), -1, varTemp1);
					if (shTableIdInserted > 0)
					{
						VARIANT varTemp2;
						varTemp2.vt = VT_I2;

						varTemp2.iVal = 5;
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellBorderWidth, varTemp2);

						varTemp2.iVal = 10000 / pForm->GetColNumber();
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellHorizontalExt, varTemp2);

						varTemp2.iVal = 10000 - ((pForm->GetColNumber() - 1) * varTemp2.iVal);
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, pForm->GetColNumber() /* ultima colonna */, m_ctrlText.txTableCellHorizontalExt, varTemp2);

						varTemp2.iVal = 1;
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellVertAlign, varTemp2);

						//
						//short shYRepouso = -1;
						for (short shX = 0; shX < pForm->GetColNumber(); shX++)
							//{
							for (short shY = 0; shY < pForm->GetRowNumber(); shY++)
								//{
								//CString text = pForm->GetTableCellText(shX, shY);
								//if (text == "Repouso")
								//shYRepouso = shY;

								//if (pForm->GetNomeProtocollo() != "CINTADENO")
								m_ctrlText.put_TableCellText(shTableIdInserted, shY + 1, shX + 1, pForm->GetTableCellText(shX, shY));
						//else
						//{
						//if (shY != shYRepouso)
						//m_ctrlText.put_TableCellText(shTableIdInserted, shY + 1, shX + 1, pForm->GetTableCellText(shX, shY));
						//}								
						//}
						//}
					}

					m_ctrlText.SetAlignment(shAlig);
					m_ctrlText.SetSelText("\r\n");
				}
			}

			if (m_pEsamiView->m_pDynForm[sub_cardio_dopo] != NULL)
			{
				CCardioDopoDynForm* pForm = (CCardioDopoDynForm*)m_pEsamiView->m_pDynForm[sub_cardio_dopo];

				if ((pForm->GetColNumber() > 0) && (pForm->GetRowNumber() > 0))
				{
					m_ctrlText.SetAlignment(2);

					m_ctrlText.SetFontBold(1);
					m_ctrlText.SetSelText(pForm->GetTitle());
					m_ctrlText.SetFontBold(0);

					m_ctrlText.SetSelText("\r\n");

					VARIANT varTemp1;
					varTemp1.vt = VT_I2;
					varTemp1.iVal = (rand() % (32767 - 10)) + 10;

					short shTableIdInserted = m_ctrlText.TableInsert(pForm->GetRowNumber(), pForm->GetColNumber(), -1, varTemp1);
					if (shTableIdInserted > 0)
					{
						VARIANT varTemp2;
						varTemp2.vt = VT_I2;

						varTemp2.iVal = 5;
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellBorderWidth, varTemp2);

						varTemp2.iVal = 10000 / pForm->GetColNumber();
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellHorizontalExt, varTemp2);

						varTemp2.iVal = 10000 - ((pForm->GetColNumber() - 1) * varTemp2.iVal);
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, pForm->GetColNumber() /* ultima colonna */, m_ctrlText.txTableCellHorizontalExt, varTemp2);

						varTemp2.iVal = 1;
						m_ctrlText.put_TableCellAttribute(shTableIdInserted, 0 /* tutte le righe */, 0 /* tutte le colonne */, m_ctrlText.txTableCellVertAlign, varTemp2);

						//

						for (short shX = 0; shX < pForm->GetColNumber(); shX++)
							for (short shY = 0; shY < pForm->GetRowNumber(); shY++)
								m_ctrlText.put_TableCellText(shTableIdInserted, shY + 1, shX + 1, pForm->GetTableCellText(shX, shY));
					}

					m_ctrlText.SetAlignment(shAlig);
					m_ctrlText.SetSelText("\r\n");
				}
			}

			m_ctrlText.SetSelText("\r\n");

			if (m_pEsamiView->m_pDynForm[sub_mielogramma] != NULL)
			{
#ifdef _DEBUG
				m_ctrlText.ResetContents();
				m_ctrlText.SetText("\r\n");
				m_ctrlText.SetSelStart(-1);
				m_ctrlText.SetSelLength(0);
#endif

				CMielogrammaDynForm* pForm = (CMielogrammaDynForm*)m_pEsamiView->m_pDynForm[sub_mielogramma];

				m_ctrlText.SetFontName("Courier New");
				m_ctrlText.SetFontSize(10);

				m_ctrlText.SetSelText("   CÉLULAS INTERSTICIAIS          CÉLULAS INDIFERENCIADAS   \r\n");
				m_ctrlText.SetSelText("---------------------------    -----------------------------\r\n");
				m_ctrlText.SetSelText("HISTIOCITOS    :  " + pForm->GetTableCellNumberPercent(5, 4) + "      BLASTOS           : " + pForm->GetTableCellNumberPercent(5, 8) + "\r\n");
				m_ctrlText.SetSelText("MACROFAGOS     :  " + pForm->GetTableCellNumberPercent(6, 4) + "      OUTROS            : " + pForm->GetTableCellNumberPercent(6, 8) + "\r\n");
				m_ctrlText.SetSelText("MASTOCITOS     :  " + pForm->GetTableCellNumberPercent(7, 4) + "\r\n");
				m_ctrlText.SetSelText("\r\n");
				m_ctrlText.SetSelText("                    SÉRIE  GRANULOCITICA                    \r\n");
				m_ctrlText.SetSelText("------------------------------------------------------------\r\n");
				m_ctrlText.SetSelText("\r\n");
				m_ctrlText.SetSelText("                   NEUTRÓFILOS    EOSINÓFILOS     BASÓFILOS \r\n");
				m_ctrlText.SetSelText("                   -----------    -----------    -----------\r\n");
				m_ctrlText.SetSelText("PROMIELOCITOS  :     " + pForm->GetTableCellNumberPercent(11, 4) + "        " + pForm->GetTableCellNumberPercent(11, 8) + "\r\n");
				m_ctrlText.SetSelText("MIELOCITOS     :     " + pForm->GetTableCellNumberPercent(12, 4) + "        " + pForm->GetTableCellNumberPercent(12, 8) + "\r\n");
				m_ctrlText.SetSelText("METAMIELOCITOS :     " + pForm->GetTableCellNumberPercent(13, 4) + "        " + pForm->GetTableCellNumberPercent(13, 8) + "\r\n");
				m_ctrlText.SetSelText("BASTONETES     :     " + pForm->GetTableCellNumberPercent(14, 4) + "        " + pForm->GetTableCellNumberPercent(14, 8) + "\r\n");
				m_ctrlText.SetSelText("SEGMENTADOS    :     " + pForm->GetTableCellNumberPercent(15, 4) + "        " + pForm->GetTableCellNumberPercent(15, 8) + "        " + pForm->GetTableCellNumberPercent(11, 12) + "\r\n");
				m_ctrlText.SetSelText("                   -----------    -----------    -----------\r\n");
				m_ctrlText.SetSelText("                     " + pForm->GetTableCellNumberPercent(16, 4) + "        " + pForm->GetTableCellNumberPercent(16, 8) + "        " + pForm->GetTableCellNumberPercent(11, 12) + "\r\n");
				m_ctrlText.SetSelText("\r\n");
				m_ctrlText.SetSelText("SÉRIE LINFO-MONO-PLASMOCITARIA                SÉRIE ERITROCÍTICA            \r\n");
				m_ctrlText.SetSelText("------------------------------    ------------------------------------------\r\n");
				m_ctrlText.SetSelText("LINFOCITOS     :     " + pForm->GetTableCellNumberPercent(20, 8) + "      PROERITROBLASTOS               : " + pForm->GetTableCellNumberPercent(20, 4) + "\r\n");
				m_ctrlText.SetSelText("MONOCITOS      :     " + pForm->GetTableCellNumberPercent(21, 8) + "      ERITROBLASTOS BASOFILOS        : " + pForm->GetTableCellNumberPercent(21, 4) + "\r\n");
				m_ctrlText.SetSelText("PLASMOCITOS    :     " + pForm->GetTableCellNumberPercent(22, 8) + "      ERITROBLASTOS POLICROMATOFILOS : " + pForm->GetTableCellNumberPercent(22, 4) + "\r\n");
				m_ctrlText.SetSelText("                                  ERITROBLASTOS ORTOCROMATICOS   : " + pForm->GetTableCellNumberPercent(23, 4) + "\r\n");
				m_ctrlText.SetSelText("\r\n");
				m_ctrlText.SetSelText("   SÉRIE MEGACARIOCÍTICA   \r\n");
				m_ctrlText.SetSelText("---------------------------\r\n");
				m_ctrlText.SetSelText("MEGACARIOCITOS : " + pForm->GetTableCellText(19, 11) + "\r\n");

				/*
				m_ctrlText.SetFontName("Consolas");

				VARIANT varTemp1;

				// TABELLA 1 //

				varTemp1.vt = VT_I2;
				varTemp1.iVal = (rand() % (32767 - 10)) + 10;

				short shTableIdInserted1 = m_ctrlText.TableInsert(4, 5, -1, varTemp1);
				if (shTableIdInserted1 > 0)
				{
				VARIANT varTemp2;
				varTemp2.vt = VT_I2;

				varTemp2.iVal = 1;
				m_ctrlText.put_TableCellAttribute(
				shTableIdInserted1,
				0, / * tutte le righe * /
				0, / * tutte le colonne * /
				m_ctrlText.txTableCellVertAlign,
				varTemp2
				);

				varTemp2.iVal = 75;
				m_ctrlText.put_TableCellAttribute(
				shTableIdInserted1,
				0, / * tutte le righe * /
				0, / * tutte le colonne * /
				m_ctrlText.txTableCellTextGap,
				varTemp2
				);

				//

				m_ctrlText.TableSelectCells(shTableIdInserted1, 1, 1, 1, 2);
				m_ctrlText.TableMergeCells();

				m_ctrlText.TableSelectCells(shTableIdInserted1, 1, 4, 1, 5);
				m_ctrlText.TableMergeCells();

				m_ctrlText.put_TableCellText(shTableIdInserted1, 1, 1, "CÉLULAS INTERSTICIAIS");
				m_ctrlText.put_TableCellText(shTableIdInserted1, 2, 1, "HISTIOCITOS");
				m_ctrlText.put_TableCellText(shTableIdInserted1, 2, 2, pForm->GetTableCellText(5, 4));
				m_ctrlText.put_TableCellText(shTableIdInserted1, 3, 1, "MACROFAGOS");
				m_ctrlText.put_TableCellText(shTableIdInserted1, 3, 2, pForm->GetTableCellText(6, 4));
				m_ctrlText.put_TableCellText(shTableIdInserted1, 4, 1, "MASTOCITOS");
				m_ctrlText.put_TableCellText(shTableIdInserted1, 4, 2, pForm->GetTableCellText(7, 4));

				m_ctrlText.put_TableCellText(shTableIdInserted1, 1, 4, "CÉLULAS INDIFERENCIADAS");
				m_ctrlText.put_TableCellText(shTableIdInserted1, 2, 4, "BLASTOS");
				m_ctrlText.put_TableCellText(shTableIdInserted1, 2, 5, pForm->GetTableCellText(5, 8));
				m_ctrlText.put_TableCellText(shTableIdInserted1, 3, 4, "OUTROS");
				m_ctrlText.put_TableCellText(shTableIdInserted1, 3, 5, pForm->GetTableCellText(6, 8));
				}

				m_ctrlText.SetSelStart(-1);
				m_ctrlText.SetSelLength(0);
				m_ctrlText.SetSelText("\r\n");

				// TABELLA 2 //

				varTemp1.vt = VT_I2;
				varTemp1.iVal = (rand() % (32767 - 10)) + 10;

				short shTableIdInserted2 = m_ctrlText.TableInsert(8, 4, -1, varTemp1);
				if (shTableIdInserted2 > 0)
				{
				VARIANT varTemp2;
				varTemp2.vt = VT_I2;

				varTemp2.iVal = 1;
				m_ctrlText.put_TableCellAttribute(
				shTableIdInserted2,
				0, / * tutte le righe * /
				0, / * tutte le colonne * /
				m_ctrlText.txTableCellVertAlign,
				varTemp2
				);

				varTemp2.iVal = 75;
				m_ctrlText.put_TableCellAttribute(
				shTableIdInserted2,
				0, / * tutte le righe * /
				0, / * tutte le colonne * /
				m_ctrlText.txTableCellTextGap,
				varTemp2
				);

				//

				m_ctrlText.TableSelectCells(shTableIdInserted2, 1, 1, 1, 4);
				m_ctrlText.TableMergeCells();

				m_ctrlText.put_TableCellText(shTableIdInserted2, 1, 1, "SÉRIE GRANULOCITICA");

				m_ctrlText.put_TableCellText(shTableIdInserted2, 3, 1, "PROMIELOCITOS");
				m_ctrlText.put_TableCellText(shTableIdInserted2, 4, 1, "MIELOCITOS");
				m_ctrlText.put_TableCellText(shTableIdInserted2, 5, 1, "METAMIELOCITOS");
				m_ctrlText.put_TableCellText(shTableIdInserted2, 6, 1, "BASTONETES");
				m_ctrlText.put_TableCellText(shTableIdInserted2, 7, 1, "SEGMENTADOS");

				m_ctrlText.put_TableCellText(shTableIdInserted2, 2, 2, "NEUTRÓFILOS");
				m_ctrlText.put_TableCellText(shTableIdInserted2, 3, 2, pForm->GetTableCellText(11, 4));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 4, 2, pForm->GetTableCellText(12, 4));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 5, 2, pForm->GetTableCellText(13, 4));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 6, 2, pForm->GetTableCellText(14, 4));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 7, 2, pForm->GetTableCellText(15, 4));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 8, 2, pForm->GetTableCellText(16, 4));

				m_ctrlText.put_TableCellText(shTableIdInserted2, 2, 3, "EOSINÓFILOS");
				m_ctrlText.put_TableCellText(shTableIdInserted2, 3, 3, pForm->GetTableCellText(11, 8));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 4, 3, pForm->GetTableCellText(12, 8));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 5, 3, pForm->GetTableCellText(13, 8));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 6, 3, pForm->GetTableCellText(14, 8));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 7, 3, pForm->GetTableCellText(15, 8));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 8, 3, pForm->GetTableCellText(16, 8));

				m_ctrlText.put_TableCellText(shTableIdInserted2, 2, 4, "BASÓFILOS");
				m_ctrlText.put_TableCellText(shTableIdInserted2, 7, 4, pForm->GetTableCellText(11, 12));
				m_ctrlText.put_TableCellText(shTableIdInserted2, 8, 4, pForm->GetTableCellText(11, 12));
				}

				m_ctrlText.SetSelStart(-1);
				m_ctrlText.SetSelLength(0);
				m_ctrlText.SetSelText("\r\n");

				// TABELLA 3 //

				varTemp1.vt = VT_I2;
				varTemp1.iVal = (rand() % (32767 - 10)) + 10;

				short shTableIdInserted3 = m_ctrlText.TableInsert(5, 5, -1, varTemp1);
				if (shTableIdInserted3 > 0)
				{
				VARIANT varTemp2;
				varTemp2.vt = VT_I2;

				varTemp2.iVal = 1;
				m_ctrlText.put_TableCellAttribute(
				shTableIdInserted3,
				0, / * tutte le righe * /
				0, / * tutte le colonne * /
				m_ctrlText.txTableCellVertAlign,
				varTemp2
				);

				varTemp2.iVal = 75;
				m_ctrlText.put_TableCellAttribute(
				shTableIdInserted3,
				0, / * tutte le righe * /
				0, / * tutte le colonne * /
				m_ctrlText.txTableCellTextGap,
				varTemp2
				);

				//

				m_ctrlText.TableSelectCells(shTableIdInserted3, 1, 1, 1, 2);
				m_ctrlText.TableMergeCells();

				m_ctrlText.TableSelectCells(shTableIdInserted3, 1, 4, 1, 5);
				m_ctrlText.TableMergeCells();

				m_ctrlText.put_TableCellText(shTableIdInserted3, 1, 1, "SÉRIE LINFO-MONO-PLASMOCITARIA");
				m_ctrlText.put_TableCellText(shTableIdInserted3, 2, 1, "LINFOCITOS");
				m_ctrlText.put_TableCellText(shTableIdInserted3, 2, 2, pForm->GetTableCellText(20, 8));
				m_ctrlText.put_TableCellText(shTableIdInserted3, 3, 1, "MONOCITOS");
				m_ctrlText.put_TableCellText(shTableIdInserted3, 3, 2, pForm->GetTableCellText(21, 8));
				m_ctrlText.put_TableCellText(shTableIdInserted3, 4, 1, "PLASMOCITOS");
				m_ctrlText.put_TableCellText(shTableIdInserted3, 4, 2, pForm->GetTableCellText(22, 8));

				m_ctrlText.put_TableCellText(shTableIdInserted3, 1, 4, "SÉRIE ERITROCÍTICA");
				m_ctrlText.put_TableCellText(shTableIdInserted3, 2, 4, "PROERITROBLASTOS");
				m_ctrlText.put_TableCellText(shTableIdInserted3, 2, 5, pForm->GetTableCellText(20, 4));
				m_ctrlText.put_TableCellText(shTableIdInserted3, 3, 4, "ERITROBLASTOS BASOFILOS");
				m_ctrlText.put_TableCellText(shTableIdInserted3, 3, 5, pForm->GetTableCellText(21, 4));
				m_ctrlText.put_TableCellText(shTableIdInserted3, 4, 4, "ERITROBLASTOS POLICROMATOFILOS");
				m_ctrlText.put_TableCellText(shTableIdInserted3, 4, 5, pForm->GetTableCellText(22, 4));
				m_ctrlText.put_TableCellText(shTableIdInserted3, 5, 4, "ERITROBLASTOS ORTOCROMATICOS");
				m_ctrlText.put_TableCellText(shTableIdInserted3, 5, 5, pForm->GetTableCellText(23, 4));
				}

				m_ctrlText.SetSelStart(-1);
				m_ctrlText.SetSelLength(0);
				m_ctrlText.SetSelText("\r\n");

				// TABELLA 4 //

				varTemp1.vt = VT_I2;
				varTemp1.iVal = (rand() % (32767 - 10)) + 10;

				short shTableIdInserted4 = m_ctrlText.TableInsert(2, 2, -1, varTemp1);
				if (shTableIdInserted4 > 0)
				{
				VARIANT varTemp2;
				varTemp2.vt = VT_I2;

				varTemp2.iVal = 1;
				m_ctrlText.put_TableCellAttribute(
				shTableIdInserted4,
				0, / * tutte le righe * /
				0, / * tutte le colonne * /
				m_ctrlText.txTableCellVertAlign,
				varTemp2
				);

				varTemp2.iVal = 75;
				m_ctrlText.put_TableCellAttribute(
				shTableIdInserted4,
				0, / * tutte le righe * /
				0, / * tutte le colonne * /
				m_ctrlText.txTableCellTextGap,
				varTemp2
				);

				//

				m_ctrlText.TableSelectCells(shTableIdInserted4, 1, 1, 1, 2);
				m_ctrlText.TableMergeCells();

				m_ctrlText.put_TableCellText(shTableIdInserted4, 1, 1, "SÉRIE MEGACARIOCÍTICA");
				m_ctrlText.put_TableCellText(shTableIdInserted4, 2, 1, "MEGACARIOCITOS");
				m_ctrlText.put_TableCellText(shTableIdInserted4, 2, 2, pForm->GetTableCellText(19, 11));
				}

				m_ctrlText.SetSelStart(-1);
				m_ctrlText.SetSelLength(0);
				m_ctrlText.SetSelText("\r\n");

				// Sandro 24/01/2017 //

				m_ctrlText.SetFormatSelection(TRUE);

				VARIANT varTemp2;
				varTemp2.vt = VT_I2;

				////////////////////////
				// formatto tabella 1 //
				////////////////////////

				varTemp2.iVal = 3150;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 0 / * tutte le righe * /, 1, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 850;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 0 / * tutte le righe * /, 2, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 500;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 0 / * tutte le righe * /, 3, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 3150;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 0 / * tutte le righe * /, 4, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 850;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 0 / * tutte le righe * /, 5, m_ctrlText.txTableCellHorizontalExt, varTemp2);

				varTemp2.iVal = 5;

				// tabella 1 sx //

				// m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 1, 1, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 2, 1, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 2, 2, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 3, 1, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 3, 2, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 4, 1, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 4, 2, m_ctrlText.txTableCellBorderWidth, varTemp2);

				m_ctrlText.TableCellSelect(shTableIdInserted1, 1, 1);
				m_ctrlText.SetAlignment(0); // 2 //
				m_ctrlText.SetFontBold(1);

				m_ctrlText.TableCellSelect(shTableIdInserted1, 2, 2);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted1, 3, 2);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted1, 4, 2);
				m_ctrlText.SetAlignment(1);

				// tabella 1 dx //

				// m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 1, 4, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 2, 4, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 2, 5, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 3, 4, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted1, 3, 5, m_ctrlText.txTableCellBorderWidth, varTemp2);

				m_ctrlText.TableCellSelect(shTableIdInserted1, 1, 4);
				m_ctrlText.SetAlignment(0); // 2 //
				m_ctrlText.SetFontBold(1);

				m_ctrlText.TableCellSelect(shTableIdInserted1, 2, 5);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted1, 3, 5);
				m_ctrlText.SetAlignment(1);

				////////////////////////
				// formatto tabella 2 //
				////////////////////////

				varTemp2.iVal = 2500;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted2, 0 / * tutte le righe * /, 1, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 2000;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted2, 0 / * tutte le righe * /, 2, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 2000;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted2, 0 / * tutte le righe * /, 3, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 2000;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted2, 0 / * tutte le righe * /, 4, m_ctrlText.txTableCellHorizontalExt, varTemp2);

				varTemp2.iVal = 5;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted2, 0 / * tutte le righe * /, 0 / * tutte le colonne * /, m_ctrlText.txTableCellBorderWidth, varTemp2);
				varTemp2.iVal = 0;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted2, 1, 0 / * tutte le colonne * /, m_ctrlText.txTableCellBorderWidth, varTemp2);

				m_ctrlText.TableCellSelect(shTableIdInserted2, 1, 1);
				m_ctrlText.SetAlignment(0); // 2 //
				m_ctrlText.SetFontBold(1);

				m_ctrlText.TableCellSelect(shTableIdInserted2, 2, 2);
				m_ctrlText.SetAlignment(2);
				m_ctrlText.SetFontBold(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 3, 2);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 4, 2);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 5, 2);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 6, 2);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 7, 2);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 8, 2);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.SetFontBold(1);

				m_ctrlText.TableCellSelect(shTableIdInserted2, 2, 3);
				m_ctrlText.SetAlignment(2);
				m_ctrlText.SetFontBold(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 3, 3);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 4, 3);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 5, 3);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 6, 3);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 7, 3);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 8, 3);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.SetFontBold(1);

				m_ctrlText.TableCellSelect(shTableIdInserted2, 2, 4);
				m_ctrlText.SetAlignment(2);
				m_ctrlText.SetFontBold(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 3, 4);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 4, 4);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 5, 4);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 6, 4);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 7, 4);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted2, 8, 4);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.SetFontBold(1);

				////////////////////////
				// formatto tabella 3 //
				////////////////////////

				varTemp2.iVal = 3150;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 0 / * tutte le righe * /, 1, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 850;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 0 / * tutte le righe * /, 2, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 500;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 0 / * tutte le righe * /, 3, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 3150;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 0 / * tutte le righe * /, 4, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 850;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 0 / * tutte le righe * /, 5, m_ctrlText.txTableCellHorizontalExt, varTemp2);

				varTemp2.iVal = 5;

				// tabella 3 sx //

				// m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 1, 1, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 2, 1, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 2, 2, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 3, 1, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 3, 2, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 4, 1, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 4, 2, m_ctrlText.txTableCellBorderWidth, varTemp2);

				m_ctrlText.TableCellSelect(shTableIdInserted3, 1, 1);
				m_ctrlText.SetAlignment(0); // 2 //
				m_ctrlText.SetFontBold(1);

				m_ctrlText.TableCellSelect(shTableIdInserted3, 2, 2);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted3, 3, 2);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted3, 4, 2);
				m_ctrlText.SetAlignment(1);

				// tabella 3 dx //

				// m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 1, 4, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 2, 4, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 2, 5, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 3, 4, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 3, 5, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 4, 4, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 4, 5, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 5, 4, m_ctrlText.txTableCellBorderWidth, varTemp2);
				m_ctrlText.put_TableCellAttribute(shTableIdInserted3, 5, 5, m_ctrlText.txTableCellBorderWidth, varTemp2);

				m_ctrlText.TableCellSelect(shTableIdInserted3, 1, 4);
				m_ctrlText.SetAlignment(0); // 2 //
				m_ctrlText.SetFontBold(1);

				m_ctrlText.TableCellSelect(shTableIdInserted3, 2, 5);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted3, 3, 5);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted3, 4, 5);
				m_ctrlText.SetAlignment(1);
				m_ctrlText.TableCellSelect(shTableIdInserted3, 5, 5);
				m_ctrlText.SetAlignment(1);

				////////////////////////
				// formatto tabella 4 //
				////////////////////////

				varTemp2.iVal = 2500;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted4, 0 / * tutte le righe * /, 1, m_ctrlText.txTableCellHorizontalExt, varTemp2);
				varTemp2.iVal = 2500;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted4, 0 / * tutte le righe * /, 2, m_ctrlText.txTableCellHorizontalExt, varTemp2);

				varTemp2.iVal = 5;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted4, 0 / * tutte le righe * /, 0 / * tutte le colonne * /, m_ctrlText.txTableCellBorderWidth, varTemp2);
				varTemp2.iVal = 0;
				m_ctrlText.put_TableCellAttribute(shTableIdInserted4, 1, 0 / * tutte le colonne * /, m_ctrlText.txTableCellBorderWidth, varTemp2);

				m_ctrlText.TableCellSelect(shTableIdInserted4, 1, 1);
				m_ctrlText.SetAlignment(0); // 2 //
				m_ctrlText.SetFontBold(1);

				//

				m_ctrlText.SetSelStart(-1);
				m_ctrlText.SetSelLength(0);

				*/
			}
		}
	}
}

void CRefertoExDlg::OnBtnPreview()
{
	//Julio 02/03/2018
	//if (theApp.AfxMessageBoxEndo(IDS_SALVARE_ANTEPRIMA, MB_YESNO) == IDYES)
	//{
	BeginWaitCursor();

	// salvo il referto //

	m_ctrlText.SetSelStart(0);
	m_ctrlText.SetSelLength(-1);

	if (CSpellCheckerDlg* pWSpell = GetWSpell())
		pWSpell->DeleteUnderline();

	CString sRefertoRtf = m_ctrlText.GetRTFSelText();
	CString sRefertoTxt = m_ctrlText.GetText();

	//

	CString sRefertoHtml = m_ctrlText.GetHTMLSelText();

	//

	if (m_pEsamiSet != NULL)
		m_pEsamiSet->SetReferto(sRefertoRtf, sRefertoTxt, sRefertoHtml);

	//

	EndWaitCursor();

	//

	m_pEsamiView->AnteprimaStampaReport(ANTEPRIMA_NO_STAMPA, VERIFICA_NO, m_sReportDefault, FALSE, 1, NULL,"");
	//}
}

void CRefertoExDlg::OnBtnCopyPrevRef()
{
	CString strTestoAttuale = m_ctrlText.GetText();
	if (!strTestoAttuale.IsEmpty())
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTOEXDLG_OVERWRITE_CONFIRM), MB_YESNO) == IDNO)
			return;
	}

	// faccio scegliere al medico l'esame da cui prelevare il referto //
	CListaOsservazioniDlg dlg(this, m_pEsamiView, m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pPazientiSet->m_sCognome + " " + m_pEsamiView->m_pPazientiSet->m_sNome, TRUE);
	dlg.DoModal();

	if (dlg.GetIDEsame() > 0)
	{
		CString sTestoNuovo = "";

		CString sFilter;
		sFilter.Format("Contatore=%li", dlg.GetIDEsame());

		CEsamiSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CRefertoExDlg::OnBtnCopyPrevRef"))
		{
			if (!setTemp.IsEOF())
				sTestoNuovo = setTemp.m_sRefertoTestoRtf;

			setTemp.CloseRecordset("CRefertoExDlg::OnBtnCopyPrevRef");
		}

		if (!sTestoNuovo.IsEmpty())
			SetReferto(sTestoNuovo);
		else
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTOEXDLG_EMPTY));
	}
}

void CRefertoExDlg::OnNMDblclkListFrasiRtf(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem >= 0)
	{
		long lIDFrase = m_ctrlListFrasiRTF.GetItemData(pNMItemActivate->iItem);

		CString sFraseRtf = CFrasiRtfSet().GetTestoRtf(lIDFrase);
		CString sFraseTxt = CFrasiRtfSet().GetTestoTxt(lIDFrase);

		if (!sFraseRtf.IsEmpty())
		{
			m_ctrlText.SetFocus();			// Marvel Carvalho - Bug 3457 (FIX) TEXTER
			ApplyTexterPhrase(lIDFrase);	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
		}
	}

	*pResult = 0;
}

// Sandro Gallina - 12/07/2004 //
void CRefertoExDlg::OnNMDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iCurSel;

	POSITION pos = m_ctrlListImage.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		iCurSel = m_ctrlListImage.GetNextSelectedItem(pos);

		pos = m_ImgListOrgani.FindIndex(iCurSel);
		if (pos != NULL)
		{
			IMG_ORGANI img_organi = m_ImgListOrgani.GetAt(pos);

			switch (img_organi.img.type)
			{
			case _image_:
			case _mptiff_:
			{
				m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);
				HBITMAP hTemp = m_pEsamiView->m_pImgManager->GetImg(img_organi.img.lID, FALSE, FALSE, FALSE);

				if (hTemp != NULL)
				{
					CDib dibTemp;
					dibTemp.Attach(CDib::BitmapToDIB(hTemp, NULL), TRUE);

					CMaximizeDlg dlgTemp(this, &dibTemp);
					dlgTemp.DoModal();
					DeleteObject(hTemp);
				}
				break;
			}
			case _movie_:
			{
				m_pEsamiView->m_pFormImmagini->ViewFilm(m_pEsamiView->m_pImgManager->GetFullPath(img_organi.img.lID));
				break;
			}
			case _dicom_:
			{
				CImageDicomDlg dlg(this, m_pEsamiView->m_pImgManager->GetFullPath(img_organi.img.lID));
				dlg.DoModal();
				break;
			}
			}
		}
	}

	m_ctrlListImage.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

	*pResult = 0;
}

void CRefertoExDlg::RiempiListaImmagini()
{
	int i;
	int nImages;

	if ((theApp.m_dwPrivileges & AMLogin_Permissions::view_image) == FALSE)
		return;

	CImgList listImg;

	BeginWaitCursor();
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	nImages = m_pEsamiView->m_pImgManager->GetImgList(&listImg);
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, nImages, "CRefertoExDlg::RiempiListaImmagini");

	m_ImgListOrgani = listImg;

	m_listImage.SetImageCount(nImages);
	m_ctrlListImage.DeleteAllItems();
	for (i = 0; i < nImages; i++)
	{
		POSITION pos = m_ImgListOrgani.FindIndex(i);

		if (pos != NULL)
		{
			IMG_ORGANI img_organi = m_ImgListOrgani.GetAt(pos);
			CBitmap* bmp = CBitmap::FromHandle(img_organi.img.hBmp);
			m_ctrlListImage.InsertItem(i, img_organi.img.szDescription, i);
			m_listImage.Replace(i, bmp, RGB(0, 0, 0));
		}
	}
	EndWaitCursor();
}

void CRefertoExDlg::OnSize(UINT nType, int cx, int cy)
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	CRect rectTemp;

	if (GetDlgItem(IDC_STATIC_FRAME1))
	{
		GetDlgItem(IDC_STATIC_FRAME1)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_BUTTONBAR)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	if (GetDlgItem(IDC_STATIC_FRAME2))
	{
		GetDlgItem(IDC_STATIC_FRAME2)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_TEXTCONTROL)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOZORDER);
	}

	if (GetDlgItem(IDC_STATIC_FRAME3))
	{
		GetDlgItem(IDC_STATIC_FRAME3)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_TEXTCONTROL_ALTRIREFERTI)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOZORDER);
	}

	if (GetDlgItem(IDC_STATIC_FRAME5))
	{
		GetDlgItem(IDC_STATIC_FRAME5)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_TEXTCONTROL_REFERENCES)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOZORDER);
	}

	if (GetDlgItem(IDC_STATIC_FRAME6))
	{
		GetDlgItem(IDC_STATIC_FRAME6)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_TEXTCONTROL_ANAMNESI)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOZORDER);
	}

	if (GetDlgItem(IDC_STATIC_FRAME4) && m_ctrlToolbar.GetSafeHwnd())
		m_ctrlToolbar.AttachEx(IDC_STATIC_FRAME4, this);

	if (m_pChecklistForm != NULL)
		m_pChecklistForm->SendMessage(EPM_RESIZE_FORM, 0, 0);
	if (m_pTabellaForm != NULL)
		m_pTabellaForm->SendMessage(EPM_RESIZE_FORM, 0, 0);

	PdfViewer_Resize(m_uiPreview);
}

void CRefertoExDlg::OnTextControlChange()
{
	if ((m_ctrlText.GetEditMode() == 0) && !m_ctrlText.IsAutoChanging() && !m_bImClosing)
	{
		TRACE0("--> CRefertoExDlg::OnTextControlChange\n");

		if (CSpellCheckerDlg* pWSpell = GetWSpell())
			pWSpell->Check();

		// Sandro 13/04/2017 //

		if (!m_sReportDefault.IsEmpty())
		{
			short shTab = m_ctrlText.GetTableAtInputPos();
			TRACE1("Table index: %d\n", (int)shTab);
			if (shTab == 0) // Sandro 12/05/2017 // lo faccio solo se NON sono dentro ad una tabella //
			{
				m_ctrlText.SetRedraw(FALSE);

				int iSelStart = m_ctrlText.GetSelStart();
				int iSelLength = m_ctrlText.GetSelLength();

				m_ctrlText.SetSelStart(0);
				m_ctrlText.SetSelLength(-1);

				m_sRTFSelText = m_ctrlText.GetRTFSelText();
				m_bIsTextChanged = TRUE;

				m_ctrlText.SetSelStart(iSelStart);
				m_ctrlText.SetSelLength(iSelLength);

				m_ctrlText.SetRedraw(TRUE);
				m_ctrlText.RedrawWindow();
			}
		}
	}
}

void CRefertoExDlg::OnTextControlMouseDown(short Button, short Shift, long X, long Y)
{
	if (Button != 2)
		return;

	if (m_ctrlText.GetEditMode() == 0)
	{
		if (CSpellCheckerDlg* pWSpell = GetWSpell())
			pWSpell->Menu(CPoint(X, Y));
	}
}

CSpellCheckerDlg* CRefertoExDlg::GetWSpell()
{
	if (!m_WSpellChecker.Create(m_pEsamiView))
		return NULL;

	m_WSpellChecker.SetTextControl(&m_ctrlText);
	return &m_WSpellChecker;
}

void CRefertoExDlg::DestroyWSpell()
{
	m_WSpellChecker.Destroy();
}

void CRefertoExDlg::CaricaTestoAltroReferto()
{
	//Julio Centralizacao
	m_ctrlEditInfoLaudoAnterior.SetWindowText("");
	m_ctrlBtnConsultaResultado.EnableWindow(FALSE);
	//

	m_ctrlTextAltriReferti.ResetContents();
	m_ctrlStatic01.SetWindowText("");
	m_ctrlStatic02.SetWindowText("");

	if (!m_setVistaRefertiPaziente.IsBOF() && !m_setVistaRefertiPaziente.IsEOF())
	{
		// Sandro 19/12/2013 // cambio perchè a Mantova per qualche strano motivo non funziona //
		m_ctrlTextAltriReferti.SetRTFSelText(m_setVistaRefertiPaziente.m_sReferto);

		// Sandro 24/07/2015 // lo rimetto temporaneamente perché sto spostando i referti nella EEsami e mi viene comodo così, casomai lo sistemerò più avanti... //
		// m_ctrlTextAltriReferti.SetRTFSelText(CRefertoSet().GetRefertoRtf(m_setVistaRefertiPaziente.m_lIDEsame));

		//

		CString sTemp;
		sTemp.Format(theApp.GetMessageString(IDS_ESAMIVIEW_EXAM_NUM_2), m_lNumRefertiAct, m_lNumRefertiTot);
		m_ctrlStatic01.SetWindowText(sTemp);

		//

		CString sTipoEsame = m_setVistaRefertiPaziente.m_sTipoEsame;
		sTipoEsame.Trim();

		if (sTipoEsame.IsEmpty())
			sTipoEsame = theApp.GetMessageString(IDS_IMAGENT_TAB_1);

		if (m_setVistaRefertiPaziente.IsFieldNull(&m_setVistaRefertiPaziente.m_lData) || (m_setVistaRefertiPaziente.m_lData == 0))
			m_ctrlStatic02.SetWindowText(sTipoEsame);
		else
			m_ctrlStatic02.SetWindowText(sTipoEsame + " " + theApp.GetMessageString(IDS_DEL) + " " + CCustomDate(m_setVistaRefertiPaziente.m_lData).GetDate("%d/%m/%Y"));
	}
}

void CRefertoExDlg::OnBnClickedBtnInsertTable()
{
	m_ctrlText.RtfInsertNewTable(this);
}

void CRefertoExDlg::OnBnClickedBtnMakeUpper()
{
	m_ctrlText.RtfSelectedTextMakeUpper();
}

void CRefertoExDlg::OnBnClickedBtnMakeNormal()
{
	m_ctrlText.RtfSelectedTextMakeNormal();
}

void CRefertoExDlg::OnBnClickedBtnMakeLower()
{
	m_ctrlText.RtfSelectedTextMakeLower();
}

void CRefertoExDlg::OnBnClickedBtnRtfFont() //Julio - BUG 4392 Edicao de texto
{
	m_ctrlText.RtfSetFontProperties();
}


void CRefertoExDlg::OnBnClickedBtnPrev()
{
	m_setVistaRefertiPaziente.MovePrev();
	m_lNumRefertiAct--;

	m_ctrlBtnPrev.EnableWindow(m_lNumRefertiAct > 1);
	m_ctrlBtnNext.EnableWindow(TRUE);

	CaricaTestoAltroReferto();
}

void CRefertoExDlg::OnBnClickedBtnNext()
{
	m_setVistaRefertiPaziente.MoveNext();
	m_lNumRefertiAct++;

	m_ctrlBtnPrev.EnableWindow(TRUE);
	m_ctrlBtnNext.EnableWindow(m_lNumRefertiAct < m_lNumRefertiTot);

	CaricaTestoAltroReferto();
}

void CRefertoExDlg::OnEnChangeEditRtfCodiceFrase()
{
	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	if (!m_bProcessOnEnChange)
		return;

	const int iMinLenCodice = 2;
	const int iMinLenFrase = 4;

	BeginWaitCursor();
	m_ctrlListFrasiRTF.SetRedraw(FALSE);
	m_ctrlListFrasiRTF.DeleteAllItems();

	CString sCodice;
	m_ctrlEditRtfCodice.GetWindowText(sCodice);
	sCodice.Trim();
	sCodice.Replace("'", "''");

	CString sFrase;
	m_ctrlEditRtfFrase.GetWindowText(sFrase);
	sFrase.Trim();
	sFrase.Replace("'", "''");

	if ((sCodice.GetLength() >= iMinLenCodice) || (sFrase.GetLength() >= iMinLenFrase))
	{
		CString sFilter = "";

		if (sCodice.GetLength() > 0)
		{
			if (!sFilter.IsEmpty())
				sFilter += " AND ";

			sFilter += "Codice LIKE '" + sCodice + "%%'";
		}

		if (sFrase.GetLength() > 0)
		{
			if (!sFilter.IsEmpty())
				sFilter += " AND ";

			sFilter += "TestoTXT LIKE '%%" + sFrase + "%%'";
		}

		CFrasiRtfSet setFrasi;
		setFrasi.SetOpenFilter(sFilter);
		if (setFrasi.OpenRecordset("CRefertoExDlg::OnEnChangeEditRtfCodiceFrase"))
		{
			int nItem = 0;

			while (!setFrasi.IsEOF())
			{
				m_ctrlListFrasiRTF.InsertItem(nItem, "");
				m_ctrlListFrasiRTF.SetItemData(nItem, setFrasi.m_lID);

				m_ctrlListFrasiRTF.SetItemText(nItem, 1, setFrasi.m_sCodice);
				m_ctrlListFrasiRTF.SetItemText(nItem, 2, setFrasi.m_sTestoTXT);

				nItem++;
				setFrasi.MoveNext();
			}

			setFrasi.CloseRecordset("CRefertoExDlg::OnEnChangeEditRtfCodiceFrase");
		}
	}

	if (m_ctrlListFrasiRTF.GetItemCount() > 0)
		m_ctrlListFrasiRTF.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	else
		m_ctrlListFrasiRTF.SetColumnWidth(2, 133);

	m_ctrlListFrasiRTF.SetRedraw(TRUE);
	EndWaitCursor();
}

LRESULT CRefertoExDlg::OnAddRtfTextToReport(WPARAM wParam, LPARAM lParam)
{
	CString* pTextToInsert = (CString*)wParam;
	if (pTextToInsert != NULL)
	{
		pTextToInsert->Trim();
		if (!pTextToInsert->IsEmpty())
		{
			try
			{
				m_ctrlText.SetRTFSelText(*pTextToInsert);
			}
			catch (CException* e)
			{
				e->Delete();
				m_ctrlText.SetSelText(*pTextToInsert);
			}
		}
	}
	return 0;
}

LRESULT CRefertoExDlg::OnAddTxtTextToReport(WPARAM wParam, LPARAM lParam)
{
	CString* pTextToInsert = (CString*)wParam;
	CString* pTextTabs = (CString*)lParam;

	if (pTextTabs->Right(1) != ";")
		pTextTabs->Append(";");

	CStringList listTabs;

	int nLastPos = 0, nPos = 0;
	while (nPos != -1)
	{
		nPos = pTextTabs->Find(";", nLastPos);
		if (nPos != -1)
		{
			CString strTabDef = pTextTabs->Mid(nLastPos, nPos - nLastPos);
			if (atol(strTabDef.Left(strTabDef.GetLength() - 1)) > 0 &&
				(strTabDef.Right(1) == "L" ||
				strTabDef.Right(1) == "C" ||
				strTabDef.Right(1) == "R"))
			{
				listTabs.AddTail(strTabDef);
			}
			nLastPos = nPos + 1;
		}
	}

	//if (m_ctrlText.GetColumns() != 0)
	//	m_ctrlText.SetSelText("\r\n");

	int pTabs[14], pTabsType[14];

	if (listTabs.GetCount() > 0)
	{
		for (int i = 14; i >= 1; i--)
		{
			m_ctrlText.SetTabCurrent(i);

			pTabs[i - 1] = m_ctrlText.GetTabPos();
			pTabsType[i - 1] = m_ctrlText.GetTabType();

			m_ctrlText.SetTabPos(0);
		}

		for (int i = 0; i < listTabs.GetCount(); i++)
		{
			CString strTabDef = listTabs.GetAt(listTabs.FindIndex(i));
			m_ctrlText.SetTabCurrent(i + 1);

			m_ctrlText.SetTabPos(atol(strTabDef.Left(strTabDef.GetLength() - 1)));

			if (strTabDef.Right(1) == "L")
				m_ctrlText.SetTabType(1);
			if (strTabDef.Right(1) == "C")
				m_ctrlText.SetTabType(3);
			if (strTabDef.Right(1) == "R")
				m_ctrlText.SetTabType(2);
		}
	}

	m_ctrlText.SetSelText(*pTextToInsert);

	if (listTabs.GetCount() > 0)
	{
		for (int i = 14; i >= 1; i--)
		{
			m_ctrlText.SetTabCurrent(i);
			m_ctrlText.SetTabPos(0);
		}

		for (int i = 0; i < 14; i++)
		{
			m_ctrlText.SetTabCurrent(i + 1);
			m_ctrlText.SetTabPos(pTabs[i]);
			m_ctrlText.SetTabType(pTabsType[i]);
		}
	}
	return 0;
}

void CRefertoExDlg::OnBnClickedBtnSave()
{
	//Gabriel BUG 5533
	if (m_bSpermChartMeasurementUpdated || IsSpermExam())
	{
		if (!CanClose())
			return;

		SaveEditedMeasurement();//Julio - correcao lista biometria
		//Gabriel BUG 5533
		CString sMessage;
		sMessage.Format(theApp.GetMessageString(IDS_MEASUREMENTS_SPERM_NEWCHART_CONFIRM));

		if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO) == IDYES)
		{
			if (m_sConcentracao.IsEmpty() || m_sMotilidadeProgressiva.IsEmpty() || m_sMorfologia.IsEmpty())
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MEASUREMENTS_SPERM_NEWCHART_ERROR1));

			else
			{
				char szModuleName[MAX_PATH];
				GetModuleFileName(NULL, szModuleName, sizeof(szModuleName));

				BOOL export2Pacs = FALSE;
				//In modalità 2 devo avviare il trasferimento automatico su PACS
				if (theApp.m_lDcmStoreMode == 2)
					export2Pacs = TRUE;

				CString sDirProg = szModuleName;
				int nTemp = sDirProg.ReverseFind('\\');

				CString sFileConfig = sDirProg.Left(nTemp) + "\\SpermChartCreator.exe";
				CString sChartTempFolder = sDirProg.Left(nTemp) + "\\TEMP\\SPERMCHARTCREATOR";
				CString sImageFile;
				sImageFile.Format("%s\\%li_%li.JPG", sChartTempFolder, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);
				//Gabriel - BUG 5533 V2
				m_sConcentracao.Replace(".", ",");
				m_sMotilidadeProgressiva.Replace(".", ",");
				m_sMorfologia.Replace(".", ",");

				StartProcess(sFileConfig + " \"" + m_sConcentracao + "\" \"" + m_sMotilidadeProgressiva + "\" \"" + m_sMorfologia + "\" \"" + sImageFile + "\" ");
				CStringList ArraySelected;
				ArraySelected.AddTail(sImageFile);
				CImgIDList listIDImageImported;
				if (m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &ArraySelected, FORM_MINI, FORM_MINI, &listIDImageImported, export2Pacs, FALSE, FALSE) > 0)
					DeleteFile(sImageFile);
				m_pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);
				listIDImageImported.RemoveAll();
				ArraySelected.RemoveAll();
			}
		}
	}
	else
	{
		if (!CanClose())
			return;

		SaveEditedMeasurement();//Julio - correcao lista biometria
	}

	m_bImClosing = TRUE;

	m_ctrlText.SetSelStart(0);
	m_ctrlText.SetSelLength(-1);

	if (CSpellCheckerDlg* pWSpell = GetWSpell())
		pWSpell->DeleteUnderline();

	CString sRefertoRtf = m_ctrlText.GetRTFSelText();
	CString sRefertoTxt = m_ctrlText.GetText();

	// Sandro 14/09/2016 //

	CString sRefertoHtml = m_ctrlText.GetHTMLSelText();
	if (theApp.m_bUsaModuloGenomica) //removing tables fixed width for genomica reports
	{
		int nPos = 0;
		while (nPos < sRefertoHtml.GetLength())
		{

			int nTablePos = sRefertoHtml.Find("<table", nPos);//find table tag
			if (nTablePos < 0)
				break;

			int nWidthPos = sRefertoHtml.Find("width:", nTablePos); //find width property inside table tag
			int nSemiCPos = sRefertoHtml.Find(";", nWidthPos) + 1; //find the ; after the width property
			int nTablePosEnd = sRefertoHtml.Find(">", nTablePos);//find table tag

			CString sTableTag = sRefertoHtml.Mid(nTablePos, (nTablePosEnd - nTablePos) + 1);
			CString sTableTagRep = sRefertoHtml.Mid(nTablePos, (nTablePosEnd - nTablePos) + 1);
			CString sWidthVal = sRefertoHtml.Mid(nWidthPos + 6, ((nSemiCPos - 1) - (nWidthPos + 6))).Trim();

			sTableTagRep.Replace(sWidthVal, "100%");
			sRefertoHtml.Replace(sTableTag, sTableTagRep);

			nPos = nTablePos + 1;
		}
	}
	//

	if (m_pEsamiSet != NULL)
		m_pEsamiSet->SetReferto(sRefertoRtf, sRefertoTxt, sRefertoHtml);

	// if (m_pChecklistForm)
	// m_pChecklistForm->SaveData();

	if (m_pTabellaForm)
		m_pTabellaForm->SaveData();

	CEndoxResizableDlg::OnOK();
}

void CRefertoExDlg::OnBnClickedBtnUndo()
{
	CEndoxResizableDlg::OnCancel();
}

DWORD WINAPI CRefertoExDlg::ThreadPdfPageCount(LPVOID lpParam)
{
	CRefertoExDlg* pDlg = (CRefertoExDlg*)lpParam;

	while (WaitForSingleObject(pDlg->m_hEventExitPdfPageCountThread, 0) != WAIT_OBJECT_0)
	{
		if (pDlg->m_bIsTextChanged)
		{
			pDlg->m_bIsTextChanged = FALSE;

			pDlg->m_sRTFSelText.Trim();
			// if (!pDlg->m_sRTFSelText.IsEmpty())
			{
				long lUserID;
				AMLogin_GetUserID(&lUserID);

				//

				CString sBase64ReportRtf = "";

				DWORD dwEncodeBufferLength = AmBase64_CalculateRequiredEncodeOutputBufferSize(pDlg->m_sRTFSelText.GetLength());
				char* pBufferB64 = new char[dwEncodeBufferLength];
				ZeroMemory(pBufferB64, dwEncodeBufferLength * sizeof(char));
				AmBase64_EncodeBuffer(pDlg->m_sRTFSelText.GetBuffer(), pDlg->m_sRTFSelText.GetLength(), pBufferB64);
				pDlg->m_sRTFSelText.ReleaseBuffer();
				sBase64ReportRtf = CString(pBufferB64);
				delete[] pBufferB64;

				//

				CString connStr = theApp.m_dbEndox.GetDecryptedConnectionString();
				connStr.Replace("ODBC;", "");

				CString sXML;
				sXML.Format("<EndoxReportMakerRequest><OdbcConnectionString>%s</OdbcConnectionString><ReportName>%s</ReportName><UO>%li</UO><PatientID>%li</PatientID><ExamID>%li</ExamID><UserID>%li</UserID><Username>%s</Username><IdPrelievo>0</IdPrelievo><ReportRtf>%s</ReportRtf></EndoxReportMakerRequest>",
					connStr,
					pDlg->m_sReportDefault,
					theApp.m_lUO,
					pDlg->m_pEsamiSet->m_lPaziente,
					pDlg->m_pEsamiSet->m_lContatore,
					lUserID,
					theApp.m_sUtenteLoggato,
					sBase64ReportRtf);

				//

				SECURITY_ATTRIBUTES sa;
				sa.nLength = sizeof(SECURITY_ATTRIBUTES);
				sa.bInheritHandle = TRUE;
				sa.lpSecurityDescriptor = NULL;

				HANDLE hChildStdinRd, hChildStdinWr;
				if (!CreatePipe(&hChildStdinRd, &hChildStdinWr, &sa, sXML.GetLength() + 1))
				{
					// MessageBox(NULL, "CreatePipe 1 error", "", MB_OK);
					// return FALSE;
				}

				HANDLE hChildStdoutRd, hChildStdoutWr;
				if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &sa, 10000000))
				{
					// MessageBox(NULL, "CreatePipe 2 error", "", MB_OK);
					// return FALSE;
				}

				int iSteps = (sXML.GetLength() / 1000000);
				if (sXML.GetLength() % 1000000)
					iSteps++;

				for (int i = 0; i < iSteps; i++)
				{
					DWORD dwWritten;
					if (!::WriteFile(hChildStdinWr,
						sXML.GetBuffer() + (i * 1000000),
						(i == iSteps - 1) ? sXML.GetLength() - (i * 1000000) : 1000000,
						&dwWritten,
						NULL))
					{
						// TCHAR szBuffer[MAX_PATH];
						// sprintf_s(szBuffer, "WriteFile 1 error %li", GetLastError());
						// MessageBox(NULL, szBuffer, "", MB_OK);
						// return FALSE;
					}
				}

				sXML.ReleaseBuffer();

				CloseHandle(hChildStdinWr);

				PROCESS_INFORMATION pi;
				ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

				STARTUPINFO si;
				ZeroMemory(&si, sizeof(STARTUPINFO));
				si.cb = sizeof(STARTUPINFO);
				si.dwFlags = STARTF_USESTDHANDLES;
				si.hStdInput = hChildStdinRd;
				si.hStdOutput = hChildStdoutWr;
				si.hStdError = NULL;

				char szProcess[1024];
				sprintf(szProcess, "%s\\EndoxReportMaker\\EndoxReportMaker.exe", theApp.m_sDirProg);

				if (CreateProcess(NULL,
					szProcess,
					NULL,
					NULL,
					TRUE,
					CREATE_NO_WINDOW,
					NULL,
					NULL,
					&si,
					&pi))
				{
					WaitForSingleObject(pi.hProcess, INFINITE);

					// if (GetExitCodeProcess(pi.hProcess, &dwExitCode) && dwExitCode == 0)
					{
						DWORD dwTotalBytes = 0, dwReaded;
						if (PeekNamedPipe(hChildStdoutRd, NULL, 0, NULL, &dwTotalBytes, NULL) && dwTotalBytes > 0)
						{
							// int const iSize = 2 * 1024 * 1024;
							// char szBufferPDF[iSize];

							// if (dwTotalBytes <= iSize)
							{
								BYTE* pBufferTemp = new BYTE[dwTotalBytes];
								if (::ReadFile(hChildStdoutRd, pBufferTemp, dwTotalBytes, &dwReaded, NULL))
								{
									CString sResponse(pBufferTemp);

									if (sResponse.Find("<ErrorCode>0</ErrorCode>") > 0)
									{
										int iFind1 = sResponse.Find("<PdfBufferBase64>");
										int iFind2 = sResponse.Find("</PdfBufferBase64>", iFind1);

										if ((iFind1 > 0) && (iFind2 > 0))
										{
											CString sBase64 = sResponse.Mid(iFind1 + 17, iFind2 - (iFind1 + 17));

											DWORD dwDecodeBufferLength = AmBase64_CalculateRequiredDecodeOutputBufferSize(sBase64.GetBuffer());
											char* pBuffer = new char[dwDecodeBufferLength];
											AmBase64_DecodeBuffer(sBase64.GetBuffer(), sBase64.GetLength(), pBuffer);
											sBase64.ReleaseBuffer();

											if (WaitForSingleObject(pDlg->m_hEventExitPdfPageCountThread, 0) != WAIT_OBJECT_0)
												if (!pDlg->m_bImClosing)
													pDlg->SendMessage(EPM_THREAD_PDF_COUNT_PAGES_UPDATE, (WPARAM)pBuffer, (LPARAM)dwDecodeBufferLength);

											delete[] pBuffer;
										}
									}

									// memcpy(pBufferPDF, pBufferTemp + iPos, dwReaded - iPos);

									// *pPDFBytesSize = dwReaded - iPos;
									// bResult = TRUE;
								}
								// else
								// MessageBox(NULL, "ReadFile error", "", MB_OK);

								delete[] pBufferTemp;
							}
							// else
							// MessageBox(NULL, "dwTotalBytes <= iBufferPDFLength", "", MB_OK);
						}
						// else
						// MessageBox(NULL, "PeekNamedPipe error", "", MB_OK);
					}
					/* else
					{
					// TCHAR szError[255];
					// sprintf_s(szError, "ExitCodeProcess %li", dwExitCode);
					// MessageBox(NULL, szError, "", MB_OK);
					} */

					CloseHandle(pi.hThread);
					CloseHandle(pi.hProcess);
				}
				else
				{
					// MessageBox(NULL, "CreateProcess error", "", MB_OK);
				}

				CloseHandle(hChildStdinRd);
				CloseHandle(hChildStdoutRd);
				CloseHandle(hChildStdoutWr);
			}
			/*
			else
			{
			if (WaitForSingleObject(pDlg->m_hEventExitPdfPageCountThread, 0) != WAIT_OBJECT_0)
			pDlg->SendMessage(EPM_THREAD_PDF_COUNT_PAGES_END, (WPARAM)1, NULL);
			}
			*/
		}
		else
		{
			Sleep(200);
		}
	}

	return 0;
}

LRESULT CRefertoExDlg::OnThreadPdfCountPagesUpdate(WPARAM wParam, LPARAM lParam)
{
	int iCurPage = 1;

	CString sAsd;
	GetDlgItemText(IDC_STATIC_PAGE, sAsd);

	if (!sAsd.IsEmpty())
	{
		int iSep = sAsd.Find('/');

		CString sLef = sAsd.Left(iSep);
		if (!sLef.IsEmpty())
			iCurPage = atoi(sLef);
	}

	if (iCurPage <= 0)
		iCurPage = 1;

	//

	if (m_pPdfBuffer != NULL)
	{
		delete m_pPdfBuffer;
		m_pPdfBuffer = NULL;
	}

	m_pPdfBuffer = new BYTE[lParam];
	memcpy(m_pPdfBuffer, (void*)wParam, lParam);

	PdfViewer_LoadFromBuffer(m_uiPreview, m_pPdfBuffer, (UINT)lParam);
	PdfViewer_SetCurrentZoom(m_uiPreview, CPdfAnteprimaDlg::m_lDefaultZoomValue);

	CString sNumber;
	sNumber.Format("%s %li", theApp.GetMessageString(IDS_NUMERO_PAGINE), PdfViewer_GetNumberOfPages(m_uiPreview));
	sNumber.Trim();
	SetDlgItemText(IDC_STATIC_PAGECOUNT, sNumber);

	//

	while (iCurPage > 1)
	{
		if (PdfViewer_GetCurrentPage(m_uiPreview) + 1 < PdfViewer_GetNumberOfPages(m_uiPreview))
			PdfViewer_GoToNextPage(m_uiPreview);
		else
			break;

		iCurPage--;
	}

	m_ctrlBtnPrevPdfPage.EnableWindow(PdfViewer_GetCurrentPage(m_uiPreview) > 0);
	m_ctrlBtnNextPdfPage.EnableWindow(PdfViewer_GetCurrentPage(m_uiPreview) + 1 < PdfViewer_GetNumberOfPages(m_uiPreview));

	CString strPage;
	strPage.Format("%li/%li", PdfViewer_GetCurrentPage(m_uiPreview) + 1, PdfViewer_GetNumberOfPages(m_uiPreview));
	SetDlgItemText(IDC_STATIC_PAGE, strPage);

	//

	m_ctrlBtnZoomIn.EnableWindow(PdfViewer_GetCurrentZoom(m_uiPreview) < PdfViewer_GetMaxZoom());
	m_ctrlBtnZoomOut.EnableWindow(PdfViewer_GetCurrentZoom(m_uiPreview) > PdfViewer_GetMinZoom());

	CString strZoom;
	strZoom.Format("%li%%", PdfViewer_GetCurrentZoom(m_uiPreview));
	SetDlgItemText(IDC_STATIC_ZOOM, strZoom);

	//

	return 0;
}

/*
LRESULT CRefertoExDlg::OnThreadPdfCountPagesEnd(WPARAM wParam, LPARAM lParam)
{
CString sNumber;
sNumber.Format("%s %li", theApp.GetMessageString(IDS_NUMERO_PAGINE), (long)wParam);
sNumber.Trim();
SetDlgItemText(IDC_STATIC_PAGECOUNT, sNumber);

TRACE1("CRefertoExDlg::OnThreadPdfCountPagesEnd --> %li\n", (long)wParam);

return 0;
}
*/

void CRefertoExDlg::OnBnClickedBtnPrev2()
{
	BeginWaitCursor();

	PdfViewer_GoToPreviousPage(m_uiPreview);

	CRect rectTemp;
	GetDlgItem(IDC_PDF_PLACE)->GetWindowRect(rectTemp);
	ScreenToClient(rectTemp);
	InvalidateRect(rectTemp, FALSE);

	m_ctrlBtnPrevPdfPage.EnableWindow(PdfViewer_GetCurrentPage(m_uiPreview) > 0);
	m_ctrlBtnNextPdfPage.EnableWindow(PdfViewer_GetCurrentPage(m_uiPreview) + 1 < PdfViewer_GetNumberOfPages(m_uiPreview));

	CString strPage;
	strPage.Format("%li/%li", PdfViewer_GetCurrentPage(m_uiPreview) + 1, PdfViewer_GetNumberOfPages(m_uiPreview));
	SetDlgItemText(IDC_STATIC_PAGE, strPage);

	EndWaitCursor();
}

void CRefertoExDlg::OnBnClickedBtnNext2()
{
	BeginWaitCursor();

	PdfViewer_GoToNextPage(m_uiPreview);

	CRect rectTemp;
	GetDlgItem(IDC_PDF_PLACE)->GetWindowRect(rectTemp);
	ScreenToClient(rectTemp);
	InvalidateRect(rectTemp, FALSE);

	m_ctrlBtnPrevPdfPage.EnableWindow(PdfViewer_GetCurrentPage(m_uiPreview) > 0);
	m_ctrlBtnNextPdfPage.EnableWindow(PdfViewer_GetCurrentPage(m_uiPreview) + 1 < PdfViewer_GetNumberOfPages(m_uiPreview));

	CString strPage;
	strPage.Format("%li/%li", PdfViewer_GetCurrentPage(m_uiPreview) + 1, PdfViewer_GetNumberOfPages(m_uiPreview));
	SetDlgItemText(IDC_STATIC_PAGE, strPage);

	EndWaitCursor();
}

void CRefertoExDlg::OnBnClickedBtnZoomOut()
{
	BeginWaitCursor();

	PdfViewer_ZoomOut(m_uiPreview);
	CPdfAnteprimaDlg::m_lDefaultZoomValue = PdfViewer_GetCurrentZoom(m_uiPreview);

	m_ctrlBtnZoomIn.EnableWindow(PdfViewer_GetCurrentZoom(m_uiPreview) < PdfViewer_GetMaxZoom());
	m_ctrlBtnZoomOut.EnableWindow(PdfViewer_GetCurrentZoom(m_uiPreview) > PdfViewer_GetMinZoom());

	CString strZoom;
	strZoom.Format("%li%%", PdfViewer_GetCurrentZoom(m_uiPreview));
	SetDlgItemText(IDC_STATIC_ZOOM, strZoom);

	EndWaitCursor();
}

void CRefertoExDlg::OnBnClickedBtnZoomIn()
{
	BeginWaitCursor();

	PdfViewer_ZoomIn(m_uiPreview);
	CPdfAnteprimaDlg::m_lDefaultZoomValue = PdfViewer_GetCurrentZoom(m_uiPreview);

	m_ctrlBtnZoomIn.EnableWindow(PdfViewer_GetCurrentZoom(m_uiPreview) < PdfViewer_GetMaxZoom());
	m_ctrlBtnZoomOut.EnableWindow(PdfViewer_GetCurrentZoom(m_uiPreview) > PdfViewer_GetMinZoom());

	CString strZoom;
	strZoom.Format("%li%%", PdfViewer_GetCurrentZoom(m_uiPreview));
	SetDlgItemText(IDC_STATIC_ZOOM, strZoom);

	EndWaitCursor();
}

void CRefertoExDlg::OnBnClickedBtnCopy()
{
	//m_ctrlText.SetText("");
	m_ctrlText.SetRTFSelText(m_ctrlTextAltriReferti.GetRTFSelText());
}

void CRefertoExDlg::OnBnClickedBtnGetLaudoAnterior()
{

	AfxGetApp()->BeginWaitCursor();

	m_ctrlBtnCopy.EnableWindow(FALSE);
	m_ctrlBtnGetLaudoAnterior.EnableWindow(FALSE);
	m_ctrlBtnGetLaudoAnterior.SetWindowTextA("Buscando...");

	CString sMessaggio;

	CString sCodEsame = m_pEsamiView->m_pEsamiSet->m_sCodEsame;
	CString sRicovero = m_pEsamiView->m_pEsamiSet->m_sRicovero;
	CString sItem = "";
	CString sSiglaUtente = "";

	int n1 = sCodEsame.Find("_");
	if (n1 > 0)
	{
		int n2 = sCodEsame.Find("_", n1 + 1);
		if (n2 > 0)
		{
			sItem = sCodEsame.Mid(n1 + 1, n2 - (n1 + 1));
			sItem += "00";

			//

			long lUserID;
			AMLogin_GetUserID(&lUserID);

			if (CMediciSet().GetContatoreFromUserID(lUserID) > 0)
			{	// se sono un medico devo usare il mio 3L3N //
				sSiglaUtente = CMediciSet().GetCodiceFromUserID(lUserID);
				//Julio Login SEGU
				/*if (sSiglaUtente.GetLength() > 3)
				sSiglaUtente = sSiglaUtente.Left(3);*/
			}
			else
			{	// se non sono un medico uso il 3L3N della Tesi //
				//sSiglaUtente = CString("EQT496").Left(3);
				//Julio Login SEGU
				sSiglaUtente = "13551";
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FLEURY_ERROR_001));
			return;
		}
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FLEURY_ERROR_001));
		return;
	}

	//AfxBeginThread(GetLaudoRtfAnterior, this);

	CString sEndpoint = theApp.m_sLaudoRtfExameAnteriorEndpoint;
	CString sIdSistema = "1"; // sempre 1, è endox //

	sRicovero.Replace("'", "''");
	sRicovero.Trim();

	sItem.Replace("'", "''");
	sItem.Trim();

	sSiglaUtente.Replace("'", "''");
	sSiglaUtente.Trim();

	sIdSistema.Replace("'", "''");
	sIdSistema.Trim();


	obterLaudoRtfExameAnteriorRequest request;
	sprintf_s(request.szFicha, sRicovero);
	sprintf_s(request.szItem, sItem);
	sprintf_s(request.szSiglaUsuarioSistema, sSiglaUtente);
	sprintf_s(request.szIdSistema, sIdSistema);

	CGetPatientExamDataService getpatientexamdataService(sEndpoint);
	obterLaudoRtfExameAnteriorResponse response = getpatientexamdataService.ObterLaudoRtfExameAnterior(request);

	if (strcmp(response.szCodigoDeErro, "0") == 0)
	{
		char rtf[135073];
		strcpy(rtf, response.pSzCorpoRtf);
		//strcat(rtf, response.szRodapeRtf);

		m_ctrlTextAltriReferti.SetText("");
		m_ctrlTextAltriReferti.Refresh();

		m_ctrlTextAltriReferti.SetRTFSelText(rtf);
		m_ctrlTextAltriReferti.Refresh();

		m_sFichaLaudoAnterior = CString(response.szNumeroFicha);
		m_sItemLaudoAnterior = CString(response.szNumeroItem);
		m_sDataLaudoAnterior = CString(response.szDataAbertura);
		m_sDataLaudoAnterior.Replace("T", " ");

		CString sInfoLaudoAnterior =
			"Ficha " + m_sFichaLaudoAnterior +
			" Item " + m_sItemLaudoAnterior +
			" - Data de Abertura: " + m_sDataLaudoAnterior;

		m_ctrlEditInfoLaudoAnterior.SetWindowText(sInfoLaudoAnterior);

		if (!m_sFichaLaudoAnterior.IsEmpty() && !m_sItemLaudoAnterior.IsEmpty())
			m_ctrlBtnConsultaResultado.EnableWindow(TRUE);
	}
	else
	{
		theApp.AfxMessageBoxEndo(response.szError);
	}

	if (response.pSzCorpoRtf != NULL)
		delete response.pSzCorpoRtf;
	if (response.pSzRubrica != NULL)
		delete response.pSzRubrica;



	m_ctrlBtnGetLaudoAnterior.SetWindowTextA("Laudo Exame Anterior");
	m_ctrlBtnGetLaudoAnterior.EnableWindow(TRUE);
	m_ctrlBtnCopy.EnableWindow(TRUE);

	AfxGetApp()->EndWaitCursor();

}

UINT CRefertoExDlg::GetLaudoRtfAnterior(LPVOID pParam)
{
	//Not Implemented
	return 0;
}

void CRefertoExDlg::OnBnClickedBtnConsultaResultado()
{
	FleuryApriConsulta(m_pEsamiView->m_pEsamiSet->m_sCodEsame);
}

//Julio
void CRefertoExDlg::OnBnClickedCheck1()
{
	m_setVistaRefertiPaziente.CloseRecordset("CRefertoExDlg::OnBnClickedCheck1");

	m_lNumRefertiAct = 0;
	m_lNumRefertiTot = 0;

	CString sFilter;

	if (m_bCheckBoxChecked)
	{
		sFilter.Format("IDPaziente = %li AND IDEsame <> %li",
			m_pEsamiView->m_pEsamiSet->m_lPaziente,
			m_pEsamiView->m_pEsamiSet->m_lContatore);

		m_bCheckBoxChecked = FALSE;
	}
	else
	{

		sFilter.Format("IDPaziente = %li AND IDEsame <> %li AND TipoEsame = '%s'",
			m_pEsamiView->m_pEsamiSet->m_lPaziente,
			m_pEsamiView->m_pEsamiSet->m_lContatore,
			CTipoEsameSet().GetDescrizione(m_pEsamiView->m_pEsamiSet->m_lIDEsame));

		m_bCheckBoxChecked = TRUE;
	}

	m_setVistaRefertiPaziente.SetOpenFilter(sFilter);
	if (m_setVistaRefertiPaziente.OpenRecordset("CRefertoExDlg::OnBnClickedCheck1"))
	{
		while (!m_setVistaRefertiPaziente.IsEOF())
		{
			m_lNumRefertiAct++;
			m_lNumRefertiTot++;

			m_setVistaRefertiPaziente.MoveNext();
		}
	}

	if (m_lNumRefertiTot > 0)
	{
		m_setVistaRefertiPaziente.MoveLast();
		CaricaTestoAltroReferto();

		if (m_lNumRefertiTot > 1)
			m_ctrlBtnPrev.EnableWindow(TRUE);
		else
		{
			m_ctrlBtnNext.EnableWindow(FALSE);
			m_ctrlBtnPrev.EnableWindow(FALSE);
		}
	}

	return;
}

// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
void CRefertoExDlg::AddRTFAnamnese(CString sRTF)
{
	if (sRTF.IsEmpty())
		return;

	m_ctrlTextTabAnamnesi.SetSelStart(-1);
	m_ctrlTextTabAnamnesi.SetSelLength(0);
	m_ctrlTextTabAnamnesi.SetRTFSelText(sRTF);

	m_ctrlTextTabAnamnesi.SetSelStart(-1);
	m_ctrlTextTabAnamnesi.SetSelLength(0);
	m_ctrlTextTabAnamnesi.SetRTFSelText(_RTFLINESEPARATOR);

	return;
}

void CRefertoExDlg::AddTXTAnamnese(CString sTXT)
{
	if (sTXT.IsEmpty())
		return;

	m_ctrlTextTabAnamnesi.SetSelStart(-1);
	m_ctrlTextTabAnamnesi.SetSelLength(0);
	m_ctrlTextTabAnamnesi.SetSelText(sTXT);

	return;
}

// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnese)
BOOL CRefertoExDlg::CaricaTestoAnamnesi(BOOL bLogSteps)
{
	if (theApp.m_sTabAnamnesiInReferto.IsEmpty()) //Possibilidade de desabilitar a aba completamente na UO
	{
		return FALSE;
		if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("Sistema configurado para não exibir anamnesi nesta UO");
	}

	BOOL bSomethingToShow = FALSE;

	m_ctrlTextTabAnamnesi.ResetContents();

	CString  sConfigAnamnesi = theApp.m_sTabAnamnesiInReferto;
	sConfigAnamnesi.MakeUpper();
	if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("Config --> " + sConfigAnamnesi);

	//Titulo da anamnsesi do paciente
	CString sTitleAnamnesiPaciente = "ANAMNESI DO PACIENTE";
	int iTitleStartPos = theApp.m_sTabAnamnesiInReferto.Find("{");
	int iTitleEndPos = theApp.m_sTabAnamnesiInReferto.Find("}");

	if (iTitleStartPos > 0 && iTitleEndPos  > 0 && iTitleEndPos > iTitleStartPos)
		sTitleAnamnesiPaciente = theApp.m_sTabAnamnesiInReferto.Mid(iTitleStartPos, (iTitleEndPos - iTitleStartPos) - 1);

	if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("Title --> " + sTitleAnamnesiPaciente);
	//

	// ELABORA UM RTF DA ANAMNESE DA ABA DO PACIENTE (Form CAbitudiniDynForm) 
	//--------------------------------------------------------------------------------------------------------
	if (sConfigAnamnesi.Find("PAZIENTE") >= 0) // IF FOUND IN CONFIG
	{
		if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> Start");

		int iAnamneseFilled = 0; // indica quantos campos estão preenchidos

		CString strNum;
		CString strHeader, strBody, strTrailer, strAux;

		strHeader =  _T("{\\rtf1\\ansi\\ansicpg1252\\deff0\\nouicompat\\deflang1046\\deflangfe1046\\deftab1134{ \\fonttbl{ \\f0\\fswiss\\fprq2\\fcharset0 \\\\panose 020B0604030504040204Tah; } }");
		strHeader += _T("{\\*\\generator Riched20 10.0.18362}{\\*\\mmathPr\\mnaryLim0\\mdispDef1\\mwrapIndent1440 }\\viewkind4\\uc1");
		strHeader += _T("\\pard\\nowidctlpar\\ul\\b\\f0\\fs24 ");
		strHeader += sTitleAnamnesiPaciente;	//ANAMNESE DO PACIENTE (TÍTULO CONFIGURAZIONE)
		strHeader += _T("\\par");
		strHeader += _T("\\pard\\nowidctlpar\\qc\\ulnone\\par");
		strHeader += _T("\\pard\\nowidctlpar ");

		strBody = "";

		int i = 1;

		if (theApp.m_bAnamVisi[0]) { // LABEL: fumo
			strNum.Format("\n%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[0];
			strAux += ": ";
			strAux += CComboBoxSet(CMB_ANA_FUMO).GetFieldText(m_pEsamiSet->m_lFumo); // traduz codigo p/ descrição
			iAnamneseFilled += (m_pEsamiSet->m_lFumo >= 0);
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> fumo");
		}

		if (theApp.m_bAnamVisi[1]) { // LABEL: sigarette
			strNum.Format("%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[1];
			strAux += ": ";
			strAux += CComboBoxSet(CMB_ANA_SIGA).GetFieldText(m_pEsamiSet->m_lSigarette); // traduz codigo p/ descrição
			iAnamneseFilled += (m_pEsamiSet->m_lSigarette >= 0);
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> sigarette");
		}

		if (theApp.m_bAnamVisi[2]) { // LABEL: caffè
			strNum.Format("%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[2];
			strAux += ": ";
			strAux += CComboBoxSet(CMB_ANA_CAFF).GetFieldText(m_pEsamiSet->m_lCaffe); // traduz codigo p/ descrição
			iAnamneseFilled += (m_pEsamiSet->m_lCaffe >= 0);
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> caffè");
		}

		if (theApp.m_bAnamVisi[3]) { // LABEL: alcool
			strNum.Format("%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[3];
			strAux += ": ";
			strAux += CComboBoxSet(CMB_ANA_ALCO).GetFieldText(m_pEsamiSet->m_lAlcool); // traduz codigo p/ descrição
			iAnamneseFilled += (m_pEsamiSet->m_lAlcool >= 0);
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> alcool");
		}

		if (theApp.m_bAnamVisi[4]) { // LABEL: superalcolici
			strNum.Format("%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[4];
			strAux += ": ";
			strAux += CComboBoxSet(CMB_ANA_SUPE).GetFieldText(m_pEsamiSet->m_lSuperAlcolici); // traduz codigo p/ descrição
			iAnamneseFilled += (m_pEsamiSet->m_lSuperAlcolici >= 0);
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> superalcolici");
		}

		if (theApp.m_bAnamVisi[5]) { // LABEL: farmaci
			strNum.Format("%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[5];
			strAux += ": ";
			strAux += m_pEsamiSet->m_sDenFarmaci;
			iAnamneseFilled += (!m_pEsamiSet->m_sDenFarmaci.IsEmpty());
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> farmaci");
		}

		if (theApp.m_bAnamVisi[6]) { // LABEL: assunzione
			strNum.Format("%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[6];
			strAux += ": ";
			strAux += CComboBoxSet(CMB_ANA_ASSU).GetFieldText(m_pEsamiSet->m_lAssunzione);		// traduz codigo p/ descrição
			iAnamneseFilled += (m_pEsamiSet->m_lAssunzione >= 0);
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> assunzione");
		}

		if (theApp.m_bAnamVisi[7]) { // LABEL: peso
			strNum.Format("%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[7];
			strAux += ": ";
			strNum.Format(" %.2f ", m_pEsamiView->m_pEsamiSet->m_fPeso);
			strAux += strNum;
			iAnamneseFilled += (m_pEsamiSet->m_fPeso > 0);
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> peso");
		}

		if (theApp.m_bAnamVisi[8]) { // LABEL: altezza
			strNum.Format("%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[8];
			strAux += ": ";
			strNum.Format(" %.2f ", m_pEsamiView->m_pEsamiSet->m_fAltezza);
			strAux += strNum;
			iAnamneseFilled += (m_pEsamiSet->m_fAltezza > 0);
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> altezza");
		}

		if (theApp.m_bAnamVisi[9]) { // LABEL: BMI
			strNum.Format("%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[9];
			strAux += ": ";
			strNum.Format(" %.2f ", m_pEsamiView->m_pEsamiSet->m_fBMI);
			strAux += strNum;
			iAnamneseFilled += (m_pEsamiSet->m_fBMI > 0);
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> bmi");
		}

		if (theApp.m_bAnamVisi[10]) { // LABEL: BSA
			strNum.Format("%d) ", i++);
			strAux += strNum;
			strAux += theApp.m_sAnamText[10];
			strAux += ": ";
			strNum.Format(" %.2f ", m_pEsamiView->m_pEsamiSet->m_fBSA);
			strAux += strNum;
			iAnamneseFilled += (m_pEsamiSet->m_fBSA > 0);
			strAux += "\\b\\par\n\\par\n";
			strBody += strAux; strAux = "";
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> bsa");
		}

		if (iAnamneseFilled > 0)
		{
			if (bLogSteps)
			{
				CString sCount;
				sCount.Format("iAnamneseFilled: %li", iAnamneseFilled);
				CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> " + sCount);
			}

			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> Add RTF Start");
			AddRTFAnamnese(strHeader + strBody + strTrailer);
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> Add RTF Finish");

			bSomethingToShow = TRUE;
		}

		if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("PAZIENTE --> Finish");
	}

	//Textos das etiquetas personalizadas

	if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Start");
	BOOL bAddEtichette[20] = { 0 };

	int iPos = 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF000") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF001") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF002") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF003") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF004") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF005") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF006") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF007") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF008") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF009") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF010") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF011") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF012") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF013") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF014") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF015") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF016") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF017") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF018") >= 0;
	bAddEtichette[iPos++] = sConfigAnamnesi.Find("TESTORTF019") >= 0;

	BOOL bWantSomething = FALSE;
	for (int i = 0; i < iPos; i++)
	{
		if (bAddEtichette[i])
		{
			if (bLogSteps)
			{
				CString sPos;
				sPos.Format("TESTO-RTF-%li", i);
				CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> " + sPos);
			}
			bWantSomething = TRUE;
			iPos = 0;
		}
	}

	// valida se vazio
	if (iPos == 0)
	{
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf000.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-000 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf000);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-000 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf001.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-001 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf001);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-001 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf002.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-002 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf002);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-002 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf003.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-003 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf003);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-003 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf004.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-004 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf004);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-004 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf005.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-005 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf005);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-005 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf006.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-006 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf006);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-006 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf007.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-007 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf007);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-007 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf008.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-008 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf008);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-008 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf009.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-009 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf009);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-009 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf010.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-010 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf010);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-010 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf011.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-011 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf011);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-011 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf012.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-012 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf012);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-012 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf013.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-013 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf013);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-013 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf014.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-014 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf014);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-014 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf015.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-015 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf015);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-015 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf016.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-016 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf016);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-016 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf017.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-017 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf017);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-017 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf018.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-018 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf018);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-018 Finish");
		}
		if (bAddEtichette[iPos++] && !m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf019.IsEmpty())
		{
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-019 Start");
			AddRTFAnamnese(m_pEsamiView->m_pEsamiSet->m_setEP.m_sTestoRtf019);
			bSomethingToShow = TRUE;
			if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Add RTF-019 Finish");
		}
	}
	if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("ETIQUETAS --> Finish");

	// há configuração para apresentar anamnesi vindo pelo TESTOTXT000..TESTOTXT019 mas o conteúdo recebido está vazio
	if (bWantSomething && !bSomethingToShow)
	{
		CString strRtfAnamneseNotDefined = "ANAMNESI NÃO RECEBIDA OU RECEBIDA EM BRANCO.";

		if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("VAZIO --> Add TXT Start");
		AddTXTAnamnese(strRtfAnamneseNotDefined);
		if (bLogSteps) CLogFileWriter::Get()->WriteLogLine0("VAZIO --> Add TXT Finish");

		bSomethingToShow = TRUE;
	}

	return bSomethingToShow;
}

void  CRefertoExDlg::CaricaTestoReferences()
{
	CStdioFile fileStream;
	CFileException fileException;

	CString sFilePath = _T(theApp.m_sPathValoresReferencia);
	CString sLine = "";
	CString sRtf = "";
	// Luiz - 17/07/2019 - P3 - Desbloqueia scroll na aba valores de referencia
	m_ctrlTextReferences.EnableWindow(TRUE);
	m_ctrlTextReferences.ResetContents();

	try
	{
		if (fileStream.Open(sFilePath, CFile::modeRead, &fileException))
		{
			while (fileStream.ReadString(sLine))
			{
				sRtf += sLine;
			}
			fileStream.Close();
		}
	}
	catch (const std::exception& ex)
	{
		CString strError;
		strError.Format("ERRO \n %s", ex.what());
		theApp.AfxMessageBoxEndo(strError);

		sRtf = "";
	}

	m_ctrlTextReferences.SetRTFSelText(sRtf);
}


//Julio BUG 3457 - Texter
LRESULT CRefertoExDlg::OnKeyboardPress(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_F3:
	case VK_TAB:
	{
		CWnd* pFocusWnd = GetFocus();
		if (pFocusWnd && pFocusWnd->IsKindOf(RUNTIME_CLASS(CTXTextControl23Ex)))
			if (pFocusWnd->GetDlgCtrlID() == IDC_TEXTCONTROL)
			{
				int iSelStart = m_ctrlText.GetSelStart();
				int iSelLength = m_ctrlText.GetSelLength();

				int iStartSearch = iSelStart + iSelLength;
				if (iStartSearch <= 0)
					return 0;

				m_ctrlText.SetRedraw(FALSE);

				CString strWord;
				while (--iStartSearch >= 0 && (strWord.GetLength() == 0 || (strWord.GetAt(0) != ' ' && strWord.GetAt(0) != '\n')))
				{
					m_ctrlText.SetSelStart(iStartSearch);
					m_ctrlText.SetSelLength(1);
					strWord = m_ctrlText.GetSelText() + strWord;
				}

				if (strWord.GetAt(0) == ' ' || strWord.GetAt(0) == '\n')
					strWord = strWord.Right(strWord.GetLength() - 1);

				if (strWord.GetLength() >= 2)
				{
					m_ctrlText.SetSelStart(iSelStart - iSelLength - strWord.GetLength());
					m_ctrlText.SetSelLength(strWord.GetLength());

					SearchAndReplaceTexterPhrase(strWord.Trim());	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
				}

				m_ctrlText.SetRedraw(TRUE);
				m_ctrlText.RedrawWindow();

				return 0;
			}
		break;
	}
	}
	return 0;

}


// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CRefertoExDlg::ApplyTexterPhrase(long p_lIDFrase)
{
	CString sFraseRtf = CFrasiRtfSet().GetTestoRtf(p_lIDFrase);
	CString sFraseTxt = CFrasiRtfSet().GetTestoTxt(p_lIDFrase);

	if (!sFraseRtf.IsEmpty())
	{
		try
		{
			if (theApp.m_bUsaTexterAsRTF)
			{
				CString sFraseRtfCleaned = cleanFinalDoubleParInRTF(sFraseRtf);
				m_ctrlText.SetRTFSelText(sFraseRtfCleaned); //quando insiro o texto como rtf o TX Text Control sempre coloca um enter no final do texto
				// remove um ENTER extra que a função SetRTFSelText adiciona indevidamente
				pressKey(VK_BACK);  // BACKSPACE key
			}
			else
			{
				m_ctrlText.SetSelText(sFraseTxt);
			}
		}
		catch (CException* e)
		{
			TCHAR szError[255];
			e->GetErrorMessage(szError, 255);
			e->Delete();
		}
	}
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CRefertoExDlg::SearchAndReplaceTexterPhrase(CString sFrase)
{
	BeginWaitCursor();

	long lIDFrase = CFrasiRtfSet().GetIDByCodice(sFrase);
	if (lIDFrase > 0)
	{
		ApplyTexterPhrase(lIDFrase);
	}
	else
	{
		m_ctrlText.SetSelStart(m_ctrlText.GetSelStart() + m_ctrlText.GetSelLength());
		m_ctrlText.SetSelLength(0);
	}

	EndWaitCursor();
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CRefertoExDlg::OnEnSetfocusEditRtfCodice()
{
	cleanEditToStart();
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CRefertoExDlg::OnEnSetfocusEditRtfFrase()
{
	cleanEditToStart();
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
void CRefertoExDlg::cleanEditToStart()
{
	CString strFrase, strCodice;
	m_ctrlEditRtfFrase.GetWindowText(strFrase);
	m_ctrlEditRtfCodice.GetWindowText(strCodice);

	if (strFrase == _T("pesquisar...") || strFrase == _T("pesquisar...")) {
		m_bProcessOnEnChange = FALSE;
		m_ctrlEditRtfFrase.SetWindowText(_T(""));
		m_ctrlEditRtfCodice.SetWindowText(_T(""));
		m_bProcessOnEnChange = TRUE;
	}
}


//Julio - correcao lista biometria
void CRefertoExDlg::SaveEditedMeasurement()
{
	if (!m_bMeasurementUpdated)
		return;

	Recalculate();

	for (int i = 0; i < m_ctrlListMeasurements.GetItemCount(); i++)
	{
		CString sNumericValue = m_ctrlListMeasurements.GetItemText(i, 2);
		CString sCodeValue = m_ctrlListMeasurements.GetItemText(i, 3);
		CString sAlias = m_ctrlListMeasurements.GetItemText(i, 0);

		long lID = m_ctrlListMeasurements.GetItemData(i); //id da tabela measurements	

		//Gabriel BUG 5533
		//MOTILIDADE PROGRESSIVA
		if (sAlias == "ESP PROGRES PR"){
			//CheckVitalityMeasurement(sNumericValue);
			m_sMotilidadeProgressiva = sNumericValue;
		}
		//CONCENTRAÇÃO
		if (sAlias == "CONCENTRACAO TOTAL DA AMOSTRA")
		{
			m_sConcentracao = sNumericValue;
		}
		//MORFOLOGIA
		if (sAlias == "MORF ESTRITA")
		{
			m_sMorfologia = sNumericValue;
		}

		if (lID == -1 &&  //Quer dizer que o exame atual nao tem essa medida ainda
			!(sNumericValue.Trim().IsEmpty() && sCodeValue.Trim().IsEmpty())) //Me certifico de que existe um valor para a medida antes de adiciona-la ao banco
		{
			CMeasurementsSet().AddRow(m_pEsamiSet->m_lContatore, sAlias, sNumericValue, sCodeValue, AMLogin_GetUsername());
		}
		else if (sNumericValue.Trim().IsEmpty() && sCodeValue.Trim().IsEmpty()) //Se a medida esta em branco removo ela deste exame
		{
			CMeasurementsSet().DelRow(lID);
		}
		else //Edicao do valor da medida
		{
			CMeasurementsSet().UpdateExamMeasurement(lID, sNumericValue, sCodeValue);
		}
	}
	m_bMeasurementUpdated = FALSE;
	m_bSpermChartMeasurementUpdated = FALSE;//Gabriel BUG 5533
	RiempiListaMeasurements();
}

//Gabriel BUG 5533
void CRefertoExDlg::CheckVitalityMeasurement(CString sNumericValue)
{
	m_bSpermMeasurementVitalityAllowEdit = (float)atof(sNumericValue) >= 32 ? FALSE : TRUE;
}

//Gabriel BUG 5533
BOOL CRefertoExDlg::CheckVitalityClosure()
{
	CString sVitality;
	float fMeasurement;
	for (int i = 0; i < m_ctrlListMeasurements.GetItemCount(); i++)
	{
		CString sNumericValue = m_ctrlListMeasurements.GetItemText(i, 2);
		CString sAlias = m_ctrlListMeasurements.GetItemText(i, 0);

		if (sAlias == "ESP PROGRES PR")
		{
			fMeasurement = (float)atof(sNumericValue);
		}
		else if (sAlias == "VITALIDADE")
		{
			sVitality = sNumericValue;
		}
	}

	if (fMeasurement >= 32)
		return TRUE;
	else if (!sVitality.Trim().IsEmpty())
		return TRUE;
	else
		return FALSE;
}

//Gabriel BUG 5533
BOOL CRefertoExDlg::IsSpermExam()
{
	CList<CString> sSiglasList;
	CString str = _T(theApp.m_sSpermaEsameSiglePerGenerazioneGrafici);

	int nTokenPos = 0;
	CString strToken = str.Tokenize(_T(";"), nTokenPos);

	while (!strToken.IsEmpty())
	{
		sSiglasList.AddTail(strToken);
		strToken = str.Tokenize(_T(";"), nTokenPos);
	}

	CString sSiglaEsame;

	for (int i = 0; i < sSiglasList.GetCount(); i++)
	{
		if (sSiglasList.GetAt(sSiglasList.FindIndex(i)) == m_pEsamiView->GetSiglaPrestazione())
		{
			return TRUE;
			break;
		}
	}

	return FALSE;
}

void CRefertoExDlg::OnItemChangedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (/*(pNMListView->uChanged & LVIF_STATE) || */(pNMListView->uOldState & LVNI_SELECTED)/* || (pNMListView->uNewState != pNMListView->uOldState)*/)
	{
		Recalculate();
	}
}

void CRefertoExDlg::CalculateMeasurements(long lItem, float fMeasurement2, float fMeasurement3, float fMeasurement4, float fValue1, long lIDCalc, long lMeasurement)
{
	if (theApp.m_bAtivaEspermograma)
	{
		float fNewValue = 0;

		switch (lIDCalc)
		{
		case 1:
		{
			fNewValue = fMeasurement2 + fMeasurement3;
			break;
		}
		case 2:
		{
			fNewValue = fMeasurement2 - fMeasurement3;
			break;
		}
		case 3:
		{
			fNewValue = fMeasurement2 * fMeasurement3;
			break;
		}
		case 4:
		{
			fNewValue = fMeasurement2 / fMeasurement3;
			break;
		}
		case 5:
		{
			fNewValue = (fMeasurement2 + fMeasurement3) / fMeasurement4;
			break;
		}
		case 6:
		{
			fNewValue = (fMeasurement2 + fMeasurement3) / fValue1;
			break;
		}
		case 7:
		{
			fNewValue = (fMeasurement2 * fMeasurement3) / fMeasurement4;
			break;
		}
		case 8:
		{
			fNewValue = (fMeasurement2 * fMeasurement3) / fValue1;
			break;
		}
		}
		//Gabriel - BUG 5533 V2
		CString sNewValue, sOldValue;
		sOldValue = m_ctrlListMeasurements.GetItemText(lItem, 2);

		sNewValue = FormatNumber(lMeasurement, sOldValue, fNewValue);
		m_ctrlListMeasurements.SetItemText(lItem, 2, sNewValue);
	}
}

void CRefertoExDlg::Recalculate()
{
	if (theApp.m_bAtivaEspermograma)
	{
		for (int i = 0; i < m_ctrlListMeasurements.GetItemCount(); i++)
		{
			long lItemID = i;
			long lID = atol(m_ctrlListMeasurements.GetItemText(i, 5));

			if (m_listCalcId.Find(lID) != NULL)
			{
				POSITION pos = m_listCalc.GetHeadPosition();
				while (pos != NULL)
				{
					tagFIELDCALC tagCalc = m_listCalc.GetAt(pos);
					if (tagCalc.lMeasurement1 == lID)
					{
						long lIDCalc = tagCalc.lIDCalc;
						long lMeasurement2 = tagCalc.lMeasurement2;
						long lMeasurement3 = tagCalc.lMeasurement3;
						long lMeasurement4 = 0;
						float fValue1 = 1;
						if (lIDCalc == 5 || lIDCalc == 7)
							lMeasurement4 = tagCalc.lMeasurement4;
						if (lIDCalc == 6 || lIDCalc == 8)
							fValue1 = tagCalc.fValue1;

						float fMeasurement2Value, fMeasurement3Value, fMeasurement4Value;

						for (int i = 0; i < m_ctrlListMeasurements.GetItemCount(); i++)
						{
							long lIDMeasurement = atol(m_ctrlListMeasurements.GetItemText(i, 5));
							if (lIDMeasurement == lMeasurement2)
							{
								CString sValue = m_ctrlListMeasurements.GetItemText(i, 2);
								sValue.Replace(",", "."); // 5533 Vitor Ávila
								fMeasurement2Value = (float)atof(sValue);
							}
							if (lIDMeasurement == lMeasurement3)
							{
								CString sValue = m_ctrlListMeasurements.GetItemText(i, 2);
								sValue.Replace(",", "."); //Vitor Vitor Ávila
								fMeasurement3Value = (float)atof(sValue);
							}
							if (lIDMeasurement == lMeasurement4 && (lIDCalc == 5 || lIDCalc == 7))
							{
								CString sValue = m_ctrlListMeasurements.GetItemText(i, 2);
								fMeasurement4Value = (float)atof(sValue);
							}
						}

						CalculateMeasurements(lItemID, fMeasurement2Value, fMeasurement3Value, fMeasurement4Value, fValue1, lIDCalc, lID);
					}

					m_listCalc.GetNext(pos);
				}
			}
		}
	}
}

BOOL CRefertoExDlg::CanEdit(long lIDMeasurement)
{
	if (theApp.m_bAtivaEspermograma)
	{
		BOOL bReturn = FALSE;
		BOOL bCanEdit = TRUE;

		if (m_listRulesId.Find(lIDMeasurement) != NULL)
		{
			POSITION pos = m_listRules.GetHeadPosition();
			while (pos != NULL)
			{
				tagFIELDRULE tagRules = m_listRules.GetAt(pos);
				if (tagRules.lMeasurementRule == lIDMeasurement && tagRules.lIDRule == 2)
				{
					long lIDMeasurementCondition = tagRules.lMeasurementCondition;
					CString sValue1 = tagRules.szValueCondition1;
					CString sValue2 = tagRules.szValueCondition2;
					CString sValueMeasurement;

					for (int i = 0; i < m_ctrlListMeasurements.GetItemCount(); i++)
					{
						long lID = atol(m_ctrlListMeasurements.GetItemText(i, 5));


						if (lIDMeasurementCondition == lID)
						{
							sValueMeasurement = m_ctrlListMeasurements.GetItemText(i, 2);
						}
					}

					switch (tagRules.lIDCondition)
					{
					case 1:
					{
						if (sValue1 == sValueMeasurement)
							bCanEdit = FALSE;
						break;
					}
					case 2:
					{
						if (sValue1 != sValueMeasurement)
							bCanEdit = FALSE;
						break;
					}
					case 3:
					{
						if ((float)atof(sValueMeasurement) > (float)atof(sValue1))
							bCanEdit = FALSE;
						break;
					}
					case 4:
					{
						if ((float)atof(sValueMeasurement) < (float)atof(sValue1))
							bCanEdit = FALSE;
						break;
					}
					case 5:
					{
						if ((float)atof(sValueMeasurement) >= (float)atof(sValue1))
							bCanEdit = FALSE;
						break;
					}
					case 6:
					{
						if ((float)atof(sValueMeasurement) <= (float)atof(sValue1))
							bCanEdit = FALSE;
						break;
					}
					case 7:
					{
						if (sValueMeasurement.IsEmpty())
							bCanEdit = FALSE;
						break;
					}
					case 8:
					{
						if (!sValueMeasurement.IsEmpty())
							bCanEdit = FALSE;
						break;
					}
					case 9:
					{
						if ((float)atof(sValueMeasurement) >= (float)atof(sValue1) && (float)atof(sValueMeasurement) <= (float)atof(sValue2))
							bCanEdit = FALSE;
						break;
					}
					}
				}

				m_listRules.GetNext(pos);
			}
		}

		if (bCanEdit) bReturn = TRUE;
		return bReturn;
	}
	else
		return TRUE;
}

BOOL CRefertoExDlg::CanClose()
{
	if (theApp.m_bAtivaEspermograma)
	{
		BOOL bReturn = FALSE;
		BOOL bCanClose = TRUE;
		CString sMeasurementAlias;

		POSITION pos = m_listRules.GetHeadPosition();
		while (pos != NULL)
		{
			tagFIELDRULE tagRules = m_listRules.GetAt(pos);
			if (tagRules.lIDRule == 1)
			{
				long lIDMeasurementCondition = tagRules.lMeasurementCondition;
				long lIDMeasurementRule = tagRules.lMeasurementRule;
				CString sValue1 = tagRules.szValueCondition1;
				CString sValue2 = tagRules.szValueCondition2;
				CString sValueMeasurementCondition, sValueMeasurementRule;

				for (int i = 0; i < m_ctrlListMeasurements.GetItemCount(); i++)
				{
					long lID = atol(m_ctrlListMeasurements.GetItemText(i, 5));

					if (lIDMeasurementCondition == lID)
						sValueMeasurementCondition = m_ctrlListMeasurements.GetItemText(i, 2);
					if (lIDMeasurementRule == lID)
						sValueMeasurementRule = m_ctrlListMeasurements.GetItemText(i, 2);
				}

				switch (tagRules.lIDCondition)
				{
				case 1:
				{
					if (sValue1 == sValueMeasurementCondition && sValueMeasurementRule.Trim().IsEmpty())
					{
						bCanClose = FALSE;
						sMeasurementAlias = CMeasurementsAliasMappingSet().GetAlias(lIDMeasurementRule);
					}
					break;
				}
				case 2:
				{
					if (sValue1 != sValueMeasurementCondition && sValueMeasurementRule.Trim().IsEmpty())
					{
						bCanClose = FALSE;
						sMeasurementAlias = CMeasurementsAliasMappingSet().GetAlias(lIDMeasurementRule);
					}
					break;
				}
				case 3:
				{
					if ((float)atof(sValueMeasurementCondition) > (float)atof(sValue1) && sValueMeasurementRule.Trim().IsEmpty())
					{
						bCanClose = FALSE;
						sMeasurementAlias = CMeasurementsAliasMappingSet().GetAlias(lIDMeasurementRule);
					}
					break;
				}
				case 4:
				{
					if ((float)atof(sValueMeasurementCondition) < (float)atof(sValue1) && sValueMeasurementRule.Trim().IsEmpty())
					{
						bCanClose = FALSE;
						sMeasurementAlias = CMeasurementsAliasMappingSet().GetAlias(lIDMeasurementRule);
					}
					break;
				}
				case 5:
				{
					if ((float)atof(sValueMeasurementCondition) >= (float)atof(sValue1) && sValueMeasurementRule.Trim().IsEmpty())
					{
						bCanClose = FALSE;
						sMeasurementAlias = CMeasurementsAliasMappingSet().GetAlias(lIDMeasurementRule);
					}
					break;
				}
				case 6:
				{
					if ((float)atof(sValueMeasurementCondition) <= (float)atof(sValue1) && sValueMeasurementRule.Trim().IsEmpty())
					{
						bCanClose = FALSE;
						sMeasurementAlias = CMeasurementsAliasMappingSet().GetAlias(lIDMeasurementRule);
					}
					break;
				}
				case 7:
				{
					if (sValueMeasurementCondition.IsEmpty() && sValueMeasurementRule.Trim().IsEmpty())
					{
						bCanClose = FALSE;
						sMeasurementAlias = CMeasurementsAliasMappingSet().GetAlias(lIDMeasurementRule);
					}
					break;
				}
				case 8:
				{
					if (!sValueMeasurementCondition.IsEmpty() && sValueMeasurementRule.Trim().IsEmpty())
					{
						bCanClose = FALSE;
						sMeasurementAlias = CMeasurementsAliasMappingSet().GetAlias(lIDMeasurementRule);
					}
					break;
				}
				case 9:
				{
					if ((float)atof(sValueMeasurementCondition) >= (float)atof(sValue1) && (float)atof(sValueMeasurementCondition) <= (float)atof(sValue2) && sValueMeasurementRule.Trim().IsEmpty())
					{
						bCanClose = FALSE;
						sMeasurementAlias = CMeasurementsAliasMappingSet().GetAlias(lIDMeasurementRule);
					}
					break;
				}
				}
			}

			m_listRules.GetNext(pos);
		}

		if (bCanClose)
			bReturn = TRUE;
		else
		{
			CString sMessage;
			sMessage.Format(theApp.GetMessageString(IDS_MEASUREMENTS_OBBLIGATORYFIELDS), sMeasurementAlias);
			theApp.AfxMessageBoxEndo(sMessage);
		}

		return bReturn;
	}
	else
		return TRUE;
}

CString CRefertoExDlg::FormatNumber(long lMeasurement, CString sValue, float fValue)
{
	CString sReturn = sValue;

	sValue.Replace(",", ".");
	long lDecimals = CMeasurementsAliasMappingSet().GetDecimals(lMeasurement);
	switch (lDecimals)
	{
	case 0:
		sReturn.Format("%.0f", fValue);
		break;
	case 1:
		sReturn.Format("%.1f", fValue);
		break;
	case 2:
		sReturn.Format("%.2f", fValue);
		break;
	case 3:
		sReturn.Format("%.3f", fValue);
		break;
	case 4:
		sReturn.Format("%.4f", fValue);
		break;
	}

	sReturn.Replace(".", ",");
	
	return sReturn;
}