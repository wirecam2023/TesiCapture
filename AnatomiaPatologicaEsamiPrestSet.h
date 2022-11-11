#ifndef _ANATOMIAPATOLOGICAESAMIPRESTSET_H_
	#define _ANATOMIAPATOLOGICAESAMIPRESTSET_H_

#include "BaseSet.h"

class CAnatomiaPatologicaEsamiPrestSet : public CBaseSet
{

	DECLARE_DYNAMIC(CAnatomiaPatologicaEsamiPrestSet)

public:

	CAnatomiaPatologicaEsamiPrestSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDPrestazione;
	BOOL m_bEliminato;

	long AddPrestazione(long lIDEsame, long lIDPrestazione);
	void EdtPrestazione(long lID, long lIDPrestazione);
	void DelPrestazione(long lID);

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ANATOMIAPATOLOGICAESAMIPRESTSET_H_ */