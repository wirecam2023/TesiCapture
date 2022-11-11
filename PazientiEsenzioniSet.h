#ifndef _PAZIENTIESENZIONISET_H_
	#define _PAZIENTIESENZIONISET_H_

#include "BaseSet.h"

class CPazientiEsenzioniSet : public CBaseSet
{
	DECLARE_DYNAMIC(CPazientiEsenzioniSet)

public:

	CPazientiEsenzioniSet();

	long m_lID;
	long m_lIDPaziente;
	long m_lIDEsenzione;
	CString m_sDataScadenza;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	BOOL InsertEsenzione(const long idPaziente, const long idEsenzione, const CString dataScadenza);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _PAZIENTIESENZIONISET_H_ */