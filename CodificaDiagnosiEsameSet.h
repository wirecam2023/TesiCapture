#ifndef _CODIFICADIAGNOSIESAMESET_H_
	#define _CODIFICADIAGNOSIESAMESET_H_

#include "BaseSet.h"

class CCodificaDiagnosiEsameSet : public CBaseSet
{
	DECLARE_DYNAMIC(CCodificaDiagnosiEsameSet)

public:

	CCodificaDiagnosiEsameSet();

	long		m_lContatore;
	long		m_lEsame;
	long		m_lOrgano;
	CString		m_sSede;
	CString		m_sDiagnosiEsame;
	BOOL        m_bEliminato;

	void CopyFieldFrom(CCodificaDiagnosiEsameSet* pSet);
	virtual void SetEmpty();

	CString GetStringForQuery(long lIDEsame);

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	// Sandro 18/11/2014 //
	CString GetCodificaDiagnosiEsame(long lIDEsame);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _CODIFICADIAGNOSIESAMESET_H_ */