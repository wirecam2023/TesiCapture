#pragma once

#include "BaseSet.h"

class CPatogenicitaSet : public CBaseSet
{
	DECLARE_DYNAMIC(CPatogenicitaSet)

public:

	CPatogenicitaSet();

	long m_lID;
	CString m_sCodice;
	CString m_sDescrizione;	
	BOOL m_bPositivita;	
	BOOL m_bEliminato;

	
	BOOL DeleteRecordset(const CString &strCommento);	
	CString SetBaseFilter(const CString &strFilter);	
	BOOL UpdateRecordset(const CString &strCommento);	

	virtual CString GetDefaultSQL();

	CString GetCodice(long lID);
	BOOL SetCodice(long lID, CString sCodice);

	CString GetDescrizione(long lID);
	BOOL SetDescrizione(long lID, CString sDescrizione);

	BOOL GetPositivita(long lID);
	BOOL SetPositivita(long lID, BOOL bPositivita);

	BOOL GetEliminato(long lID);
	BOOL SetEliminato(long lID);

	void GetIDList(CList<long>& listID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};