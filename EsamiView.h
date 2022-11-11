#ifndef __ESAMIVIEW_H__
	#define __ESAMIVIEW_H__

#include "DLL_Imaging\h\AmPdfCreatorHaru.h"
#include "DLL_Imaging\h\AmPdfManager.h"
#include "DLL_Imaging\h\AmXmlReportGenerator.h"

#include "Common.h"
#include "EndoxTabCtrl.h"
#include "FrameStatic.h"
#include "ObSelect.h"
#include "TXTextControl23.h"
#include "StdAfx.h"
#include "ACEdit.h"

class CAlbumForm;
class CEndoxBar;
class CEndoxDynForm;
class CEsamiDoc;
class CEsamiSet;
class CExportDlg;
class CMyDocManager;
class CQueryDlg;
class CEsamiIntegratiSet; // Luiz - 07/05/2019 - P3 - Desconjuga exames - ESAMIINTEGRATI
class CImageDlg; //Gabriel BUG 6225 - Lista DO

#define HSIZE_PAL 768
#define VSIZE_PAL 576

#define HSIZE_PAL_2 384 // (768 / 2) //
#define VSIZE_PAL_2 288 // (576 / 2) //

#define HSIZE_PAL_3 256 // (768 / 3) //
#define VSIZE_PAL_3 192 // (576 / 3) //

#define HSIZE_PAL_4 192 // (768 / 4) //
#define VSIZE_PAL_4 144 // (576 / 4) //

#define STAMPA 0x111
#define ANTEPRIMA 0x222
#define CHIUSURA 0x333
#define CHIUSURA_FASE 0x444
#define ANTEPRIMA_NO_STAMPA 0x555
#define CHIUSURA_ESAMECORRELATI 0x900

#define ANTEPRIMADLG_SEMPLICE 0x666
#define ANTEPRIMADLG_CHIUSURA 0x777
#define ANTEPRIMADLG_FIRMA 0x888
#define ANTEPRIMADLG_NO_STAMPA 0x999

#define VERIFICA_NO FALSE
#define VERIFICA_SI TRUE

enum EsamiViewPrinters
{
	Printer_ChiediStampante = 0,

	Printer_Immagini,

	Printer_Report1,
	Printer_Report2,
	Printer_Report3,
	Printer_Report4,
	Printer_Report5,
	Printer_Report6,
	Printer_Report7,
	Printer_Report8,
	Printer_Report9,

	Printer_Totali
};

typedef struct
{  

	BOOL m_bArchivePDFCopy;

	long m_lImagePrinting;
	long m_lImageToPrint;
	long m_lOrganPrinting;
	long m_lOrganToPrint;
	long m_lPrinterToUse;
	BOOL m_bFitToPage;

	CList <int> m_listImmaginiStampa;
	CList <tagPunti> m_listPuntiStampa;

	CString m_sReportFileOriginal;
	CString m_sReportFilePrinting;

} STRUCT_STAMPA;

typedef struct
{
	CString m_sRptFile;
	CString m_sPdfFile;
	long m_lPrinterToUse;
	long m_lCopies;
	BOOL m_bFitToPage;
} STRUCT_STAMPA_CUMULATIVA;

struct tagStreamingStateTHREAD
{
	CEsamiView* pEsamiView;
	HWND hWndParent;
};

/// <summary> 
/// Vista primaria dell'applicazione
/// Rappresenta l'oggetto finestra dell'interfaccia principale
/// </summary> 

class CEsamiView : public CResizableFormView
{

	DECLARE_DYNCREATE(CEsamiView)

public:

	/// <summary>
	/// Costruttore
	/// </summary>
	CEsamiView();

	/// <summary>
	/// Distruttore
	/// </summary>
	virtual ~CEsamiView();

	enum { IDD = IDD_ENDOX_FORM };

	/// <summary>
	/// Aggiunge l'elemento alla pagina di stampa
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite pdf tramite Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="listElement">riferimento alla lista degli elementi del report attualmente pronti per la stampa</param>
	/// <param name="lFieldType">tipo di campo da stampare</param>
	/// <param name="sFieldValue">valore del campo</param>
	/// <param name="lLeft">posizione sinistra</param>
	/// <param name="lRight">posizione destra</param>
	/// <param name="lTop">posizione in alto</param>
	/// <param name="lBottom">posizione in basso</param>
	/// <param name="rgbColor">colore da utilizzare</param>
	/// <param name="lCheck">determina se bisogna stampare il commento all'immagine</param>
	/// <param name="lParam">non utilizzato</param>
	/// <param name="sFontName">nome del font</param>
	/// <param name="lFontHeight">altezza del font</param>
	/// <param name="lFontWeight">peso del font</param>
	/// <param name="lFontUnder">sottolineatura del font</param>
	/// <param name="lFontItalic">font "italico"</param>
	/// <param name="lAlignment">allinemento del campo</param>
	/// <param name="lRotation">rotazione del campo</param>
	/// <param name="sComment">commento</param>
	/// <param name="pStruct">puntatore alla struttura che contiene i dati del report da stampare</param>
	void AddElementToList(CList<TAG_ELEMENT>& listElements, ENUM_FIELD_TYPE lFieldType, CString sFieldValue, long lLeft, long lRight, long lTop, long lBottom, COLORREF rgbColor, long lCheck, long lParam, CString sFontName, long lFontHeight, long lFontWeight, long lFontUnder, long lFontItalic, long lAlignment, long lRotation, CString sComment, STRUCT_STAMPA* pStruct);

	/// <summary>
	/// Annulla i pdf firmati sostituendoli con un documento (firmato) di sostituzione
	/// </summary>
	/// <param name="lIDEsame">ID dell'esame di cui annullare tutti i pdf</param>
	void AnnullaDocumentiFirmati(long lIDEsame);

	/// <summary>
	/// Stampa le immagini selezionate mostrando, se richiesto, un'anteprima
	/// </summary>
	/// <param name="operazione">definisce se deve essere mostrata un anteprima di stampa o se deve stampare direttamente</param>
	/// <param name="what">definisce se stampare immagini</param>
	/// <param name="lCopies">indica quante copie stampare... se 0 viene richiesto all'utente</param>
	void AnteprimaStampaImmagini(UINT operazione, UINT what, long lCopies);

	/// <summary>
	/// Stampa un report mostrando, se richiesto, un'anteprima
	/// </summary>
	/// <param name="operazione">definisce se deve essere mostrata un anteprima di stampa o se deve stampare direttamente</param>
	/// <param name="bVerificaCampiObbligatori">definisce se bisogna verificare i campi obbligatori</param>
	/// <param name="strReportFile">specifica il nome del file del report, se vuoto </param>
	/// <param name="bFromQueryDlg">indica se il report è il risultato di una query</param>
	/// <param name="lCopieStampa">indica quante copie stampare (ne caso in cui sia prevista la stampa)... se passo 0 e stampo mi chiede il numero di copie</param>
	/// <param name="lGeneratedPdfId">se il metodo crea un pdf, questo parametro verrà valorizzato con l'id del pdf appena generato</param>
	void AnteprimaStampaReport(UINT operazione, BOOL bVerificaCampiObbligatori, CString strReportFile, BOOL bFromQueryDlg, long lCopieStampa, long* lGeneratedPdfId, CString codEsame);

	/// <summary>
	/// Crea il pdf delle immagini selezionate
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite PDF con Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <returns>Il percorso del PDF creato</returns>
	CString CreateHaruPdfImageFile(CString codEsame);
	CString CreateHaruPdfImageFileFromDib(CList<CDib*>* pListImmagini);

	CString CreateHaruPdfCentraleStampaFile(long lIDHeader, long lIDFooter1, long lIDFooter2, CString sReferto);

	/// <summary>
	/// Crea il pdf del report selezionato
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014  | Introduzione stampa tramite PDF con Haru
	/// | Gall   | 05/11/2013 | RAS 20130189 | Possibilità di accodare le immagini al referto
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="pStruct">eventuale parametro passato dall'oggetto</param>
	/// <param name="bAccodaStampaImmagini">indica se accodare alla stampa del referto anche la stampa delle immagini</param>
	/// <returns>Il percorso del PDF creato</returns>
	BOOL CreateHaruPdfReportFile(CString& sOutputFileComplete, STRUCT_STAMPA* pStructStampa, BOOL bAccodaStampaImmagini, CString codEsame);
	void CreateHaruPdfReportFileComplete(CString sOutputFile, STRUCT_STAMPA* pStructStampa, TAG_HEADERFOOTER* pTagHeader1, TAG_HEADERFOOTER* pTagHeader2, TAG_HEADERFOOTER* pTagFooter1, TAG_HEADERFOOTER* pTagFooter2, LOGFONT* pLogFontProduct, LOGFONT* pLogFontComment, LOGFONT* pLogFontPoint, BOOL bAccodaStampaImmagini);

	/// <summary>
	/// Crea il pdf del report selezionato partendo dal risultato di una ricerca
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite PDF con Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="pStruct">eventuale parametro passati dall'oggetto</param>
	/// <returns>Il percorso del PDF creato</returns>
	CString CreateHaruPdfReportFileFromQuery(STRUCT_STAMPA* pStruct);

