#ifndef _VISTAUTENTIMEDICISET_H_
	#define _VISTAUTENTIMEDICISET_H_

#include "BaseSet.h"

class CVistaUtentiMediciSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaUtentiMediciSet)

public:

	CVistaUtentiMediciSet();

	long m_lID;
	CString m_sUsername;
	CString m_sTitolo;
	CString m_sCognome;
	CString m_sNome;

	CString GetDescrizione(long lID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //

};

#endif /* _VISTAUTENTIMEDICISET_H_ */