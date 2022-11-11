#ifndef _LISTAOSSERVAZIONISET_H_
	#define _LISTAOSSERVAZIONISET_H_

#include "BaseSet.h"

class CListaOsservazioniSet : public CBaseSet  
{

	DECLARE_DYNAMIC(CListaOsservazioniSet)

public:

	CListaOsservazioniSet();
	virtual ~CListaOsservazioniSet();

	long	m_lContatore;
	long	m_lData;
	CString m_sTipoEsame;
	long	m_lOrgano;
	CString m_sSede;
	CString m_sOsservazioni;

	BOOL OpenRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _LISTAOSSERVAZIONISET_H_*/