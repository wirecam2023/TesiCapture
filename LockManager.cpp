#include "stdafx.h"
#include "Endox.h"
#include "LockManager.h"

#include "AccessDlg.h"
#include "EsamiSet.h"
#include "VistaAttivazioneSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLockManager CLockManager::m_LockManager;

CLockManager::CLockManager(void)
{
}

CLockManager::~CLockManager(void)
{
}

CLockManager* CLockManager::Get()
{
	return &CLockManager::m_LockManager;
}

BOOL CLockManager::Initialize()
{
	if (!theApp.m_bLockServerAttivo)
		return TRUE;

	if (theApp.m_sLockServerIndirizzo != "" && theApp.m_lLockServerPorta > 0)
	{
		CString sServerAddress = theApp.m_sLockServerIndirizzo;
		int iServerPort = theApp.m_lLockServerPorta;

		if (!AmLockEx_Initialize(AmLockEx_ServerType::ServerHttp, sServerAddress.GetBuffer(), iServerPort, SEND_ALIVE_MESSAGE_INTERVAL_SEC))
		{
			delete theApp.m_pAccessWnd;
			theApp.m_pAccessWnd = NULL;

			// theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_LOCK_INIT), MB_ICONSTOP); // Sandro 30/04/2014 // tanto subito dopo mi esce l'altro errore che mi chiede se continuare o meno //
			return FALSE;
		}
		else
		{
			AmLockEx_UnlockAll(theApp.m_sUtenteLoggato);
		}

		sServerAddress.ReleaseBuffer();
	}
	else
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CLockManager::Finalize()
{
	if (theApp.m_bLockServerAttivo)
		AmLockEx_Finalize();

	return TRUE;
}

BOOL CLockManager::LockExam(long lExamID)
{

#ifdef _DEBUG
	return TRUE;
#endif

	if (!theApp.m_bLockServerAttivo)
		return TRUE;

	BOOL bReturn = FALSE;
	BOOL bExitWhile = FALSE;

	// Provo a bloccare il paziente...
	while(!bExitWhile)
	{
		AfxGetApp()->DoWaitCursor(1);
		CString sReturnedMessage;
		INT iResult = AmLockEx_LockExam(theApp.m_sUtenteLoggato, lExamID, &sReturnedMessage);
		AfxGetApp()->DoWaitCursor(-1);
		
		if (iResult < 0)
		{
			switch(theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_LOCK_SERVICE_DOWN), MB_ICONSTOP | MB_ABORTRETRYIGNORE))
			{
				case IDABORT:
				{
					bReturn = FALSE;
					bExitWhile = TRUE;

					break;
				}
				case IDRETRY:
				{
					break;
				}
				case IDIGNORE:
				{
					// Sandro 27/08/2012 //
					// theApp.m_bLockServerAttivo = FALSE;
					// AmLockEx_Finalize();

					bReturn = TRUE;
					bExitWhile = TRUE;

					break;
				}
			}
		}
		else if (iResult == 0)
		{
			AfxGetApp()->DoWaitCursor(1);
			CString sUserLockOut;
			CString sComputerLockOut;
			AmLockEx_QueryLock(sReturnedMessage, &sUserLockOut, &sComputerLockOut);
			AfxGetApp()->DoWaitCursor(-1);

			CString sDescrizioneComputer = CVistaAttivazioneSet().GetDescrizione(sComputerLockOut);
			sDescrizioneComputer.Trim();
			
			CString strError;

			if (sDescrizioneComputer.IsEmpty())
				strError.Format(theApp.GetMessageString(IDS_ERROR_LOCK_EXAM_LOCKED), sUserLockOut, sComputerLockOut);
			else
				strError.Format(theApp.GetMessageString(IDS_ERROR_LOCK_EXAM_LOCKED2), sUserLockOut, sDescrizioneComputer, sComputerLockOut);

			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP); // "Impossibile eseguire l'operazione richiesta. Paziente/esame già in lavorazione dall'utente %s (PC %s)\n\nRiprovare più tardi." //

			bReturn = FALSE;
			bExitWhile = TRUE;
		}
		else
		{
			bReturn = TRUE;
			bExitWhile = TRUE;
		}
	}

	return bReturn;
}


