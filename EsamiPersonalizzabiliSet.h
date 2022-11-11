#ifndef _EESAMIPERSONALIZZABILISET_H_
	#define _EESAMIPERSONALIZZABILISET_H_

#include "BaseSet.h"

/// <summary> 
/// Oggetto dati aggiuntivi dell'esame
/// Rappresenta un'estensione della tabella esami;
/// è collegata 1 a 1 alla stessa tramite la relazione
/// tra il campo id esame e contatore
/// L'oggetto è utilizzato anche per il salvataggio dei dati
/// di default di un esame passando il valore opportuno durante
/// la costruzione dell'oggetto
/// </summary> 
class CEsamiPersonalizzabiliSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiPersonalizzabiliSet)

public:

	/// <summary> 
	/// Costruttore
	/// </summary> 
	/// <param name="bDefaultFieldSet">TRUE se serve per salvare valori di default esame</param> 
	CEsamiPersonalizzabiliSet(BOOL bDefaultFieldSet = FALSE);

	/// <summary> 
	/// Campo id esame - mantiene la relazione con la tabella esame
	/// </summary> 
	long m_lIDEsame;

	/// <summary> 
	/// Campi di testo personalizzabili (100)
	/// </summary> 
	CString m_sTesto000;
	CString m_sTesto001;
	CString m_sTesto002;
	CString m_sTesto003;
	CString m_sTesto004;
	CString m_sTesto005;
	CString m_sTesto006;
	CString m_sTesto007;
	CString m_sTesto008;
	CString m_sTesto009;
	CString m_sTesto010;
	CString m_sTesto011;
	CString m_sTesto012;
	CString m_sTesto013;
	CString m_sTesto014;
	CString m_sTesto015;
	CString m_sTesto016;
	CString m_sTesto017;
	CString m_sTesto018;
	CString m_sTesto019;
	CString m_sTesto020;
	CString m_sTesto021;
	CString m_sTesto022;
	CString m_sTesto023;
	CString m_sTesto024;
	CString m_sTesto025;
	CString m_sTesto026;
	CString m_sTesto027;
	CString m_sTesto028;
	CString m_sTesto029;
	CString m_sTesto030;
	CString m_sTesto031;
	CString m_sTesto032;
	CString m_sTesto033;
	CString m_sTesto034;
	CString m_sTesto035;
	CString m_sTesto036;
	CString m_sTesto037;
	CString m_sTesto038;
	CString m_sTesto039;
	CString m_sTesto040;
	CString m_sTesto041;
	CString m_sTesto042;
	CString m_sTesto043;
	CString m_sTesto044;
	CString m_sTesto045;
	CString m_sTesto046;
	CString m_sTesto047;
	CString m_sTesto048;
	CString m_sTesto049;
	CString m_sTesto050;
	CString m_sTesto051;
	CString m_sTesto052;
	CString m_sTesto053;
	CString m_sTesto054;
	CString m_sTesto055;
	CString m_sTesto056;
	CString m_sTesto057;
	CString m_sTesto058;
	CString m_sTesto059;
	CString m_sTesto060;
	CString m_sTesto061;
	CString m_sTesto062;
	CString m_sTesto063;
	CString m_sTesto064;
	CString m_sTesto065;
	CString m_sTesto066;
	CString m_sTesto067;
	CString m_sTesto068;
	CString m_sTesto069;
	CString m_sTesto070;
	CString m_sTesto071;
	CString m_sTesto072;
	CString m_sTesto073;
	CString m_sTesto074;
	CString m_sTesto075;
	CString m_sTesto076;
	CString m_sTesto077;
	CString m_sTesto078;
	CString m_sTesto079;
	CString m_sTesto080;
	CString m_sTesto081;
	CString m_sTesto082;
	CString m_sTesto083;
	CString m_sTesto084;
	CString m_sTesto085;
	CString m_sTesto086;
	CString m_sTesto087;
	CString m_sTesto088;
	CString m_sTesto089;
	CString m_sTesto090;
	CString m_sTesto091;
	CString m_sTesto092;
	CString m_sTesto093;
	CString m_sTesto094;
	CString m_sTesto095;
	CString m_sTesto096;
	CString m_sTesto097;
	CString m_sTesto098;
	CString m_sTesto099;

	/// <summary> 
	/// Campi di testo RTF personalizzabili (20)
	/// </summary> 
	CString	m_sTestoRtf000;
	CString	m_sTestoTxt000;
	CString	m_sTestoRtf001;
	CString	m_sTestoTxt001;
	CString	m_sTestoRtf002;
	CString	m_sTestoTxt002;
	CString	m_sTestoRtf003;
	CString	m_sTestoTxt003;
	CString	m_sTestoRtf004;
	CString	m_sTestoTxt004;
	CString	m_sTestoRtf005;
	CString	m_sTestoTxt005;
	CString	m_sTestoRtf006;
	CString	m_sTestoTxt006;
	CString	m_sTestoRtf007;
	CString	m_sTestoTxt007;
	CString	m_sTestoRtf008;
	CString	m_sTestoTxt008;
	CString	m_sTestoRtf009;
	CString	m_sTestoTxt009;
	CString	m_sTestoRtf010;
	CString	m_sTestoTxt010;
	CString	m_sTestoRtf011;
	CString	m_sTestoTxt011;
	CString	m_sTestoRtf012;
	CString	m_sTestoTxt012;
	CString	m_sTestoRtf013;
	CString	m_sTestoTxt013;
	CString	m_sTestoRtf014;
	CString	m_sTestoTxt014;
	CString	m_sTestoRtf015;
	CString	m_sTestoTxt015;
	CString	m_sTestoRtf016;
	CString	m_sTestoTxt016;
	CString	m_sTestoRtf017;
	CString	m_sTestoTxt017;
	CString	m_sTestoRtf018;
	CString	m_sTestoTxt018;
	CString	m_sTestoRtf019;
	CString	m_sTestoTxt019;

	/// <summary> 
	/// Campi checklist personalizzabili (20)
	/// </summary> 
	CString m_sTestoCLRtf000;
	CString m_sTestoCLTxt000;
	CString m_sTestoCLRtf001;
	CString m_sTestoCLTxt001;
	CString m_sTestoCLRtf002;
	CString m_sTestoCLTxt002;
	CString m_sTestoCLRtf003;
	CString m_sTestoCLTxt003;
	CString m_sTestoCLRtf004;
	CString m_sTestoCLTxt004;
	CString m_sTestoCLRtf005;
	CString m_sTestoCLTxt005;
	CString m_sTestoCLRtf006;
	CString m_sTestoCLTxt006;
	CString m_sTestoCLRtf007;
	CString m_sTestoCLTxt007;
	CString m_sTestoCLRtf008;
	CString m_sTestoCLTxt008;
	CString m_sTestoCLRtf009;
	CString m_sTestoCLTxt009;
	CString m_sTestoCLRtf010;
	CString m_sTestoCLTxt010;
	CString m_sTestoCLRtf011;
	CString m_sTestoCLTxt011;
	CString m_sTestoCLRtf012;
	CString m_sTestoCLTxt012;
	CString m_sTestoCLRtf013;
	CString m_sTestoCLTxt013;
	CString m_sTestoCLRtf014;
	CString m_sTestoCLTxt014;
	CString m_sTestoCLRtf015;
	CString m_sTestoCLTxt015;
	CString m_sTestoCLRtf016;
	CString m_sTestoCLTxt016;
	CString m_sTestoCLRtf017;
	CString m_sTestoCLTxt017;
	CString m_sTestoCLRtf018;
	CString m_sTestoCLTxt018;
	CString m_sTestoCLRtf019;
	CString m_sTestoCLTxt019;

	/// <summary> 
	/// Campi data/ora personalizzabili (20)
	/// </summary> 
	long m_lDataOra000;
	long m_lDataOra001;
	long m_lDataOra002;
	long m_lDataOra003;
	long m_lDataOra004;
	long m_lDataOra005;
	long m_lDataOra006;
	long m_lDataOra007;
	long m_lDataOra008;
	long m_lDataOra009;
	long m_lDataOra010;
	long m_lDataOra011;
	long m_lDataOra012;
	long m_lDataOra013;
	long m_lDataOra014;
	long m_lDataOra015;
	long m_lDataOra016;
	long m_lDataOra017;
	long m_lDataOra018;
	long m_lDataOra019;

	/// <summary> 
	/// Copia il contenuto di un oggetto esame aggiuntivo all'attuale
	/// </summary> 
	/// <param name="pSet">oggetto paziente sorgente</param> 
	/// <param name="bEmpty">svuota l'oggetto corrente prima di cominciare la copia</param> 
	virtual void CopyFieldFrom(CEsamiPersonalizzabiliSet* pSet, BOOL bEmpty = TRUE);

	/// <summary> 
	/// Ritorna lo stato attuale del recordset
	/// (Vedi struttura EditMode all'interno della classe CRecordset)
	/// </summary> 
	/// <returns>stato attuale recordset</returns>
	int GetEditMode();

	/// <summary> 
	/// Svuota i dati contenuti all'interno dell'oggetto
	/// </summary> 
	virtual void SetEmpty();

