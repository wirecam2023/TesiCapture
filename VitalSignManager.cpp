#include "stdafx.h"
#include "Endox.h"
#include "VitalSignManager.h"

#include "CustomDate.h"
#include "EsamiView.h"
#include "VitalSignDispositiviSet.h"
#include "VitalSignMisurazioniDetailSet.h"
#include "VitalSignMisurazioniHeaderSet.h"
#include "VitalSignPdfWaitingDlg.h"

#include "XmlUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CVitalSignManager::CVitalSignManager(CEsamiView *pEsamiView)
{
	m_pEsamiView = pEsamiView;
	m_pxmlDocument = NULL;	

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	if (SUCCEEDED(m_pxmlDocument.CreateInstance(__uuidof(MSXML2::DOMDocument60))))
	{
		m_pxmlDocument->async = VARIANT_FALSE;
		m_pxmlDocument->preserveWhiteSpace = VARIANT_TRUE;
	}
}


CVitalSignManager::~CVitalSignManager()
{
	if (m_pxmlDocument != NULL)
		m_pxmlDocument.Release();
}

BOOL CVitalSignManager::StartSession(int idDispositivo, CString *pIdSessione, MonitoringPhase fase)
{
	BOOL bReturn = FALSE;

	CString codDisp;
	CVitalSignDispositiviSet dispositiviSet;
	CString filter;
	filter.Format("id=%li", idDispositivo);
	dispositiviSet.SetOpenFilter(filter);

	if (dispositiviSet.OpenRecordset("CVitalSignManager::StartSession"))
	{
		if (!dispositiviSet.IsEOF())
		{
			codDisp = dispositiviSet.m_sCodiceIdentificativo;
		}

		dispositiviSet.CloseRecordset("CVitalSignManager::StartSession");
	}	

	//

	CString rootTag = "<StartNewSession></StartNewSession>";
	BSTR bstr = rootTag.AllocSysString();
	if (m_pxmlDocument->loadXML(bstr) == VARIANT_FALSE)
	{
		theApp.AfxMessageBoxEndo("Error creating xml document");
		::SysFreeString(bstr);
		return FALSE;
	}
	::SysFreeString(bstr);

	//Get the root element just created    
	MSXML2::IXMLDOMElementPtr pXMLRootElem = m_pxmlDocument->GetdocumentElement();

	MSXML2::IXMLDOMProcessingInstructionPtr pXMLProcessingNode =
		m_pxmlDocument->createProcessingInstruction("xml", " version='1.0' encoding='UTF-8'");

	//Attacco l'elemento root
	_variant_t vtObject;
	vtObject.vt = VT_DISPATCH;
	vtObject.pdispVal = pXMLRootElem;
	vtObject.pdispVal->AddRef();
	m_pxmlDocument->insertBefore(pXMLProcessingNode, vtObject);

	//

	//tag sessionId
	MSXML2::IXMLDOMElementPtr pXMLChildSessionId;
	CString sFase;
	sFase.Format("%li", fase);
	CXmlUtils::AddNode(pXMLChildSessionId, m_pxmlDocument, pXMLRootElem, "fase", sFase);

	//tag idDispositivo
	MSXML2::IXMLDOMElementPtr pXMLChildIdDispositivo;
	CXmlUtils::AddNode(pXMLChildIdDispositivo, m_pxmlDocument, pXMLRootElem, "idDispositivo", codDisp);

	//tag Measuraments
	MSXML2::IXMLDOMElementPtr pXMLChildIdEsame;
	CString sIdEsame;
	sIdEsame.Format("%li", m_pEsamiView->m_pEsamiSet->m_lContatore);
	CXmlUtils::AddNode(pXMLChildIdEsame, m_pxmlDocument, pXMLRootElem, "idEsame", sIdEsame);

	//tag Patient
	MSXML2::IXMLDOMElementPtr pXMLChildPatient;
	CXmlUtils::AddNode(pXMLChildPatient, m_pxmlDocument, pXMLRootElem, "patient");

	//tag patient->id
	CString sIdPaziente;
	sIdPaziente.Format("%li", m_pEsamiView->m_pPazientiSet->m_lContatore);
	MSXML2::IXMLDOMElementPtr pXMLChildIdPaziente;
	CXmlUtils::AddNode(pXMLChildIdPaziente, m_pxmlDocument, pXMLChildPatient, "id", sIdPaziente);

	//tag patient->cognome
	MSXML2::IXMLDOMElementPtr pXMLChildCognome;
	CXmlUtils::AddNode(pXMLChildCognome, m_pxmlDocument, pXMLChildPatient, "cognome", m_pEsamiView->m_pPazientiSet->m_sCognome);

	//tag patient->nome
	MSXML2::IXMLDOMElementPtr pXMLChildNome;
	CXmlUtils::AddNode(pXMLChildNome, m_pxmlDocument, pXMLChildPatient, "nome", m_pEsamiView->m_pPazientiSet->m_sNome);

	//tag patient->dataNascita
	CCustomDate dataNascita(m_pEsamiView->m_pPazientiSet->m_lNatoIlCustom);
	MSXML2::IXMLDOMElementPtr pXMLChildDataNascita;
	CXmlUtils::AddNode(pXMLChildDataNascita, m_pxmlDocument, pXMLChildPatient, "dataNascita", dataNascita.GetDate("%Y%m%d"));

	//tag patient->sesso
	MSXML2::IXMLDOMElementPtr pXMLChildSesso;
	CString sSesso;
	sSesso.Format("%li", m_pEsamiView->m_pPazientiSet->m_lSessoPaz);
	CXmlUtils::AddNode(pXMLChildSesso, m_pxmlDocument, pXMLChildPatient, "sesso", sSesso);

	//tag patient->cittaNascita
	MSXML2::IXMLDOMElementPtr pXMLChildCittaNascita;
	CXmlUtils::AddNode(pXMLChildCittaNascita, m_pxmlDocument, pXMLChildPatient, "cittaNascita", m_pEsamiView->m_pPazientiSet->m_sNatoA);

	//tag patient->istatNascita
	MSXML2::IXMLDOMElementPtr pXMLChildIstatNascita;
	CString lIDComuneN;
	lIDComuneN.Format("%li", m_pEsamiView->m_pPazientiSet->m_lIDComuneNascita);
	CXmlUtils::AddNode(pXMLChildIstatNascita, m_pxmlDocument, pXMLChildPatient, "istatNascita", lIDComuneN);

	//tag patient->indirizzo
	MSXML2::IXMLDOMElementPtr pXMLChildIndirizzo;
	CXmlUtils::AddNode(pXMLChildIndirizzo, m_pxmlDocument, pXMLChildPatient, "indirizzo", m_pEsamiView->m_pPazientiSet->m_sVia);

	//tag patient->citta
	MSXML2::IXMLDOMElementPtr pXMLChildCitta;
	CXmlUtils::AddNode(pXMLChildCitta, m_pxmlDocument, pXMLChildPatient, "citta", m_pEsamiView->m_pPazientiSet->m_sCitta);

	//tag patient->provincia
	MSXML2::IXMLDOMElementPtr pXMLChildProvincia;
	CXmlUtils::AddNode(pXMLChildProvincia, m_pxmlDocument, pXMLChildPatient, "provincia", m_pEsamiView->m_pPazientiSet->m_sProvincia);

	//tag patient->CAP
	MSXML2::IXMLDOMElementPtr pXMLChildCap;
	CXmlUtils::AddNode(pXMLChildCap, m_pxmlDocument, pXMLChildPatient, "CAP", m_pEsamiView->m_pPazientiSet->m_sCAP);

	//tag patient->istat
	MSXML2::IXMLDOMElementPtr pXMLChildIstat;
	CString lIDComune;
	lIDComune.Format("%li", m_pEsamiView->m_pPazientiSet->m_lIDComune);
	CXmlUtils::AddNode(pXMLChildIstat, m_pxmlDocument, pXMLChildPatient, "istat", lIDComune);

	//tag patient->telefono1
	MSXML2::IXMLDOMElementPtr pXMLChildTelefono1;
	CXmlUtils::AddNode(pXMLChildTelefono1, m_pxmlDocument, pXMLChildPatient, "telefono1", m_pEsamiView->m_pPazientiSet->m_sTelefono1);

	//tag patient->telefono2
	MSXML2::IXMLDOMElementPtr pXMLChildTelefono2;
	CXmlUtils::AddNode(pXMLChildTelefono2, m_pxmlDocument, pXMLChildPatient, "telefono2", m_pEsamiView->m_pPazientiSet->m_sTelefono2);

	//tag patient->telefono3
	MSXML2::IXMLDOMElementPtr pXMLChildTelefono3;
	CXmlUtils::AddNode(pXMLChildTelefono3, m_pxmlDocument, pXMLChildPatient, "telefono3", m_pEsamiView->m_pPazientiSet->m_sCellulare1);

	//tag patient->telefono4
	MSXML2::IXMLDOMElementPtr pXMLChildTelefono4;
	CXmlUtils::AddNode(pXMLChildTelefono4, m_pxmlDocument, pXMLChildPatient, "telefono4", m_pEsamiView->m_pPazientiSet->m_sCellulare2);

	//tag patient->codiceFiscale
	MSXML2::IXMLDOMElementPtr pXMLChildCF;
	CXmlUtils::AddNode(pXMLChildCF, m_pxmlDocument, pXMLChildPatient, "codiceFiscale", m_pEsamiView->m_pPazientiSet->m_sCodFisc);

	//tag patient->codiceSanitario
	MSXML2::IXMLDOMElementPtr pXMLChildCS;
	CXmlUtils::AddNode(pXMLChildCS, m_pxmlDocument, pXMLChildPatient, "codiceSanitario", m_pEsamiView->m_pPazientiSet->m_sCodSanit);

	//tag patient->nazionalita
	MSXML2::IXMLDOMElementPtr pXMLChildNazionalita;
	CXmlUtils::AddNode(pXMLChildNazionalita, m_pxmlDocument, pXMLChildPatient, "nazionalita", m_pEsamiView->m_pPazientiSet->m_sNazionalita);

	//tag patient->medicoCurante
	MSXML2::IXMLDOMElementPtr pXMLChildMedico;
	CXmlUtils::AddNode(pXMLChildMedico, m_pxmlDocument, pXMLChildPatient, "medicoCurante", m_pEsamiView->m_pPazientiSet->m_sMedicoCurante);

	//tag patient->ulssResidenza
	MSXML2::IXMLDOMElementPtr pXMLChildUlssResidenza;
	CXmlUtils::AddNode(pXMLChildUlssResidenza, m_pxmlDocument, pXMLChildPatient, "ulssResidenza", m_pEsamiView->m_pPazientiSet->m_sUlssResidenza);

	//tag patient->codiceRicovero
	MSXML2::IXMLDOMElementPtr pXMLChildCodiceRicovero;
	CXmlUtils::AddNode(pXMLChildCodiceRicovero, m_pxmlDocument, pXMLChildPatient, "codiceRicovero", m_pEsamiView->m_pPazientiSet->m_sIdEpisodioRicovero);



	//By default it is writing the encoding = UTF-16. Let us change the encoding to UTF-8
	MSXML2::IXMLDOMNodePtr pXMLFirstChild = m_pxmlDocument->GetfirstChild();
	// A map of the a attributes (vesrsion, encoding) values (1.0, UTF-8) pair
	MSXML2::IXMLDOMNamedNodeMapPtr pXMLAttributeMap = pXMLFirstChild->Getattributes();
	MSXML2::IXMLDOMNodePtr pXMLEncodNode = pXMLAttributeMap->getNamedItem(_T("encoding"));
	pXMLEncodNode->PutnodeValue(_T("UTF-8"));    //encoding = UTF-8

	//

	CString strInput = CXmlUtils::GetXml(m_pxmlDocument);

	CString strOutput;
	if (Go(strInput, &strOutput))
	{
		BSTR bstr = strOutput.AllocSysString();
		if (m_pxmlDocument->loadXML(bstr) == VARIANT_FALSE)
		{
			theApp.AfxMessageBoxEndo("Error creating xml document");
			strOutput.ReleaseBuffer();
			bReturn = FALSE;
		}
		else
		{
			if (MSXML2::IXMLDOMNodePtr pStartNewSession = m_pxmlDocument->GetdocumentElement())
			{
				if (MSXML2::IXMLDOMNodePtr pIdSessionet = CXmlUtils::FindChild(pStartNewSession, "idSessione"))
				{
					pIdSessione->Format("%s", CString(pIdSessionet->firstChild->nodeValue));
					bReturn = TRUE;
				}
				else
				{
					theApp.AfxMessageBoxEndo(strOutput);
				}
			}
		}

		::SysFreeString(bstr);		
	}	

	return bReturn;
}

