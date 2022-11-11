#pragma once

#include "BaseSet.h"

class CTipiRefertoSet : public CBaseSet
{

	DECLARE_DYNAMIC(CTipiRefertoSet)

public:

	CTipiRefertoSet();

	long m_lID;
	CString m_sCodice;
	CString m_sTitoloRtf;
	CString m_sTestoRtf001;	
	CString m_sTestoRtf002;
	CString m_sTestoRtf003;
	CString m_sTestoRtf004;
	CString m_sTestoRtf005;
	CString m_sTestoRtf006;
	CString m_sTestoRtf007;
	CString m_sTestoRtf008;
	CString m_sTestoRtf009;
	CString m_sTestoRtf010;
	BOOL m_bEliminato;

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);

	virtual CString GetDefaultSQL();

	CString GetCodice(long lID);
	BOOL SetCodice(long lID, CString sCodice);

	CString GetTitolo(long lID);
	BOOL SetTitolo(long lID, CString sTitolo);

	CString GetTestoRtf(long lID, long lPos);
	BOOL SetTestoRtf(long lID, long lPos, CString sTesto);
	
	BOOL SetEliminato(long lID);

	void GetIDList(CList<long>& listID);

	void GetIDTipoRefertoList(CList<long>& listID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};