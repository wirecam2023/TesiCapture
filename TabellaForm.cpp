#include "stdafx.h"
#include "Endox.h"
#include "TabellaForm.h"

#include "EsamiView.h"
#include "TabellaEsamiSet.h"
#include "VistaTabellaStruttureParametriSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _SPREADSHEET_FIXED_ROW   3
#define _SPREADSHEET_WEIGHT_ROW  1
#define _SPREADSHEET_HEIGHT_ROW  2
#define _SPREADSHEET_BSA_ROW     3
#define _SPREADSHEET_BSA_NAME    "BSA"

#define _SPREADSHEET_COL_ID			1
#define _SPREADSHEET_COL_STRUCTURE	2
#define _SPREADSHEET_COL_PARAMETER	3
#define _SPREADSHEET_COL_NUMBER		4
#define _SPREADSHEET_COL_REF_TXT	5
#define _SPREADSHEET_COL_REF_MIN	6
#define _SPREADSHEET_COL_REF_MAX	7
#define _SPREADSHEET_COL_UNI_MIS	8

#define _SPREADSHEET_COL_LETTER(a) CString((TCHAR)(a - 1 + 'A'))

CTabellaForm::CTabellaForm(CWnd* pParentWnd, CEsamiView* pEsamiView, CTXTextControl23Ex* pTxTextControl)
	: CEndoxDynForm(CTabellaForm::IDD, pParentWnd, pEsamiView)
{
	// ASSERT(pParentWnd != NULL);
	ASSERT(pEsamiView != NULL);
	ASSERT(pTxTextControl != NULL);

	m_pTxTextControl = pTxTextControl;

	m_bAutoUpdate = FALSE;

	m_bDebugBSA = FALSE;
	m_lFrassaoRow = -1;
	m_sFrassaoFormula = "";
}

CTabellaForm::~CTabellaForm()
{
}

BEGIN_MESSAGE_MAP(CTabellaForm, CEndoxDynForm)

	ON_BN_CLICKED(IDC_BUTTON_IMPORT, OnButtonImport)

	ON_CBN_SELCHANGE(IDC_CMB_FRAZIONE_EIEZIONE, OnCbnSelchangeCmbFrazioneEiezione)

	ON_EN_CHANGE(IDC_ALTEZZA, OnEnChangeAltezza)
	ON_EN_CHANGE(IDC_PESO, OnEnChangePeso)

	ON_WM_SIZE()

END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CTabellaForm, CEndoxDynForm)

	ON_EVENT(CTabellaForm, IDC_MEASURE_SHEET, DISPID_KEYDOWN, OnSpreadsheetKeyDown, VTS_PI2 VTS_I2)
	ON_EVENT(CTabellaForm, IDC_MEASURE_SHEET, 6, OnSpreadsheetEndEditCell, VTS_PBSTR VTS_PI2)

END_EVENTSINK_MAP()

void CTabellaForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ANAM_8, theApp.m_sAnamText[7]); // peso //
	DDX_Text(pDX, IDC_ANAM_9, theApp.m_sAnamText[8]); // altezza //

	DDX_Control(pDX, IDC_PESO, m_ctrlEditPeso);
	DDX_Control(pDX, IDC_ALTEZZA, m_ctrlEditAltezza);

	DDX_Control(pDX, IDC_MEASURE_SHEET, m_ctrlSpreadsheet);

	DDX_Control(pDX, IDC_ANAM_11, m_ctrlStaticAnam11);
	DDX_Control(pDX, IDC_ANAM_12, m_ctrlStaticAnam12);

	DDX_Control(pDX, IDC_CMB_FRAZIONE_EIEZIONE, m_ctrlCmbFrazioneEiezione);
}

BOOL CTabellaForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_ANAM_12, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_CMB_FRAZIONE_EIEZIONE, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_BUTTON_IMPORT, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_PLACE, CSize(0, 0), CSize(100, 100));

	//

	m_bDebugBSA = (GetPrivateProfileInt(szSettings, "Debug BSA", 0, theApp.m_sFileConfig) == 0 ? FALSE : TRUE);
	WritePrivateProfileInt(szSettings, "Debug BSA", m_bDebugBSA ? 1 : 0, theApp.m_sFileConfig);

	//

	m_ctrlCmbFrazioneEiezione.InsertString(0, theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE_0));
	m_ctrlCmbFrazioneEiezione.InsertString(1, theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE_1));
	m_ctrlCmbFrazioneEiezione.InsertString(2, theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE_2));
	m_ctrlCmbFrazioneEiezione.InsertString(3, theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE_3));
	m_ctrlCmbFrazioneEiezione.SetCurSel(m_pEsamiView->m_pEsamiSet->m_lFrazioneEiezione % 4);

	//

	InitSpreadsheet();
	LoadData();
	EnableSpreadSheet(TRUE);
	ResizeSpreadsheet();

	//

	OnCbnSelchangeCmbFrazioneEiezione();

	//

	theApp.LocalizeDialog(this, CTabellaForm::IDD, "TabellaForm");
	return TRUE;
}

