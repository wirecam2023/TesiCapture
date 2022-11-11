//Julio - BUG 3365 - MAMOGUS
#pragma once

#include "BaseSet.h"

class CComboPrestazioni : public CBaseSet
{

	DECLARE_DYNAMIC(CComboPrestazioni)

public:

	CComboPrestazioni();

	// mi serve per escludere i record di altre UO //
	CString SetBaseFilter(const CString &strFilter);
	BOOL DeleteRecordset(const CString &strCommento) { return FALSE; };

	long m_lID;
	CString m_sCodicePrestazione1;
	CString m_sCodicePrestazione2;
	BOOL m_bEliminato;

	void GetComboList(CString sCodicePrestazione, CList<CString>* listResult);
	

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();
	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
	
};