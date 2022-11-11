#include "stdafx.h"
#include "Endox.h"
#include "ArchivioStampeDlg.h"

#include <io.h>

#include "DLL_Imaging\h\AmDes.h"
#include "DLL_Imaging\h\AmLogin.h"
#include "DLL_Imaging\h\AmSumatraPdfViewer.h"
#include "DLL_Imaging\h\AmTesiSign.h"

#include "DigitalSignUtil.h"
#include "EsamiView.h"
#include "MotivoDlg.h"
#include "MediciSet.h"
#include "PasswordDlg.h"
#include "PdfAnteprimaDlg.h"
#include "PdfManager.h"
#include "PdfStampaDlg.h"
#include "SmartCardPinDlg.h"
#include "VitalSignModificaNoteDlg.h"
#include "VitalSignMisurazioniHeaderSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CArchivioStampeDlg, CEndoxResizableDlg)

CArchivioStampeDlg::CArchivioStampeDlg(CWnd* pParentWnd, CEsamiView* pEsamiView, CList<tagPDFVIEW>* pPdfView, LPCTSTR szTitle, BOOL bShowLeftList)
	: CEndoxResizableDlg(CArchivioStampeDlg::IDD, pParentWnd)
{
	m_pEsamiView = pEsamiView;
	m_pListPDF = pPdfView;
	m_strTitle = szTitle;
	m_bShowLeftList = bShowLeftList;

	//

	m_pBufferPdf = NULL;
	m_uiTemp = 0;
}

CArchivioStampeDlg::~CArchivioStampeDlg()
{
}

BEGIN_MESSAGE_MAP(CArchivioStampeDlg, CEndoxResizableDlg)

	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_BTN_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnButtonExport)
	ON_BN_CLICKED(IDC_BTN_MAIL, OnButtonMail)
	ON_BN_CLICKED(IDC_BTN_ANNULLA, OnButtonAnnullaPDF)
	ON_BN_CLICKED(IDC_BTN_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BTN_FIRMASELEZIONATO, OnButtonFirmaSelezionato)
	ON_BN_CLICKED(IDC_BTN_FIRMATUTTI, OnButtonFirmaTutti)

	ON_BN_CLICKED(IDC_BTN_PAGE_PREC, OnButtonPagePrec)
	ON_BN_CLICKED(IDC_BTN_PAGE_PREC_FULL, OnButtonPagePrec)
	ON_BN_CLICKED(IDC_BTN_PAGE_SUCC, OnButtonPageSucc)
	ON_BN_CLICKED(IDC_BTN_PAGE_SUCC_FULL, OnButtonPageSucc)
	ON_BN_CLICKED(IDC_BTN_ZOOM_IN, OnButtonZoomIn)
	ON_BN_CLICKED(IDC_BTN_ZOOM_IN_FULL, OnButtonZoomIn)
	ON_BN_CLICKED(IDC_BTN_ZOOM_OUT, OnButtonZoomOut)
	ON_BN_CLICKED(IDC_BTN_ZOOM_OUT_FULL, OnButtonZoomOut)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnListSelchange) 

	ON_BN_CLICKED(IDC_BTN_MODIFICANOTE_VS, &CArchivioStampeDlg::OnBnClickedBtnModificanoteVs)
END_MESSAGE_MAP()

void CArchivioStampeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_PRINT, m_ctrlBtnPrint);
	DDX_Control(pDX, IDC_BTN_EXPORT, m_ctrlBtnExport);
	DDX_Control(pDX, IDC_BTN_MAIL, m_ctrlBtnMail);
	DDX_Control(pDX, IDC_BTN_MODIFICANOTE_VS, m_ctrlBtnModificaNoteVS);
	DDX_Control(pDX, IDC_BTN_ANNULLA, m_ctrlBtnAnnullaPDF);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnEliminaPdf);
	DDX_Control(pDX, IDC_BTN_FIRMASELEZIONATO, m_ctrlBtnFirmaSelezionato);
	DDX_Control(pDX, IDC_BTN_FIRMATUTTI, m_ctrlBtnFirmaTutti);

	DDX_Control(pDX, IDC_BTN_PAGE_PREC, m_ctrlBtnPagePrec);
	DDX_Control(pDX, IDC_BTN_PAGE_PREC_FULL, m_ctrlBtnPagePrecFull);
	DDX_Control(pDX, IDC_BTN_PAGE_SUCC, m_ctrlBtnPageSucc);
	DDX_Control(pDX, IDC_BTN_PAGE_SUCC_FULL, m_ctrlBtnPageSuccFull);
	DDX_Control(pDX, IDC_BTN_ZOOM_IN, m_ctrlBtnZoomIn);
	DDX_Control(pDX, IDC_BTN_ZOOM_IN_FULL, m_ctrlBtnZoomInFull);
	DDX_Control(pDX, IDC_BTN_ZOOM_OUT, m_ctrlBtnZoomOut);
	DDX_Control(pDX, IDC_BTN_ZOOM_OUT_FULL, m_ctrlBtnZoomOutFull);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

