#ifndef _ESAMICONVALIDATISET_H_
	#define _ESAMICONVALIDATISET_H_

#include "BaseSet.h"

class CEsamiConvalidatiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiConvalidatiSet)

public:

	CEsamiConvalidatiSet();

	long m_lId;
	long m_lIdEsame;	
	CString m_sDataOra;
	long m_lIdUtente;
	long m_lEseguito;

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

#endif /* _ESAMICONVALIDATISET_H_ */