#include "stdafx.h"
#include "Endox.h"
#include "CentraleDiStampaDynForm.h"

#include <io.h>

#include "DLL_Imaging\h\AmBase64.h"
#include "DLL_Imaging\h\AmLogin.h"
#include "DLL_Imaging\h\PrintService.h"

#include "ElemReportSet.h"
#include "EsamiView.h"
#include "HeaderFooterSet.h"
#include "MediciSet.h"
#include "PasswordDlg.h"
#include "PdfAnteprimaDlg.h"
#include "PdfStampaDlg.h"
#include "PdfUtilInterface.h"
#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCentraleDiStampaDynForm::CCentraleDiStampaDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
	m_bThreadAlreadyGoing = FALSE;
	m_bUtilizzaCartaIntestata = FALSE;

	m_lFontHeightNormal = -13;
	m_lFontHeightSmall = -11;
	m_lFontHeightSmallSmall = -8;

	m_sFontName = "MS Sans Serif";
	m_sPrintingFicha = "";
	m_sError = "";
}

CCentraleDiStampaDynForm::~CCentraleDiStampaDynForm()
{
}

BEGIN_MESSAGE_MAP(CCentraleDiStampaDynForm, CEndoxDynForm)

	ON_BN_CLICKED(IDC_BTN_CONFERMA, OnBnClickedBtnConferma)

	ON_MESSAGE(EPM_CHECKVALUE, OnCheckValue)
	ON_MESSAGE(EPM_PRINTINGTHREADENDED, OnPrintingThreadEnded)

	ON_WM_CTLCOLOR()
	ON_WM_TIMER()

END_MESSAGE_MAP()

void CCentraleDiStampaDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView)
{
	if (pEsamiView->m_pDynForm[sub_centraledistampa] == NULL)
	{
		pEsamiView->m_pDynForm[sub_centraledistampa] = new CCentraleDiStampaDynForm(CCentraleDiStampaDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_centraledistampa] != NULL)
		{
			pEsamiView->m_pDynForm[sub_centraledistampa]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_centraledistampa]->m_lColore = 0;
			pEsamiView->m_pDynForm[sub_centraledistampa]->m_lIDFaseBlocco = 0;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_centraledistampa]->CreateChildForm(CCentraleDiStampaDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CCentraleDiStampaDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_FICHA:
		case IDC_EDIT_FICHA:
		case IDC_BTN_CONFERMA:
		{
			pDC->SetTextColor(theApp.m_color[1]);
			break;
		}
		case IDC_STATIC_TITLE1:
		case IDC_LIST1:
		{
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}
		case IDC_STATIC_PRINTING1:
		case IDC_STATIC_PRINTING2:
		{
			pDC->SetTextColor(theApp.m_color[3]);
			break;
		}
		case IDC_STATIC_TITLE2:
		case IDC_LIST2:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
	}

	return hBrush;
}

void CCentraleDiStampaDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_CONFERMA, m_ctrlBtnConferma);

	DDX_Control(pDX, IDC_EDIT_FICHA, m_ctrlEditFicha);

	DDX_Control(pDX, IDC_LIST1, m_ctrlList1);
	DDX_Control(pDX, IDC_LIST2, m_ctrlList2);

	DDX_Control(pDX, IDC_STATIC_FICHA, m_ctrlStaticFicha);
	DDX_Control(pDX, IDC_STATIC_PRINTING1, m_ctrlStaticPrinting1);
	DDX_Control(pDX, IDC_STATIC_PRINTING2, m_ctrlStaticPrinting2);
	DDX_Control(pDX, IDC_STATIC_TITLE1, m_ctrlStaticTitle1);
	DDX_Control(pDX, IDC_STATIC_TITLE2, m_ctrlStaticTitle2);
}

BOOL CCentraleDiStampaDynForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_TEST, CSize(50, 31), CSize(50, 47));

	AddAnchor(IDC_STATIC_FICHA, CSize(50, 31), CSize(50, 31));
	AddAnchor(IDC_EDIT_FICHA, CSize(50, 31), CSize(50, 31));
	AddAnchor(IDC_BTN_CONFERMA, CSize(50, 31), CSize(50, 31));
	AddAnchor(IDC_STATIC_TITLE1, CSize(50, 31), CSize(50, 31));
	AddAnchor(IDC_LIST1, CSize(50, 31), CSize(50, 47));

	AddAnchor(IDC_STATIC_PRINTING1, CSize(50, 31), CSize(50, 31));
	AddAnchor(IDC_STATIC_PRINTING2, CSize(50, 31), CSize(50, 31));
	AddAnchor(IDC_STATIC_TITLE2, CSize(50, 31), CSize(50, 31));
	AddAnchor(IDC_LIST2, CSize(50, 31), CSize(50, 47));

	//

	m_ctrlList1.SetExtendedStyle(m_ctrlList1.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

	m_ctrlList1.InsertColumn(0, ""); // empty //
	m_ctrlList1.InsertColumn(1, "", LVCFMT_CENTER); // ora //
	m_ctrlList1.InsertColumn(2, "", LVCFMT_CENTER); // ficha //

	m_ctrlList1.SetColumnWidth(0, 0);
	m_ctrlList1.SetColumnWidth(1, 145);
	m_ctrlList1.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList1.SetTextColor(theApp.m_color[0]);

	//

	m_ctrlList2.SetExtendedStyle(m_ctrlList2.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);

	m_ctrlList2.InsertColumn(0, ""); // empty //
	m_ctrlList2.InsertColumn(1, "", LVCFMT_CENTER); // ora //
	m_ctrlList2.InsertColumn(2, "", LVCFMT_LEFT); // ficha //

	m_ctrlList2.SetColumnWidth(0, 0);
	m_ctrlList2.SetColumnWidth(1, 145);
	m_ctrlList2.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList2.SetTextColor(theApp.m_color[2]);

	//

	m_ctrlStaticFicha.SetFont(&theApp.m_fontBigBig);
	m_ctrlEditFicha.SetFont(&theApp.m_fontBigBig);
	m_ctrlBtnConferma.SetFont(&theApp.m_fontBigBig);
	m_ctrlStaticTitle1.SetFont(&theApp.m_fontBigBig);
	m_ctrlList1.SetFont(&theApp.m_fontBigBig);

	m_ctrlStaticPrinting1.SetFont(&theApp.m_fontBigBig);
	m_ctrlStaticPrinting2.SetFont(&theApp.m_fontBigBig);
	m_ctrlStaticTitle2.SetFont(&theApp.m_fontBigBig);
	m_ctrlList2.SetFont(&theApp.m_fontBigBig);

	// provo a caricare la stampante su cui dopo lancerò la stampa //

	HGLOBAL hDevNames = NULL;
	HGLOBAL hDevMode = NULL;
	while ((hDevNames == NULL) || (hDevMode == NULL))
	{
		if (!LoadPrinterSettingsFromNumber(Printer_Immagini, &hDevNames, &hDevMode))
		{
			theApp.AfxMessageBoxEndo(IDS_STAMPANTEIMMAGINI_NONDEFINITA, MB_ICONSTOP);
			if (CPasswordDlg(this, theApp.GetMessageString(IDS_PASSWORD_SETUP), "nautilus").DoModal() == IDOK)
			{
				if (CSetupDlg(m_pEsamiView).DoModal() == IDOK)
					theApp.SaveSetting();
			}
			else
			{
				m_pEsamiView->m_bImporting = FALSE;
				theApp.m_bChiusuraProgrammaConferma = FALSE;
				AfxGetMainWnd()->PostMessage(WM_CLOSE);
				return TRUE;
			}
		}
	}

	//

	CString sPdfPrintFile = theApp.m_sDirProg + "\\xPdfPrint.exe";
	if (_access(sPdfPrintFile, 06) != 00)
	{
		theApp.AfxMessageBoxEndo(IDS_XPDFPRINT_NONTROVATO, MB_ICONSTOP);

		m_pEsamiView->m_bImporting = FALSE;
		theApp.m_bChiusuraProgrammaConferma = FALSE;
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
		return TRUE;
	}

	//

	unidadeRequest request;
	sprintf(request.szCodigoUnidade, "%li", theApp.m_lCentraleStampaCodiceUnita);

	CPrintService printService(theApp.m_sHttpServerRichiestaUnidade, theApp.m_sHttpServerRichiestaLaudos);
	unidadeResponse response = printService.GetUnidade(request);

	CString sError(response.szError);
	sError.Trim();
	if (sError.IsEmpty() || (sError.Compare("0") == 0))
	{
		if (CString(response.szUtilizaPapelTimbrado).CompareNoCase("s") == 0)
			m_bUtilizzaCartaIntestata = TRUE;
	}
	else
	{
// #ifndef _DEBUG
		CString sMessageError;
		sMessageError.Format(theApp.GetMessageString(IDS_ERROREUNIDADEREQUEST) + " (" + CString(request.szCodigoUnidade) + ")\r\n\r\n" + sError);
		theApp.AfxMessageBoxEndo(sMessageError);
// #endif
	}

	//

	SetTimer(0xeda, 5000, NULL);

	//

	theApp.LocalizeDialog(this, CCentraleDiStampaDynForm::IDD, "CentraleDiStampaDynForm");

	m_ctrlEditFicha.SetFocus();
	return FALSE;
}

