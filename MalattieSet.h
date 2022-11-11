#ifndef _MALATTIESET_H_
	#define _MALATTIESET_H_

#include "BaseSet.h"

class CMalattieSet : public CBaseSet
{

	DECLARE_DYNAMIC(CMalattieSet)

public:

	CMalattieSet();

	long m_lContatore;
	long m_lEsame;
	CString m_sMalattia;
	long m_lClasse;
	long m_lEpisodi;
	BOOL m_bEliminato;

	void CopyFieldFrom(CMalattieSet* pSet);
	virtual void SetEmpty();

	void GetFieldText(CString& sReturn, long lEsame);

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	
	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _MALATTIESET_H_ */