#include "stdafx.h"
#include "Endox.h"
#include "DocumentiDlg.h"

#include "DLL_Imaging\h\FileReceiver.h"

#include "ArchivioStampeDlg.h"
#include "DocManager.h"
#include "EditDateStringDlg.h"
#include "EsamiView.h"
#include "ExtOrdiniAllegatiSet.h"
#include "ExtOrdiniSet.h"
#include "ImageSimpleDlg.h"
#include "MultiPageTiffNewEdtDlg.h"

IMPLEMENT_DYNAMIC(CDocumentiDlg, CDialog)

CDocumentiDlg::CDocumentiDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bAlbumPaziente, BOOL bInviareCarestream, BOOL bInviaCentraleRefertazione)
: CDialog(CDocumentiDlg::IDD, pParent), m_ctrlList(TRUE, FALSE, FALSE)
{
	m_pEsamiView = pEsamiView;
	m_bAlbumPaziente = bAlbumPaziente;
	m_bInviareCarestream = bInviareCarestream;
	m_bInviaCentraleRefertazione = bInviaCentraleRefertazione;
}

CDocumentiDlg::~CDocumentiDlg()
{
}

BEGIN_MESSAGE_MAP(CDocumentiDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_DISCO, OnBnClickedBtnDisco)
	ON_BN_CLICKED(IDC_BTN_SCANNER, OnBnClickedBtnScanner)
	ON_BN_CLICKED(IDC_BTN_TIFFMP, OnBnClickedBtnTiffMP)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)

	ON_BN_CLICKED(IDC_BTN_INTEGRAZIONE, OnBnClickedBtnIntegrazione)
	ON_BN_CLICKED(IDC_BTN_EXPALL, OnBnClickedBtnExpAll)

END_MESSAGE_MAP()

void CDocumentiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_DISCO, m_ctrlBtnDisco);
	DDX_Control(pDX, IDC_BTN_SCANNER, m_ctrlBtnScanner);
	DDX_Control(pDX, IDC_BTN_TIFFMP, m_ctrlBtnTiffMP);
	DDX_Control(pDX, IDC_BTN_INTEGRAZIONE, m_ctrlBtnIntegrazione);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	DDX_Control(pDX, IDC_BTN_EXPALL, m_ctrlBtnExpAll);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
	DDX_Control(pDX, IDC_BTN_ARCHIVIA, m_ctrlBtnArchivia);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

BOOL CDocumentiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, theApp.GetMessageString(IDS_DATADOCUMENTO), LVCFMT_CENTER, 0);
	m_ctrlList.InsertColumn(2, theApp.GetMessageString(IDS_DESCRIZIONE), LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(3, theApp.GetMessageString(IDS_TIPO), LVCFMT_CENTER, 0);
	m_ctrlList.InsertColumn(4, theApp.GetMessageString(IDS_DATAIMPORTAZIONE), LVCFMT_CENTER, 0);
	m_ctrlList.InsertColumn(5, "", LVCFMT_LEFT, 0);

	if (m_bAlbumPaziente || m_bInviareCarestream)
		m_ctrlBtnIntegrazione.ShowWindow(SW_HIDE);
	 
	if (theApp.m_bDemoAliar)
		m_ctrlBtnExpAll.ShowWindow(SW_SHOW);

	RiempiLista();

	theApp.LocalizeDialog(this, CDocumentiDlg::IDD, "DocumentiDlg");

	if (m_bInviareCarestream)
		SetWindowText(theApp.GetMessageString(IDS_GESTIONEALLEGATI_INVIARECARESTREAM));

	BOOL bEnable = !m_pEsamiView->m_pEsamiSet->m_bSuperLocked;
	m_ctrlBtnDisco.EnableWindow(bEnable);
	m_ctrlBtnScanner.EnableWindow(bEnable);
	m_ctrlBtnTiffMP.EnableWindow(bEnable);
	m_ctrlBtnIntegrazione.EnableWindow(bEnable);
	m_ctrlBtnEdt.EnableWindow(bEnable);
	m_ctrlBtnDel.EnableWindow(bEnable);
	m_ctrlBtnExpAll.EnableWindow(bEnable);
	m_ctrlBtnArchivia.EnableWindow(bEnable);
	
	if (bEnable && theApp.m_bPersonalizzazioniBrasileFleury && m_pEsamiView->m_lNumDocumentsExam == 0 && m_bInviareCarestream == FALSE)
	{
		OnBnClickedBtnIntegrazione();
	}
	

	return TRUE;
}

void CDocumentiDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bEnable = !m_pEsamiView->m_pEsamiSet->m_bSuperLocked;

	m_ctrlBtnEdt.EnableWindow(bEnable && m_ctrlList.GetFirstSelectedItemPosition() != NULL);

	if(theApp.m_bPersonalizzazioniBrasileSirio) // Sandro 17/09/2015 // RIMA 15071.8 //
		m_ctrlBtnDel.EnableWindow(FALSE);
	else
		m_ctrlBtnDel.EnableWindow(bEnable && m_ctrlList.GetFirstSelectedItemPosition() != NULL);
}

void CDocumentiDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList.GetNextSelectedItem(pos);
		long lID = (long)m_ctrlList.GetItemData(nItem);

		if (lID > 0)
		{
			CList<DOC> lst;

			// Sandro 04/01/2014 // RAS 20130175 //
			BOOL bContinue = FALSE;
			if (m_bAlbumPaziente)
				bContinue = m_pEsamiView->m_pDocManager->GetAttachedDocListPatient(m_pEsamiView->m_pPazientiSet->m_lContatore, &lst);
			else
				bContinue = m_pEsamiView->m_pDocManager->GetAttachedDocListExam(m_pEsamiView->m_pEsamiSet->m_lContatore, m_bInviareCarestream ? DOCUMENTS_ONLY_EXPORT : DOCUMENTS_NOT_EXPORT, &lst);

			//
			if (bContinue)
			{
				for(int i = 0; i < lst.GetCount(); i++)
				{
					DOC doc = lst.GetAt(lst.FindIndex(i));
					if (doc.lID == lID)
					{
						if ((CString(doc.szDisco).CompareNoCase("R") == 0) && !CString(doc.szPercorsoFileRemoto).IsEmpty())
						{
							if (m_pEsamiView->m_pDocManager->CopyToLocal(doc.lID))
							{
								sprintf(doc.szDisco, "H");
								lst.SetAt(lst.FindIndex(i), doc);
							}
							else
							{
								sprintf(doc.szFile, doc.szPercorsoFileRemoto);
							}
						}

						switch(doc.dtTipo)
						{
							case doctype_jpeg:
							case doctype_jpg:
							case doctype_bmp:
							case doctype_tif:
							case doctype_tiff:
							case doctype_mptiff:
							{
								CImageSimpleDlg(this, m_pEsamiView, doc.szFile).DoModal();
								break;
							}
							case doctype_pdf:
							case doctype_p7m:
							{
								CArchivioStampeDlg::tagPDFVIEW pdfView;
								pdfView.lID = 0;
								strcpy_s(pdfView.szNote, "");
								strcpy_s(pdfView.szData, "");
								strcpy_s(pdfView.szFile, doc.szFile);
								pdfView.bFitToPage = FALSE;
								pdfView.bFirmato = FALSE;
								pdfView.bSospeso = FALSE;
								pdfView.bAnnullato = FALSE;
								pdfView.bCriptato = FALSE;
								strcpy_s(pdfView.szDisco, doc.szDisco);
								strcpy_s(pdfView.szPercorsoFileRemoto, doc.szPercorsoFileRemoto);

								CList<CArchivioStampeDlg::tagPDFVIEW> listViewPdf;
								listViewPdf.AddTail(pdfView);

								CString sTitle = "";

								CArchivioStampeDlg dlg(this, m_pEsamiView, &listViewPdf, sTitle, FALSE);
								dlg.DoModal();

								break;
							}
							default:
							{
								if ((long)ShellExecute(NULL, "open", doc.szFile, NULL, NULL, SW_SHOWMAXIMIZED) == ERROR_FILE_NOT_FOUND)
									theApp.AfxMessageBoxEndo("File " + CString(doc.szFile) + theApp.GetMessageString(IDS_NOT_FOUND), MB_ICONSTOP);

								break;
							}
						}
					}
				}
			}
		}
	}
}

