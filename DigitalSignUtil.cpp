#include "stdafx.h"
#include "Endox.h"
#include "DigitalSignUtil.h"

#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\AMTesiSign.h"

#include <io.h>
#include <psapi.h>

#include "CodificaRegionaleExSet.h"
#include "CustomDate.h"
#include "ExtPrestazioniSet.h"
#include "MediciSet.h"
#include "PazientiSet.h"
#include "PdfSissSet.h"
#include "RegioneSet.h"
#include "SediEsameSet.h"
#include "SmartCardPinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct Siss_Prestazione
{
	Siss_Prestazione()
	{
		ZeroMemory(this, sizeof(Siss_Prestazione));
	}

	TCHAR szIDPrescrizione[51];
	TCHAR szCodicePrestazione[51];
	TCHAR szCodicePrestazioneSiss[51];
	TCHAR szCodiceBrancaSpecialistica[51];
	TCHAR szDescPrestazione[256];
	UINT iQuantitaErogata;
	BOOL  bFlagAggiuntiva;
};

BOOL CDigitalSignUtil::Initialize()
{
	BOOL bReturn = FALSE;
	switch(theApp.m_enumFirmaDigitale)
	{
		case CEndoxApp::sign_comped:
		{
			if (theApp.m_bFirmaDigitaleChiudiComped)
				KillProcess("Digita~1.exe");

			theApp.m_sSmartCardPin = "";

			if (AmTesiSign_Initialize(theApp.m_bFirmaDigitaleDebug) != NoError)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_1), MB_ICONSTOP);

				if (theApp.m_bFirmaDigitaleChiudiComped)
					KillProcess("Digita~1.exe");
			}
			else if (AmTesiSign_ReadSmartCard() != NoError)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_2), MB_ICONSTOP);
				AmTesiSign_Finalize();

				if (theApp.m_bFirmaDigitaleChiudiComped)
					KillProcess("Digita~1.exe");
			}
			else
			{
				AmTesiSign_SMARTCARDDATA data;
				AmTesiSign_GetSmartCardData(&data);
				if (strlen(data.szUserFirstLastName) == 0)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_5), MB_ICONSTOP);
					AmTesiSign_Finalize();
				}
				else
				{
					// Sandro 01/03/2013 //
					INT_PTR iReturn = IDCANCEL;
					CSmartCardPinDlg dlg;
					do
					{
						iReturn = dlg.DoModal();
						if (iReturn == IDCANCEL)
							break;
					}
					while(AmTesiSign_ReadCertificate(dlg.m_strPin) != NoError);

					if (iReturn == IDCANCEL)
					{
						AmTesiSign_Finalize();
					}
					else
					{
						theApp.m_sSmartCardPin = dlg.m_strPin;
						bReturn = TRUE;
					}
				}
			}

			break;
		}
		default:
		{
			bReturn = TRUE;
			break;
		}
	}

	return bReturn;
}

BOOL CDigitalSignUtil::Finalize()
{
	BOOL bReturn = FALSE;

	switch(theApp.m_enumFirmaDigitale)
	{
		case CEndoxApp::sign_comped:
		{
			bReturn = AmTesiSign_Finalize();

			if (theApp.m_bFirmaDigitaleChiudiComped)
				KillProcess("Digita~1.exe");

			break;
		}
		default:
		{
			bReturn = TRUE;
			break;
		}
	}

	return bReturn;
}

