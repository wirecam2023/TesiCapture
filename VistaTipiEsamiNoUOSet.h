#ifndef _VISTATIPIESAMINOUOSET_H_
	#define _VISTATIPIESAMINOUOSET_H_

#include "BaseSet.h"

class CVistaTipiEsamiNoUOSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaTipiEsamiNoUOSet)

public:

	CVistaTipiEsamiNoUOSet();

	long m_lContatore;
	CString m_sDescrizioneUO;
	CString m_sDescrizioneTipoEsame;
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

#endif /* _VISTATIPIESAMINOUOSET_H_ */