void CDocumentiDlg::OnBnClickedBtnDisco()
{
	CFileDialog dlgFile(TRUE, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, theApp.GetMessageString(IDS_DOCUMENTS_TYPES) + "|*.txt; *.rtf; *.doc; *.pdf; *.docx; *.ppt; *.pptx; *.xls; *.xlsx; *.jpeg; *.jpg; *.bmp; *.tif; *.tiff; *.p7m; *.htm; *.html; *.mht|BMP|*.bmp|DOC|*.doc|DOCX|*.docx|HTM|*.htm|HTML|*.html|JPEG|*.jpeg|JPG|*.jpg|MHT|*.mht|P7M|*.p7m|PDF|*.pdf|PPT|*.ppt|PPTX|*.pptx|RTF|*.rtf|TIF|*.tif|TIFF|*.tiff|TXT|*.txt|XLS|*.xls|XLSX|*.xlsx|", this, 0, FALSE);
	
	if (dlgFile.DoModal())
	{
		CEditDateStringDlg dlgComm(this, IDS_DOCUMENT_COMMENT, "", "");
		if (dlgComm.DoModal() == IDCANCEL)
			return;

		// Sandro 04/01/2014 // RAS 20130175 //
		BOOL bContinue = FALSE;
		if (m_bAlbumPaziente)
			bContinue = m_pEsamiView->m_pDocManager->ImportDoc(m_pEsamiView->m_pPazientiSet->m_lContatore, 0, dlgComm.GetDescrizione(), dlgComm.GetData(), dlgFile.GetPathName(), m_bInviareCarestream);
		else
			bContinue = m_pEsamiView->m_pDocManager->ImportDoc(m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, dlgComm.GetDescrizione(), dlgComm.GetData(), dlgFile.GetPathName(), m_bInviareCarestream);

		//
		if (!bContinue)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMPORT_FAILED));
			return;
		}

		RiempiLista();
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FILE_NON_SUPPORTATO));
	}
}

void CDocumentiDlg::OnBnClickedBtnScanner()
{
	switch (theApp.m_enumScannerConnectionType)
	{
		case 0:
			OnBnClickedBtnScannerTwain();
			break;
		case 1:
			OnBnClickedBtnScannerWM();
			break;
		default:
			break;
	}
}

