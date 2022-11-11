#ifndef _ALBUMFORM_H_
#define _ALBUMFORM_H_

#include "EndoxResizableDlg.h"
#include "EditBmp.h"
#include "EndoxBar.h"

class CWaitingDicomDlg;

struct tagIMAGEINFO
{
	TCHAR szFileName[256];
};

struct tagIMAGESINFO
{
	long lPatientID;
	long lExamID;
	CList<tagIMAGEINFO>* pImageListID;
};

/// <summary> 
/// Oggetto album
/// Gestisce la visualizzazione / aggiunta / cancellazione
/// delle immagini associate all'esame corrente
/// Vengono visualizzate 6 immagini per volta e l'utente ha
/// la possibilità di muoversi tra le immagini con appositi bottoni
/// </summary> 
class CAlbumForm : public CEndoxResizableDlg
{
	DECLARE_DYNCREATE(CAlbumForm)

public:

	/// <summary> 
	/// Costruttore protetto: è necessario passare per la funzione CreateFormEx
	/// per garantire l'univocità d'istanza di questo oggetto
	/// </summary> 
	CAlbumForm(CWnd* pParent = NULL, CEsamiView* pEsamiView = NULL);

	/// <summary> 
	/// Distruttore
	/// </summary> 
	virtual ~CAlbumForm(void);

	enum { IDD = IDD_ALBUM };

	/// <summary> 
	/// Acquisizione da sorgente twain
	/// </summary> 
	void AcqFromScanner(BOOL bCI);

	/// <summary> 
	/// Acquisizione da sorgente alternativa
	/// </summary> 
	void AcqFromWindowMessage();

	/// <summary> 
	/// Svuota l'album e ricarica le immagini posizionandosi
	/// nella prima pagina disponibile
	/// </summary> 
	/// <param name="bDeleteSelected">resetta anche le immagini precedentemente selezionate</param> 
	void AfterMoveEsame(BOOL bDeleteSelectedImages = TRUE, BOOL bMoveToLastPage = FALSE);

	//Gabriel BUG 7768 - Continuous capture problem
	LRESULT AfterMoveEsameTrue(WPARAM wParam, LPARAM lParam);

	LRESULT AcquisitionWaiterClosing(WPARAM wParam, LPARAM lParam);

	LRESULT WaitingAutoImportClosing(WPARAM wParam, LPARAM lParam);

	/// <summary> 
	/// Permette il recupero delle immagini della cartella temporanea in caso di errore
	/// Le immagini vengono temporaneamente salvate in locale da xcap e poi importate
	/// nell'archivio alla chiusura del programma di acquisizione. I nomi dei files
	/// hanno come prefisso l'id paziente e id esame per cui in caso di errore EcoPlus
	/// è in grado di importarle nell'esame corretto. Viene chiamata ogni volta prima
	/// di una nuova acquisizione per verificare la corretta importazione delle immagini
	/// del caso precedente
	/// </summary> 
	BOOL CheckTempFolder();

	/// <summary> 
	/// Funzione di supporto per la creazione della form
	/// </summary> 
	/// <param name="pParentWnd">finestra parent</param> 
	/// <param name="rectFrame">dimensione form richiesta</param> 
	/// <returns>sempre 0</returns>
	BOOL CreateChildForm(CWnd* pParentWnd, CRect rectFrame);

	/// <summary> 
	/// Crea la form garantendo l'univocità della stessa
	/// Solo un AlbumForm può essere istanziato per volta
	/// </summary> 
	/// <param name="pParentWnd">finestra padre</param> 
	/// <param name="pFrame">frame con conterrà la form</param> 
	/// <param name="pDlg">puntatore all'oggetto creato OUT</param> 
	/// <param name="pEsamiView">vista principale</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	static BOOL CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CAlbumForm** pDlg, CEsamiView* pEsamiView);

	/// <summary> 
	/// Legge le immagini da ImgManager e le salva nelle liste di supporto
	/// </summary> 
	/// <returns>numero immagini caricate</returns>
	int FillDiapoIndex();

	/// <summary> 
	/// Aggiorna le immagini da visualizzare a seconda dello
	/// spostamento effettuato tra le immagini stesse
	/// </summary> 
	void MoveImage();

	/// <summary> 
	/// Aggiorna la pagina corrente dell'album per quanto riguarda la
	/// selezione degli oggetti
	/// </summary> 
	void RefreshAlbum();

	/// <summary> 
	/// Aggiorna le immagini da visualizzare a seconda dello
	/// spostamento effettuato tra le immagini stesse controllando prima
	/// lo stato degli indici interni
	/// </summary> 
	void RequeryPage();

	/// <summary> 
	/// Svuota l'album
	/// </summary> 
	void ResetAlbum();

	/// <summary> 
	/// Azzerra il contenuto dell'album e delle liste interne
	/// </summary> 
	/// <param name="bReposition">azzerra anche la posizione attuale</param> 
	void ResetVetDiapo(BOOL bReposition);

	/// <summary> 
	/// Seleziona automaticamente tutte le immagini
	/// </summary> 
	void SelectAllImages();