BOOL CVitalSignManager::StopSession(CString pIdSessione)
{
	BOOL bReturn = FALSE;

	//

	CString rootTag = "<StopSession></StopSession>";
	BSTR bstr = rootTag.AllocSysString();
	if (m_pxmlDocument->loadXML(bstr) == VARIANT_FALSE)
	{
		theApp.AfxMessageBoxEndo("Error creating xml document");
		::SysFreeString(bstr);
		return FALSE;
	}
	::SysFreeString(bstr);

	//Get the root element just created    
	MSXML2::IXMLDOMElementPtr pXMLRootElem = m_pxmlDocument->GetdocumentElement();

	MSXML2::IXMLDOMProcessingInstructionPtr pXMLProcessingNode =
		m_pxmlDocument->createProcessingInstruction("xml", " version='1.0' encoding='UTF-8'");

	//Attacco l'elemento root
	_variant_t vtObject;
	vtObject.vt = VT_DISPATCH;
	vtObject.pdispVal = pXMLRootElem;
	vtObject.pdispVal->AddRef();
	m_pxmlDocument->insertBefore(pXMLProcessingNode, vtObject);

	//

	//tag sessionId
	MSXML2::IXMLDOMElementPtr pXMLChildSessionId;
	CXmlUtils::AddNode(pXMLChildSessionId, m_pxmlDocument, pXMLRootElem, "idSessione", pIdSessione);	

	//By default it is writing the encoding = UTF-16. Let us change the encoding to UTF-8
	MSXML2::IXMLDOMNodePtr pXMLFirstChild = m_pxmlDocument->GetfirstChild();
	// A map of the a attributes (vesrsion, encoding) values (1.0, UTF-8) pair
	MSXML2::IXMLDOMNamedNodeMapPtr pXMLAttributeMap = pXMLFirstChild->Getattributes();
	MSXML2::IXMLDOMNodePtr pXMLEncodNode = pXMLAttributeMap->getNamedItem(_T("encoding"));
	pXMLEncodNode->PutnodeValue(_T("UTF-8"));    //encoding = UTF-8

	//

	CString strInput = CXmlUtils::GetXml(m_pxmlDocument);

	CString strOutput;
	if (Go(strInput, &strOutput))
	{		
		BSTR bstr = strOutput.AllocSysString();
		if (m_pxmlDocument->loadXML(bstr) == VARIANT_FALSE)
		{
			theApp.AfxMessageBoxEndo("Error creating xml document");
			strOutput.ReleaseBuffer();
			bReturn = FALSE;
		}
		else
		{
			if (MSXML2::IXMLDOMNodePtr pStartNewSession = m_pxmlDocument->GetdocumentElement())
			{
				if (MSXML2::IXMLDOMNodePtr pIdSessionet = CXmlUtils::FindChild(pStartNewSession, "result"))
				{
					if (CString(pIdSessionet->firstChild->nodeValue) != "true")
						theApp.AfxMessageBoxEndo(CString(pIdSessionet->firstChild->nodeValue));					
					else
						bReturn = TRUE;
				}
				else
				{
					theApp.AfxMessageBoxEndo(strOutput);
				}
			}
		}

		::SysFreeString(bstr);		
	}			

	return bReturn;
}

