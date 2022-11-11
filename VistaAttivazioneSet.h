#ifndef _VISTAATTIVAZIONESET_H_
	#define _VISTAATTIVAZIONESET_H_

#include "BaseSet.h"

class CVistaAttivazioneSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaAttivazioneSet)

public:

	CVistaAttivazioneSet();

	CString GetDescrizione(CString sStazione);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

	// --- //

	CString m_sStazione;
	CString m_sSoftware;
	CString m_sDescrizione;

};

#endif /* _VISTAATTIVAZIONESET_H_ */