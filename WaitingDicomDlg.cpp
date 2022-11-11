#include "stdafx.h"
#include "Endox.h"
#include "WaitingDicomDlg.h"
#include "LogFileWriter.h"			// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
#include "DLL_Imaging\h\AmRes.h"
#include "EsamiView.h"
#include "Common.h"
#include <io.h>
#include "CommonCLR.h"

#include "MmSystem.h" //Gabriel BUG 7768 - Continuous capture problem

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LOCALTIMER  0x585
#define LOCALTIMER2 0x586

IMPLEMENT_DYNAMIC(CWaitingDicomDlg, CDialog)

CWaitingDicomDlg::CWaitingDicomDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL p_bIsContinuousCapture)	// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM DICOM
	: CDialog(CWaitingDicomDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_bExit = FALSE;
	m_pEsamiView = pEsamiView;
	
	m_bIsContinuousCapture = p_bIsContinuousCapture;
	m_bIsContinuousCaptureImporting = FALSE; //indico que a captura continua inda nao esta importando nada
	m_iQtyFilesCapturaContinua = 0; //zero o contador de imagens importadas

	m_pEsamiView->m_bImporting = TRUE; //indico que o sistema esta em fase de importacao de imagens
	strLogInThread = "\r\n"; //inicializo a string de log da thread
	
	m_listHashesAlreadyImported.RemoveAll(); //limpo a lista de hashes

	LogMessage("Executando CWaitingDicomDlg::Constructor()");

	InitializeCriticalSection(&m_cs);
}

CWaitingDicomDlg::~CWaitingDicomDlg()
{
	LogMessage("Executando CWaitingDicomDlg::Destructor()");
	DeleteCriticalSection(&m_cs);
}

BEGIN_MESSAGE_MAP(CWaitingDicomDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ESCI, OnBnClickedBtnEsci)
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CWaitingDicomDlg::DoDataExchange(CDataExchange* pDX)
{
	//registro todos os controles
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ANIM,			 m_ctrlAnim);
	DDX_Control(pDX, IDC_BTN_ESCI,		 m_ctrlBtnTerminaAcquisizione);
	DDX_Control(pDX, IDC_PROGRESS_LABEL, m_ctrlStaticProgressLabel);
	DDX_Control(pDX, IDC_NUMEROIMMAGINI, m_ctrlStaticNumeroImmagini);
}

BOOL CWaitingDicomDlg::OnInitDialog()
{
	LogMessage("Executando CWaitingDicomDlg::OnInit()"); //logo que entrei no metodo

	CDialog::OnInitDialog();

	m_ctrlStaticNumeroImmagini.SetFont(&theApp.m_fontBig); //coloco a fonte padrao

	if (HMODULE hModule = ::LoadLibrary("Amres.dll")) //carrego a biblioteca de recursos
	{
		HINSTANCE hInstance = AfxGetResourceHandle(); //instancio o handle
		AfxSetResourceHandle(hModule);
		m_ctrlAnim.Open(Amres_waiting); //seleciono a animacao
		m_ctrlAnim.Play(0, -1, -1); //inicio a animacao
		AfxSetResourceHandle(hInstance); 
	}

	theApp.LocalizeDialog(this, CWaitingDicomDlg::IDD, "WaitingDicomDlg"); //traduzo a tela

	if (m_bIsContinuousCapture)
	{
		CImgIDList listCount;
		m_pEsamiView->m_pImgManager->GetImgIDList(&listCount);
		m_lAlbumCount = listCount.GetCount();
		listCount.RemoveAll();

		SetTimer(LOCALTIMER2, 1000, NULL);

		//Gabriel BUG 7768 - Continuous capture problem
		//AcquisizioneCapturaContinua(); //em caso de captura continua eu iniciarei a thread
	}
	else
	{
		SetTimer(LOCALTIMER, 1000, NULL); //para captura normal eu inicio o timer
	}

	return TRUE;
}

void CWaitingDicomDlg::CreateModelessDialog(CWnd* pParent)
{
	Create(CWaitingDicomDlg::IDD, pParent);
}

