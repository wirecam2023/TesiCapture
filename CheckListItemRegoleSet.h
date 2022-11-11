#pragma once

#include "BaseSet.h"

class CCheckListItemRegoleSet : public CBaseSet
{
	DECLARE_DYNAMIC(CCheckListItemRegoleSet)

public:

	CCheckListItemRegoleSet();

	long m_lID;
	long m_lIDCheckListItem;
	long m_lIDCheckListItemBind;
	long m_lTipoRegola;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	//
	void AddRow(long lIDCheckListItem, long lIDCheckListItemBind, long lTipoRegola);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};