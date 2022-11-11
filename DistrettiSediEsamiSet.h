#ifndef _DISTRETTISEDIESAMISET_H_
	#define _DISTRETTISEDIESAMISET_H_

#include "BaseSet.h"

class CDistrettiSediEsamiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CDistrettiSediEsamiSet)

public:

	CDistrettiSediEsamiSet();

	long m_lID;
	long m_lIDDistretto;
	long m_lIDSedeEsame;
	BOOL m_bEliminato;

	long GetIDDistretto(long lIDSedeEsame);
	BOOL GetStessoDistretto(long lIDSedeEsame);

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual CBaseSet* CreateNew();

};

#endif /* _DISTRETTISEDIESAMISET_H_ */