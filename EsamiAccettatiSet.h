#ifndef _ESAMIACCETTATISET_H_
	#define _ESAMIACCETTATISET_H_

#include "BaseSet.h"
//#include "CupWorkListManager.h"

class CEsamiAccettatiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiAccettatiSet)

public:

	CEsamiAccettatiSet();

	long m_lId;
	long m_lIdEsame;	
	CString m_sDataOra;
	long m_lEseguito;
	long m_lIdUtente;	

	void InserisciRecord(long idEsame, long idUtente);

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

#endif /* _ESAMIACCETTATISET_H_ */