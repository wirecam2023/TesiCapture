#ifndef _ESAMISBLOCCATISET_H_
#define _ESAMISBLOCCATISET_H_

#include "BaseSet.h"

class CEsamiSbloccatiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiSbloccatiSet)

public:

	CEsamiSbloccatiSet();

	void InserisciRecord(long idEsame, long idUtente);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

	long m_lId;
	long m_lIdEsame;
	CString m_sDataOra;
	long m_lIdUtente;
	long m_lEseguito;
};

#endif /* _ACCESSORISET_H_ */