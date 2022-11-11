#pragma once

#include "BaseSet.h"

class CEndoGridCLComboSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEndoGridCLComboSet)

public:
	CEndoGridCLComboSet(void);
	~CEndoGridCLComboSet(void);

	long m_lId;
	long m_lIdparametro;
	CString m_sDescrizione;
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
