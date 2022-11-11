#ifndef _ANATOMIAPATOLOGICAIMMSET_H_
	#define _ANATOMIAPATOLOGICAIMMSET_H_

#include "BaseSet.h"

class CAnatomiaPatologicaImmSet : public CBaseSet
{

	DECLARE_DYNAMIC(CAnatomiaPatologicaImmSet)

public:

	CAnatomiaPatologicaImmSet();

	long m_lID;
	long m_lIDEsame;
	CString m_sPercorso;
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

#endif /* _ANATOMIAPATOLOGICAIMMSET_H_ */