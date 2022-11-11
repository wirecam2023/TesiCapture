#ifndef _IMAGEDLG_H_
#define _IMAGEDLG_H_

#include "EndoxResizableDlg.h"
#include "xrclient\xrclient.h"

/// <summary> 
/// Dialogo visualizzazione immagine reale
/// Permette anche la chiamata a Microimage - modulo per elaborazione / misurazione
/// </summary> 
class CImageDlg : public CEndoxResizableDlg
{

public:

	//Gabriel BUG 6225 - Lista DO
	/// <summary>
	/// Costruttore
	/// </summary>
	CImageDlg(CWnd *pParent, BOOL bDoModal, long lPaziente, long lEsame, long lID, int iType, BOOL bIsReferto);

	/// <summary>
	/// Distruttore
	/// </summary>
	virtual ~CImageDlg(void);

	/// <summary>
	/// ID risorsa
	/// </summary>
	enum { IDD = IDD_IMAGE };

	/// <summary>
	/// Imposta i riferimenti per la visualizzazione dell'immagine
	/// </summary>
	/// <param name="lPaziente">id paziente</param>
	/// <param name="lEsame">id esame</param>
	/// <param name="lID">id immagine</param>
	void SetIDs(long lPaziente, long lEsame, long lID, int iType);

	/// <summary>
	/// Modalità visualizzazione immagine attuale 0 dimensioni reali 1 adatta l'immagine alla finestra
	/// </summary>
	static int m_nShowMode;

	/// <summary>
	/// Flag deselezione immagine
	/// </summary>
	BOOL m_bDeselectImage;

	/// <summary>
	/// Flag dialogo chiamato da album generale
	/// </summary>
	BOOL m_bIsAlbumGlobal;

	/// <summary>
	/// Flag immagine modificata
	/// </summary>
	BOOL m_bRequeryImage;

	/// <summary>
	/// Riferimento alla schermata principale
	/// </summary>
	CEsamiView* m_pEsamiView;

	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#1 - dual screen)
	CImgList* m_listImgFromOutside;
	int       m_nImagesFromOutside;
	BOOL   m_bDoModal; //Gabriel BUG 6225 - Lista DO
	BOOL   m_bIsReferto;
protected:

	/// <summary>
	/// Effettua lo scambio dati tra l'interfaccia e gli attributi della classe
	/// </summary>
	/// <param name="pDX">oggetto utilizzato per il recupero dei riferimenti dall'interfaccia</param>
	virtual void DoDataExchange(CDataExchange* pDX);

	/// <summary> 
	/// Chiamata dal framework mfc per l'inizializzazione del dialogo
	/// Vengono effettuate le operazioni preliminari di caricamento della form
	/// </summary> 
	/// <returns>TRUE per assegnazione automatica focus al primo controllo</returns>
	virtual BOOL OnInitDialog();

	/// <summary> 
	/// Gestione tasto uscita dialogo
	/// </summary> 
	virtual void OnOK();

	virtual void PostNcDestroy(); //Gabriel BUG 6225 - Lista DO

	/// <summary> 
	/// Pre processing messaggi; viene chiamato da Windows prima della gestione vera e
	/// proprio dela messaggio stesso
	/// </summary> 
	/// <param name="pMsg">messaggio da gestire</param> 
	/// <returns>TRUE per messaggio gestito correttamente</returns>
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

	/// <summary> 
	/// Gestione tasto luminosità manuale
	/// </summary> 
	afx_msg void OnBrightnessManuale();

	/// <summary> 
	/// Esporta il singolo frame da un TIFF multipagina
	/// </summary> 
	afx_msg void OnButtonEsportaFrame();

	/// <summary> 
	/// Gestione tasto prima immagine
	/// </summary> 
	afx_msg void OnButtonFirst();

	/// <summary> 
	/// Gestione tasto ultima immagine
	/// </summary> 
	afx_msg void OnButtonLast();

	/// <summary> 
	/// Gestione tasto per tenere l'immagine
	/// </summary> 
	afx_msg void OnButtonMantieniImmagine();

	/// <summary> 
	/// Gestione tasto prossima immagine
	/// </summary> 
	afx_msg void OnButtonNext();

	/// <summary> 
	/// Gestione tasto prossimo frame immagine
	/// </summary> 
	afx_msg void OnButtonNextTiff();

	/// <summary> 
	/// Gestione tasto immagine precedente
	/// </summary> 
	afx_msg void OnButtonPrev();

	/// <summary> 
	/// Gestione tasto frame immagine precedente
	/// </summary> 
	afx_msg void OnButtonPrevTiff();

	/// <summary> 
	/// Gestione tasto per la stampa di tutti i frame
	/// </summary> 
	afx_msg void OnButtonPrintAll();