	/// <summary>
	/// Calcola l'altezza di header o footer
	/// </summary>
	/// <param name="lID">identificativo dell'header o del footer</param>
	/// <returns>l'altezza dell'header o del footer</returns>
	int GetAltezzaHF(long lID);

	/// <summary>
	/// Ritorna un riferimento alla classe CEsamiDoc
	/// </summary>
	/// <returns>riferimento alla classe CEsamiDoc</returns>
	CEsamiDoc* GetDocument();

	/// <summary>
	/// Aggiunge a listElement il valore del campo identificato da tagElement
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento  | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Rizz   | 26/01/2011 | RAS 20110028 | Stampa campo firma operatore refertazione
	/// | Rizz   | 18/04/2011 | RAS 20110101 | Il campo data di validazione deve mostrare la reale data in cui è stato validato l'esame
	/// | Gall   | 14/06/2011 | RIMA 11-014  | Introduzione stampa tramite pdf tramite Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="listElement">riferimento alla lista degli elementi del report attualmente pronti per la stampa</param>
	/// <param name="tagElement">riferimento all'elemento da ricercare</param>
	BOOL GetField(CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid);

	/// <summary>
	///	Parte relativa al paziente di GetField
	/// </summary>
	/// <param name="nFiels">identificativo del campo da stampare</param>
	/// <param name="listElement">riferimento alla lista degli elementi del report attualmente pronti per la stampa</param>
	/// <param name="tagElement">riferimento all'elemento da ricercare</param>
	BOOL GetFieldPaziente(int nField, CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid);

	/// <summary>
	///	Parte relativa all'anamnesi di GetField
	/// </summary>
	/// <param name="nFiels">identificativo del campo da stampare</param>
	/// <param name="listElement">riferimento alla lista degli elementi del report attualmente pronti per la stampa</param>
	/// <param name="tagElement">riferimento all'elemento da ricercare</param>
	BOOL GetFieldAnamnesi(int nField, CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid);

	/// <summary>
	///	Parte relativa ai preliminari di GetField
	/// </summary>
	/// <param name="nFiels">identificativo del campo da stampare</param>
	/// <param name="listElement">riferimento alla lista degli elementi del report attualmente pronti per la stampa</param>
	/// <param name="tagElement">riferimento all'elemento da ricercare</param>
	BOOL GetFieldPreliminari(int nField, CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid);

	/// <summary>
	///	Parte relativa ai testi liberi di GetField
	/// </summary>
	/// <param name="nFiels">identificativo del campo da stampare</param>
	/// <param name="listElement">riferimento alla lista degli elementi del report attualmente pronti per la stampa</param>
	/// <param name="tagElement">riferimento all'elemento da ricercare</param>
	BOOL GetFieldTestiLiberi(int nField, CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid);

	/// <summary>
	///	Parte relativa alle grid checklist di GetField
	/// </summary>
	/// <param name="nFiels">identificativo del campo da stampare</param>
	/// <param name="listElement">riferimento alla lista degli elementi del report attualmente pronti per la stampa</param>
	/// <param name="tagElement">riferimento all'elemento da ricercare</param>
	BOOL GetFieldGridCL(int nField, CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement, BOOL bOnlyIsValid);

	/// <summary>
	/// Restituisce l'identificativo del tipo passato come parametro
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite pdf tramite Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="strTipo">tipo cercato</param>
	/// <returns>identificativo del tipo del campo</returns>
	ENUM_FIELD_TYPE GetFieldType(CString strTipo);

	/// <summary>
	/// Restituisce la struttura dell'header e del footer
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite pdf tramite Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="lID">id di header e footer cercati</param>
	/// <param name="lPaperHeight">altezza del foglio di stampa</param>
	/// <param name="tagReturn">riferimento alla struttura che viene ritornata al chiamante</param>
	void GetHeaderFooter(long lID, long lPaperHeight, TAG_HEADERFOOTER& tagReturn);

	/// <summary>
	/// Restituisce l'orientamento di stampa per il report selezionato
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite pdf tramite Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="sReportFile">percorso del report</param>
	/// <returns>l'orientamento della pagina</returns>
	HPDF_PageDirection GetPageDirection(CString sReportFile);

	/// <summary>
	/// Restituisce il formato richiesto per la stampa del report
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite pdf tramite Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="sReportFile">percorso del report</param>
	/// <returns>il formato di stampa richiesto</returns>
	HPDF_PageSizes GetPageSize(CString sReportFile);

	/// <summary>
	/// Aggiunge tagElement a listElements trasformando la data in esso contenuta
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite pdf tramite Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="listElements">riferimento alla lista degli elementi del report attualmente pronti per la stampa</param>
	/// <param name="tagElement">riferimento all'elemento da aggiungere</param>
	void GetParam(CList<TAG_ELEMENT>& listElements, TAG_ELEMENT& tagElement);

	/// <summary>
	/// Procedura per aggiungere una nuova provetta di anatomia patologica
	/// </summary>
	void InserisciNuovaProvetta();

	/// <summary>
	/// Procedura per aggiungere una nuova riga nella tabella del monitoraggio parametri vitali paziente
	/// </summary>
	void InserisciNuovoMonitoraggio();

	/// <summary>
	/// Esegue il logout dell'utente
	/// </summary>
	/// <returns>il formato di stampa richiesto</returns>
	BOOL Logout(BOOL bMoveEsami);

	/// <summary>
	/// Sposta il recordset degli esami (m_pEsamiSet) nella direzione indicata da nIDMoveCommand
	/// </summary>
	/// <param name="nIDMoveCommand">direzione dello spostamento (ID_RECORD_PREV, ID_RECORD_NEXT, ID_RECORD_FIRST, ID_RECORD_LAST)</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	BOOL MoveEsamiRecordset(UINT nIDMoveCommand);

	/// <summary>
	/// Sposta la visualizzazione sul paziente situato nella posizione indicata da nIDMoveCommand
	/// </summary>
	/// <param name="nIDMoveCommand">direzione dello spostamento (ID_RECORD_PREV, ID_RECORD_NEXT, ID_RECORD_FIRST, ID_RECORD_LAST)</param>
	/// <param name="bMoveEsami">se TRUE, si sposta sull'ultimo esame del paziente (solo se bRefreshSubForm = TRUE)</param>
	/// <param name="bRefreshSubForm">se TRUE, viene fatto un refresh del subform degli esami</param>
	/// <param name="bRefreshNeeded">se TRUE, viene fatto un refresh dell'intera finestra</param>
	void MovePazientiAndEsami(UINT nIDMoveCommand, BOOL bMoveEsami, BOOL bRefreshSubForm);

	/// <summary>
	/// Apre un dialog per il confronto delle immagini di due esami diversi dello stesso paziente
	/// </summary>
	void OnAlbumConfronto();

	/// <summary>
	/// Esegue la ricerca con i filtri impostati
	/// </summary>
	void OnApplicaQuery();

	/// <summary>
	/// Chiude l'esame corrente
	/// </summary>
	/// <returns>L'id del pdf appena generato</returns>
	long OnChiudiEsame();

	/// <summary>
	/// Chiude la fase dell'esame corrente
	/// </summary>
	/// <param name="lIDFase">id della fase</param>
	/// <returns>L'id del pdf appena generato</returns>
	long GeneraPdfFase(long lIDFase);

	/// <summary>
	/// Apre il dialog per la gestione degli allegati all'esame
	/// </summary>
	void OnEsameAllegati();
	void OnEsameAllegatiCarestream();

	/// <summary>
	/// Avvia la procedura di cancellazione di un esame
	/// </summary>
	void OnEsameDelete();

	/// <summary>
	/// Avvia la procedura per lo spostamento al primo esame del paziente corrente
	/// </summary>
	void OnEsameFirst();

	/// <summary>
	/// Avvia la procedura per lo spostamento all'ultimo esame del paziente corrente
	/// </summary>
	void OnEsameLast();

	/// <summary>
	/// Avvia la procedura per il passaggio in modalità "modifica esame"
	/// </summary>
	void OnEsameModify();

	/// <summary>
	/// Avvia la procedura per l'inserimento di un nuovo esame sul paziente corrente
	/// </summary>
	void OnEsameNew();

	/// <summary>
	/// Avvia la procedura per l'inserimento di un nuovo esame (in automatico) sul paziente corrente
	/// </summary>
	void OnEsameNewAuto(long lIDTipoEsame, long lIDPrenotazione);

	/// <summary>
	/// Avvia la procedura per l'inserimento di un nuovo esame (in automatico via CUP) sul paziente corrente
	/// </summary>
	void OnEsameNewAutoCup(long lIDTipoEsame, long lIDPrenotazione);

	/// <summary>
	/// Avvia la procedura per l'inserimento di un nuovo esame (via CUP) sul paziente corrente
	/// </summary>
	void OnEsameNewCup();

	/// <summary>
	/// Avvia la procedura per l'inserimento di un nuovo esame sul paziente corrente
	/// </summary>
	void OnEsameNewEndox();

	/// <summary>
	/// Avvia la procedura per lo spostamento al successivo esame del paziente corrente
	/// </summary>
	void OnEsameNext();

	/// <summary>
	/// Avvia la procedura per lo spostamento al precedente esame del paziente corrente
	/// </summary>
	void OnEsamePrev();

