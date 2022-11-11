#ifndef _ESAMICARICOANNULLATOSET_H_
#define _ESAMICARICOANNULLATOSET_H_

#include "BaseSet.h"

class CEsamiCaricoAnnullatoSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiCaricoAnnullatoSet)

public:

	CEsamiCaricoAnnullatoSet();

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

	void CEsamiCaricoAnnullatoSet::InserisciRecordForFaliure(long idUtente, long lIdLastAdd, CString sOrderNumber);//Julio Correcao do problema de exames em pacientes errados

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ESAMICARICOANNULLATOSET_H_ */