void CTabellaForm::OnButtonImport()
{
	if (m_pTxTextControl != NULL)
	{
		if (m_pTxTextControl->GetTableAtInputPos() == 0)
		{
			if (m_pTxTextControl->GetTableCanInsert())
			{
				srand((unsigned)time(NULL));
				rand();	rand();	rand(); rand();

				short shRigaAttuale = _SPREADSHEET_FIXED_ROW + 1;
				short shRigheTotali = 0;
				while (m_ctrlSpreadsheet.get_NumberSRC(1, shRigaAttuale, _SPREADSHEET_COL_ID) > 0)
				{
					shRigaAttuale++;
					shRigheTotali++;
				}

				// Sandro 04/11/2016 // tolgo due righe (perché faccio una tabella a parte per peso, altezza, bsa) //
				if (shRigheTotali > 0)
				{
					m_pTxTextControl->SetSelText("\r\n");

					VARIANT varTemp;
					varTemp.vt = VT_I2;

					varTemp.iVal = (rand() % (32767 - 10)) + 10;
					short shTableIdInserted1 = m_pTxTextControl->TableInsert(1, 3, -1, varTemp);
					if (shTableIdInserted1 > 0)
					{
						CString sTemp;
						CString sText;

						// peso, altezza, bsa //

						sText = "";
						GetDlgItemText(IDC_ANAM_8, sTemp);
						sText += sTemp + ": ";
						GetDlgItemText(IDC_PESO, sTemp);
						sText += sTemp;
						m_pTxTextControl->put_TableCellText(shTableIdInserted1, 1, 1, sText);

						sText = "";
						GetDlgItemText(IDC_ANAM_9, sTemp);
						sText += sTemp + ": ";
						GetDlgItemText(IDC_ALTEZZA, sTemp);
						sText += sTemp;
						m_pTxTextControl->put_TableCellText(shTableIdInserted1, 1, 2, sText);

						sText = "";
						GetDlgItemText(IDC_ANAM_11, sTemp);
						sText += sTemp + ": ";
						GetDlgItemText(IDC_BSA, sTemp);
						sText += sTemp;
						m_pTxTextControl->put_TableCellText(shTableIdInserted1, 1, 3, sText);

						// Sandro 04/11/2016 // provo a cambiare la larghezza della tabella e delle colonne //

						VARIANT varNewValue;
						varNewValue.vt = VT_I2;
						varNewValue.iVal = 2500;

						m_pTxTextControl->put_TableCellAttribute(shTableIdInserted1, 0 /* tutte le righe */, 1, m_pTxTextControl->txTableCellHorizontalExt, varNewValue);
						m_pTxTextControl->put_TableCellAttribute(shTableIdInserted1, 0 /* tutte le righe */, 2, m_pTxTextControl->txTableCellHorizontalExt, varNewValue);
						m_pTxTextControl->put_TableCellAttribute(shTableIdInserted1, 0 /* tutte le righe */, 3, m_pTxTextControl->txTableCellHorizontalExt, varNewValue);
					}

					//

					m_pTxTextControl->SetFormatSelection(TRUE);
					m_pTxTextControl->SetFontBold(1);
					m_pTxTextControl->SetSelText("\r\n" + theApp.GetMessageString(IDS_MISURE_E_CALCOLI) + "\r\n\r\n");
					m_pTxTextControl->SetFontBold(0);

					//

					varTemp.iVal = (rand() % (32767 - 10)) + 10;
					short shTableIdInserted2 = m_pTxTextControl->TableInsert(shRigheTotali + 1, 4, -1, varTemp);
					if (shTableIdInserted2 > 0)
					{
						CString sTemp;
						CString sText;

						//

						/* Sandro 02/11/2016 // tolti i bordi su richiesta di Pilotto (racconta di casini con la direzione del Fleury proprio per questo motivo) //
						VARIANT varTemp2;
						varTemp2.vt = VT_I2;
						varTemp2.iVal = 5;

						m_pTxTextControl->put_TableCellAttribute(
							shTableIdInserted,
							0, / * tutte le righe * /
							0, / * tutte le colonne * /
							txTableCellBorderWidth,
							varTemp2
							);
						*/

						// intestazione colonne //

						sText = theApp.GetMessageString(IDS_TABELLAFORM_COL1);
						sText.MakeUpper();
						m_pTxTextControl->put_TableCellText(shTableIdInserted2, 1, 1, sText);

						sText = theApp.GetMessageString(IDS_TABELLAFORM_COL2);
						sText.MakeUpper();
						m_pTxTextControl->put_TableCellText(shTableIdInserted2, 1, 2, sText);

						sText = theApp.GetMessageString(IDS_TABELLAFORM_COL3);
						sText.MakeUpper();
						m_pTxTextControl->put_TableCellText(shTableIdInserted2, 1, 3, sText);

						sText = theApp.GetMessageString(IDS_TABELLAFORM_COL4);
						sText.MakeUpper();
						m_pTxTextControl->put_TableCellText(shTableIdInserted2, 1, 4, sText);

						// contenuto della tabella //

						for (short shRiga = 0; shRiga < shRigheTotali; shRiga++)
						{
							m_pTxTextControl->put_TableCellText(shTableIdInserted2, shRiga + 2, 1, m_ctrlSpreadsheet.get_TextSRC(1, shRiga + _SPREADSHEET_FIXED_ROW + 1, _SPREADSHEET_COL_STRUCTURE));
							m_pTxTextControl->put_TableCellText(shTableIdInserted2, shRiga + 2, 2, m_ctrlSpreadsheet.get_TextSRC(1, shRiga + _SPREADSHEET_FIXED_ROW + 1, _SPREADSHEET_COL_PARAMETER));
							m_pTxTextControl->put_TableCellText(shTableIdInserted2, shRiga + 2, 3, m_ctrlSpreadsheet.get_FormattedTextSRC(1, shRiga + _SPREADSHEET_FIXED_ROW + 1, _SPREADSHEET_COL_NUMBER) + m_ctrlSpreadsheet.get_TextSRC(1, shRiga + _SPREADSHEET_FIXED_ROW + 1, _SPREADSHEET_COL_UNI_MIS));
							m_pTxTextControl->put_TableCellText(shTableIdInserted2, shRiga + 2, 4, m_ctrlSpreadsheet.get_TextSRC(1, shRiga + _SPREADSHEET_FIXED_ROW + 1, _SPREADSHEET_COL_REF_TXT));
						}

						//

						long lSelStart = m_pTxTextControl->GetSelStart();
						long lSelLength = m_pTxTextControl->GetSelLength();

						// Sandro 04/11/2016 // provo a mettere i titoli in grassetto //

						m_pTxTextControl->TableCellSelect(shTableIdInserted2, 1, 1);
						m_pTxTextControl->SetFontBold(1);
						m_pTxTextControl->TableCellSelect(shTableIdInserted2, 1, 2);
						m_pTxTextControl->SetFontBold(1);
						m_pTxTextControl->TableCellSelect(shTableIdInserted2, 1, 3);
						m_pTxTextControl->SetFontBold(1);
						m_pTxTextControl->TableCellSelect(shTableIdInserted2, 1, 4);
						m_pTxTextControl->SetFontBold(1);

						// Sandro 04/11/2016 // provo a cambiare la larghezza della tabella e delle colonne //

						VARIANT varNewValue;
						varNewValue.vt = VT_I2;

						varNewValue.iVal = 2500;
						m_pTxTextControl->put_TableCellAttribute(shTableIdInserted2, 0 /* tutte le righe */, 1, m_pTxTextControl->txTableCellHorizontalExt, varNewValue);

						varNewValue.iVal = 4000;
						m_pTxTextControl->put_TableCellAttribute(shTableIdInserted2, 0 /* tutte le righe */, 2, m_pTxTextControl->txTableCellHorizontalExt, varNewValue);

						varNewValue.iVal = 1500;
						m_pTxTextControl->put_TableCellAttribute(shTableIdInserted2, 0 /* tutte le righe */, 3, m_pTxTextControl->txTableCellHorizontalExt, varNewValue);

						varNewValue.iVal = 2000;
						m_pTxTextControl->put_TableCellAttribute(shTableIdInserted2, 0 /* tutte le righe */, 4, m_pTxTextControl->txTableCellHorizontalExt, varNewValue);

						//

						m_pTxTextControl->SetSelStart(lSelStart);
						m_pTxTextControl->SetSelLength(lSelLength);
					}
				}
			}
		}
	}
}

