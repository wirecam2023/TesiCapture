#pragma once

#include "BaseSet.h"

class CEsamiChecklistSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEsamiChecklistSet)

public:
	CEsamiChecklistSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDCheck;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

private:
	virtual void DoFieldExchange(CFieldExchange* pFX);

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

	virtual CString GetDefaultSQL();
	virtual void SetEmpty();
};
