#ifndef _CHECKLISTCHECKEDELEMENTSET_H_
	#define _CHECKLISTCHECKEDELEMENTSET_H_

#include "BaseSet.h"

class CCheckListCheckedElementSet : public CBaseSet
{

	DECLARE_DYNAMIC(CCheckListCheckedElementSet)

public:

	CCheckListCheckedElementSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDItem;
	BOOL m_bEliminato;

	BOOL AddCheck(long lIDEsame, long lIDItem);
	BOOL DelCheck(long lIDEsame, long lIDItem);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _CHECKLISTCHECKEDELEMENTSET_H_ */