#ifndef _VITALSIGNDISPOSITIVISET_H_
#define _VITALSIGNDISPOSITIVISET_H_

#include "BaseSet.h"

class CVitalSignDispositiviSet : public CBaseSet
{
	DECLARE_DYNAMIC(CVitalSignDispositiviSet)

public:

	CVitalSignDispositiviSet();

	long m_lID;
	CString m_sDescrizione;
	CString m_sCodiceIdentificativo;	
	long m_lUO;
	BOOL m_bEliminato;	

	CString GetDescrizione(long id);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual CBaseSet* CreateNew();

};

#endif /* _VITALSIGNDISPOSITIVISET_H_ */