BOOL CArchivioStampeDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	if (m_bShowLeftList)
	{
		//Se devo mostrare la lista dei pdf, e quindi altri pulsanti, devo spostare questo alla destra di elimina
		if (theApp.m_bVitalSignIntegrazioneAttiva)
		{
			CRect eliminaRect, mailRect;
			m_ctrlBtnEliminaPdf.GetWindowRect(&eliminaRect);
			m_ctrlBtnMail.GetWindowRect(&mailRect);
			ScreenToClient(&eliminaRect);
			ScreenToClient(&mailRect);
			m_ctrlBtnModificaNoteVS.SetWindowPos(NULL, eliminaRect.right + (eliminaRect.left - mailRect.right), eliminaRect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		}
	}

	AddAnchor(IDC_LIST, CSize(0, 0), CSize(0, 100));
	AddAnchor(IDC_PLACE, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_PLACE_FULL, CSize(0, 0), CSize(100, 100));

	AddAnchor(IDC_BTN_PRINT, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_EXPORT, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_MAIL, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_MODIFICANOTE_VS, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_ANNULLA, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_DEL, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_FIRMASELEZIONATO, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_FIRMATUTTI, CSize(0, 100), CSize(0, 100));

	AddAnchor(IDC_BTN_PAGE_PREC, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_BTN_PAGE_PREC_FULL, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_PAGE, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_PAGE_FULL, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_BTN_PAGE_SUCC, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_BTN_PAGE_SUCC_FULL, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_LINE, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_LINE_FULL, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_BTN_ZOOM_IN, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_BTN_ZOOM_IN_FULL, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_ZOOM, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_STATIC_ZOOM_FULL, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_BTN_ZOOM_OUT, CSize(50, 100), CSize(50, 100));
	AddAnchor(IDC_BTN_ZOOM_OUT_FULL, CSize(50, 100), CSize(50, 100));

	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));

	if (m_bShowLeftList)
	{
		m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
		m_ctrlList.InsertColumn(0, "");
		m_ctrlList.InsertColumn(1, "");
		m_ctrlList.SetColumnWidth(0, 296);
		m_ctrlList.SetColumnWidth(1, 136);

		GetDlgItem(IDC_PLACE)->ShowWindow(SW_SHOW);
		m_uiTemp = PdfViewer_Initialize(GetDlgItem(IDC_PLACE)->GetSafeHwnd());

		GetDlgItem(IDC_BTN_PAGE_PREC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PAGE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_PAGE_SUCC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LINE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_ZOOM_IN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ZOOM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_ZOOM_OUT)->ShowWindow(SW_SHOW);
	
		m_ctrlBtnMail.ShowWindow(SW_SHOW);

	}
	else
	{
		m_ctrlList.ShowWindow(SW_HIDE);

		GetDlgItem(IDC_PLACE_FULL)->ShowWindow(SW_SHOW);
		m_uiTemp = PdfViewer_Initialize(GetDlgItem(IDC_PLACE_FULL)->GetSafeHwnd());

		GetDlgItem(IDC_BTN_PAGE_PREC_FULL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PAGE_FULL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_PAGE_SUCC_FULL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_LINE_FULL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_ZOOM_IN_FULL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ZOOM_FULL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_ZOOM_OUT_FULL)->ShowWindow(SW_SHOW);

		m_ctrlBtnMail.ShowWindow(SW_HIDE);
	}

	int nIndex = 0;
	POSITION pos = m_pListPDF->GetHeadPosition();
	while(pos != NULL)
	{
		tagPDFVIEW pdf = m_pListPDF->GetAt(pos);

		m_ctrlList.InsertItem(nIndex, pdf.szNote);
		m_ctrlList.SetItemData(nIndex, pdf.lID);

		m_ctrlList.SetItemText(nIndex, 1, pdf.szData);

		nIndex++;
		m_pListPDF->GetNext(pos);
	}

	if (m_ctrlList.GetItemCount() > 0)
	{
		m_ctrlList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
		ViewPdf();
	}

	//
	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	//
	theApp.LocalizeDialog(this, CArchivioStampeDlg::IDD, "ArchivioStampe");
	SetWindowText(m_strTitle);

	//
	return TRUE;
}

void CArchivioStampeDlg::OnButtonAnnullaPDF()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		// chiudo il dialog per procedere con l'annullamento del documento //
		EndDialog(0x333);
	}
}

void CArchivioStampeDlg::OnButtonDel()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlList.GetNextSelectedItem(pos);
		tagPDFVIEW tagTemp = m_pListPDF->GetAt(m_pListPDF->FindIndex(iCurSel));

		// chiedo la password //

		if (CPasswordDlg(this, theApp.GetMessageString(IDS_PASSWORD_PDFELIMINA), theApp.m_sPdfEliminazionePassword).DoModal() == IDOK)
		{
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ELIMINARE_PDF), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				if (AmPdfManager_SetPdfEliminato(tagTemp.lID, m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer))
				{
					m_ctrlList.DeleteItem(iCurSel);
					m_pListPDF->RemoveAt(m_pListPDF->FindIndex(iCurSel));
				}
			}
		}
	}
}