	/// <summary> 
	/// Seleziona automaticamente tutte le immagini già stampate in precedenza
	/// </summary> 
	void SelectAlreadyPrintedImages();

	/// <summary> 
	/// Trasferisce su PACS le immagini
	/// </summary> 
	void StoreImmOnPacs(); // Sandro 26/11/2013 //

	/// <summary> 
	/// Apre il programma esterno per la visualizzazione di un filmato
	/// </summary> 
	/// <param name="strFileFilm">file filmato</param> 
	void ViewFilm(CString strFileFilm);

	/// <summary> 
	/// Apre il programma esterno per la visualizzazione di un filmato
	/// con la possibilità di acquisire dei frame del filmato stesso
	/// </summary> 
	/// <param name="strFileFilm">file filmato</param> 
	void ViewFilmAndSelectFrame(CString strFileFilm);

	/// <summary> 
	/// Restituisce il numero di immagini selezionate
	/// </summary> 
	long GetSelectedCount();

	/// <summary> 
	/// Refresh Static component form with number total of images into the album
	/// </summary> 
	void CAlbumForm::refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK

	/// <summary> 
	/// Caselle testo per commenti
	/// </summary> 
	CEditBmp m_ctrlBmpEdit[NUM_MAX_BMP];

	/// <summary> 
	/// Frame contenente controlli immagine
	/// </summary> 
	CStatic m_ctrlFrame[NUM_MAX_BMP];

	/// <summary> 
	/// Lista immagini caricate
	/// </summary> 
	CImgListOrgani m_ImgListOrgani;

	/// <summary> 
	/// Numero di immagini relative al consenso informato
	/// </summary> 
	long m_lCINum;

	/// <summary> 
	/// Lista punti associazione immagine / organo
	/// </summary> 
	CList <tagPunti> m_listPunti;

	/// <summary> 
	/// Indice prima immagine visualizzata
	/// </summary> 
	int m_nDiapoPage;

	/// <summary> 
	/// Numero immagini totale album
	/// </summary> 
	int m_nMaxDiapo;

	/// <summary> 
	/// Numero immagini per pagina
	/// </summary> 
	int m_nNumMaxBmp;

	/// <summary> 
	/// Oggetto esame attuale
	/// </summary> 
	CEsamiSet* m_pEsamiSet;

	/// <summary> 
	/// Vista principale
	/// </summary> 
	CEsamiView* m_pEsamiView;

	/// <summary> 
	/// Controlli immagine
	/// </summary> 
	CFileBmp* m_pFileBmp[NUM_MAX_BMP];

	/// <summary> 
	/// Oggetto paziente attuale
	/// </summary> 
	CPazientiSet* m_pPazientiSet;

	/// <summary> 
	/// Toolbar dei tasti
	/// </summary> 
	CEndoxBar m_wndAlbumBar;

	/// <summary> 
	/// Flag che identifica se è attiva l'acquisizione da fotocamera per Dermox
	/// </summary> 
	BOOL m_bDermoxPhotoAcq;

	/// <summary> 
	/// Directory da verificare nell'acquisizione da fotocamera
	/// </summary> 
	CString m_sDermoxAcqPhotoDirectory;

protected:

	/// <summary> 
	/// Funzione standard per l'interscambio dei dati tra controlli e variabili
	/// </summary> 
	/// <param name="pDX">oggetto per interscambio</param> 
	virtual void DoDataExchange(CDataExchange* pDX);

	/// <summary> 
	/// Ridefinizione per evitare che con il tasto esc si chiuda il dialogo
	/// </summary> 
	virtual void OnCancel();

	/// <summary> 
	/// Chiamata dal framework mfc per l'inizializzazione del dialogo
	/// Vengono effettuate le operazioni preliminari di caricamento della form
	/// </summary> 
	/// <returns>TRUE per assegnazione automatica focus al primo controllo</returns>
	virtual BOOL OnInitDialog();

	/// <summary> 
	/// Ridefinizione per evitare che con il tasto enter si chiuda il dialogo
	/// </summary> 
	virtual void OnOK();

	/// <summary> 
	/// Messaggio ricevuto dopo il cambio di un commento da parte dell'utente
	/// </summary> 
	/// <param name="wParam">non usato</param> 
	/// <param name="lParam">non usato</param> 
	/// <returns>sempre 0</returns>
	afx_msg LRESULT AfterChangeComment(WPARAM wParam, LPARAM lParam);

	/// <summary> 
	/// Messaggio ricevuto per imporre un nuovo caricamento dell'album
	/// </summary> 
	/// <param name="wParam">non usato</param> 
	/// <param name="lParam">non usato</param> 
	/// <returns>sempre 0</returns>
	afx_msg LRESULT AfterElabImage(WPARAM wParam, LPARAM lParam);

	//
	afx_msg LRESULT RefreshImages(WPARAM wParam, LPARAM lParam);

	//
	afx_msg LRESULT WaitingDicomClosing(WPARAM wParam, LPARAM lParam);

	/// <summary> 
	/// Evento collegato al bottone importa da disco
	/// </summary> 
	afx_msg void OnImmAcqFromDisk();

