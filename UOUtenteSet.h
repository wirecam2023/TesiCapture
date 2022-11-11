#ifndef _UOUTENTESET_H_
	#define _UOUTENTESET_H_

#include "BaseSet.h"

class CUOUtenteSet : public CBaseSet
{
	DECLARE_DYNAMIC(CUOUtenteSet)

public:

	CUOUtenteSet();

	long m_lID;
	long m_lIDUO;
	long m_lIDUtente;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	//
	long ContaUOUtente(long lIDUtente);
	void VerificaUODefault(long lIDUtente);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual CBaseSet* CreateNew();

};

#endif /* _UOUTENTESET_H_ */