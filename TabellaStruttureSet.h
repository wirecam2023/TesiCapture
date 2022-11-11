#ifndef _TABELLASTRUTTURESET_H_
	#define _TABELLASTRUTTURESET_H_

#include "BaseSet.h"

class CTabellaStruttureSet : public CBaseSet
{

	DECLARE_DYNAMIC(CTabellaStruttureSet)

public:

	CTabellaStruttureSet();

	long m_lID;
	long m_lIDTipoEsame;
	long m_lOrdine;
	CString m_sStruttura;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	long FleuryTrans(long lIDTipoEsame, CString sStruttura);
	long GetCount(long lIDTipoEsame);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _TABELLASTRUTTURESET_H_ */