	/// <summary> 
	/// Evento collegato al bottone importa da sorgente twain
	/// </summary> 
	afx_msg void OnImmAcqFromScanner();

	/// <summary> 
	/// Evento collegato al bottone importa da sorgente video
	/// </summary> 
	afx_msg void OnImmAcqFromTele();

	/// <summary> 
	/// Evento collegato al bottone album esame
	/// </summary> 
	afx_msg void OnImmAlbum();

	/// <summary> 
	/// Evento collegato al bottone associazione immagine / organo
	/// </summary> 
	afx_msg void OnImmAss();

	/// <summary> 
	/// Evento collegato al bottone elimina immagini
	/// </summary> 
	afx_msg void OnImmDelete();

	/// <summary> 
	/// Evento collegato al tasto dei TIFF multipagina
	/// </summary> 
	afx_msg void OnImmMultiPage();

	/// <summary> 
	/// Evento collegato al tasto che seleziona tutte le immagini
	/// </summary> 
	afx_msg void OnImmSelectAll();

	/// <summary> 
	/// Evento collegato al tasto che deseleziona tutte le immagini
	/// </summary> 
	afx_msg void OnImmUnselectAll();

	/// <summary> 
	/// Evento collegato al tasto che fa l'anteprima delle immagini
	/// </summary> 
	afx_msg void OnImmPreview();

	/// <summary> 
	/// Evento collegato al bottone prima pagina
	/// </summary> 
	afx_msg void OnPageFirst();

	/// <summary> 
	/// Evento collegato al bottone ultima pagina
	/// </summary> 
	afx_msg void OnPageLast();

	/// <summary> 
	/// Evento collegato al bottone pagina successiva
	/// </summary> 
	afx_msg void OnPageNext();

	/// <summary> 
	/// Evento collegato al bottone pagina precedente
	/// </summary> 
	afx_msg void OnPagePrev();

	/// <summary> 
	/// Messaggio ricevuto durante il ridensionamento della form principale
	/// </summary> 
	/// <param name="wParam">non usato</param> 
	/// <param name="lParam">non usato</param> 
	/// <returns>sempre 0</returns>
	afx_msg LRESULT OnResizeForm(WPARAM wParam, LPARAM lParam);

	/// <summary> 
	/// Messaggio ricevuto durante il cambio di selezione delle immagini
	/// </summary> 
	/// <param name="wParam">numero immagini selezionate</param> 
	/// <param name="lParam">non usato</param> 
	/// <returns>sempre 0</returns>
	afx_msg LRESULT OnUpdateSel(WPARAM wParam, LPARAM lParam);

	/// <summary> 
	/// Dichiarazione mappa dei messaggi
	/// </summary> 
	DECLARE_MESSAGE_MAP()

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	/// <summary> 
	/// Apre il tool per l'acquisizione dei grafici di audiologia
	/// </summary> 
	afx_msg void OnAudiologia();

	afx_msg void OnReOrderSelected();

	afx_msg LRESULT RefreshAlbumMessage(WPARAM wParam, LPARAM lParam); //Gabriel - BUG Refresh álbum

private:

	/// <summary> 
	/// check if exist MoveFile.exe / storescp.exe / storescp.cfg in the app folder because it's essencial to work
	// Marvel Carvalho - Bug 5512 Duplicação imagens ultrassom
	/// </summary> 
	BOOL ExternalExeToolsExists();

	/// <summary> 
	/// Acquisizione da sorgente video
	/// </summary> 
	BOOL AcqFromTele();

	/// <summary> 
	/// Acquisizione da sorgente video Dermox
	/// </summary> 
	BOOL AcqFromTeleDermox();

	/// <summary> 
	/// Carica l'associazione immagini / organo per le immagini precedentemente caricate
	/// </summary> 
	void CaricaPunti();

	/// <summary> 
	/// Verifica se sono presenti immagini "normali" ed immagini del Consenso Informato
	/// </summary> 
	void ControllaNormaliCI(BOOL& bRefNormali, BOOL& bRefCI);

	/// <summary> 
	/// Riempie la lista delle immagini selezionate
	/// </summary> 
	void FillArraySelected(CStringList* pArraySelected);

	/// <summary> 
	/// Salva il tempo impiegato dall'acquisizione
	/// </summary> 
	void SetTimestampAcq();

	//
	void PostAcquisizione();

	/// <summary>
	/// Controlli label
	/// </summary>
	CString m_ctrlStaticNum = TEXT("0");	// BUG 4197 - total imagens / qtd selecionadas / OK
	//CStaticLocalize m_ctrlStaticNum;		// antes apresentava a palavra "Seleção"
	CStaticLocalize m_ctrlStaticUser;

	/// <summary>
	/// Thread per lo spostamento delle immagini dalla TEMP locale al server
	/// </summary>
	static UINT AcqFromTeleImportThread(LPVOID pParam);

	BOOL OpenAudiologyTool(CString *tempDir);

	//

	CWaitingDicomDlg* m_pWaitingDicomDlg;

	char m_szProcessToKill[4000];
	PROCESS_INFORMATION m_piToKill;
};

#endif /* _ALBUMFORM_H_ */