void CWaitingDicomDlg::OnBnClickedBtnEsci()
{
	LogMessage("Executando CWaitingDicomDlg::OnBnClickedBtnEsci()");

	BeginWaitCursor();

	m_ctrlBtnTerminaAcquisizione.EnableWindow(FALSE); //desabilito o botao para que o usuario nao pressione mais de uma vez
	m_bExit = TRUE; //sinalizo para a thread de importacao que ela precisa parar

	m_ctrlStaticNumeroImmagini.SetWindowText("Finalizando captura..."); //coloco o texto na tela

	KillAndExit();

	EndWaitCursor();
}

void CWaitingDicomDlg::OnCancel()
{
	//nao faco nada
}

void CWaitingDicomDlg::OnOK()
{
	//nao faco nada
}

// do not capture anything, just find files and show on Dialog how many was found...
void CWaitingDicomDlg::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if (nIDEvent == LOCALTIMER)
	{
		int iNumeroFiles = CountImageFilesInFolder(); //conto quantos arquivos de imagem para este exame tem na pasta de importacao

		CString sImmaginiAcquisite; //gero o texto que vai aparecer para o usuario na tela
		sImmaginiAcquisite.Format("%s: %d", theApp.GetMessageString(IDS_IMMAGINI_ACQUISITE), iNumeroFiles);

		m_ctrlStaticNumeroImmagini.SetWindowText(sImmaginiAcquisite); //coloco o texto na tela

		if (m_bExit) //se o usuario clicou para finalizar a captura
			KillAndExit();
	}

	if (nIDEvent == LOCALTIMER2)
	{
		//Gabriel BUG 7768 - Continuous capture problem
		/*
		CImgIDList listCount;
		m_pEsamiView->m_pImgManager->GetImgIDList(&listCount);
		m_iQtyFilesCapturaContinua = listCount.GetCount() - m_lAlbumCount; //conto quantos arquivos de imagem para este exame tem na pasta de importacao
		listCount.RemoveAll();

		CString sImmaginiAcquisite; //gero o texto que vai aparecer para o usuario na tela
		sImmaginiAcquisite.Format("%s: %d", theApp.GetMessageString(IDS_IMMAGINI_ACQUISITE), m_iQtyFilesCapturaContinua);

		m_ctrlStaticNumeroImmagini.SetWindowText(sImmaginiAcquisite); //coloco o texto na tela

		if (m_bExit) //se o usuario clicou para finalizar a captura
			KillTimer(LOCALTIMER2);
			*/
		BeginWaitCursor();

		CImgIDList listCount;
		m_pEsamiView->m_pImgManager->GetImgIDList(&listCount);
		m_iQtyFilesCapturaContinua = listCount.GetCount() - m_lAlbumCount; //conto quantos arquivos de imagem para este exame tem na pasta de importacao
		listCount.RemoveAll();

		long lImported = 0;

		CFileFind finder;
		BOOL bWorking = finder.FindFile(theApp.m_sDirTempAcq + "\\*.*");
		while (bWorking)
		{
			bWorking = finder.FindNextFile();

			if (finder.IsDirectory())
			{
				if (!finder.IsDots())
					m_iQtyFilesCapturaContinua += ImportAndDeleteImagesFromPath(finder.GetFilePath());
			}
		}

		CString sImmaginiAcquisite; //gero o texto que vai aparecer para o usuario na tela
		sImmaginiAcquisite.Format("%s: %d", theApp.GetMessageString(IDS_IMMAGINI_ACQUISITE), m_iQtyFilesCapturaContinua);

		m_ctrlStaticNumeroImmagini.SetWindowText(sImmaginiAcquisite); //coloco o texto na tela

		EndWaitCursor();

		// --- //

		if (m_bExit)
		{
			DeleteEmptyDirectories();

			KillTimer(LOCALTIMER2);
		}
		else
		{
			SetTimer(LOCALTIMER2, 1000, NULL);
		}
	}
}

