#ifndef _PROVENIENZASET_H_
	#define _PROVENIENZASET_H_

#include "BaseSet.h"

class CProvenienzaSet : public CBaseSet
{
	DECLARE_DYNAMIC(CProvenienzaSet)

public:

	CProvenienzaSet();

	long	m_lId;
	CString m_sDescrizione;
	CString m_sCodice;
	long	m_lIdProvenienzaEndox;
	BOOL m_bAperturaPSMDolo;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);	

	long GetInternoEsterno(long idProvenienza);
	CString GetCodiceIntegrazione(long idProvenienza);
	CString GetDescrizione(long idProvenienza);
	long GetIdFromValue(CString value);
	BOOL PSMRequired(long idProvenienza);
	long GetFirst(int InternoEsterno);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _EXTTRANSPROVENIENZASET_H_ */