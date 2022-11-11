#ifndef _NRELOTTISET_H_
	#define _NRELOTTISET_H_

#include "BaseSet.h"

class CNRELottiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CNRELottiSet)

public:

	CNRELottiSet();

	long	m_lId;
	CString m_sRegione;
	CString m_sCodRaggruppamento;
	CString m_sCodiceLotto;
	long	m_lContatore;
	long	m_lContatoreMax;
	long	m_lIdUtente;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	BOOL DeleteRecordset(const CString &strCommento);

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _NRELOTTISET_H_ */