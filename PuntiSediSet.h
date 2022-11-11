#ifndef _PUNTISEDISET_H_
	#define _PUNTISEDISET_H_

#include "BaseSet.h"

class CPuntiSediSet : public CBaseSet
{

	DECLARE_DYNAMIC(CPuntiSediSet)

public:

	CPuntiSediSet();

	long m_lID;
	CString m_sSede;
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

#endif /* _PUNTISEDISET_H_ */