BOOL CDigitalSignUtil::SignPdf(CWnd* pParentWnd, long lPatientID, long lExamID, LPCTSTR szPdfPath, tagSissInfo* pSissInfo, BOOL bRefertoAnnullativo)
{
	BOOL bReturn = FALSE;

	switch(theApp.m_enumFirmaDigitale)
	{
		case CEndoxApp::sign_comped:
		{
			bReturn = SignPdfWithComped(pParentWnd, lPatientID, lExamID, szPdfPath, pSissInfo);
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}

	return bReturn;
}

BOOL CDigitalSignUtil::SignPdfWithComped(CWnd* pParentWnd, long lPatientID, long lExamID, LPCTSTR szPdfPath, tagSissInfo* pSissInfo)
{
	tagPdfInfo pdf;
	pdf.lPatientID = lPatientID;
	pdf.lExamID = lExamID;
	strcpy_s(pdf.szPdfPath, szPdfPath);

	CList<tagPdfInfo> listIn, listOut;
	listIn.AddTail(pdf);

	if (!SignPdfWithComped(pParentWnd, &listIn, &listOut))
		return FALSE;
	
	if (listOut.GetCount() != 1)
		return FALSE;
	
	if (_access(listOut.GetHead().szPdfPath, 00) != 0)
		return FALSE;

	memcpy(pSissInfo, &listOut.GetHead().sissInfo, sizeof(tagSissInfo));
	return TRUE;
}

BOOL CDigitalSignUtil::SignPdfWithComped(CWnd* pParentWnd, CList<tagPdfInfo>* pPdfToSign, CList<tagPdfInfo>* pPdfSigned)
{
	UINT iCounter = 1;

	for(POSITION pos = pPdfToSign->GetHeadPosition(); pos;)
	{
		CDigitalSignUtil::tagPdfInfo pdf = pPdfToSign->GetNext(pos);

		pParentWnd->BeginWaitCursor();
		if (AmTesiSign_SignFile(pdf.szPdfPath, theApp.m_sSmartCardPin) != NoError)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_3), MB_ICONSTOP);
			break;
		}
		else
		{
			strcat_s(pdf.szPdfPath, ".p7m");
			pPdfSigned->AddTail(pdf);
		}
	}

	pParentWnd->EndWaitCursor();
	return TRUE;
}

BOOL CDigitalSignUtil::GetSmartCardUtente(CString* pUtente)
{
	BOOL bReturn = FALSE;

	switch(theApp.m_enumFirmaDigitale)
	{
		case CEndoxApp::sign_comped:
		{
			AmTesiSign_SMARTCARDDATA scData;
			AmTesiSign_GetSmartCardData(&scData);
			*pUtente = scData.szUserFirstLastName;

			bReturn = TRUE;
			break;
		}
		default:
		{
			break;
		}
	}

	return bReturn;
}

BOOL CDigitalSignUtil::GetSmartCardNumero(CString* pNumero)
{
	BOOL bReturn = FALSE;

	switch(theApp.m_enumFirmaDigitale)
	{
		case CEndoxApp::sign_comped:
		{
			AmTesiSign_CERTIFICATEDATA certData;
			AmTesiSign_GetCertificateData(&certData);
			*pNumero = certData.szSerialNumber;

			bReturn = TRUE;
			break;
		}
		default:
		{
			break;
		}
	}

	return bReturn;
}

BOOL CDigitalSignUtil::GetSmartCardEnteCertificato(CString* pEnteCertificato)
{
	BOOL bReturn = FALSE;

	switch(theApp.m_enumFirmaDigitale)
	{
		case CEndoxApp::sign_comped:
		{
			AmTesiSign_CERTIFICATEDATA certData;
			AmTesiSign_GetCertificateData(&certData);
			*pEnteCertificato = certData.szIssuer;

			bReturn = TRUE;
			break;
		}
		default:
		{
			break;
		}
	}

	return bReturn;
}

