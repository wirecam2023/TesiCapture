#ifndef _MSTSEDISET_H_
	#define _MSTSEDISET_H_

#include "BaseSet.h"

class CMstSediSet : public CBaseSet
{
	DECLARE_DYNAMIC(CMstSediSet)

public:

	CMstSediSet();

	long	m_lContatore;
	long	m_lOrgano;
	long	m_lPadre;
	CString	m_sDescrizione;
	CString m_sCodiceIntegrazione;
	BOOL    m_bEliminato;

	CString GetCodiceIntegrazione(int id);

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

#endif /* _MSTSEDISET_H_ */