void CArchivioStampeDlg::OnButtonExport()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (!pos)
		return;

	int iCurSel = m_ctrlList.GetNextSelectedItem(pos);

	CString strPdfArchive = m_pListPDF->GetAt(m_pListPDF->FindIndex(iCurSel)).szFile;

	CString strExtension;
	for(int i = strPdfArchive.GetLength() - 1; i >= 0; i--)
	{
		if (strPdfArchive.GetAt(i) == '\\')
		{
			for(int j = i + 1; j < strPdfArchive.GetLength(); j++)
			{
				if (strPdfArchive.GetAt(j) == '.')
				{
					strExtension = strPdfArchive.Mid(j + 1, strPdfArchive.GetLength() - j - 1);
					break;
				}
			}
			break;
		}
	}

	CFileDialog dlg(FALSE, NULL, NULL, OFN_LONGNAMES | OFN_FILEMUSTEXIST, "File PDF (*.pdf)|*.pdf|File P7M (*.p7m)|*.p7m||", this, 0, FALSE);
	if (dlg.DoModal() == IDOK)
	{
		if (POSITION pos = dlg.GetStartPosition())
		{
			CString strFile = dlg.GetNextPathName(pos);
			strFile.MakeUpper();
			if (strFile.Right(3) == "PDF")
				strFile = strFile.Left(strFile.GetLength() - 3);
			if (strFile.Right(1) != ".")
				strFile += ".";
			strFile += strExtension;

			::CopyFile(strPdfArchive, strFile, FALSE);
		}
	}
}

void CArchivioStampeDlg::OnButtonMail()
{
	BeginWaitCursor();

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlList.GetNextSelectedItem(pos);

		//
		CString strPdfArchive = m_pListPDF->GetAt(m_pListPDF->FindIndex(iCurSel)).szFile;

		// Sandro 04/12/2014 // RAS 20140100 // rinomino i P7M in "semplici" PDF //
		if (strPdfArchive.GetLength() > 4)
		{
			if (strPdfArchive.Right(3).CompareNoCase("p7m") == 0)
			{
				int nBackslash = strPdfArchive.ReverseFind('\\');

				CString sNewFileName = theApp.m_sDirTemp + strPdfArchive.Mid(nBackslash, strPdfArchive.GetLength() - nBackslash - 4); // con il -4 tolgo anche l'estensione .P7M

				if (CopyFile(strPdfArchive, sNewFileName, FALSE))
					strPdfArchive = sNewFileName;
			}
		}

		//
		WritePrivateProfileString("Settings", "MailDest", "mail", theApp.m_sDirProg + "\\MailSender.cfg");
		// WritePrivateProfileString("Settings", "MailSender", "", theApp.m_sDirProg + "\\MailSender.cfg");
		WritePrivateProfileString("Settings", "Modality", "", theApp.m_sDirProg + "\\MailSender.cfg");
		WritePrivateProfileString("Settings", "Object", m_pEsamiView->m_pPazientiSet->m_sCognome + " " + m_pEsamiView->m_pPazientiSet->m_sNome, theApp.m_sDirProg + "\\MailSender.cfg");
		WritePrivateProfileString("Settings", "TempPath", theApp.m_sDirTemp, theApp.m_sDirProg + "\\MailSender.cfg");

		WritePrivateProfileInt("Settings", "AttachmentNumber", 1, theApp.m_sDirProg + "\\MailSender.cfg");
		WritePrivateProfileString("Settings", "Attachment1", strPdfArchive, theApp.m_sDirProg + "\\MailSender.cfg");

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		TCHAR szProcess[255];
		sprintf_s(szProcess, "%s\\MailSender.exe", theApp.m_sDirProg);

		if (CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
	}

	EndWaitCursor();
}

void CArchivioStampeDlg::OnButtonPrint()
{
	BOOL bStampa = TRUE;

	CString sMessaggio = "";
	if (theApp.m_bPersonalizzazioniBrasileFleury)
		bStampa = FleuryPossoStampare(sMessaggio, m_pEsamiView->m_pEsamiSet->m_sRicovero, m_pEsamiView->m_pEsamiSet->m_sCodEsame);

	if (!bStampa)
	{
		theApp.AfxMessageBoxEndo(sMessaggio);
		return;
	}

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlList.GetNextSelectedItem(pos);

		tagPDFVIEW tagTemp = m_pListPDF->GetAt(m_pListPDF->FindIndex(iCurSel));

		// PdfViewer_Print(tagTemp.szFile, NULL, NULL, 0, tagTemp.bFitToPage);

		PdfViewer_Close(m_uiTemp);
		PdfViewer_Finalize(m_uiTemp);

		if (m_pBufferPdf)
			delete m_pBufferPdf;
		m_pBufferPdf = NULL;

		CPdfStampaDlg printDlg(this, tagTemp.szNote, tagTemp.szFile, tagTemp.bCriptato, Printer_ChiediStampante, 0, tagTemp.bFitToPage);
		printDlg.DoModal();

		if (m_bShowLeftList)
			m_uiTemp = PdfViewer_Initialize(GetDlgItem(IDC_PLACE)->GetSafeHwnd());
		else
			m_uiTemp = PdfViewer_Initialize(GetDlgItem(IDC_PLACE_FULL)->GetSafeHwnd());

		if (tagTemp.bCriptato)
		{
			DWORD dwBufferSize = 0;
			if (CDigitalSignUtil::DecryptPdf(tagTemp.szFile, &m_pBufferPdf, &dwBufferSize))
				PdfViewer_LoadFromBuffer(m_uiTemp, m_pBufferPdf, dwBufferSize);
		}
		else
		{
			PdfViewer_Load(m_uiTemp, tagTemp.szFile);
		}

		PdfViewer_SetCurrentZoom(m_uiTemp, CPdfAnteprimaDlg::m_lDefaultZoomValue);

		CString strPage;
		strPage.Format("%li/%li", PdfViewer_GetCurrentPage(m_uiTemp) + 1, PdfViewer_GetNumberOfPages(m_uiTemp));
		SetDlgItemText(IDC_STATIC_PAGE, strPage);
		SetDlgItemText(IDC_STATIC_PAGE_FULL, strPage);

		CString strZoom;
		strZoom.Format("%li%%", PdfViewer_GetCurrentZoom(m_uiTemp));
		SetDlgItemText(IDC_STATIC_ZOOM, strZoom);
		SetDlgItemText(IDC_STATIC_ZOOM_FULL, strZoom);
	}
}

