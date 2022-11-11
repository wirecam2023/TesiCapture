#ifndef _ESAMIINTEGRATISET_H_
	#define _ESAMIINTEGRATISET_H_

#include "BaseSet.h"

class CEsamiIntegratiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEsamiIntegratiSet)

public:

	CEsamiIntegratiSet();

	long m_lID;
	long m_lIDEsamePrincipale;
	long m_lIDEsameSecondario;
	BOOL m_bEliminato;
	BOOL m_bIsTCP; //Gabriel - TCP

	BOOL m_bColumnsTCP; //Gabriel - TCP

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	//
	void AddRecord(long lIDPrincipale, long lIDSecondario, BOOL bIsTCP = FALSE); //Gabriel - TCP
	void DelRecord(long lIDPrincipale, long lIDSecondario);
	BOOL ExistsRecord(long lIDPrincipale, long lIDSecondario);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual CBaseSet* CreateNew();

};

#endif /* _ESAMIINTEGRATISET_H_ */