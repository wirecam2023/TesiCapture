//Julio - BUG 3365 - MAMOGUS
#pragma once

#include "BaseSet.h"

class CVistaComboPrestazioni : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaComboPrestazioni)

public:

	CVistaComboPrestazioni();
	
	long m_lIDOrdine;
	CString m_sNosologico;
	CString m_sAssiden;
	CString m_sCodicePrestazione;
	CString m_sDescrizionePrestazione;
	long m_lStatoAccettazione;
	long m_lIDEsameIns;

	CString GetCodicePrestazione(CString sNosologico);
	CString GetCodicePrestazione(long lIDOrdine);

	CString GetNosologico(long lIDOrdine);
	long GetIDEsameIns(long lIDOrdine);

	BOOL ExamHasCombo(CString sNosologico, CString sCodiceToFind);
	
	// mi serve per escludere i record di altre UO //
	CString SetBaseFilter(const CString &strFilter);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};