BOOL CVitalSignManager::ChangeNotes(CString idSessione, CString note, CList<Measurament>* measuraments)
{
	BOOL bReturn = FALSE;

	//

	CString rootTag = "<ChangeNotes></ChangeNotes>";
	BSTR bstr = rootTag.AllocSysString();
	if (m_pxmlDocument->loadXML(bstr) == VARIANT_FALSE)
	{
		theApp.AfxMessageBoxEndo("Error creating xml document");
		::SysFreeString(bstr);
		return FALSE;
	}
	::SysFreeString(bstr);

	//Get the root element just created    
	MSXML2::IXMLDOMElementPtr pXMLRootElem = m_pxmlDocument->GetdocumentElement();

	MSXML2::IXMLDOMProcessingInstructionPtr pXMLProcessingNode =
		m_pxmlDocument->createProcessingInstruction("xml", " version='1.0' encoding='UTF-8'");

	//Attacco l'elemento root
	_variant_t vtObject;
	vtObject.vt = VT_DISPATCH;
	vtObject.pdispVal = pXMLRootElem;
	vtObject.pdispVal->AddRef();
	m_pxmlDocument->insertBefore(pXMLProcessingNode, vtObject);

	//

	//tag sessionId
	MSXML2::IXMLDOMElementPtr pXMLChildSessionId;
	CXmlUtils::AddNode(pXMLChildSessionId, m_pxmlDocument, pXMLRootElem, "sessionId", idSessione);

	//tag notes
	MSXML2::IXMLDOMElementPtr pXMLChildNotes;
	CXmlUtils::AddNode(pXMLChildNotes, m_pxmlDocument, pXMLRootElem, "notes", note);

	//tag Measuraments
	MSXML2::IXMLDOMElementPtr pXMLChildMeasuraments;
	CXmlUtils::AddNode(pXMLChildMeasuraments, m_pxmlDocument, pXMLRootElem, "Measuraments");

	if (measuraments)
	{
		POSITION pos = measuraments->GetHeadPosition();
		while (pos)
		{
			Measurament tempMes = measuraments->GetNext(pos);

			//tag Measuraments->Measurament
			MSXML2::IXMLDOMElementPtr pXMLChildMeasurament;
			CXmlUtils::AddNode(pXMLChildMeasurament, m_pxmlDocument, pXMLChildMeasuraments, "Measurament");

			//tag Measuraments->Measurament->id
			MSXML2::IXMLDOMElementPtr pXMLChildId;
			CXmlUtils::AddNode(pXMLChildId, m_pxmlDocument, pXMLChildMeasurament, "id", tempMes.sId);

			//tag Measuraments->Measurament->notes
			MSXML2::IXMLDOMElementPtr pXMLChildNotes;
			CXmlUtils::AddNode(pXMLChildNotes, m_pxmlDocument, pXMLChildMeasurament, "notes", tempMes.sNotes);

		}
	}

	//By default it is writing the encoding = UTF-16. Let us change the encoding to UTF-8
	MSXML2::IXMLDOMNodePtr pXMLFirstChild = m_pxmlDocument->GetfirstChild();
	// A map of the a attributes (vesrsion, encoding) values (1.0, UTF-8) pair
	MSXML2::IXMLDOMNamedNodeMapPtr pXMLAttributeMap = pXMLFirstChild->Getattributes();
	MSXML2::IXMLDOMNodePtr pXMLEncodNode = pXMLAttributeMap->getNamedItem(_T("encoding"));
	pXMLEncodNode->PutnodeValue(_T("UTF-8"));    //encoding = UTF-8

	//

	CString strInput = CXmlUtils::GetXml(m_pxmlDocument);	

	CString strOutput;
	if (Go(strInput, &strOutput))
	{		
		BSTR bstr = strOutput.AllocSysString();
		if (m_pxmlDocument->loadXML(bstr) == VARIANT_FALSE)
		{
			theApp.AfxMessageBoxEndo("Error creating xml document");
			strOutput.ReleaseBuffer();
			bReturn = FALSE;
		}
		else
		{
			if (MSXML2::IXMLDOMNodePtr pStartNewSession = m_pxmlDocument->GetdocumentElement())
			{
				if (MSXML2::IXMLDOMNodePtr pIdSessionet = CXmlUtils::FindChild(pStartNewSession, "result"))
				{
					if (CString(pIdSessionet->firstChild->nodeValue) != "true")
						theApp.AfxMessageBoxEndo(CString(pIdSessionet->firstChild->nodeValue));
					else
						bReturn = TRUE;

				}
				else
				{
					theApp.AfxMessageBoxEndo(strOutput);
				}
			}
		}

		::SysFreeString(bstr);

		
	}	

	return bReturn;
}