void CDocumentiDlg::OnBnClickedBtnScannerTwain()
{
	if (!theApp.m_bCanAcquire)
		return;

	if (!VerificaPercorso(theApp.m_sDirTemp))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_ERR_PATH) + theApp.m_sDirTemp);
		return;
	}

	// Sandro 27/09/2013 // RAS 20130154 //

	CEditDateStringDlg dlgComm(this, IDS_DOCUMENT_COMMENT, "", "");
	if (dlgComm.DoModal() == IDCANCEL)
		return;

	//

	char szBuffer[512];

	sprintf_s(szBuffer, "%s", theApp.m_sDirTemp);
	WritePrivateProfileString("xTwain", "Path", szBuffer, theApp.m_sFileConfig);

	sprintf_s(szBuffer, "%08d_%08d_", m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);
	WritePrivateProfileString("xTwain", "ImagePrefix", szBuffer, theApp.m_sFileConfig);

	TCHAR szProcess[1024];
	sprintf_s(szProcess, "%s\\xTwain\\xTwain.exe %s", theApp.m_sDirProg, theApp.m_sFileConfig); // xTAIUAN //

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

		return;
	}

	// Sandro 04/05/2010 - RAS 20100072 --> //
	DWORD dwState = 0;
	do
	{
		// ogni tre secondi faccio il giro della cartella temporanea in cerca di nuovi files //
		dwState = WaitForSingleObject(pi.hProcess, 3000);

		BeginWaitCursor();

		// importo solo le immagini e/o filmati dell'esame corrente //
		CString strWildcard;
		strWildcard.Format("%s\\%08d_%08d_*.*",
			theApp.m_sDirTemp,
			m_pEsamiView->m_pEsamiSet->m_lPaziente,
			m_pEsamiView->m_pEsamiSet->m_lContatore);

		CStringList listPath;
		WIN32_FIND_DATA dataFile;
		HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
		if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
		{
			do
			{
				CString strFile(dataFile.cFileName);

				if (strFile.GetLength() > 3)
				{
					if (strFile.Right(3).CompareNoCase("bmp") == 0)
					{
						CString strAddFile = theApp.m_sDirTemp + "\\" + strFile;

						// controllo che la dimensione del file sia maggiore di 0 (capita per certi filmati e si blocca tutto) //

						HANDLE hFile = CreateFile(strAddFile, STANDARD_RIGHTS_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
						{
							LARGE_INTEGER llTemp;
							if (GetFileSizeEx(hFile, &llTemp))
							{
								if (llTemp.QuadPart > 0)
									listPath.AddHead(strAddFile);
								else
									DeleteFile(strAddFile);
							}
						}
						CloseHandle(hFile);

						POSITION pos = listPath.GetHeadPosition();
						while (pos != NULL)
						{
							CString sFileToImport = listPath.GetAt(pos);

							// Sandro 04/01/2014 // RAS 20130175 //
							BOOL bContinue = FALSE;
							if (m_bAlbumPaziente)
								bContinue = m_pEsamiView->m_pDocManager->ImportDoc(m_pEsamiView->m_pPazientiSet->m_lContatore, 0, dlgComm.GetDescrizione(), dlgComm.GetData(), sFileToImport, m_bInviareCarestream);
							else
								bContinue = m_pEsamiView->m_pDocManager->ImportDoc(m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, dlgComm.GetDescrizione(), dlgComm.GetData(), sFileToImport, m_bInviareCarestream);

							//
							if (bContinue)
								DeleteFile(sFileToImport);

							listPath.GetNext(pos);
						}

						if (listPath.GetCount() > 0)
							RiempiLista();

						listPath.RemoveAll();
					}
				}
			} while (FindNextFile(hFile, &dataFile));
			FindClose(hFile);
		}
		EndWaitCursor();

	} while (dwState == WAIT_TIMEOUT);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	// <-- Sandro 04/05/2010 - RAS 20100072 //
}

void CDocumentiDlg::OnBnClickedBtnScannerWM()
{
	if (!theApp.m_bCanAcquire)
		return;

	if (!VerificaPercorso(theApp.m_sDirTemp))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_ERR_PATH) + theApp.m_sDirTemp);
		return;
	}

	// Sandro 27/09/2013 // RAS 20130154 //

	CEditDateStringDlg dlgComm(this, IDS_DOCUMENT_COMMENT, "", "");
	if (dlgComm.DoModal() == IDCANCEL)
		return;

	//

	CStringList strFileList;

	if (!FileReceiver_ReceiveFile(&strFileList))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SCANNERACQ_ERROR));
		return;
	}	

	POSITION pos = strFileList.GetHeadPosition();
	while (pos)
	{
		CString strFile = strFileList.GetNext(pos);

		BOOL bContinue = FALSE;
		if (m_bAlbumPaziente)
			bContinue = m_pEsamiView->m_pDocManager->ImportDoc(m_pEsamiView->m_pPazientiSet->m_lContatore, 0, dlgComm.GetDescrizione(), dlgComm.GetData(), strFile, m_bInviareCarestream);
		else
			bContinue = m_pEsamiView->m_pDocManager->ImportDoc(m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, dlgComm.GetDescrizione(), dlgComm.GetData(), strFile, m_bInviareCarestream);

		//
		if (bContinue)
			DeleteFile(strFile);
		else
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SCANNERIMP_ERROR) + " " + strFile);		
	}
	// <-- Sandro 04/05/2010 - RAS 20100072 //

	RiempiLista();
}

