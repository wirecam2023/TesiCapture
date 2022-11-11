#ifndef _MSTPROCEDUREDIAGNOSTICHESET_H_
	#define _MSTPROCEDUREDIAGNOSTICHESET_H_

#include "BaseSet.h"

class CMstProcedureDiagnosticheSet : public CBaseSet
{

	DECLARE_DYNAMIC(CMstProcedureDiagnosticheSet)

public:

	CMstProcedureDiagnosticheSet();

	long m_lContatore;
	long m_lPadre;
	long m_lLivello;
	CString m_sDescrizione;
	long m_lUO;
	BOOL m_bEliminato;

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

#endif /* _MSTPROCEDUREDIAGNOSTICHESET_H_ */