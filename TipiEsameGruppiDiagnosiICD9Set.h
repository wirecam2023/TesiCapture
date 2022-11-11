#ifndef _TIPIESAMEGRUPPIDIAGNOSIICD9SET_H_
	#define _TIPIESAMEGRUPPIDIAGNOSIICD9SET_H_

#include "BaseSet.h"

class CTipiEsameGruppiDiagnosiICD9Set : public CBaseSet
{
	DECLARE_DYNAMIC(CTipiEsameGruppiDiagnosiICD9Set)

public:

	CTipiEsameGruppiDiagnosiICD9Set();

	long m_lID;
	long m_lIDTipoEsame; // --> legato al contatore della tabella ETipoEsame
	long m_lIDGruppo;	 // --> legato al contatore della tabella GruppiDiagnosiICD9
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

#endif /* _TIPIESAMIGRUPPIDIAGNOSIICD9SET_H_ */