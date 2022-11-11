#pragma once

#include "BaseSet.h"

class CEndoGridCLParameterSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEndoGridCLParameterSet)

public:
	CEndoGridCLParameterSet(BOOL bVersionJoin = FALSE, CDatabase* pDatabase = NULL);

	long   	m_lId;
	long	m_lIdEtichetta;
	CString m_sParameterName;
	CString m_sDescription;
	long	m_lType;
	long	m_lOrder;
	BOOL    m_bDefaultBool;
	long    m_lDefaultInt;
	float   m_fDefaultFloat;
	CString m_sDefaultString;
	long    m_lParentID;
	//long	m_lGridCLIndex;
	BOOL    m_bExpanded;
	BOOL    m_bRequired;
	BOOL    m_bChangeColor;
	CString m_sNotes;
	BOOL	m_bBold;
	long	m_lFontSize;
	//long	m_lUO;
	BOOL	m_bEliminato;
				
	enum FIELD_TYPE
	{
		type_double = 0,
		type_bool,
		type_integer,
		type_combo,
		type_date,
		type_string,
		type_combo_multi,
		//type_formula,
		type_notes,
		type_combo_fixed,
		type_date_free,
		//type_alarm,
		type_check
	};

	FIELD_TYPE GetFieldType();

	CXTPPropertyGridItem* CreateItem();
	long GetLastGridVersion();

	long Insert(CString strParameterName,
		CString strDescription,
		CString strNotes,
		long lGridIndex,
		int iFieldType,
		long lSort,
		long lParentID = -1, 
		BOOL bBold = FALSE, 
		long lFontSize = 10);

	long* GetType() { return &m_lType; }

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	void CancelUpdateRecordset(const CString &strCommento);

	float GetDefaultFloatValue(long id);
	BOOL GetDefaultBoolValue(long id);
	long GetDefaultLongValue(long id);
	CString GetDefaultValue(long id);

protected:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

	BOOL m_bVersionJoin;
};