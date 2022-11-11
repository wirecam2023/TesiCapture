#include "stdafx.h"
#include "Endox.h"
#include "PacsArchiver.h"

#include <io.h>

#include "LogFileWriter.h"
#include "MmSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPacsArchiver::CPacsArchiver(void)
{
}

CPacsArchiver::~CPacsArchiver(void)
{
}

void CPacsArchiver::Archive(long lPatientID, long lExamID, long lPdfID)
{
	CImgManager imTemp(theApp.m_sPathImageOD, &theApp.m_dbEndox);
	imTemp.SetCurrentIDs(lPatientID, lExamID);

	if (!theApp.m_sEsportaFilmatiPerVisoreWebSuPath.IsEmpty() && _access(theApp.m_sEsportaFilmatiPerVisoreWebSuPath, 00) == 0)
	{
		CImgList listImg;

		DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
		int nImages = imTemp.GetImgList(&listImg);
		if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
			CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, lPatientID, lExamID, nImages, "CPacsArchiver::Archive");

		for(POSITION pos = listImg.GetHeadPosition(); pos;)
		{
			IMG img = listImg.GetNext(pos);
			if (img.type != _movie_)
				continue;

			CString strPathInput = imTemp.GetFullPath(img.lID);
			CString strPathOutput;
			strPathOutput.Format("%s\\%08d",
				                 theApp.m_sEsportaFilmatiPerVisoreWebSuPath,
								 img.lID);

			TCHAR szProcess[1024];
			sprintf_s(szProcess, 
				      "%s\\ExpressionEncoderWnd\\ExpressionEncoderWnd.exe %s %s", 
				      theApp.m_sDirProg,
					  strPathInput,
					  strPathOutput);

			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));

			theApp.BeginWaitCursor();

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

			theApp.EndWaitCursor();
		}

		listImg.RemoveAll();
	}

	if (theApp.m_bIntegrazionePacsAttiva)
	{
		CImgIDList listImg;
		imTemp.GetImgMovieDicomIDList(&listImg);

		for(POSITION pos = listImg.GetHeadPosition(); pos;)
			CSPInsertImgInDicomTransferQueue(&theApp.m_dbEndox).Exec(listImg.GetNext(pos));

		CSPInsertPdfInDicomTransferQueue(&theApp.m_dbEndox).Exec(lPdfID);
		SendToPacs();
	}
}

void CPacsArchiver::SendToPacs()
{
	if (!theApp.m_bIntegrazionePacsSincrona)
		return;

	TCHAR szProcess[1024];
	sprintf_s(szProcess, "%s\\AmDcmQueueManager\\DcmStoreScu.exe", theApp.m_sDirProg);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	theApp.BeginWaitCursor();

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

	theApp.EndWaitCursor();
}

//
//
//

CPacsArchiver::CSPInsertImgInDicomTransferQueue::CSPInsertImgInDicomTransferQueue(CDatabase* pDatabase) : CRecordset(pDatabase)
{
	m_imageid = 0;
	m_result = 0;
	// 
	m_nFields = 0;
	m_nParams = 2;
}

void CPacsArchiver::CSPInsertImgInDicomTransferQueue::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputParam);
	RFX_Long(pFX, "@RESULT", m_result);
	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Long(pFX, "@IMAGEID", m_imageid);	
}

long CPacsArchiver::CSPInsertImgInDicomTransferQueue::Exec(long lImageID)
{
	m_imageid = lImageID;

	try
	{
		Open(CRecordset::snapshot, NULL, CRecordset::readOnly);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		m_result = -1;
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		m_result = -1;
	}

	if (IsOpen())
		Close();

	return m_result;
}

//
//
//

CPacsArchiver::CSPInsertPdfInDicomTransferQueue::CSPInsertPdfInDicomTransferQueue(CDatabase* pDatabase) : CRecordset(pDatabase)
{
	m_pdfid = 0;
	m_result = 0;
	// 
	m_nFields = 0;
	m_nParams = 2;
}

void CPacsArchiver::CSPInsertPdfInDicomTransferQueue::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputParam);
	RFX_Long(pFX, "@RESULT", m_result);
	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Long(pFX, "@PDFID", m_pdfid);	
}

long CPacsArchiver::CSPInsertPdfInDicomTransferQueue::Exec(long lPdfID)
{
	m_pdfid = lPdfID;

	try
	{
		Open(CRecordset::snapshot, NULL, CRecordset::readOnly);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		m_result = -1;
	}
	catch (CMemoryException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		m_result = -1;
	}

	if (IsOpen())
		Close();

	return m_result;
}