#ifndef _PROCEDUREICD9SET_H_
	#define _PROCEDUREICD9SET_H_

#include "BaseSet.h"

class CProcedureICD9Set : public CBaseSet
{

	DECLARE_DYNAMIC(CProcedureICD9Set)

public:

	CProcedureICD9Set();

	long m_lID;
	CString m_sDescrizione;
	CString m_sCodificaInterna;
	CString m_sCodificaICD9Interni;
	CString m_sCodificaICD9Esterni;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	CString GetFieldText(long lID);
	CString GetCodificaInterna(long lID);
	CString GetCodificaICD9Interni(long lID);
	CString GetCodificaICD9Esterni(long lID);
	// CString GetDescrizione(long lID);
	long GetIdFromICD9(CString codiceICD9);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _PROCEDUREICD9SET_H_ */