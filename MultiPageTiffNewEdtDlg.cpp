#include "stdafx.h"
#include "Endox.h"
#include "MultiPageTiffNewEdtDlg.h"

#include "AlbumForm.h"
#include "CustomDate.h"
#include "DocManager.h"
#include "EditDateStringDlg.h"
#include "EsamiView.h"
#include "LockManager.h"
#include "LogFileWriter.h"
#include "MmSystem.h"
#include "VistaDocumentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMultiPageTiffNewEdtDlg, CDialog)

CMultiPageTiffNewEdtDlg::CMultiPageTiffNewEdtDlg(CWnd* pParent, CEsamiView* pEsamiView, CPazientiSet* pPazienteSet, CEsamiSet* pEsamiSet, long lIDImageTIFF, BOOL bPaziente)
	: CDialog(CMultiPageTiffNewEdtDlg::IDD, pParent)
{
	ASSERT((pEsamiView != NULL) && (pEsamiSet != NULL));

	m_pAlbumForm = NULL;
	m_pEsamiView = pEsamiView;
	m_pPazienteSet = pPazienteSet;
	m_pEsamiSet = pEsamiSet;
	m_lIDImageTIFF = lIDImageTIFF;
	m_bPaziente = bPaziente;
}

CMultiPageTiffNewEdtDlg::~CMultiPageTiffNewEdtDlg()
{
}

BEGIN_MESSAGE_MAP(CMultiPageTiffNewEdtDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_BTN_DISCO, OnBnClickedBtnDisco)
	ON_BN_CLICKED(IDC_BTN_SCANNER, OnBnClickedBtnScanner)
END_MESSAGE_MAP()

void CMultiPageTiffNewEdtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDC_BTN_DISCO, m_ctrlBtnDisco);
	DDX_Control(pDX, IDC_BTN_SCANNER, m_ctrlBtnScanner);

	DDX_Control(pDX, IDC_STATIC_TITLE_1, m_ctrlStaticTitle1);
	DDX_Control(pDX, IDC_STATIC_TITLE_2, m_ctrlStaticTitle2);
}

BOOL CMultiPageTiffNewEdtDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStaticTitle1.SetFont(&theApp.m_fontBig);
	m_ctrlStaticTitle2.SetFont(&theApp.m_fontBig);
	m_ctrlBtnDisco.SetFont(&theApp.m_fontBold);
	m_ctrlBtnScanner.SetFont(&theApp.m_fontBold);

	if (m_lIDImageTIFF <= 0)
		m_ctrlStaticTitle1.ShowWindow(SW_SHOW);
	else
		m_ctrlStaticTitle2.ShowWindow(SW_SHOW);

	theApp.LocalizeDialog(this, CMultiPageTiffNewEdtDlg::IDD, "MultiPageTiffNewDlg");
	return TRUE;
}

HBRUSH CMultiPageTiffNewEdtDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hReturn = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_TITLE_1:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
		case IDC_STATIC_TITLE_2:
		{
			pDC->SetTextColor(theApp.m_color[4]);
			break;
		}
	}

	return hReturn;
}

