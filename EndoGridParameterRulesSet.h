#pragma once

#include "BaseSet.h"

class CEndoGridParameterRulesSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEndoGridParameterRulesSet)

public:
	CEndoGridParameterRulesSet(BOOL bJoin, CDatabase* pDatabase = NULL);

	enum RuleType
	{
		hidefield = 0,
		colorfield,
		showfield,
		valorizefield
	};

	enum OperatorType
	{
		equal = 1,
		valid,
		startwith,
		major,
		minor,
		different,
		contains,
		minor_major
	};

	long   	m_id;
	long    m_tiporegola;
	long    m_idparametro1;
	long    m_operatore;
	CString m_valore;
	long    m_idparametro2;
	CString m_valore2;
	CString m_nota;
	long    m_colore;
	long    m_ordine;
	BOOL	m_bEliminato;

	CString m_nomeparametro1;
	CString m_note1;
	long    m_fbisd1;
	CString m_nomeparametro2;
	CString m_note2;
	long    m_fbisd2;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

protected:
	virtual CString SetSortRecord(const CString& strSort);

	BOOL m_bJoin;
	
	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);
	

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};