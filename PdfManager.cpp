#include "stdafx.h"
#include "Endox.h"
#include "PdfManager.h"

#include <io.h>

#include "DLL_Imaging\h\AmTesiSign.h"
#include "DLL_Imaging\h\ImgArchive.h"
#include "DLL_Imaging\h\AmLogin.h"
#include "DLL_Imaging\h\AmBase64.h"

#include "LogFileWriter.h"
#include "MmSystem.h"
#include "PdfDatiAggiuntiviSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPdfManager::CPdfManager() 
{
	// se il percorso dei PDF è vuoto lo imposto con il percorso delle immagini //
	if (theApp.m_sPercorsoPDF.IsEmpty())
	{
		char szPathImm[MAX_PATH];
		char szPathMin[MAX_PATH];
		if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
		{
			theApp.m_sPercorsoPDF = szPathImm;
		}
		else
		{
			ASSERT(FALSE);
		}
	}

	if (_access(theApp.m_sPercorsoPDF, 06) != 0)
	{
		// percorso impostato ma non esistente/raggiungibile //
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PDF_PATH_ERROR), MB_ICONSTOP);

		// segno che non siamo inizializzati //
		m_bInit = FALSE;
	}
	else
	{
		// percorso OK //
		m_bInit = AmPdfManager_Init(&theApp.m_dbEndox, theApp.m_sPercorsoPDF);
	}
}

CPdfManager::~CPdfManager(void)
{
	AmPdfManager_Finalize();
}

BOOL CPdfManager::GetPdf(const long lIDEsame, CPdfList* pList)
{
	ASSERT(pList && pList->IsEmpty());

	LONG lPdfNumber = AmPdfManager_GetPdfExamNumber(lIDEsame);
	if (lPdfNumber <= 0)
		return TRUE;

	PDF* pPdfBuffer = new PDF[lPdfNumber];
	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	if (!AmPdfManager_GetPdfExamList(lIDEsame, pPdfBuffer))
	{
		delete pPdfBuffer;
		return FALSE;
	}
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_PdfRetrieve(timeGetTime() - timeForLog, 0, lIDEsame, lPdfNumber, "CPdfManager::GetPdf");

	for(int i = 0; i < lPdfNumber; i++)
		pList->AddHead(pPdfBuffer[i]); // lo metto in testa così i PDF più nuovi sono sopra, non sotto //

	delete pPdfBuffer;
	return TRUE;
}

// --> Davide - Firma digitale
CString CPdfManager::GetPdfPath(const long lPdfID)
{
	return AmPdfManager_GetPdfPath(lPdfID);
}
// <-- Davide - Firma digitale

long CPdfManager::ImportPdf(const long lIDPaziente, const long lIDEsame, const pdftype pdTipo, const CString sNote, const long lVersioneReferto, const long lIDPdfCheSostituisce, const BOOL bFitToPage, const CString sClassificazione, const CString sFileComplete)
{
	long lPdfID = 0;

	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	AmPdfManager_AddPdf_File(lIDPaziente, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, pdTipo, sNote, lVersioneReferto, lIDPdfCheSostituisce, FALSE, FALSE, bFitToPage, sClassificazione, sFileComplete, &lPdfID);
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_PdfStore(timeGetTime() - timeForLog, lIDPaziente, lIDEsame, 1, "CPdfManager::ImportPdf");

	return lPdfID;
}

// Sandro 30/06/2017 // nuove funzioni per Fleury...
long CPdfManager::ImportPdfRemoto(const long lIDPaziente, const long lIDEsame, const long lVersione, const CString sData, const long lTipo, const CString sEstensione, const CString sNote, const long lVersioneReferto, const BOOL bFitToPage, const CString sClassificazione, const long lInviareACarestream, const CString sPercorsoFileRemoto)
{
	long lReturn = 0;

	if (IsInitialize())
	{
		DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //

		lReturn = AmPdfManager_AddPdf_RemoteFile(lIDPaziente, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, lVersione, sData, lTipo, sEstensione, sNote, lVersioneReferto, bFitToPage, sClassificazione, lInviareACarestream, sPercorsoFileRemoto);

		if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
			CLogFileWriter::Get()->WriteLogLine0_PdfStore(timeGetTime() - timeForLog, lIDPaziente, lIDEsame, 1, "CPdfManager::ImportPdfRemoto");
	}

	return lReturn;
}

