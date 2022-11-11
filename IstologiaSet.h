#ifndef _ISTOLOGIASET_H_
	#define _ISTOLOGIASET_H_

#include "BaseSet.h"

class CIstologiaSet : public CBaseSet
{

	DECLARE_DYNAMIC(CIstologiaSet)

public:

	CIstologiaSet();

	long m_lContatore;
	long m_lEsame;
	long m_lTipo;
	long m_lOrgano;
	CString m_sProvette;
	long m_lProcedura;
	CString m_sSede;
	CString m_sDiagnosi;
	BOOL m_bEliminato;

	void CopyFieldFrom(CIstologiaSet* pSet);
	virtual void SetEmpty();

	CString GetEseguitoPrelievo(long lEsame);
	void GetFieldText(CString& sReturn, long lEsame);

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

#endif /* _ISTOLOGIASET_H_ */