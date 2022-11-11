#ifndef _ESAMISET_H_
	#define _ESAMISET_H_

#include "BaseSet.h"
#include "EsamiMielogrammaSet.h"
#include "EsamiPersonalizzabiliSet.h"
#include "RefertoIntegratoSet.h" //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture

class CRefertoForm;

/// <summary> 
/// Oggetto dati esame
/// Rappresenta la tabella esami; è collegata 1 a molti tramite 
/// il campo paziente con la tabella pazienti (contatore)
/// L'oggetto è utilizzato anche per il salvataggio dei dati
/// di default di un esame passando l'opportuna valore durante
/// la costruzione dell'oggetto
/// </summary> 
class CEsamiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiSet)

public:

	/// <summary> 
	/// Costruttore
	/// </summary> 
	/// <param name="bDefaultFieldSet">TRUE se serve per salvare valori di default esame</param> 
	CEsamiSet(BOOL bDefaultFieldSet = FALSE);

	/// <summary> 
	/// Oggetto tabella collegata contenente campi aggiuntivi esame (collegato 1 a 1 con questo oggetto)
	/// </summary> 
	CEsamiPersonalizzabiliSet m_setEP;
	CEsamiMielogrammaSet m_setEM;
	
	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	CRefertoIntegratoSet m_setRI;

	/// <summary> 
	/// Svuota i campi
	/// </summary> 
	void SetFieldNull(void* pv, BOOL bNull = TRUE);

	/// <summary> 
	/// Ridefinizione metodo aggiunta recordset;
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL AddNewRecordset(const CString &strCommento);

	/// <summary> 
	/// Ridefinizione metodo chiusura recordset; 
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL CloseRecordset(const CString &strCommento);

	/// <summary> 
	/// Ridefinizione metodo modifica recordset;
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL EditRecordset(const CString &strCommento);

	/// <summary> 
	/// Ridefinizione metodo annulla modifica recordset;
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL NoEditRecordset(const CString &strCommento);

	/// <summary> 
	/// Ridefinizione metodo apertura recordset;
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL OpenRecordset(const CString &strCommento);

	/// <summary> 
	/// Ridefinizione metodo riapertura recordset;
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL RecordsetReOpen(BOOL &bError, const CString &strFilter, const CString &strSort, const CString &strCommento);

	/// <summary> 
	/// Ridefinizione metodo aggiornamento dati recordset;
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL RefreshRecordset();

	/// <summary> 
	/// Ricerca all'interno del recordset l'esame con l'identificativo passato
	/// </summary> 
	/// <param name="lContatore">id esame</param> 
	/// <returns>ricerca ha avuto successo</returns>
	BOOL GotoExam(long lContatore);

	/// <summary> 
	/// Ridefinizione metodo cancellazione record; in realtà il record
	/// viene segnalato come eliminato
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL DeleteRecordset(const CString &strCommento);

	/// <summary> 
	/// Imposta un filtro di base per l'oggetto corrente
	/// </summary> 
	/// <param name="strFilter">filtro tabella pazienti</param> 
	/// <returns>filtro precedentemente impostato</returns>
	CString SetBaseFilter(const CString &strFilter);

	/// <summary> 
	/// Ridefinizione metodo salvataggio recordset;
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL UpdateRecordset(const CString &strCommento);
	BOOL UpdateRecordsetAPStato(const CString &strCommento, BOOL waitingForGroupNumber);

	/// <summary>
	/// Metodo per annullare la convalida dell'esame
	/// </summary>
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL AnnullaConvalidaEsame();

	/// <summary>
	/// Metodo per convalidare l'esame
	/// </summary>
	/// <param name="closeTime">ora di convalida esame</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL ConvalidaEsame(CString sTime);

	/// <summary>
	/// Metodo per chiudere l'esame
	/// </summary>
	/// <param name="sCloseTime">ora di chiusura esame</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL ChiudiEsame(CString sCloseTime, CRefertoForm* pRefertoForm);
	BOOL ChiudiEsameIntegrato(long lIDEsame, CString sCloseTime);

	/// <summary>
	/// Metodo per flaggare l'esame per l'invio alla centrale di refertazione
	/// </summary>
	BOOL FlaggaEsameInviareCentraleRefertazione();

	/// <summary>
	/// Metodo per sbloccare l'esame
	/// </summary>
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL SbloccaEsame(CWnd* pParent);

	/// <summary>
	/// Metodo per annullare una chiusura di un esame appena effettuata
	/// </summary>
	/// <param name="lIDEsameChiuso">ID della tabella ext_esami_chiusi</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL AnnullaChiusura(CWnd* pParent, const long lIDEsameChiuso);

	/// <summary>
	/// Dato un ID esame, ritorna la data in cui è stato creato
	/// </summary>
	/// <param name="lIDEsame">ID dell'esame</param> 
	/// <returns>stringa formattata con la data dell'esame</returns>
	CString GetDataEsame(long lIDEsame);

	/// <summary>
	/// Dato un contatore esame, torna il tipo
	/// </summary>
	/// <param name="lContatore">contatore dell'esame</param> 
	/// <returns>il tipo dell'esame</returns>
	long GetTipoEsame(long lContatore);

	/// Sandro 20/09/2013 // RAS 20130152 ///
	/// BOOL MedicoHasEsamiAperti(long lIDMedico);

	/// <summary>
	/// Utilizzato dal disegna interfaccia operatore, reimposta ad 1 l'interfaccia di TUTTI gli esami
	/// </summary>
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL ResetVersionID();

	/// <summary>
	/// Dato un contatore esame, torna il numero di protocollo INPS
	/// </summary>
	/// <param name="lContatore">contatore dell'esame</param> 
	/// <returns>numero di protocollo</returns>
	CString GetNumeroProtocolloINPS(long lContatore);

	/// <summary>
	/// Dato un contatore esame, ritorna TRUE se l'esame è sbloccabile
	/// </summary>
	/// <param name="lContatore">contatore dell'esame</param> 
	/// <returns>TRUE se l'esame è sbloccabile</returns>
	BOOL EsameSbloccabile(long lContatore);

	/// <summary>
	/// Dato un contatore esame, ritorna TRUE se la chiusura dell'esame è bloccata da un integrazione
	/// </summary>
	/// <param name="lContatore">contatore dell'esame</param> 
	/// <returns>TRUE se la chiusura è bloccata</returns>
	BOOL GetChiusuraBloccataDaIntegrazione(long lContatore);

	/// <summary>
	/// Setta il blocco sulla chiusura
	/// </summary>
	/// <returns>TRUE se l'operazione è andata a buon fine</returns>
	BOOL SetChiusuraBloccataDaIntegrazione();

	//
	void SetIDProtocolloUsato(long lContatore, long lIDProtocolloUsato);

	/// <summary> 
	/// Ridefinizione metodo sposta al primo record;
	/// </summary> 
	void MoveFirst();

	/// <summary> 
	/// Ridefinizione metodo sposta al record precedente;
	/// </summary> 
	void MovePrev();

	/// <summary> 
	/// Ridefinizione metodo sposta al record successivo;
	/// </summary> 
	void MoveNext();

	/// <summary> 
	/// Ridefinizione metodo sposta all'ultimo record;
	/// </summary> 
	void MoveLast();

	///
	long GetLastPatientExam(long lIDPaziente);

	///
	long GetPaziente(long lIDEsame);
	long GetUO(long lIDEsame);

	/// <summary> 
	/// Campo identificativo esame
	/// </summary> 
	long m_lContatore;

	/// <summary> 
	/// Campo ricovero associato all'esame
	/// </summary> 
	CString m_sRicovero;

	/// <summary> 
	/// Campo codice esame
	/// </summary> 
	CString m_sCodEsame;

	/// <summary> 
	/// Campo identificativo paziente
	/// </summary> 
	long m_lPaziente;

	/// <summary> 
	/// Campo tipo esame - collegato tabella ETipiEsami
	/// </summary> 
	long m_lIDEsame;

	/// <summary> 
	/// Campo data inserimento esame - codificato con CustomDate
	/// </summary> 
	long m_lData;

	/// <summary> 
	/// Campo medico
	/// </summary> 
	long m_lMedico;
	CString m_sMedicoLibero;

	/// <summary>
	/// Campo assistente
	/// </summary>
	long m_lAssistente;
	CString m_sAssistenteLibero;

	/// <summary>
	/// Campo anestesista
	/// </summary>
	CString m_sAnestesista;

	/// <summary>
	/// Campo primo infermiere
	/// </summary>
	long m_lInfermiere1;

	/// <summary>
	/// Campo secondo infermiere
	/// </summary>
	long m_lInfermiere2;

	/// <summary>
	/// Campo terapia
	/// </summary>
	CString m_sTerapia;

	/// <summary>
	/// Campo data prossimo controllo
	/// </summary>
	long m_lDataControllo;

	/// <summary>
	/// Campo durata esame
	/// </summary>
	long m_lDurata;

	/// <summary>
	/// Campo difficoltà esame
	/// </summary>
	long m_lDifficolta;

	/// <summary>
	/// Campo conclusioni esame
	/// </summary>
	CString m_sConclusioni;

	/// <summary>
	/// Campo integrazioni all'esame
	/// </summary>
	CString m_sIntegrazioni;

	/// <summary>
	/// Campo appunti sull'esame
	/// </summary>
	CString m_sAppunti;

	/// <summary>
	/// Campo indicazioni all'esame
	/// </summary>
	CString m_sIndicazioni;

	/// <summary>
	/// Campo farmaco trial
	/// </summary>
	CString m_sFarmacoTrial;

	/// <summary>
	/// Campo tipo di studio
	/// </summary>
	CString m_sStudio;

	/// <summary>
	/// Campo tipo di visita
	/// </summary>
	CString m_sTipoVisita;

	/// <summary>
	/// Campo ID premedicazione
	/// </summary>
	long m_lIdPremedicazione;

	/// <summary>
	/// Campo testo premedicazioni
	/// </summary>
	CString m_sPremedicazioni;

	/// <summary>
	/// Campo strumenti
	/// </summary>
	CString m_sStrumenti;

	/// <summary>
	/// Campo accessori
	/// </summary>
	CString m_sAccessori;

	/// <summary>
	/// Campo progressivo per anno
	/// </summary>
	CString m_sProgressivoAnno;

	/// <summary>
	/// Campo codice prenotazione
	/// </summary>
	CString m_sCodicePrenotazione;

	/// <summary>
	/// Campo valutazione
	/// </summary>
	CString m_sValutazione;

	/// <summary>
	/// Campo complicanze
	/// </summary>
	CString m_sComplicanzeOld;

	/// <summary>
	/// Campo guarigione
	/// </summary>
	CString m_sGuarigione;

	/// <summary>
	/// Campo quadro complessivo
	/// </summary>
	CString m_sQuadro;

	/// <summary>
	/// Campo metodo
	/// </summary>
	CString m_sMetodo;

	/// <summary>
	/// Campo estensione
	/// </summary>
	CString m_sEstensione;

	/// <summary>
	/// Campo procedure terapeutiche
	/// </summary>
	CString m_sProcTerapeutiche;

	/// <summary>
	/// Campo procedure diagnostiche
	/// </summary>
	CString m_sProcDiagnostiche;

	/// <summary>
	/// Campo complicanze
	/// </summary>
	CString m_sMstComplicanze1;

	/// <summary>
	/// Campo complicanze
	/// </summary>
	CString m_sMstComplicanze2;

	/// <summary>
	/// Campo complicanze
	/// </summary>
	CString m_sMstComplicanze3;

	/// <summary>
	/// Campo provenienza
	/// </summary>
	long m_lProvenienza;

	/// <summary>
	/// Campo inviante
	/// </summary>
	long m_lInviante;

	/// <summary>
	/// Campo camera
	/// </summary>
	long m_lCamera;

	/// <summary>
	/// Campo medico inviante
	/// </summary>
	CString m_sInvMedico;

	/// <summary>
	/// Campo ID medico inviante
	/// </summary>
	long m_lInvMedico; // non cancellare, serve per gli interfacciamenti, capito Sandrella??? // a scanceo tuto mi, gheto capio Silvanooo!!! :-D //

	/// <summary>
	/// Campo anamnesi fumo
	/// </summary>
	long m_lFumo;

	/// <summary>
	/// Campo anamnesi sigarette
	/// </summary>
	long m_lSigarette;

	/// <summary>
	/// Campo anamnesi caffè
	/// </summary>
	long m_lCaffe;

	/// <summary>
	/// Campo anamnesi alcol
	/// </summary>
	long m_lAlcool;

	/// <summary>
	/// Campo anamnesi alcolici
	/// </summary>
	long m_lSuperAlcolici;

	/// <summary>
	/// Campo anamnesi farmaci
	/// </summary>
	CString m_sDenFarmaci;

	/// <summary>
	/// Campo anamnesi assunzione
	/// </summary>
	long m_lAssunzione;

	/// <summary>
	/// Campo anamnesi peso
	/// </summary>
	float m_fPeso;

	/// <summary>
	/// Campo anamnesi altezza
	/// </summary>
	float m_fAltezza;

	/// <summary>
	/// Campo anamnesi BMI
	/// </summary>
	float m_fBMI;

	//
	float m_fMisuraA;
	float m_fMisuraB;
	float m_fMisuraC;
	float m_fVolume;

	/// <summary>
	/// Campo anamnesi BSA
	/// </summary>
	float m_fBSA;

	/// <summary>
	/// Campo complicanze
	/// </summary>
	CString m_sComplicanze1;

	/// <summary>
	/// Campo complicanze
	/// </summary>
	CString m_sComplicanze2;

	/// <summary>
	/// Campo complicanze
	/// </summary>
	CString m_sComplicanze3;

	/// <summary>
	/// Campo ID versione interfaccia operatore
	/// </summary>
	long m_lIDVersione;

	/// <summary>
	/// Campo note monitoraggio
	/// </summary>
	CString m_sNoteMonitoraggio;

	/// <summary>
	/// Campo infermiere monitoraggio
	/// </summary>
	long m_lInfermiereMonitoraggio;

	/// <summary>
	/// Campo ospedale
	/// </summary>
	long m_lOspedale;

	/// <summary>
	/// Campo codice RAO
	/// </summary>
	int m_nCodiceRAO;

	/// <summary>
	/// Campo concordanza RAO
	/// </summary>
	BOOL m_bConcordanza;

	/// <summary>
	/// Campo codice RAO specialista
	/// </summary>
	int m_nCodiceRAOSpec;

	/// <summary>
	/// Campo consenso informato
	/// </summary>
	int m_iConsensoInformato;

	/// <summary>
	/// Campo note consenso informato
	/// </summary>
	CString m_sNoteConsensoInformato;

	/// <summary>
	/// Campo allergie
	/// </summary>
	int m_iAllergie;

	/// <summary>
	/// Campo descrizione allergie
	/// </summary>
	CString m_sDescrizioneAllergie;

	/// <summary>
	/// Campo pacemaker
	/// </summary>
	int m_iPacemaker;

	/// <summary>
	/// Campo descrizione pacemaker
	/// </summary>
	CString m_sDescrizionePacemaker;

	/// <summary>
	/// Campo anticoagulanti
	/// </summary>
	int m_iAnticoagulanti;

	/// <summary>
	/// Campo descrizione anticoagulanti
	/// </summary>
	CString m_sDescrizioneAnticoagulanti;

	/// <summary>
	/// Campo antiaggreganti
	/// </summary>
	int m_iAntiaggreganti;

	/// <summary>
	/// Campo descrizione antiaggreganti
	/// </summary>
	CString m_sDescrizioneAntiaggreganti;

	/// <summary>
	/// Campo breath test HP
	/// </summary>
	int m_iBreathTestHP;

	/// <summary>
	/// Campo valore 1 del breath test HP
	/// </summary>
	float m_fBreathTestHPVal1;

	/// <summary>
	/// Campo valore 2 del breath test HP
	/// </summary>
	float m_fBreathTestHPVal2;

	/// <summary>
	/// Campo valore differenza del breath test HP
	/// </summary>
	float m_fBreathTestHPDiff;

	/// <summary>
	/// Campo ID sede esame
	/// </summary>
	long m_lIDSedeEsame;

	/// <summary>
	/// Campo sala esame
	/// </summary>
	CString m_sSalaEsame;

	/// <summary>
	/// Campo tipo di degenza interno
	/// </summary>
	long m_lTipoDegenzaInterno;

	/// <summary>
	/// Campo tipo di degenza esterno
	/// </summary>
	long m_lTipoDegenzaEsterno;

	/// <summary>
	/// Campo minuti fluoroscopia
	/// </summary>
	long m_lFluoroscopiaMinuti;

	/// <summary>
	/// Campo secondi fluoroscopia
	/// </summary>
	long m_lFluoroscopiaSecondi;

	/// <summary>
	/// Campo descrizione fluoroscopia
	/// </summary>
	float m_fFluoroscopiaDose;

	/// <summary>
	/// Flag che indica se l'esame è stato firmato
	/// </summary>
	BOOL m_bFirmato;

	/// <summary>
	/// Flag che indica se l'esame risulta chiuso
	/// </summary>
	BOOL m_bLocked;

	/// <summary>
	/// Campo utente che ha chiuso l'esame
	/// </summary>
	long m_lIdUtenteLock;

	/// <summary>
	/// Campo data/ora chiusura
	/// </summary>
	CString m_sDataOraLock;

	/// <summary>
	/// Campo ID sede prevista
	/// </summary>
	long m_lIDSedePrevista; // serve per gli interfacciamenti, NON RIMUOVERE! //

	/// <summary>
	/// Campo descrizione sede prevista
	/// </summary>
	CString m_sSedePrevista;

	/// <summary>
	/// Campo ID sede raggiunta
	/// </summary>
	long m_lIDSedeRaggiunta; // serve per gli interfacciamenti, NON RIMUOVERE! //

	/// <summary>
	/// Campo descrizione sede raggiunta
	/// </summary>
	CString m_sSedeRaggiunta;

	/// <summary>
	/// Campo data invio richiesta ad AP
	/// </summary>
	CString m_sAPDataInvio;

	/// <summary>
	/// Campo operatore invio ad AP
	/// </summary>
	CString m_sAPOperInvio;

	/// <summary>
	/// Campo data annullamento richiesta AP
	/// </summary>
	CString m_sAPDataAnnullamento;

	/// <summary>
	/// Campo operatore annullamento richiesta AP
	/// </summary>
	CString m_sAPOperAnnullamento;

	/// <summary>
	/// Campo data ricezione risultato AP
	/// </summary>
	CString m_sAPDataRicezione;

	/// <summary>
	/// Campo data conferma
	/// </summary>
	CString m_sAPDataConferma;

	/// <summary>
	/// Campo operatore conferma
	/// </summary>
	CString m_sAPOperConferma;

	/// <summary>
	/// Campo stato richiesta anatomia
	/// </summary>
	long m_lAPStato;

	/// <summary>
	/// Campo motivazione rifiuto richiesta
	/// </summary>
	CString m_sAPMotivazioneRifiuto;

	/// <summary>
	/// Campo descrizione richiesta AP
	/// </summary>
	CString m_sAPDescrizioneRichiesta;

	/// <summary>
	/// Campo risposta codificata AP
	/// </summary>
	CString m_sAPRispostaCodificata;

	/// <summary>
	/// Campo risposta libera AP
	/// </summary>
	CString m_sAPRispostaLibera;

	/// <summary>
	/// Campo referto PDF AP
	/// </summary>
	CString m_sAPRefertoPDF;

	/// <summary>
	/// Campo suggerimenti pre referto AP
	/// </summary>
	CString m_sAPSuggerimenti1;

	/// <summary>
	/// Campo suggerimenti post referto AP
	/// </summary>
	CString m_sAPSuggerimenti2;

	/// <summary>
	/// Campo ID richiesta AP
	/// </summary>
	CString m_sAPIDRichiesta;

	/// <summary>
	/// Campo che indica se spedire il referto di AP
	/// </summary>
	int m_nAPSpedireRitirare;

	/// <summary>
	/// Flag che indica se il referto di AP è emesso
	/// </summary>
	BOOL m_bAPRefertato;

	/// <summary>
	/// Flag che indica se l'endoscopista ha verificato il referto di AP
	/// </summary>
	BOOL m_bAPVerificato;

	/// <summary>
	/// Campo referto AP verificato dal medico
	/// </summary>
	int m_nAPVerificatoMedico;

	/// <summary>
	/// Flag che indica se il referto è stato spedito
	/// </summary>
	BOOL m_bAPSpeditoRitirato;

	/// <summary>
	/// Campo data verifica referto AP
	/// </summary>
	CString m_sAPDataVerificato;

	/// <summary>
	/// Campo data spedizione referto AP
	/// </summary>
	CString m_sAPDataSpeditoRitirato;

	/// <summary>
	/// Campo provenienza richiesta AP
	/// </summary>
	CString m_sAPProvenienza;

	/// <summary>
	/// Campo convenzione AP
	/// </summary>
	CString m_sAPConvenzione;

	/// <summary>
	/// Campo indirizzo a cui spedire il referto di AP
	/// </summary>
	CString m_sAPIndirizzo;

	/// <summary>
	/// Campo che indica se sono presenti prelievi istologico
	/// </summary>
	int m_nAPEseguitiPrelievi;

	/// <summary>
	/// Campo ID della ricetta associata alla richiesta AP
	/// </summary>
	long m_lAPIdRicetta;

	/// <summary>
	/// Campo numero gruppo AP
	/// </summary>
	CString m_sAPGroupNumber;

	/// <summary>
	/// Campo ID complicanze immediate
	/// </summary>
	long m_lIDComplicanzeImmediate;

	/// <summary>
	/// Campo ID complicanze tardive
	/// </summary>
	long m_lIDComplicanzeTardive;

	/// <summary>
	/// Campo ID pulizia
	/// </summary>
	long m_lIDPulizia;

	/// <summary>
	/// Campo ID causa non completamento
	/// </summary>
	long m_lIDCausaNonCompleto;

	/// <summary>
	/// Flag che indica se necessita assistenza ospedaliera
	/// </summary>
	BOOL m_bNecAssistenzaOspedaliera;

	/// <summary>
	/// Campo ID tolleranza
	/// </summary>
	long m_lIDTolleranza;

	/// <summary>
	/// Campo posologia premedicazione
	/// </summary>
	CString m_sPremedPosologia;

	/// <summary>
	/// Campo ID conclusioni (per screening)
	/// </summary>
	long m_lIDConclusioniScreening;

	/// <summary>
	/// Campo ID conclusioni colon
	/// </summary>
	long m_lIDConclusioniColon;

	/// <summary>
	/// Flag che indica la presenza di una lesione sospetta per CCR (screening)
	/// </summary>
	BOOL m_bPresenzaLesioneCCR;

	/// <summary>
	/// Campo ID altre anomalie screening
	/// </summary>
	long m_lIDAltreAnomalie;

	/// <summary>
	/// Flag che indica se l'esame è chiuso
	/// </summary>
	BOOL m_bSuperLocked;

	/// <summary>
	/// Campo ID utente che ha chiuso l'esame
	/// </summary>
	long m_lIdUtenteSuperLock;

	/// <summary>
	/// Campo data chiusura esame
	/// </summary>
	CString m_sDataOraSuperLock;
	CString m_sDataOraSuperLockPrimo;

	/// <summary>
	/// Flag che indica l'invio allo screening
	/// </summary>
	BOOL m_bInviatoScreening;

	/// <summary>
	/// Campo ID diagnosi finale
	/// </summary>
	long m_lIDDiagnosiFinale;

	/// <summary>
	/// Campo sospensione esame
	/// </summary>
	int m_iSospeso;

	/// <summary>
	/// Campo data scadenza sospensione
	/// </summary>
	long m_lDataScadenzaSospensione;

	/// <summary>
	/// Campo motivo sospensione
	/// </summary>
	CString m_sMotivoSospensione;

	/// <summary>
	/// Campo data acquisizione immagini
	/// </summary>
	CString m_sDataOraAcquisizione;

	/// <summary>
	/// Campo tempo per la convalida
	/// </summary>
	CString m_sTempoConvalida;

	/// <summary>
	/// Campo tempo per la chiusura
	/// </summary>
	CString m_sTempoChiusura;

	/// <summary>
	/// Campo ora inizio acquisizione
	/// </summary>
	long m_lCustomDataOraInizioAcq;

	/// <summary>
	/// Campo ora fine acquisizione
	/// </summary>
	long m_lCustomDataOraFineAcq;

	/// <summary>
	/// Campi pressione sanguigna
	/// </summary>
	CString m_sPressione1;
	CString m_sPressione2;

	/// <summary>
	/// Campo certificato inviato all'inps
	/// </summary>
	BOOL m_bInviatoInps;

	/// <summary>
	/// Campo data inizio certificato
	/// </summary>
	long m_lInpsDataInizio;

	/// <summary>
	/// Campo data fine certificato
	/// </summary>
	long m_lInpsDataFine;

	/// <summary>
	/// Campo tipo certificato INPS
	/// </summary>
	int m_iInpsTipo;

	/// <summary>
	/// Campo note INPS
	/// </summary>
	CString m_sInpsNote;

	/// <summary>
	/// Campo cognome INPS
	/// </summary>
	CString m_sInpsCognome;

	/// <summary>
	/// Campo via INPS
	/// </summary>
	CString m_sInpsVia;

	/// <summary>
	/// Campo CAP INPS
	/// </summary>
	CString m_sInpsCap;

	/// <summary>
	/// Campo comune INPS
	/// </summary>
	CString m_sInpsComune;

	/// <summary>
	/// Campo provincia INPS
	/// </summary>
	CString m_sInpsProvincia;

	/// <summary>
	/// Campo numero protocollo assegnato al certificato dall'inps
	/// </summary>
	CString m_sInpsNumeroProtocollo;

	/// <summary>
	/// Campo id annullamento assegnato al certificato dall'inps in caso di annullamento
	/// </summary>
	CString m_sInpsIdAnnullamento;

	/// <summary>
	/// Campi utilizzati per la firma digitale SISS
	/// </summary>
	BOOL m_bSissOscuramento10;
	BOOL m_bSissOscuramento20;
	BOOL m_bSissOscuramento30;
	BOOL m_bSissOscuramento40;
	BOOL m_bSissOscuramento50;
	BOOL m_bSissOscuramento50Bloccato;
	BOOL m_bSissAutorizzazioneConsultaz;
	CString m_sSissNoteReperibilita;

	/// <summary> 
	/// Campo id episodio ricovero (barcode)
	/// </summary> 
	CString m_sIdEpisodioRicovero;

	/// <summary>
	/// Campo data ricovero
	/// </summary>
	long m_lDataRicoveroCustom;

	/// <summary>
	/// Campo contenente l'ID della malattia cronica
	/// </summary>
	long m_lIDMalattiaCronica;

	/// <summary>
	/// Indica se il record (l'esame) NON è associato ad un accesso del paziente
	/// </summary>
	BOOL m_bRecordSenzaAccesso;

	/// <summary>
	/// Contiene l'id di registrazione della videocapsula se questa è stata registrata //
	/// </summary>
	//long m_lIDVideocapsulaRegistrata;

	/// <summary>
	/// Contiene lo score HB del paziente cronico //
	/// </summary>
	CString m_sPazientiCroniciScoreHB;

	/// <summary>
	/// Contiene lo score S (mayo) del paziente cronico //
	/// </summary>
	CString m_sPazientiCroniciScoreS;

	/// <summary>
	/// Contiene l'ID dello studio //
	/// </summary>
	long m_lIDStudio;

	/// <summary>
	/// Contiene la data di inizio dello studio //
	/// </summary>
	long m_lDataStudio;

	/// <summary>
	/// Contiene l'ID dell'utente che ha creato l'esame //
	/// </summary>
	long m_lIDUtenteInserimentoEsame;

	/// <summary>
	/// Campo di screening, data del referto istologico
	/// </summary>
	long m_lDataRefertoIstologico;

	/// <summary>
	/// Campo di screening, presenza lesione sospetta per CCR
	/// </summary>
	BOOL m_bPresenzaLesioneSospettaCCR;

	/// <summary>
	/// Campo di screening, numero totale dei polipi individuati
	/// </summary>
	long m_lNumeroTotalePolipi;

	/// <summary>
	/// Campi contenenti i Boston score
	/// </summary>
	long m_lBostonScoreDx;
	long m_lBostonScoreMid;
	long m_lBostonScoreSx;

	/// <summary>
	/// Tempo di retrazione (in secondi)
	/// </summary>
	long m_lTempoRetrazione;

	/// <summary>
	/// Esenzione ricevuta dall'integrazione
	/// </summary>
	CString m_sEsenzioneDaIntegrazione;

	/// <summary>
	/// Pagamento ricevuto
	/// </summary>
	BOOL m_bPagamentoRicevuto;

	/// <summary>
	/// Flag che identifica che l'esame non è più riapribile	
	/// </summary>
	BOOL m_bNonSbloccabile;

	/// <summary>
	/// Campi del referto
	/// </summary>
	CString m_sRefertoTestoRtf;
	CString m_sRefertoTestoTxt;
	CString m_sRefertoTestoHtml;
	CString m_sRefertoDataOra;
	long m_lRefertoRedattore;
	BOOL m_bRefertoScaduto;
	long m_lRefertoStato;

	/// <summary>
	/// Flag che indica che la chiusura dell'esame è bloccata a causa dell'attesa di un input solitamente da integrazione esterna	
	/// </summary>
	BOOL m_bChiusuraBloccataDaIntegrazione;

	/// <summary>
	/// Campo nuova provenienza. Identifica un livello superiore della provenienza, che riconduce alla vecchia m_lProvenienza per determinare se INTERNO o ESTERNO
	/// </summary>
	long m_lIdProvenienzaNew;

	/// <summary>
	/// Stato invio a centrale di refertazione 0: non inviare, 1: da inviare, 2: inviato
	/// </summary>
	long m_lStatoInvioCentraleRefertaz;

	/// <summary>
	/// Stato invio a centrale di refertazione 0: non inviare, 1: da inviare, 2: inviato
	/// </summary>
	long m_lStatoInvioControlloQualita;

	/// <summary>
	/// Versione delle GridCL utilizzata per questo esame
	/// </summary>
	long m_lVersioneGridCL;

	/// <summary>
	/// Flag esame eliminato
	/// </summary>
	BOOL m_bEliminato;

	/// <summary>
	/// Campo unità operativa
	/// </summary>
	long m_lUO;

	/// <summary>
	/// Campo contenente il numero dell'esame corrente
	/// campo non scambiato col DB //
	/// </summary>
	long m_lNumEsame;

	/// <summary>
	/// Flag che avvisa se il distretto dell'esame è il nostro
	/// campo non scambiato col DB //
	/// </summary>
	BOOL m_bStessoDistretto;	

	/// <summary>
	/// Indicatore del livello d'urgenza dell'esame
	/// </summary>
	long m_lLivelloUrgenza;

	/// <summary>
	/// Indicatore della frazione di eiezione (personalizzazione Brasile Sirio)
	/// </summary>
	long m_lFrazioneEiezione;

	/// <summary>
	/// Quesito diagnostico
	/// </summary>
	CString m_sQuesitoDiagnostico;

	/// <summary>
	/// Quesito diagnostico codificato
	/// </summary>
	CString m_sQuesitoDiagnosticoCodificato;

	/// <summary>
	/// ID dell'ultima checklist utilizzata
	/// </summary>
	long m_lIDUltimaChecklistUsata;
	
	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	/// <summary>
	/// Campo medico inviante/solicitante 2
	/// </summary>
	CString m_sInvMedico2;

	/// <summary>
	/// Campo ID medico inviante/solicitante 2
	/// </summary>
	long m_lInvMedico2; 

	/// <summary>
	/// Campo medico inviante/solicitante 3
	/// </summary>
	CString m_sInvMedico3;

	/// <summary>
	/// Campo ID medico inviante/solicitante 3
	/// </summary>
	long m_lInvMedico3;

	/// <summary>
	/// Campo medico inviante/solicitante 4
	/// </summary>
	CString m_sInvMedico4;

	/// <summary>
	/// Campo ID medico inviante/solicitante 4
	/// </summary>
	long m_lInvMedico4;
	//
	CString m_sFCMassima;
	CString m_sFCSubmassima;
	long m_lIDProtocolloUsato;

	//
	CString m_sRefertoConiugatoPrincipale;
	CString m_sRefertoConiugatoSecondario;
	BOOL m_bRefertoConiugatoAltraUO;
	BOOL m_bRefertoConiugatoImportato;

	CString m_sFleuryTrasferito;
	CString m_sFleuryEndpointRemoto;

	/// <summary>
	/// Flag que indica se o protocolo XXI já foi feito
	/// </summary>
	BOOL m_bHyperLocked;

	/// <summary>
	/// Campo ID utente que fez o protocolo XXI
	/// </summary>
	long m_lIdUtenteHyperLock;

	/// <summary>
	/// Campo data do protocolo XXI
	/// </summary>
	CString m_sDataOraHyperLock;

	/// <summary> 
	/// Copia il contenuto di un oggetto esame aggiuntivo all'attuale
	/// </summary> 
	/// <param name="pSet">oggetto paziente sorgente</param> 
	/// <param name="bEmpty">svuota l'oggetto corrente prima di cominciare la copia</param> 
	void CopyFieldFrom(CEsamiSet* pSet, BOOL bEmpty = TRUE);

	/// <summary> 
	/// Ritorna lo stato attuale del recordset
	/// (Vedi struttura EditMode all'interno della classe CRecordset)
	/// </summary> 
	/// <returns>stato attuale recordset</returns>
	int GetEditMode();

	/// <summary> 
	/// Svuota i dati contenuti all'interno dell'oggetto
	/// </summary> 
	void SetEmpty();

	/// <summary>
	/// Dato un contatore esame, torna l'id della videocapsula associata
	/// </summary>
	/// <param name="idEsame">contatore dell'esame</param> 
	/// <returns>id videocapsula</returns>
	//long GetIDVideocapsula(long lIDEsame);

	/// <summary>
	/// Controlla se il referto è modificabile oppure se è stato bloccato dal sistema
	/// </summary>
	BOOL IsRefertoUpdatable();

	/// <summary>
	/// Imposta il referto dell'esame e gli altri campi relativi
	/// </summary>
	void SetReferto(const CString &sRefertoRtf, const CString &sRefertoTxt, const CString &sRefertoHtml);

	//

	BOOL IsConiugatoPrincipale(long lID);
	BOOL IsConiugatoSecondario(long lID);

	BOOL IsConiugatoPrincipaleSecondario(CString sFichaItem);
	void SetConiugatoPrincipaleSecondario(CString sFichaItemPrincipale, CString sFichaItemSecondario, BOOL bAltraUO);
	void Desconjugar(CString sFichaItemPrincipale, CString sFichaItemSecondario);

	/// <summary>
	/// Metodo para chamar o protocolo XXI
	/// </summary>
	/// <param name="sTime">Hora do protocolo XXI</param> 
	void ProtocoloXXI(CString sTime);

	/// <summary>
	/// Metodo per annullare il Protocolo XXI
	/// </summary>
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL AnnullaProtocoloXXI();

	void GetMediciRichiedente(CString& sMedico, long& lArrayCount);

	//Gabriel - TCP
	/// <summary>
	/// Stato invio a altra unita 0: non inviare, 1: da inviare, 2: inviato
	/// </summary>
	long m_lStatoInvioAltraUnita;

	//Gabriel - TCP
	CString m_sRefertoTestoCorrelatiRtf;
	CString m_sRefertoTestoCorrelatiTxt;
	CString m_sRefertoTestoCorrelatiHtml;

	//Gabriel - TCP
	CString m_sCodesameCorrelati;

	/// <summary>
	/// Metodo per flaggare l'esame per l'invio alla altra unita
	/// </summary>
	BOOL FlaggaEsameInviaAltraUnita();

	BOOL m_bColumnsP3;

	//Gabriel - TCP
	BOOL m_bColumnsTCP;

	//Gabriel - TCP
	long GetContatore(CString sCodesame);

