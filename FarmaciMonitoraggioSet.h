#ifndef _FARMACIMONITORAGGIOSET_H_
	#define _FARMACIMONITORAGGIOSET_H_

#include "BaseSet.h"

class CFarmaciMonitoraggioSet : public CBaseSet
{
	DECLARE_DYNAMIC(CFarmaciMonitoraggioSet)

public:

	CFarmaciMonitoraggioSet();

	long m_lID;
	CString m_sNome;
	long m_lUO;
	BOOL m_bEliminato;

	long Add(CString strDescrizione);
	void Edt(long lID, CString strDescrizione);
	void Del(long lID);

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

#endif /* _FARMACISET_H_ */