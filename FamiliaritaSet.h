#ifndef _FAMILIARITASET_H_
	#define _FAMILIARITASET_H_

#include "BaseSet.h"

class CFamiliaritaSet : public CBaseSet
{

	DECLARE_DYNAMIC(CFamiliaritaSet)

public:

	CFamiliaritaSet();
	
	long m_lContatore;
	long m_lPaziente;
	CString m_sFamiliarita;
	long m_lParentela;
	long m_lUO;
	BOOL m_bEliminato;

	//
	void CopyFieldFrom(CFamiliaritaSet* pSet);
	virtual void SetEmpty();

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	
	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _FAMILIARITASET_H_ */