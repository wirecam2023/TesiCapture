#include "stdafx.h"
#include "Endox.h"
#include "WaitImportImageDlg.h"

#include "DLL_Imaging\h\AmRes.h"

#include "EsamiView.h"
#include "LogFileWriter.h"
#include "MmSystem.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CWaitImportImageDlg, CDialog)

BOOL CWaitImportImageDlg::m_sbError = FALSE;

CWaitImportImageDlg::CWaitImportImageDlg(CWnd* pParent, CImgManager* pImgManager, CStringList* pImgList)
: CDialog(CWaitImportImageDlg::IDD, pParent)
{
	m_sbError = FALSE;

	m_ThreadParam.pImageManager = pImgManager;
	m_ThreadParam.pImgList = pImgList;

	SetProgress(IDS_TRANSFER_IMAGE, (UINT)pImgList->GetCount());
}

CWaitImportImageDlg::~CWaitImportImageDlg()
{
}

BEGIN_MESSAGE_MAP(CWaitImportImageDlg, CDialog)

	ON_MESSAGE(EM_DESTROY_WAITIMPORTIMAGEDLG, OnDestroyWaitImportImageDlg)
	ON_MESSAGE(EPM_THREAD_IMPORT_IMAGE, OnUpdateProgress)

END_MESSAGE_MAP()

void CWaitImportImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ANIM, m_ctrlAnim);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
}

void CWaitImportImageDlg::OnCancel()
{
}

BOOL CWaitImportImageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CWaitImportImageDlg::IDD, "WaitImportImageDlg");

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

	m_ctrlProgress.SetRange(0, m_iMax);

	return TRUE;
}

void CWaitImportImageDlg::OnOK()
{
}

LRESULT CWaitImportImageDlg::OnDestroyWaitImportImageDlg(WPARAM wParam, LPARAM lParam)
{
	CDialog::OnOK();
	return 0;
}

LRESULT CWaitImportImageDlg::OnUpdateProgress(WPARAM wParam, LPARAM lParam)
{
	m_ctrlProgress.SetPos((int)wParam);

	CString strTmp;
	strTmp.Format(theApp.GetMessageString(m_idString), wParam, m_iMax);
	SetDlgItemText(IDC_PROGRESS_LABEL, strTmp);

	return 0;
}

void CWaitImportImageDlg::SetProgress(UINT idString, UINT iMax)
{
	m_idString = idString;
	m_iMax = iMax;
}

