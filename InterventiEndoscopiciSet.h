#ifndef _INTERVENTIENDOSCOPICISET_H_
	#define _INTERVENTIENDOSCOPICISET_H_

#include "BaseSet.h"

class CInterventiEndoscopiciSet : public CBaseSet
{
	DECLARE_DYNAMIC(CInterventiEndoscopiciSet)

public:

	CInterventiEndoscopiciSet();

	long		m_lContatore;
	long		m_lEsame;
	long		m_lClasse;
	CString		m_sIntervento;
	long		m_lIDEsameRiferimento;
	BOOL        m_bEliminato;

	void CopyFieldFrom(CInterventiEndoscopiciSet* pSet);
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

#endif /* _INTERVENTIENDOSCOPICISET_H_ */