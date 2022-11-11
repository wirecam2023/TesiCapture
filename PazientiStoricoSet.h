#ifndef _PAZIENTISTORICOSET_H_
	#define _PAZIENTISTORICOSET_H_

#include "BaseSet.h"

class CPazientiStoricoSet : public CBaseSet
{
	DECLARE_DYNAMIC(CPazientiStoricoSet)

public:

	CPazientiStoricoSet();

	long	m_lId;
	long	m_lIdPaziente;
	CString m_sAssIden;
	BOOL	m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	BOOL UndeleteRecordset(const CString &strCommento);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	void	DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _PAZIENTISTORICOSET_H_ */