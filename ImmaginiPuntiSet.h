#ifndef _IMMAGINIPUNTISET_H_
	#define _IMMAGINIPUNTISET_H_

#include "BaseSet.h"

class CImmaginiPuntiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CImmaginiPuntiSet)

public:

	CImmaginiPuntiSet();

	long GetIDPunto(long lIDImmagine);
	void SetIDPunto(long lIDImmagine, long lIDPunto);

	long m_lID;
	long m_lIDImmagine;
	long m_lIDPunto;
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

#endif /*_IMMAGINIPUNTISET_H_ */