#ifndef _FRASIEXSET_H_
	#define _FRASIEXSET_H_

#include "BaseSet.h"

class CFrasiExSet : public CBaseSet
{

	DECLARE_DYNAMIC(CFrasiExSet)

public:

	CFrasiExSet();

	long	m_lContatore;
	long	m_lTipoEsame;
	long	m_lFamiglia;
	long	m_lPadre;
	CString m_sTitolo;
	CString m_sDescrizione;
	BOOL    m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void	DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void	SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _FRASIEXSET_H_ */