#ifndef _DATABASESSET_H_
	#define _DATABASESSET_H_

#include "BaseSet.h"

class CDatabasesSet : public CBaseSet
{

	DECLARE_DYNAMIC(CDatabasesSet)

public:

	CDatabasesSet();

	long m_lID;
	CString m_sDescrizione;
	CString m_sOracleDriver;
	CString m_sServerDBQ;
	CString m_sUsername;
	CString m_sPassword;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _DATABASESSET_H_ */