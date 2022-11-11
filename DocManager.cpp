#include "stdafx.h"
#include "Endox.h"
#include "DocManager.h"

#include <io.h>

#include "DLL_Imaging\h\ImgArchive.h"

#include "LogFileWriter.h"
#include "MmSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMyDocManager::CMyDocManager() 
{
	// se il percorso degli allegati al paziente è vuoto lo imposto con il percorso delle immagini //
	if (theApp.m_sPercorsoAllegatiPaz.IsEmpty())
	{
		char szPathImm[MAX_PATH];
		char szPathMin[MAX_PATH];
		if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
		{
			theApp.m_sPercorsoAllegatiPaz = szPathImm;
		}
		else
		{
			ASSERT(FALSE);
		}
	}

	// se il percorso degli allegati all'esame è vuoto lo imposto con il percorso delle immagini //
	if (theApp.m_sPercorsoAllegatiEsa.IsEmpty())
	{
		char szPathImm[MAX_PATH];
		char szPathMin[MAX_PATH];
		if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
		{
			theApp.m_sPercorsoAllegatiEsa = szPathImm;
		}
		else
		{
			ASSERT(FALSE);
		}
	}

	//
	if ((_access(theApp.m_sPercorsoAllegatiPaz, 06) != 0) || (_access(theApp.m_sPercorsoAllegatiEsa, 06) != 0))
	{
		// percorso impostato ma non esistente/raggiungibile //
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ATT_PATH_ERROR), MB_ICONSTOP);

		// segno che non siamo inizializzati //
		m_bInit = FALSE;
	}
	else
	{
		// percorso OK //
		m_bInit = AmDocManager_Init(&theApp.m_dbEndox, theApp.m_sPercorsoAllegatiPaz, theApp.m_sPercorsoAllegatiEsa);
	}
}

CMyDocManager::~CMyDocManager()
{
	AmDocManager_Finalize();
}

long CMyDocManager::GetAttachedDocNumberPatient(const long lIDPatient)
{
	if (!m_bInit)
		return 0;

	return AmDocManager_GetDocNumberPatient(lIDPatient);
}

long CMyDocManager::GetAttachedDocNumberExam(const long lIDExam, const long lWhat)
{
	ASSERT((lWhat == DOCUMENTS_NOT_EXPORT) || (lWhat == DOCUMENTS_ONLY_EXPORT) || (lWhat == DOCUMENTS_ALL));

	if (!m_bInit)
		return 0;

	return AmDocManager_GetDocNumberExam(lIDExam, lWhat);
}

BOOL CMyDocManager::GetAttachedDocListPatient(const long lIDPatient, CList<DOC>* pList)
{
	ASSERT(pList && pList->IsEmpty());

	if (!m_bInit)
		return FALSE;

	LONG lDocNumber = AmDocManager_GetDocNumberPatient(lIDPatient);
	if (lDocNumber <= 0)
		return TRUE;

	DOC* pDocBuffer = new DOC[lDocNumber];
	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	if (!AmDocManager_GetDocListPatient(lIDPatient, pDocBuffer))
	{
		delete pDocBuffer;
		return FALSE;
	}
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_DocRetrieve(timeGetTime() - timeForLog, lIDPatient, 0, lDocNumber, "CMyDocManager::GetAttachedDocListPatient");

	for(int i = 0; i < lDocNumber; i++)
		pList->AddTail(pDocBuffer[i]);

	delete pDocBuffer;
	return TRUE;
}

BOOL CMyDocManager::GetAttachedDocListExam(const long lIDExam, const long lWhat, CList<DOC>* pList)
{
	ASSERT((lWhat == DOCUMENTS_NOT_EXPORT) || (lWhat == DOCUMENTS_ONLY_EXPORT) || (lWhat == DOCUMENTS_ALL));
	ASSERT(pList && pList->IsEmpty());

	if (!m_bInit)
		return FALSE;

	LONG lDocNumber = AmDocManager_GetDocNumberExam(lIDExam, lWhat);
	if (lDocNumber <= 0)
		return TRUE;

	DOC* pDocBuffer = new DOC[lDocNumber];
	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	if (!AmDocManager_GetDocListExam(lIDExam, lWhat, pDocBuffer))
	{
		delete pDocBuffer;
		return FALSE;
	}
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_DocRetrieve(timeGetTime() - timeForLog, 0, lIDExam, lDocNumber, "CMyDocManager::GetAttachedDocListExam");

	for(int i = 0; i < lDocNumber; i++)
		pList->AddTail(pDocBuffer[i]);

	delete pDocBuffer;
	return TRUE;
}