BOOL CLockManager::LockPatient(long lPatientID)
{

#ifdef _DEBUG
	return TRUE;
#endif

	if (!theApp.m_bLockServerAttivo)
		return TRUE;

	BOOL bReturn = FALSE;
	BOOL bExitWhile = FALSE;

	// Provo a bloccare il paziente...
	while(!bExitWhile)
	{
		AfxGetApp()->DoWaitCursor(1);
		CString sReturnedMessage;
		INT iResult = AmLockEx_LockPatient(theApp.m_sUtenteLoggato, lPatientID, &sReturnedMessage);
		AfxGetApp()->DoWaitCursor(-1);
		
		if (iResult < 0)
		{
			switch(theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_LOCK_SERVICE_DOWN), MB_ICONSTOP | MB_ABORTRETRYIGNORE))
			{
				case IDABORT:
				{
					bReturn = FALSE;
					bExitWhile = TRUE;

					break;
				}
				case IDRETRY:
				{
					break;
				}
				case IDIGNORE:
				{
					// Sandro 27/08/2012 //
					// theApp.m_bLockServerAttivo = FALSE;
					// AmLockEx_Finalize();

					bReturn = TRUE;
					bExitWhile = TRUE;

					break;
				}
			}
		}
		else if (iResult == 0)
		{
			AfxGetApp()->DoWaitCursor(1);
			CString sUserLockOut;
			CString sComputerLockOut;
			AmLockEx_QueryLock(sReturnedMessage, &sUserLockOut, &sComputerLockOut);
			AfxGetApp()->DoWaitCursor(-1);
			
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_ERROR_LOCK_EXAM_LOCKED), sUserLockOut, sComputerLockOut);
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP); // "Impossibile eseguire l'operazione richiesta. Paziente/esame già in lavorazione dall'utente %s (PC %s)\n\nRiprovare più tardi." //

			bReturn = FALSE;
			bExitWhile = TRUE;
		}
		else
		{
			bReturn = TRUE;
			bExitWhile = TRUE;
		}
	}

	return bReturn;
}

BOOL CLockManager::LockPatientAndAllExams(long lPatientID)
{

#ifdef _DEBUG
	return TRUE;
#endif

	if (!theApp.m_bLockServerAttivo)
		return TRUE;

	ASSERT(m_listPatientExamLocked.GetCount() == 0);

	if (!LockPatient(lPatientID))
		return FALSE;

	// Provo a bloccare tutti gli esami del paziente...
	BuildExamList(lPatientID);
	BOOL bReturn = TRUE;

	CList<long> listExamsAlreadyLock;
	for(POSITION pos = m_listPatientExamLocked.GetHeadPosition(); pos;)
	{
		long lExamID = m_listPatientExamLocked.GetNext(pos);
		if (!LockExam(lExamID))
		{
			m_listPatientExamLocked.RemoveAll();

			// Sblocco le risorse eventualmente già bloccate...
			for (POSITION pos = listExamsAlreadyLock.GetHeadPosition(); pos;)
			{
				UnlockExam(listExamsAlreadyLock.GetNext(pos));
			}
			UnlockPatient(lPatientID);

			bReturn = FALSE;
			break;
		}
		else
		{
			listExamsAlreadyLock.AddTail(lExamID);
		}
	}
	
	return bReturn;
}

