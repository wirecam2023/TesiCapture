#pragma once

#include "BaseSet.h"

class CVistaCampiObbligatoriFasiNewSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaCampiObbligatoriFasiNewSet)

public:

	CVistaCampiObbligatoriFasiNewSet();

	long m_lID;
	long m_lIdTipoEsame;
	CString m_sTipoEsame;
	long m_lIdProvenienzaNew;
	CString m_sProvenienza;
	long m_lIDFaseNew;
	long m_lCampo;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
	CString SetBaseFilter(const CString &strFilter);

};
