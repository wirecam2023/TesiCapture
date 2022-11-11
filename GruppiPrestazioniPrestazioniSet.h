#ifndef _GRUPPIPRESTAZIONIPRESTAZIONISET_H_
	#define _GRUPPIPRESTAZIONIPRESTAZIONISET_H_

#include "BaseSet.h"

class CGruppiPrestazioniPrestazioniSet : public CBaseSet
{
	DECLARE_DYNAMIC(CGruppiPrestazioniPrestazioniSet)

public:

	CGruppiPrestazioniPrestazioniSet();

	long m_lID;
	long m_lIDGruppo;
	long m_lIDPrestazione;
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

#endif /* _GRUPPIPRESTAZIONIPRESTAZIONISET_H_ */