#ifndef _CHECKLISTESAMISET_H_
	#define _CHECKLISTESAMISET_H_

#include "BaseSet.h"

class CCheckListEsamiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CCheckListEsamiSet)

public:

	CCheckListEsamiSet();

	long m_lID;
	long m_lIDCheckList;
	long m_lIDTipoEsame;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _CHECKLISTESAMISET_H_ */