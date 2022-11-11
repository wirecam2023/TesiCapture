#ifndef _INDAGINIPREGRESSESET_H_
	#define _INDAGINIPREGRESSESET_H_

#include "BaseSet.h"

class CIndaginiPregresseSet : public CBaseSet
{
	DECLARE_DYNAMIC(CIndaginiPregresseSet)

public:

	CIndaginiPregresseSet();

	long m_lContatore;
	long m_lEsame;
	long m_lPatologico;
	CString m_sIndagine;
	BOOL m_bEliminato;

	void CopyFieldFrom(CIndaginiPregresseSet* pSet);
	virtual void SetEmpty();

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _INDAGINIPREGRESSESET_H_ */