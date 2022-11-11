#pragma once

#include "BaseSet.h"

class CFasiEsameGruppiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CFasiEsameGruppiSet)

public:

	CFasiEsameGruppiSet();

	long m_lID;
	long m_lIDFase;
	long m_lIDGruppo;
	BOOL m_bEliminato;

	CString GetGruppiListAsString(long idFase);
	void GetGruppiList(long lIdFase, CList<long>* activeGroupList);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};