void CTabellaForm::OnEnChangePeso()
{
	if (!m_bAutoUpdate)
	{
		CString strText;
		int nStartChar;
		int nEndChar;

		//
		GetDlgItemText(IDC_PESO, strText);

		strText.Replace(',', '.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditPeso.GetSel(nStartChar, nEndChar);
		m_ctrlEditPeso.SetWindowText(strText);
		m_ctrlEditPeso.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fPeso = (float)atof(strText);

		//

		GetDlgItemText(IDC_ALTEZZA, strText);

		strText.Replace(',', '.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditAltezza.GetSel(nStartChar, nEndChar);
		m_ctrlEditAltezza.SetWindowText(strText);
		m_ctrlEditAltezza.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fAltezza = (float)atof(strText);

		//
		UpdateBSA(fPeso, fAltezza);

		//
		long iYears = 0, iMonths = 0, iDays = 0;
		if (GetDateDifference(m_pEsamiView->m_pPazientiSet->m_lNatoIlCustom, m_pEsamiView->m_pEsamiSet->m_lData, &iYears, &iMonths, &iDays))
		{
			if (iYears < 18) // era 12, modifica richiesta da Pilotto via mail 27/03/2017
			{
				// PEDIATRICO //
				UpdateRiferimenti(fPeso);
			}
		}
	}
}

void CTabellaForm::OnEnChangeAltezza()
{
	if (!m_bAutoUpdate)
	{
		CString strText;
		int nStartChar;
		int nEndChar;

		//

		GetDlgItemText(IDC_PESO, strText);

		strText.Replace(',', '.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditPeso.GetSel(nStartChar, nEndChar);
		m_ctrlEditPeso.SetWindowText(strText);
		m_ctrlEditPeso.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fPeso = (float)atof(strText);

		//

		GetDlgItemText(IDC_ALTEZZA, strText);

		strText.Replace(',', '.');

		m_bAutoUpdate = TRUE;
		m_ctrlEditAltezza.GetSel(nStartChar, nEndChar);
		m_ctrlEditAltezza.SetWindowText(strText);
		m_ctrlEditAltezza.SetSel(nStartChar, nEndChar, FALSE);
		m_bAutoUpdate = FALSE;

		if (strText.Right(1).Compare(".") == 0)
			strText = strText.Left(strText.GetLength() - 1);

		float fAltezza = (float)atof(strText);

		//

		UpdateBSA(fPeso, fAltezza);
	}
}

void CTabellaForm::OnSize(UINT nType, int cx, int cy)
{
	CEndoxDynForm::OnSize(nType, cx, cy);
	ResizeSpreadsheet();
}

LRESULT CTabellaForm::OnResizeForm(WPARAM wParam, LPARAM lParam)
{
	CEndoxResizableDlg::OnResizeForm(wParam, lParam);
	return 0;
}

void CTabellaForm::OnSpreadsheetKeyDown(short* KeyCode, short Shift)
{
	//if (theApp.GetState() != CEcoState::EXAM_EDIT && theApp.GetState() != CEcoState::DIRTY)
	//	return;

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

void CTabellaForm::OnSpreadsheetEndEditCell(BSTR* EditString, short* Cancel)
{
	// per usare macro di conversione
	USES_CONVERSION;
	BOOL bError = FALSE;

	char* cellvalue = W2A(*EditString);
	CString strCellValue(cellvalue);
	strCellValue.Replace(",", ".");

	for (int i = 0; i < strCellValue.GetLength(); i++)
	{
		if ((strCellValue.GetAt(i) < '0' && strCellValue.GetAt(i) != '.') ||
			(strCellValue.GetAt(i) > '9' && strCellValue.GetAt(i) != '.'))
		{
			bError = TRUE;
		}
	}

	long lRow, lCol;
	m_ctrlSpreadsheet.GetActiveCell(&lRow, &lCol);

	if (bError || lCol != _SPREADSHEET_COL_NUMBER)
	{
		m_ctrlSpreadsheet.CancelEdit();
	}
	else
	{
		m_ctrlSpreadsheet.CancelEdit();

		m_ctrlSpreadsheet.put_NumberRC(lRow, lCol, atof(strCellValue));

		// Sandro 01/10/2015 // per salvare tutte le cifre con il giusto numero di decimali...

		CString sRealText = m_ctrlSpreadsheet.get_FormattedTextSRC(1, lRow, lCol);
		m_ctrlSpreadsheet.put_TextSRC(1, lRow, lCol, sRealText);

		// Sandro 27/09/2016 //

		CString sSel;
		sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), lRow);
		m_ctrlSpreadsheet.SetSelection(sSel);

		m_ctrlSpreadsheet.SetFontColor(RGB(0, 0, 0));

		if (!m_ctrlSpreadsheet.get_TextSRC(1, lRow, _SPREADSHEET_COL_REF_MIN).IsEmpty())
		{
			double dMin = m_ctrlSpreadsheet.get_NumberSRC(1, lRow, _SPREADSHEET_COL_REF_MIN);
			double dVal = m_ctrlSpreadsheet.get_NumberSRC(1, lRow, _SPREADSHEET_COL_NUMBER);
			if (dVal < dMin)
			{
				CString sSel;
				sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), lRow);
				m_ctrlSpreadsheet.SetSelection(sSel);

				m_ctrlSpreadsheet.SetFontColor(RGB(255, 0, 0));
			}
		}

		if (!m_ctrlSpreadsheet.get_TextSRC(1, lRow, _SPREADSHEET_COL_REF_MAX).IsEmpty())
		{
			double dMax = m_ctrlSpreadsheet.get_NumberSRC(1, lRow, _SPREADSHEET_COL_REF_MAX);
			double dVal = m_ctrlSpreadsheet.get_NumberSRC(1, lRow, _SPREADSHEET_COL_NUMBER);
			if (dVal > dMax)
			{
				CString sSel;
				sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), lRow);
				m_ctrlSpreadsheet.SetSelection(sSel);

				m_ctrlSpreadsheet.SetFontColor(RGB(255, 0, 0));
			}
		}

		//

		lRow++;
		BOOL bRestart = FALSE;
		while (TRUE)
		{
			if (m_ctrlSpreadsheet.get_TextRC(lRow, _SPREADSHEET_COL_ID) != "")
			{
				if (!m_ctrlSpreadsheet.get_RowHidden(lRow))
					break;
				lRow++;
			}
			else if (!bRestart)
			{
				lRow = 1;
				bRestart = TRUE;
			}
			else
			{
				// per evitare loop....

				lRow = 1;
				break;
			}
		}

		m_ctrlSpreadsheet.SetActiveCell(lRow, lCol);
	}

	m_ctrlSpreadsheet.Recalc();
	RecolorFormulaCells();
}

BOOL CTabellaForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CTXTextControl23Ex* pTxTextControl, CTabellaForm** pForm)
{
	BOOL bResult = FALSE;

	if ((*pForm) == NULL)
	{
		(*pForm) = new CTabellaForm(NULL, pEsamiView, pTxTextControl);
		if ((*pForm) != NULL)
		{
			(*pForm)->m_pParentFrame = pParentFrame;
			(*pForm)->m_lColore = -1;
			(*pForm)->m_lIDFaseBlocco = 2;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			//pParent->ScreenToClient(&rectFrame); // Sandro 19/10/2015 //
			(*pForm)->CreateChildForm(CTabellaForm::IDD, pParent, rectFrame);
		}
	}

	return bResult;
}

long CTabellaForm::GetContenuto()
{
	return -1;
}

BOOL CTabellaForm::CampoObbligatorioValido()
{
	return TRUE;
}

void CTabellaForm::ResizeSpreadsheet()
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
									   rect.Width(),
									   rect.Height(),
									   SWP_NOZORDER | SWP_NOMOVE);
	}
}

