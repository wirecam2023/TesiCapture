#ifndef _OSSERVAZIONISET_H_
	#define _OSSERVAZIONISET_H_

#include "BaseSet.h"

class COsservazioniSet : public CBaseSet
{
	DECLARE_DYNAMIC(COsservazioniSet)

public:

	COsservazioniSet();

	long		m_lContatore;
	long		m_lEsame;
	long		m_lOrgano;
	CString		m_sSede;
	CString		m_sOsservazioni;
	BOOL        m_bEliminato;

	void CopyFieldFrom(COsservazioniSet* pSet);
	virtual void SetEmpty();

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _OSSERVAZIONISET_H_ */