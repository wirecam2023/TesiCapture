//Gabriel - BUG 5533 V2 - Cálculos medidas biométricas
#pragma once
#include "BaseSet.h"

class CMeasurementsCalculationSet : public CBaseSet
{
	DECLARE_DYNAMIC(CMeasurementsCalculationSet)

public:

	CMeasurementsCalculationSet();

	long m_lID;
	CString m_sName;
	long m_lIDCalc;
	long m_lMeasurement1;
	long m_lMeasurement2;
	long m_lMeasurement3;
	long m_lMeasurement4;
	float m_fValue1;
	long m_lUO;
	BOOL m_bEliminato;

	CString SetBaseFilter(const CString &strFilter);
	BOOL DeleteRecordset(const CString &strCommento);

	void AddRow(long lIDCalc, long lMeasurement1, long lMeasurement2, long lMeasurement3, long lMeasurement4, CString sName, float fValue1);
	BOOL SetEliminato(long lID);
	void GetIDList(CList<long>& listID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};