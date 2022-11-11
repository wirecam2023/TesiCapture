#pragma once

#include "DLL_Imaging\h\AMPDFManager.h"

typedef CList<PDF> CPdfList;

class CPdfManager
{

public:

	CPdfManager();
	~CPdfManager(void);

	BOOL IsInitialize() { return m_bInit; };

	BOOL GetPdf(const long lIDEsame, CPdfList* pList);
	CString GetPdfPath(const long lPdfID);

	long ImportPdf(const long lIDPaziente, const long lIDEsame, const pdftype pdTipo, const CString sNote, const long lVersioneReferto, const long lIDPdfCheSostituisce, const BOOL bFitToPage, const CString sClassificazione, const CString sFileComplete);
	long ImportPdfRemoto(const long lIDPaziente, const long lIDEsame, const long lVersione, const CString sData, const long lTipo, const CString sEstensione, const CString sNote, const long lVersioneReferto, const BOOL bFitToPage, const CString sClassificazione, const long lInviareACarestream, const CString sPercorsoFileRemoto);
	BOOL ImportSignedPdf(const long lIDPaziente, const long lIDEsame, const pdftype ptTipo, const CString sNote, const CString sSmartCardUtente, const CString sSmartCardNumero, const CString sSmartCardEnteCertificato, const long lVersioneReferto, const long lIDPdfCheSostituisce, const BOOL bFitToPage, const CString sClassificazione, const CString sFileComplete, long* pIDPdf);
	long MovePdfEx(const long lIDPazienteOld, const long lIDPazienteNew, const long lIDEsame);

	BOOL SetPdfSospeso(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione, const BOOL bSospeso);
	BOOL SetPdfSospesoMotivo(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione, const CString sMotivoSospensione);
	BOOL SetPdfAnnullato(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione, const BOOL bAnnullato);
	BOOL SetPdfAnnullatoMotivo(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione, const CString sMotivoAnnullamento);
	BOOL SetPdfFirmato(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione);
	BOOL SetDocumentoXml(const long lIDPdf, const CString sRefertoXml);

	BOOL SetSignedPdfAsCanceled(const long lIDPaziente, const long lIDEsame, CPdfIDList* pListPdfFirmatiAnnullati);
	BOOL SetSingleSignedPdfAsCanceled(const long lIDPdf, const long lIDPaziente, const long lIDEsame);

	// Sandro 21/01/2014 // RAS 20130207 //

	BOOL GetDatiUltimoPdfFirmato(const long lIDEsame, long& lIDPrecedente, CString& sDataPrecedente, CString& sMotivoPrecedente);
	BOOL GetDatiUltimoPdfFirmatoIDVersioneReferto(const long lIDEsame, long& lIDPrecedente, long& lVersioneRefertoPrecedente);
	BOOL GetDatiUltimoPdfFirmatoData(const long lIDEsame, CString& sDataPrecedente);
	BOOL GetDatiUltimoPdfFirmatoMotivo(const long lIDEsame, CString& sMotivoPrecedente);

	BOOL GetDatiUltimoPdf(const long lIDEsame, long& lIDPrecedente, long& lVersioneRefertoPrecedente);

	// Sandro 16/03/2015 // modifica per Battaglia //
	BOOL UpdatePdfToFirmato(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sSmartCardUtente, const CString sSmartCardNumero, const CString sSmartCardEnteCertificato);

	BOOL SetPdfEliminato(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione);

	void SetPdfHistorical(const long lIDPdf, const long lIDPaziente, const long lIDEsame, const CString sImpianto, const CString sUtente, const CString sStazione);

	// Sandro 05/07/2017 //
	BOOL CopyToLocal(const long lIDPdf);

private:	

	BOOL m_bInit;

};