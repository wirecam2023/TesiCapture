#ifndef _VISTACHECKLISTITEMREGOLESET_H_
	#define _VISTACHECKLISTITEMREGOLESET_H_

#include "BaseSet.h"

class CVistaChecklistItemRegoleSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaChecklistItemRegoleSet)

public:

	CVistaChecklistItemRegoleSet();

	long m_lIDChecklist;
	long m_lIDChecklistItem;
	long m_lIDChecklistItemBind;
	long m_lTipoRegola;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _VISTACHECKLISTITEMREGOLESET_H_ */