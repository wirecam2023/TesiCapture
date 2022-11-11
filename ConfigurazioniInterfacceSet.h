#ifndef _CONFIGURAZIONIINTERFACCESET_H_
	#define _CONFIGURAZIONIINTERFACCESET_H_

#include "BaseSet.h"

class CConfigurazioniInterfacceSet : public CBaseSet
{
	DECLARE_DYNAMIC(CConfigurazioniInterfacceSet)

public:

	CConfigurazioniInterfacceSet();

	CString m_sVoce;
	CString m_sValore;
	long m_lUO;

	//
	void GetBoolValue(const CString& strVoce, BOOL& bValore);
	void GetLongValue(const CString& strVoce, long& lValore);
	void GetStringValue(const CString& strVoce, CString& strValore);
	void SetBoolValue(const CString& strVoce, const BOOL& bValore);
	void SetLongValue(const CString& strVoce, const long& lValore);
	void SetStringValue(const CString& strVoce, const CString& strValore);

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
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};

#endif /* _CONFIGURAZIONIINTERFACCESET_H_ */