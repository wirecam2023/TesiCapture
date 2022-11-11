#ifndef _ESAMIFARMACICRONICISET_H_
	#define _ESAMIFARMACICRONICISET_H_

#include "BaseSet.h"

class CEsamiFarmaciCroniciSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiFarmaciCroniciSet)

public:

	CEsamiFarmaciCroniciSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDFarmaco;
	long m_lFase;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	//
	virtual void SetEmpty();

	//
	void AddRow(long lIDEsame, long lIDFarmaco, long lFase);
	void CloneAllRows(long lIDEsameOld, long lIDEsameNew);
	void DelAllRows(long lIDEsame);
	long GetFase(long lIDEsame, long lIDFarmaco);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	
	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ESAMIFARMACICRONICISET_H_ */