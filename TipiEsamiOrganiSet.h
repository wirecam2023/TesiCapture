#ifndef _TIPIESAMIORGANISET_H_
	#define _TIPIESAMIORGANISET_H_

#include "BaseSet.h"

class CTipiEsamiOrganiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CTipiEsamiOrganiSet)

public:

	CTipiEsamiOrganiSet();

	long	m_lID;
	long	m_lTipoEsame;	// --> legato al contatore della tabella ETipoEsame
	long	m_lOrgano;		// --> legato al contatore della tabella EMSTOrgano
	BOOL    m_bEliminato;

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

#endif /* _TIPIESAMIORGANISET_H_ */