	/// <summary>
	/// Avvia la procedura per il passaggio in modalità "ricerca esame"
	/// </summary>
	void OnEsameQuery();

	/// <summary>
	/// Avvia la procedura che permette di modificare il referto dell'esame corrente
	/// </summary>
	void OnEsameReferto();

	/// <summary>
	/// Avvia la procedura che permette di modificare il referto dell'esame corrente
	/// </summary>
	void OnEsameRefertoGenomica();

	/// <summary>
	/// Invocabile in modalità "modifica esame", avvia la procedura di annullamento delle modifiche effettuate
	/// </summary>
	void OnEsameRefresh();

	/// <summary>
	/// Invocabile in modalità "modifica esame", avvia la procedura di salvataggio delle modifiche apportate all'esame
	/// </summary>
	void OnEsameUpdate();

	/// <summary>
	/// Invocabile in modalità "modifica esame", avvia la procedura di salvataggio delle modifiche apportate all'esame prendendo i dati dal CUP
	/// </summary>
	BOOL OnEsameUpdateCup();

	/// <summary>
	/// Fa parte della procedura di spostamento sull'esame cercato e, in particolare, 
	/// verifica l'esistenza dell'esame stesso e invoca altri metodi per il caricamento dell'interfaccia
	/// </summary>
	/// <param name="nIDMoveCommand">direzione dello spostamento (ID_RECORD_PREV, ID_RECORD_NEXT, ID_RECORD_FIRST, ID_RECORD_LAST)</param>
	/// <param name="bRefreshNeeded">specifica se deve essere fatto un refresh sulla finestra</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	BOOL OnEsamiMove(UINT nIDMoveCommand, BOOL bDeleteSelectedImages = TRUE);

	/// <summary>
	/// Lancia la procedura per la stampa del report
	/// </summary>
	void OnToolbarStampaReport();

	/// <summary>
	/// Lancia la procedura per la firma digitale di un report
	/// </summary>
	void OnToolbarStampaReportFirmaDigitale(CString sReportDaFirmare, long lCopieDaStampare);

	/// <summary>
	/// Lancia la procedura per la stampa dei report contenuti in una macro
	/// </summary>
	void OnToolbarStampaReportMacro();

	/// <summary>
	/// Gestisce lo stato degli oggetti all'interno della finestra, abilitandoli
	/// o meno a seconda dello stato in cui si trova l'applicazione. 
	/// Viene chiamata periodicamente dal sistema.
	/// </summary>
	/// <param name="pCmdUI">identificativo dell'oggetto</param>
	void OnUpdateUI(CCmdUI* pCmdUI);

	/// <summary>
	/// Apre la dialog per il setup della stampante
	/// </summary>
	/// <param name="strTitle">non più utilizzato</param>
	/// <returns>Ritorna TRUE se sono state confermate le modifiche, FALSE se è stato premuto il tasto annulla</returns>
	BOOL PrinterSetup(CString strTitle);

	/// <summary>
	/// Stampa le immagini selezionate
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite pdf tramite Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="lHeaderHeight">altezza dell'header</param>
	/// <param name="lFooterHeight">altezza del footer</param>
	void PrintImages(long lHeaderHeight, long lFooterHeight);
	void PrintImagesFromDibs(CList<CDib*>* pListImmagini);

	/// <summary>
	/// Stampa il report selezionato
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite pdf tramite Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="lHeaderHeight">altezza dell'header</param>
	/// <param name="lFooterHeight">altezza del footer</param>
	/// <param name="pStruct">puntatore alla struttura che contiene i dati del report da stampare</param>
	void PrintReport(long lHeaderHeight, long lFooterHeight, STRUCT_STAMPA* pStruct);

	/// <summary>
	/// Stampa il report selezionato partendo da un risultato di ricerca
	/// --------------------------------------------------------------------------------------
	/// | Autore | Data       | Riferimento | Descrizione
	/// --------------------------------------------------------------------------------------
	/// | Gall   | 14/06/2011 | RIMA 11-014 | Introduzione stampa tramite pdf tramite Haru
	/// --------------------------------------------------------------------------------------	
	/// </summary>
	/// <param name="lHeaderHeight">altezza dell'header</param>
	/// <param name="lFooterHeight">altezza del footer</param>
	/// <param name="pStruct">puntatore alla struttura che contiene i dati del report da stampare</param>
	void PrintReportFromQuery(long lHeaderHeight, long lFooterHeight, STRUCT_STAMPA* pStruct);

	/// <summary>
	/// Aggiorna il software dopo che è stata impostata la nuova UO
	/// </summary>
	void RicaricaDatiDopoCambioUO();

	/// <summary>
	/// Avvia la procedura di ricerca del paziente/esame tramire id dopo che l'utente 
	/// ha già inserito il valore da ricercare (o è già stato individuato dal sistema)
	/// </summary>
	/// <param name="lPaziente">se maggiore di 0, identifica il paziente da ricercare</param>
	/// <param name="lEsame">se maggiore di 0, identifica l'esame da ricercare</param>
	/// <param name="bSafeValue">se TRUE, prima dello spostamento i valori del precedente esame devono essere salvati</param>
	/// <param name="bVerbose">non più utilizzato</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	BOOL RicercaCodicePaziente(long lPaziente, long lEsame, BOOL bSafeValue, BOOL bVerbose);

	/// <summary>
	/// Avvia la procedura di ricerca del paziente tramire AssIden dopo che l'utente ha inserito il valore da ricercare
	/// </summary>
	/// <param name="sAssiden">identifica il paziente da ricercare</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	BOOL RicercaCodicePazienteAssiden(CString sAssiden);

	/// <summary>
	/// Avvia la procedura di ricerca del paziente/esame tramire codice esame dopo che l'utente ha inserito il valore da ricercare
	/// </summary>
	/// <param name="sCodesame">identifica l'esame da ricercare</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	long RicercaCodicePazienteCodEsameEx(CString sCodEsame);

	/// <summary>
	/// Avvia la procedura di ricerca del paziente tramire CodiceRicovero dopo che l'utente ha inserito il valore da ricercare
	/// </summary>
	/// <param name="sCodiceRicovero">identifica il paziente da ricercare</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	BOOL RicercaCodicePazienteCodiceRicovero(CString sCodiceRicovero, BOOL bShowError = TRUE);

	/// <summary>
	/// Richiama gli UpdateData di tutti i subform 
	/// </summary>
	/// <param name="bSaveAndValidate">se TRUE, copia i dati dell'interfaccia nelle variabili, se FALSE fa il viceversa</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	BOOL UpdateData(BOOL bSaveAndValidate = TRUE);

	/// <summary>
	/// Verifica se tutti i campi obbligatori sono stati compilati correttamente
	/// </summary>
	/// <returns>TRUE se tutti i campi obbligatori sono stati compilati correttamente, FALSE altrimenti</returns>
	//BOOL VerificaCampiObbligatori(long lFase);

	/// <summary>
	/// Verifica se tutti i campi obbligatori della fase sono stati compilati correttamente
	/// </summary>
	/// <returns>TRUE se tutti i campi obbligatori sono stati compilati correttamente, FALSE altrimenti</returns>
	BOOL VerificaCampiObbligatoriFase(long lIDFase);

	/// <summary>
	/// Chiude il monitoraggio in corso e pulisce le variabili globali
	/// </summary>
	void ChiudiMonitoraggioInCorso();

	/// <summary>
	/// Avvia una sessione di monitoraggio del dispositivo
	/// </summary>
	/// <param name="idDispositivo">identificativo del dispositivo utilizzato</param>
	/// <param name="idSessione">parametro che sarà valorizzato con id sessione restituito</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	BOOL AvviaSessioneMonitoraggio(int idDispositivo, CString *pIdSessione, MonitoringPhase fase);
	
	/// <summary>
	/// Chiude la sessione di monitoraggio in corso
	/// </summary>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	BOOL ChiudiSessioneMonitoraggioInCorso();

	/// <summary>
	/// Verifica lo stato di una fase
	/// </summary>
	/// <param name="lIDFase">identificativo della fase</param>
	/// <returns>TRUE se la fase è chiusa</returns>
	BOOL IsFaseChiusa(long lIDFase);

	/// <summary>
	/// Ricarica i dati dell'esame per abilitare o meno i campi dell'interfaccia
	/// </summary>
	void RicaricaDatiAssociatiAllEsame();

	/// <summary>
	/// Chiude la fase per l'esame attualmente visualizzato
	/// </summary>
	/// <param name="lIDFase">identificativo della fase</param>
	void ChiudiFase(long lIDFase);

	/// <summary>
	/// Chiude la fase di convalida per l'esame attualmente visualizzato
	/// </summary>
	void ConvalidaEsame();

	/// <summary>
	/// Chiude la fase di chiusura per l'esame attualmente visualizzato
	/// </summary>
	void ChiudiEsame();

	// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
	/// <summary>
	/// Fecha fase para liberar laudo no sistema Fleury
	/// </summary>
	void LiberaLaudo();
	/// <summary>
	/// Verifica se Exame é principal
	/// </summary>
	BOOL RefertoPrincipale(long lContatore);
	/// <summary>
	/// Verifica se Exame é principal ou secundário
	/// </summary>
	BOOL RefertoPrincipaleSecondario(long lContatore);