BOOL CLockManager::LockUser(CString sUserToLock)
{

#ifdef _DEBUG
	return TRUE;
#endif

	BOOL bReturn = FALSE;
	BOOL bExitWhile = FALSE;

	if (!theApp.m_bLockServerAttivo || theApp.m_bLoginMultiploUtente)
		return TRUE;
	
	while(!bExitWhile)
	{
		AfxGetApp()->DoWaitCursor(1);
		CString sReturnedMessage;
		int iResult = AmLockEx_LockUser(theApp.m_sUtenteLoggato, sUserToLock, &sReturnedMessage);
		AfxGetApp()->DoWaitCursor(-1);
		
		if (iResult < 0)
		{
			switch(theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_LOCK_SERVICE_DOWN), MB_ICONSTOP | MB_ABORTRETRYIGNORE))
			{
				case IDABORT:
				{
					bReturn = FALSE;
					bExitWhile = TRUE;

					break;
				}
				case IDRETRY:
				{
					break;
				}
				case IDIGNORE:
				{
					// Sandro 27/08/2012 //
					// theApp.m_bLockServerAttivo = FALSE;
					// AmLockEx_Finalize();

					bReturn = TRUE;
					bExitWhile = TRUE;

					break;
				}
			}
		}
		else if (iResult == 0)
		{
			AfxGetApp()->DoWaitCursor(1);
			CString sUserLockOut;
			CString sComputerLockOut;
			AmLockEx_QueryLock(sReturnedMessage, &sUserLockOut, &sComputerLockOut);
			AfxGetApp()->DoWaitCursor(-1);
					
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_ERROR_LOCK_USER_LOGGED), sUserToLock, sComputerLockOut);
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP); // "L'utente %s è già autenticato nella stazione %s!" //

			bReturn = FALSE;
			bExitWhile = TRUE;
		}
		else
		{
			bReturn = TRUE;
			bExitWhile = TRUE;
		}
	}	

	return bReturn;
}

BOOL CLockManager::UnlockExam(long lExamID)
{

#ifdef _DEBUG
	return TRUE;
#endif

	BOOL bReturn = TRUE;

	if (theApp.m_bLockServerAttivo)
	{
		AfxGetApp()->DoWaitCursor(1);
		bReturn = AmLockEx_UnlockExam(theApp.m_sUtenteLoggato, lExamID);
		AfxGetApp()->DoWaitCursor(-1);
	}

	return bReturn;
}

BOOL CLockManager::UnlockPatient(long lPatientID)
{

#ifdef _DEBUG
	return TRUE;
#endif

	BOOL bReturn = TRUE;

	if (theApp.m_bLockServerAttivo)
	{
		AfxGetApp()->DoWaitCursor(1);
		bReturn = AmLockEx_UnlockPatient(theApp.m_sUtenteLoggato, lPatientID);
		AfxGetApp()->DoWaitCursor(-1);
	}

	return bReturn;
}

BOOL CLockManager::UnlockPatientAndAllExams(long lPatientID)
{

#ifdef _DEBUG
	return TRUE;
#endif

	if (theApp.m_bLockServerAttivo)
	{
		UnlockPatient(lPatientID);
		for (POSITION pos = m_listPatientExamLocked.GetHeadPosition(); pos;)
		{
			UnlockExam(m_listPatientExamLocked.GetNext(pos));
		}
	}

	m_listPatientExamLocked.RemoveAll();
	return TRUE;
}

BOOL CLockManager::UnlockUser(CString sUserToUnlock)
{

#ifdef _DEBUG
	return TRUE;
#endif

	BOOL bReturn = TRUE;

	if (!theApp.m_bLockServerAttivo || theApp.m_bLoginMultiploUtente)
		return TRUE;

	AfxGetApp()->DoWaitCursor(1);
	bReturn = AmLockEx_UnlockUser(theApp.m_sUtenteLoggato, sUserToUnlock);
	AfxGetApp()->DoWaitCursor(-1);

	return bReturn;
}

void CLockManager::BuildExamList(long lPatientID)
{
	CEsamiSet setEsami;
	CString strFilter;

	m_listPatientExamLocked.RemoveAll();
	strFilter.Format("Paziente=%li", lPatientID);

	setEsami.SetOpenFilter(strFilter);

	if (setEsami.OpenRecordset("CLockManager::BuildExamList"))
	{
		while(!setEsami.IsEOF())
		{
			m_listPatientExamLocked.AddTail(setEsami.m_lContatore);
			setEsami.MoveNext();
		}

		setEsami.CloseRecordset("CLockManager::BuildExamList");
	}
}
