#ifndef _FARMACIGRUPPIRICITEMSSET_H_
	#define _FARMACIGRUPPIRICITEMSSET_H_

#include "BaseSet.h"

class CFarmaciGruppiRicItemsSet : public CBaseSet
{

	DECLARE_DYNAMIC(CFarmaciGruppiRicItemsSet)

public:

	CFarmaciGruppiRicItemsSet();

	long m_lID;
	long m_lIDGruppo;
	long m_lIDFarmaco;
	long m_lQuantita;
	CString m_sTestoLibero;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	//
	long GetIDFarmaco(long lID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _FARMACIGRUPPIRICITEMSSET_H_ */