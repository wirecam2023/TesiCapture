#pragma once

#include "BaseSet.h"

class CTipiMaterialiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CTipiMaterialiSet)

public:

	CTipiMaterialiSet();

	long m_lID;
	CString m_sCodice;
	CString m_sDescrizione;	
	CString m_sTestoRtf001;	
	BOOL m_bEliminato;

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);

	virtual CString GetDefaultSQL();

	CString GetCodice(long lID);
	BOOL SetCodice(long lID, CString sCodice);

	CString GetDescrizione(long lID);
	BOOL SetDescrizione(long lID, CString sDescrizione);

	CString GetTestoRtf(long lID, long lPos);
	BOOL SetTestoRtf(long lID, long lPos, CString sTesto);	

	BOOL SetEliminato(long lID);

	void GetIDList(CList<long>& listID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};