BOOL CVitalSignManager::Go(CString sInput, CString* sOutput)
{
	BOOL bReturn = FALSE;

	//Chiamata all'exe
	TCHAR szProcess[1024];
	sprintf_s(szProcess, "%s\\VitalSignIntegrationClient\\VitalSignIntegrationClient.exe %s", theApp.m_sDirProg, theApp.m_sVitalSignWebServiceEndpoint);

	DWORD dwError = 0, dwExitCode = 0;

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	DWORD iBufferPSLength = (DWORD)strlen(sInput);
	BYTE* pBufferPS = (BYTE*)sInput.GetBuffer(MAX_PATH);
	sInput.ReleaseBuffer();

	HANDLE hChildStdinRd, hChildStdinWr;
	if (!CreatePipe(&hChildStdinRd, &hChildStdinWr, &sa, iBufferPSLength + 1))
	{
		theApp.AfxMessageBoxEndo("CreatePipe 1 error");
		return FALSE;
	}

	HANDLE hChildStdoutRd, hChildStdoutWr;
	if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &sa, 10000000))
	{
		theApp.AfxMessageBoxEndo("CreatePipe 2 error");
		return FALSE;
	}

	DWORD dwWritten;
	if (!::WriteFile(hChildStdinWr,
		pBufferPS,
		iBufferPSLength,
		&dwWritten,
		NULL))
	{
		CString error;
		error.Format("WriteFile 1 error %li", GetLastError());
		theApp.AfxMessageBoxEndo(error);
		return FALSE;
	}

	CloseHandle(hChildStdinWr);

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hChildStdinRd;
	si.hStdOutput = hChildStdoutWr;
	si.hStdError = NULL;

	DWORD iBufferPDFLength = 1024 * 1024;

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
				if (dwTotalBytes <= iBufferPDFLength)
				{
					BYTE* pBufferTemp = new BYTE[iBufferPDFLength];
					ZeroMemory(pBufferTemp, sizeof(BYTE)*iBufferPDFLength);
					if (::ReadFile(hChildStdoutRd, pBufferTemp, dwTotalBytes, &dwReaded, NULL))
					{
						sOutput->Format("%s", (LPTSTR)pBufferTemp);
#ifdef _DEBUG
						theApp.AfxMessageBoxEndo(*sOutput);
#endif
						bReturn = TRUE;
					}
					else
						theApp.AfxMessageBoxEndo("RTead file error");

					delete pBufferTemp;
				}
				else
					theApp.AfxMessageBoxEndo("RTead file error");
			}
			else
				theApp.AfxMessageBoxEndo("PeekNamedPipe error");
		}
		else
		{
			theApp.AfxMessageBoxEndo("ExitCodeProcess %li", dwExitCode);
		}

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	else
	{
		theApp.AfxMessageBoxEndo("CreateProcess error");
	}

	CloseHandle(hChildStdinRd);
	CloseHandle(hChildStdoutRd);
	CloseHandle(hChildStdoutWr);

	return bReturn;
}

