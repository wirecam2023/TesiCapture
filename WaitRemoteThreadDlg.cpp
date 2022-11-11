#include "stdafx.h"
#include "Endox.h"
#include "WaitRemoteThreadDlg.h"

#include "DLL_Imaging\h\AmRes.h"

#include "EsamiView.h"
#include "LogFileWriter.h"
#include "MmSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CWaitRemoteThreadDlg, CDialog)

CWaitRemoteThreadDlg::CWaitRemoteThreadDlg(CWnd* pParent, CEsamiView* pEsamiView, long lPaziente, long lEsame)
	: CDialog(CWaitRemoteThreadDlg::IDD, pParent)
{
	m_ThreadParam.pEsamiView = pEsamiView;
	m_ThreadParam.lPaziente = lPaziente;
	m_ThreadParam.lEsame = lEsame;
}

CWaitRemoteThreadDlg::~CWaitRemoteThreadDlg()
{
}

BEGIN_MESSAGE_MAP(CWaitRemoteThreadDlg, CDialog)

	ON_MESSAGE(EM_DESTROY_WAITREMOTETHREADDLG, OnDestroyWaitRemoteThreadDlg)
	ON_MESSAGE(EPM_THREAD_IMPORT_IMAGE, OnUpdateProgress)

END_MESSAGE_MAP()

void CWaitRemoteThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ANIM, m_ctrlAnim);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
}

void CWaitRemoteThreadDlg::OnCancel()
{
}

BOOL CWaitRemoteThreadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CWaitRemoteThreadDlg::IDD, "WaitRemoteThreadDlg");

	m_ThreadParam.hWndParent = GetSafeHwnd();

	AfxBeginThread(Thread, &m_ThreadParam, THREAD_PRIORITY_NORMAL);

	if (HMODULE hModule = ::LoadLibrary("Amres.dll"))
	{
		HINSTANCE hInstance = AfxGetResourceHandle();
		AfxSetResourceHandle(hModule);
		m_ctrlAnim.Open(Amres_waiting);
		m_ctrlAnim.Play(0, -1, -1);
		AfxSetResourceHandle(hInstance);
	}

	CString strWildcard;
	strWildcard.Format("%s\\%08d_%08d_*.*", 
		               theApp.m_sDirTempAcq,
					   m_ThreadParam.lPaziente,
					   m_ThreadParam.lEsame);

	// Recupero il numero di file da analizzare
	long numeroFile = 0;
	CStringList listPath;
	WIN32_FIND_DATA dataFile;
	HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		numeroFile = 1;
		while(FindNextFile(hFile, &dataFile))
			numeroFile++;
	}

	m_ctrlProgress.SetRange32(0, numeroFile);
	m_ctrlProgress.SetPos(0);

	GetDlgItem(IDC_PROGRESS_LABEL)->SetWindowText(theApp.GetMessageString(IDS_IMPORTAZIONE_WAIT));

	return TRUE;
}

void CWaitRemoteThreadDlg::OnOK()
{
}

LRESULT CWaitRemoteThreadDlg::OnDestroyWaitRemoteThreadDlg(WPARAM wParam, LPARAM lParam)
{
	CDialog::OnOK();
	return 0;
}

LRESULT CWaitRemoteThreadDlg::OnUpdateProgress(WPARAM wParam, LPARAM lParam)
{
	m_ctrlProgress.SetPos(m_ctrlProgress.GetPos() + 1);
	return 0;
}

UINT CWaitRemoteThreadDlg::Thread(LPVOID pParam)
{
	tagTHREAD* param = (tagTHREAD*)pParam;

	if FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED))
		return 0;

	// importo solo le immagini e/o filmati dell'esame corrente //
	CString strWildcard;
	strWildcard.Format("%s\\%08d_%08d_*.*", 
		               theApp.m_sDirTempAcq,
					   param->lPaziente,
					   param->lEsame);

	//
	CStringList listPath;
	WIN32_FIND_DATA dataFile;
	HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		do
		{
			// Aggiorno la barra di avanzamento
			::SendMessage(param->hWndParent, EPM_THREAD_IMPORT_IMAGE, 0, 0);

			CString strFile(dataFile.cFileName);

			if (strFile.GetLength() > 3)
			{
				if ((strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0))
				{
					CString strAddFile = theApp.m_sDirTempAcq + "\\" + strFile;

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

					BOOL export2Pacs = FALSE;
					// In modalità 2 devo avviare il trasferimento automatico su PACS
					if (theApp.m_lDcmStoreMode == 2)
						export2Pacs = TRUE;

					CImgIDList outputImgIdList;

					DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
					if (param->pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &listPath, FORM_IMM, FORM_MINI, &outputImgIdList, export2Pacs, FALSE, FALSE) > 0)
					{
						// importo anche il file .MIS associato //
						long lLastID = 0;

						/*CImgIDList IdList;
						int nCount = param->pEsamiView->m_pImgManager->GetImgIDList(&IdList);

						POSITION pos = IdList.GetHeadPosition();
						while(pos != NULL)
						{
							long lID = IdList.GetNext(pos);
							if (lID > lLastID)
								lLastID = lID;
						}*/

						POSITION pos = outputImgIdList.GetHeadPosition();
						if (pos)
						{
							lLastID = outputImgIdList.GetNext(pos);
						}

						if (lLastID > 0)
						{
							CString strLastFile = param->pEsamiView->m_pImgManager->GetFullPath(lLastID);

							CString strOrigMis = strAddFile.Left(strAddFile.GetLength() - 4) + ".MIS";
							if (theApp.m_nApplication != PRG_ENDOX)
							{
								CString strDestMis = strLastFile.Left(strLastFile.GetLength() - 4) + ".MIS";
								CopyFile(strOrigMis, strDestMis, FALSE);
							}

							if (DeleteFileSecure(strAddFile, strLastFile))
								DeleteFile(strOrigMis);
						}
					}
					if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
						CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, param->lPaziente, param->lEsame, 1, "CWaitRemoteThreadDlg::Thread");

					listPath.RemoveAll();
				}
			}
		} while(FindNextFile(hFile, &dataFile));
		FindClose(hFile);
	}

	::PostMessage(param->hWndParent, EM_DESTROY_WAITREMOTETHREADDLG, NULL, NULL);
	delete param;

	::CoUninitialize();

	return 0;
}