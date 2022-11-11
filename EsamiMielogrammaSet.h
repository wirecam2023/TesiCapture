#ifndef _EESAMIMIELOGRAMMASET_H_
	#define _EESAMIMIELOGRAMMASET_H_

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
class CEsamiMielogrammaSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiMielogrammaSet)

public:

	CEsamiMielogrammaSet();

	long m_lIDESAME;
	long m_lCELULASACONTAR;
	long m_lHISTIOCITOS;
	long m_lMACROFAGOS;
	long m_lMASTOCITOS;
	long m_lNPROM;
	long m_lNMIEL;
	long m_lNMETAM;
	long m_lNBAST;
	long m_lNSEGM;
	long m_lPROERITRO;
	long m_lERITROBASO;
	long m_lERITPOLICRO;
	long m_lERITROORTO;
	long m_lBLASTOS;
	long m_lOUTROS;
	long m_lEPROM;
	long m_lEMIEL;
	long m_lEMETAM;
	long m_lEBAST;
	long m_lESEGM;
	long m_lLINFOCITO;
	long m_lMONOCITO;
	long m_lPLASMOCITO;
	long m_lBSEGM;
	CString m_sMGC;

	/// <summary> 
	/// Copia il contenuto di un oggetto esame aggiuntivo all'attuale
	/// </summary> 
	/// <param name="pSet">oggetto paziente sorgente</param> 
	/// <param name="bEmpty">svuota l'oggetto corrente prima di cominciare la copia</param> 
	virtual void CopyFieldFrom(CEsamiMielogrammaSet* pSet, BOOL bEmpty = TRUE);

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
	void AddNew() { AddNewRecordset("CEsamiMielogrammaSet::AddNew"); }

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
	void Close() { CloseRecordset("CEsamiMielogrammaSet::CloseRecordset"); }

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
	void Edit() { EditRecordset("CEsamiMielogrammaSet::Edit"); }

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
	/// Classe CEsamiSet può chiamare anche i metodi privati
	/// </summary> 
	friend class CEsamiSet;

};

#endif /* _EESAMIMIELOGRAMMASET_H_ */