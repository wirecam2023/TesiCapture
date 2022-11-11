#include "stdafx.h"
#include "Endox.h"
#include "WaitingAutoImportDlg.h"

#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\AmRes.h"

#include <io.h>

#include "AlbumForm.h"
#include "EsamiView.h"
#include "InsertLogAcquisizioneSPSet.h"
#include "LogFileWriter.h"
#include "MmSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CWaitingAutoImportDlg, CDialog)

CWaitingAutoImportDlg::CWaitingAutoImportDlg(CWnd* pParent, CAlbumForm* pAlbumForm, BOOL p_bIsContinuousCapture)
: CDialog(CWaitingAutoImportDlg::IDD, pParent)
{
	m_pAlbumForm = pAlbumForm;

	m_bExit = FALSE;
	m_lImmaginiAcquisite = 0;
	m_bIsContinuousCapture = p_bIsContinuousCapture; //Gabriel BUG 7768 - Continuous capture problem
}

CWaitingAutoImportDlg::~CWaitingAutoImportDlg()
{
}

void CWaitingAutoImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ANIM, m_ctrlAnim);

	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_PROGRESS_LABEL1, m_ctrlStaticProgress1);
	DDX_Control(pDX, IDC_PROGRESS_LABEL2, m_ctrlStaticProgress2);
	DDX_Control(pDX, IDC_PROGRESS_LABEL3, m_ctrlStaticProgress3);
}

BEGIN_MESSAGE_MAP(CWaitingAutoImportDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CWaitingAutoImportDlg::OnCancel()
{
}

BOOL CWaitingAutoImportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStaticProgress1.SetFont(&theApp.m_fontBold);
	m_ctrlStaticProgress2.SetFont(&theApp.m_fontBold);
	m_ctrlStaticProgress3.SetFont(&theApp.m_fontBigBig);

	if (HMODULE hModule = ::LoadLibrary("Amres.dll"))
	{
		HINSTANCE hInstance = AfxGetResourceHandle();
		AfxSetResourceHandle(hModule);
		m_ctrlAnim.Open(Amres_waiting);
		m_ctrlAnim.Play(0, -1, -1);
		AfxSetResourceHandle(hInstance);
	}

	CInsertLogAcquisizioneSPSet().Exec(m_pAlbumForm->m_pEsamiView->m_pPazientiSet->m_lContatore, m_pAlbumForm->m_pEsamiView->m_pEsamiSet->m_lContatore, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.GetMessageString(IDS_ACQUISIZIONE_INIZIO));

	SetTimer(0x573, 1000, NULL);

	theApp.LocalizeDialog(this, CWaitingAutoImportDlg::IDD, "WaitingAutoImportDlg");

	// SPOSTO TUTTE LE IMMAGINI GIA' PRESENTI IN UN'ALTRA CARTELLA TEMPORANEA //

	if (theApp.m_sDirTempAcq2.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PERCORSOSECONDARIO_NONIMPOSTATO));
	}
	else
	{
		BeginWaitCursor();

		if (VerificaPercorso(theApp.m_sDirTempAcq2))
		{
			long lImported = 0;

			CFileFind finder;
			BOOL bWorking = finder.FindFile(theApp.m_sDirTempAcq + "\\*.*");
			while(bWorking)
			{
				bWorking = finder.FindNextFile();

				if (finder.IsDirectory())
				{
					if (!finder.IsDots())
						lImported += MoveImagesFromPathToPath(finder.GetFilePath());
				}
			}

			if (lImported > 0)
			{
				CString sMessage;
				sMessage.Format(theApp.GetMessageString(IDS_ACQUISIZIONE_MESSAGGIO4), m_lImmaginiAcquisite);
				CInsertLogAcquisizioneSPSet().Exec(m_pAlbumForm->m_pEsamiView->m_pPazientiSet->m_lContatore, m_pAlbumForm->m_pEsamiView->m_pEsamiSet->m_lContatore, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, sMessage);
			}
		}

		EndWaitCursor();
	}

	//Gabriel BUG 7768 - Continuous capture problem
	if (!m_bIsContinuousCapture)
		DeleteEmptyDirectories();

	//
	return TRUE;
}

void CWaitingAutoImportDlg::OnOK()
{
	m_ctrlBtnOK.EnableWindow(FALSE);
	m_bExit = TRUE;
	m_pParentWnd->SendMessage(WM_WAITINGAUTOIMPORT_CLOSING); //Gabriel BUG 7768 - Continuous capture problem
}

HBRUSH CWaitingAutoImportDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_PROGRESS_LABEL3:
	{
		pDC->SetTextColor(theApp.m_color[0]);
		break;
	}
	}

	return hBrush;
}

