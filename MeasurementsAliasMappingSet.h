#pragma once
#include "BaseSet.h"

class CMeasurementsAliasMappingSet : public CBaseSet
{	
	DECLARE_DYNAMIC(CMeasurementsAliasMappingSet)

public:
	
	CMeasurementsAliasMappingSet();

	long m_lID;
	CString m_sAlias;
	CString m_sNomeParametro;
	CString m_sVariableName;
	long m_lUO; //Gabriel - BUG 5533 V2 - Filtro por UO
	CString m_sValueType; //Gabriel - BUG 5533 V2 - Filtro por UO
	long m_lDecimals; //Gabriel - BUG 5533 V2

	BOOL m_bColumnsEspermograma; //Gabriel - BUG 5533 V2 - Filtro por UO

	CString SetBaseFilter(const CString &strFilter);
	BOOL DeleteRecordset(const CString &strCommento);

	void AddRow(CString sAlias, CString sVariableName, CString sNomeParametro, CString sValueType = "", long lDecimals = 0); //Gabriel - BUG 5533 V2
	void DelRow(long lID);

	CString GetAlias(long lID); //Gabriel - BUG 5533 V2
	long GetDecimals(long lID); //Gabriel - BUG 5533 V2
	BOOL IsNumeric(long lID); //Gabriel - BUG 5533 V2

private: 

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};