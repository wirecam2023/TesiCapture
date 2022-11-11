#pragma once

#include "BaseSet.h"

class CEndoGridCLDatiEsameSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEndoGridCLDatiEsameSet)

public:
	CEndoGridCLDatiEsameSet(CDatabase* pDatabase = NULL);

	long   	m_lID;
	long	m_lIDEsame;
	long	m_lIDParametro;
	BOOL	m_bDatoBool;
	long	m_lDatoInt;
	float	m_fDatoFloat;
	CString m_sDatoStringa;
	long	m_lColore;
	BOOL	m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

protected:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};