void CTabellaForm::LoadData()
{
	CString strFormulaBSA = theApp.m_sTabellaEcocardioFormulaBSA;
	strFormulaBSA.MakeUpper();

	CString strTmp;
	strTmp.Format("%s%li", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), _SPREADSHEET_WEIGHT_ROW);
	strFormulaBSA.Replace(_SPREADSHEET_FORMULA_SEPARATOR + CString(_SPREADSHEET_WEIGHT_NAME) + _SPREADSHEET_FORMULA_SEPARATOR, strTmp);
	strTmp.Format("%s%li", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), _SPREADSHEET_HEIGHT_ROW);
	strFormulaBSA.Replace(_SPREADSHEET_FORMULA_SEPARATOR + CString(_SPREADSHEET_HEIGHT_NAME) + _SPREADSHEET_FORMULA_SEPARATOR, strTmp);

	// Sandro 09/10/2015 // utilizzo il separatore decimale preso dal sistema //

	char szSep[8];
	GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, szSep, 8);
	strFormulaBSA.Replace('.', szSep[0]);

	//

	m_ctrlSpreadsheet.put_NumberSRC(1, _SPREADSHEET_WEIGHT_ROW, _SPREADSHEET_COL_ID, -1);
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_WEIGHT_ROW, _SPREADSHEET_COL_STRUCTURE, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_WEIGHT_ROW, _SPREADSHEET_COL_PARAMETER, _SPREADSHEET_WEIGHT_NAME);
	m_ctrlSpreadsheet.put_NumberSRC(1, _SPREADSHEET_WEIGHT_ROW, _SPREADSHEET_COL_NUMBER, 0.0);
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_WEIGHT_ROW, _SPREADSHEET_COL_REF_TXT, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_WEIGHT_ROW, _SPREADSHEET_COL_REF_MIN, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_WEIGHT_ROW, _SPREADSHEET_COL_REF_MAX, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_WEIGHT_ROW, _SPREADSHEET_COL_UNI_MIS, "");

	m_ctrlSpreadsheet.put_NumberSRC(1, _SPREADSHEET_HEIGHT_ROW, _SPREADSHEET_COL_ID, -2);
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_HEIGHT_ROW, _SPREADSHEET_COL_STRUCTURE, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_HEIGHT_ROW, _SPREADSHEET_COL_PARAMETER, _SPREADSHEET_HEIGHT_NAME);
	m_ctrlSpreadsheet.put_NumberSRC(1, _SPREADSHEET_HEIGHT_ROW, _SPREADSHEET_COL_NUMBER, 0.0);
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_HEIGHT_ROW, _SPREADSHEET_COL_REF_TXT, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_HEIGHT_ROW, _SPREADSHEET_COL_REF_MIN, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_HEIGHT_ROW, _SPREADSHEET_COL_REF_MAX, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_HEIGHT_ROW, _SPREADSHEET_COL_UNI_MIS, "");

	m_ctrlSpreadsheet.put_NumberSRC(1, _SPREADSHEET_BSA_ROW, _SPREADSHEET_COL_ID, -3);
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_BSA_ROW, _SPREADSHEET_COL_STRUCTURE, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_BSA_ROW, _SPREADSHEET_COL_PARAMETER, _SPREADSHEET_BSA_NAME);
	m_ctrlSpreadsheet.put_FormulaLocalSRC(1, _SPREADSHEET_BSA_ROW, _SPREADSHEET_COL_NUMBER, strFormulaBSA);
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_BSA_ROW, _SPREADSHEET_COL_REF_TXT, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_BSA_ROW, _SPREADSHEET_COL_REF_MIN, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_BSA_ROW, _SPREADSHEET_COL_REF_MAX, "");
	m_ctrlSpreadsheet.put_EntrySRC(1, _SPREADSHEET_BSA_ROW, _SPREADSHEET_COL_UNI_MIS, "");

	if (m_bDebugBSA)
	{
		CString sTempMessage;
		sTempMessage.Format("BSA FORMULA UO %li\n\n--> %s", theApp.m_lUO, strFormulaBSA);
		theApp.AfxMessageBoxEndo(sTempMessage);
	}
	else
	{
		for (int i = 1; i <= _SPREADSHEET_FIXED_ROW; i++)
			m_ctrlSpreadsheet.SetRowHidden(i, i, TRUE);
	}

	CString strText;

	if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_fAltezza) && (m_pEsamiView->m_pEsamiSet->m_fAltezza > 0))
	{
		strText.Format("%.0f", m_pEsamiView->m_pEsamiSet->m_fAltezza);
		SetDlgItemText(IDC_ALTEZZA, strText);
	}

	if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_fPeso) && (m_pEsamiView->m_pEsamiSet->m_fPeso > 0))
	{
		strText.Format("%.0f", m_pEsamiView->m_pEsamiSet->m_fPeso);
		SetDlgItemText(IDC_PESO, strText);
	}

	CList<tagFORMULA> listParFormula;

	CString strFilter;
	strFilter.Format("IDTipoEsame=%li", m_pEsamiView->m_pEsamiSet->m_lIDEsame);

	int iRow = _SPREADSHEET_FIXED_ROW + 1;
	long lIDStrutturaOld = -1;

	// Sandro 11/09/2015 //

	long iYears = 0, iMonths = 0, iDays = 0;
	BOOL bEtaOK = GetDateDifference(m_pEsamiView->m_pPazientiSet->m_lNatoIlCustom, m_pEsamiView->m_pEsamiSet->m_lData, &iYears, &iMonths, &iDays);

	//

	m_ctrlSpreadsheet.SetEnableProtection(FALSE);

	CString sCell;
	CString sFormat;

	CVistaTabellaStruttureParametriSet ParametriSet;
	ParametriSet.SetOpenFilter(strFilter);
	if (ParametriSet.OpenRecordset("CTabellaForm::LoadData"))
	{
		while (!ParametriSet.IsEOF())
		{
			m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_ID, ParametriSet.m_lIDParametro);

			if (lIDStrutturaOld != ParametriSet.m_lIDStruttura)
			{
				m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_STRUCTURE, ParametriSet.m_sStruttura);
				lIDStrutturaOld = ParametriSet.m_lIDStruttura;
			}

			//

			sCell.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), iRow);

			sFormat = "0";
			if (ParametriSet.m_lDecimali > 0)
			{
				sFormat += ".";
				while (ParametriSet.m_lDecimali > 0)
				{
					sFormat += "0";
					ParametriSet.m_lDecimali--;
				}
			}

			m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_PARAMETER, ParametriSet.m_sParametro);
			m_ctrlSpreadsheet.SetSelection(sCell);
			m_ctrlSpreadsheet.SetNumberFormat(sFormat);

			// Sandro 04/11/2016 //

			m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_UNI_MIS, ParametriSet.m_sUnitaDiMisura);

			// Sandro 11/09/2015 //

			if (bEtaOK)
			{
				if (iYears >= 18)
				{
					switch (m_pEsamiView->m_pPazientiSet->m_lSessoPaz)
					{
						case 0:
						{
							// MASCHIO //

							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoM);

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoMmin))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoMmin);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoMmax))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoMmax);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");

							break;
						}
						case 1:
						{
							// FEMMINA //

							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoF);

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoFmin))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoFmin);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoFmax))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoFmax);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");

							break;
						}
					}
				}
				else
				{
					// PEDIATRICO //
					if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_fPeso) && (m_pEsamiView->m_pEsamiSet->m_fPeso >= 2))
					{
						if (m_pEsamiView->m_pEsamiSet->m_fPeso < 5)
						{
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed00);

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed00min))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed00min);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed00max))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed00max);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
						}
						else if (m_pEsamiView->m_pEsamiSet->m_fPeso < 11)
						{
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed01);

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed01min))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed01min);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed01max))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed01max);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
						}
						else if (m_pEsamiView->m_pEsamiSet->m_fPeso < 21)
						{
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed02);

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed02min))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed02min);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed02max))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed02max);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
						}
						else if (m_pEsamiView->m_pEsamiSet->m_fPeso < 31)
						{
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed03);

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed03min))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed03min);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed03max))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed03max);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
						}
						else if (m_pEsamiView->m_pEsamiSet->m_fPeso < 41)
						{
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed04);

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed04min))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed04min);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed04max))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed04max);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
						}
						else if (m_pEsamiView->m_pEsamiSet->m_fPeso < 51)
						{
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed05);

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed05min))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed05min);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed05max))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed05max);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
						}
						else
						{
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed06);

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed06min))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed06min);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

							if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed06max))
								m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed06max);
							else
								m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
						}
					}
				}
			}

			// metto da parte i parametri con formula...
			ParametriSet.m_sFormula.Trim();
			if (!ParametriSet.m_sFormula.IsEmpty())
			{
				tagFORMULA tf;
				tf.lRow = iRow;
				strcpy_s(tf.szFormula, ParametriSet.m_sFormula);
				listParFormula.AddTail(tf);
			}
			else
			{
				long editablecolor = RGB(255, 255, 127);
				long gridcolor = RGB(192, 192, 192);
				m_ctrlSpreadsheet.SetPattern(1, editablecolor, editablecolor);
				m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, -1, -1, gridcolor, gridcolor, gridcolor, gridcolor);
			}

			// Sandro 30/09/2015 //
			if (ParametriSet.m_sParametro.Left(16).CompareNoCase("Fração de ejeção") == 0)
				m_lFrassaoRow = iRow;

			ParametriSet.MoveNext();
			iRow++;
		}

		ParametriSet.CloseRecordset("CTabellaForm::LoadData");
	}

	m_ctrlSpreadsheet.SetEnableProtection(TRUE);

	//

	for (POSITION posFormula = listParFormula.GetHeadPosition(); posFormula;)
	{
		tagFORMULA tf = listParFormula.GetNext(posFormula);
		CStringList listParams;

		// Separo i nomi dei parametri presenti nella formula...
		CString strTmp, strFormula(tf.szFormula);
		int iStart = 0, iFirst;
		strFormula.MakeUpper();
		while ((iFirst = strFormula.Find(_SPREADSHEET_FORMULA_SEPARATOR, iStart)) >= 0)
		{
			int iSecond = strFormula.Find(_SPREADSHEET_FORMULA_SEPARATOR, iFirst + 1);
			strTmp = strFormula.Mid(iFirst + 1, iSecond - iFirst - 1);
			iStart = iSecond + 1;
			strTmp.MakeUpper();

			listParams.AddTail(strTmp);
		}

		// Cerco nella griglia i parametri trovati nella formula e li sostituisco con il riferimento alla cella corretta...
		BOOL bError = FALSE;
		for (POSITION posString = listParams.GetHeadPosition(); posString;)
		{
			CString strParameter = listParams.GetNext(posString), strParSheet;
			strParameter.MakeUpper();
			BOOL bFound = FALSE;
			for (int i = 1; i < iRow; i++)
			{
				strParSheet = m_ctrlSpreadsheet.get_TextSRC(1, i, _SPREADSHEET_COL_PARAMETER);
				strParSheet.MakeUpper();
				if (strParameter == strParSheet)
				{
					strTmp.Format("%s%li", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), i);
					strFormula.Replace(_SPREADSHEET_FORMULA_SEPARATOR + strParameter + _SPREADSHEET_FORMULA_SEPARATOR, strTmp);
					bFound = TRUE;
					break;
				}
			}

			if (!bFound)
				bError = TRUE;
		}

		// Quando ho finito di scandire i parametri della formula, la inserisco nella cella corretta...
		if (!bError)
		{
			// Sandro 09/10/2015 // utilizzo il separatore decimale preso dal sistema //
			// Sandro 29/04/2016 // ricommento perché sembra non funzionare più :-( // va lasciato solo nella formula del BSA chissà perché //

			// char szSep[8];
			// GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, szSep, 8);
			// strFormula.Replace('.', szSep[0]);

			//

			if (tf.lRow == m_lFrassaoRow)
			{
				m_sFrassaoFormula = strFormula;

				// Sandro 04/11/2016 // carico la formula solo se nella combo della frazione di eiezione è selezionata la prima voce (teicholz) //
				if (m_ctrlCmbFrazioneEiezione.GetCurSel() == 0)
				{
					m_ctrlSpreadsheet.put_FormulaSRC(1, tf.lRow, _SPREADSHEET_COL_NUMBER, strFormula);
					m_ctrlSpreadsheet.SetSelection(tf.lRow, _SPREADSHEET_COL_NUMBER, tf.lRow, _SPREADSHEET_COL_NUMBER);
					m_ctrlSpreadsheet.SetFontColor(RGB(0, 0, 223));
				}
			}
			else
			{
				m_ctrlSpreadsheet.put_FormulaSRC(1, tf.lRow, _SPREADSHEET_COL_NUMBER, strFormula);
				m_ctrlSpreadsheet.SetSelection(tf.lRow, _SPREADSHEET_COL_NUMBER, tf.lRow, _SPREADSHEET_COL_NUMBER);
				m_ctrlSpreadsheet.SetFontColor(RGB(0, 0, 223));
			}
		}
		else
		{
			//CString strError;
			//strError.Format(theApp.GetMessageString(IDS_ERROR_FORMULA), m_measureSpreadSheet.get_TextSRC(sheetnumber, tf.lRow, 1));
			//theApp.EcoMessageBox(strError, MB_ICONSTOP);
		}
	}

	strFilter.Format("IDEsame = %li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	CTabellaEsamiSet DataSet;
	DataSet.SetOpenFilter(strFilter);
	if (DataSet.OpenRecordset("CTabellaForm::LoadData"))
	{
		while (!DataSet.IsEOF())
		{
			for (int i = _SPREADSHEET_FIXED_ROW + 1; i < iRow; i++)
			{
				if (m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_ID) == DataSet.m_lIDParametro)
				{
					if (m_ctrlSpreadsheet.get_FormulaSRC(1, i, _SPREADSHEET_COL_NUMBER).IsEmpty())
					{
						m_ctrlSpreadsheet.put_NumberSRC(1, i, _SPREADSHEET_COL_NUMBER, DataSet.m_fValore);

						if (!m_ctrlSpreadsheet.get_TextSRC(1, i, _SPREADSHEET_COL_REF_MIN).IsEmpty())
						{
							double dMin = m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_REF_MIN);
							if ((double)DataSet.m_fValore < dMin)
							{
								CString sSel;
								sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), i);
								m_ctrlSpreadsheet.SetSelection(sSel);

								m_ctrlSpreadsheet.SetFontColor(RGB(255, 0, 0));
							}
						}

						if (!m_ctrlSpreadsheet.get_TextSRC(1, i, _SPREADSHEET_COL_REF_MAX).IsEmpty())
						{
							double dMax = m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_REF_MAX);
							if ((double)DataSet.m_fValore > dMax)
							{
								CString sSel;
								sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), i);
								m_ctrlSpreadsheet.SetSelection(sSel);

								m_ctrlSpreadsheet.SetFontColor(RGB(255, 0, 0));
							}
						}
					}

					break;
				}
			}

			DataSet.MoveNext();
		}

		DataSet.CloseRecordset("CTabellaForm::LoadData");
	}

	//
	m_ctrlSpreadsheet.SetSelection(_SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER) + "4"); // seleziona la prima cella editabile

	//
	RecolorFormulaCells();
}

