#ifndef _PRESTAZIONESET_H_
	#define _PRESTAZIONESET_H_

#include "BaseSet.h"

class CPrestazioneSet : public CBaseSet
{

	DECLARE_DYNAMIC(CPrestazioneSet)

public:

	CPrestazioneSet();

	CString m_sCodice;
	CString	m_sDescrizione;
	long	m_lSumQuantita;
	CString m_sInviante1;
	CString m_sInviante2;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _PRESTAZIONESET_H_ */