//Gabriel - BUG 5533 V2 - Regras medidas biométricas
#pragma once
#include "BaseSet.h"

class CMeasurementsRulesSet : public CBaseSet
{
	DECLARE_DYNAMIC(CMeasurementsRulesSet)

public:

	CMeasurementsRulesSet();

	long m_lID;
	CString m_sName;
	long m_lIDRule;
	long m_lIDCondition;
	long m_lMeasurementCondition;
	long m_lMeasurementRule;
	CString m_sValueCondition1;
	CString m_sValueCondition2;
	long m_lUO;
	BOOL m_bEliminato;

	CString SetBaseFilter(const CString &strFilter);
	BOOL DeleteRecordset(const CString &strCommento);

	void AddRow(long lIDCondition, long lMeasurementCondition, long lIDRule, long lMeasurementRule, CString sName, CString sValueCondition1, CString sValueCondition2);
	BOOL SetEliminato(long lID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};