int CWaitingDicomDlg::CountImageFilesInFolder()
{
	//wildcard usado para o paciente e exame atual
	CString strWildcard;
	strWildcard.Format("%s\\%08d_%08d_*.*", 
		theApp.m_sDirTempAcq, 
		m_pEsamiView->m_pEsamiSet->m_lPaziente, 
		m_pEsamiView->m_pEsamiSet->m_lContatore);

	
	int iNumeroFiles = 0;
	
	//Procuro arquivos com o wildcard na pasta
	WIN32_FIND_DATA dataFile;
	HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
	//

	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		do
		{
			CString strFile(dataFile.cFileName);

			if (strFile.GetLength() > 3) //verifico se o tamanho do nome é valido
			{
				strFile = strFile.Right(3); //verifico se a extensao do arquivo e compativel com o que eu posso importar
				if ((strFile.CompareNoCase("bmp") == 0) || (strFile.CompareNoCase("mpg") == 0) || 
					(strFile.CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.CompareNoCase("dcm") == 0))
					iNumeroFiles++; //acrescento ao contador
			}

		} while (FindNextFile(hFile, &dataFile)); //loop enquanto tiver arquivos deste formato na pasta
	}
	FindClose(hFile); //finalizo a pesquisa

	return iNumeroFiles; //retorno o numero de arquivos encontrados
}

void CWaitingDicomDlg::KillAndExit()
{
	LogMessage("Executando CWaitingDicomDlg::KillAndExit()"); //logo que entrei no metodo

	if (!m_bIsContinuousCapture) //mato o timer
		KillTimer(LOCALTIMER);
	

	m_bIsContinuousCaptureImporting = FALSE; //indico que a captura continua foi finalizada
	m_pEsamiView->m_bImporting = FALSE; //indico que o exame saiu de modo de captura
	m_listHashesAlreadyImported.RemoveAll(); //limpo a lista de hashes importados
	
	if (!strLogInThread.IsEmpty()) //se a thread tiver escrito algum log eu escrevo agora no arquivo
		CLogFileWriter::Get()->WriteLogLine0(strLogInThread);	

	m_pParentWnd->SendMessage(WM_WAITINGDICOM_CLOSING); //envio uma mensagem ao AlbumForm que esta tela vai ser encerrada

	CDialog::OnOK();
}


