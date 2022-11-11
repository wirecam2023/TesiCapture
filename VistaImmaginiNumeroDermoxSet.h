#ifndef _VISTAIMMAGININUMERODERMOXSET_H_
	#define _VISTAIMMAGININUMERODERMOXSET_H_

#include "BaseSet.h"

class CVistaImmaginiNumeroDermoxSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaImmaginiNumeroDermoxSet)

public:

	CVistaImmaginiNumeroDermoxSet();

	long m_lID;
	long m_lNumeroDermox;
	CString m_sSede;

	long GetNumeroDermox(long lID);
	void GetNumeroDermoxSede(long lID, long& lReturn, CString& sReturn);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};

#endif /* _VISTAIMMAGININUMERODERMOXSET_H_ */