	/// <summary>
	/// Chiede il login e verifica che l'utente abbia diritti su uo e fase attuali
	/// </summary>
	/// <param name="lIDFase">id della fase</param>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	BOOL ChiudiFase_CambioUtente(long lIDFase);

	/// <summary>
	/// Attributo che determina se l'esame è in fase di modifica
	/// </summary>
	BOOL m_bEsamiBusy;

	/// <summary>
	/// Attributo che verifica se stiamo visualizzando un esame valido
	/// </summary>
	BOOL m_bEsamiIsNull;

	/// <summary>
	/// Attributo per la gestione del pulsante "modifica esame"
	/// </summary>
	BOOL m_bEsamiModify;

	/// <summary>
	/// Attributo per la gestione del tasto "esame successivo"
	/// </summary>
	BOOL m_bEsamiNext;

	/// <summary>
	/// Attributo per la gestione del tasto "esame precedente"
	/// </summary>
	BOOL m_bEsamiPrev;

	/// <summary>
	/// Attributo per la verifica se l'esame attualmente visualizzato è valido
	/// </summary>
	BOOL m_bEsamiValid;

	/// <summary>
	/// Attributo per la gestione del filtro per la ricerca
	/// </summary>
	BOOL m_bFilterBusy;

	/// <summary>
	/// Attributo che determina se il paziente è in fase di modifica
	/// </summary>
	BOOL m_bPazientiBusy;

	/// <summary>
	/// Attributo che determina se si sta visualizzando un paziente valido
	/// </summary>
	BOOL m_bPazientiIsNull;

	/// <summary>
	/// Attributo per la gestione del pulsante "modifica paziente"
	/// </summary>
	BOOL m_bPazientiModify;

	/// <summary>
	/// Attributo per la gestione del tasto "paziente successivo"
	/// </summary>
	BOOL m_bPazientiNext;

	/// <summary>
	/// Attributo per la gestione del tasto "paziente precedente"
	/// </summary>
	BOOL m_bPazientiPrev;

	/// <summary>
	/// Attributo che determina se si sta visualizzando un paziente valido
	/// </summary>
	BOOL m_bPazientiValid;

	// Sandro 14/12/2015 // RIMA 15135 //
	BOOL m_bVisualizzaTastoCaricaImmagini;

	/// <summary>
	/// Servono per nascondere l'album delle immagini
	/// </summary>
	CButtonLocalize m_ctrlBtnHide;

	/// <summary>
	/// Servono per scoprire l'album delle immagini
	/// </summary>
	CButtonLocalize m_ctrlBtnShow;

	//
	CButtonLocalize m_ctrlBtnImmagini;

	//
	CButtonLocalize m_ctrlBtnStopMonitoraggio;

	/// <summary>
	/// I seguenti attributi servono per gestire gli elementi della form
	/// </summary>
	CEndoxTabCtrl m_ctrlGruppoEsame;
	CStatic m_ctrlSubForm3;
	CStatic m_ctrlSubFormAlbum;
	CStatic m_ctrlSubFormEsame;

	/// <summary>
	/// Handle alle impostazioni di stampa
	/// </summary>
	HANDLE m_hDevMode;

	/// <summary>
	/// Handle alle impostazioni di stampa
	/// </summary>
	HANDLE m_hDevNames;

	/// <summary>
	/// Mantiene in memoria l'ID della prenotazione associata all'esame corrente
	/// </summary>
	long m_lIDPrenotazione;

	/// <summary>
	/// Specifica il tipo di esame che deve essere inserito automaticamente
	/// </summary>
	long m_lIDTipoEsameAutoInsert;

	/// <summary>
	/// Contiene il numero di immagini selezionate
	/// </summary>
	long m_lLocalImagesSelected;

	/// <summary>
	/// Contiene il numero di TIFF multipagina selezionati
	/// </summary>
	long m_lLocalMultiPageTiffSelected;

	/// <summary>
	/// Contiene il numero di documenti allegati al paziente
	/// </summary>
	long m_lNumDocumentsPatient;
	long m_lNumDocumentsPatientOffset;

	/// <summary>
	/// Contiene il numero di documenti allegati all'esame
	/// </summary>
	long m_lNumDocumentsExam;
	long m_lNumDocumentsExamOffset;

	/// <summary>
	/// Contiene il numero di documenti allegati all'esame da inviare a Carestream
	/// </summary>
	long m_lNumDocumentsExamCarestream;
	long m_lNumDocumentsExamCarestreamOffset;

	/// <summary>
	/// Recordset contenente tutti i pazienti di Endox
	/// </summary>
	CPazientiSet m_PazTempSet;

	/// <summary>
	/// Puntatore al gestore dei documenti allegati
	/// </summary>
	CMyDocManager* m_pDocManager;

	/// <summary>
	/// Array di puntatori ai controlli inseribili in interfaccia utente
	/// </summary>
	CEndoxDynForm* m_pDynForm[form_list_total];

	/// <summary>
	/// Puntatore al recordset relativo agli esami
	/// </summary>
	CEsamiSet* m_pEsamiSet;

	/// <summary>
	/// Ponteiro para Exame Integrado - Conjugação N x N
	/// </summary>
	CEsamiIntegratiSet* m_pEsamiIntegratiSet;

	/// <summary>
	/// Puntatore all'album delle immagini
	/// </summary>
	CAlbumForm* m_pFormImmagini;
	
	//Gabriel BUG 6225 - Lista DO
	/// <summary>
	/// Puntatore all'dialog di detaglio delle immagini
	/// </summary>
	CImageDlg* m_pImageDlg;

	/// <summary>
	/// Puntatore al gestore delle immagini
	/// </summary>
	CImgManager* m_pImgManager;

	/// <summary>
	/// Puntatore al recordset relativo ai pazienti
	/// </summary>
	CPazientiSet* m_pPazientiSet;

	/// <summary>
	/// Puntatore alla finestra dei risultati della ricerca
	/// </summary>
	CQueryDlg* m_pQueryDlg;

	/// <summary>
	/// Puntatore alla finestra di export immagini
	/// </summary>
	CExportDlg* m_pWndExport;

	/// <summary>
	/// Codice fiscale da cercare nell'anagrafica centralizzata
	/// </summary>
	CString m_sCodiceFiscaleRicercaAnagCen;

	/// <summary>
	/// Cognome da cercare nell'anagrafica centralizzata
	/// </summary>
	CString m_sCognomeRicercaAnagCen;

	/// <summary>
	/// Data di nascita da cercare nell'anagrafica centralizzata
	/// </summary>
	CString m_sDataNascitaRicercaCen;

	/// <summary>
	/// Ora di chiusura esame
	/// </summary>
	CString m_sDataOraChiusura;

	/// <summary>
	/// Ora di convalida
	/// </summary>
	CString m_sDataOraConvalida;

	/// <summary>
	/// Recordset che contiene i dati per legare i punti alle immagini
	/// </summary>
	// CImmaginiPuntiSet m_setImmaginiPunti;

	/// <summary>
	/// Recordset contenente i punti delle immagini
	/// </summary>
	// CPuntiSet m_setPunti;

	/// <summary>
	/// Nome da cercare nell'anagrafica centralizzata
	/// </summary>
	CString m_sNomeRicercaAnagCen;

	/// <summary>
	/// Sesso da cercare nell'anagrafica centralizzata
	/// </summary>
	CString m_sSessoRicercaAnagCen;

	///
	BOOL m_bBurning;
	BOOL m_bImporting;
	BOOL m_bPrinting;
	BOOL m_bRimage;

	/// <summary>
	/// Simone 01/12/2015
	/// Flag che indica lo stato del monitoraggio
	/// </summary>
	BOOL m_bMonitoraggioAttivo;

	/// <summary>
	/// Recharge data from database
	/// </summary>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL EsameRefreshSoft();

	/// <summary>
	/// after detected that referto was updated by another user in concurrent context, refreshes and format a msg to show it
	/// </summary>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	void FormatMsgGotRefertoRefreshWithUpdate(BOOL p_bFillMessage);

	//Gabriel BUG 6303
	/// <summary>
	/// retorna a sigla do exame da ExtPrestazioni
	/// </summary>
	/// <returns></returns>
	CString GetSiglaPrestazione();

	//Gabriel BUG 6225 - Lista DO
	/// <summary>
	/// retorna a sigla do exame da ExtPrestazioni
	/// </summary>
	/// <returns></returns>
	void RefreshNumDocumentsExam();

	//Gabriel BUG 6225 - Lista DO
	/// <summary>
	/// verifica se o exame foi reconvocado
	/// </summary>
	/// <returns></returns>
	BOOL BloccaEsameRiconvocazione();

	//Gabriel - P3
	/// <summary>
	/// Importa a receita automaticamente, caso não tenha sido importada
	/// </summary>
	/// <returns></returns>
	void OnEsameAllegatiCentralizzazione();
protected:

	/// <summary>
	/// Effettua lo scambio dati tra l'interfaccia e gli attributi della classe
	/// </summary>
	/// <param name="pDX">oggetto utilizzato per il recupero dei riferimenti dall'interfaccia</param>
	virtual void DoDataExchange(CDataExchange* pDX);

	/// <summary>
	/// Metodo che intercetta la pressione di un pulsante del menu
	/// </summary>
	void OnCommand(UINT nID);