void CWaitingDicomDlg::AcquisizioneCapturaContinua()
{		
	m_iQtyFilesCapturaContinua = 0; //zero a quantidade de arquivos importados
	
	if (m_bIsContinuousCapture && !theApp.m_bContingencia && theApp.m_bArchivioImmaginiThreadImport && !m_bIsContinuousCaptureImporting) //verifico novamente que estou em captura continua
	{
		AfxBeginThread(AcqFromTeleImportThreadCapturaContinua, this); //inicio a thread de importacao
	}
}
UINT CWaitingDicomDlg::AcqFromTeleImportThreadCapturaContinua(LPVOID pParam)
{
	//AfxMessageBox("CWaitingDicomDlg AcqFromTeleImportThreadCapturaContinua()");

	// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
	CWaitingDicomDlg *p_this = (CWaitingDicomDlg*)pParam;
	CEsamiView* pEsamiView = p_this->m_pEsamiView;

	if (p_this->m_bIsContinuousCaptureImporting) // already running
	{
		//AfxMessageBox("CWaitingDicomDlg AcqFromTeleImportThreadCapturaContinua() tentou entrar pela 2a vez na Thread!");
		SYSTEMTIME st; GetLocalTime(&st); TCHAR szDateNow[1024]; sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		CString strLog = "";
		strLog.Format("[%s] %s paziente=%ld esame=%ld"
			, szDateNow
			, "CWaitingDicomDlg AcqFromTeleImportThreadCapturaContinua() tentou entrar pela 2a vez na Thread!"
			, pEsamiView->m_pPazientiSet->m_lContatore
			, pEsamiView->m_pEsamiSet->m_lContatore
			);
		//CLogFileWriter::Get()->WriteLogLine0(strLog);
		p_this->strLogInThread += strLog + "\r\n";

		return 0;
	}

	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
		return 0;

	SYSTEMTIME st; GetLocalTime(&st); TCHAR szDateNow[1024]; sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	CString strLog = "";
	strLog.Format("[%s] INSTANCIADA NOVA THREAD em %s >>> p_this->m_iQtyFilesCapturaContinua = %do. paziente=%ld esame=%ld"
		, szDateNow
		, "CWaitingDicomDlg::AcqFromTeleImportThreadCapturaContinua"
		, p_this->m_iQtyFilesCapturaContinua
		, pEsamiView->m_pPazientiSet->m_lContatore
		, pEsamiView->m_pEsamiSet->m_lContatore
		);
	//CLogFileWriter::Get()->WriteLogLine0(strLog);
	p_this->strLogInThread += strLog + "\r\n";

	// visualizzo la barra di avanzamento //
	int nPos = 0;
	//pEsamiView->SendMessage(EPM_THREAD_IMPORT_SETPOS, nPos, 0);

	do
	{
		BOOL bImportedSomething = FALSE;

		// importo solo le immagini e/o filmati dell'esame corrente //
		CString strWildcard;
		strWildcard.Format("%s\\%08d_%08d_*.*",
			theApp.m_sDirTempAcq,
			pEsamiView->m_pPazientiSet->m_lContatore,
			pEsamiView->m_pEsamiSet->m_lContatore);

		//
		CStringList listPath;
		WIN32_FIND_DATA dataFile;
		HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
		if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
		{
			BOOL bDBOpened = FALSE;
			CAMBaseDB tempDbEndox;

			if (theApp.m_sPassedConnectionString.IsEmpty())
				bDBOpened = tempDbEndox.OpenDirect(theApp.m_sFileConfig);
			else
				bDBOpened = tempDbEndox.OpenEx(theApp.m_sPassedConnectionString, CDatabase::noOdbcDialog); // Sandro 07/12/2015 // RIMA 15135 //

			if (bDBOpened)
			{
				//configuro o ImgManager
				CImgManager tempImgManager(theApp.m_sPathImageOD, &tempDbEndox);
				if (theApp.m_nApplication == PRG_CARDIOX)
				{
					tempImgManager.SetThumbStoreSize(CSize(HSIZE_PAL / 2, VSIZE_PAL / 2));
					tempImgManager.SetThumbRetrieveSize(CSize(HSIZE_PAL / 2, VSIZE_PAL / 2));
				}
				else
				{
					tempImgManager.SetThumbStoreSize(CSize(HSIZE_PAL / 4, VSIZE_PAL / 4));
					tempImgManager.SetThumbRetrieveSize(CSize(HSIZE_PAL / 4, VSIZE_PAL / 4));
				}
				tempImgManager.SetImageExt(CString(EXT_IMG).Right(3));
				tempImgManager.SetThumbExt(CString(EXT_WIN).Right(3));
				tempImgManager.SetMovieBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_FILM)), RGB(255, 255, 255));
				tempImgManager.SetTiffBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_TIFF)), RGB(255, 255, 255));
				tempImgManager.SetPrintBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PRINT)), RGB(255, 0, 0), bottomright);
				tempImgManager.SetSelectBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SELEZIONE)), RGB(0, 255, 0), topleft);
				tempImgManager.SetDicomBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DICOM_IMM)), RGB(255, 255, 255));
				tempImgManager.SetDicomMovieBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DICOM_FILM)), RGB(255, 255, 255));
				tempImgManager.SetCIBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ICON_CI)), RGB(255, 255, 255));
				tempImgManager.SetImageQuality(theApp.m_nArchivioImmaginiQualita, theApp.m_nArchivioMiniatureQualita, 100);

				tempImgManager.SetCurrentIDs(pEsamiView->m_pPazientiSet->m_lContatore, pEsamiView->m_pEsamiSet->m_lContatore);
				//

				//removo todos os readonly 
				CString strFile(dataFile.cFileName);
				strFile = strFile.Mid(strFile.ReverseFind('\\') + 1); //Julio 19/03/2021 Fix erro de import por nomeFile errado
				CString strAddFile = theApp.m_sDirTempAcq + "\\" + strFile;
				LPCTSTR pszFile = strAddFile;
				DWORD dwAttrs = dwAttrs = GetFileAttributes(pszFile);
				if (dwAttrs != INVALID_FILE_ATTRIBUTES)
				{
					try
					{
						SetFileAttributes(pszFile, GetFileAttributes(pszFile) & ~FILE_ATTRIBUTE_READONLY);
					}
					catch (...)
					{
						//
					}
				}
				//

				//importo as imagens uma a uma
				hFile = FindFirstFile(strWildcard, &dataFile);
				do
				{
					double dKb = 0;
					LONGLONG QuadPart;

					CString strFile(dataFile.cFileName);
					strFile = strFile.Mid(strFile.ReverseFind('\\') + 1); //Julio 19/03/2021 Fix erro de import por nomeFile errado

					if (strFile.GetLength() > 3 && ((strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) 
					|| (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0)))
					{
						CString strAddFile = theApp.m_sDirTempAcq + "\\" + strFile;

						// controllo che la dimensione del file sia maggiore di 0 (capita per certi filmati e si blocca tutto) //
						HANDLE hFileSize = CreateFile(strAddFile, STANDARD_RIGHTS_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						if ((hFileSize != NULL) && (hFileSize != INVALID_HANDLE_VALUE))
						{
							LARGE_INTEGER llTemp;
							if (GetFileSizeEx(hFileSize, &llTemp))
							{
								dKb = ((double)llTemp.QuadPart / (double)1024.0f);
								QuadPart = llTemp.QuadPart;
							}
						}
						CloseHandle(hFileSize);

						// Controlo o Hash da imagem para ver se ja nao importei ela
						CString sHASH = CCommonCLR::GetHASHFromFile(strAddFile);
						if (!sHASH.IsEmpty() && !p_this->IsHashAlreadyImported(sHASH))
						{
							if (QuadPart > 0)
							{
								if ((_access(strAddFile, 6)) == 00) //verifico se o arquivo atual tem permissão de leitura e gravação									
									listPath.AddHead(strAddFile);
							}
							/*else 
								DeleteFile(strAddFile);*/
						}
						else
						{
							//AcqFromTeleImportThreadMoveFile(p_this, strFile, pEsamiView->m_pPazientiSet->m_lContatore, pEsamiView->m_pEsamiSet->m_lContatore, sHASH);

							if (_access(strFile, 06) == 0) //verifico se tenho permissao para modificar o arquivo
							{
								//construo o caminho da pasta de erro
								CString strRejectedFilesInImportError = theApp.m_sDirTempAcq + "\\IMPORT_IMG_ERROR"; 
								
								//verifico se o caminho ja existe e em caso negativo crio a pasta
								CreateLogFolderIfNotExists(strRejectedFilesInImportError); 

								//obtenho o caminho completo do arquivo que quero mover (origem)
								CString strOrigFile = theApp.m_sDirTempAcq + "\\" + strFile; 

								//obtenho o caminho completo de onde quero levar o arquivo (destino)
								CString strDestFile = strRejectedFilesInImportError + "\\" + strFile; 
								MoveFile(strOrigFile, strDestFile);
							}
						}

						BOOL export2Pacs = theApp.m_lDcmStoreMode == 2 ? TRUE : FALSE;
						CImgIDList outputImgIdList;

						if (listPath.GetCount() > 0)
						{
							EnterCriticalSection(&p_this->m_cs);

							long lImportedID = -1;
							CImgIDList ImgImported;
							if (tempImgManager.ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &listPath, FORM_IMM, FORM_MINI, &ImgImported, export2Pacs, FALSE, FALSE) && ImgImported.GetCount() == 1)
							{
								lImportedID = ImgImported.GetHead();
									
								//log and refresh dialog
								bImportedSomething = TRUE;
								p_this->AddAndRefreshNumberInDialog(1);

								p_this->m_listHashesAlreadyImported.AddHead(sHASH);

								SYSTEMTIME st; GetLocalTime(&st); TCHAR szDateNow[1024]; sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
								CString strLog = "";
								strLog.Format("[%s] %s >>> %do.) IMPORTADO nomearq:'%s' TAMANHO: %g kb; paziente=%ld esame=%ld hash=%s"
									, szDateNow
									, "CWaitingDicomDlg::AcqFromTeleImportThreadCapturaContinua"
									, p_this->m_iQtyFilesCapturaContinua
									, listPath.GetHead()
									, dKb
									, pEsamiView->m_pPazientiSet->m_lContatore
									, pEsamiView->m_pEsamiSet->m_lContatore
									, sHASH
									);

								p_this->strLogInThread += strLog + "\r\n";
								//
									
								//try to importing MIS
								CString strLastFile = tempImgManager.GetFullPath(lImportedID);

								CString strOrigMis = strAddFile.Left(strAddFile.GetLength() - 4) + ".MIS";
								if (theApp.m_nApplication != PRG_ENDOX)
								{
									CString strDestMis = strLastFile.Left(strLastFile.GetLength() - 4) + ".MIS";
									CopyFile(strOrigMis, strDestMis, FALSE);
								}

								//if (DeleteFileSecure(strAddFile, strLastFile))
								if (_access(strAddFile, 06) == 0) //verifico se tenho permissao para modificar o arquivo
								{
									DeleteFile(strAddFile);
									DeleteFile(strOrigMis);
								}
								//

								//Esta linha faz o refresh do album
								pEsamiView->SendMessage(EPM_THREAD_IMPORT_SETPOS, (WPARAM)99, 0);
								//Sleep(5000);

							}
							else
							{
								// ERRO NA IMPORTAÇAO
								CString strListPath = "[";
								POSITION p;
								for (p = listPath.GetHeadPosition(); p != NULL;)
								{
									CString strNomeArq(listPath.GetNext(p));
									strListPath += ", " + strNomeArq;
								}
								strListPath += "]";

								SYSTEMTIME st; GetLocalTime(&st); TCHAR szDateNow[1024]; sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
								CString strLog = "";
								strLog.Format("[%s] ERRO NA IMPORTAÇÃO DO CImgManager.ImportImgList() em %s >>> %do.) lista arq:'%s' paziente=%ld esame=%ld"
									, szDateNow
									, "CWaitingDicomDlg::AcqFromTeleImportThreadCapturaContinua"
									, p_this->m_iQtyFilesCapturaContinua
									, strListPath
									, pEsamiView->m_pPazientiSet->m_lContatore
									, pEsamiView->m_pEsamiSet->m_lContatore
									);
								p_this->strLogInThread += strLog + "\r\n";
							}
							LeaveCriticalSection(&p_this->m_cs);
						}
						listPath.RemoveAll();
					}

				} while (FindNextFile(hFile, &dataFile));
				FindClose(hFile);
			}

			if (tempDbEndox.IsOpen())
				tempDbEndox.Close();
		}

		// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
		if (!bImportedSomething)
		{
			Sleep(1000);
			p_this->AddAndRefreshNumberInDialog(0);
		}

	} while (!p_this->m_bExit);	// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM

	//if (nPos < 100)
	pEsamiView->SendMessage(EPM_THREAD_IMPORT_SETPOS, (WPARAM)100, 0);

	::CoUninitialize();

	return 0;
}