	/// <summary> 
	/// Gestione tasto per la stampa di un singolo frame
	/// </summary> 
	afx_msg void OnButtonPrintOne();

	/// <summary> 
	/// Lancia modulo esterno elaborazione / misurazione
	/// </summary> 
	afx_msg void OnCallProgram();

	/// <summary> 
	/// Gestione tasto elimina immagine
	/// </summary> 
	afx_msg void OnCancella();

	/// <summary> 
	/// Gestione radio cambia tipo visuale immagine
	/// </summary> 
	afx_msg void OnChangeShow();

	/// <summary> 
	/// Gestione del cambio commento
	/// </summary> 
	afx_msg void OnCommentoUpdate();

	/// <summary> 
	/// Gestione tasto contrasto manuale
	/// </summary> 
	afx_msg void OnContrastManuale();

	/// <summary> 
	/// Gestione tasto filtro enhance
	/// </summary> 
	afx_msg void OnEnhance();


	/// <summary> 
	/// Gestione scrollbar orizzontale
	/// </summary> 
	/// <param name="nSBCode">non usato</param> 
	/// <param name="nPos"non usato</param> 
	/// <param name="pScrollBar"non usato</param> 
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	/// <summary> 
	/// Gestione doppio click mouse; visualizza immagine a pieno schermo
	/// </summary> 
	/// <param name="nFlags">non usato</param> 
	/// <param name="point"non usato</param> 
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	/// <summary> 
	/// Gestione rotellina mouse; cambia immagine attuale
	/// </summary> 
	/// <param name="nFlags">non usato</param> 
	/// <param name="zDelta">non usato</param> 
	/// <param name="pt">non usato</param> 
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	/// <summary> 
	/// Gestione spostamento immagine
	/// </summary> 
	/// <param name="x">offset x</param> 
	/// <param name="y">offset y</param> 
	afx_msg void OnMove(int x, int y);

	/// <summary> 
	/// Gestione ridisegno finestra
	/// </summary> 
	afx_msg void OnPaint();

	/// <summary> 
	/// Gestione tasto destro mouse; modifica selezione immagine attuale
	/// </summary> 
	/// <param name="nFlags">non usato</param> 
	/// <param name="point"non usato</param> 
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	/// <summary> 
	/// Gestione tasto salva modifiche
	/// </summary> 
	afx_msg void OnSalva();

	/// <summary> 
	/// Gestione tasto salva modifiche su nuova immagine
	/// </summary> 
	afx_msg void OnSalvaNuovo();

	/// <summary> 
	/// Gestione ridimensionamento finestra
	/// </summary> 
	/// <param name="nType">non usato</param> 
	/// <param name="cx"non usato</param> 
	/// <param name="cy"non usato</param> 
	afx_msg void OnSize(UINT nType, int cx, int cy);

	/// <summary> 
	/// Gestione tasto annulla modifiche
	/// </summary> 
	afx_msg void OnUndo();

	/// <summary> 
	/// Gestione scrollbar verticale
	/// </summary> 
	/// <param name="nSBCode">non usato</param> 
	/// <param name="nPos">non usato</param> 
	/// <param name="pScrollBar">non usato</param> 
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCancel(); //Gabriel BUG 6225 - Lista DO

	afx_msg virtual LRESULT OnExamChanged(WPARAM wParam, LPARAM lParam); //Gabriel BUG 6225 - Lista DO

private:

	void UpdateWindowTitle(CString p_sTitle);  // Marvel Carvalho - Bug 4269 Dialog ImageSimple2Dlg ignora album com 1 imagem

	/// <summary> 
	/// Impone ridisegno finestra
	/// </summary> 
	void AutoRedraw();

	/// <summary> 
	/// Carica immagini attuale
	/// </summary> 
	/// <returns>TRUE se l'operazione è stata effettuata correttamente</returns>
	BOOL CaricaImmagine();

	/// <summary> 
	/// Gestione punti immagini associazione immagine organo
	/// </summary> 
	void CaricaPunti();

	/// <summary> 
	/// Recupera id immagine a partire dall'ordinale
	/// </summary> 
	/// <returns></returns>
	long GetId(int nPos);

	/// <summary> 
	/// Vai alla prima immagine
	/// </summary> 
	/// <returns>TRUE se l'operazione è stata effettuata correttamente</returns>
	BOOL GoFirst();

	/// <summary> 
	/// Vai all'ultima immagine
	/// </summary> 
	/// <returns>TRUE se l'operazione è stata effettuata correttamente</returns>
	BOOL GoLast();

	/// <summary> 
	/// Vai alla prossima immagine
	/// </summary> 
	/// <returns>TRUE se l'operazione è stata effettuata correttamente</returns>
	BOOL GoNext();

