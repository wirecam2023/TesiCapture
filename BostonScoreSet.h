#ifndef _BOSTONSCORESET_H_
	#define _BOSTONSCORESET_H_

#include "BaseSet.h"

class CBostonScoreSet : public CBaseSet
{

	DECLARE_DYNAMIC(CBostonScoreSet)

public:

	CBostonScoreSet();

	long m_lID;
	long m_lValore;
	CString m_sFraseStampata;
	long m_lUO;
	BOOL m_bEliminato;

	//
	void AddEdt(long lValore, CString sDescrizione);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _BOSTONSCORESET_H_ */