void CWaitingDicomDlg::AddAndRefreshNumberInDialog(int p_iUnit)
{
	CString strSpinningSignal; //vai representar um traco rodando ou uma reticencia crescente

	static int iCont = 0; //
	if (p_iUnit == 0)
		strSpinningSignal = (iCont == 0 ? "." : (iCont == 1 ? ".." : (iCont == 2 ? "..." : (iCont == 3 ? "...." : "")))); // waiting spinning signal
	else
		strSpinningSignal = (iCont == 0 ? "|" : (iCont == 1 ? "/" : (iCont == 2 ? "--" : (iCont == 3 ? "\\" : "")))); // working spinning signal

	m_iQtyFilesCapturaContinua += p_iUnit; //adiciono o valor que recebi a quantidade de imagens importadas

	CString sImmaginiAcquisite; //gero o texto que vai aparecer para o usuario na tela
	sImmaginiAcquisite.Format("%s: %d %s", theApp.GetMessageString(IDS_IMMAGINI_ACQUISITE), m_iQtyFilesCapturaContinua, strSpinningSignal);

	m_ctrlStaticNumeroImmagini.SetWindowText(sImmaginiAcquisite); //coloco o texto na tela

	if (iCont++ >= 3) //caso o iCont tenha chegado a 3 volto ele para zero
		iCont = 0;	
}

