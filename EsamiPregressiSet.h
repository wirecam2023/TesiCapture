#ifndef _ESAMIPREGRESSISET_H_
	#define _ESAMIPREGRESSISET_H_

#include "BaseSet.h"

class CEsamiPregressiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiPregressiSet)

public:

	CEsamiPregressiSet();

	long m_lContatore;
	long m_lEsame;
	long m_lData;
	CString m_sEsamePregresso;
	CString m_sEsito;
	BOOL m_bEliminato;

	void CopyFieldFrom(CEsamiPregressiSet* pSet);
	virtual void SetEmpty();

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	
	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ESAMIPREGRESSISET_H_ */