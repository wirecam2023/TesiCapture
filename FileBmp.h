#ifndef _FILEBMP_H_
#define _FILEBMP_H_

#include "Bmp.h"
#include "ObSelect.h"

#define CARICA_MINI 0
#define CARICA_IMM 1

#define BORDO_PUNTO 2
#define RAGGIO_PUNTO 12

#define ALL_IMAGES 0x777
#define LOCAL_IMAGES 0x888
#define GLOBAL_IMAGES 0x999

class CImgListOrgani;

/// <summary> 
/// Visualizza una miniatura all'interno dell'album delle immagini
/// Contiene delle variabili e metodi statici che invece servono a gestire
/// operazioni trasversali tra l'insieme di tutte le istanze dell'oggetto allocate
/// </summary> 
class CFileBmp : public CBmp
{

public:

	/// <summary> 
	/// Costruttore
	/// </summary> 
	CFileBmp();

	/// <summary> 
	/// Distruttore
	/// </summary> 
	virtual ~CFileBmp();

	/// <summary> 
	/// Crea l'istanza per un nuovo oggetto CFileBmp; automaticamente si aggancia
	/// ad un frame contenitore
	/// </summary> 
	/// <param name="pActiveView">vista principale</param> 
	/// <param name="pParentWnd">finestra padre</param> 
	/// <param name="pctrFrame">frame contenitore</param> 
	/// <param name="pBmp">istanza oggetto OUT</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	static BOOL CreateBmp(CEsamiView* pActiveView, CWnd* pParentWnd, CWnd* pctrFrame, CFileBmp** pBmp);

	/// <summary> 
	/// Svuota la lista degli oggetti selezionati
	/// </summary> 
	/// <param name="what">Può essere ALL_IMAGES o LOCAL_IMAGES o GLOBAL_IMAGES</param> 
	static void DeleteListSelected(UINT what);

	/// <summary> 
	/// Elimina dalla lista delle immagini da stampare quello passato
	/// </summary> 
	/// <param name="pSel">CFileBmp da non stampare</param> 
	static void DeletePrinter(CObSelect* pSel);

	/// <summary> 
	/// Conta il numero delle immagini da stampare partendo dalla lista di quelle selezionate
	/// </summary> 
	/// <param name="what">ALL_IMAGES considera tutte le immagini LOCAL_IMAGES solo immagini album locale GLOBAL_IMAGES solo immagini album generale</param> 
	/// <returns>numero immagini che sono selezionate per la stampa</returns>
	static long CountPrinterList(UINT what); // Sandro 26/11/2013 // conta il numero delle immagini da stampare partendo dalla lista di quelle selezionate //

	/// <summary> 
	/// Riempie la lista delle immagini da stampare partendo dalla lista di quelle selezionate
	/// </summary> 
	/// <param name="what">ALL_IMAGES considera tutte le immagini LOCAL_IMAGES solo immagini album locale GLOBAL_IMAGES solo immagini album generale</param> 
	/// <returns>numero immagini che saranno stampate</returns>
	static long FillImagesPrinterList(UINT what); // Sandro 30/11/2010 // mi riempie la lista delle immagini da stampare partendo dalla lista di quelle selezionate //

	/// <summary> 
	/// Riempie la lista delle immagini da stampare partendo dalla lista di quelle selezionate
	/// A differenza della funzione precedente prevede un numero massimo di immagini stampabili
	/// </summary> 
	/// <param name="what">ALL_IMAGES considera tutte le immagini LOCAL_IMAGES solo immagini album locale GLOBAL_IMAGES solo immagini album generale</param> 
	/// <param name="lMaxImages">numero massimo immagini stampabili</param> 
	/// <returns>numero immagini che saranno stampate</returns>
	static long FillImagesPrinterList(UINT what, long lMaxImages); // Sandro 30/11/2010 // mi riempie la lista delle immagini da stampare partendo dalla lista di quelle selezionate //