void CWaitingDicomDlg::AcqFromTeleImportThreadMoveFile(LPVOID pParam, CString p_strFile, long PazientiSetContatore, long EsamiSetContatore, CString sHash)
{
	CWaitingDicomDlg *p_this = (CWaitingDicomDlg*)pParam; //recupero a classe atual como parametro
	
	CString strRejectedFilesInImportError = theApp.m_sDirTempAcq + "\\IMPORT_IMG_ERROR"; //construo o caminho da pasta de erro
	CreateLogFolderIfNotExists(strRejectedFilesInImportError); //verifico se o caminho ja existe e em caso negativo crio a pasta

	CString strOrigFile = theApp.m_sDirTempAcq + "\\" + p_strFile; //obtenho o caminho completo do arquivo que quero mover (origem)
	CString strDestFile = strRejectedFilesInImportError + "\\" + p_strFile; //obtenho o caminho completo de onde quero levar o arquivo (destino)

	try 
	{		
		CString strLog = "";
		if (_access(strOrigFile, 06) == 0) //verifico se tenho permissao para modificar o arquivo
		{
			if (MoveFile(strOrigFile, strDestFile)) //tento mover o arquivo
			{
				strLog.Format("%s %s >>> %do.) ARQUIVO REPETIDO:'%s' HASH: %s MOVIDO DE:'%s' PARA:'%s'."
					, p_this->GetLogString()
					, "CWaitingDicomDlg::AcqFromTeleImportThreadCapturaContinua"
					, p_this->m_iQtyFilesCapturaContinua
					, p_strFile
					, sHash
					, strOrigFile
					, strDestFile
					);
			}
			else //nao consegui mover o arquivo
			{
				strLog.Format("[%s] %s >>> %do.) ERRO NA TENTATIVA DE MOVER O ARQUIVO REPETIDO:'%s' HASH: %s DE:'%s' PARA:'%s'. paziente=%ld esame=%ld"
					, p_this->GetLogString()
					, "CWaitingDicomDlg::AcqFromTeleImportThreadCapturaContinua"
					, p_this->m_iQtyFilesCapturaContinua
					, p_strFile
					, sHash
					, strOrigFile
					, strDestFile
					, PazientiSetContatore
					, EsamiSetContatore
					);
			}
		}
		else
		{
			strLog.Format("[%s] %s >>> %do.) ERRO DE ACESSO NA TENTATIVA DE MOVER O ARQUIVO REPETIDO:'%s' HASH: %s DE:'%s' PARA:'%s'. paziente=%ld esame=%ld"
				, p_this->GetLogString()
				, "CWaitingDicomDlg::AcqFromTeleImportThreadCapturaContinua"
				, p_this->m_iQtyFilesCapturaContinua
				, p_strFile
				, sHash
				, strOrigFile
				, strDestFile
				, PazientiSetContatore
				, EsamiSetContatore
				);
		}
		p_this->strLogInThread += strLog; //adiciono ao log
	}
	catch (CException* e) //em caso de excecao
	{		
		TCHAR szError[255];
		e->GetErrorMessage(szError, 255); //coloco o erro em uma variavel
		e->Delete(); //deleto o erro
		
		CString strLog = "";
		strLog.Format("%s %s >>> %do.) ERRO NA TENTATIVA DE MOVER O ARQUIVO '%s' HASH: %s (Exception: %s) paziente=%ld esame=%ld"
			, p_this->GetLogString()
			, "CWaitingDicomDlg::AcqFromTeleImportThreadCapturaContinua"
			, p_this->m_iQtyFilesCapturaContinua
			, p_strFile
			, sHash
			, szError //mostro qual foi a excecao
			, PazientiSetContatore
			, EsamiSetContatore
			);		
		p_this->strLogInThread += strLog; //adiciono ao log
	}
	return;
}

