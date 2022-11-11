#ifndef _TIPOESAMESET_H_
	#define _TIPOESAMESET_H_

#include "BaseSet.h"

class CTipoEsameSet : public CBaseSet
{

	DECLARE_DYNAMIC(CTipoEsameSet)

public:

	CTipoEsameSet();

	long m_lContatore;
	CString m_sDescrizione;
	CString m_sSigla;
	CString m_sSiglaPrenotazione;
	BOOL m_bPrivato;
	long m_lIDCronicita;
	long m_lContatoreAnnuale;
	long m_lAnno;
	CString m_sStazione; // utilizzabile nelle stazioni "mobile" per identificare da quale di queste è stato inserito l'esame ed evitare doppione nel progressivo //
	BOOL m_bEsameScreening;
	long m_lSfondo;
	long m_lEliminaCodeBack;
	long m_lEliminaCodeFore;
	BOOL m_bErogaSoloPrestazioniPrincipali;
	long m_lUO;
	BOOL m_bEliminato;

	//
	CString GetDescrizione(long lContatore);
	CString GetSigla(long lContatore);
	CString GetSiglaPrenotazione(long lContatore);
	BOOL IsPrivato(long lTipoEsame);
	long GetIDCronicita(long lTipoEsame);
	long GetSfondo(long lTipoEsame);
	void GetColoriEliminaCode(long lTipoEsame, long& lColoreBackR, long& lColoreBackG, long& lColoreBackB, long& lColoreForeR, long& lColoreForeG, long& lColoreForeB);
	long GetIdTipoEsameScreening();

	long FleuryTrans(CString sSigla, CString sDescrizione);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /*_TIPOESAMESET_H_ */