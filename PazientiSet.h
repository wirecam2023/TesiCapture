#ifndef _PAZIENTISET_H_
#define _PAZIENTISET_H_

#include "BaseSet.h"

/// <summary> 
/// Oggetto pazienti
/// Rappresenta l'elenco dei pazienti
/// </summary> 
class CPazientiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CPazientiSet)

public:

	/// <summary> 
	/// Costruttore
	/// </summary> 
	CPazientiSet();

	/// <summary> 
	/// Campo identificativo
	/// </summary> 
	long m_lContatore;

	/// <summary> 
	/// Campo identificativo anagrafe esterna
	/// </summary> 
	CString m_sAssIden;

	/// <summary> 
	/// Campo codice alfanumerico associato al paziente
	/// </summary> 
	CString m_sCodAlfa;

	/// <summary> 
	/// Campo cognome
	/// </summary> 
	CString m_sCognome;

	/// <summary> 
	/// Campo nome
	/// </summary> 
	CString m_sNome;

	/// <summary> 
	/// Campo data di nascita codificato tramite CustomDate
	/// </summary> 
	long m_lNatoIlCustom;

	/// <summary> 
	/// Campo usato SOLO per la ricerca per data di nascita, non viene scambiato su DB
	/// </summary> 
	/// CString m_sNatoIlCustom; // Sandro 23/07/2013 //

	/// <summary> 
	/// Campo luogo di nascita
	/// </summary> 
	CString m_sNatoA;

	/// <summary> 
	/// Campo indirizzo di residenza
	/// </summary> 
	CString m_sVia;

	/// <summary> 
	/// Campo città di residenza
	/// </summary> 
	CString m_sCitta;

	/// <summary> 
	/// Campo CAP di residenza
	/// </summary> 
	CString m_sCAP;

	/// <summary> 
	/// Campo provincia di residenza
	/// </summary> 
	CString m_sProvincia;

	/// <summary> 
	/// Campo numero di telefono
	/// </summary> 
	CString m_sTelefono1;

	/// <summary> 
	/// Campo numero di telefono alternativo
	/// </summary> 
	CString m_sTelefono2;

	/// <summary> 
	/// Campo numero di fax
	/// </summary> 
	CString m_sFax;

	/// <summary> 
	/// Campo numero di telefono cellulare
	/// </summary> 
	CString m_sCellulare1;

	/// <summary> 
	/// Campo numero di telefono cellulare alternativo
	/// </summary> 
	CString m_sCellulare2;

	/// <summary> 
	/// Campo email
	/// </summary> 
	CString m_sEmail;

	/// <summary> 
	/// Campo codice fiscale
	/// </summary> 
	CString m_sCodFisc;

	/// <summary> 
	/// Campo codice sanitario
	/// </summary> 
	CString m_sCodSanit;

	/// <summary> 
	/// Campo sesso paziente (0 maschio, 1 femmina, -1 non definito, 2 ambiguo, 3 non applicabile, 4 altro)
	/// </summary> 
	long m_lSessoPaz;

	/// <summary> 
	/// Campo ID medico curante
	/// </summary> 
	long m_lMedicoCurante;

	/// <summary> 
	/// Campo nominativo medico curante
	/// </summary> 
	CString m_sMedicoCurante;

	/// <summary> 
	/// Campo telefono del medico curante
	/// </summary> 
	CString m_sMedicoTel;

	/// <summary> 
	/// Campo indirizzo del medico curante
	/// </summary> 
	CString m_sMedicoIndirizzo;

	/// <summary> 
	/// Campo email del medico curante
	/// </summary> 
	CString m_sMedicoEmail;

	/// <summary> 
	/// Campo professione
	/// </summary> 
	CString m_sProfessione;

	/// <summary> 
	/// Campo nota libera
	/// </summary> 
	CString m_sDenSegnalato;

	/// <summary> 
	/// Campo nazionalità
	/// </summary> 
	CString m_sNazionalita;

	/// <summary> 
	/// Campo id comune di residenza (tabella comuni)
	/// </summary> 
	long m_lIDComune;

	/// <summary> 
	/// Campo id comune di nascita (tabella comuni)
	/// </summary> 
	long m_lIDComuneNascita;

	/// <summary> 
	/// Campo codice libero
	/// </summary> 
	CString m_sCodiceCliente;

	/// <summary> 
	/// Campo secondo cognome
	/// </summary> 
	CString m_sCognome2;

	/// <summary> 
	/// Campo nome padre
	/// </summary> 
	CString m_sNominativoPadre;

	/// <summary> 
	/// Campo nome madre
	/// </summary> 
	CString m_sNominativoMadre;

	/// <summary> 
	/// Campo data ultimo esame (codificato tramite CustomDate)
	/// </summary> 
	long m_lDataUltimoEsame;

	/// <summary> 
	/// Campo stato APC
	/// </summary> 
	long m_lStatoAPC;

	/// <summary> 
	/// Campo login del paziente
	/// </summary> 
	CString m_sLogin;

	/// <summary> 
	/// Campo flag spedizione email
	/// </summary> 
	BOOL m_bSendEmail;

	/// <summary> 
	/// Campo flag spedizione SMS
	/// </summary> 
	BOOL m_bSendSms;

	/// <summary> 
	/// Campo ULSS di residenza
	/// </summary> 
	CString m_sUlssResidenza;

	/// <summary> 
	/// Campo "Paziente del direttore"
	/// </summary> 
	BOOL m_bPazienteDelDirettore;

	/// <summary> 
	/// Campo "ID malattia cronica"
	/// </summary> 
	long m_lIDMalattiaCronica;

	/// <summary> 
	/// Campo "Descrizione malattia cronica"
	/// </summary> 
	CString m_sDescrizioneMalattiaCronica;

	/// <summary> 
	/// Campo "Certificazione MEF"
	/// </summary> 
	BOOL m_bCertificazioneMEF;

	/// <summary> 
	/// Campo "Certificazione SISS"
	/// </summary> 
	BOOL m_bCertificazioneSISS;

	/// <summary> 
	/// Campo codice ricovero paziente
	/// </summary> 
	CString m_sCodiceRicovero;

	/// <summary> 
	/// Campo id episodio ricovero (barcode)
	/// </summary> 
	CString m_sIdEpisodioRicovero;

	/// <summary> 
	/// Id reparto degenza
	/// </summary> 
	long m_lIdRepartoDegenza;

	/// <summary> 
	/// Campo data ricovero
	/// </summary> 
	long m_lDataRicoveroCustom;

	/// <summary> 
	/// Campo che indica il paziente sotto il quale sono stati spostati gli esami
	/// </summary> 
	long m_lIDPazienteUnificato;

	/// <summary> 
	/// Campo che indica l'eventuale decesso del paziente
	/// </summary> 
	BOOL m_bDeceduto;

	/// <summary> 
	/// Campo che indica l'eventuale data del decesso del paziente
	/// </summary> 
	long m_lDataDecesso;

	/// <summary> 
	/// Campo che indica il codice STP se straniero
	/// </summary> 
	CString m_sCodiceSTP;

	/// <summary> 
	/// Campo che indica l'eventuale codice dell'istituzione assicurativa del paziente se straniero
	/// </summary> 
	CString m_sCodiceIstAssicurativa;

	/// <summary> 
	/// Campo che indica il codice della tessera TEAM se cittadino europeo
	/// </summary> 
	CString m_sCodiceTEAM;

	/// <summary> 
	/// Campo flag paziente eliminato
	/// </summary> 
	BOOL m_bEliminato;

	///
	long m_lTotEsami;

	///
	CString m_sFiltroExtra;

	CString m_sIdentificazionePassaporto;	//Julio - BUG 3285 - Adequação de laudos
	CString m_sIdentificazioneDoc1;			//Julio - BUG 3285 - Adequação de laudos
	CString m_sIdentificazioneDoc2;			//Julio - BUG 3285 - Adequação de laudos

	/// <summary> 
	/// Aggiorna la data dell'ultimo esame eseguio dal paziente
	/// </summary> 
	/// <param name="lContatore">contatore paziente</param> 
	void UpdateDataUltimoEsame(const long lContatore);

	/// <summary> 
	/// Recupera un paziente precedentemente eliminato
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL UndeleteRecordset(const CString &strCommento);

	/// <summary> 
	/// Ritorna il nominativo (cognome + nome) del paziente passato
	/// </summary> 
	/// <param name="lContatore">id paziente</param> 
	/// <returns>nominativo paziente</returns>
	CString GetCognomeNome(long lContatore);

	/// <summary> 
	/// Ritorna il nominativo (cognome + nome + data nascita) del paziente passato
	/// </summary> 
	/// <param name="lContatore">id paziente</param> 
	/// <returns>nominativo paziente + data nascita</returns>
	CString GetCognomeNomeDataNascita(long lContatore);

	/// <summary> 
	/// Copia il contenuto di un oggetto paziente all'attuale
	/// </summary> 
	/// <param name="pSet">oggetto paziente sorgente</param> 
	void CopyFieldFrom(CPazientiSet* pSet);

	/// <summary> 
	/// Svuota i dati contenuti all'interno dell'oggetto
	/// </summary> 
	void SetEmpty();

	/// <summary> 
	/// Imposta un filtro di base per l'oggetto corrente
	/// In automatico la funzione provvederà ad aggiungere il filtro per
	/// escludere i pazienti eliminati
	/// </summary> 
	/// <param name="strFilter">filtro tabella pazienti</param> 
	/// <returns>filtro precedentemente impostato</returns>
	CString SetBaseFilter(const CString &strFilter);

	/// <summary> 
	/// Elimina il paziente attuale; in realtà non viene fisicamente eliminato
	/// dal database, ma invece contrassegnato come eliminato
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL DeleteRecordset(const CString &strCommento);

	///
	void SetFastSearch(BOOL bFast);

private:

	/// <summary> 
	/// Gestione scambio dati tra database / variabili e viceversa
	/// </summary> 
	/// <param name="pFX">oggetto usato internamente dal framework; non è modificabile</param> 
	void DoFieldExchange(CFieldExchange* pFX);

	/// <summary> 
	/// Ritorna il nome della tabella
	/// </summary> 
	/// <returns>nome tabella (pazienti)</returns>
	CString GetDefaultSQL();

	/// <summary> 
	/// Crea una nuova istanza di quest'oggetto
	/// Viene usato durante le operazioni di aggiunta/modifica da CBaseSet
	/// per la gestione automatica del log operazioni
	/// </summary> 
	/// <returns>nuovo oggetto</returns>
	virtual CBaseSet* CreateNew();

	/// <summary> 
	/// Copia il contenuto di un oggetto paziente all'attuale
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

};

#endif /* _PAZIENTISET_H_ */