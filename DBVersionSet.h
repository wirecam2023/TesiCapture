#ifndef _DBVERSIONSET_H_
	#define _DBVERSIONSET_H_

#include "BaseSet.h"

class CDBVersionSet : public CBaseSet
{

	DECLARE_DYNAMIC(CDBVersionSet)

public:

	CDBVersionSet();

	CString GetDBVersion();

private:

	long m_lVersion1;
	long m_lVersion2;
	long m_lVersion3;
	long m_lVersion4;

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //

};

#endif /* _DBVERSIONSET_H_ */