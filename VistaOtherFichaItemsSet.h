#ifndef _VISTAOTHERFICHAITEMSSET_H_
	#define _VISTAOTHERFICHAITEMSSET_H_

#include "BaseSet.h"
#include "Common.h"

class CVistaOtherFichaItemsSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaOtherFichaItemsSet)

public:

	CVistaOtherFichaItemsSet();

	CString m_sFichaItem;
	CString m_sCodice;
	CString m_sDescrizione;
	long m_lIDEsameIns;
	BOOL m_bSuperlocked;
	CString m_sRefertoConiugatoPrincipale;
	CString m_sRefertoConiugatoSecondario;

	//
	CString GetFleuryListOtherFichaItems(CString sFichaItem, CList<STRUCT_FICHA_ITEM> *pListFichaItem);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //

};

#endif /* _VISTAOTHERFICHAITEMSSET_H_ */