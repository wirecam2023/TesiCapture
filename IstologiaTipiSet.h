#ifndef _ISTOLOGIATIPISET_H_
	#define _ISTOLOGIATIPISET_H_

#include "BaseSet.h"

class CIstologiaTipiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CIstologiaTipiSet)

public:

	CIstologiaTipiSet();

	long m_lID;
	CString m_sDescrizione;
	long m_lUO;
	BOOL m_bEliminato;

	//
	void Add(CString sDescrizione);
	void Edt(long lID, CString sDescrizione);
	void Del(long lID);

	CString GetDescrizione(long lID);

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

#endif /* _ISTOLOGIATIPISET_H_ */