void CTabellaForm::SaveData()
{
	CString strText;

	GetDlgItemText(IDC_ALTEZZA, strText);
	float fAltezza = (float)atof(strText);

	GetDlgItemText(IDC_PESO, strText);
	float fPeso = (float)atof(strText);

	GetDlgItemText(IDC_BSA, strText);
	float fBSA = (float)atof(strText);

	BOOL bEsamiModify = theApp.m_nProgramMode & ADD_RECORD_ESAMI || theApp.m_nProgramMode & MODIFY_RECORD_ESAMI;

	BOOL bDoUpdate = FALSE;
	if (!bEsamiModify)
		bDoUpdate = m_pEsamiView->m_pEsamiSet->EditRecordset("CTabellaForm::SaveData");

	if ((m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_fAltezza) && (fAltezza > 0)) || (m_pEsamiView->m_pEsamiSet->m_fAltezza != fAltezza) ||
		(m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_fPeso) && (fPeso > 0)) || (m_pEsamiView->m_pEsamiSet->m_fPeso != fPeso))
	{
		m_pEsamiView->m_pEsamiSet->m_fAltezza = fAltezza;
		m_pEsamiView->m_pEsamiSet->m_fPeso = fPeso;
		m_pEsamiView->m_pEsamiSet->m_fBSA = fBSA;
	}

	// Sandro 30/09/2015 //
	m_pEsamiView->m_pEsamiSet->m_lFrazioneEiezione = m_ctrlCmbFrazioneEiezione.GetCurSel();

	if (bDoUpdate)
		m_pEsamiView->m_pEsamiSet->UpdateRecordset("CTabellaForm::SaveData");

	int lTotRows = 1;
	while (m_ctrlSpreadsheet.get_EntryRC(lTotRows, 1) != "") 
		lTotRows++;

	CList<int> listRowProcessed;

	CString strFilter;
	strFilter.Format("IDEsame = %li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	CTabellaEsamiSet DataSet;
	DataSet.SetOpenFilter(strFilter);
	if (DataSet.OpenRecordset("CTabellaForm::SaveData"))
	{
		while (!DataSet.IsEOF())
		{
			BOOL bFound = FALSE;
			for (int i = _SPREADSHEET_FIXED_ROW + 1; i < lTotRows; i++)
			{
				if (m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_ID) == DataSet.m_lIDParametro)
				{
					CString strValue1, strValue2;
					strValue1.Format("%.2f", m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_NUMBER));
					strValue2.Format("%.2f", DataSet.m_fValore);

					if (strValue1 != strValue2)
					{
						if (DataSet.EditRecordset("CTabellaForm::SaveData"))
						{
							DataSet.m_fValore = (float)m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_NUMBER);
							DataSet.UpdateRecordset("CTabellaForm::SaveData");
						}
					}

					listRowProcessed.AddTail(i);
					bFound = TRUE;
					break;
				}
			}

			if (!bFound)
				DataSet.DeleteRecordset("CTabellaForm::SaveData");

			DataSet.MoveNext();
		}

		for (int i = _SPREADSHEET_FIXED_ROW + 1; i < lTotRows; i++)
		{
			if (listRowProcessed.Find(i))
				continue;

			if (DataSet.AddNewRecordset("CTabellaForm::SaveData"))
			{
				DataSet.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
				DataSet.m_lIDParametro = (long)m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_ID);
				DataSet.m_fValore = (float)m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_NUMBER);
				DataSet.UpdateRecordset("CTabellaForm::SaveData");
			}
		}

		DataSet.CloseRecordset("CTabellaForm::SaveData");
	}
}