void CDocumentiDlg::OnBnClickedBtnTiffMP()
{
	// creazione/modifica di un TIFF multipagina (da disco o da scanner) //

	long lIDTiffMP = 0;

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlList.GetNextSelectedItem(pos);

		if (m_ctrlList.GetItemText(nCurSel, 3) == "TIFF (MP)")
			lIDTiffMP = m_ctrlList.GetItemData(nCurSel);
	}

	CMultiPageTiffNewEdtDlg dlg(this, m_pEsamiView, m_pEsamiView->m_pPazientiSet, m_pEsamiView->m_pEsamiSet, lIDTiffMP, m_bAlbumPaziente);
	dlg.DoModal();

	RiempiLista();
}

void CDocumentiDlg::OnBnClickedBtnIntegrazione()
{	
	
	//if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_VERIFICA_DOCUMENTI), MB_YESNO) == IDNO)
	//	return;
		

	BeginWaitCursor();

	CString strFilter;
	long idOrdine = -1;

	//Recupero l'id dell'ordine
	CExtOrdiniSet ordiniSet;
	strFilter.Format("idesameins=%li",m_pEsamiView->m_pEsamiSet->m_lContatore);
	ordiniSet.SetOpenFilter(strFilter);

	if (ordiniSet.OpenRecordset("CDocumentiDlg::OnBnClickedBtnIntegrazione"))
	{
		if (!ordiniSet.IsEOF())
			idOrdine = ordiniSet.m_lID;

		ordiniSet.CloseRecordset("CDocumentiDlg::OnBnClickedBtnIntegrazione");
	}

	int allegatiImportati = 0;

	if (idOrdine > 0) //Se ho trovato un ordine in wl, importo gli allegati
	{
		CExtOrdiniAllegatiSet allegatiSet;

		strFilter.Format("idRichiesta=%li and getOnDemand=1", idOrdine); //Prendo solo gli allegati on-demand
		allegatiSet.SetOpenFilter(strFilter);
		if (allegatiSet.OpenRecordset("CDocumentiDlg::OnBnClickedBtnIntegrazione"))
		{
			while (!allegatiSet.IsEOF())
			{
				CTime timeNow = CTime::GetCurrentTime();
				if (!m_pEsamiView->m_pDocManager->ImportDoc(m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, allegatiSet.m_sDescrizione, timeNow.Format("%Y%m%d%H%M%S"), allegatiSet.m_sPath, FALSE))
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DOCUMENTI_ERRORE) + " " + allegatiSet.m_sPath);
				else
				{
					allegatiImportati++;
					//Julio 13/11/2018 : open file automatically
					if (theApp.m_bPersonalizzazioniBrasileFleury && m_pEsamiView->m_lNumDocumentsExam == 0 && !m_bInviaCentraleRefertazione)
					{
						RiempiLista();
						long lID = (long)m_ctrlList.GetItemData(0);

						if (lID > 0)
						{
							CList<DOC> lst;


							BOOL bContinue = FALSE;
							if (m_bAlbumPaziente)
								bContinue = m_pEsamiView->m_pDocManager->GetAttachedDocListPatient(m_pEsamiView->m_pPazientiSet->m_lContatore, &lst);
							else
								bContinue = m_pEsamiView->m_pDocManager->GetAttachedDocListExam(m_pEsamiView->m_pEsamiSet->m_lContatore, m_bInviareCarestream ? DOCUMENTS_ONLY_EXPORT : DOCUMENTS_NOT_EXPORT, &lst);

							//
							if (bContinue)
							{
								for (int i = 0; i < lst.GetCount(); i++)
								{
									DOC doc = lst.GetAt(lst.FindIndex(i));
									if (doc.lID == lID)
									{
										if ((CString(doc.szDisco).CompareNoCase("R") == 0) && !CString(doc.szPercorsoFileRemoto).IsEmpty())
										{
											if (m_pEsamiView->m_pDocManager->CopyToLocal(doc.lID))
											{
												sprintf(doc.szDisco, "H");
												lst.SetAt(lst.FindIndex(i), doc);
											}
											else
											{
												sprintf(doc.szFile, doc.szPercorsoFileRemoto);
											}
										}

										switch (doc.dtTipo)
										{
										case doctype_jpeg:
										case doctype_jpg:
										case doctype_bmp:
										case doctype_tif:
										case doctype_tiff:
										case doctype_mptiff:
										{
											CImageSimpleDlg(this, m_pEsamiView, doc.szFile).DoModal();
											break;
										}
										case doctype_pdf:
										case doctype_p7m:
										{
											CArchivioStampeDlg::tagPDFVIEW pdfView;
											pdfView.lID = 0;
											strcpy_s(pdfView.szNote, "");
											strcpy_s(pdfView.szData, "");
											strcpy_s(pdfView.szFile, doc.szFile);
											pdfView.bFitToPage = FALSE;
											pdfView.bFirmato = FALSE;
											pdfView.bSospeso = FALSE;
											pdfView.bAnnullato = FALSE;
											pdfView.bCriptato = FALSE;
											strcpy_s(pdfView.szDisco, doc.szDisco);
											strcpy_s(pdfView.szPercorsoFileRemoto, doc.szPercorsoFileRemoto);

											CList<CArchivioStampeDlg::tagPDFVIEW> listViewPdf;
											listViewPdf.AddTail(pdfView);

											CString sTitle = "";

											CArchivioStampeDlg dlg(this, m_pEsamiView, &listViewPdf, sTitle, FALSE);
											dlg.DoModal();

											break;
										}
										default:
										{
											if ((long)ShellExecute(NULL, "open", doc.szFile, NULL, NULL, SW_SHOWMAXIMIZED) == ERROR_FILE_NOT_FOUND)
												theApp.AfxMessageBoxEndo("File " + CString(doc.szFile) + theApp.GetMessageString(IDS_NOT_FOUND), MB_ICONSTOP);

											break;
										}
										}
									}
								}
							}
						}
					}
					//
				}
					
				allegatiSet.MoveNext();
			}

			allegatiSet.CloseRecordset("CDocumentiDlg::OnBnClickedBtnIntegrazione");
		}
	}

	EndWaitCursor();

	if (allegatiImportati > 0)
	{
		CString temp;
		temp.Format("%li %s", allegatiImportati, theApp.GetMessageString(IDS_DOCUMENTI_IMPORTATI));
		//theApp.AfxMessageBoxEndo(temp);

		RiempiLista();
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NO_DOCUMENTI));
	}

	if (m_bInviaCentraleRefertazione)
		CDialog::OnOK();
}