	/// <summary>
	/// I metodi del gruppo seguente sono invocati alla pressione dei pulsanti del menu, ed ognuno di questi avvia una determinata procedura
	/// </summary>
	void OnCommandFileAnteprimaPDF();
	void OnCommandFileChangePassword();
	void OnCommandFileGestioneUtenti();
	void OnCommandFileAssociazioneUtentiUnitaOperative();
	void OnCommandFileCambioUO();
	void OnCommandFileCambioPasswordEliminazionePdf();
	void OnCommandFileInquiero1();
	void OnCommandFileInquiero2();
	void OnCommandFileLogout();
	void OnCommandFileSpostaEsame();
	void OnCommandFileStampaPDF();
	void OnCommandInfoUser();	
	void OnCommandMenuArchiviAccessori();
	void OnCommandMenuArchiviAltreAnomalie();
	void OnCommandMenuArchiviAltreTabelle();
	void OnCommandMenuArchiviAssociazioniICD9();

	//Julio BUG 3249
	void OnCommandMenuArchiviPatogenicita();
	void OnCommandMenuArchiviTipiVariantiGenetiche();
	void OnCommandMenuArchiviTipiAlterazioni();
	void OnCommandMenuArchiviVariantiGenetiche();
	void OnCommandMenuArchiviSezioniReferto();
	void OnCommandMenuArchivTipiReferto();
	void OnCommandMenuArchiviCorpoReferto();
	void OnCommandMenuArchiviTipiMateriali();
	void OnCommandMenuArchiviFrasiRisultato();
	//

	void OnCommandMenuArchiviBackup();
	void OnCommandMenuArchiviBackupDati();
	void OnCommandMenuArchiviBackupDatiDoppiaCopia();
	void OnCommandMenuArchiviCauseNonCompletamento();
	void OnCommandMenuArchiviCentriDiCosto();
	void OnCommandMenuArchiviCheckList();
	void OnCommandMenuArchiviCodificaRegionale();
	void OnCommandMenuArchiviComplicanzeImmediate();
	void OnCommandMenuArchiviComplicanzeTardive();
	void OnCommandMenuArchiviConclusioniColon();
	void OnCommandMenuArchiviConclusioniScreening();
	void OnCommandMenuArchiviDiagnosiFinale();
	void OnCommandMenuArchiviDiagnosiICD9();
	void OnCommandMenuArchiviDosiMonitoraggio();
	void OnCommandMenuArchiviEjectVolume();
	void OnCommandMenuArchiviEsami();
	void OnCommandMenuEsamiFasi();
	void OnCommandMenuArchiviEsenzioneRicetta();
	void OnCommandMenuArchiviEtichette();
	void OnCommandMenuArchiviEtichetteAnamnesi();
	void OnCommandMenuArchiviFarmaciMonitoraggio();
	void OnCommandMenuArchiviFarmaciPazientiCronici();
	void OnCommandMenuArchiviFrasiPostEsame();
	void OnCommandMenuArchiviFrasiRTF();
	void OnCommandMenuArchiviFrasiStandard();
	void OnCommandMenuArchiviGruppiDiagnosiICD9();
	void OnCommandMenuArchiviTipiPrelievi();
	void OnCommandMenuArchiviProcedurePrelievi();
	void OnCommandMenuArchiviGruppiPrelievi();
	void OnCommandMenuArchiviGruppiPrestazioni();
	void OnCommandMenuArchiviGruppiPrestazioniRicetta();
	void OnCommandMenuArchiviGruppiProcedureICD9();
	void OnCommandMenuArchiviImportaCaso();
	void OnCommandMenuArchiviEsameIntegrato();
	void OnCommandMenuArchiviParametriTabellaEcocardiografia();
	void OnCommandMenuArchiviCommentiImmagini();
	void OnCommandMenuArchiviInfermieri();
	void OnCommandMenuArchiviIntegrazioni();
	void OnCommandMenuArchiviInviantiExt();
	void OnCommandMenuArchiviInviantiInt();
	void OnCommandMenuArchiviMacroDiStampa();
	void OnCommandMenuArchiviMalattieCroniche();
	void OnCommandMenuArchiviMedici();
	void OnCommandMenuArchiviMediciCuranti();
	void OnCommandMenuArchiviMediciInvianti();
	void OnCommandMenuArchiviMstCodificaDiagnosiEsame();
	void OnCommandMenuArchiviMstComplicanze1();
	void OnCommandMenuArchiviMstComplicanze2();
	void OnCommandMenuArchiviMstComplicanze3();
	void OnCommandMenuArchiviMstDiagnosi();
	void OnCommandMenuArchiviMstIndicazioni();
	void OnCommandMenuArchiviMstOsservazioni();
	void OnCommandMenuArchiviMstProcDiagnostiche();
	void OnCommandMenuArchiviMstProcTerapeutiche();
	void OnCommandMenuArchiviOccupazioneGiornaliera();
	void OnCommandMenuArchiviOrganiSedi();
	void OnCommandMenuArchiviProcedureICD9();
	void OnCommandMenuArchiviProntuarioFarmaceutico();
	void OnCommandMenuArchiviProntuarioFarmaceuticoRicetta();
	void OnCommandMenuArchiviPulizia();
	void OnCommandMenuArchiviRAO();
	void OnCommandMenuArchiviRepAspettoMacro();
	void OnCommandMenuArchiviRepGradoDisplasia();
	void OnCommandMenuArchiviRepIstologia();
	void OnCommandMenuArchiviRepNotizieTerapia();
	void OnCommandMenuArchiviReportsDefault();
	void OnCommandMenuArchiviRepRegione();
	void OnCommandMenuArchiviRepTecnica();
	void OnCommandMenuArchiviRepTipoLesione();
	void OnCommandMenuArchiviRepTrattamento();
	void OnCommandMenuArchiviSalvaValoriDefault();
	void OnCommandMenuArchiviStorePacsImage();
	void OnCommandMenuArchiviStrumenti();
	void OnCommandMenuArchiviStudi();
	void OnCommandMenuArchiviTolleranza();
	void OnCommandMenuArchiviTrasferimParziale();
	void OnCommandMenuArchiviTrasferimTotale();	
	void OnCommandMenuConnessioneRemota();
	void OnCommandMenuFileAnteprimaImmagini();
	void OnCommandMenuFileAnteprimaReport();
	void OnCommandMenuFileImpostaPagina();
	void OnCommandMenuFileIntestazioneReferto();
	void OnCommandMenuFileSelTwain();
	void OnCommandMenuFileStampaEtichette();
	void OnCommandMenuFileStampaImmagini();
	void OnCommandMenuFileStampaReport();
	void OnCommandMenuGestioneConfigStatistiche();
	void OnCommandMenuGestioneEsamiPendenti();
	void OnCommandMenuGestioneNomenclatore();
	void OnCommandMenuGestioneSospesiIstologici();
	void OnCommandMenuGestioneStatistiche();
	void OnCommandMenuGestioneStatisticheEsami();
	BOOL OnCommandMenuGestioneVisualizzaStampe(BOOL bShowErrors);
	void OnCommandMenuGestioneVisualizzatoreLog();
	void OnCommandMenuGestioneLogSintetico();
	void OnCommandMenuGestioneVisualizzatoreLogImportazioneCasi();
	void OnCommandMenuGestioneLogIntegrazioni();
	void OnCommandMenuGestioneInviaVideo();
	void OnCommandMenuGestioneAccessoSediEsterne();
	void OnCommandMenuGestioneItensFicha();// Julio 09/02/2018
	void OnCommandMenuGestioneDesconjugarItens();// Julio 02/03/2018
	void OnCommandMenuGestionePersonificacao(); // Julio 22/10/2018
	void OnCommandMenuGestioneFlussoDiStato(); //Gabriel BUG 6225 - Lista DO
	void OnCommandMenuOpzioniAcquisizione();
	void OnCommandMenuOpzioniCalib();
	void OnCommandMenuOpzioniCampiObbligatori();
	void OnCommandMenuOpzioniDisattivaFirmaPerQuestoEsame();
	void OnCommandMenuOpzioniSetupDatabasesRemoti();
	void OnCommandMenuOpzioniDisegnaOperator();
	void OnCommandMenuOpzioniDisegnaReport();
	void OnCommandMenuOpzioniInterfacciaWEB();
	void OnCommandMenuOpzioniOrgani();
	void OnCommandMenuOpzioniSetup();
	void OnCommandMenuVariDiagnosiIstologica();
	void OnCommandMenuVariBostonScore();
	void OnCommandMenuVariCodiciClassificazioneDiagnostica();
	void OnCommandMenuVariProtocolli();
	void OnCommandMenuVariMedidasBiometricas(); //Julio 01/02/2019
	void OnCommandMenuVariSchemiAnatomiciRecord(); // Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	void OnCommandMenuVariSchemiAnatomiciAdd(); // Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	void OnCommandMenuVariSchemiAnatomiciEdit(); // Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	void OnCommandMenuVariFoglioRiferimento(); //Gabriel BUG 6225 - Lista DO
	void OnCommandMenuVariCalcoloMedidasBiometricas(); //Gabriel - BUG 5533 V2 - Cálculos medidas biométricas
	void OnCommandMenuVariRegoleMedidasBiometricas(); //Gabriel - BUG 5533 V2 - Regras medidas biométricas
	void OnCommandMenuEsameCorrenteReconvocazione(); //Gabriel BUG 6225 - Lista DO
	void OnCommandOptionPrinters();
	void OnCommandSetupDbase();
	void OnCommandSetupColori();
	void OnCommandMenuRoutingAudio();
	void OnCommandMenuRoutingVideo();
	void OnCommandMenuAttivazioneUtenti();
	void OnCommandChiudiFase(long lIDFase);
	void OnCommandAnnullaChiudiFase(long lIDFase);
	
	// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
	BOOL ExameSecundario(long lExam);
	CString ComboSelecionaMotivo();
	void AnulaFaseEConjugados(long lIDFase);
	void OnCommandAtualizaMedicoSolicitante();// Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico e Paciente - Inclui Médicos solicitantes

	BOOL FechaProtocoloXXI(CString sRicovero, CString sCodEsame);//Gabriel - P3

	/// <summary>
	/// Effettua lo scambio dati tra l'interfaccia e gli attributi della classe
	/// </summary>
	/// <param name="pDC">puntatore al contesto di dispositivo dello schermo</param>
	virtual void OnDraw(CDC* pDC);

	/// <summary>
	/// Metodo richiamato dal sistema nel momento in cui viene inizializzata la dialog
	/// </summary>
	virtual void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()	

	void UpdateModalityWorklistSCP();

private:

	CTXTextControl23Ex m_ctrlTextControlView;

	/// <summary>
	/// Svuota i campi relativi all'esame
	/// </summary>
	void AnnullaCampiEsame();

	/// <summary>
	/// Svuota i campi relativi al paziente
	/// </summary>
	void AnnullaCampiPaziente();

	/// <summary>
	/// Salva il PDF nell'archivio
	/// </summary>
	/// <returns>l'ID del PDF appena aggiunto</returns>
	long ArchiviaPdf(pdftype pdfType, CString* pStrPdfFileComplete, CString sNote, BOOL bFirma, BOOL bSaltaFirma, BOOL bFitToPage, long lVersioneReferto, long lIDPdfCheSostituisce);

	/// <summary>
	/// Valorizza i puntatori ai recordset principali
	/// </summary>
	void AssociaRecordset();

	/// <summary>
	/// Copia i valori di default sull'esame attuale
	/// </summary>
	void CaricaCampiDefault();

	/// <summary>
	/// Recupera le parti anatomiche da associare alle immagini contenute in pStruct
	/// </summary>
	/// <param name="pStruct">struttura contenente i dati del report</param>
	/// <returns>sempre 0</returns>
	long CaricaImmaginiPunti(STRUCT_STAMPA* pStruct);

	/// <summary>
	/// Carica l'interfaccia relativa alla versione passata
	/// </summary>
	/// <param name="lVersione">id versione</param>
	void CaricaInterfaccia(long lVersione);

	/// <summary>
	/// Copia tutti i dati presenti in interfaccia sul nuovo esame
	/// </summary>
	void CloneForm(long lContatoreOrigine);

	/// <summary>
	/// Prepara filtro da applicare ai pazienti per la ricerca
	/// </summary>
	/// <param name="strFilter">filtro OUT</param>
	void ComposeFilter(CString& strFilter);

	/// <summary>
	/// Conta le immagini che possono essere contenute nel report
	/// </summary>
	/// <param name="strFileReport">percorso del report</param>
	/// <returns>il numero di immagini che possono essere contenute nel report</returns>
	long ContaImmagini(CString strFileReport);

	/// <summary>
	/// Conta le immagini degli organi che possono essere contenute nel report
	/// </summary>
	/// <param name="strFileReport">percorso del report</param>
	/// <returns>il numero di immagini degli organi che possono essere contenute nel report</returns>
	long ContaOrgani(CString strFileReport);

	/// <summary>
	/// Crea copia di un'area di memoria
	/// </summary>
	/// <param name="h">handle origine</param> 
	/// <returns>nuovo handle</returns>
	HANDLE CopyHandle(HANDLE h);

	/// <summary>
	/// Elimina tutti gli esami del paziente attuale
	/// </summary>
	void DeleteEsamiEndox();

	/// <summary>
	/// Mette il programma in stato di modifica esame
	/// </summary>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL EsameModify(); 

	/// <summary>
	/// Aggiunge un nuovo esame al paziente attuale
	/// </summary>
	/// <param name="lTipoEsame">tipologia esame</param>
	/// <param name="lIDVersione">versione maschera</param>
	void EsameNew(long lTipoEsame, long lIDVersione);

	/// <summary>
	/// Annulla lo stato di modifica dell'esame
	/// </summary>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL EsameRefresh();

	/// <summary>
	/// Salva l'esame attuale
	/// </summary>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL EsameUpdateClassic();

	/// <summary>
	/// Salva la modifica dell'esame
	/// </summary>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL EsameUpdateDefault();

	/// <summary>
	/// Segna in giallo i titoli dei campi obbligatori
	/// </summary>
	//void EvidenziaCampiObbligatori();

	/// <summary>
	/// Segna i titoli dei campi obbligatori new
	/// </summary>
	void EvidenziaCampiObbligatoriFasi();

	/// <summary>
	/// Allinea il recordset esami relativo al paziente corrente
	/// </summary>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL FiltraEsami();

	/// <summary>
	/// Restituisce l'indice dell'organo da stampare
	/// </summary>
	/// <param name="nCurOrgan">numero organo</param>
	/// <param name="listPunti">lista punti</param>
	/// <returns>indice organo</returns>
	long GetOrganIndex(int nCurOrgan, CList <tagPunti> &listPunti);

	/// <summary>
	/// Carica le toolbar della schermata principale
	/// </summary>
	void InitToolbar();

	/// <summary>
	/// Aggiunge un nuovo esame al paziente attuale
	/// </summary>
	/// <param name="lTipoEsame">tipologia esame</param>
	void InsertNewEsame(long lTipoEsame);

	/// <summary>
	/// Leggi informazioni relative ad un campo del report
	/// salvata nel report
	/// </summary>
	/// <param name="strFileReport">file report</param>
	/// <param name="strSezione">nome campo</param>
	/// <param name="strEtichetta">contenuto campo OUT</param>
	/// <param name="rectInMm">dimensione OUT</param>
	/// <param name="bCheck">parametro check associato OUT</param>
	/// <param name="rgbColor">colore OUT</param>
	/// <param name="nParam">parametro generico OUT</param>
	/// <param name="nAlignment">allineamento OUT</param>
	/// <param name="nRotation">rotazione OUT</param>
	/// <param name="lfPrinterFont">font stampa OUT</param>
	void LeggiCampo(const CString &strFileReport, const CString &strSezione, CString &strEtichetta, CRect &rectInMm, BOOL &bCheck, COLORREF &rgbColor, int &nParam, int &nAlignment, int &nRotation, LOGFONT &lfPrinterFont);

	/// <summary>
	/// Carica le etichette dei campi personalizzabili
	/// </summary>
	void LeggiEtichette();

	/// <summary>
	/// Carica tutte le form relative all'esame attuale
	/// </summary>
	void LoadForm();

	/// <summary>
	/// Gestione movimenti su recordset pazienti
	/// </summary>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL MovePazientiRecordset(UINT nIDMoveCommand);

	/// <summary>
	/// Gestione movimenti su recordset pazienti / esami
	/// </summary>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL MoveRecord(UINT nIDMoveCommand);

	/// <summary>
	/// Nasconde i menù non necessari richiamando le funzioni seguenti
	/// </summary>
	void NascondiMenuEndox();

	/// <summary>
	/// Nasconde i menù non necessari dalla voce Archivi
	/// </summary>
	void NascondiMenuEndoxArchivi(CMenu* pMenu);

	/// <summary>
	/// Nasconde i menù non necessari dalla voce File
	/// </summary>
	void NascondiMenuEndoxFile(CMenu* pMenu);

	/// <summary>
	/// Nasconde i menù non necessari dalla voce Gestione
	/// </summary>
	void NascondiMenuEndoxGestione(CMenu* pMenu);

	/// <summary>
	/// Nasconde i menù non necessari dalla voce Opzioni
	/// </summary>
	void NascondiMenuEndoxOpzioni(CMenu* pMenu);

	/// <summary>
	/// Nasconde i menù non necessari richiamando le funzioni seguenti
	/// </summary>
	void NascondiMenuImageNT();

	/// <summary>
	/// Nasconde i menù non necessari dalla voce Archivi
	/// </summary>
	void NascondiMenuImageNTArchivi(CMenu* pMenu);

	/// <summary>
	/// Nasconde i menù non necessari dalla voce File
	/// </summary>
	void NascondiMenuImageNTFile(CMenu* pMenu);

	/// <summary>
	/// Nasconde i menù non necessari dalla voce Gestione
	/// </summary>
	void NascondiMenuImageNTGestione(CMenu* pMenu);

	/// <summary>
	/// Nasconde i menù non necessari dalla voce Opzioni
	/// </summary>
	void NascondiMenuImageNTOpzioni(CMenu* pMenu);

	/// <summary>
	/// Elimina separatori menù doppi
	/// </summary>
	void NascondiSeparatori(CMenu* pMenu);