void CTabellaForm::UpdateBSA(float fPeso, float fAltezza)
{
	m_ctrlSpreadsheet.put_NumberSRC(1, _SPREADSHEET_WEIGHT_ROW, _SPREADSHEET_COL_NUMBER, fPeso);
	m_ctrlSpreadsheet.put_NumberSRC(1, _SPREADSHEET_HEIGHT_ROW, _SPREADSHEET_COL_NUMBER, fAltezza);
	m_ctrlSpreadsheet.Recalc();
	RecolorFormulaCells();

	double dBSA = m_ctrlSpreadsheet.get_NumberSRC(1, _SPREADSHEET_BSA_ROW, 4);
	
	CString strText;
	strText.Format("%.2f", dBSA);
	SetDlgItemText(IDC_BSA, strText);
}

void CTabellaForm::UpdateRiferimenti(float fPeso)
{
	int iRow = _SPREADSHEET_FIXED_ROW + 1;

	CString strFilter;
	strFilter.Format("IDTipoEsame=%li", m_pEsamiView->m_pEsamiSet->m_lIDEsame);

	CVistaTabellaStruttureParametriSet ParametriSet;
	ParametriSet.SetOpenFilter(strFilter);
	if (ParametriSet.OpenRecordset("CTabellaForm::LoadData"))
	{
		while (!ParametriSet.IsEOF())
		{
			if (iRow != m_lFrassaoRow)
			{
				// PEDIATRICO //
				if (fPeso >= 2)
				{
					if (fPeso < 5)
					{
						m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed00);

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed00min))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed00min);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed00max))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed00max);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
					}
					else if (fPeso < 11)
					{
						m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed01);

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed01min))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed01min);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed01max))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed01max);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
					}
					else if (fPeso < 21)
					{
						m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed02);

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed02min))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed02min);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed02max))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed02max);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
					}
					else if (fPeso < 31)
					{
						m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed03);

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed03min))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed03min);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed03max))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed03max);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
					}
					else if (fPeso < 41)
					{
						m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed04);

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed04min))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed04min);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed04max))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed04max);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
					}
					else if (fPeso < 51)
					{
						m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed05);

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed05min))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed05min);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed05max))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed05max);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
					}
					else
					{
						m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "'" + ParametriSet.m_sRiferimentoPed06);

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed06min))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MIN, ParametriSet.m_fRiferimentoPed06min);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");

						if (!ParametriSet.IsFieldNull(&ParametriSet.m_fRiferimentoPed06max))
							m_ctrlSpreadsheet.put_NumberSRC(1, iRow, _SPREADSHEET_COL_REF_MAX, ParametriSet.m_fRiferimentoPed06max);
						else
							m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
					}
				}
				else
				{
					m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_TXT, "");
					m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MIN, "");
					m_ctrlSpreadsheet.put_EntrySRC(1, iRow, _SPREADSHEET_COL_REF_MAX, "");
				}
			}

			iRow++;
			ParametriSet.MoveNext();
		}

		ParametriSet.CloseRecordset("CTabellaForm::LoadData");
	}
}

