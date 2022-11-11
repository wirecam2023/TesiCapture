#ifndef _ESAMICODICICLASSDIAGNOSTSET_H_
	#define _ESAMICODICICLASSDIAGNOSTSET_H_

#include "BaseSet.h"

class CEsamiCodiciClassDiagnostSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiCodiciClassDiagnostSet)

public:

	CEsamiCodiciClassDiagnostSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDCodiciClassificazioneDiag;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato)
	BOOL DeleteRecordset(const CString &strCommento);

	void AddRecord(long lIDEsame, long lIDCodiciClassificazioneDiag);
	void DelRecord(long lIDEsame, long lIDCodiciClassificazioneDiag);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ESAMICODICICLASSDIAGNOSTSET_H_ */