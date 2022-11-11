#ifndef _COMBORAOSET_H_
	#define _COMBORAOSET_H_

#include "BaseSet.h"

class CComboRAOSet : public CBaseSet
{

	DECLARE_DYNAMIC(CComboRAOSet)

public:

	CComboRAOSet();

	long m_lID;
	CString m_sDescrizione;
	long m_lPercentualeRicetta;
	long m_lUO;
	BOOL m_bEliminato;

	long AddRAO(CString sDescrizione);
	void EdtRAO(long lID, CString sDescrizione);
	BOOL DelRAO(long lID);

	//
	CString GetDescrizione(long lID);
	long GetPercentualeRicetta(long lID);

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

#endif /* _ANATOMIAPATOLOGICAESAMIPRESTSET_H_ */