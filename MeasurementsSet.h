#pragma once
#include "BaseSet.h"
class CMeasurementsSet : public CBaseSet
{
	DECLARE_DYNAMIC(CMeasurementsSet)
public:
	CMeasurementsSet();
	
	long m_lID;
	long m_lIDEsame;
	CString m_sAlias;
	CString m_sNumericValue;
	CString m_sCodeValue;
	CString m_sNote;
	BOOL m_bEliminato;

	CString SetBaseFilter(const CString &strFilter);
	BOOL DeleteRecordset(const CString &strCommento);

	void AddRow(long lIDEsame, CString sAlias, CString m_sNumericValue, CString m_sCodeValue, CString sNote);
	void DelRow(long lID);	

	void UpdateExamMeasurement(long lID, CString sNumericValue, CString sCodeValue); //Julio - correcao lista biometria

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);	
};