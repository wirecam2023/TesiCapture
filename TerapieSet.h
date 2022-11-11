#ifndef _TERAPIESET_H_
	#define _TERAPIESET_H_

#include "BaseSet.h"

class CTerapieSet : public CBaseSet
{
	DECLARE_DYNAMIC(CTerapieSet)

public:

	CTerapieSet();

	long		m_lContatore;
	long		m_lEsame;
	CString		m_sTerapia;
	long		m_lDurata;
	CString		m_sDurata;
	long		m_lDose;
	CString		m_sDose;
	BOOL        m_bEliminato;

	void CopyFieldFrom(CTerapieSet* pSet);
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

#endif /* _TERAPIESET_H_ */