BOOL CDigitalSignUtil::DecryptPdf(LPCTSTR szFilePdf, LPBYTE* pBufferDecryptedPDF, DWORD* pBufferDecryptedPDFSize)
{
	(*pBufferDecryptedPDF) = NULL;
	*pBufferDecryptedPDFSize = 0;

	HANDLE hFilePdf = ::CreateFile(szFilePdf,
		                           FILE_READ_DATA,
								   FILE_SHARE_READ,
								   NULL,
								   OPEN_EXISTING,
								   FILE_ATTRIBUTE_NORMAL,
								   NULL);
	
	if (hFilePdf == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD dwFileSize = GetFileSize(hFilePdf, NULL);

	DWORD dwReaded;
	BYTE* pBufferPS = new BYTE[dwFileSize];
	if (!ReadFile(hFilePdf, pBufferPS, dwFileSize, &dwReaded, NULL))
	{
		delete pBufferPS;
		return FALSE;
	}

	DWORD dwError = 0, dwExitCode = 0;
	BOOL bResult = FALSE;

	TCHAR szProcess[1024];
	sprintf_s(szProcess,
		     "%s\\OpenSSL\\openssl.exe smime -decrypt -verify -inform DER -noverify",
			 theApp.m_sDirProg);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

	HANDLE hChildStdinRd, hChildStdinWr;
	if (!CreatePipe(&hChildStdinRd, &hChildStdinWr, &sa, dwFileSize + 1))
	{
		delete pBufferPS;
		theApp.AfxMessageBoxEndo("CreatePipe 1 error");
		return FALSE;
	}

	HANDLE hChildStdoutRd, hChildStdoutWr;
	if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &sa, 10000000))
	{
		delete pBufferPS;
		theApp.AfxMessageBoxEndo("CreatePipe 2 error");
		return FALSE;
	}

	int iSteps = (dwFileSize / 1000000);
	if (dwFileSize % 1000000)
		iSteps++;

	for(int i = 0; i < iSteps; i++)
	{
		DWORD dwWritten;
		if (!::WriteFile(hChildStdinWr, 
			             pBufferPS + (i * 1000000), 
						 (i == iSteps - 1) ? dwFileSize - (i * 1000000) : 1000000, 
						 &dwWritten, 
						 NULL))
		{
			TCHAR szBuffer[MAX_PATH];
			sprintf_s(szBuffer, "WriteFile 1 error %li", GetLastError());
			theApp.AfxMessageBoxEndo(szBuffer);
			delete pBufferPS;
			return FALSE;
		}
	}

	CloseHandle(hChildStdinWr);
	
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
    si.dwFlags    = STARTF_USESTDHANDLES;
    si.hStdInput  = hChildStdinRd;
    si.hStdOutput = hChildStdoutWr;
    si.hStdError  = NULL;

	// Start the child process. 
	if (CreateProcess(NULL,
					  szProcess,
					  NULL,
					  NULL,
					  TRUE,
					  CREATE_NO_WINDOW,
					  NULL,
					  NULL,
					  &si,
					  &pi))
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		
		if (GetExitCodeProcess(pi.hProcess, &dwExitCode) && dwExitCode == 0)
		{
			DWORD dwTotalBytes = 0, dwReaded;
			if (PeekNamedPipe(hChildStdoutRd, NULL, 0, NULL, &dwTotalBytes, NULL) && dwTotalBytes > 0)
			{
				*pBufferDecryptedPDFSize = dwTotalBytes;
				(*pBufferDecryptedPDF) = new BYTE[dwTotalBytes];

				if (!::ReadFile(hChildStdoutRd, (*pBufferDecryptedPDF), dwTotalBytes, &dwReaded, NULL))
				{
					theApp.AfxMessageBoxEndo("ReadFile error");
					delete (*pBufferDecryptedPDF);
					(*pBufferDecryptedPDF) = NULL;
					*pBufferDecryptedPDFSize = 0;
				}
				else
					bResult = TRUE;
			}
			else
				theApp.AfxMessageBoxEndo("PeekNamedPipe error");
		}
		else
		{
			TCHAR szError[255];
			sprintf_s(szError, "ExitCodeProcess %li", dwExitCode);
			theApp.AfxMessageBoxEndo(szError);
		}

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	else
	{
		theApp.AfxMessageBoxEndo("CreateProcess error");
	}

	delete pBufferPS;
	CloseHandle(hChildStdinRd);
	CloseHandle(hChildStdoutRd);
	CloseHandle(hChildStdoutWr);

	return bResult;
}

