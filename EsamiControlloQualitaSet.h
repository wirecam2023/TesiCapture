#ifndef _ESAMICONTROLLOQUALITASET_H_
	#define _ESAMICONTROLLOQUALITASET_H_

#include "BaseSet.h"

class CEsamiControlloQualitaSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiControlloQualitaSet)

public:

	CEsamiControlloQualitaSet();

	long m_lID;
	long m_lIDEsame;
	CString m_sDataOra;
	long m_lIDUtente;
	long m_lEseguito;
	CString m_sEsito;

	void InserisciRecord(long lIDEsame, long lIDUtente);
	void EliminaRecord(long lIDEsame, CString sEsito);

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

#endif /* _ESAMICONTROLLOQUALITASET_H_ */