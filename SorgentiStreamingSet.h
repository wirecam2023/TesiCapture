#ifndef _SORGENTISTREAMINGSET_H_
	#define _SORGENTISTREAMINGSET_H_

#include "BaseSet.h"

class CEsamiSet;

class CSorgentiStreamingSet : public CBaseSet
{
	DECLARE_DYNAMIC(CSorgentiStreamingSet)

public:

	CSorgentiStreamingSet();

	long m_lID;
	CString m_sDescrizione;
	CString m_sIndirizzoCompleto;
	CString m_sNomeComputerSala;
	CString m_sPazienteEsame;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	void ResetPazienteEsame();

	// 
	void SetPazienteEsame(CPazientiSet* pPazientiSet, CEsamiSet* pEsamiSet);

	long Add(CString sDescrizione, CString sIndirizzo, CString sComputer);
	void Edt(long lID, CString sDescrizione, CString sIndirizzo, CString sComputer);
	BOOL Del(long lID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _SORGENTISTREAMINGSET_H_ */