BOOL CWaitingDicomDlg::IsHashAlreadyImported(CString sHash)
{
	if (m_listHashesAlreadyImported.GetCount() > 0) //vejo se tem pelo menos um hash importado
	{
		for (POSITION pos = m_listHashesAlreadyImported.GetHeadPosition(); pos;) //loop pelos hashes
		{
			CString sCurHash = m_listHashesAlreadyImported.GetNext(pos);
			if (sCurHash == sHash) //se o hash do parametro ja estiver na lista eu retorno true
				return TRUE;
			
		}
	}
	return FALSE; //se o hash do parametro nao esta na lista eu retorno false
}

void CWaitingDicomDlg::LogMessage(CString sMessage)
{
	CString strLog = GetLogString(); //obtenho o texto referente a data
	strLog += sMessage; //concateno a mensagem passada como parametro

	CLogFileWriter::Get()->WriteLogLine0(strLog); //logo no arquivo
}
CString CWaitingDicomDlg::GetLogString()
{
	SYSTEMTIME st;
	GetLocalTime(&st); //pego a data do computador

	TCHAR szDateNow[1024]; //formato a data
	sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	CString strLog = ""; //adiciono a uma string
	strLog.Format("\r\n[%s] ", szDateNow);

	return strLog; //retorno a data formatada
}