void CTabellaForm::InitSpreadsheet()
{
	m_ctrlSpreadsheet.SetAllowFillRange(FALSE);
	m_ctrlSpreadsheet.SetAllowMoveRange(FALSE);

	long lActiveSheet = m_ctrlSpreadsheet.GetSheet();
	for (int i = 1; i <= m_ctrlSpreadsheet.GetNumSheets(); i++)
	{
		m_ctrlSpreadsheet.SetSheet(i);
		m_ctrlSpreadsheet.put_ColText(_SPREADSHEET_COL_STRUCTURE, theApp.GetMessageString(IDS_TABELLAFORM_COL1));
		m_ctrlSpreadsheet.put_ColText(_SPREADSHEET_COL_PARAMETER, theApp.GetMessageString(IDS_TABELLAFORM_COL2));
		m_ctrlSpreadsheet.put_ColText(_SPREADSHEET_COL_NUMBER, theApp.GetMessageString(IDS_TABELLAFORM_COL3));
		m_ctrlSpreadsheet.put_ColText(_SPREADSHEET_COL_REF_TXT, theApp.GetMessageString(IDS_TABELLAFORM_COL4));
		m_ctrlSpreadsheet.put_ColText(_SPREADSHEET_COL_REF_MIN, theApp.GetMessageString(IDS_TABELLAFORM_COL5));
		m_ctrlSpreadsheet.put_ColText(_SPREADSHEET_COL_REF_MAX, theApp.GetMessageString(IDS_TABELLAFORM_COL6));
		m_ctrlSpreadsheet.put_ColText(_SPREADSHEET_COL_UNI_MIS, theApp.GetMessageString(IDS_TABELLAFORM_COL7));
		m_ctrlSpreadsheet.SetSelection(1, 1, 9999, _SPREADSHEET_COL_UNI_MIS);
		m_ctrlSpreadsheet.SetFont("Tahoma", 10, FALSE, FALSE, FALSE, FALSE, RGB(0, 0, 0), FALSE, FALSE);
		m_ctrlSpreadsheet.SetSelection(1, _SPREADSHEET_COL_NUMBER, 1, _SPREADSHEET_COL_NUMBER);
	}

	m_ctrlSpreadsheet.SetSheet(lActiveSheet);
	m_ctrlSpreadsheet.SetAutoRecalc(TRUE);

	CString temp;

	long sheets = 0;
	long maxrow = 0;
	long maxcol = 0;

	m_ctrlSpreadsheet.SetMaxRow(1000);

	m_ctrlSpreadsheet.SetAllowDesigner(FALSE); //impedisce che venga lanciato il workbook designer

	sheets = m_ctrlSpreadsheet.GetNumSheets();
	maxrow = m_ctrlSpreadsheet.GetMaxRow();
	maxcol = m_ctrlSpreadsheet.GetMaxCol();

	//inizializza ogni foglio della grid (finisce lasciando selezionato il primo foglio).
	for (int i = sheets; i > 0; i--)
	{
		m_ctrlSpreadsheet.SetSelection(1, 1, maxrow, maxcol); //setta il colore del font su tutti i fogli
		m_ctrlSpreadsheet.SetSheet(i);
		m_ctrlSpreadsheet.SetAllowDelete(FALSE); //disabilita il tasto canc per eliminare i valori (gestito con l'onkeypress del tasto canc)

		//crea la selezione
		temp.Format("%s1:%s%i", 
			        _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER),
					_SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER),
					maxrow);
		m_ctrlSpreadsheet.SetSelection(temp.GetBuffer());
		//m_ctrlSpreadsheet.AddSelection(-1, 3, -1, MEASUREGRIDVISIBLECOL);

		m_ctrlSpreadsheet.SetProtection(TRUE, FALSE); //imposta la protezione sulle celle selezionate

		//allinea al centro tutte le colonne tranne la prima
		temp.Format("%s1:%s%i",
			        _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER),
			        _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER),
			        maxrow);
		m_ctrlSpreadsheet.SetSelection(temp.GetBuffer());
		m_ctrlSpreadsheet.SetVAlign(2);
		m_ctrlSpreadsheet.SetHAlign(3);

		//allinea a sinistra
		temp.Format("%s1:%s%i",
			        _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_ID),
			        _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_PARAMETER),
			        maxrow);
		m_ctrlSpreadsheet.SetSelection(temp.GetBuffer());
		m_ctrlSpreadsheet.SetVAlign(2);
		m_ctrlSpreadsheet.SetHAlign(2);

		temp.Format("%s1:%s%i",
			_SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_REF_TXT),
			_SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_REF_TXT),
			maxrow);
		m_ctrlSpreadsheet.SetSelection(temp.GetBuffer());
		m_ctrlSpreadsheet.SetVAlign(2);
		m_ctrlSpreadsheet.SetHAlign(2);

		temp.Format("%s1:%s%i",
			_SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_REF_MIN),
			_SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_REF_MIN),
			maxrow);
		m_ctrlSpreadsheet.SetSelection(temp.GetBuffer());
		m_ctrlSpreadsheet.SetVAlign(3);
		m_ctrlSpreadsheet.SetHAlign(3);

		temp.Format("%s1:%s%i",
			_SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_REF_MAX),
			_SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_REF_MAX),
			maxrow);
		m_ctrlSpreadsheet.SetSelection(temp.GetBuffer());
		m_ctrlSpreadsheet.SetVAlign(3);
		m_ctrlSpreadsheet.SetHAlign(3);

		m_ctrlSpreadsheet.SetEnableProtection(TRUE); 		//abilita la protezione sul foglio
		m_ctrlSpreadsheet.SetSelection(_SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER) + "1"); 		//seleziona la prima cella editabile

		// m_ctrlSpreadsheet.SetColWidth(1, 1, 256 * 17, FALSE);
	}

	for (int i = m_ctrlSpreadsheet.GetNumSheets(); i > 0; i--)
	{
		m_ctrlSpreadsheet.SetSheet(i);
		m_ctrlSpreadsheet.put_ColHidden(1, TRUE);

		m_ctrlSpreadsheet.SetColWidth(2, 2, 256 * 20, FALSE);
		m_ctrlSpreadsheet.SetColWidth(3, 3, 256 * 26, FALSE);
		m_ctrlSpreadsheet.SetColWidth(4, 4, 256 * 11, FALSE);
		m_ctrlSpreadsheet.SetColWidth(5, 5, 256 * 26, FALSE);
	}

#ifdef _DEBUG
	m_ctrlSpreadsheet.SetColWidth(_SPREADSHEET_COL_REF_MIN, _SPREADSHEET_COL_REF_MIN, 256 * 10, FALSE);
	m_ctrlSpreadsheet.SetColWidth(_SPREADSHEET_COL_REF_MAX, _SPREADSHEET_COL_REF_MAX, 256 * 10, FALSE);
	m_ctrlSpreadsheet.SetColWidth(_SPREADSHEET_COL_UNI_MIS, _SPREADSHEET_COL_UNI_MIS, 256 * 10, FALSE);
#endif
}

void CTabellaForm::EnableSpreadSheet(BOOL enable)
{
	long sheets = m_ctrlSpreadsheet.GetNumSheets();
	CString strselection;

	//blocca le celle della seconda colonna di ogni foglio
	for (int i = sheets; i >= 1; i--)
	{
		m_ctrlSpreadsheet.SetSheet(i);

		long lTotRows = 1;
		while (m_ctrlSpreadsheet.get_EntryRC(lTotRows, 1) != "") lTotRows++;

		// Davide - Lascio le celle contenenti formule protette	
		CString strSelection = m_ctrlSpreadsheet.GetSelection();
		for (int j = 1; j < lTotRows; j++)
		{
			if (m_ctrlSpreadsheet.get_FormulaRC(j, _SPREADSHEET_COL_NUMBER).IsEmpty())
			{
				m_ctrlSpreadsheet.SetSelection(j, _SPREADSHEET_COL_NUMBER, j, _SPREADSHEET_COL_NUMBER);
				m_ctrlSpreadsheet.SetProtection(!enable, FALSE);
			}
		}

		m_ctrlSpreadsheet.SetSelection(strSelection); // seleziona la prima cella editabile
	}
}