void CCentraleDiStampaDynForm::OnOK()
{
}

LRESULT CCentraleDiStampaDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CCentraleDiStampaDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CCentraleDiStampaDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CCentraleDiStampaDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CCentraleDiStampaDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CCentraleDiStampaDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

long CCentraleDiStampaDynForm::GetContenuto()
{
	return sub_centraledistampa;
}

BOOL CCentraleDiStampaDynForm::CampoObbligatorioValido()
{
	return TRUE;
}

void CCentraleDiStampaDynForm::OnTimer(UINT nIDEvent)
{
	if (nIDEvent != 0xeda)
		return;

	if (m_bThreadAlreadyGoing)
		return;

	if (m_ctrlList1.GetItemCount() <= 0)
		return;

	//

	m_bThreadAlreadyGoing = TRUE;
	KillTimer(0xeda);

	m_sPrintingFicha = m_ctrlList1.GetItemText(0, 2);
	m_ctrlList1.DeleteItem(0);

	m_ctrlStaticPrinting2.SetWindowText(m_sPrintingFicha);

	GetDlgItem(IDC_STATIC_PRINTING1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_PRINTING2)->ShowWindow(SW_SHOW);

	AfxBeginThread(PrintingThread, this);
}

void CCentraleDiStampaDynForm::OnBnClickedBtnConferma()
{
	CString sFicha;
	m_ctrlEditFicha.GetWindowText(sFicha);
	sFicha.Trim();
	/*
	if (sFicha.Find('_') != -1 && sFicha.GetLength() < 14)
	{
		theApp.AfxMessageBoxEndo(IDS_NUMEROFICHA_NONCORRETTO);
		return;
	}
	else
	{
		if (sFicha.GetLength() < 16)
		{
			theApp.AfxMessageBoxEndo(IDS_NUMEROFICHA_NONCORRETTO);
			return;
		}
	}*/

	m_pEsamiView->m_bPrinting = TRUE;	

	int nItem = m_ctrlList1.GetItemCount();
	nItem = m_ctrlList1.InsertItem(nItem, "");
	m_ctrlList1.SetItemText(nItem, 1, CTime::GetCurrentTime().Format("%H:%M:%S"));
	m_ctrlList1.SetItemText(nItem, 2, sFicha);
	
	m_ctrlEditFicha.SetWindowText("");
}