BOOL CDigitalSignUtil::KillProcess(LPCTSTR szProcess)
{
    DWORD dwProcesses[1024], dwNeededProcesses;
    if (!EnumProcesses(dwProcesses, sizeof(dwProcesses), &dwNeededProcesses))
        return FALSE;

	BOOL bReturn = FALSE;
	for(UINT i = 0; i < dwNeededProcesses / sizeof(DWORD); i++)
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE,
									  FALSE,
									  dwProcesses[i]);
		if (hProcess != NULL)
		{
			DWORD dwNeededModule;
			HMODULE hModule;
			if (EnumProcessModules(hProcess, 
				                   &hModule, 
								   sizeof(hModule), 
				                   &dwNeededModule))
			{
				TCHAR szProcessName[MAX_PATH];
				ZeroMemory(szProcessName, sizeof(TCHAR) * MAX_PATH);
				if (GetModuleFileNameEx(hProcess, hModule, szProcessName, MAX_PATH) > 0)
				{
					CString strProcessName(szProcessName);
					strProcessName.MakeUpper();
					
					CString strProcessToKill(szProcess);
					strProcessToKill.MakeUpper();

					if (strProcessName.Right(strProcessToKill.GetLength()) == strProcessToKill)
						bReturn = TerminateProcess(hProcess, 0);
				}
			}
	
			CloseHandle(hProcess);
		}
	}

	return bReturn;
}

/*BOOL CDigitalSignUtil::SignPdfWithSiss(CWnd* pParentWnd, long lPatientID, long lExamID, LPCTSTR szPdfPath, tagSissInfo* pSissInfo, BOOL bRefertoAnnullativo)
{
	tagPdfInfo pdf;
	pdf.lPatientID = lPatientID;
	pdf.lExamID = lExamID;
	pdf.bRefertoAnnullativo = bRefertoAnnullativo;
	strcpy_s(pdf.szPdfPath, szPdfPath);

	CList<tagPdfInfo> listIn, listOut;
	listIn.AddTail(pdf);

	if (!SignPdfWithSiss(pParentWnd, &listIn, &listOut))
		return FALSE;
	
	if (listOut.GetCount() != 1)
		return FALSE;
	
	if (_access(listOut.GetHead().szPdfPath, 00) != 0)
		return FALSE;

	memcpy(pSissInfo, &listOut.GetHead().sissInfo, sizeof(tagSissInfo));
	return TRUE;
}

BOOL CDigitalSignUtil::SignPdfWithSiss(CWnd* pParentWnd, CList<tagPdfInfo>* pPdfToSign, CList<tagPdfInfo>* pPdfSigned)
{
	long lUserID;
	AMLogin_GetUserID(&lUserID);

	CString strMedicoCognome, strMedicoNome, strMedicoCodFisc;
	CMediciSet().GetUserData(lUserID, &strMedicoCognome, &strMedicoNome, &strMedicoCodFisc);

	if (strMedicoCognome.IsEmpty() || strMedicoNome.IsEmpty() || strMedicoCodFisc.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITALSIGN_ERROR_USER_DATA1), MB_ICONSTOP);
		return FALSE;
	}

	Siss_Operatore op;
	/*if (!TiSiss_GetUserInfo(siss_2007, &op)) // TiSiss_GetUserInfo è una chiamata del 2007 //
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITALSIGN_ERROR_USER_DATA2), MB_ICONSTOP);
		return FALSE;
	}*/