	/// <summary> 
	/// Vai all'immagine precedente
	/// </summary> 
	/// <returns>TRUE se l'operazione è stata effettuata correttamente</returns>
	BOOL GoPrev();

	/// <summary> 
	/// Converte le coordinate di un punto passato
	/// </summary> 
	/// <param name="ptPoint">coordinate del punto da convertire</param> 
	/// <returns>coordinate del punto convertito</returns>
	CPoint ImageToScreen(CPoint ptPoint);

	/// <summary> 
	/// Inizializzazione finestra
	/// </summary> 
	void InitializeWindow();

	/// <summary> 
	/// Verifica se l'immagine attuale è selezionata
	/// </summary> 
	void PrepareDataImage();

	/// <summary> 
	/// Prepara frame visualizzante immagine
	/// </summary> 
	void PrepareRectangle();

	/// <summary> 
	/// Salva le modifiche apportate all'immagine attuale
	/// </summary> 
	void SalvaImmagine();

	/// <summary> 
	/// Aggiunge l'immagine attuale alla lista generale delle
	/// immagini selezionate
	/// </summary> 
	void SelectThisImage();

	/// <summary> 
	/// Flag che indica se si è verificato un errore
	/// </summary> 
	BOOL m_bError;

	/// <summary> 
	/// Flag dialogo inizializzato
	/// </summary> 
	BOOL m_bInit;

	/// <summary> 
	/// Flag che dice se l'immagine è un multipagina o meno
	/// </summary> 
	BOOL m_bIsMultipage;

	/// <summary> 
	/// Flag immagine selezionata
	/// </summary> 
	BOOL m_bIsSelect;

	/// <summary> 
	/// Flag che indica se mantenere l'immagine
	/// </summary> 
	BOOL m_bMantieniImmagine;

	/// <summary> 
	/// Flag tasto immagine successiva attivo
	/// </summary> 
	BOOL m_bNext;

	/// <summary> 
	/// Flag tasto frame successivo attivo
	/// </summary> 
	BOOL m_bNextTiff;

	/// <summary> 
	/// Flag tasto immagine precedente attivo
	/// </summary> 
	BOOL m_bPrev;

	/// <summary> 
	/// Flag tasto frame precedente attivo
	/// </summary> 
	BOOL m_bPrevTiff;

	/// <summary> 
	/// Flag che indica se ridisegnare il background
	/// </summary> 
	BOOL m_bRedrawBack;

	/// <summary> 
	/// Flag salva immagine attuale
	/// </summary> 
	BOOL m_bSaveImage;

	/// <summary> 
	/// Flag salva immagine annullata
	/// </summary> 
	BOOL m_bSaveUndo;

	/// <summary> 
	/// Bottone luminosità
	/// </summary> 
	CBitmapButtonEx m_btnBright;

	/// <summary> 
	/// Bottone annulla modifiche
	/// </summary> 
	CBitmapButtonEx m_btnCancel;

	/// <summary> 
	/// Bottone contrasto
	/// </summary> 
	CBitmapButtonEx m_btnContra;

	/// <summary> 
	/// Bottone modulo elaborazione
	/// </summary> 
	CBitmapButtonEx m_btnElabor;

	/// <summary> 
	/// Bottone salva nuova immagine
	/// </summary> 
	CBitmapButtonEx m_btnSalNuo;

	/// <summary> 
	/// Bottone annulla ultima modifica
	/// </summary> 
	CBitmapButtonEx m_btnUndLas;

	/// <summary> 
	/// Bottone salva modifiche
	/// </summary> 
	CBitmapButtonEx m_btnUpdate;

	/// <summary> 
	/// Gestione localizzazione tasti
	/// </summary> 
	CButtonLocalize m_ctrlButtonEnhance;
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonShow1;
	CButtonLocalize m_ctrlButtonShow2;
	CButtonLocalize m_ctrlButtonShow3;

	/// <summary> 
	/// Frame contenente immagine della sagoma
	/// </summary> 
	CStatic m_ctrlFrameSagoma;

	/// <summary> 
	/// Frame contenente la sede
	/// </summary> 
	CStatic m_ctrlFrameSede;

	/// <summary> 
	/// Frame contenente immagine
	/// </summary> 
	CStatic m_ctrlImage;

	/// <summary> 
	/// Scrollbar orizzontale
	/// </summary> 
	CScrollBar m_ctrlScrollH;

	/// <summary> 
	/// Scrollbar verticale
	/// </summary> 
	CScrollBar m_ctrlScrollV;

	/// <summary> 
	/// Gestione localizzazione etichette
	/// </summary> 
	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStatic m_ctrlStaticSede;
	CStaticLocalize m_ctrlStaticView;

