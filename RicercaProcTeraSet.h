#ifndef _RICERCAPROCTERASET_H_
	#define _RICERCAPROCTERASET_H_

#include "BaseSet.h"

class CRicercaProcTeraSet : public CBaseSet
{

	DECLARE_DYNAMIC(CRicercaProcTeraSet)

public:

	CRicercaProcTeraSet();

	CString	m_sDescr1;
	long	m_lLevel2;
	CString	m_sDescr2;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _RICERCAPROCTERASET_H_ */