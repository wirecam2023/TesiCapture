#ifndef _DIAGNOSIESAMISET_H_
	#define _DIAGNOSIESAMISET_H_

#include "BaseSet.h"

class CDiagnosiEsamiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CDiagnosiEsamiSet)

public:

	CDiagnosiEsamiSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDDiagnosi;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	void CopyFieldFrom(CDiagnosiEsamiSet* pSet);
	CString GetFieldText(long lEsame);
	CString GetStringDescrizione(long lEsame);
	BOOL Add(long lEsame, long idDiagnosi);

	virtual void SetEmpty();

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _DIAGNOSIESAMISET_H_ */