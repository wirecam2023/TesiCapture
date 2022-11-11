#pragma once

#include "BaseSet.h"

class CCorpoSezioneSet : public CBaseSet
{

	DECLARE_DYNAMIC(CCorpoSezioneSet)

public:

	CCorpoSezioneSet();

	long m_lID;
	long m_lIDSezione;
	long m_lIDVariante;
	CString m_sCorpoRtf;
	BOOL m_bEliminato;

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);

	virtual CString GetDefaultSQL();
	
	CString GetCorpoRtf(long lIDCorpo);
	CString GetCorpoRtf(long lIDSezione, long lIDVariante);
	BOOL SetCorpoRtf(long lIDSezione, long lIDVariante, CString sCorpo);
	
	BOOL SetEliminato(long lIDSezione, long lIDVariante);
	void GetIDList(CList<long>& listID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};