#pragma once

#include "BaseSet.h"

class CEndoGridCLOptionsSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEndoGridCLOptionsSet)

public:
	CEndoGridCLOptionsSet(void);
	~CEndoGridCLOptionsSet(void);

	long m_lId;
	CString m_sGridIdentifier;
	float m_fDividerPos;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
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