void CArchivioStampeDlg::OnButtonFirmaSelezionato()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			tagPDFVIEW tagTemp = m_pListPDF->GetAt(m_pListPDF->FindIndex(nCurSel));
			if (!tagTemp.bFirmato)
			{
				theApp.m_sSmartCardPin = "";

				if (AmTesiSign_Initialize() != NoError)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_1), MB_ICONSTOP);
					return;
				}

				if (AmTesiSign_ReadSmartCard() != NoError)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_2), MB_ICONSTOP);
					AmTesiSign_Finalize();
					return;
				}

				// Sandro 01/03/2013 //
				INT_PTR iReturn = IDCANCEL;
				CSmartCardPinDlg dlg(this);
				do
				{
					iReturn = dlg.DoModal();
					if (iReturn == IDCANCEL)
						break;
				} while (AmTesiSign_ReadCertificate(dlg.m_strPin) != NoError);

				if (iReturn == IDCANCEL)
				{
					AmTesiSign_Finalize();
					return;
				}

				theApp.m_sSmartCardPin = dlg.m_strPin;

				// Sandro 27/02/2013 // controllo che il codice fiscale estratto dalla smartcard sia presente nella tabella EMedici //

				long lConteggioMedici = 0;

				AmTesiSign_SMARTCARDDATA scData;
				AmTesiSign_GetSmartCardData(&scData);

				CString sCodiceFiscaleSmartCard = scData.szUserFiscalCode;
				sCodiceFiscaleSmartCard.MakeUpper();
				sCodiceFiscaleSmartCard.Trim();

				CString sFilter;
				sFilter.Format("CodiceFiscale='%s'", sCodiceFiscaleSmartCard);

				CMediciSet setMedici;
				setMedici.SetOpenFilter(sFilter);
				if (setMedici.OpenRecordset("CPDFCreator::SaveSignedPdfFileIntoRepository"))
				{
					while (!setMedici.IsEOF())
					{
						lConteggioMedici++;
						setMedici.MoveNext();
					}

					setMedici.CloseRecordset("CPDFCreator::SaveSignedPdfFileIntoRepository");
				}

				if (lConteggioMedici < 1)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_09), MB_ICONSTOP);
					// DeleteFile(*pStrFile);
					return; //  FALSE;
				}

				if (lConteggioMedici > 1)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_10), MB_ICONSTOP);
					// DeleteFile(*pStrFile);
					return; //  FALSE;
				}

				// Sandro 29/10/2014 // RAS 20140089 //
				if (theApp.m_bFirmaDigitaleSmartcardUgualeMedico1)
				{
					// controllo se il codice fiscale della smartcard corrisponde a quello del medico che ha fatto l'esame //

					BOOL bOK = FALSE;

					if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lMedico) && (m_pEsamiView->m_pEsamiSet->m_lMedico > 0))
					{
						CString sCodiceFiscaleMedico = CMediciSet().GetCodiceFiscaleFromContatore(m_pEsamiView->m_pEsamiSet->m_lMedico);
						sCodiceFiscaleMedico.Trim();

						if (sCodiceFiscaleMedico.GetLength() > 0)
							if (sCodiceFiscaleSmartCard.CompareNoCase(sCodiceFiscaleMedico) == 0)
								bOK = TRUE;
					}

					if (!bOK)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_11), MB_ICONSTOP);
						// DeleteFile(*pStrFile);
						return; // FALSE;
					}
				}

				// Sandro 29/10/2014 // RAS 20140089 //
				if (theApp.m_bFirmaDigitaleSmartcardUgualeUtenteEndox)
				{
					// controllo se il codice fiscale della smartcard corrisponde a quello dell'utente attualmente loggato in Endox //

					BOOL bOK = FALSE;

					long lUserID;
					AMLogin_GetUserID(&lUserID);

					CString sCodiceFiscaleUtente = CMediciSet().GetCodiceFiscaleFromUserID(lUserID);
					sCodiceFiscaleUtente.Trim();

					if (sCodiceFiscaleUtente.GetLength() > 0)
						if (sCodiceFiscaleSmartCard.CompareNoCase(sCodiceFiscaleUtente) == 0)
							bOK = TRUE;

					if (!bOK)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_12), MB_ICONSTOP);
						// DeleteFile(*pStrFile);
						return; // FALSE;
					}
				}

				// aggiungo firma digitale al PDF... //
				if (AmTesiSign_SignFile(tagTemp.szFile, theApp.m_sSmartCardPin) != NoError)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_3), MB_ICONSTOP);
					// DeleteFile(*pStrFile);
					return; // FALSE;
				}

				if (_access(CString(tagTemp.szFile) + ".p7m", 00) != 0)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_4), MB_ICONSTOP);
					AmTesiSign_Finalize();
					return; // FALSE;
				}
				else
				{
					// cancello PDF non firmato... //
					// DeleteFile(*pStrFile);
				}

				// importo su archivio... //
				CString sSmartCardUtente = "";
				CDigitalSignUtil::GetSmartCardUtente(&sSmartCardUtente);

				CString sSmartCardNumero = "";
				CDigitalSignUtil::GetSmartCardNumero(&sSmartCardNumero);

				CString sSmartCardEnteCertificato = "";
				CDigitalSignUtil::GetSmartCardEnteCertificato(&sSmartCardEnteCertificato);

				CPdfManager PdfManager;
				if (PdfManager.IsInitialize())
				{
					// Sandro 16/03/2015 //
					// non togliere le note, serve per visualizzare nelle liste il nome del report da cui è stato generato il PDF //
					if (PdfManager.UpdatePdfToFirmato(tagTemp.lID, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, sSmartCardUtente, sSmartCardNumero, sSmartCardEnteCertificato))
					{
						tagTemp.ptTipo = pdftype_report_allegato;
						tagTemp.bFirmato = TRUE;
						// tagTemp.bCriptato;
						// tagTemp.szFile[MAX_PATH];

						m_pListPDF->SetAt(m_pListPDF->FindIndex(nCurSel), tagTemp);

						CString sTemp = m_ctrlList.GetItemText(nCurSel, 0);
						sTemp = theApp.GetMessageString(IDS_PDF_TYPE_8) + " - " + sTemp;
						m_ctrlList.SetItemText(nCurSel, 0, sTemp);
					}
				}
			}
		}
	}

	AmTesiSign_Finalize();

	// Sandro 12/03/2015 // se c'è anche un solo PDF non firmato faccio comparire il tasto "firma tutti" //
	int nCmdShow = SW_HIDE;
	if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
	{
		POSITION pos = m_pListPDF->GetHeadPosition();
		while (pos != NULL)
		{
			tagPDFVIEW tagTemp = m_pListPDF->GetAt(pos);

			if (!tagTemp.bFirmato)
			{
				nCmdShow = SW_SHOW;
				break;
			}

			m_pListPDF->GetNext(pos);
		}
	}
	m_ctrlBtnFirmaTutti.ShowWindow(nCmdShow);
}

