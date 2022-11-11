#ifndef _MONITORAGGIOFARMACIDOSISET_H_
	#define _MONITORAGGIOFARMACIDOSISET_H_

#include "BaseSet.h"

class CMonitoraggioFarmaciDosiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CMonitoraggioFarmaciDosiSet)

public:

	CMonitoraggioFarmaciDosiSet();

	long m_lID;
	long m_lIDMonitoraggio;
	long m_lIDFarmaco;
	CString m_sDose;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _FARMACISET_H_ */