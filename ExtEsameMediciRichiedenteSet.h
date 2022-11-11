#pragma once

#include "BaseSet.h"

class CExtEsameMediciRichiedenteSet : public CBaseSet
{
	DECLARE_DYNAMIC(CExtEsameMediciRichiedenteSet)

public:

	CExtEsameMediciRichiedenteSet();

	long m_lID;
	long m_lIDEsame;
	CString m_sDataOra;
	long m_lIDUtente;
	long m_lEseguito;
	CString m_sEsito;

	long Insert(long lIDEsame);
	BOOL DeleteRecordset(const CString &strCommento);

	CString SetBaseFilter(const CString &strFilter);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};