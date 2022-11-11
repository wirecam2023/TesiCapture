#ifndef _VISTACHECKLISTSET_H_
	#define _VISTACHECKLISTSET_H_

#include "BaseSet.h"

class CVistaCheckListSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaCheckListSet)

public:

	CVistaCheckListSet();

	long m_lID;
	CString m_sCodice;
	CString m_sDescrizione;
	long m_lIDTipoEsame;
	long m_lCampoCL;
	long m_lOrdine;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _VISTACHECKLISTSET_H_ */