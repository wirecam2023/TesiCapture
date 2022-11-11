#pragma once

#include "BaseSet.h"

class CEndoGridCLGruppiUtenteSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEndoGridCLGruppiUtenteSet)

public:
	CEndoGridCLGruppiUtenteSet(CDatabase* pDatabase = NULL);

	long   	m_lID;
	long	m_lIDEtichetta;
	long	m_lIDGruppo;
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