UINT CCentraleDiStampaDynForm::PrintingThread(LPVOID pParam)
{
	CCentraleDiStampaDynForm* pForm = (CCentraleDiStampaDynForm*)pParam;

	//

	CString sUnita = pForm->m_sPrintingFicha.Left(3);

	//

	CString sSignatureFile = theApp.m_sDirTemp + "\\signature.xxx";

	//

	if (sUnita.GetLength() == 3)
	{
		long lIDHeader = CHeaderFooterSet().AddRow(sUnita, 1, 50);
		long lIDFooter1 = CHeaderFooterSet().AddRow(sUnita, 2, 65);
		long lIDFooter2 = CHeaderFooterSet().AddRow(sUnita, 2, 65);

		CString sIDMarca = "";

		if (pForm->RecuperaDatiUnita(sUnita, lIDHeader, lIDFooter1, lIDFooter2, sIDMarca))
		{
			long lUserID;
			AMLogin_GetUserID(&lUserID);

			obterLaudoResponse* pResponse = pForm->RecuperaDatiReferti(sIDMarca, pForm->m_sPrintingFicha, CMediciSet().GetCodiceFromUserID(lUserID).Left(3));
			if (pResponse != NULL)
			{
				if (CString(pResponse->szError).GetLength() > 0)
				{
					pForm->m_sError = CString(pResponse->szError);

					CHeaderFooterSet().DelRow(lIDHeader);
					CHeaderFooterSet().DelRow(lIDFooter1);
					CHeaderFooterSet().DelRow(lIDFooter2);

					pForm->PostMessage(EPM_PRINTINGTHREADENDED);
					return 0;
				}
				// HEADER //

				CElemReportSet().AddRow(lIDHeader, "Text", theApp.GetMessageString(IDS_PAZIENTE) + ":", 15, 35, 25, 30, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);
				CElemReportSet().AddRow(lIDHeader, "Text", pResponse->szPaciente, 35, 150, 25, 30, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);

				CElemReportSet().AddRow(lIDHeader, "Text", theApp.GetMessageString(IDS_MEDICO) + ":", 15, 35, 30, 35, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);
				CElemReportSet().AddRow(lIDHeader, "Text", pResponse->szMedico, 35, 150, 30, 35, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);

				CElemReportSet().AddRow(lIDHeader, "Text", theApp.GetMessageString(IDS_DATADINASCITA) + ":", 15, 50, 35, 40, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);
				CElemReportSet().AddRow(lIDHeader, "Text", CString(pResponse->szDataNascimento).Left(10), 50, 150, 35, 40, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);

				CElemReportSet().AddRow(lIDHeader, "Text", theApp.GetMessageString(IDS_ESAME) + ":", 150, 165, 25, 30, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);
				CElemReportSet().AddRow(lIDHeader, "Text", pResponse->szExame, 165, 195, 25, 30, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);

				CElemReportSet().AddRow(lIDHeader, "Text", theApp.GetMessageString(IDS_DATA) + ":", 150, 165, 30, 35, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);
				CElemReportSet().AddRow(lIDHeader, "Text", CString(pResponse->szDataExame).Left(10), 165, 195, 30, 35, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);

				// FOOTER1 //

				CElemReportSet().AddRow(lIDFooter1, "PageNum", "PageNum", 176, 186, 33, 37, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmall, FW_NORMAL, 0, 0, 2, 0);
				CElemReportSet().AddRow(lIDFooter1, "Text", "/", 186, 190, 33, 37, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmall, FW_NORMAL, 0, 0, 1, 0);
				CElemReportSet().AddRow(lIDFooter1, "PageTot", "PageTot", 190, 200, 33, 37, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmall, FW_NORMAL, 0, 0, 0, 0);
				CElemReportSet().AddRow(lIDFooter1, "Text", theApp.GetMessageString(IDS_CONTINUA), 176, 200, 37, 41, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmall, FW_NORMAL, 0, 0, 1, 0);

				// FOOTER2 //

				CElemReportSet().AddRow(lIDFooter2, "Icon", sSignatureFile, 110, 160, 0, 15, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightNormal, FW_NORMAL, 0, 0, 0, 0);

				long lIDRiga123Rtf = CElemReportSet().AddRow(lIDFooter2, "Rtf", "", 10, 205, 15, 27, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmall, FW_NORMAL, 0, 0, 0, 0);
				long lIDRiga1Sx = CElemReportSet().AddRow(lIDFooter2, "Text", "", 10, 105, 15, 19, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmallSmall, FW_NORMAL, 0, 0, 0, 0);
				long lIDRiga1Dx = CElemReportSet().AddRow(lIDFooter2, "Text", "", 110, 205, 15, 19, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmallSmall, FW_NORMAL, 0, 0, 0, 0);
				long lIDRiga2Sx = CElemReportSet().AddRow(lIDFooter2, "Text", "", 10, 105, 19, 23, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmallSmall, FW_NORMAL, 0, 0, 0, 0);
				long lIDRiga2Dx = CElemReportSet().AddRow(lIDFooter2, "Text", "", 110, 205, 19, 23, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmallSmall, FW_NORMAL, 0, 0, 0, 0);
				long lIDRiga3Sx = CElemReportSet().AddRow(lIDFooter2, "Text", "", 10, 105, 23, 27, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmallSmall, FW_NORMAL, 0, 0, 0, 0);
				long lIDRiga3Dx = CElemReportSet().AddRow(lIDFooter2, "Text", "", 110, 205, 23, 27, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmallSmall, FW_NORMAL, 0, 0, 0, 0);

				CElemReportSet().AddRow(lIDFooter2, "PageNum", "PageNum", 176, 186, 33, 37, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmall, FW_NORMAL, 0, 0, 2, 0);
				CElemReportSet().AddRow(lIDFooter2, "Text", "/", 186, 190, 33, 37, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmall, FW_NORMAL, 0, 0, 1, 0);
				CElemReportSet().AddRow(lIDFooter2, "PageTot", "PageTot", 190, 200, 33, 37, 1, 0, 0, pForm->m_sFontName, 34, pForm->m_lFontHeightSmall, FW_NORMAL, 0, 0, 0, 0);

				//

				CStringList listReferti;

				for (int i = 0; i < pResponse->iNumeroLaudos; i++)
				{
					DeleteFile(sSignatureFile);

					CString sRodape(pResponse->laudos[i].szRodapeRtf);
					sRodape.Trim();

					CString sRiga123Rtf = "";
					CString sRiga1Sx = "";
					CString sRiga1Dx = "";
					CString sRiga2Sx = "";
					CString sRiga2Dx = "";
					CString sRiga3Sx = "";
					CString sRiga3Dx = "";

					if (!sRodape.IsEmpty())
					{
						if (sRodape.Left(5).CompareNoCase("{\rtf") == 0)
						{
							// è un rtf //
							sRiga123Rtf = sRodape;
						}
						else
						{
							/* #ifdef _DEBUG
							sRodape = "ASD^ASD^ASD^|PROVA^PROVA^PROVA^|";
							#endif */

							long lBarra1 = sRodape.Find("|");
							long lBarra2 = sRodape.Find("|", lBarra1 + 1);

							CString sSx = "";
							CString sDx = "";

							if (lBarra1 == 0)
							{
								if (lBarra2 > 0)
									sDx = sRodape.Mid(1, lBarra2 - 1);
								else
									sDx = sRodape.Mid(1);
							}
							else if (lBarra1 > 0)
							{
								sSx = sRodape.Left(lBarra1);

								if (lBarra2 > 0)
									sDx = sRodape.Mid(lBarra1 + 1, lBarra2 - (lBarra1 + 1));
								else
									sDx = sRodape.Mid(lBarra1 + 1);
							}

							if (!sSx.IsEmpty())
							{
								long lCappe1 = sSx.Find("^");
								long lCappe2 = sSx.Find("^", lCappe1 + 1);
								long lCappe3 = sSx.Find("^", lCappe2 + 1);

								if (lCappe1 > 0)
								{
									sRiga1Sx = sSx.Left(lCappe1);

									if (lCappe2 > 0)
									{
										sRiga2Sx = sSx.Mid(lCappe1 + 1, lCappe2 - (lCappe1 + 1));

										if (lCappe3 > 0)
											sRiga3Sx = sSx.Mid(lCappe2 + 1, lCappe3 - (lCappe2 + 1));
										else
											sRiga3Sx = sSx.Mid(lCappe2 + 1);
									}
									else
									{
										sRiga2Sx = sSx.Mid(lCappe1 + 1);
									}
								}
								else
								{
									sRiga1Sx = sSx;
								}
							}

							if (!sDx.IsEmpty())
							{
								long lCappe1 = sDx.Find("^");
								long lCappe2 = sDx.Find("^", lCappe1 + 1);
								long lCappe3 = sDx.Find("^", lCappe2 + 1);

								if (lCappe1 > 0)
								{
									sRiga1Dx = sDx.Left(lCappe1);

									if (lCappe2 > 0)
									{
										sRiga2Dx = sDx.Mid(lCappe1 + 1, lCappe2 - (lCappe1 + 1));

										if (lCappe3 > 0)
											sRiga3Dx = sDx.Mid(lCappe2 + 1, lCappe3 - (lCappe2 + 1));
										else
											sRiga3Dx = sDx.Mid(lCappe2 + 1);
									}
									else
									{
										sRiga2Dx = sDx.Mid(lCappe1 + 1);
									}
								}
								else
								{
									sRiga1Dx = sDx;
								}
							}
						}
					}

					CElemReportSet().EdtRow(lIDRiga123Rtf, sRiga123Rtf);
					CElemReportSet().EdtRow(lIDRiga1Sx, sRiga1Sx);
					CElemReportSet().EdtRow(lIDRiga1Dx, sRiga1Dx);
					CElemReportSet().EdtRow(lIDRiga2Sx, sRiga2Sx);
					CElemReportSet().EdtRow(lIDRiga2Dx, sRiga2Dx);
					CElemReportSet().EdtRow(lIDRiga3Sx, sRiga3Sx);
					CElemReportSet().EdtRow(lIDRiga3Dx, sRiga3Dx);

					//

					CString sImmagineFirmaOriginale = CString(pResponse->laudos[i].szRubrica);
					if (sImmagineFirmaOriginale.GetLength() > 0)
					{
						BOOL bOK = TRUE;

						BYTE* pImmagineFirmaOriginaleBuffer = NULL;
						DWORD dwImmaginefirmaOriginaleBufferLength = 0;

						// decodifico quello che ricevo da amremote in base64 //

						if (bOK)
						{
							bOK = FALSE;

							LPTSTR pImmagineFirmaOriginale = sImmagineFirmaOriginale.GetBuffer(sImmagineFirmaOriginale.GetLength());
							UINT iImmagineFirmaOriginaleSize = AmBase64_CalculateRequiredDecodeOutputBufferSize(pImmagineFirmaOriginale);
							pImmagineFirmaOriginaleBuffer = new BYTE[iImmagineFirmaOriginaleSize];
							dwImmaginefirmaOriginaleBufferLength = iImmagineFirmaOriginaleSize;
							bOK = (AmBase64_DecodeBuffer(pImmagineFirmaOriginale, sImmagineFirmaOriginale.GetLength(), (TCHAR*)pImmagineFirmaOriginaleBuffer) > 0);
							sImmagineFirmaOriginale.ReleaseBuffer();
						}

						// salvo su file quello che ho appena decodificato //

						if (bOK && (pImmagineFirmaOriginaleBuffer != NULL) && (dwImmaginefirmaOriginaleBufferLength > 0))
						{
							bOK = FALSE;

							HANDLE hFileXXX = CreateFile(sSignatureFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
							if (hFileXXX != INVALID_HANDLE_VALUE)
							{
								DWORD dwBytesWrite;
								bOK = WriteFile(hFileXXX, pImmagineFirmaOriginaleBuffer, dwImmaginefirmaOriginaleBufferLength, &dwBytesWrite, NULL);
							}
							CloseHandle(hFileXXX);
						}

						/* riapro con le gdiplus il file appena salvato e lo salvo di nuovo in formato bmp //
						if (bOK)
						{
							bOK = FALSE;

							USES_CONVERSION;
							Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)Gdiplus::Bitmap::FromFile(A2W(strFileTmp));
							if (pBitmap->GetLastStatus() == Gdiplus::Ok)
							{
								CLSID idClass;
								if (GetEncoderClsid(L"image/bmp", &idClass))
								bOK = (pBitmap->Save(T2W(strFileBmp), &idClass, NULL) == Gdiplus::Ok);

								delete pBitmap;
							}
						}
						*/

						if (pImmagineFirmaOriginaleBuffer != NULL)
							delete pImmagineFirmaOriginaleBuffer;
					}

					//

					CString sFilePdf = pForm->m_pEsamiView->CreateHaruPdfCentraleStampaFile(lIDHeader, lIDFooter1, lIDFooter2, pResponse->laudos[i].szCorpoRtf);
					if (!sFilePdf.IsEmpty())
						listReferti.AddTail(sFilePdf);

					DeleteFile(sSignatureFile);
				}
				delete pResponse;

				//

				if (listReferti.GetCount() > 0)
				{
					SYSTEMTIME timeLocal;
					::GetLocalTime(&timeLocal);

					CString sFinalFileName;
					sFinalFileName.Format("%s\\%04d%02d%02d%02d%02d%02d.pdf", theApp.m_sDirTemp, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond);

					// accorpo tutto all'interno di un unico grande pdf e ne lancio la stampa //

					if (CPdfUtilInterface::Get()->Merge(&listReferti, sFinalFileName))
						pForm->VaiConLaStampa(sFinalFileName);

					// cancello i file dei "pdf singoli" //

					POSITION posTmp = listReferti.GetHeadPosition();
					while (posTmp != NULL)
						DeleteFile(listReferti.GetNext(posTmp));

					// cancello il file del "pdf cumulativo" //

					DeleteFile(sFinalFileName);
				}

			}
		}

		CHeaderFooterSet().DelRow(lIDHeader);
		CHeaderFooterSet().DelRow(lIDFooter1);
		CHeaderFooterSet().DelRow(lIDFooter2);
	}

	//

	pForm->PostMessage(EPM_PRINTINGTHREADENDED);
	return 0;
}

LRESULT CCentraleDiStampaDynForm::OnCheckValue(WPARAM wParam, LPARAM lParam)
{
	OnBnClickedBtnConferma();
	return 1;
}

LRESULT CCentraleDiStampaDynForm::OnPrintingThreadEnded(WPARAM wParam, LPARAM lParam)
{
	if (m_sError.GetLength() > 0)
	{
		if (m_sError.GetLength() > 25)
		{
			m_ctrlList2.InsertItem(0, "");
			m_ctrlList2.SetItemText(0, 1, "");
			m_ctrlList2.SetItemText(0, 2, m_sError.Mid(25));			

			m_ctrlList2.InsertItem(0, "");
			m_ctrlList2.SetItemText(0, 1, "");
			m_ctrlList2.SetItemText(0, 2, m_sError.Mid(0, 25));
			m_sError = "";
		}
		else
		{
			m_ctrlList2.InsertItem(0, "");
			m_ctrlList2.SetItemText(0, 1, "");
			m_ctrlList2.SetItemText(0, 2, m_sError);
			m_sError = "";
		}		
	}	
	m_ctrlList2.InsertItem(0, "");
	m_ctrlList2.SetItemText(0, 1, CTime::GetCurrentTime().Format("%H:%M:%S"));
	m_ctrlList2.SetItemText(0, 2, m_sPrintingFicha);

	m_sPrintingFicha = "";
	m_ctrlStaticPrinting2.SetWindowText("");

	GetDlgItem(IDC_STATIC_PRINTING1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PRINTING2)->ShowWindow(SW_HIDE);

	m_bThreadAlreadyGoing = FALSE;
	SetTimer(0xeda, 5000, NULL);

	m_pEsamiView->m_bPrinting = (m_ctrlList1.GetItemCount() > 0);

	return 0;
}

BOOL CCentraleDiStampaDynForm::RecuperaDatiUnita(CString sUnita, long lIDHeader, long lIDFooter1, long lIDFooter2, CString &sIDMarca)
{
	BOOL bReturn = FALSE;

	unidadeRequest request;
	sprintf(request.szCodigoUnidade, "%s", sUnita);

	CPrintService printService(theApp.m_sHttpServerRichiestaUnidade, theApp.m_sHttpServerRichiestaLaudos);
	unidadeResponse response = printService.GetUnidade(request);

	CString sError(response.szError);
	sError.Trim();
	if (sError.IsEmpty() || (sError.Compare("0") == 0))
	{
		// immagine della carta intestata nell'header e nei footer //

		if (!m_bUtilizzaCartaIntestata)
		{
			CElemReportSet().AddRow(lIDHeader, "Icon", response.szUrlCabecalho, 0, 210, 0, 25, 1, 0, 0, m_sFontName, 34, m_lFontHeightSmall, FW_NORMAL, 0, 0, 0, 0);

			CElemReportSet().AddRow(lIDFooter1, "Icon", response.szUrlRodape, 0, 210, 40, 65, 1, 0, 0, m_sFontName, 34, m_lFontHeightSmall, FW_NORMAL, 0, 0, 0, 0);
			CElemReportSet().AddRow(lIDFooter2, "Icon", response.szUrlRodape, 0, 210, 40, 65, 1, 0, 0, m_sFontName, 34, m_lFontHeightSmall, FW_NORMAL, 0, 0, 0, 0);
		}

		//

		CString sTeemp;

		sTeemp = CString(response.szRazaoSocial) + " - " + CString(response.szCRM) + " - " + CString(response.szDescricaoAnvisa);
		sTeemp.Trim();
		while (sTeemp.Find("  ") > 0)
			sTeemp.Replace("  ", " ");
		while (sTeemp.Find("- -") > 0)
			sTeemp.Replace("- -", "-");
		CElemReportSet().AddRow(lIDFooter2, "Text", sTeemp, 10, 205, 37, 41, 1, 0, 0, m_sFontName, 34, m_lFontHeightSmallSmall, FW_NORMAL, 0, 0, 0, 0);

		sTeemp = CString(response.szLogradouro) + " " + CString(response.szNumero) + " - " + CString(response.szCEP) + " - " + CString(response.szBairro) + " - " + CString(response.szMunicipio) + " - " + CString(response.szUF) + " - " + "BRASIL";
		sTeemp.Trim();
		while (sTeemp.Find("  ") > 0)
			sTeemp.Replace("  ", " ");
		while (sTeemp.Find("- -") > 0)
			sTeemp.Replace("- -", "-");
		CElemReportSet().AddRow(lIDFooter2, "Text", sTeemp, 10, 205, 41, 45, 1, 0, 0, m_sFontName, 34, m_lFontHeightSmallSmall, FW_NORMAL, 0, 0, 1, 0);

		//

		sIDMarca.Format("%s", response.szIDMarca);

		//

		bReturn = TRUE;
	}
	else
	{
// #ifndef _DEBUG
		CString sMessageError;
		sMessageError.Format(theApp.GetMessageString(IDS_ERROREUNIDADEREQUEST) + " (" + CString(request.szCodigoUnidade) + ")\r\n\r\n" + sError);
		theApp.AfxMessageBoxEndo(sMessageError);
// #endif
	}

	return bReturn;
}

obterLaudoResponse* CCentraleDiStampaDynForm::RecuperaDatiReferti(CString sIDMarca, CString sFicha, CString sUtente)
{
	obterLaudoResponse* pResponse = NULL;

	obterLaudoRequest request;
	sprintf(request.szIDMarca, "%s", sIDMarca);
	sprintf(request.szFicha, "%s", sFicha);
	sprintf(request.szItensIgnorados, "%s", "");
	sprintf(request.szSiglaUsuarioSistema, "%s", sUtente);
	sprintf(request.szIDSistema, "%li", 1);

	CPrintService printService(theApp.m_sHttpServerRichiestaUnidade, theApp.m_sHttpServerRichiestaLaudos);
	pResponse = printService.GetLaudos(request);
	if (pResponse != NULL)
	{
		CString sError(pResponse->szError);
		sError.Trim();
		if (!sError.IsEmpty() && (sError.Compare("0") != 0))
		{
			CString sMessageError;
			sMessageError.Format(theApp.GetMessageString(IDS_ERROREOBTERLAUDOREQUEST) + " (" + CString(request.szFicha) + ")\r\n\r\n" + sError);
			//theApp.AfxMessageBoxEndo(sMessageError);
		}
	}
	else
	{
		CString sMessageError;
		sMessageError.Format(theApp.GetMessageString(IDS_ERROREOBTERLAUDOREQUEST) + " (" + CString(request.szFicha) + ")");
		//theApp.AfxMessageBoxEndo(sMessageError);
	}

	return pResponse;
}

void CCentraleDiStampaDynForm::VaiConLaStampa(CString sFileDaStampare)
{
	char szProcess[1024];
	sprintf_s(szProcess, "\"%s\\xPdfPrint.exe\" -f:\"%s\"", theApp.m_sDirProg, sFileDaStampare);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		LPVOID lpMsgBuf;
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
			theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
		else
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
		LocalFree(lpMsgBuf);
	}
	else
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}