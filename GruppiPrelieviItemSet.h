#ifndef _GRUPPIPRELIEVIITEMSET_H_
	#define _GRUPPIPRELIEVIITEMSET_H_

#include "BaseSet.h"

class CGruppiPrelieviItemSet : public CBaseSet
{
	DECLARE_DYNAMIC(CGruppiPrelieviItemSet)

public:

	CGruppiPrelieviItemSet();

	long m_lID;
	long m_lIDGruppo;
	long m_lIDIntervento;
	long m_lPrelievi;
	CString m_sDescrizione;
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

#endif /* _GRUPPIPRELIEVIITEMSET_H_ */