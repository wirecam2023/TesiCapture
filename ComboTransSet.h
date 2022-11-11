#ifndef _COMBOTRANSSET_H_
	#define _COMBOTRANSSET_H_

#include "BaseSet.h"

class CComboTransSet : public CBaseSet
{

	DECLARE_DYNAMIC(CComboTransSet)

public:

	CComboTransSet();

	long m_lID;
	CString m_sDescrizione;
	CString m_sExtCode;
	long m_lUO;
	BOOL m_bEliminato;

	//
	long Add(CString sDescrizione, CString sExtCode);
	void Edt(long lID, CString sDescrizione, CString sExtCode);
	BOOL Del(long lID);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	CString GetDescrizione(long lID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL() = 0;
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() = 0;
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _COMBOTRANSSET_H_ */