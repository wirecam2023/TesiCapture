#ifndef _VISTAEXTTRANSSALESET_H_
	#define _VISTAEXTTRANSSALESET_H_

#include "BaseSet.h"

class CVistaExtTransSaleSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaExtTransSaleSet)

public:

	CVistaExtTransSaleSet();

	long m_lidSalaEndox;
	long m_lidSedeEndox;
	CString m_sCodiceSalaEst;
	CString m_sDescrizione;
	long m_lUO;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /*_VISTAEXTTRANSSALESET_H_ */