BOOL CVitalSignManager::ChangeNotesAndWait(CString sIdSessione, long lIDHeader, long lOldIdPdf, CString sOldNotes, CList<Measurament>* oldChangedMeasuraments, CString sNote, CList<Measurament>* changedMeasuraments)
{
	BOOL bReturn = FALSE;

	if (CVitalSignManager(m_pEsamiView).ChangeNotes(sIdSessione, sNote, changedMeasuraments))
	{
		//Proviamo a mettere una dialog di attesa per ricevere il pdf
		CVitalSignPdfWaitingDlg waitingDlg(m_pEsamiView, lIDHeader, lOldIdPdf);
		if (waitingDlg.DoModal() == IDOK)
		{
			return TRUE; //Qui ritorno.
		}

	}
	
	//Questo codice viene eseguito se ChangeNotes fallisce o se premo annulla durante l'attesa del nuovo pdf.
	//Ripristino i vecchi commenti
	CString filter;
	filter.Format("ID=%li", lIDHeader);
	CVitalSignMisurazioniHeaderSet vitalSignMisSet;
	vitalSignMisSet.SetOpenFilter(filter);
			
	if (vitalSignMisSet.OpenRecordset("CVitalSignManager::ChangeNotesAndWait"))
	{
		if (vitalSignMisSet.EditRecordset("CVitalSignManager::ChangeNotesAndWait"))
		{
			//Riprisitno le vecchie note del pdf
			vitalSignMisSet.m_sNote = sOldNotes;
			vitalSignMisSet.UpdateRecordset("CVitalSignManager::ChangeNotesAndWait");

			//Ripristino le vecchie note delle misurazioni
			POSITION pos = oldChangedMeasuraments->GetHeadPosition();
			while (pos)
			{
				CVitalSignManager::Measurament tempMes = oldChangedMeasuraments->GetNext(pos);

				CString filter;
				filter.Format("ID=%li", tempMes.lId);
				CVitalSignMisurazioniDetailSet tmpDetailSet;
				tmpDetailSet.SetOpenFilter(filter);

				if (tmpDetailSet.OpenRecordset("CVitalSignManager::ChangeNotesAndWait"))
				{
					if (!tmpDetailSet.IsEOF())
					{
						if (tmpDetailSet.EditRecordset("CVitalSignManager::ChangeNotesAndWait"))
						{
							tmpDetailSet.m_sNote = tempMes.sNotes;

							tmpDetailSet.UpdateRecordset("CVitalSignManager::ChangeNotesAndWait");
						}
					}

					tmpDetailSet.CloseRecordset("CVitalSignManager::ChangeNotesAndWait");
				}

			}			
		}

		vitalSignMisSet.CloseRecordset("CVitalSignManager::ChangeNotesAndWait");
	}

	return FALSE;
}