void CArchivioStampeDlg::OnButtonFirmaTutti()
{
	theApp.m_sSmartCardPin = "";

	if (AmTesiSign_Initialize() != NoError)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_1), MB_ICONSTOP);
		return;
	}

	if (AmTesiSign_ReadSmartCard() != NoError)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_2), MB_ICONSTOP);
		AmTesiSign_Finalize();
		return;
	}

	// Sandro 01/03/2013 //
	INT_PTR iReturn = IDCANCEL;
	CSmartCardPinDlg dlg(this);
	do
	{
		iReturn = dlg.DoModal();
		if (iReturn == IDCANCEL)
			break;
	} while (AmTesiSign_ReadCertificate(dlg.m_strPin) != NoError);

	if (iReturn == IDCANCEL)
	{
		AmTesiSign_Finalize();
		return;
	}

	theApp.m_sSmartCardPin = dlg.m_strPin;

	// Sandro 27/02/2013 // controllo che il codice fiscale estratto dalla smartcard sia presente nella tabella EMedici //

	long lConteggioMedici = 0;

	AmTesiSign_SMARTCARDDATA scData;
	AmTesiSign_GetSmartCardData(&scData);

	CString sCodiceFiscaleSmartCard = scData.szUserFiscalCode;
	sCodiceFiscaleSmartCard.MakeUpper();
	sCodiceFiscaleSmartCard.Trim();

	CString sFilter;
	sFilter.Format("CodiceFiscale='%s'", sCodiceFiscaleSmartCard);

	CMediciSet setMedici;
	setMedici.SetOpenFilter(sFilter);
	if (setMedici.OpenRecordset("CPDFCreator::SaveSignedPdfFileIntoRepository"))
	{
		while (!setMedici.IsEOF())
		{
			lConteggioMedici++;
			setMedici.MoveNext();
		}

		setMedici.CloseRecordset("CPDFCreator::SaveSignedPdfFileIntoRepository");
	}

	if (lConteggioMedici < 1)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_09), MB_ICONSTOP);
		// DeleteFile(*pStrFile);
		return; //  FALSE;
	}

	if (lConteggioMedici > 1)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_10), MB_ICONSTOP);
		// DeleteFile(*pStrFile);
		return; //  FALSE;
	}

	// Sandro 29/10/2014 // RAS 20140089 //
	if (theApp.m_bFirmaDigitaleSmartcardUgualeMedico1)
	{
		// controllo se il codice fiscale della smartcard corrisponde a quello del medico che ha fatto l'esame //

		BOOL bOK = FALSE;

		if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lMedico) && (m_pEsamiView->m_pEsamiSet->m_lMedico > 0))
		{
			CString sCodiceFiscaleMedico = CMediciSet().GetCodiceFiscaleFromContatore(m_pEsamiView->m_pEsamiSet->m_lMedico);
			sCodiceFiscaleMedico.Trim();

			if (sCodiceFiscaleMedico.GetLength() > 0)
				if (sCodiceFiscaleSmartCard.CompareNoCase(sCodiceFiscaleMedico) == 0)
					bOK = TRUE;
		}

		if (!bOK)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_11), MB_ICONSTOP);
			// DeleteFile(*pStrFile);
			return; // FALSE;
		}
	}

	// Sandro 29/10/2014 // RAS 20140089 //
	if (theApp.m_bFirmaDigitaleSmartcardUgualeUtenteEndox)
	{
		// controllo se il codice fiscale della smartcard corrisponde a quello dell'utente attualmente loggato in Endox //

		BOOL bOK = FALSE;

		long lUserID;
		AMLogin_GetUserID(&lUserID);

		CString sCodiceFiscaleUtente = CMediciSet().GetCodiceFiscaleFromUserID(lUserID);
		sCodiceFiscaleUtente.Trim();

		if (sCodiceFiscaleUtente.GetLength() > 0)
			if (sCodiceFiscaleSmartCard.CompareNoCase(sCodiceFiscaleUtente) == 0)
				bOK = TRUE;

		if (!bOK)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_12), MB_ICONSTOP);
			// DeleteFile(*pStrFile);
			return; // FALSE;
		}
	}

	for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
	{
		tagPDFVIEW tagTemp = m_pListPDF->GetAt(m_pListPDF->FindIndex(i));
		if (!tagTemp.bFirmato)
		{
			// aggiungo firma digitale al PDF... //
			if (AmTesiSign_SignFile(tagTemp.szFile, theApp.m_sSmartCardPin) != NoError)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_3), MB_ICONSTOP);
				// DeleteFile(*pStrFile);
				continue; // return FALSE;
			}

			if (_access(CString(tagTemp.szFile) + ".p7m", 00) != 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_4), MB_ICONSTOP);
				AmTesiSign_Finalize();
				continue; // return FALSE;
			}
			else
			{
				// cancello PDF non firmato... //
				// DeleteFile(*pStrFile);
			}

			// importo su archivio... //
			CString sSmartCardUtente = "";
			CDigitalSignUtil::GetSmartCardUtente(&sSmartCardUtente);

			CString sSmartCardNumero = "";
			CDigitalSignUtil::GetSmartCardNumero(&sSmartCardNumero);

			CString sSmartCardEnteCertificato = "";
			CDigitalSignUtil::GetSmartCardEnteCertificato(&sSmartCardEnteCertificato);

			CPdfManager PdfManager;
			if (PdfManager.IsInitialize())
			{
				// Sandro 16/03/2015 //
				// non togliere le note, serve per visualizzare nelle liste il nome del report da cui è stato generato il PDF //
				if (PdfManager.UpdatePdfToFirmato(tagTemp.lID, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, sSmartCardUtente, sSmartCardNumero, sSmartCardEnteCertificato))
				{
					tagTemp.ptTipo = pdftype_report_allegato;
					tagTemp.bFirmato = TRUE;
					// tagTemp.bCriptato;
					// tagTemp.szFile[MAX_PATH];

					m_pListPDF->SetAt(m_pListPDF->FindIndex(i), tagTemp);

					CString sTemp = m_ctrlList.GetItemText(i, 0);
					sTemp = theApp.GetMessageString(IDS_PDF_TYPE_8) + " - " + sTemp;
					m_ctrlList.SetItemText(i, 0, sTemp);
				}
			}
		}
	}

	AmTesiSign_Finalize();

	// Sandro 12/03/2015 // se c'è anche un solo PDF non firmato faccio comparire il tasto "firma tutti" //
	int nCmdShow = SW_HIDE;
	if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
	{
		POSITION pos = m_pListPDF->GetHeadPosition();
		while (pos != NULL)
		{
			tagPDFVIEW tagTemp = m_pListPDF->GetAt(pos);

			if (!tagTemp.bFirmato)
			{
				nCmdShow = SW_SHOW;
				break;
			}

			m_pListPDF->GetNext(pos);
		}
	}
	m_ctrlBtnFirmaTutti.ShowWindow(nCmdShow);
}

