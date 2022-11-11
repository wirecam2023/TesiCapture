#ifndef _LEGENDASET_H_
	#define _LEGENDASET_H_

#include "BaseSet.h"

class CLegendaSet : public CBaseSet
{

	DECLARE_DYNAMIC(CLegendaSet)

public:

	CLegendaSet();

	long m_lUO;
	long m_lVoce;
	CString m_sValore;

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // non lascio traccia delle modifiche //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // non lascio traccia delle modifiche //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // non lascio traccia delle modifiche //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _LEGENDASET_H_ */