private:

	/// <summary> 
	/// Gestione scambio dati tra database / variabili e viceversa
	/// </summary> 
	/// <param name="pFX">oggetto usato internamente dal framework; non è modificabile</param> 
	virtual void DoFieldExchange(CFieldExchange* pFX);

	/// <summary> 
	/// Ritorna il nome della tabella
	/// </summary> 
	/// <returns>nome tabella (esami)</returns>
	virtual CString GetDefaultSQL();

	/// <summary> 
	/// Crea una nuova istanza di quest'oggetto
	/// Viene usato durante le operazioni di aggiunta/modifica da CBaseSet
	/// per la gestione automatica del log operazioni
	/// </summary> 
	/// <returns>nuovo oggetto</returns>
	virtual CBaseSet* CreateNew();

	/// <summary> 
	/// Copia il contenuto di un oggetto all'attuale
	/// Viene usato durante le operazioni di aggiunta/modifica da CBaseSet
	/// per la gestione automatica del log operazioni
	/// </summary> 
	/// <param name="pOriginalSet">oggetto paziente sorgente</param> 
	/// <param name="bCopyAll">copia tutti i dati senza controllare se sono validi</param> 
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);

	/// <summary> 
	/// Salva il log delle operazioni confrontando due recordset
	/// </summary> 
	/// <param name="pOldValues">oggetto prima modifiche</param> 
	/// <param name="pNewValues">oggetto dopo modifiche</param> 
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

	/// <summary>
	/// Flag oggetto usato per salvataggio profilo di default
	/// </summary>
	BOOL m_bDefaultFieldSet;

	//
	BOOL m_bUpdatingAPStato;
	BOOL m_bWaitingForGroupNumber;

};

#endif /* _ESAMISET_H_ */