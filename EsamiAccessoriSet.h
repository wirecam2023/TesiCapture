#ifndef _ESAMIACCESSORISET_H_
	#define _ESAMIACCESSORISET_H_

#include "BaseSet.h"

class CEsamiAccessoriSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiAccessoriSet)

public:

	CEsamiAccessoriSet();

	long m_lContatore;
	long m_lEsame;
	long m_lCodice;
	long m_lQuantita;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	void CopyFieldFrom(CEsamiAccessoriSet* pSet);
	CString GetFieldText(long lEsame);

	virtual void SetEmpty();

private:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _REGIONESET_H_ */