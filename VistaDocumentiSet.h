#ifndef _VISTADOCUMENTISET_H_
	#define _VISTADOCUMENTISET_H_

#include "BaseSet.h"

class CVistaDocumentiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaDocumentiSet)

public:

	CVistaDocumentiSet();

	CString GetDescrizione(long lID);
	CString GetDataPersonalizzabile(long lID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

	//

	CString m_sDescrizione;
	CString m_sDataPersonalizzabile;

};

#endif /* _VISTADOCUMENTISET_H_ */