void CArchivioStampeDlg::OnButtonPagePrec()
{
	PdfViewer_GoToPreviousPage(m_uiTemp);
	RedrawWindow();

	m_ctrlBtnPagePrec.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) > 0);
	m_ctrlBtnPagePrecFull.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) > 0);
	m_ctrlBtnPageSucc.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) + 1 < PdfViewer_GetNumberOfPages(m_uiTemp));
	m_ctrlBtnPageSuccFull.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) + 1 < PdfViewer_GetNumberOfPages(m_uiTemp));

	CString strPage;
	strPage.Format("%li/%li", PdfViewer_GetCurrentPage(m_uiTemp) + 1, PdfViewer_GetNumberOfPages(m_uiTemp));
	SetDlgItemText(IDC_STATIC_PAGE, strPage);
	SetDlgItemText(IDC_STATIC_PAGE_FULL, strPage);
}

void CArchivioStampeDlg::OnButtonPageSucc()
{
	PdfViewer_GoToNextPage(m_uiTemp);
	RedrawWindow();

	m_ctrlBtnPagePrec.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) > 0);
	m_ctrlBtnPagePrecFull.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) > 0);
	m_ctrlBtnPageSucc.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) + 1 < PdfViewer_GetNumberOfPages(m_uiTemp));
	m_ctrlBtnPageSuccFull.EnableWindow(PdfViewer_GetCurrentPage(m_uiTemp) + 1 < PdfViewer_GetNumberOfPages(m_uiTemp));

	CString strPage;
	strPage.Format("%li/%li", PdfViewer_GetCurrentPage(m_uiTemp) + 1, PdfViewer_GetNumberOfPages(m_uiTemp));
	SetDlgItemText(IDC_STATIC_PAGE, strPage);
	SetDlgItemText(IDC_STATIC_PAGE_FULL, strPage);
}

