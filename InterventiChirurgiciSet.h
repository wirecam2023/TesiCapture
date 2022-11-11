#ifndef _INTERVENTICHIRURGICISET_H_
	#define _INTERVENTICHIRURGICISET_H_

#include "BaseSet.h"

class CInterventiChirurgiciSet : public CBaseSet
{
	DECLARE_DYNAMIC(CInterventiChirurgiciSet)

public:

	CInterventiChirurgiciSet();

	long m_lContatore;
	long m_lEsame;
	long m_lClasse;
	CString m_sIntervento;
	BOOL m_bEliminato;

	void CopyFieldFrom(CInterventiChirurgiciSet* pSet);
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

#endif /* _INTERVENTICHIRURGICISET_H_ */