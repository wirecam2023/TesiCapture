#ifndef _PROCEDUREESAMISET_H_
	#define _PROCEDUREESAMISET_H_

#include "BaseSet.h"

class CProcedureEsamiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CProcedureEsamiSet)

public:

	CProcedureEsamiSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDProcedura;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	void CopyFieldFrom(CProcedureEsamiSet* pSet);
	CString GetFieldText(long lEsame);
	// CString GetStringDescrizione(long lEsame);
	BOOL Add(long lEsame, long idProcedura);

	virtual void SetEmpty();

private:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _PROCEDUREESAMISET_H_ */