// --> Davide - Firma digitale
BOOL CPdfManager::ImportSignedPdf(const long lIDPaziente, const long lIDEsame, const pdftype ptTipo, const CString sNote, const CString sSmartCardUtente, const CString sSmartCardNumero, const CString sSmartCardEnteCertificato, const long lVersioneReferto, const long lIDPdfCheSostituisce, const BOOL bFitToPage, const CString sClassificazione, const CString sFileComplete, long* pIDPdf)
{
	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	BOOL bReturn = (AmPdfManager_AddSignedPdf_File(lIDPaziente, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, ptTipo, sNote, sSmartCardUtente, sSmartCardNumero, sSmartCardEnteCertificato, lVersioneReferto, lIDPdfCheSostituisce, FALSE, FALSE, bFitToPage, sClassificazione, FALSE, sFileComplete, pIDPdf) > 0);
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_PdfStore(timeGetTime() - timeForLog, lIDPaziente, lIDEsame, 1, "CPdfManager::ImportSignedPdf");

	return bReturn;
}
// <-- Davide - Firma digitale

long CPdfManager::MovePdfEx(const long lIDPazienteOld, const long lIDPazienteNew, const long lIDEsame)
{
	return AmPdfManager_SetPdfNuovoPaziente(lIDPazienteOld, lIDPazienteNew, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer);
}

BOOL CPdfManager::SetPdfSospeso(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione, const BOOL bSospeso)
{
	if (m_bInit)
		return AmPdfManager_SetPdfSospeso(lIDPdf, lIDPaziente, lIDEsame, sImpianto, sUtente, sStazione, bSospeso);

	return FALSE;
}

BOOL CPdfManager::SetPdfSospesoMotivo(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione, const CString sMotivoAnnullamento)
{
	if (m_bInit)
		return AmPdfManager_SetPdfSospesoMotivo(lIDPdf, lIDPaziente, lIDEsame, sImpianto, sUtente, sStazione, sMotivoAnnullamento);

	return FALSE;
}

BOOL CPdfManager::SetPdfAnnullato(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione, const BOOL bAnnullato)
{
	if (m_bInit)
		return AmPdfManager_SetPdfAnnullato(lIDPdf, lIDPaziente, lIDEsame, sImpianto, sUtente, sStazione, bAnnullato);

	return FALSE;
}

BOOL CPdfManager::SetPdfAnnullatoMotivo(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione, const CString sMotivoAnnullamento)
{
	if (m_bInit)
		return AmPdfManager_SetPdfAnnullatoMotivo(lIDPdf, lIDPaziente, lIDEsame, sImpianto, sUtente, sStazione, sMotivoAnnullamento);

	return FALSE;
}

BOOL CPdfManager::SetPdfFirmato(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione)
{
	if (m_bInit)
		return AmPdfManager_SetPdfFirmato(lIDPdf, lIDPaziente, lIDEsame, sImpianto, sUtente, sStazione);

	return FALSE;
}

BOOL CPdfManager::SetSignedPdfAsCanceled(const long lIDPaziente, const long lIDEsame, CPdfIDList* pListPdfFirmatiAnnullati)
{
	return AmPdfManager_SetEliminatoAllSignedPdf(lIDPaziente, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, pListPdfFirmatiAnnullati);
}