UINT CWaitImportImageDlg::Thread(LPVOID pParam)
{
	m_sbError = FALSE;

	tagTHREAD* param = (tagTHREAD*)pParam;

	if FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED))
		return 0;

	CStringList imageList;
	int iCurrImage = 0;

	for (POSITION pos = param->pImgList->GetHeadPosition(); pos;)
	{
		imageList.RemoveAll();
		imageList.AddTail(param->pImgList->GetNext(pos));
		::SendMessage(param->hWndParent, EPM_THREAD_IMPORT_IMAGE, iCurrImage, 0);

		int nCount = imageList.GetCount();
		
		CString strListPath = "[";
		POSITION p;
		for (p = imageList.GetHeadPosition(); p != NULL;)
		{
			CString strNomeArq(imageList.GetNext(p));
			strListPath += ", " + strNomeArq;

			LPCTSTR pszFile = strNomeArq;
			DWORD dwAttrs = dwAttrs = GetFileAttributes(pszFile);
			if (dwAttrs != INVALID_FILE_ATTRIBUTES)
			{
				SetFileAttributes(pszFile, GetFileAttributes(pszFile) & ~FILE_ATTRIBUTE_READONLY);
			}
		}
		strListPath += "]";

		CImgIDList outputImgIdList;

		DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
		int iQtdImportada = param->pImageManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &imageList, FORM_IMM, FORM_MINI, &outputImgIdList, FALSE, FALSE, FALSE);
		if (iQtdImportada == nCount)
		{
			SYSTEMTIME st; GetLocalTime(&st); TCHAR szDateNow[1024]; sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
			CString strLog = "";
			strLog.Format("[%s] %s >>> IMPORTADO nomearq:[%s]"
				, szDateNow
				, "CWaitImportImageDlg::Thread()"
				, strListPath
				);
			CLogFileWriter::Get()->WriteLogLine0(strLog);
		}
		else
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_ERROR_IMPORT_IMAGE), imageList.GetHead());
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
			m_sbError = TRUE;

			// ERRO NA IMPORTAÇAO
			SYSTEMTIME st; GetLocalTime(&st); TCHAR szDateNow[1024]; sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
			CString strLog = "";
			strLog.Format("[%s] %s ERRO NA IMPORTAÇÃO DO CImgManager.ImportImgList() lista arq:'%s' qtdLista:%d qtdImportada:%d [%s]"
				, szDateNow
				, "CWaitImportImageDlg::Thread()"
				, strListPath
				, iQtdImportada
				, nCount
				, strError
				);
			CLogFileWriter::Get()->WriteLogLine0(strLog);

			// importo anche il file .MIS associato //
			long lLastID = 0;

			/*CImgIDList IdList;
			int nCount = param->pImageManager->GetImgIDList(&IdList);

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
				CString strAddFile = imageList.GetHead();
				CString strLastFile = param->pImageManager->GetFullPath(lLastID);

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

		BOOL bDeleteError = FALSE;
		for (p = imageList.GetHeadPosition(); p != NULL;)
		{
			CString strNomeArq(imageList.GetNext(p));
			if (_access(strNomeArq, 00) == 0)	// _access(file,attr) >> 00=Existência apenas | 02=Somente gravação | 04=Somente leitura | 06=Leitura e gravação
			{
				bDeleteError = TRUE;

				SYSTEMTIME st; GetLocalTime(&st); TCHAR szDateNow[1024]; sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
				CString strLog = "";
				strLog.Format("[%s] %s >>> ERRO NA DELEÇÃO DO arq:'%s'"
					, szDateNow
					, "CWaitImportImageDlg::Thread()"
					, strNomeArq
					);
				CLogFileWriter::Get()->WriteLogLine0(strLog);
			}
		}

		if (bDeleteError)
		{
			for (p = imageList.GetHeadPosition(); p != NULL;)
			{
				CString strFile(imageList.GetNext(p));

				// ARQUIVO JA IMPORTADO - "IGNORA"
				BOOL bFileMoved = FALSE;

				CString strRejectedFilesInImportError = theApp.m_sDirTempAcq + "\\IMPORT_IMG_ERROR";
				CreateLogFolderIfNotExists(strRejectedFilesInImportError);

				SYSTEMTIME st;
				GetLocalTime(&st);
				TCHAR szDateNow1[1024];
				TCHAR szDateNow2[1024];
				sprintf_s(szDateNow1, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
				sprintf_s(szDateNow2, "%04d-%02d-%02d_%02d-%02d-%02d-%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
				CString strOrigFile = strFile;
				CString strDestFile = strRejectedFilesInImportError + "\\" + szDateNow2 + "_" + strFile.Mid(strFile.ReverseFind('\\') + 1);
				CString strLog = "";

				try {
					// MOVE ARQUIVO POR SEGURANCA PARA PASTA .\IMPORT_IMG_ERROR
					if (MoveFile(strOrigFile, strDestFile))
					{
						bFileMoved = TRUE;
						strLog.Format("[%s] %s >>> MOVIDO ARQUIVO DE:'%s' PARA:'%s'"
							, szDateNow1
							, "CWaitImportImageDlg::Thread()"
							, strOrigFile
							, strDestFile
							);
					}
					else
					{
						strLog.Format("[%s] %s >>> ERRO NA TENTATIVA DE MOVER O ARQUIVO DE:'%s' PARA:'%s'"
							, szDateNow1
							, "CWaitImportImageDlg::Thread()"
							, strOrigFile
							, strDestFile
							);
					}
					CLogFileWriter::Get()->WriteLogLine0(strLog);
				}
				catch (CException* e)
				{
					bFileMoved = FALSE;

					TCHAR szError[255];
					e->GetErrorMessage(szError, 255);
					e->Delete();

					SYSTEMTIME st; GetLocalTime(&st); TCHAR szDateNow[1024]; sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
					CString strLog = "";
					strLog.Format("[%s] %s >>> ERRO NA TENTATIVA DE MOVER O ARQUIVO DE:'%s' PARA:'%s' (Exception: %s)"
						, szDateNow
						, "CWaitImportImageDlg::Thread()"
						, strOrigFile
						, strDestFile
						, szError
						);
					CLogFileWriter::Get()->WriteLogLine0(strLog);
				}
			}
		}

		if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
			CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, 0, 0, nCount, "CWaitImportImageDlg::Thread");
		iCurrImage++;

		if (m_sbError)
			break;
	}
	
	::PostMessage(param->hWndParent, EM_DESTROY_WAITIMPORTIMAGEDLG, NULL, NULL);
	// delete param; // Sandro 18/11/2013 //

	::CoUninitialize();

	return 0;
}