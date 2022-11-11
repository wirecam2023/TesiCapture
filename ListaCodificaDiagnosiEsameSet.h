#ifndef _LISTACODIFICADIAGNOSIESAMESET_H_
	#define _LISTACODIFICADIAGNOSIESAMESET_H_

#include "BaseSet.h"

class CListaCodificaDiagnosiEsameSet : public CBaseSet  
{

	DECLARE_DYNAMIC(CListaCodificaDiagnosiEsameSet)

public:

	CListaCodificaDiagnosiEsameSet();
	virtual ~CListaCodificaDiagnosiEsameSet();

	long	m_lIDPaziente;
	long	m_lIDEsame;
	long	m_lData;
	CString m_sOrgano;
	CString m_sSede;
	CString m_sDiagnosi;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _LISTACODIFICADIAGNOSIESAMESET_H_*/