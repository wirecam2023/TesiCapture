#ifndef _TIPIESAMIPROGRESSIVOANNUALESET_H_
	#define _TIPIESAMIPROGRESSIVOANNUALESET_H_

#include "BaseSet.h"

class CTipiEsamiProgressivoAnnualeSet : public CBaseSet
{
	DECLARE_DYNAMIC(CTipiEsamiProgressivoAnnualeSet)

public:

	CTipiEsamiProgressivoAnnualeSet();

	long m_lID;
	long m_lIDSede;				// --> legato al contatore della tabella SediEsame
	long m_lIDTipoEsame;		// --> legato al contatore della tabella ETipoEsame
	long m_lContatoreAnnuale;
	long m_lAnno;
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

#endif /* _TIPIESAMIPROGRESSIVOANNUALESET_H_ */