#ifndef _VISTASTATISTICHEESAMISET_H_
	#define _VISTASTATISTICHEESAMISET_H_

#include "BaseSet.h"

class CVistaStatisticheEsamiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaStatisticheEsamiSet)

public:

	CVistaStatisticheEsamiSet(BOOL bStatisticaEsamiChiusi);

	long m_lIDEsame;
	long m_lData;
	long m_lMedico;

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

	//

	BOOL m_bStatisticaEsamiChiusi;

};

#endif /* _VISTASTATISTICHEESAMISET_H_ */