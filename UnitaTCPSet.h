#ifndef _UNITATCPSET_H_
#define _UNITATCPSET_H_

#include "BaseSet.h"

class CUnitaTCPSet : public CBaseSet
{

	DECLARE_DYNAMIC(CUnitaTCPSet)

public:

	CUnitaTCPSet();

	long m_lID;
	long m_lUnita;
	CString m_sDescrizione;
	CString m_sEndpoint;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	BOOL SetEliminato(long lID);
	CString GetEndpoint(long lID);
	long GetUnita(long lID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _UNITATCPSET_H_ */