void CTabellaForm::OnCbnSelchangeCmbFrazioneEiezione()
{
	if (m_lFrassaoRow >= 0)
	{
		CString sParameter = theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE);
		CString sRefTxt = "";
		double lfRefMin = 0;

		switch (m_ctrlCmbFrazioneEiezione.GetCurSel())
		{
			case 1:
			case 2:
			case 3:
			{
				if (m_ctrlCmbFrazioneEiezione.GetCurSel() == 1)
				{
					sParameter.Format("%s (%s)", theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE), theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE_1));
					sRefTxt = "'> 52%";
					lfRefMin = 52;
				}
				else if (m_ctrlCmbFrazioneEiezione.GetCurSel() == 2)
				{
					sParameter.Format("%s (%s)", theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE), theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE_2));
					sRefTxt = "'> 53%";
					lfRefMin = 53;
				}
				else if (m_ctrlCmbFrazioneEiezione.GetCurSel() == 3)
				{
					sParameter.Format("%s (%s)", theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE), theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE_3));
					sRefTxt = "'> 54%";
					lfRefMin = 54;
				}

				long editablecolor = RGB(255, 255, 127);
				long gridcolor = RGB(192, 192, 192);
				
				CString sCell;
				sCell.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), m_lFrassaoRow);
				m_ctrlSpreadsheet.SetSelection(sCell.GetBuffer());

				m_ctrlSpreadsheet.SetPattern(1, editablecolor, editablecolor);
				m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, -1, -1, gridcolor, gridcolor, gridcolor, gridcolor);
				m_ctrlSpreadsheet.SetFontColor(RGB(0, 0, 0));
				m_ctrlSpreadsheet.SetProtection(FALSE, FALSE);

				double dTemp = m_ctrlSpreadsheet.get_NumberSRC(1, m_lFrassaoRow, _SPREADSHEET_COL_NUMBER);
				m_ctrlSpreadsheet.put_NumberSRC(1, m_lFrassaoRow, _SPREADSHEET_COL_NUMBER, dTemp);

				sCell.ReleaseBuffer();

				break;
			}
			default:
			{
				sParameter.Format("%s (%s)", theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE), theApp.GetMessageString(IDS_FRAZIONE_EIEZIONE_0));
				sRefTxt = "'> 54%";
				lfRefMin = 54;

				long noneditablecolor = RGB(255, 255, 255);
				long gridcolor = RGB(192, 192, 192);

				CString sCell;
				sCell.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), m_lFrassaoRow);
				m_ctrlSpreadsheet.SetSelection(sCell.GetBuffer());

				m_ctrlSpreadsheet.SetPattern(1, noneditablecolor, noneditablecolor);
				m_ctrlSpreadsheet.SetBorder(-1, 1, 1, 1, 1, -1, -1, gridcolor, gridcolor, gridcolor, gridcolor);
				m_ctrlSpreadsheet.SetFontColor(RGB(0, 0, 223));
				m_ctrlSpreadsheet.SetProtection(TRUE, FALSE);

				m_ctrlSpreadsheet.put_FormulaSRC(1, m_lFrassaoRow, _SPREADSHEET_COL_NUMBER, m_sFrassaoFormula);

				sCell.ReleaseBuffer();

				break;
			}
		}

		m_ctrlSpreadsheet.put_EntrySRC(1, m_lFrassaoRow, _SPREADSHEET_COL_PARAMETER, sParameter);
		m_ctrlSpreadsheet.put_EntrySRC(1, m_lFrassaoRow, _SPREADSHEET_COL_REF_TXT, sRefTxt);
		m_ctrlSpreadsheet.put_NumberSRC(1, m_lFrassaoRow, _SPREADSHEET_COL_REF_MIN, lfRefMin);
		m_ctrlSpreadsheet.put_EntrySRC(1, m_lFrassaoRow, _SPREADSHEET_COL_REF_MAX, "");

		// Sandro 04/11/2016 // riaggiorno anche il colore del testo nella cella //

		CString sSel;
		sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), m_lFrassaoRow);
		m_ctrlSpreadsheet.SetSelection(sSel);

		// m_ctrlSpreadsheet.SetFontColor(RGB(0, 0, 0));

		if (!m_ctrlSpreadsheet.get_TextSRC(1, m_lFrassaoRow, _SPREADSHEET_COL_REF_MIN).IsEmpty())
		{
			double dMin = m_ctrlSpreadsheet.get_NumberSRC(1, m_lFrassaoRow, _SPREADSHEET_COL_REF_MIN);
			double dVal = m_ctrlSpreadsheet.get_NumberSRC(1, m_lFrassaoRow, _SPREADSHEET_COL_NUMBER);
			if (dVal < dMin)
			{
				CString sSel;
				sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), m_lFrassaoRow);
				m_ctrlSpreadsheet.SetSelection(sSel);

				m_ctrlSpreadsheet.SetFontColor(RGB(255, 0, 0));
			}
		}

		if (!m_ctrlSpreadsheet.get_TextSRC(1, m_lFrassaoRow, _SPREADSHEET_COL_REF_MAX).IsEmpty())
		{
			double dMax = m_ctrlSpreadsheet.get_NumberSRC(1, m_lFrassaoRow, _SPREADSHEET_COL_REF_MAX);
			double dVal = m_ctrlSpreadsheet.get_NumberSRC(1, m_lFrassaoRow, _SPREADSHEET_COL_NUMBER);
			if (dVal > dMax)
			{
				CString sSel;
				sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), m_lFrassaoRow);
				m_ctrlSpreadsheet.SetSelection(sSel);

				m_ctrlSpreadsheet.SetFontColor(RGB(255, 0, 0));
			}
		}

	}

	m_ctrlSpreadsheet.SetFocus();
}

void CTabellaForm::RecolorFormulaCells()
{
	CString sSel = m_ctrlSpreadsheet.GetSelection();
	for (int i = _SPREADSHEET_FIXED_ROW + 1; i < 256; i++)
	{
		CString sFormula = m_ctrlSpreadsheet.get_FormulaSRC(1, i, _SPREADSHEET_COL_NUMBER);
		sFormula.Trim();
		if (!sFormula.IsEmpty())
		{
			// Sandro 27/09/2016 //

			CString sSel;
			sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), i);
			m_ctrlSpreadsheet.SetSelection(sSel);

			m_ctrlSpreadsheet.SetFontColor(RGB(0, 0, 223));

			if (!m_ctrlSpreadsheet.get_TextSRC(1, i, _SPREADSHEET_COL_REF_MIN).IsEmpty())
			{
				double dMin = m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_REF_MIN);
				double dVal = m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_NUMBER);
				if (dVal < dMin)
				{
					CString sSel;
					sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), i);
					m_ctrlSpreadsheet.SetSelection(sSel);

					m_ctrlSpreadsheet.SetFontColor(RGB(255, 0, 0));
				}
			}

			if (!m_ctrlSpreadsheet.get_TextSRC(1, i, _SPREADSHEET_COL_REF_MAX).IsEmpty())
			{
				double dMax = m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_REF_MAX);
				double dVal = m_ctrlSpreadsheet.get_NumberSRC(1, i, _SPREADSHEET_COL_NUMBER);
				if (dVal > dMax)
				{
					CString sSel;
					sSel.Format("%s%i", _SPREADSHEET_COL_LETTER(_SPREADSHEET_COL_NUMBER), i);
					m_ctrlSpreadsheet.SetSelection(sSel);

					m_ctrlSpreadsheet.SetFontColor(RGB(255, 0, 0));
				}
			}
		}
	}
	m_ctrlSpreadsheet.SetSelection(sSel);
}