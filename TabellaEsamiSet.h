#ifndef _TABELLAESAMISET_H_
	#define _TABELLAESAMISET_H_

#include "BaseSet.h"

class CTabellaEsamiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CTabellaEsamiSet)

public:

	CTabellaEsamiSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDParametro;
	float m_fValore;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	//
	long AddRow(long lIDEsame, long lIDParametro, float fValore);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _TABELLAESAMISET_H_ */