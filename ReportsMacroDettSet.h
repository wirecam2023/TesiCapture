#ifndef _REPORTSMACRODETTSET_H_
	#define _REPORTSMACRODETTSET_H_

#include "BaseSet.h"

class CReportsMacroDettSet : public CBaseSet
{

	DECLARE_DYNAMIC(CReportsMacroDettSet)

public:

	CReportsMacroDettSet();

	long	m_lID;
	long	m_lIDMacro;
	CString m_sReport;
	long	m_lCopie;
	BOOL    m_bEliminato;

	BOOL ReportDn(long lID1, long lIDMacro);
	BOOL ReportUp(long lID1, long lIDMacro);

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	BOOL ReportEdt(long lID, long lIDMacro, CString &sReport, long lCopie);

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _REPORTSMACRODETTSET_H_ */