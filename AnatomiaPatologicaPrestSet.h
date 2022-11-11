#ifndef _ANATOMIAPATOLOGICAPRESTSET_H_
	#define _ANATOMIAPATOLOGICAPRESTSET_H_

#include "BaseSet.h"

class CAnatomiaPatologicaPrestSet : public CBaseSet
{

	DECLARE_DYNAMIC(CAnatomiaPatologicaPrestSet)

public:

	CAnatomiaPatologicaPrestSet();

	long m_lID;
	CString m_sPrestazione;
	CString m_sCodice;
	CString m_sDescrizione;
	CString m_sTipoEsame;
	long m_lUO;
	BOOL m_bEliminato;

	//
	CString GetFieldText(long lID);
	CString GetFieldTextComplete(long lID);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ANATOMIAPATOLOGICAPRESTSET_H_ */