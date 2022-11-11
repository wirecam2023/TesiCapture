#ifndef _UTENTISET_H_
	#define _UTENTISET_H_

#include "BaseSet.h"

class CUtentiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CUtentiSet)

public:

	CUtentiSet();

	long m_lID;
	long m_lIDGruppo;
	CString m_sUsername;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	//
	CString GetUsername(long lID);
	long GetIdGruppo(long lID);

	long GetIDFromUsername(CString sUsername);
	long FleuryTrans(CString sUsername);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /*_UTENTISET_H_ */