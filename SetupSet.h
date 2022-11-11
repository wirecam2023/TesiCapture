#ifndef _SETUPSET_H_
	#define _SETUPSET_H_

#include "BaseSet.h"

class CSetupSet : public CBaseSet
{

	DECLARE_DYNAMIC(CSetupSet)

public:

	CSetupSet();

	long m_lUO;
	CString m_sVoce;
	CString m_sValore;

	// mi serve per escludere i record di altre UO //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // non lascio traccia delle modifiche //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // non lascio traccia delle modifiche //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // non lascio traccia delle modifiche //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; }

};

#endif /* _SETUPSET_H_ */