void CWaitingAutoImportDlg::OnTimer(UINT nIDEvent)
{
	KillTimer(nIDEvent);

	if (nIDEvent == 0x573)
	{
		BeginWaitCursor();

		long lImported = 0;

		CFileFind finder;
		BOOL bWorking = finder.FindFile(theApp.m_sDirTempAcq + "\\*.*");
		while(bWorking)
		{
			bWorking = finder.FindNextFile();

			if (finder.IsDirectory())
			{
				if (!finder.IsDots())
					lImported += ImportAndDeleteImagesFromPath(finder.GetFilePath());
			}
		}

		if (lImported > 0)
		{
			SetDlgItemInt(IDC_PROGRESS_LABEL3, m_lImmaginiAcquisite, FALSE);

			//

			CString sMessage;
			sMessage.Format(theApp.GetMessageString(IDS_ACQUISIZIONE_MESSAGGIO3), m_lImmaginiAcquisite);
			CInsertLogAcquisizioneSPSet().Exec(m_pAlbumForm->m_pEsamiView->m_pPazientiSet->m_lContatore, m_pAlbumForm->m_pEsamiView->m_pEsamiSet->m_lContatore, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, sMessage);

			//

			m_pAlbumForm->AfterMoveEsame(TRUE, TRUE);
		}

		EndWaitCursor();

		// --- //

		if (m_bExit)
		{
			DeleteEmptyDirectories();

			CInsertLogAcquisizioneSPSet().Exec(m_pAlbumForm->m_pEsamiView->m_pPazientiSet->m_lContatore, m_pAlbumForm->m_pEsamiView->m_pEsamiSet->m_lContatore, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.GetMessageString(IDS_ACQUISIZIONE_FINE));

			CDialog::OnOK();
		}
		else
		{
			SetTimer(0x573, 1000, NULL);
		}
	}
}

void CWaitingAutoImportDlg::DeleteEmptyDirectories()
{
	BeginWaitCursor();

	CFileFind finder1;
	BOOL bWorking1 = finder1.FindFile(theApp.m_sDirTempAcq + "\\*.*");
	while(bWorking1)
	{
		bWorking1 = finder1.FindNextFile();

		if (finder1.IsDirectory())
		{
			if (!finder1.IsDots())
			{
				BOOL bFull = FALSE;

				CFileFind finder2;
				BOOL bWorking2 = finder2.FindFile(finder1.GetFilePath() + "\\*.*");
				while(bWorking2)
				{
					bWorking2 = finder2.FindNextFile();

					if (!finder2.IsDots())
					{
						bFull = TRUE;
						break;
					}
				}

				if (!bFull)
					RemoveDirectory(finder1.GetFilePath());
			}
		}
	}

	EndWaitCursor();
}

long CWaitingAutoImportDlg::ImportAndDeleteImagesFromPath(CString sPath)
{
	long lReturn = 0;

	CFileFind finder;
	BOOL bWorking = finder.FindFile(sPath + "\\*.jpg") || finder.FindFile(sPath + "\\*.bmp"); //Gabriel BUG 7768 - Continuous capture problem
	while(bWorking)
	{
		bWorking = finder.FindNextFile();

		Sleep(1000); // metto un secondo di delay per non acquisire l'immagine prima che l'endoscopio abbia finito di scriverla completamente //
		if (ImportaImmagine(finder.GetFilePath()) > 0)
		{
			m_lImmaginiAcquisite++;
			SetDlgItemInt(IDC_PROGRESS_LABEL3, m_lImmaginiAcquisite, FALSE);
			lReturn++;
		}
	}

	return lReturn;
}

long CWaitingAutoImportDlg::ImportaImmagine(CString strFile)
{
	long lReturn = 0;

	if (_access(strFile, 0) == 0)
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

		//
		CImgIDList listIDImageImported;
		m_pAlbumForm->m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pAlbumForm->m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pAlbumForm->m_pEsamiView->m_pEsamiSet->m_lContatore);

		DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
		if (m_pAlbumForm->m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, 0, &listPath, FORM_IMM, FORM_MINI, &listIDImageImported, bExportToPacs, FALSE, FALSE) > 0)
		{
			if (listIDImageImported.GetCount() > 0)
				lReturn = listIDImageImported.GetHead();

			// --- //

			DeleteFile(strFile);

			// --- //

			CString sMiniToDelete = "";
			int i1 = strFile.ReverseFind('\\') + 1;
			int i2 = strFile.ReverseFind('.');
			sMiniToDelete = strFile.Left(i1) + "s" + strFile.Mid(i1, i2 - i1) + ".tif";

			DeleteFile(sMiniToDelete);
		}
		if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
			CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pAlbumForm->m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pAlbumForm->m_pEsamiView->m_pEsamiSet->m_lContatore, 1, "CWaitingAutoImportDlg::ImportaImmagine");

		listPath.RemoveAll();
	}

	return lReturn;
}

long CWaitingAutoImportDlg::MoveImagesFromPathToPath(CString sPathOrigine)
{
	long lReturn = 0;

	CFileFind finder;
	BOOL bWorking = finder.FindFile(sPathOrigine + "\\*.jpg") || finder.FindFile(sPathOrigine + "\\*.bmp"); //Gabriel BUG 7768 - Continuous capture problem
	while(bWorking)
	{
		bWorking = finder.FindNextFile();

		int nTemp = sPathOrigine.ReverseFind('\\');
		CString sPathDestinazione = theApp.m_sDirTempAcq2 + sPathOrigine.Right(sPathOrigine.GetLength() - nTemp);

		if (VerificaPercorso(sPathDestinazione))
		{
			CString sFileOrigine = finder.GetFilePath();
			CString sFileDestinazione = sPathDestinazione + "\\" + finder.GetFileName();

			if (MoveFile(sFileOrigine, sFileDestinazione))
				lReturn++;
		}
	}

	return lReturn;
}
