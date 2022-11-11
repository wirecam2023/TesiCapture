#include "stdafx.h"
#include "Endox.h"
#include "MielogrammaDynForm.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMielogrammaDynForm::CMielogrammaDynForm(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxDynForm(CMielogrammaDynForm::IDD, pParent, pEsamiView)
{
}

CMielogrammaDynForm::~CMielogrammaDynForm(void)
{
}

BEGIN_MESSAGE_MAP(CMielogrammaDynForm, CEndoxDynForm)

	// ON_WM_CTLCOLOR()

	ON_MESSAGE(WM_USER + 0xabc, UpdateContagem)

	ON_WM_SIZE()

END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CMielogrammaDynForm, CEndoxDynForm)

	ON_EVENT(CMielogrammaDynForm, IDC_MEASURE_SHEET, DISPID_KEYDOWN, OnSpreadsheetKeyDown, VTS_PI2 VTS_I2)
	ON_EVENT(CMielogrammaDynForm, IDC_MEASURE_SHEET, 6, OnSpreadsheetEndEditCell, VTS_PBSTR VTS_PI2)

END_EVENTSINK_MAP()

void CMielogrammaDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_mielogramma] == NULL)
	{
		pEsamiView->m_pDynForm[sub_mielogramma] = new CMielogrammaDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_mielogramma] != NULL)
		{
			pEsamiView->m_pDynForm[sub_mielogramma]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_mielogramma]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_mielogramma]->m_lIDFaseBlocco = lIDFaseBlocco;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_mielogramma]->CreateChildForm(CMielogrammaDynForm::IDD, pParent, rectFrame);
		}
	}
}

void CMielogrammaDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MEASURE_SHEET, m_ctrlSpreadsheet);
}

HBRUSH CMielogrammaDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	/*
	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_ANAM_6:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}
		case IDC_SUAB_00:
		case IDC_ANAM_1:
		case IDC_BMI_1:
		case IDC_BMI_2:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}
	*/

	return hReturn;
}

BOOL CMielogrammaDynForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_PLACE, CSize(0, 0), CSize(100, 100));

	InitSpreadsheet();

	theApp.LocalizeDialog(this, CMielogrammaDynForm::IDD, "MielogrammaDynForm");
	return TRUE;
}

void CMielogrammaDynForm::OnSize(UINT nType, int cx, int cy)
{
	CEndoxDynForm::OnSize(nType, cx, cy);
	ResizeSpreadsheet();
}

