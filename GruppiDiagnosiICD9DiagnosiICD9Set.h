#ifndef _GRUPPIDIAGNOSIICD9DIAGNOSIICD9SET_H_
	#define _GRUPPIDIAGNOSIICD9DIAGNOSIICD9SET_H_

#include "BaseSet.h"

class CGruppiDiagnosiICD9DiagnosiICD9Set : public CBaseSet
{
	DECLARE_DYNAMIC(CGruppiDiagnosiICD9DiagnosiICD9Set)

public:

	CGruppiDiagnosiICD9DiagnosiICD9Set();

	long m_lID;
	long m_lIDGruppo;
	long m_lIDDiagnosi;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _GRUPPIDIAGNOSIICD9DIAGNOSIICD9SET_H_ */