	/// <summary>
	/// Collegato al tasto album generale
	/// </summary>
	void OnAlbum();

	/// <summary>
	/// Tasto nascondi album immagini
	/// </summary>
	void OnBnClickedBtnHide();

	/// <summary>
	/// Tasto mostra album immagini
	/// </summary>
	void OnBnClickedBtnShow();

	//
	void OnBnClickedBtnImmagini();

	/// <summary>
	/// Riepilogo dati paziente
	/// </summary>
    void OnBnClickedDatiPaziente();

	/// <summary>
	/// Lancia l'esecuzione di un programma esterno
	/// </summary>
	void OnBtnComando();

	/// <summary>
	/// Apre la finestra delle conclusioni del paziente
	/// </summary>
	void OnBtnConclusioni();

	///
	void OnBtnPazienteCronico();

	/// <summary>
	/// Apre il dettaglio delle allergie paziente
	/// </summary>
	void OnClickIconAllergie();

	/// <summary>
	/// Apre il dettaglio delle segnalazioni sul paziente
	/// </summary>
	void OnClickIconSegnalato();

	/// <summary>
	/// Gestione dei colori dei controlli
	/// </summary>
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	/// <summary>
	/// Si occupa di distruggere la finestra di ricerca
	/// </summary>
	LRESULT OnDestroyQueryWnd(WPARAM, LPARAM);

	/// <summary>
	/// Si occupa di distruggere la finestra dei sospesi istologici
	/// </summary>
	LRESULT OnDestroySospesiIstologiciWnd(WPARAM, LPARAM);

	/// <summary>
	/// Nasconde la finestra di ricerca
	/// </summary>
	LRESULT OnHideQueryWnd(WPARAM, LPARAM);

	/// <summary>
	/// Nasconde la finestra dei sospesi istologici
	/// </summary>
	LRESULT OnHideSospesiIstologiciWnd(WPARAM, LPARAM);

	/// <summary>
	/// Chiude e riapre la finestra di ricerca
	/// </summary>
	LRESULT OnReloadQueryWnd(WPARAM, LPARAM);

	// Sandro 17/07/2017 //
	static UINT CopyImagesFromRemotePath(LPVOID pParam);

	/// <summary>
	/// Aggiorna la barra di avanzamento del thread di import
	/// </summary>
	LRESULT OnThreadImportSetPos(WPARAM wParam, LPARAM lParam);

	/// <summary>
	/// Aggiorna la barra di avanzamento del thread Rimage
	/// </summary>
	LRESULT OnThreadRimageSetPos(WPARAM wParam, LPARAM lParam);

	/// <summary>
	/// Aggiorna lo stato del thread Rimage
	/// </summary>
	LRESULT OnThreadRimageOn(WPARAM wParam, LPARAM lParam);

	/// <summary>
	/// Aggiorna lo stato del thread Rimage
	/// </summary>
	LRESULT OnThreadRimageOff(WPARAM wParam, LPARAM lParam);

	/// <summary>
	/// Avvia il monitoraggio
	/// </summary>
	LRESULT OnThreadStartMonitoraggio(WPARAM wParam, LPARAM lParam);

	/// <summary>
	/// Apre la lista delle prenotazioni
	/// </summary>
	void OnListaPrenotazioni();

	/// <summary>
	/// Apre la finestra degli allegati al paziente
	/// </summary>
	void OnPazienteAllegati();

	//
	void OnFleuryFicha();
	void OnFleuryFicha2();

	void OnFleuryAssessoria();

	//Julio 09/02/2018
	void OnFleuryCentralizacao(CString sFicha, BOOL bAskBefore = TRUE);

	/// <summary>
	/// Associato al tasto per eliminare il paziente attuale
	/// </summary>
	void OnPazienteDelete();

	/// <summary>
	/// Si sposta al primo paziente
	/// </summary>
	void OnPazienteFirst();

	/// <summary>
	/// Chiede l'ID del paziente su cui spostarsi
	/// </summary>
	void OnPazienteGoto();

	/// <summary>
	/// Si sposta all'ultimo paziente
	/// </summary>
	void OnPazienteLast();

	/// <summary>
	/// Modifica paziente attuale
	/// </summary>
	void OnPazienteModify();

	/// <summary>
	/// Inserisce un nuovo paziente
	/// </summary>
	void OnPazienteNew();

	/// <summary>
	/// Si sposta al paziente successivo
	/// </summary>
	void OnPazienteNext();

	/// <summary>
	/// Si sposta al paziente precedente
	/// </summary>
	void OnPazientePrev();

	/// <summary>
	/// Attiva la modalità di ricerca
	/// </summary>
	void OnPazienteQuery();

	/// <summary>
	/// Annulla le modifica al dati del paziente
	/// </summary>
	void OnPazienteRefresh();

	/// <summary>
	/// Salva le modifiche ai dati del paziente
	/// </summary>
	void OnPazienteUpdate();

	/// <summary>
	/// Salva le modifiche ai dati del paziente
	/// </summary>
	void OnPazienteUpdateEndox();

	/// <summary>
	/// Apre Agenda per l'inserimento di una nuova prenotazione
	/// </summary>
	void OnPrenotazione();

	/// <summary>
	/// Esegue il resize dei controlli contenuti nella finestra principale
	/// </summary>
	void OnSize(UINT nType, int cx, int cy);

	/// <summary>
	/// Esegue ping dei server e salva il risultaqto su un file di log
	/// </summary>
	void OnTimer(UINT nIDEvent);

	/// <summary>
	/// Stampa le immagini dentro al PDF in fase di creazione
	/// </summary>
	void PrintImageOnPdf(IMAGE_TO_PRINT* pSel, long* pImageOnPdfNumber, CRect rectImage);
	void PrintImageOnPdfFromDib(CDib* pDib, long lImageNumber, CRect rectImage);

	/// <summary>
	/// Azzera il contenuto di tutte le forms
	/// </summary>
	void ResetForm();

	/// <summary>
	/// Cerca di posizionarsi sopra all'esame passato
	/// </summary>
	/// <param name="lContatore">id esame</param> 
	/// <param name="bSafeValue">non usato</param> 
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL RicercaContatoreEsame(long lContatore, BOOL bSafeValue);

	/// <summary>
	/// Carica nel menu File->Etichette i dati presenti nella tabella del DB
	/// </summary>
	/// <returns>TRUE se le operazioni sono state effettuate correttamente</returns>
	BOOL RiempiMenuEndoxFileEtichette(CMenu* pMenu);

	/// <summary>
	/// Salva l'esame corrente
	/// </summary>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL SaveEsami();

	/// <summary>
	/// Salva le form
	/// </summary>
	void SaveForm();

	/// <summary>
	/// Salva le etichette dei campi personalizzabili
	/// </summary>
	void ScriviEtichette();

	/// <summary>
	/// Mostra la dialog per la selezione del report da stampare, ritorna in pStruct la struttura del report selezionato
	/// </summary>
	/// <param name="pStruct">struttura del report selezionato</param>
	/// <returns>TRUE se è stato selezionato un report valido, FALSE se è stata annullata la procedura o se si sono incontrati dei problemi</returns>
	BOOL SelezionaFileReport(STRUCT_STAMPA* pStruct);

	/// <summary>
	/// ritorna in pStruct la struttura del report il cui percorso è stato passato in sFile
	/// </summary>
	/// <param name="pStruct">struttura del report</param>
	/// <param name="sFile">pecorso del report</param>
	/// <returns>TRUE se il report è valido, FALSE se si sono incontrati dei problemi</returns>
	BOOL SelezionaFileReport(STRUCT_STAMPA* pStruct, CString sFile);

	/// <summary>
	/// Prepara font di default per campo report
	/// </summary>
	/// <param name="pPrinterFont">font default OUT</param>
	void SetDefaultFont(LOGFONT* pPrinterFont);

	/// <summary>
	/// Notifica a tutte le form il cambiamento di stato
	/// </summary>
	/// <param name="bReadOnly">TRUE sola lettura</param> 
	void SetReadOnly(BOOL bReadOnly);

	/// <summary>
	/// Ferma il play remoto del filmato
	/// </summary>
	void StopRemotePlay();

	/// <summary>
	/// Archivia le immagini su PACS
	/// </summary>
	void StoreImmOnPacs();

	/// <summary>
	/// Esegue il backup dell'archivio immagini
	/// </summary>
	/// <returns>il numero di immagini trasferite</returns>
	int TrasferimentoImmagini(BOOL bVerbose);

	/// <summary>
	/// Permette all'utente di risolvere i casi di omonimia
	/// </summary>
	/// <param name="strTitle">titolo finestra</param> 
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL VerifyDuplicated(CString strTitle = "");

	/// <summary>
	/// Aggiorna il frame che indica lo stato dell'esame
	/// </summary>	
	void UpdateFrameStato();

	/// <summary>
	/// Imposta lo stato di visualizzazione della form di stato esame
	/// </summary>
	/// <param name="show">TRUE mostra lo stato esame, FALSE nascondilo</param>	
	void ShowStatoEsame(BOOL show);
	
	/// <summary>
	/// Imposta lo stato di visualizzazione della form di stato monitoraggio
	/// </summary>
	/// <param name="show">TRUE mostra lo stato monitoraggio, FALSE nascondilo</param>	
	void ShowStatoMonitoraggio(BOOL show);

