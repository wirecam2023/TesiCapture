#ifndef _MSTINDICAZIONISET_H_
	#define _MSTINDICAZIONISET_H_

#include "BaseSet.h"

class CMstIndicazioniSet : public CBaseSet
{

	DECLARE_DYNAMIC(CMstIndicazioniSet)

public:

	CMstIndicazioniSet();

	long	m_lContatore;
	long	m_lTipoEsame;
	long	m_lPadre;
	CString	m_sDescrizione;
	BOOL    m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _MSTINDICAZIONISET_H_ */