	/// <summary> 
	/// Riempie la lista dei frames da stampare a partire dalla lista m_listPrinter
	/// Analizza tutti gli oggetti aggiungendo in lista anche tutti i frame presenti
	/// all'interno di un immagine multiframe
	/// </summary> 
	/// <param name="pImgManager">gestore immagini</param> 
	/// <param name="pListImagesToPrint">lista immagini effettivamente da stampare</param> 
	/// <returns>numero immagini che saranno stampate</returns>
	static long FillListImagesToPrint(CImgManager* pImgManager, CList<IMAGE_TO_PRINT*> *pListImagesToPrint); // Sandro 30/11/2010 // mi riempie la lista dei frames da stampare partendo dalla lista di immagini selezionate //

	/// <summary> 
	/// Ritorna la posizione del primo elemento CFileBmp selezionato
	/// dall'utente
	/// </summary> 
	/// <returns>posizione del primo elemento selezionato</returns>
	static POSITION GetFirstSelectedPos();

	/// <summary> 
	/// Ritorna l'elemento selezionato della posizione passata;
	/// automaticamente si posiziona all'elemento successivo selezionato
	/// </summary> 
	/// <param name="pos">elemento selezionato OUT</param> 
	/// <returns>elemento selezionato puntato da pos</returns>
	static CObSelect* GetNextSelected(POSITION& pos);

	/// <summary> 
	/// Aggiunge agli elementi selezionati un nuovo elemento
	/// </summary> 
	/// <param name="pFileBmp">elemento da selezionare</param> 
	/// <returns>NULL se l'elemento è già selezionato altrimenti il riferimento alla selezione</returns>
	static CObSelect* NewSelected(CFileBmp* pFileBmp);

	/// <summary> 
	/// Ritorna l'elemento selezionato della posizione passata;
	/// automaticamente si posiziona all'elemento successivo selezionato
	/// </summary> 
	/// <param name="pos">elemento selezionato OUT</param> 
	/// <returns>elemento selezionato puntato da pos</returns>
	static CObSelect* NewSelected(long lID, BOOL bIsAlbumGlobal, int iType, const CString &strDescription, long lPaziente, long lEsame, BOOL bTransferred, const CString &strDvdLabel, BOOL bCI);

	/// <summary> 
	/// Rimuove dalle immagini selezionate l'elemento
	/// </summary> 
	/// <param name="lIDImmagine">l'ID dell'elemento da eliminare</param> 
	/// <returns>TRUE se l'operazione è stata completata con successo</returns>
	static BOOL RemoveSelected(long lIDImmagine, BOOL bIsGlobal);

	/// <summary> 
	/// Rimuove dalle immagini selezionate l'elemento
	/// </summary> 
	/// <param name="pFileBmp">elemento da eliminare</param> 
	/// <returns>TRUE se l'operazione è stata completata con successo</returns>
	static BOOL RemoveSelected(CFileBmp* pFileBmp);

	/// <summary> 
	/// Rimuove dalle immagini selezionate l'elemento per riferimento alla selezione
	/// </summary> 
	/// <param name="pSel">elemento da eliminare</param> 
	/// <returns>TRUE se l'operazione è stata completata con successo</returns>
	static BOOL RemoveSelected(CObSelect* pSel);

	/// <summary> 
	/// Allinea la selezione dell'oggetto passato con la lista interna di riferimenti
	/// </summary> 
	/// <param name="pFileBmp">elemento da allineare</param> 
	/// <param name="bCheck">controlla se necessario anche lo stato deselezionato</param> 
	static void ReselectBmp(CFileBmp* pFileBmp, BOOL bCheck);

	/// <summary> 
	/// Informa la finestra parent di un cambio di selezione tra gli oggetti
	/// </summary> 
	static void SendUpdateMessage();

	/// <summary> 
	/// Lista immagini da stampare
	/// </summary> 
	static CObArray m_listPrinter;

	/// <summary> 
	/// Lista immagini selezionate
	/// </summary> 
	static CObList m_listSelected;