LRESULT CMielogrammaDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CMielogrammaDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	m_ctrlSpreadsheet.put_NumberRC(2, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lCELULASACONTAR);

	m_ctrlSpreadsheet.put_NumberRC(5, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lHISTIOCITOS);
	m_ctrlSpreadsheet.put_NumberRC(6, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lMACROFAGOS);
	m_ctrlSpreadsheet.put_NumberRC(7, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lMASTOCITOS);

	m_ctrlSpreadsheet.put_NumberRC(11, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lNPROM);
	m_ctrlSpreadsheet.put_NumberRC(12, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lNMIEL);
	m_ctrlSpreadsheet.put_NumberRC(13, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lNMETAM);
	m_ctrlSpreadsheet.put_NumberRC(14, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lNBAST);
	m_ctrlSpreadsheet.put_NumberRC(15, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lNSEGM);

	m_ctrlSpreadsheet.put_NumberRC(20, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lPROERITRO);
	m_ctrlSpreadsheet.put_NumberRC(21, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lERITROBASO);
	m_ctrlSpreadsheet.put_NumberRC(22, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lERITPOLICRO);
	m_ctrlSpreadsheet.put_NumberRC(23, 3, m_pEsamiView->m_pEsamiSet->m_setEM.m_lERITROORTO);

	m_ctrlSpreadsheet.put_NumberRC(5, 7, m_pEsamiView->m_pEsamiSet->m_setEM.m_lBLASTOS);
	m_ctrlSpreadsheet.put_NumberRC(6, 7, m_pEsamiView->m_pEsamiSet->m_setEM.m_lOUTROS);

	m_ctrlSpreadsheet.put_NumberRC(11, 7, m_pEsamiView->m_pEsamiSet->m_setEM.m_lEPROM);
	m_ctrlSpreadsheet.put_NumberRC(12, 7, m_pEsamiView->m_pEsamiSet->m_setEM.m_lEMIEL);
	m_ctrlSpreadsheet.put_NumberRC(13, 7, m_pEsamiView->m_pEsamiSet->m_setEM.m_lEMETAM);
	m_ctrlSpreadsheet.put_NumberRC(14, 7, m_pEsamiView->m_pEsamiSet->m_setEM.m_lEBAST);
	m_ctrlSpreadsheet.put_NumberRC(15, 7, m_pEsamiView->m_pEsamiSet->m_setEM.m_lESEGM);

	m_ctrlSpreadsheet.put_NumberRC(20, 7, m_pEsamiView->m_pEsamiSet->m_setEM.m_lLINFOCITO);
	m_ctrlSpreadsheet.put_NumberRC(21, 7, m_pEsamiView->m_pEsamiSet->m_setEM.m_lMONOCITO);
	m_ctrlSpreadsheet.put_NumberRC(22, 7, m_pEsamiView->m_pEsamiSet->m_setEM.m_lPLASMOCITO);

	m_ctrlSpreadsheet.put_NumberRC(11, 11, m_pEsamiView->m_pEsamiSet->m_setEM.m_lBSEGM);

	m_ctrlSpreadsheet.put_TextRC(19, 11, m_pEsamiView->m_pEsamiSet->m_setEM.m_sMGC);

	m_ctrlSpreadsheet.SetSelection("F26");

	PostMessage(WM_USER + 0xabc); // m_ctrlSpreadsheet.put_TextRC(26, 6, "CONTAGEM OK"); // debug //
	return UpdateData(FALSE);
}

LRESULT CMielogrammaDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	m_ctrlSpreadsheet.EnableWindow(!(BOOL)wParam);
	return 1;
}

LRESULT CMielogrammaDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CMielogrammaDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	BOOL bUpdate = FALSE;

	if (m_pEsamiView->m_pEsamiSet->GetEditMode() == 0)
		bUpdate = m_pEsamiView->m_pEsamiSet->EditRecordset("CMielogrammaDynForm::OnFormSave");

	m_pEsamiView->m_pEsamiSet->m_setEM.m_lCELULASACONTAR = (int)m_ctrlSpreadsheet.get_NumberRC(2, 3);

	m_pEsamiView->m_pEsamiSet->m_setEM.m_lHISTIOCITOS = (int)m_ctrlSpreadsheet.get_NumberRC(5, 3);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lMACROFAGOS = (int)m_ctrlSpreadsheet.get_NumberRC(6, 3);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lMASTOCITOS = (int)m_ctrlSpreadsheet.get_NumberRC(7, 3);

	m_pEsamiView->m_pEsamiSet->m_setEM.m_lNPROM = (int)m_ctrlSpreadsheet.get_NumberRC(11, 3);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lNMIEL = (int)m_ctrlSpreadsheet.get_NumberRC(12, 3);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lNMETAM = (int)m_ctrlSpreadsheet.get_NumberRC(13, 3);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lNBAST = (int)m_ctrlSpreadsheet.get_NumberRC(14, 3);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lNSEGM = (int)m_ctrlSpreadsheet.get_NumberRC(15, 3);

	m_pEsamiView->m_pEsamiSet->m_setEM.m_lPROERITRO = (int)m_ctrlSpreadsheet.get_NumberRC(20, 3);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lERITROBASO = (int)m_ctrlSpreadsheet.get_NumberRC(21, 3);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lERITPOLICRO = (int)m_ctrlSpreadsheet.get_NumberRC(22, 3);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lERITROORTO = (int)m_ctrlSpreadsheet.get_NumberRC(23, 3);

	m_pEsamiView->m_pEsamiSet->m_setEM.m_lBLASTOS = (int)m_ctrlSpreadsheet.get_NumberRC(5, 7);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lOUTROS = (int)m_ctrlSpreadsheet.get_NumberRC(6, 7);

	m_pEsamiView->m_pEsamiSet->m_setEM.m_lEPROM = (int)m_ctrlSpreadsheet.get_NumberRC(11, 7);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lEMIEL = (int)m_ctrlSpreadsheet.get_NumberRC(12, 7);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lEMETAM = (int)m_ctrlSpreadsheet.get_NumberRC(13, 7);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lEBAST = (int)m_ctrlSpreadsheet.get_NumberRC(14, 7);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lESEGM = (int)m_ctrlSpreadsheet.get_NumberRC(15, 7);

	m_pEsamiView->m_pEsamiSet->m_setEM.m_lLINFOCITO = (int)m_ctrlSpreadsheet.get_NumberRC(20, 7);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lMONOCITO = (int)m_ctrlSpreadsheet.get_NumberRC(21, 7);
	m_pEsamiView->m_pEsamiSet->m_setEM.m_lPLASMOCITO = (int)m_ctrlSpreadsheet.get_NumberRC(22, 7);

	m_pEsamiView->m_pEsamiSet->m_setEM.m_lBSEGM = (int)m_ctrlSpreadsheet.get_NumberRC(11, 11);

	m_pEsamiView->m_pEsamiSet->m_setEM.m_sMGC = m_ctrlSpreadsheet.get_TextRC(19, 11);

	if (bUpdate)
		m_pEsamiView->m_pEsamiSet->UpdateRecordset("CMielogrammaDynForm::OnFormSave");

	return UpdateData(TRUE);
}