BOOL CMyDocManager::ImportDoc(const long lIDPaziente, const long lIDEsame, const CString sDescrizione, const CString sDataPersonalizzabile, const CString sFile, const BOOL bDaEsportare)
{
	if (!m_bInit)
		return FALSE;

	long lDocID = 0;
	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	BOOL bReturn = AmDocManager_AddDoc_File(lIDPaziente, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, sDescrizione, sDataPersonalizzabile, sFile, bDaEsportare, &lDocID);
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_DocStore(timeGetTime() - timeForLog, lIDPaziente, lIDEsame, 1, "CMyDocManager::ImportDoc");

	return bReturn;
}

long CMyDocManager::ImportDocRemoto(const long lIDPaziente, const long lIDEsame, const long lVersione, const CString sData, const long lTipo, const CString sDescrizione, const CString sUtente, const CString sDataPersonalizzazile, const CString sEstensione, const CString sNomeFileOriginale, const BOOL bDaEsportare, const CString sPercorsoFileRemoto)
{
	long lReturn = 0;

	if (m_bInit)
	{
		DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //

		lReturn = AmDocManager_AddDoc_RemoteFile(lIDPaziente, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, lVersione, sData, lTipo, sDescrizione, sUtente, sDataPersonalizzazile, sEstensione, sNomeFileOriginale, bDaEsportare, sPercorsoFileRemoto);

		if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
			CLogFileWriter::Get()->WriteLogLine0_DocStore(timeGetTime() - timeForLog, lIDPaziente, lIDEsame, 1, "CMyDocManager::ImportDocRemoto");
	}

	return lReturn;
}

long CMyDocManager::ImportDocTiffMP(const long lIDPaziente, const long lIDEsame, const CString sDescrizione, const CString sDataPersonalizzabile, const CStringList* pPathList, const BOOL bDaEsportare, long& lTiffID)
{
	if (!m_bInit)
		return 0;

	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	long lReturn = AmDocManager_AddDoc_File_TiffMP(lIDPaziente, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, sDescrizione, sDataPersonalizzabile, pPathList, bDaEsportare, lTiffID);
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_DocStore(timeGetTime() - timeForLog, lIDPaziente, lIDEsame, 1, "CMyDocManager::ImportDocTiffMP");

	return lReturn;
}

BOOL CMyDocManager::DeleteDoc(const long lDocID)
{
	if (!m_bInit)
		return FALSE;

	return AmDocManager_DeleteDoc(theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, lDocID);
}

BOOL CMyDocManager::EditDoc(const long lDocID, const CString sDescrizione, const CString sDataPersonalizzabile)
{
	if (!m_bInit)
		return FALSE;

	return AmDocManager_EditDoc(theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, lDocID, sDescrizione, sDataPersonalizzabile);
}

BOOL CMyDocManager::MoveDocPatient(const long lOldPatientID, const long lNewPatientID)
{
	if (!m_bInit)
		return FALSE;

	return AmDocManager_MoveDocPatient(theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, lOldPatientID, lNewPatientID);
}

BOOL CMyDocManager::MoveDocExam(const long lOldPatientID, const long lNewPatientID, const long lExamID)
{
	if (!m_bInit)
		return FALSE;

	return AmDocManager_MoveDocExam(theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, lOldPatientID, lNewPatientID, lExamID);
}

BOOL CMyDocManager::CopyToLocal(const long lDocID)
{
	if (!m_bInit)
		return FALSE;

	return AmDocManager_CopyToLocal(lDocID);
}