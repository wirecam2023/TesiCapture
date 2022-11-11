#ifndef _VISTAMONITORAGGIOFARMACISET_H_
	#define _VISTAMONITORAGGIOFARMACISET_H_

#include "BaseSet.h"

class CVistaMonitoraggioFarmaciSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaMonitoraggioFarmaciSet)

public:

	CVistaMonitoraggioFarmaciSet();

	CString GetFarmaci(long lIDEsame);

private:

	long m_lIDEsame;
	CString m_sNomeFarmaco;
	CString m_sDoseFarmaco;

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};

#endif /* _VISTAMONITORAGGIOFARMACISET_H_ */