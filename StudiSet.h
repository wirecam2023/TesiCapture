#ifndef _STUDISET_H_
	#define _STUDISET_H_

#include "BaseSet.h"

class CStudiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CStudiSet)

public:

	CStudiSet();

	long m_lID;
	CString m_sDescrizione;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	void AddStudio(CString sDescrizione);
	void EdtStudio(long lID, CString sDescrizione);
	BOOL DelStudio(long lID);
	CString GetDescrizione(long lID);

private:

	virtual void	DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void	SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _STUDISET_H_ */