BOOL CPdfManager::SetDocumentoXml(const long lIDPdf, const CString sRefertoXml)
{
	BOOL bReturn = TRUE;

	//Uso recordset esterno a pdf
	CString strFilter;
	strFilter.Format("idpdf=%li", lIDPdf);

	CPdfDatiAggiuntiviSet datiAggiuntiviSet(&theApp.m_dbEndox);
	datiAggiuntiviSet.SetOpenFilter(strFilter);

	datiAggiuntiviSet.Open();
	
	if (datiAggiuntiviSet.IsEOF())
	{
		datiAggiuntiviSet.AddNew();
		datiAggiuntiviSet.m_lIDPdf = lIDPdf;
		datiAggiuntiviSet.m_sRappresentazioneXml = sRefertoXml;
		
	}
	else
	{
		datiAggiuntiviSet.Edit();
		datiAggiuntiviSet.m_lIDPdf = lIDPdf;
		datiAggiuntiviSet.m_sRappresentazioneXml = sRefertoXml;
	}

	if (!datiAggiuntiviSet.Update())
		bReturn = FALSE;

	datiAggiuntiviSet.Close();

	return bReturn;
}

BOOL CPdfManager::SetSingleSignedPdfAsCanceled(const long lIDPdf, const long lIDPaziente, const long lIDEsame)
{
	return AmPdfManager_SetPdfEliminato(lIDPdf, lIDPaziente, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer);
}

BOOL CPdfManager::GetDatiUltimoPdfFirmato(const long lIDEsame, long& lIDPrecedente, CString& sDataPrecedente, CString& sMotivoPrecedente)
{
	return AmPdfManager_GetDatiUltimoPdfFirmato(pdftype_report, lIDEsame, lIDPrecedente, sDataPrecedente, sMotivoPrecedente);
}

BOOL CPdfManager::GetDatiUltimoPdfFirmatoIDVersioneReferto(const long lIDEsame, long& lIDPrecedente, long& lVersioneRefertoPrecedente)
{
	return AmPdfManager_GetDatiUltimoPdfFirmatoIDVersioneReferto(pdftype_report, lIDEsame, lIDPrecedente, lVersioneRefertoPrecedente);
}

BOOL CPdfManager::GetDatiUltimoPdf(const long lIDEsame, long& lIDPrecedente, long& lVersioneRefertoPrecedente)
{
	return AmPdfManager_GetDatiUltimoPdf(pdftype_report, lIDEsame, lIDPrecedente, lVersioneRefertoPrecedente);
}

BOOL CPdfManager::GetDatiUltimoPdfFirmatoData(const long lIDEsame, CString& sDataPrecedente)
{
	return AmPdfManager_GetDatiUltimoPdfFirmatoData(pdftype_report, lIDEsame, sDataPrecedente);
}

BOOL CPdfManager::GetDatiUltimoPdfFirmatoMotivo(const long lIDEsame, CString& sMotivoPrecedente)
{
	return AmPdfManager_GetDatiUltimoPdfFirmatoMotivo(pdftype_report, lIDEsame, sMotivoPrecedente);
}

BOOL CPdfManager::UpdatePdfToFirmato(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sSmartCardUtente, const CString sSmartCardNumero, const CString sSmartCardEnteCertificato)
{
	if (m_bInit)
		return AmPdfManager_UpdatePdfToFirmato(lIDPdf, lIDPaziente, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, pdftype_report_allegato, "P7M", sSmartCardUtente, sSmartCardNumero, sSmartCardEnteCertificato);

	return FALSE;
}

BOOL CPdfManager::SetPdfEliminato(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione)
{
	if (m_bInit)
		return AmPdfManager_SetPdfEliminato(lIDPdf, lIDPaziente, lIDEsame, sImpianto, sUtente, sStazione);

	return FALSE;
}

void CPdfManager::SetPdfHistorical(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione)
{
	if (m_bInit)
		AmPdfManager_SetPdfToHistoricalArchive(lIDPdf, lIDPaziente, lIDEsame, sImpianto, sUtente, sStazione);
}

// Sandro 05/07/2017 //
BOOL CPdfManager::CopyToLocal(const long lIDPdf)
{
	if (m_bInit)
		return AmPdfManager_CopyToLocal(lIDPdf);

	return FALSE;
}