void CArchivioStampeDlg::OnButtonZoomIn()
{
	PdfViewer_ZoomIn(m_uiTemp);
	CPdfAnteprimaDlg::m_lDefaultZoomValue = PdfViewer_GetCurrentZoom(m_uiTemp);

	m_ctrlBtnZoomIn.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) < PdfViewer_GetMaxZoom());
	m_ctrlBtnZoomInFull.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) < PdfViewer_GetMaxZoom());
	m_ctrlBtnZoomOut.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) > PdfViewer_GetMinZoom());
	m_ctrlBtnZoomOutFull.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) > PdfViewer_GetMinZoom());

	CString strZoom;
	strZoom.Format("%li%%", PdfViewer_GetCurrentZoom(m_uiTemp));
	SetDlgItemText(IDC_STATIC_ZOOM, strZoom);
	SetDlgItemText(IDC_STATIC_ZOOM_FULL, strZoom);
}

void CArchivioStampeDlg::OnButtonZoomOut()
{
	PdfViewer_ZoomOut(m_uiTemp);
	CPdfAnteprimaDlg::m_lDefaultZoomValue = PdfViewer_GetCurrentZoom(m_uiTemp);

	m_ctrlBtnZoomIn.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) < PdfViewer_GetMaxZoom());
	m_ctrlBtnZoomInFull.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) < PdfViewer_GetMaxZoom());
	m_ctrlBtnZoomOut.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) > PdfViewer_GetMinZoom());
	m_ctrlBtnZoomOutFull.EnableWindow(PdfViewer_GetCurrentZoom(m_uiTemp) > PdfViewer_GetMinZoom());

	CString strZoom;
	strZoom.Format("%li%%", PdfViewer_GetCurrentZoom(m_uiTemp));
	SetDlgItemText(IDC_STATIC_ZOOM, strZoom);
	SetDlgItemText(IDC_STATIC_ZOOM_FULL, strZoom);
}

void CArchivioStampeDlg::OnSize(UINT nType, int cx, int cy)
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);

	PdfViewer_Resize(m_uiTemp);
}

void CArchivioStampeDlg::OnClose()
{
	PostMessage(WM_COMMAND, IDCANCEL);
}

void CArchivioStampeDlg::OnDestroy()
{
	PdfViewer_Close(m_uiTemp);
	PdfViewer_Finalize(m_uiTemp);

	if (m_pBufferPdf)
		delete m_pBufferPdf;
	m_pBufferPdf = NULL;

	CEndoxResizableDlg::OnDestroy();
}

void CArchivioStampeDlg::OnListSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	ViewPdf();
}

void CArchivioStampeDlg::OnCancel()
{
	CEndoxResizableDlg::OnCancel();
}

