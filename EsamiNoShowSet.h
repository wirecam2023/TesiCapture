#ifndef _ESAMINOSHOWSET_H_
#define _ESAMINOSHOWSET_H_

#include "BaseSet.h"

class CEsamiNoShowSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiNoShowSet)

public:

	CEsamiNoShowSet();

	long m_lId;
	long m_lIdOrdine;
	CString m_sDataOra;
	long m_lIdUtente;
	BOOL m_bEseguito;
	CString m_sEsito;

	void InserisciRecord(long idOrdine, long idUtente);

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

#endif /* _ESAMINOSHOWSET_H_ */