LRESULT CMielogrammaDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	return 1;
}

long CMielogrammaDynForm::GetContenuto()
{
	return sub_mielogramma;
}

BOOL CMielogrammaDynForm::CampoObbligatorioValido()
{
	return TRUE;
}

void CMielogrammaDynForm::OnSpreadsheetKeyDown(short* KeyCode, short Shift)
{
	long lRow, lCol;
	switch (*KeyCode)
	{
		//gestione tasto canc
	case VK_DELETE:
		m_ctrlSpreadsheet.EditClear(3);
		break;

		//gestione tasto tab
	case VK_TAB:
		m_ctrlSpreadsheet.GetActiveCell(&lRow, &lCol);
		if (m_ctrlSpreadsheet.get_EntrySRC(m_ctrlSpreadsheet.GetSheet(), lRow + 1, 1).IsEmpty())
			lRow = 0;
		m_ctrlSpreadsheet.SetActiveCell(lRow + 1, lCol - 1);
		break;

	default:
		break;
	}
}

void CMielogrammaDynForm::InitSpreadsheet()
{
	m_ctrlSpreadsheet.put_PaletteEntry(1, RGB(150, 54, 52)); // rosso scuro //
	m_ctrlSpreadsheet.put_PaletteEntry(2, RGB(242, 220, 219)); // rosso chiaro //
	m_ctrlSpreadsheet.put_PaletteEntry(3, RGB(190, 227, 149)); // verde //
	m_ctrlSpreadsheet.put_PaletteEntry(4, RGB(255, 255, 204)); // giallo //
	m_ctrlSpreadsheet.put_PaletteEntry(5, RGB(0, 0, 0)); // nero //
	m_ctrlSpreadsheet.put_PaletteEntry(6, RGB(128, 128, 128)); // grigio scuro scuro //
	m_ctrlSpreadsheet.put_PaletteEntry(7, RGB(166, 166, 166)); // grigio scuro //
	m_ctrlSpreadsheet.put_PaletteEntry(8, RGB(191, 191, 191)); // grigio medio //
	m_ctrlSpreadsheet.put_PaletteEntry(9, RGB(242, 242, 242)); // grigio chiaro //
	m_ctrlSpreadsheet.put_PaletteEntry(10, RGB(255, 255, 255)); // bianco //

	unsigned long ulColorRedDark = m_ctrlSpreadsheet.get_PaletteEntry(1);
	unsigned long ulColorRedLite = m_ctrlSpreadsheet.get_PaletteEntry(2);
	unsigned long ulColorGreen = m_ctrlSpreadsheet.get_PaletteEntry(3);
	unsigned long ulColorYellow = m_ctrlSpreadsheet.get_PaletteEntry(4);
	unsigned long ulColorBlack = m_ctrlSpreadsheet.get_PaletteEntry(5);
	unsigned long ulColorGrayDarkDark = m_ctrlSpreadsheet.get_PaletteEntry(6);
	unsigned long ulColorGrayDark = m_ctrlSpreadsheet.get_PaletteEntry(7);
	unsigned long ulColorGrayMidd = m_ctrlSpreadsheet.get_PaletteEntry(8);
	unsigned long ulColorGrayLite = m_ctrlSpreadsheet.get_PaletteEntry(9);
	unsigned long ulColorWhite = m_ctrlSpreadsheet.get_PaletteEntry(10);

	m_ctrlSpreadsheet.SetAllowDelete(FALSE); // disabilita il tasto canc per eliminare i valori (gestito con l'onkeypress del tasto canc)
	m_ctrlSpreadsheet.SetAllowDesigner(FALSE);
	m_ctrlSpreadsheet.SetAllowFillRange(FALSE);
	m_ctrlSpreadsheet.SetAllowMoveRange(FALSE);
	m_ctrlSpreadsheet.SetAllowObjSelections(FALSE);
	m_ctrlSpreadsheet.SetAllowResize(FALSE);
	// m_ctrlSpreadsheet.SetAllowSelections(FALSE);
	m_ctrlSpreadsheet.SetAutoRecalc(TRUE);
	// m_ctrlSpreadsheet.SetEnableProtection(TRUE); // abilita la protezione sul foglio... lo faccio alla fine //
	m_ctrlSpreadsheet.SetMaxCol(13);
	m_ctrlSpreadsheet.SetMaxRow(27);
	m_ctrlSpreadsheet.SetShowColHeading(FALSE);
	m_ctrlSpreadsheet.SetShowHScrollBar(0);
	m_ctrlSpreadsheet.SetShowRowHeading(FALSE);
	m_ctrlSpreadsheet.SetShowTabs(FALSE);
	m_ctrlSpreadsheet.SetShowVScrollBar(GetSystemMetrics(SM_CYSCREEN) < 1000 ? 1 : 0);

	m_ctrlSpreadsheet.SetColWidth(1, 1, 1000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(2, 2, 6000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(3, 3, 3000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(4, 4, 3000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(5, 5, 1000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(6, 6, 6000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(7, 7, 3000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(8, 8, 3000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(9, 9, 1000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(10, 10, 6100, FALSE);
	m_ctrlSpreadsheet.SetColWidth(11, 11, 3000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(12, 12, 3000, FALSE);
	m_ctrlSpreadsheet.SetColWidth(13, 13, 1000, FALSE);

	m_ctrlSpreadsheet.SetRowHeight(1, 27, 333, FALSE);

	m_ctrlSpreadsheet.SetSelection(1, 1, 27, 13);
	m_ctrlSpreadsheet.SetHAlign(2);
	m_ctrlSpreadsheet.SetVAlign(2);
	m_ctrlSpreadsheet.SetProtection(TRUE, FALSE); // imposta la protezione sulle celle selezionate

	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <= 13; j++)
		{
			m_ctrlSpreadsheet.SetSelection(i, j, i, j);
			m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, -1, -1, ulColorWhite, ulColorWhite, ulColorWhite, ulColorWhite);
		}
	}

	m_ctrlSpreadsheet.SetSelection("B2");
	m_ctrlSpreadsheet.put_TextRC(2, 2, "CÉLULAS A CONTAR");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedDark, 0);

	m_ctrlSpreadsheet.SetSelection("B3");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 1, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.put_TextRC(5, 2, "HISTIOCITOS");

	m_ctrlSpreadsheet.put_TextRC(6, 2, "MACROFAGOS");

	m_ctrlSpreadsheet.put_TextRC(7, 2, "MASTOCITOS");

	m_ctrlSpreadsheet.SetSelection("B9");
	m_ctrlSpreadsheet.put_TextRC(9, 2, "SÉRIE  GRANULOCITICA");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetFontUnderline(TRUE);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("B10");
	m_ctrlSpreadsheet.put_TextRC(10, 2, "NEUTROFILO");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.put_TextRC(11, 2, "N'-PROM");

	m_ctrlSpreadsheet.put_TextRC(12, 2, "N'-MIEL");

	m_ctrlSpreadsheet.put_TextRC(13, 2, "N'-METAM");

	m_ctrlSpreadsheet.put_TextRC(14, 2, "N'-BAST");

	m_ctrlSpreadsheet.put_TextRC(15, 2, "N'-SEGM");

	m_ctrlSpreadsheet.SetSelection("B16");
	m_ctrlSpreadsheet.put_TextRC(16, 2, "TT.NEUTROFILOS");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("B17");
	m_ctrlSpreadsheet.SetBorder(-1, 0, -1, 1, 0, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);

	m_ctrlSpreadsheet.SetSelection("B18");
	m_ctrlSpreadsheet.put_TextRC(18, 2, "SÉRIE VERMELHA");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetFontUnderline(TRUE);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("B19");
	m_ctrlSpreadsheet.put_TextRC(19, 2, "ERITROBLASTOS");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.put_TextRC(20, 2, "PROERITRO");

	m_ctrlSpreadsheet.put_TextRC(21, 2, "ERITRO  BASO");

	m_ctrlSpreadsheet.put_TextRC(22, 2, "ERIT POLICRO");

	m_ctrlSpreadsheet.put_TextRC(23, 2, "ERITRO ORTO");

	m_ctrlSpreadsheet.SetSelection("B24");
	m_ctrlSpreadsheet.put_TextRC(24, 2, "TT.ERITROBLASTOS");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("B25");
	m_ctrlSpreadsheet.SetBorder(-1, 0, -1, 1, 0, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);

	m_ctrlSpreadsheet.SetSelection("B26");
	m_ctrlSpreadsheet.put_TextRC(26, 2, "MIELOGRAMA TOTAL");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedDark, 0);

	m_ctrlSpreadsheet.SetSelection("B27");
	m_ctrlSpreadsheet.SetBorder(-1, 0, -1, 1, -1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C3");
	m_ctrlSpreadsheet.SetBorder(-1, -1, -1, 1, -1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("C4");
	m_ctrlSpreadsheet.put_TextRC(4, 3, "Absoluto");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("C5");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C6");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C7");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C8");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("C9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("C10");
	m_ctrlSpreadsheet.put_TextRC(10, 3, "Absoluto");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB(255, 255, 255));
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("C11");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C12");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C13");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C14");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C15");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C16");
	m_ctrlSpreadsheet.put_FormulaRC(16, 3, "C11+C12+C13+C14+C15");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("C17");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("C18");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("C19");
	m_ctrlSpreadsheet.put_TextRC(19, 3, "Absoluto");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB(255, 255, 255));
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("C20");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C21");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C22");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C23");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("C24");
	m_ctrlSpreadsheet.put_FormulaRC(24, 3, "C20+C21+C22+C23");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("C25");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("C26");
	m_ctrlSpreadsheet.put_FormulaRC(26, 3, "C5+C6+C7+C16+C24+G5+G6+G16+G20+G21+G22+K11");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDark, 0);

	m_ctrlSpreadsheet.SetSelection("C27");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 1, 1, -1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("D2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 0, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("D4");
	m_ctrlSpreadsheet.put_TextRC(4, 4, "%");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB(255, 255, 255));
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("D5");
	m_ctrlSpreadsheet.put_FormulaRC(5, 4, "C5/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D6");
	m_ctrlSpreadsheet.put_FormulaRC(6, 4, "C6/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D7");
	m_ctrlSpreadsheet.put_FormulaRC(7, 4, "C7/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D8");
	m_ctrlSpreadsheet.SetBorder(-1, -1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("D9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("D10");
	m_ctrlSpreadsheet.put_TextRC(10, 4, "%");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB(255, 255, 255));
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("D11");
	m_ctrlSpreadsheet.put_FormulaRC(11, 4, "C11/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D12");
	m_ctrlSpreadsheet.put_FormulaRC(12, 4, "C12/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D13");
	m_ctrlSpreadsheet.put_FormulaRC(13, 4, "C13/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D14");
	m_ctrlSpreadsheet.put_FormulaRC(14, 4, "C14/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D15");
	m_ctrlSpreadsheet.put_FormulaRC(15, 4, "C15/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D16");
	m_ctrlSpreadsheet.put_FormulaRC(16, 4, "D11+D12+D13+D14+D15");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D17");
	m_ctrlSpreadsheet.SetBorder(-1, -1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("D18");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("D19");
	m_ctrlSpreadsheet.put_TextRC(19, 4, "%");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB(255, 255, 255));
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("D20");
	m_ctrlSpreadsheet.put_FormulaRC(20, 4, "C20/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D21");
	m_ctrlSpreadsheet.put_FormulaRC(21, 4, "C21/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D22");
	m_ctrlSpreadsheet.put_FormulaRC(22, 4, "C22/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D23");
	m_ctrlSpreadsheet.put_FormulaRC(23, 4, "C23/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D24");
	m_ctrlSpreadsheet.put_FormulaRC(24, 4, "D20+D21+D22+D23");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("D25");
	m_ctrlSpreadsheet.SetBorder(-1, -1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("D26");
	m_ctrlSpreadsheet.put_FormulaRC(26, 4, "D5+D6+D7+D16+D24+H5+H6+H16+H20+H21+H22+L11");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDark, 0);

	m_ctrlSpreadsheet.SetSelection("D27");
	m_ctrlSpreadsheet.SetBorder(-1, -1, 1, 1, -1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("E4");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E5");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E6");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E7");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);

	m_ctrlSpreadsheet.SetSelection("E10");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E11");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E12");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E13");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E14");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E15");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E16");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E18");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);

	m_ctrlSpreadsheet.SetSelection("E19");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E20");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E21");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E22");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E23");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E24");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("E26");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("F5");
	m_ctrlSpreadsheet.put_TextRC(5, 6, "BLASTOS");

	m_ctrlSpreadsheet.SetSelection("F6");
	m_ctrlSpreadsheet.put_TextRC(6, 6, "OUTROS");

	m_ctrlSpreadsheet.SetSelection("F9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("F10");
	m_ctrlSpreadsheet.put_TextRC(10, 6, "EOSINOFILO");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("F11");
	m_ctrlSpreadsheet.put_TextRC(11, 6, "E'-PROM");

	m_ctrlSpreadsheet.SetSelection("F12");
	m_ctrlSpreadsheet.put_TextRC(12, 6, "E'-MIEL");

	m_ctrlSpreadsheet.SetSelection("F13");
	m_ctrlSpreadsheet.put_TextRC(13, 6, "E'-METAM");

	m_ctrlSpreadsheet.SetSelection("F14");
	m_ctrlSpreadsheet.put_TextRC(14, 6, "E'-BAST");

	m_ctrlSpreadsheet.SetSelection("F15");
	m_ctrlSpreadsheet.put_TextRC(15, 6, "E'-SEGM");

	m_ctrlSpreadsheet.SetSelection("F16");
	m_ctrlSpreadsheet.put_TextRC(16, 6, "TT.EOSINOFILOS");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("F18");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("F19");
	m_ctrlSpreadsheet.put_TextRC(19, 6, "MONONUCLEARES");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("F20");
	m_ctrlSpreadsheet.put_TextRC(20, 6, "LINFOCITO");

	m_ctrlSpreadsheet.SetSelection("F21");
	m_ctrlSpreadsheet.put_TextRC(21, 6, "MONOCITO");

	m_ctrlSpreadsheet.SetSelection("F22");
	m_ctrlSpreadsheet.put_TextRC(22, 6, "PLASMOCITO");

	m_ctrlSpreadsheet.SetSelection("F26");
	m_ctrlSpreadsheet.SetBorder(-1, 2, 2, 2, 2, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGreen, 0);

	m_ctrlSpreadsheet.SetSelection("F27");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 0, 2, -1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("G4");
	m_ctrlSpreadsheet.put_TextRC(4, 7, "Absoluto");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("G5");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("G6");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("G7");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 0, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("G9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("G10");
	m_ctrlSpreadsheet.put_TextRC(10, 7, "Absoluto");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("G11");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("G12");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("G13");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("G14");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("G15");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("G16");
	m_ctrlSpreadsheet.put_FormulaRC(16, 7, "G11+G12+G13+G14+G15");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("G17");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 0, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("G18");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("G19");
	m_ctrlSpreadsheet.put_TextRC(19, 7, "Absoluto");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("G20");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("G21");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("G22");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("G23");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 0, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("G26");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, 0, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("H4");
	m_ctrlSpreadsheet.put_TextRC(4, 8, "%");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("H5");
	m_ctrlSpreadsheet.put_FormulaRC(5, 8, "G5/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H6");
	m_ctrlSpreadsheet.put_FormulaRC(6, 8, "G6/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H7");
	m_ctrlSpreadsheet.SetBorder(-1, -1, 0, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("H9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("H10");
	m_ctrlSpreadsheet.put_TextRC(10, 8, "%");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("H11");
	m_ctrlSpreadsheet.put_FormulaRC(11, 8, "G11/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H12");
	m_ctrlSpreadsheet.put_FormulaRC(12, 8, "G12/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H13");
	m_ctrlSpreadsheet.put_FormulaRC(13, 8, "G13/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H14");
	m_ctrlSpreadsheet.put_FormulaRC(14, 8, "G14/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H15");
	m_ctrlSpreadsheet.put_FormulaRC(15, 8, "G15/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H16");
	m_ctrlSpreadsheet.put_FormulaRC(16, 8, "H11+H12+H13+H14+H15");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H17");
	m_ctrlSpreadsheet.SetBorder(-1, -1, 0, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("H18");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("H19");
	m_ctrlSpreadsheet.put_TextRC(19, 8, "%");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("H20");
	m_ctrlSpreadsheet.put_FormulaRC(20, 8, "G20/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H21");
	m_ctrlSpreadsheet.put_FormulaRC(21, 8, "G21/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H22");
	m_ctrlSpreadsheet.put_FormulaRC(22, 8, "G22/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("H23");
	m_ctrlSpreadsheet.SetBorder(-1, -1, 0, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("I4");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I5");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I6");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);

	m_ctrlSpreadsheet.SetSelection("I10");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I11");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I12");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I13");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I14");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I15");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I16");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I18");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);

	m_ctrlSpreadsheet.SetSelection("I19");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I20");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I21");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("I22");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("J9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("J10");
	m_ctrlSpreadsheet.put_TextRC(10, 10, "BASOFILO");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.put_TextRC(11, 10, "B'-SEGM");

	m_ctrlSpreadsheet.SetSelection("J18");
	m_ctrlSpreadsheet.put_TextRC(18, 10, "SÉRIE MEGACARIOCITICA");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetFontUnderline(TRUE);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("J19");
	m_ctrlSpreadsheet.put_TextRC(19, 10, "MGC");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("J21");
	m_ctrlSpreadsheet.put_TextRC(21, 10, "G.E.");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("J22");
	m_ctrlSpreadsheet.put_TextRC(22, 10, "E.G.");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("J23");
	m_ctrlSpreadsheet.put_TextRC(23, 10, "GRANULO / ERITROB");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	//

	m_ctrlSpreadsheet.SetSelection("K9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("K10");
	m_ctrlSpreadsheet.put_TextRC(10, 11, "Absoluto");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("K11");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

	m_ctrlSpreadsheet.SetSelection("K12");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 0, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("K18");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("K19");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayLite, 0);
	m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);
	// m_ctrlSpreadsheet.put_ObjItems(1, "PRESENTE;AUSENTE");

	m_ctrlSpreadsheet.SetSelection("K20");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 0, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("K21");
	m_ctrlSpreadsheet.put_FormulaRC(21, 11, "(C16+G16+K11)/C24");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.00");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("K22");
	m_ctrlSpreadsheet.put_FormulaRC(22, 11, "1/K21");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.00");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("K23");
	m_ctrlSpreadsheet.put_FormulaRC(23, 11, "(C16+G16+K11)/C24");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("K24");
	m_ctrlSpreadsheet.SetBorder(-1, 0, 0, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("L9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);
	m_ctrlSpreadsheet.SetPattern(1, ulColorRedLite, 0);

	m_ctrlSpreadsheet.SetSelection("L10");
	m_ctrlSpreadsheet.put_TextRC(10, 12, "%");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetFontBold(TRUE);
	m_ctrlSpreadsheet.SetFontColor(RGB_WHITE);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayDarkDark, 0);

	m_ctrlSpreadsheet.SetSelection("L11");
	m_ctrlSpreadsheet.put_FormulaRC(11, 12, "K11/C2");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);
	m_ctrlSpreadsheet.SetHAlign(3);
	m_ctrlSpreadsheet.SetNumberFormat("0.0%");
	m_ctrlSpreadsheet.SetPattern(1, ulColorGrayMidd, 0);

	m_ctrlSpreadsheet.SetSelection("L12");
	m_ctrlSpreadsheet.SetBorder(-1, -1, 0, 1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("L18");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);

	m_ctrlSpreadsheet.SetSelection("L19");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("L21");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("L22");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("L23");
	m_ctrlSpreadsheet.SetBorder(-1, 1, 0, -1, 0, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("M9");
	m_ctrlSpreadsheet.SetBorder(-1, 1, -1, 0, -1, 0, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite, ulColorRedLite);

	m_ctrlSpreadsheet.SetSelection("M10");
	m_ctrlSpreadsheet.SetBorder(-1, 1, -1, 0, -1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	m_ctrlSpreadsheet.SetSelection("M11");
	m_ctrlSpreadsheet.SetBorder(-1, 1, -1, 0, -1, 0, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack, ulColorBlack);

	//

	m_ctrlSpreadsheet.SetSelection("F26");
	m_ctrlSpreadsheet.SetEnableProtection(TRUE); // abilita la protezione sul foglio
}

void CMielogrammaDynForm::OnSpreadsheetEndEditCell(BSTR* EditString, short* Cancel)
{
	PostMessage(WM_USER + 0xabc);
}

void CMielogrammaDynForm::ResizeSpreadsheet()
{
	CWnd* pSpreadSheetPlace = GetDlgItem(IDC_STATIC_PLACE);
	if (pSpreadSheetPlace && m_ctrlSpreadsheet.GetSafeHwnd())
	{
		CRect rect;
		pSpreadSheetPlace->GetWindowRect(rect);
		ScreenToClient(&rect);
		m_ctrlSpreadsheet.SetWindowPos(NULL,
			0,
			0,
			rect.Width() - 11,
			rect.Height() - 11,
			SWP_NOZORDER | SWP_NOMOVE);
	}
}

LRESULT CMielogrammaDynForm::UpdateContagem(WPARAM wParam, LPARAM lParam)
{
	CString sCelulasAContar = m_ctrlSpreadsheet.get_TextRC(2, 3);
	CString sMielogramaTotal = m_ctrlSpreadsheet.get_TextRC(26, 3);

	CString sOldSelection = m_ctrlSpreadsheet.GetSelection();
	m_ctrlSpreadsheet.SetSelection("F26");
	if (sCelulasAContar.CompareNoCase(sMielogramaTotal) == 0)
	{
		unsigned long ulColorGreen = m_ctrlSpreadsheet.get_PaletteEntry(3);

		m_ctrlSpreadsheet.put_TextRC(26, 6, "CONTAGEM OK");
		m_ctrlSpreadsheet.SetPattern(1, ulColorGreen, 0);
	}
	else
	{
		unsigned long ulColorYellow = m_ctrlSpreadsheet.get_PaletteEntry(4);

		m_ctrlSpreadsheet.put_TextRC(26, 6, "EM CONTAGEM");
		m_ctrlSpreadsheet.SetPattern(1, ulColorYellow, 0);
	}
	m_ctrlSpreadsheet.SetSelection(sOldSelection);

	return 1;
}

CString CMielogrammaDynForm::GetTableCellNumberPercent(long lRow, long lCol)
{
	CString sReturn = "";

	sReturn = m_ctrlSpreadsheet.get_FormattedTextRC(lRow, lCol);
	sReturn.Replace("%", " %");

	while (sReturn.GetLength() < 7)
		sReturn = " " + sReturn;

	return sReturn;
}

CString CMielogrammaDynForm::GetTableCellText(long lRow, long lCol)
{
	CString sReturn = "";
	sReturn = m_ctrlSpreadsheet.get_FormattedTextRC(lRow, lCol);
	return sReturn;
}