#pragma once

#include "BaseSet.h"

class CEndoGridCLVersionSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEndoGridCLVersionSet)

public:
	CEndoGridCLVersionSet(CDatabase* pDatabase = NULL);

	long	m_lID;
	long    m_lParameterID;
	long    m_lVersionID;
	BOOL	m_bEliminato;

	void DuplicateVersion(long lOldVersionID, long lNewVersionID);
	long GetLastGridVersion();

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset //
	BOOL UpdateRecordset(const CString &strCommento);

protected:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};