void CArchivioStampeDlg::ViewPdf()
{
	BeginWaitCursor();

	PdfViewer_Close(m_uiTemp);

	if (m_pBufferPdf)
		delete m_pBufferPdf;
	m_pBufferPdf = NULL;

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (!pos)
	{
		m_ctrlBtnAnnullaPDF.ShowWindow(SW_HIDE);
		m_ctrlBtnEliminaPdf.ShowWindow(SW_HIDE);
		m_ctrlBtnFirmaSelezionato.ShowWindow(SW_HIDE);
		m_ctrlBtnExport.EnableWindow(FALSE);
		m_ctrlBtnMail.EnableWindow(FALSE);
		m_ctrlBtnPrint.EnableWindow(FALSE);
		return;
	}

	int iCurSel = m_ctrlList.GetNextSelectedItem(pos);
	tagPDFVIEW tagTemp = m_pListPDF->GetAt(m_pListPDF->FindIndex(iCurSel));

	if ((CString(tagTemp.szDisco).CompareNoCase("R") == 0) && !CString(tagTemp.szPercorsoFileRemoto).IsEmpty())
	{
		CPdfManager PdfManager;
		if (PdfManager.IsInitialize())
		{
			if (PdfManager.CopyToLocal(tagTemp.lID))
			{
				sprintf(tagTemp.szDisco, "H");
				m_pListPDF->SetAt(m_pListPDF->FindIndex(iCurSel), tagTemp);
			}
			else
			{
				sprintf(tagTemp.szFile, tagTemp.szPercorsoFileRemoto);
			}
		}
		else
		{
			sprintf(tagTemp.szFile, tagTemp.szPercorsoFileRemoto);
		}
	}

	CString strFile = tagTemp.szFile;

	if (_access(strFile, 06) == 0)
	{
		if (tagTemp.bCriptato)
		{
			DWORD dwBufferSize = 0;
			if (CDigitalSignUtil::DecryptPdf(strFile, &m_pBufferPdf, &dwBufferSize))
				PdfViewer_LoadFromBuffer(m_uiTemp, m_pBufferPdf, dwBufferSize);
		}
		else
		{
			PdfViewer_Load(m_uiTemp, strFile);
		}

		PdfViewer_SetCurrentZoom(m_uiTemp, CPdfAnteprimaDlg::m_lDefaultZoomValue);

		m_ctrlBtnPagePrec.EnableWindow(FALSE);
		m_ctrlBtnPagePrecFull.EnableWindow(FALSE);
		m_ctrlBtnPageSucc.EnableWindow(PdfViewer_GetNumberOfPages(m_uiTemp) > 1);
		m_ctrlBtnPageSuccFull.EnableWindow(PdfViewer_GetNumberOfPages(m_uiTemp) > 1);

		CString strPage;
		strPage.Format("%li/%li", PdfViewer_GetCurrentPage(m_uiTemp) + 1, PdfViewer_GetNumberOfPages(m_uiTemp));
		SetDlgItemText(IDC_STATIC_PAGE, strPage);
		SetDlgItemText(IDC_STATIC_PAGE_FULL, strPage);

		CString strZoom;
		strZoom.Format("%li%%", PdfViewer_GetCurrentZoom(m_uiTemp));
		SetDlgItemText(IDC_STATIC_ZOOM, strZoom);
		SetDlgItemText(IDC_STATIC_ZOOM_FULL, strZoom);

		m_ctrlBtnAnnullaPDF.ShowWindow((tagTemp.bFirmato && (tagTemp.ptTipo == pdftype_report)) ? SW_SHOW : SW_HIDE);
		m_ctrlBtnAnnullaPDF.EnableWindow(!tagTemp.bSospeso && !tagTemp.bAnnullato);
		m_ctrlBtnEliminaPdf.ShowWindow(!tagTemp.bFirmato && m_bShowLeftList ? SW_SHOW : SW_HIDE);
		m_ctrlBtnFirmaSelezionato.ShowWindow(FALSE && !tagTemp.bFirmato && m_bShowLeftList ? SW_SHOW : SW_HIDE);
		m_ctrlBtnExport.EnableWindow(!tagTemp.bSospeso && !tagTemp.bAnnullato);
		m_ctrlBtnMail.EnableWindow(!tagTemp.bSospeso && !tagTemp.bAnnullato);
		m_ctrlBtnPrint.EnableWindow(!tagTemp.bSospeso && !tagTemp.bAnnullato);

		//Recupero l'informazione se il pdf è di VitalSign, in caso affermativo mostro il pulsante per modificare le note.
		// Ovviamente posso modificare le note dei pdf attualmente associati ad un monitoraggio.
		CString filter;
		filter.Format("IDPDF=%li", tagTemp.lID);
		CVitalSignMisurazioniHeaderSet vitalSignMisSet;
		vitalSignMisSet.SetOpenFilter(filter);

		m_ctrlBtnModificaNoteVS.ShowWindow(SW_HIDE);

		if (vitalSignMisSet.OpenRecordset("CArchivioStampeDlg::ViewPdf"))
		{
			if (!vitalSignMisSet.IsEOF())
			{
				m_ctrlBtnModificaNoteVS.ShowWindow(SW_SHOW);
			}
			
			vitalSignMisSet.CloseRecordset("CArchivioStampeDlg::ViewPdf");
		}	
	}

	EndWaitCursor();
}

void CArchivioStampeDlg::OnBnClickedBtnModificanoteVs()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	int iCurSel = m_ctrlList.GetNextSelectedItem(pos);
	tagPDFVIEW tagTemp = m_pListPDF->GetAt(m_pListPDF->FindIndex(iCurSel));

	//Recupero l'informazione se il pdf è di VitalSign, in caso affermativo mostro il pulsante per modificare le note.
	// Ovviamente posso modificare le note dei pdf attualmente associati ad un monitoraggio.
	CString filter;
	filter.Format("IDPDF=%li", tagTemp.lID);
	CVitalSignMisurazioniHeaderSet vitalSignMisSet;
	vitalSignMisSet.SetOpenFilter(filter);

	BOOL bClose = FALSE;

	m_ctrlBtnModificaNoteVS.ShowWindow(SW_HIDE);

	if (vitalSignMisSet.OpenRecordset("CArchivioStampeDlg::OnBnClickedBtnModificanoteVs"))
	{
		if (!vitalSignMisSet.IsEOF())
		{
			CVitalSignModificaNoteDlg noteDlg(this, m_pEsamiView, vitalSignMisSet.m_lID);
			if (noteDlg.DoModal() == IDOK)
				bClose = TRUE;
		}

		vitalSignMisSet.CloseRecordset("CArchivioStampeDlg::OnBnClickedBtnModificanoteVs");
	}

	if (bClose)
		CEndoxResizableDlg::OnOK();
	else
		ViewPdf();
}
