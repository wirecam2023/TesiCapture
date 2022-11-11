#ifndef _VISTAFLEURYURMSET_H_
	#define _VISTAFLEURYURMSET_H_

#include "BaseSet.h"

#define VIEW_UNIDADE 0x1001
#define VIEW_REGIONAL 0x1002
#define VIEW_MARCA 0x1003

class CVistaFleuryURMSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaFleuryURMSet)

public:

	CVistaFleuryURMSet();

	CString m_sValori;

	void SetView(long lView);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

	//

	long m_lView;
};

#endif /* _VISTAFLEURYURMSET_H_ */