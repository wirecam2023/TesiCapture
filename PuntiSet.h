#ifndef _PUNTISET_H_
	#define _PUNTISET_H_

#include "BaseSet.h"

class CPuntiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CPuntiSet)

public:

	CPuntiSet();

	BOOL GetDatiPunto(long lIDPunto, long &lIDOrgano, long &lX, long &lY);
	long SetDatiPunto(long lIDPunto, long lIDOrgano, long lX, long lY);

	long m_lID;
	long m_lIDOrgano;
	long m_lX;
	long m_lY;
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

#endif /*_PUNTISET_H_ */