void CMultiPageTiffNewEdtDlg::OnBnClickedBtnDisco()
{
    if (!m_pEsamiSet->IsOpen() || m_pEsamiSet->IsBOF() || m_pEsamiSet->IsEOF())
        return;
 
	if (!theApp.m_bCanAcquire)
		return;

	CStringList ArraySelected;

	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, NULL, this, 0, FALSE);
	dlgFile.GetOFN().lpstrInitialDir = theApp.m_sEditImm;

	CString strFileDialog;
	int iMaxFiles = 100;
	int iBuffSize = (iMaxFiles * (MAX_PATH + 1)) + 1;

	dlgFile.GetOFN().lpstrFile = strFileDialog.GetBuffer(iBuffSize);
	dlgFile.GetOFN().nMaxFile = iBuffSize;
	dlgFile.GetOFN().lpstrInitialDir = theApp.m_sEditImm;

	if (dlgFile.DoModal() == IDOK)
	{
		// Sandro Gallina - 06/04/2004 --> //
		if (theApp.m_bCheckImm == FALSE)
		{
			CString strTemp = dlgFile.GetPathName();
			int iTemp = 0;
			int iLastSlash = 0;

			while(iTemp >= 0)
			{
				iTemp = strTemp.Find('\\', iLastSlash);
				if (iTemp >= 0)
					iLastSlash = iTemp + 1;
			}
			
			theApp.m_sEditImm = strTemp.Left(iLastSlash - 1);
			WritePrivateProfileString(szPercorsi, szEditImm, theApp.m_sEditImm, theApp.m_sFileConfig);
		}
		// <-- Sandro Gallina - 06/04/2004 //

		POSITION pos = dlgFile.GetStartPosition();
		while(pos)
		{
			CString strFile = dlgFile.GetNextPathName(pos);

			if (strFile != "")
			{
				BOOL bContinue = TRUE;
				int nIndex = 0;
				int nMaxIndex = ArraySelected.GetSize();

				while((bContinue == TRUE) && (nIndex < nMaxIndex))
				{
					POSITION pos = ArraySelected.FindIndex(nIndex);
					CString strIndex = ArraySelected.GetAt(pos);

					if (strIndex > strFile)
					{
						bContinue = FALSE;
						ArraySelected.InsertAfter(pos, strFile);
					}

					nIndex++;
				}

				if (bContinue)
					ArraySelected.AddTail(strFile);
			}
		}
	}
	strFileDialog.ReleaseBuffer();

	if (ArraySelected.GetCount() > 0)
	{
		BeginWaitCursor();

		if (m_pAlbumForm != NULL)
		{
			// acquisizione nell'album esame //

			m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

			DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
			if (m_pEsamiView->m_pImgManager->ImportImgListMP(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &ArraySelected, FORM_MINI, FALSE, m_lIDImageTIFF) != ArraySelected.GetCount())
			{
				EndWaitCursor();
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMPORTERROR));
			}

			if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
				CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, ArraySelected.GetCount(), "CMultiPageTiffNewEdtDlg::OnBnClickedBtnDisco");

			m_pAlbumForm->AfterMoveEsame();
		}
		else
		{
			// acquisizione negli allegati //

			CEditDateStringDlg dlgComm(this, IDS_DOCUMENT_COMMENT, CVistaDocumentiSet().GetDataPersonalizzabile(m_lIDImageTIFF), CVistaDocumentiSet().GetDescrizione(m_lIDImageTIFF));
			if (dlgComm.DoModal() == IDOK)
				if (m_lIDImageTIFF > 0)
					m_pEsamiView->m_pDocManager->EditDoc(m_lIDImageTIFF, dlgComm.GetDescrizione(), dlgComm.GetData());

			// Sandro 04/01/2014 // RAS 20130175 //
			long lImported = 0;
			if (m_bPaziente)
				lImported = m_pEsamiView->m_pDocManager->ImportDocTiffMP(m_pPazienteSet->m_lContatore, 0, dlgComm.GetDescrizione(), dlgComm.GetData(), &ArraySelected, FALSE, m_lIDImageTIFF);
			else
				lImported = m_pEsamiView->m_pDocManager->ImportDocTiffMP(m_pPazienteSet->m_lContatore, m_pEsamiSet->m_lContatore, dlgComm.GetDescrizione(), dlgComm.GetData(), &ArraySelected, FALSE, m_lIDImageTIFF);

			//
			if (lImported != ArraySelected.GetCount())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMPORT_FAILED));
				return;
			}

			// RiempiLista(); // lo faccio da fuori //
		}

		ArraySelected.RemoveAll();
		EndWaitCursor();
	}

	UpdateData(TRUE);

	EndDialog(IDOK);
}

