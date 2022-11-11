#ifndef _REPORTSDEFAULTSET_H_
	#define _REPORTSDEFAULTSET_H_

#include "BaseSet.h"

class CReportsDefaultSet : public CBaseSet
{

	DECLARE_DYNAMIC(CReportsDefaultSet)

public:

	CReportsDefaultSet();

	long m_lID;
	CString m_sSedeEsame;
	long m_lTipoEsame;
	CString m_sReport;
	long m_lCopie;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	BOOL ReportAdd(CString &sSedeEsame, long lTipoEsame, CString sReport, long lCopie);
	BOOL ReportDel(long lID);
	BOOL ReportEdt(long lID, CString &sSedeEsame, long lTipoEsame, CString sReport, long lCopie);

	BOOL ReportUp(long lID1, CString &sSedeEsame, long lTipoEsame);
	BOOL ReportDn(long lID1, CString &sSedeEsame, long lTipoEsame);

	//
	CString GetDefaultReport(long lTipoEsame);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _REPORTSDEFAULTSET_H_ */