	/// <summary> 
	/// Dimensioni e posizione frame
	/// </summary> 
	CRect m_DibRectScreen;

	/// <summary> 
	/// Dimensioni immagine
	/// </summary> 
	CRect m_DibRectSource;

	/// <summary> 
	/// Immagine della sagoma
	/// </summary> 
	CDib m_dibSagome;

	/// <summary> 
	/// Tasto per esportazione di un singolo frame
	/// </summary> 
	CButtonLocalize m_ExportFrameButton;

	/// <summary> 
	/// Bottone prima immagine
	/// </summary> 
	CBitmapButtonEx m_FrstButton;

	/// <summary> 
	/// Handle al modulo remoto
	/// </summary> 
	HMODULE m_hModule;

	/// <summary> 
	/// Lista immagini esame attuale
	/// </summary> 
	CImgListOrgani m_ImgListOrgani;

	/// <summary> 
	/// Bottone ultima immagine
	/// </summary> 
	CBitmapButtonEx m_LastButton;

	/// <summary> 
	/// Frame corrente all'interno del multipagina
	/// </summary> 
	long m_lCurTiffPage;

	/// <summary> 
	/// ID Esame
	/// </summary> 
	long m_lEsame;

	/// <summary> 
	/// ID immagine visualizzata
	/// </summary> 
	long m_lID;
	int m_iType;

	/// <summary> 
	/// Lista contentente i punti
	/// </summary> 
	CList <tagPunti> m_listPunti;

	/// <summary> 
	/// Numero immagine di Dermox
	/// </summary> 
	long m_lNumeroDermox;

	/// <summary> 
	/// ID Paziente
	/// </summary> 
	long m_lPaziente;

	/// <summary> 
	/// Numero totale di frames contenuti nel TIFF multipagina
	/// </summary> 
	long m_lTotTiffPages;

	/// <summary> 
	/// Altezza dell'immagine
	/// </summary> 
	int m_nBMPHeight;

	/// <summary> 
	/// Larghezza dell'immagine
	/// </summary> 
	int m_nBMPWidth;

	/// <summary> 
	/// Altezza della finestra
	/// </summary> 
	int m_nDLGHeight;

	/// <summary> 
	/// Larghezza della finestra
	/// </summary> 
	int m_nDLGWidth;

	/// <summary> 
	/// Tasto immagine successiva
	/// </summary> 
	CBitmapButtonEx m_NextButton;

	/// <summary> 
	/// Tasto frame successivo
	/// </summary> 
	CBitmapButtonEx m_NextTiffButton;

	/// <summary> 
	/// Progressivo immagine all'interno dell'esame
	/// </summary> 
	int m_nNumPage;

	/// <summary> 
	/// Altezza immagine
	/// </summary> 
	int m_nTGAHeight;

	/// <summary> 
	/// Larghezza immagine
	/// </summary> 
	int m_nTGAWidth;

	/// <summary> 
	/// Numero totali immagini esame
	/// </summary> 
	int m_nTotPage;

	/// <summary> 
	/// Gestore immagine
	/// </summary> 
	CDib* m_pDib;

	/// <summary> 
	/// Gestore immagine per annullare l'ultima modifica
	/// </summary> 
	CDib* m_pDibUndo;

	/// <summary> 
	/// Tasto immagine precedente
	/// </summary> 
	CBitmapButtonEx m_PrevButton;

	/// <summary> 
	/// Tasto frame precedente
	/// </summary> 
	CBitmapButtonEx m_PrevTiffButton;

	/// <summary> 
	/// Tasto stampa tutti i frame
	/// </summary> 
	CButtonLocalize m_PrintAllButton;

	/// <summary> 
	/// Tasto stampa frame corrente
	/// </summary> 
	CButtonLocalize m_PrintOneButton;

	/// <summary> 
	/// Punto sulla sagoma
	/// </summary> 
	CPoint m_ptSagome;

	/// <summary> 
	/// Dimensione del frame della sagoma
	/// </summary> 
	CRect m_rectFrameSagoma;

	/// <summary> 
	/// Dimensione dell'immagine della sagoma
	/// </summary> 
	CRect m_rectPaintSagoma;

	/// <summary> 
	/// Puntatori alle funzioni per la visualizzazione remota
	/// </summary> 
	ENABLEVIDEOOUTPUTPTR XRClient_EnableVideoOutput;
	GETERROROCCURREDPTR XRClient_GetErrorOccurred;
	GETVIDEOINPUTPTR XRClient_GetVideoInput;
	PLAYPTR XRClient_Play;
	STOPPLAYPTR XRClient_StopPlay;

	void OpenImgFullscreen(); //Gabriel BUG 6225 - Lista DO FIX
};

#endif /* _IMAGEDLG_H_ */