	/// <summary>
	/// Verifica che il monitoraggio sia ancora in corso
	/// </summary>
	void CheckMonitoraggioInCorso();	

	/// <summary>
	/// Verifica se la stazione ha monitoraggi in corso
	/// </summary>
	void VerificaSeMonitoraggiInCorsoStazione();

	/// <summary>
	/// Aggiorna i dati del monitoraggio su db
	/// </summary>
	///	<param name="idSessione">id della sessione assegnato</param>
	///	<param name="idDispositivo">id del dispositivo</param>
	///	<param name="fase">fase del monitoraggio</param>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL InsertHeaderMonitoraggioIdSessione(CString idSessione, long idDispositivo, MonitoringPhase fase);

	/// <summary>
	/// Setta il monitoraggio come terminato su db
	/// </summary>
	/// <param name="lIDHeaderMisurazioni">id dell'header delle misurazioni vital sign</param>
	/// <returns>TRUE se tutte le operazioni hanno avuto successo</returns>
	BOOL UpdateMonitoraggioTerminato(long lIDHeaderMisurazioni);

	/// <summary>
	/// Ritorna lo stato del monitoraggio
	/// </summary>
	/// <param name="lIDHeaderMisurazioni">id dell'header delle misurazioni vital sign</param>
	/// <returns>TRUE se il monitoraggio è in corso</returns>
	BOOL IsMonitoraggioInCorso(long lIDHeaderMisurazioni);

	/// <summary>
	/// Chiede se la stazione ha un monitoraggio in corso
	/// </summary>
	/// <param name="m_idMonitoraggioInCorso">parametro di uscita, id del monitoraggio in corso individuato</param>
	/// <param name="idDispositivo">parametro di uscita, id del dispositivo</param>
	/// <returns>TRUE se la stazione ha monitoraggio in corso</returns>
	BOOL StazioneHaMonitoraggiPreInCorso(long *m_idMonitoraggioInCorso, long *idDispositivo);

	/// <summary>
	/// Aggiunge l'elemento alla lista degli elementi del referto
	/// </summary>
	/// <param name="chiave">nome del campo</param>
	///	<param name="valore">valore</param>
	CList<reportElement*> *AddElementToDocument(LPCTSTR chiave, LPCTSTR valore, CList<reportElement*> *reportElementList = NULL);	

	/// <summary>
	/// Aggiorna i dati dell'esame con quelli provenienti dalla worklist
	/// </summary>	
	void UpdateDataFromWorklist();	

	/// <summary>
	/// Archivia su storico l'esame
	/// </summary>
	//void ArchiviaEsame();

	/// <summary>
	/// Metodo da invocare tramite thread esterno per ottenere lo stato dello streaming
	/// </summary>
	/// <param name="pParam">parametri della chiamata</param>
	static UINT OnThreadGetStreamingState(LPVOID pParam);

	/// <summary>
	/// Flag maschere read only
	/// </summary>
	BOOL m_bReadOnly;

	/// <summary>
	/// Brush sfondo casella paziente programma
	/// </summary>
	CBrush m_brushSfondoPaziente;

	/// <summary>
	/// Brush sfondo casella stato programma
	/// </summary>
	CBrush m_brushSfondoStato;

	/// <summary>
	/// Attributo che determina se devono essere utilizzati i valori di default per i nuovi esami
	/// </summary>
	BOOL m_bValoriDefault;

	/// <summary>
	/// Etichette ridefinite per localizzazione automatica
	/// </summary>
	CStaticLocalize m_ctrlStaticPaziente;
	CStatic m_ctrlPatientLabel00;
	CStaticLocalize m_ctrlPatientLabel01;
	CStaticLocalize m_ctrlPatientLabel02;
	CStaticLocalize m_ctrlPatientLabel03;
	CStaticLocalize m_ctrlPatientLabel04;
	CStaticLocalize m_ctrlPatientLabel05;
	CStaticLocalize m_ctrlPatientLabel06;
	CStaticLocalize m_ctrlPatientLabel07;
	CStaticLocalize m_ctrlPatientLabel08;
	CStaticLocalize m_ctrlStaticExamNum;

	/// <summary>
	/// Frame principale
	/// </summary>
	CFrameStatic m_ctrlStaticFrameStato;
	CProgressCtrl m_ctrlProgressImport;

	/// <summary>
	/// ID del footer da stampare
	/// </summary>
	long m_lIDFooterToPrint;

	/// <summary>
	/// ID dell'header da stampare in prima pagina
	/// </summary>
	long m_lIDHeaderToPrint1;

	/// <summary>
	/// ID dell'header da stampare nelle pagine successive
	/// </summary>
	long m_lIDHeaderToPrint2;

	/// <summary>
	/// Esame lockato
	/// </summary>
	long m_lLockedExam;

	/// <summary>
	/// Versione interfaccia esame precedente
	/// </summary>
	long m_lPrevVers;

	/// <summary>
	/// Toolbar esami
	/// </summary>
	CEndoxBar* m_pExamBar;

	/// <summary>
	/// Toolbat paziente
	/// </summary>
	CEndoxBar* m_pPatientBar;

	/// <summary>
	/// Riferimento al dialog dei sospesi istologici
	/// </summary>
	CEndoxResizableDlg* m_pSospesiIstologiciDlg;

	/// <summary>
	/// Sandro 29/05/2014
	/// Lista delle immagini inserite nei PDF, eventualmente da contrassegnare come "stampate"
	/// </summary>
	CImgIDList m_listIDStampate;

	/*
	/// <summary>
	/// Simone 21/07/2015
	/// lista che verrà popolata con i tag che compongono il referto
	/// </summary>
	CList<reportElement*> *m_pReportElementList;
	*/

	/// <summary>
	/// Simone 01/12/2015
	/// Id dell'header delle misurazioni Vital Sign in corso
	/// </summary>
	long m_lIDHeaderMisurazioniInCorso;

	/// <summary>
	/// Simone 01/12/2015
	/// Nome del dispositivo utilizzato per il monitoraggio in corso
	/// </summary>
	CString m_sNomeDispositivoMonitoraggio;

	/// <summary>
	/// Oggetto che rappresenta i parametri del thread
	/// </summary>
	tagStreamingStateTHREAD m_streamingThreadState;

	/// <summary>
	/// Oggetto che rappresenta la critical section del thread del controllo dello streaming
	/// </summary>
	CRITICAL_SECTION m_streamingStateThreadCS;

	/// <summary>
	/// Oggetto che rappresenta l'evento per uscire dal thread
	/// </summary>
	HANDLE m_hEventExitStreamingStateThread;

	/// <summary>
	/// Simone 29/03/2016
	/// Stato dello streaming della stazione corrente
	/// </summary>
	long m_lStreamingState;

	/// <summary>
	/// Simone 09/06/2016
	/// Lista delle fasi attualmente chiuse sull'esame
	/// </summary>
	CList<long> m_listIDFasiChiuse;

	/// <summary>
	/// Julio 09/03/2018
	/// Textbox de Ficha no menu principal para o Fleury
	/// </summary>
	CString m_sFleuryFicha;

	/// <summary>
	/// Julio 09/03/2018
	/// Textbox de Item no menu principal para o Fleury
	/// </summary>
	CString m_sFleuryItem;
		
	/// <summary>
	/// Julio 02/08/2018
	/// Lista das fichas que são carregadas ao clique de m_ctrlBtnFleuryFichaItem
	/// </summary>
	CString m_arrayFleuryFichaItem[15];

	CACEdit m_ctrlEditFleuryFicha;
	
	void OnBnClickedBtnViewPacs();	

	void OnEnChangeEditFleuryEnterPressed();

	void AddFleuryFichaToEditBox(CString sFicha);

	/// <summary>
	///Gabriel 12/01/2021
	/// Verifica a lista de siglas que utilizam laudo de imagens em modo paisagem
	/// </summary>
	BOOL GetPdfImagePageOrientation();//Gabriel BUG 6303

	/// <summary>
	///Gabriel 12/05/2021
	/// Dispara a mensagem de substituição de resultado para a API do Fleury
	/// </summary>
	BOOL SubstituicaoResultado(CString sMotivo);//Gabriel - P3

	void OnCommandMenuOpzioniSetupUnitaTCP(); //Gabriel - TCP

	/// <summary>
	///Gabriel 27/09/2021
	/// Fecha o exame relacionado
	/// </summary>
	long OnChiudiEsameCorrelati(long lIdEsame);
	
public:	

	CString m_sMsgGotRefertoRefreshWithUpdate = ""; // Marvel BUG 4092 - concorrência na edição de laudos
	afx_msg void OnBnClickedBtnMonStop();	
	afx_msg void OnEnChangeEditFleuryficha();	
	afx_msg void OnEnChangeEditFleuryitem();	

	//Gabriel - TCP
	/// <summary>
	///Gabriel 04/09/2021
	/// Verifica se a ficha é TCP
	/// </summary>
	BOOL IsTCP();

	/// <summary>
	///Gabriel 27/09/2021
	/// Gera o laudo do exame principal
	/// </summary>
	long OnGeneraRefertoEsamePrincipale();
};

#endif  /* __ESAMIVIEW_H__ */