/*
#ifndef _DEBUG
	if (strcmp(op.szCodiceFiscale, strMedicoCodFisc) != 0)
	{
		CString strError;
		strError.Format(theApp.GetMessageString(IDS_DIGITALSIGN_ERROR_USER_DATA3),
			            strMedicoCodFisc,
						op.szCodiceFiscale);
		theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
		return FALSE;
	}
#endif

	CList<tagPdfInfo> listPdfToSign;
	for(POSITION pos = pPdfToSign->GetHeadPosition(); pos;)
	{
		tagPdfInfo pdf = pPdfToSign->GetNext(pos);
		if (_access(pdf.szPdfPath, 00) == 0)
			listPdfToSign.AddTail(pdf);
	}

	if (listPdfToSign.GetCount() == 0)
		return FALSE;

	// Preparo documenti...
	CList<Siss_Documento> listDoc;
	for(int i = 0; i < listPdfToSign.GetCount(); i++)
	{
		tagPdfInfo pdf = listPdfToSign.GetAt(listPdfToSign.FindIndex(i));

		CString strFilter;
		strFilter.Format("Contatore=%li", pdf.lPatientID);

		CPazientiSet PatientSet;
		PatientSet.SetOpenFilter(strFilter);

		if (PatientSet.OpenRecordset("CDigitalSignUtil::SignPdfWithSiss"))
		{
			if (!PatientSet.IsEOF())
			{
				Siss_Documento doc;

				BYTE* pBufferPdf = NULL;
				UINT iBufferPdfLength = 0;

				HANDLE hFile = ::CreateFile(pdf.szPdfPath,
											FILE_READ_DATA,
											FILE_SHARE_READ,
											NULL,
											OPEN_EXISTING,
											FILE_ATTRIBUTE_NORMAL,
											NULL);
				if (hFile != INVALID_HANDLE_VALUE)
				{
					DWORD dwReaded;
					iBufferPdfLength = GetFileSize(hFile, NULL);
					pBufferPdf = new BYTE[iBufferPdfLength];
					if (!ReadFile(hFile, pBufferPdf, iBufferPdfLength, &dwReaded, NULL))
					{
						iBufferPdfLength = 0;
						delete pBufferPdf;
						pBufferPdf = NULL;
					}
					CloseHandle(hFile);
				}

				if (pBufferPdf && iBufferPdfLength > 0)
				{
					sprintf_s(doc.szIdentificativoDocumento, "%08d", pdf.lExamID);
					strcpy_s(doc.szPazienteID, PatientSet.m_sAssIden);
					strcpy_s(doc.szPazienteCodiceFiscale, PatientSet.m_sCodFisc);
					strcpy_s(doc.szPazienteCognome, PatientSet.m_sCognome);
					strcpy_s(doc.szPazienteNome,PatientSet.m_sNome);
					doc.szPazienteSesso = GetPatientSex(PatientSet.m_lSessoPaz);
					strcpy_s(doc.szPazienteDataNascita, CCustomDate(PatientSet.m_lNatoIlCustom).GetDate("%Y%m%d"));
					strcpy_s(doc.szMedicoCodiceFiscale, strMedicoCodFisc);
					strcpy_s(doc.szMedicoCognome, strMedicoCognome);
					strcpy_s(doc.szMedicoNome, strMedicoNome);

					strcpy_s(doc.szIdentificativoDocumentoPrec, GetDocumentPrecLink(pdf.lExamID));
					doc.bRefertoAnnullativo = pdf.bRefertoAnnullativo;
					//

					strcpy_s(doc.szDataOraCompilazione, CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00"));

					doc.pRefertoPdf = pBufferPdf;
					doc.iSizeRefertoPdf = iBufferPdfLength;

					strFilter.Format("Esame=%li", pdf.lExamID);

					// prestazioni //
					CList<Siss_Prestazione> listPrestazione;
					CRegioneSet setPrest;
					setPrest.SetOpenFilter(strFilter);
					setPrest.SetSortRecord("Contatore");
					if (setPrest.OpenRecordset("CDigitalSignUtil::SignPdfWithSiss"))
					{
						while(!setPrest.IsEOF())
						{
							Siss_Prestazione prestazione;
							ZeroMemory(&prestazione, sizeof(Siss_Prestazione));
							strcpy_s(prestazione.szIDPrescrizione, "");
							strcpy_s(prestazione.szCodicePrestazione, CCodificaRegionaleExSet().GetStringCodiceRegionale(setPrest.m_Codice));
							strcpy_s(prestazione.szCodiceBrancaSpecialistica, "");
							listPrestazione.AddTail(prestazione);
							setPrest.MoveNext();
						}

						setPrest.CloseRecordset("CDigitalSignUtil::SignPdfWithSiss");
					}

					doc.iNumPrestazioni = listPrestazione.GetCount();
					if (listPrestazione.GetCount() > 0)
					{
						doc.pElencoPrestazioni = new Siss_Prestazione_Firma[listPrestazione.GetCount()];
						for(int i = 0; i < listPrestazione.GetCount(); i++)
							memcpy(&doc.pElencoPrestazioni[i], &listPrestazione.GetAt(listPrestazione.FindIndex(i)), sizeof(Siss_Prestazione));
					}
					else
					{
						doc.pElencoPrestazioni = NULL;
					}

					doc.bInviareAlSiss = GetSendToSiss(pdf.lExamID);

					strFilter.Format("Contatore=%li", pdf.lExamID);

					CEsamiSet ExamSet;
					ExamSet.SetOpenFilter(strFilter);
					if (ExamSet.OpenRecordset("CDigitalSignUtil::SignPdfWithSiss"))
					{
						if (!ExamSet.IsEOF())
						{
							doc.bGeneraDao = ExamSet.m_bSissOscuramento10 ||
											 ExamSet.m_bSissOscuramento20 ||
											 ExamSet.m_bSissOscuramento30 ||
											 ExamSet.m_bSissOscuramento40 ||
											 ExamSet.m_bSissOscuramento50 ||
											 !ExamSet.m_bSissAutorizzazioneConsultaz;

							doc.bOscuramento10 = ExamSet.m_bSissOscuramento10; // Tossicodipendenza
							doc.bOscuramento20 = ExamSet.m_bSissOscuramento20; // HIV
							doc.bOscuramento30 = ExamSet.m_bSissOscuramento30; // Violenze subite
							doc.bOscuramento40 = ExamSet.m_bSissOscuramento40; // Interruzione volontaria di gravidanza
							doc.bOscuramento50 = ExamSet.m_bSissOscuramento50; // Oscuramento volontario del cittadino
							doc.bAutorizzazioneConsultazione = ExamSet.m_bSissAutorizzazioneConsultaz;
							strcpy_s(doc.szNoteReperibilita, ExamSet.m_sSissNoteReperibilita);
						}

						ExamSet.CloseRecordset("CDigitalSignUtil::SignPdfWithSiss");
					}
					
					listDoc.AddTail(doc);
				}
			}

			PatientSet.CloseRecordset("CDigitalSignUtil::SignPdfWithSiss");
		}
	}

	if (listDoc.GetCount() == 0)
		return FALSE;

	// Mando richieste al SISS...
	Siss_Documento* pDocuments = new Siss_Documento[listDoc.GetCount()];
	for(int i = 0; i < listDoc.GetCount(); i++)
		memcpy(&pDocuments[i], &listDoc.GetAt(listDoc.FindIndex(i)), sizeof(Siss_Documento));

	UINT iSize;
	Siss_DocumentoFirmato* pDocumentoFirmato;
	if (TiSiss_Sign(siss_2009_direct, pDocuments, listDoc.GetCount(), &pDocumentoFirmato, &iSize, theApp.m_bGeneraSempreDAO, theApp.m_bGeneraMarcaTemporale))
	{
		if (pDocumentoFirmato && iSize > 0) 
		{
			for(UINT i = 0; i < iSize; i++)
			{
				if (!pDocumentoFirmato[i].pReferto)
					continue;
				
				// Cerco l'esame nella lista...
				BOOL bFound = FALSE;
				for(POSITION pos = listPdfToSign.GetHeadPosition(); pos;)
				{
					tagPdfInfo pdf = listPdfToSign.GetNext(pos);

					if (pdf.lExamID != atol(pDocumentoFirmato[i].szIdentificativoDocumento))
						continue;
					
					HANDLE hFile = ::CreateFile(CString(pdf.szPdfPath) + ".p7m",
												FILE_WRITE_DATA,
												FILE_SHARE_WRITE,
												NULL,
												CREATE_ALWAYS,
												FILE_ATTRIBUTE_NORMAL,
												NULL);
					if (hFile == INVALID_HANDLE_VALUE)
					{
						theApp.AfxMessageBoxEndo(CString(pdf.szPdfPath) + ".p7m", MB_ICONSTOP);
						break;
					}

					DWORD dwWritten;
					WriteFile(hFile, pDocumentoFirmato[i].pReferto, pDocumentoFirmato[i].iSizeReferto, &dwWritten, NULL);
					CloseHandle(hFile);

					if (pDocumentoFirmato[i].pAutorizzazione)
					{
						pdf.sissInfo.pAutorizzazione = new TCHAR[pDocumentoFirmato[i].iSizeAutorizzazione + 1];
						strcpy_s(pdf.sissInfo.pAutorizzazione, pDocumentoFirmato[i].iSizeAutorizzazione + 1, pDocumentoFirmato[i].pAutorizzazione);
					}
					if (pDocumentoFirmato[i].pDocumento)
					{
						pdf.sissInfo.pDocumento = new TCHAR[pDocumentoFirmato[i].iSizeDocumento + 1];
						strcpy_s(pdf.sissInfo.pDocumento, pDocumentoFirmato[i].iSizeDocumento + 1, pDocumentoFirmato[i].pDocumento);
					}
					if (pDocumentoFirmato[i].pHashDocumento)
					{
						pdf.sissInfo.pHashDocumento = new TCHAR[pDocumentoFirmato[i].iSizeHashDocumento + 1];
						strcpy_s(pdf.sissInfo.pHashDocumento, pDocumentoFirmato[i].iSizeHashDocumento + 1, pDocumentoFirmato[i].pHashDocumento);
					}

					strcpy_s(pdf.sissInfo.szDocumentoFormato, pDocumentoFirmato[i].szDocumentoFormato);
					strcpy_s(pdf.sissInfo.szDocumentoFirmato, pDocumentoFirmato[i].szDocumentoFirmato);
					strcpy_s(pdf.sissInfo.szDocumentoMarcato, pDocumentoFirmato[i].szDocumentoMarcato);
					strcpy_s(pdf.sissInfo.szAutorizzazioneFormato, pDocumentoFirmato[i].szAutorizzazioneFormato);
					strcpy_s(pdf.sissInfo.szAutorizzazioneFirmato, pDocumentoFirmato[i].szAutorizzazioneFirmato);
					strcpy_s(pdf.sissInfo.szAutorizzazioneVersione, pDocumentoFirmato[i].szAutorizzazioneVersione);
					strcpy_s(pdf.sissInfo.szAlgoritmoHash, pDocumentoFirmato[i].szAlgoritmoHash);
					pdf.sissInfo.iSizeDocumento = pDocumentoFirmato[i].iSizeDocumentoOrig;
					strcat_s(pdf.szPdfPath, ".p7m");

					pPdfSigned->AddTail(pdf);
					bFound = TRUE;
					break;
				}

				if (!bFound)
				{
					CString strError;
					strError.Format(theApp.GetMessageString(IDS_SISS_CANT_FIND_REPORT_SIGNED), pDocumentoFirmato[i].szIdentificativoDocumento);
					theApp.AfxMessageBoxEndo(strError);
				}

				if (pDocumentoFirmato[i].pAutorizzazione)
					delete pDocumentoFirmato[i].pAutorizzazione;
				if (pDocumentoFirmato[i].pDocumento)
					delete pDocumentoFirmato[i].pDocumento;
				if (pDocumentoFirmato[i].pHashDocumento)
					delete pDocumentoFirmato[i].pHashDocumento;
				if (pDocumentoFirmato[i].pReferto)
					delete pDocumentoFirmato[i].pReferto;
			}

			delete pDocumentoFirmato;
		}
	}

	// Elimino memoria allocata...
	for(int i = 0; i < listDoc.GetCount(); i++)
	{
		if (pDocuments[i].pRefertoPdf)
			delete pDocuments[i].pRefertoPdf;

		if (pDocuments[i].pElencoPrestazioni)
			delete pDocuments[i].pElencoPrestazioni;
	}
	delete pDocuments;

	return pPdfSigned->GetCount() > 0;
}*/