//Gabriel BUG 7768 - Continuous capture problem
long CWaitingDicomDlg::ImportAndDeleteImagesFromPath(CString sPath)
{
	long lReturn = 0;

	CFileFind finder;
	CString sTempFolder;
	sTempFolder.Format("\\%08d_%08d",
	m_pEsamiView->m_pEsamiSet->m_lPaziente,
	m_pEsamiView->m_pEsamiSet->m_lContatore);

	if (sPath.Find(sTempFolder) >= 0)
	{
		BOOL bWorking = finder.FindFile(sPath + "\\*.jpg") || finder.FindFile(sPath + "\\*.bmp"); //Gabriel BUG 7768 - Continuous capture problem
		while (bWorking)
		{
			bWorking = finder.FindNextFile();

			Sleep(1000); // metto un secondo di delay per non acquisire l'immagine prima che l'endoscopio abbia finito di scriverla completamente //
			if (ImportaImmagine(finder.GetFilePath()) > 0)
			{
				m_pParentWnd->SendMessage(WM_WAITINGDICOM_AFTERMOVEESAME);

				lReturn++;
			}
		}
	}
	
	return lReturn;
}

//Gabriel BUG 7768 - Continuous capture problem
long CWaitingDicomDlg::ImportaImmagine(CString strFile)
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
//		m_pAlbumForm->m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pAlbumForm->m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pAlbumForm->m_pEsamiView->m_pEsamiSet->m_lContatore);
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

		DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
		if (m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, 0, &listPath, FORM_IMM, FORM_MINI, &listIDImageImported, bExportToPacs, FALSE, FALSE) > 0)
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
			CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, 1, "CWaitingAutoImportDlg::ImportaImmagine");

		listPath.RemoveAll();
	}

	return lReturn;
}

//Gabriel BUG 7768 - Continuous capture problem
void CWaitingDicomDlg::DeleteEmptyDirectories()
{
	BeginWaitCursor();

	CFileFind finder1;
	BOOL bWorking1 = finder1.FindFile(theApp.m_sDirTempAcq + "\\*.*");
	while (bWorking1)
	{
		bWorking1 = finder1.FindNextFile();

		if (finder1.IsDirectory())
		{
			if (!finder1.IsDots())
			{
				BOOL bFull = FALSE;

				CFileFind finder2;
				BOOL bWorking2 = finder2.FindFile(finder1.GetFilePath() + "\\*.*");
				while (bWorking2)
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