void CDocumentiDlg::OnBnClickedBtnEdt()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList.GetNextSelectedItem(pos);
		long lID = (long)m_ctrlList.GetItemData(nItem);

		if (lID > 0)
		{
			CEditDateStringDlg dlgComm(this, IDS_DOCUMENT_COMMENT, m_ctrlList.GetItemText(nItem, 1), m_ctrlList.GetItemText(nItem, 2));
			if (dlgComm.DoModal() == IDOK)
			{
				m_pEsamiView->m_pDocManager->EditDoc(lID, dlgComm.GetDescrizione(), dlgComm.GetData());
				RiempiLista();
			}
		}
	}
}

void CDocumentiDlg::OnBnClickedBtnDel()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nItem = m_ctrlList.GetNextSelectedItem(pos);
		long lID = (long)m_ctrlList.GetItemData(nItem);

		if (lID > 0)
		{
			if (theApp.MessageBoxEndo(theApp.GetMessageString(IDS_DELETE_DOCUMENT), theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONSTOP) == IDYES)
			{
				m_pEsamiView->m_pDocManager->DeleteDoc(lID);
				RiempiLista();
			}
		}
	}
}

void CDocumentiDlg::RiempiLista()
{
	// static CString sTypes[20] = { "TXT", "RTF", "DOC", "PDF", "?", "DOCX", "PPT", "PPTX", "XLS", "XLSX", "JPEG", "JPG", "BMP", "TIF", "TIFF", "P7M", "HTM", "HTML", "MHT", "TIFF (MP)" };

	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	CList<DOC> lst;

	// Sandro 04/01/2014 // RAS 20130175 //
	BOOL bContinue = FALSE;
	if (m_bAlbumPaziente)
		bContinue = m_pEsamiView->m_pDocManager->GetAttachedDocListPatient(m_pEsamiView->m_pPazientiSet->m_lContatore, &lst);
	else
		bContinue = m_pEsamiView->m_pDocManager->GetAttachedDocListExam(m_pEsamiView->m_pEsamiSet->m_lContatore, m_bInviareCarestream ? DOCUMENTS_ONLY_EXPORT : DOCUMENTS_NOT_EXPORT, &lst);

	//
	if (bContinue)
	{
		for(int i = 0; i < lst.GetCount(); i++)
		{
			DOC doc = lst.GetAt(lst.FindIndex(i));

			CString sData;
			sData.Format("%s/%s/%s %s.%s.%s",
						   CString(doc.szData).Mid(6, 2),
						   CString(doc.szData).Mid(4, 2),
						   CString(doc.szData).Mid(0, 4),
						   CString(doc.szData).Mid(8, 2),
						   CString(doc.szData).Mid(10, 2),
						   CString(doc.szData).Mid(12, 2));

			CString sDataPersonalizzabile;
			sDataPersonalizzabile.Format("%s/%s/%s",
						   CString(doc.szDataPersonalizzabile).Mid(6, 2),
						   CString(doc.szDataPersonalizzabile).Mid(4, 2),
						   CString(doc.szDataPersonalizzabile).Mid(0, 4));
			if (sDataPersonalizzabile == "//")
				sDataPersonalizzabile.Empty();

			int iInserted = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), "");
			m_ctrlList.SetItemData(iInserted, doc.lID);

			m_ctrlList.SetItemText(iInserted, 1, sDataPersonalizzabile);

			m_ctrlList.SetItemText(iInserted, 2, doc.szDescrizione);

			CString sFileType(doc.szFileTypeDescription);
			CString sFileExtension(doc.szFileExtension);
			if ((sFileType.IsEmpty() || sFileType.CompareNoCase("?") == 0) && (!sFileExtension.IsEmpty()))
				sFileType = sFileExtension;
			sFileType.MakeUpper();
			m_ctrlList.SetItemText(iInserted, 3, sFileType);

			m_ctrlList.SetItemText(iInserted, 4, sData);

			m_ctrlList.SetItemText(iInserted, 5, doc.szUtente);
		}
	}

	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(5, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(6, 100);

	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CDocumentiDlg::OnBnClickedBtnExpAll()
{
	CString sTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_15);
	CFolderDialog dlg(sTitle, theApp.m_sExportFolder, 0x0040, this);
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

		CList<DOC> lst;

		// Sandro 04/01/2014 // RAS 20130175 //
		BOOL bContinue = FALSE;
		if (m_bAlbumPaziente)
			bContinue = m_pEsamiView->m_pDocManager->GetAttachedDocListPatient(m_pEsamiView->m_pPazientiSet->m_lContatore, &lst);
		else
			bContinue = m_pEsamiView->m_pDocManager->GetAttachedDocListExam(m_pEsamiView->m_pEsamiSet->m_lContatore, m_bInviareCarestream ? DOCUMENTS_ONLY_EXPORT : DOCUMENTS_NOT_EXPORT, &lst);

		//
		if (bContinue)
		{
			for (int i = 0; i < lst.GetCount(); i++)
			{
				DOC doc = lst.GetAt(lst.FindIndex(i));

				CString sOrigFile(doc.szFile);
				// int nFind = sOrigFile.ReverseFind('\\');
				CString sDestFile = strTemp + CString(doc.szFileOriginalName) + "." + CString(doc.szFileExtension);

				CopyFile(sOrigFile, sDestFile, FALSE);
			}
		}
	}
}