void CMultiPageTiffNewEdtDlg::OnBnClickedBtnScanner()
{
    if (!m_pEsamiSet->IsOpen() || m_pEsamiSet->IsBOF() || m_pEsamiSet->IsEOF())
        return;
 
	if (!theApp.m_bCanAcquire)
		return;

	if (m_pAlbumForm != NULL)
	{
		// acquisizione nell'album esame //

		if (m_pAlbumForm->CheckTempFolder())
		{
			// creo la stringa con la data di oggi //
			SYSTEMTIME SystemTime;
			GetLocalTime(&SystemTime);	
			CString strDataOggi;
			strDataOggi.Format("%04d%02d%02d", SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay);

			// creo la stringa con la data dell'esame //
			CCustomDate ExamTime(m_pEsamiSet->m_lData);
			CString strDataEsame = ExamTime.GetDate("%Y%m%d");

			// confronto le due date e se diverse do un alert che forse si è su un esame sbagliato //
			if (strDataOggi != strDataEsame)
			{
				if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_LAUNCHACQUISITION), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
				{
					EndDialog(IDOK);
					return;
				}
			}

			// long lLockedPatient = m_pEsamiView->m_pEsamiSet->m_lPaziente;
			long lLockedExam = m_pEsamiView->m_pEsamiSet->m_lContatore;
			if (CLockManager::Get()->LockExam(lLockedExam))
			{
				if (!VerificaPercorso(theApp.m_sDirTemp))
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_ERR_PATH) + theApp.m_sDirTemp);
					return;
				}

				char szBuffer[512];

				sprintf_s(szBuffer, "%s", theApp.m_sDirTemp);
				WritePrivateProfileString("xTwain", "Path", szBuffer, theApp.m_sFileConfig);

				sprintf_s(szBuffer, "%08d_%08d_", m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);
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
					strWildcard.Format("%s\\%08d_%08d_*.*", theApp.m_sDirTemp, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

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
								if ((strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0))
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

									DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
									if (m_pEsamiView->m_pImgManager->ImportImgListMP(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &listPath, FORM_MINI, FALSE, m_lIDImageTIFF) > 0)
										DeleteFile(strAddFile);
									if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
										CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, 1, "CMultiPageTiffNewEdtDlg::OnBnClickedBtnScanner");

									listPath.RemoveAll();
								}
							}
						} while(FindNextFile(hFile, &dataFile));
						FindClose(hFile);
					}
					EndWaitCursor();
					m_pAlbumForm->AfterMoveEsame();

				} while(dwState == WAIT_TIMEOUT);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				// <-- Sandro 04/05/2010 - RAS 20100072 //

				CLockManager::Get()->UnlockExam(lLockedExam);
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_IMPORT_PREVIMAGE));
			EndDialog(IDOK);
			return;
		}
	}
	else
	{
		// acquisizione negli allegati //

		if (!theApp.m_bCanAcquire)
			return;

		if (!VerificaPercorso(theApp.m_sDirTemp))
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_ERR_PATH) + theApp.m_sDirTemp);
			return;
		}

		// Sandro 27/09/2013 // RAS 20130154 //

		CEditDateStringDlg dlgComm(this, IDS_DOCUMENT_COMMENT, CVistaDocumentiSet().GetDataPersonalizzabile(m_lIDImageTIFF), CVistaDocumentiSet().GetDescrizione(m_lIDImageTIFF));
		if (dlgComm.DoModal() == IDOK)
			if (m_lIDImageTIFF > 0)
				m_pEsamiView->m_pDocManager->EditDoc(m_lIDImageTIFF, dlgComm.GetDescrizione(), dlgComm.GetData());

		//

		char szBuffer[512];

		sprintf_s(szBuffer, "%s", theApp.m_sDirTemp);
		WritePrivateProfileString("xTwain", "Path", szBuffer, theApp.m_sFileConfig);

		sprintf_s(szBuffer, "%08d_%08d_", m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);
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
			strWildcard.Format("%s\\%08d_%08d_*.*", theApp.m_sDirTemp, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

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
						if ((strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0))
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

							// Sandro 04/01/2014 // RAS 20130175 //
							long lImported = 0;
							if (m_bPaziente)
								lImported = m_pEsamiView->m_pDocManager->ImportDocTiffMP(m_pPazienteSet->m_lContatore, 0, dlgComm.GetDescrizione(), dlgComm.GetData(), &listPath, FALSE, m_lIDImageTIFF);
							else
								lImported = m_pEsamiView->m_pDocManager->ImportDocTiffMP(m_pPazienteSet->m_lContatore, m_pEsamiSet->m_lContatore, dlgComm.GetDescrizione(), dlgComm.GetData(), &listPath, FALSE, m_lIDImageTIFF);

							//
							if (lImported > 0)
								DeleteFile(strAddFile);

							listPath.RemoveAll();
						}
					}
				} while(FindNextFile(hFile, &dataFile));
				FindClose(hFile);
			}
			EndWaitCursor();

		} while(dwState == WAIT_TIMEOUT);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		// <-- Sandro 04/05/2010 - RAS 20100072 //
	}

	UpdateData(TRUE);

	EndDialog(IDOK);
}