	/// <summary> 
	/// Verfica l'esistenza del file immagine all'interno dell'archivio
	/// </summary> 
	/// <returns>TRUE se il file esiste</returns>
	BOOL FileMainIsPresent();

	/// <summary> 
	/// Carica un'immagine all'interno del controllo
	/// </summary> 
	/// <param name="lPaziente">id paziente</param> 
	/// <param name="lEsame">id esame</param> 
	/// <param name="pImgListOrgani">lista immagini pre caricate</param> 
	/// <param name="lIndex">indice immagine da caricare dalla lista passata</param> 
	/// <param name="bIsTransferred">immagine trasferita</param> 
	/// <param name="strDvdLabel">etichetta dvd</param> 
	/// <param name="lCosaCarico">CARICA_MINI miniatura CARICA_IMM immagine intera</param> 
	/// <returns>TRUE se le operazioni hanno avuto esito positivo</returns>
	BOOL LoadImage(long lPaziente, long lEsame, CImgListOrgani* pImgListOrgani, long lIndex, BOOL bIsTransferred, CString strDvdLabel, short lCosaCarico);

	/// <summary> 
	/// Svuota il controllo dall'immagine esistente
	/// </summary> 
	/// <param name="bOnExit">se TRUE il controllo non viene ridisegnato</param> 
	void ResetImage(BOOL bOnExit = FALSE);

	/// <summary> 
	/// Imposta il controllo per associarlo all'album generale
	/// </summary> 
	/// <param name="bIsAlbumGlobal">TRUE per specificare che fa parte dell'album generale</param> 
	void SetAlbumType(BOOL bIsAlbumGlobal);

	/// <summary> 
	/// Visualizza l'immagine a risoluzione effettiva
	/// </summary> 
	void ShowTga();

	/// <summary> 
	/// Immagine del Consenso Informato
	/// </summary> 
	BOOL m_bCI;

	/// <summary> 
	/// Immagine trasferita e confermata
	/// </summary> 
	BOOL m_bConfirmed;

	/// <summary> 
	/// Flag appartenenza album generale
	/// </summary> 
	BOOL m_bIsAlbumGlobal;

	/// <summary> 
	/// Handle miniatura visualizzata
	/// </summary> 
	HBITMAP m_hMiniBmp;

	/// <summary> 
	/// Tipologia contenuto
	/// </summary> 
	int m_iType;

	/// <summary> 
	/// ID esame
	/// </summary> 
	long m_lEsame;

	/// <summary> 
	/// ID paziente
	/// </summary> 
	long m_lPaziente;

	/// <summary> 
	/// Etichetta dvd nel caso di immagine trasferita e confermata
	/// </summary> 
	CString m_strDvdLabel;

protected:

	/// <summary> 
	/// Messaggio inviato da Windows con la richiesta di ridisegno del controllo
	/// </summary> 
	afx_msg void OnPaint();

	/// <summary> 
	/// Evento collegato al doppio click all'interno del controllo
	/// </summary> 
	/// <param name="nFlags">non usato</param> 
	/// <param name="point">non usato</param> 
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	/// <summary> 
	/// Evento collegato alla pressione della rotellina all'interno del controllo
	/// </summary> 
	/// <param name="nFlags">non usato</param> 
	/// <param name="point">non usato</param> 
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);

	/// <summary> 
	/// Evento collegato alla pressione del tasto destro
	/// </summary> 
	/// <param name="nFlags">non usato</param> 
	/// <param name="point">non usato</param> 
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	/// <summary> 
	/// Dichiarazione della mappa dei messaggi
	/// </summary> 
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT RefreshAlbum(WPARAM wParam, LPARAM lParam); //Gabriel - BUG Refresh álbum

private:

	/// <summary> 
	/// Lista immagini esame corrente
	/// </summary> 
	CImgListOrgani* m_pImgListOrgani;

};

#endif /* _FILEBMP_H_ */