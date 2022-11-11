#pragma once

class CDigitalSignUtil
{
public:
	/// <summary> 
	/// Dati necessari firma SISS
	/// </summary> 
	struct tagSissInfo
	{
		tagSissInfo()
		{
			ZeroMemory(this, sizeof(tagSissInfo));
		}

		LPTSTR pAutorizzazione;
		TCHAR szAutorizzazioneFormato[51];
		TCHAR szAutorizzazioneFirmato[51];
		TCHAR szAutorizzazioneVersione[51];

		LPTSTR pDocumento;
		TCHAR szDocumentoFormato[51];
		TCHAR szDocumentoFirmato[51];
		TCHAR szDocumentoMarcato[51];
		LPTSTR pHashDocumento;
		TCHAR szAlgoritmoHash[51];
		UINT iSizeDocumento;
		TCHAR szDataOraDocumento[15];
	};

	/// <summary> 
	/// Oggetto pdf da firmare
	/// </summary> 
	struct tagPdfInfo
	{
		tagPdfInfo()
		{
			ZeroMemory(this, sizeof(tagPdfInfo));
		}

		long lPatientID;
		long lExamID;
		TCHAR szPdfPath[MAX_PATH];

		tagSissInfo sissInfo;

		// BOOL bReferto;
		BOOL bRefertoAnnullativo;
	};

	/// <summary> 
	/// Inizializzazione oggetto
	/// </summary> 
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	static BOOL Initialize();

	/// <summary> 
	/// Distruzione oggetto
	/// </summary> 
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	static BOOL Finalize();

	/// <summary> 
	/// Distruzione oggetto
	/// </summary> 
	/// <param name="pUser">infomazioni smart card attuale OUT</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	static BOOL GetSmartCardUtente(CString* pUtente);
	static BOOL GetSmartCardNumero(CString* pNumero);
	static BOOL GetSmartCardEnteCertificato(CString* pEnteCertificato);

	/// <summary> 
	/// Firma digitalmente un pdf
	/// </summary> 
	/// <param name="pParentWnd">finestra padre</param>
	/// <param name="lPatientID">id paziente</param>
	/// <param name="lExamID">id esame</param>
	/// <param name="szPdfPath">path pdf da firmare</param>
	/// <param name="pSissInfo">informazioni SISS OUT</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	static BOOL SignPdf(CWnd* pParentWnd, long lPatientID, long lExamID, LPCTSTR szPdfPath, tagSissInfo* pSissInfo, BOOL bRefertoAnnullativo);

	/// <summary> 
	/// 
	/// </summary> 
	/// <param name="szFilePdf"></param>
	/// <param name="pBufferPDF"></param>
	/// <param name="pPDFBytesSize"></param>
	static BOOL DecryptPdf(LPCTSTR szFilePdf, LPBYTE* pBufferDecryptedPDF, DWORD* pBufferDecryptedPDFSize);

protected:
	/// <summary> 
	/// Firma digitalmente un elenco di pdf con Comped
	/// </summary> 
	/// <param name="pParentWnd">finestra padre</param>
	/// <param name="pPdfToSign">lista pdf da firmare</param>
	/// <param name="pPdfSigned">ilista pdf firmati correttamente OUT</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	static BOOL SignPdfWithComped(CWnd* pParentWnd, CList<tagPdfInfo>* pPdfToSign, CList<tagPdfInfo>* pPdfSigned);

	/// <summary> 
	/// Firma digitalmente un pdf con Comped
	/// </summary> 
	/// <param name="pParentWnd">finestra padre</param>
	/// <param name="lPatientID">id paziente</param>
	/// <param name="lExamID">id esame</param>
	/// <param name="szPdfPath">path pdf da firmare</param>
	/// <param name="pSissInfo">informazioni SISS OUT</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	static BOOL SignPdfWithComped(CWnd* pParentWnd, long lPatientID, long lExamID, LPCTSTR szPdfPath, tagSissInfo* pSissInfo);

	static BOOL KillProcess(LPCTSTR szProcess);
};
