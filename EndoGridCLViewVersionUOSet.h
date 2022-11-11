#pragma once

#include "BaseSet.h"

class CEndoGridCLViewVersionUOSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEndoGridCLViewVersionUOSet)

public:
	CEndoGridCLViewVersionUOSet(CDatabase* pDatabase = NULL);
	
	long	m_lUO;
	long    m_lVersionID;

	long GetLastGridVersion(long lUO);


private:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};

