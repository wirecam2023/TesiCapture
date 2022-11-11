#ifndef _GRUPPIPROCEDUREICD9SET_H_
	#define _GRUPPIPROCEDUREICD9SET_H_

#include "BaseSet.h"

class CGruppiProcedureICD9Set : public CBaseSet
{

	DECLARE_DYNAMIC(CGruppiProcedureICD9Set)

public:

	CGruppiProcedureICD9Set();

	long m_lID;
	CString m_sDescrizione;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	CString GetStringDescrizione(long lID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _GRUPPIPROCEDUREICD9SET_H_ */