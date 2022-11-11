#ifndef _MEDICISEDIESANESET_H_
	#define _MEDICISEDIESANESET_H_

#include "BaseSet.h"

class CMediciSediEsameSet : public CBaseSet
{

	DECLARE_DYNAMIC(CMediciSediEsameSet)

public:

	CMediciSediEsameSet();

	long m_lID;
	long m_lIDMedico;
	long m_lIDSede;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	//
	void AddRow(long lIDMedico, long lIDSede);
	void DelRow(long lIDMedico, long lIDSede);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _MEDICISEDIESANESET_H_ */