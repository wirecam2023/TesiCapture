#ifndef _TIPIESAMIGRUPPIPRESTAZIONISET_H_
	#define _TIPIESAMIGRUPPIPRESTAZIONISET_H_

#include "BaseSet.h"

class CTipiEsamiGruppiPrestazioniSet : public CBaseSet
{
	DECLARE_DYNAMIC(CTipiEsamiGruppiPrestazioniSet)

public:

	CTipiEsamiGruppiPrestazioniSet();

	long	m_lID;
	long	m_lTipoEsame;	// --> legato al contatore della tabella ETipoEsame
	long	m_lGruppo;		// --> legato al contatore della tabella GruppiPrestazioni
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

#endif /* _TIPIESAMIGRUPPIPRESTAZIONISET_H_ */