#ifndef _DIAGNOSISET_H_
	#define _DIAGNOSISET_H_

#include "BaseSet.h"

class CDiagnosiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CDiagnosiSet)

public:

	CDiagnosiSet();

	long		m_lContatore;
	long		m_lEsame;
	long		m_lOrgano;
	CString		m_sSede;
	CString		m_sDiagnosi;
	BOOL        m_bEliminato;

	void CopyFieldFrom(CDiagnosiSet* pSet);
	virtual void SetEmpty();

	CString GetDiagnosi(long lEsame);

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

#endif /* _DIAGNOSISET_H_ */