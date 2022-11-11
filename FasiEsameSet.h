#pragma once

#include "BaseSet.h"

class CFasiEsameSet : public CBaseSet
{
	DECLARE_DYNAMIC(CFasiEsameSet)

public:

	CFasiEsameSet();

	long m_lID;
	CString m_sDescrizione;	
	long m_lColor;
	CString m_sReport;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	CString GetDescrizione(long id);
	COLORREF GetColor(long id);
	CString GetReport(long id);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};