private:

	/// <summary> 
	/// Ridefinizione metodo aggiunta recordset come privato per impedire
	/// l'aggiunta di record tramite questo oggetto; deve essere tutto comandato
	/// dall'oggetto padre CEsamiSet
	/// </summary> 
	void AddNew() { AddNewRecordset("CEsamiPersonalizzabiliSet::AddNew"); }

	/// <summary> 
	/// Ridefinizione metodo aggiunta recordset come privato per impedire
	/// l'aggiunta di record tramite questo oggetto; deve essere tutto comandato
	/// dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL AddNewRecordset(const CString &strCommento) { return CBaseSet::AddNewRecordset(strCommento); }

	/// <summary> 
	/// Ridefinizione metodo chiusura recordset come privato; 
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	void Close() { CloseRecordset("CEsamiPersonalizzabiliSet::CloseRecordset"); }

	/// <summary> 
	/// Ridefinizione metodo chiusura recordset come privato; 
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL CloseRecordset(const CString &strCommento) { return CBaseSet::CloseRecordset(strCommento); }

	/// <summary> 
	/// Ridefinizione metodo modifica recordset come privato per impedire
	/// la modifica di record tramite questo oggetto; deve essere tutto comandato
	/// dall'oggetto padre CEsamiSet
	/// </summary> 
	void Edit() { EditRecordset("CEsamiPersonalizzabiliSet::Edit"); }

	/// <summary> 
	/// Ridefinizione metodo modifica recordset come privato per impedire
	/// la modifica di record tramite questo oggetto; deve essere tutto comandato
	/// dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL EditRecordset(const CString &strCommento) { return CBaseSet::EditRecordset(strCommento); }

	/// <summary> 
	/// Ridefinizione metodo annulla modifica recordset come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL NoEditRecordset(const CString &strCommento) { return CBaseSet::NoEditRecordset(strCommento); }

	/// <summary> 
	/// Ridefinizione metodo apertura recordset come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <param name="nOpenType">tipo apertura</param> 
	/// <param name="lpszSQL">query</param> 
	/// <param name="nOptions">opzioni di apertura</param> 
	void Open(int nOpenType = CRecordset::dynaset, LPCTSTR lpszSQL = NULL, int nOptions = CRecordset::skipDeletedRecords) { OpenRecordset("CBaseSet::Open"); }

	/// <summary> 
	/// Ridefinizione metodo apertura recordset come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL OpenRecordset(const CString &strCommento) { return CBaseSet::OpenRecordset(strCommento); }

	/// <summary> 
	/// Ridefinizione metodo riapertura recordset come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL RecordsetReOpen(BOOL &bError, const CString &strFilter, const CString &strSort, const CString &strCommento) { return CBaseSet::RecordsetReOpen(bError, strFilter, strSort, strCommento); }

	/// <summary> 
	/// Ridefinizione metodo aggiornamento dati recordset come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL RefreshRecordset() { return CBaseSet::RefreshRecordset(); }

	/// <summary> 
	/// Imposta un filtro di base per l'oggetto corrente
	/// Viene definito come privato perchè deve essere tutto comandato 
	/// dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <param name="strFilter">filtro tabella pazienti</param> 
	/// <returns>filtro precedentemente impostato</returns>
	CString SetBaseFilter(const CString &strFilter) { return CBaseSet::SetBaseFilter(strFilter); }

	/// <summary> 
	/// Ridefinizione metodo salvataggio recordset come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL Update() { return UpdateRecordset("CBaseSet::Update"); }

	/// <summary> 
	/// Ridefinizione metodo salvataggio recordset come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	BOOL UpdateRecordset(const CString &strCommento) { return CBaseSet::UpdateRecordset(strCommento); }

	/// <summary> 
	/// Ridefinizione metodo cancellazione record come privato;
	/// non è possibile eliminare record da questa tabella perchè viene contrassegnato
	/// come eliminato il record principale della tabella esami
	/// </summary> 
	/// <param name="strCommento">informazione di debug</param> 
	/// <returns>TRUE se l'operazione è stata eseguita con successo</returns>
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è COME una vista //

	/// <summary> 
	/// Ridefinizione metodo sposta al primo record come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	void MoveFirst() { CBaseSet::MoveFirst(); }

	/// <summary> 
	/// Ridefinizione metodo sposta al record precedente come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	void MovePrev() { CBaseSet::MovePrev(); }

	/// <summary> 
	/// Ridefinizione metodo sposta al record successivo come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	void MoveNext() { CBaseSet::MoveNext(); }

	/// <summary> 
	/// Ridefinizione metodo sposta all'ultimo record come privato;
	/// deve essere tutto comandato dall'oggetto padre CEsamiSet
	/// </summary> 
	void MoveLast() { CBaseSet::MoveLast(); }

	/// <summary> 
	/// Gestione scambio dati tra database / variabili e viceversa
	/// </summary> 
	/// <param name="pFX">oggetto usato internamente dal framework; non è modificabile</param> 
	virtual void DoFieldExchange(CFieldExchange* pFX);

	/// <summary> 
	/// Ritorna il nome della tabella
	/// </summary> 
	/// <returns>nome tabella (esamirtf)</returns>
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

	/// <summary> 
	/// Classe CEsamiSet può chiamare anche i metodi privati
	/// </summary> 
	friend class CEsamiSet;

};

#endif /* _EESAMIPERSONALIZZABILISET_H_ */