#ifndef _TIPIESAMIPRESTAZIONISET_H_
	#define _TIPIESAMIPRESTAZIONISET_H_

#include "BaseSet.h"

class CTipiEsamiPrestazioniSet : public CBaseSet
{
	DECLARE_DYNAMIC(CTipiEsamiPrestazioniSet)

public:

	CTipiEsamiPrestazioniSet();

	long	m_lID;
	long	m_lTipoEsame;	// --> legato al contatore della tabella ETipoEsame
	long	m_lPrestazione;	// --> legato al contatore della tabella ECodificaRegionaleEx
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

#endif /* _TIPIESAMIPRESTAZIONISET_H_ */