#ifndef _ANATOMIAPATOLOGICAINTERVSET_H_
	#define _ANATOMIAPATOLOGICAINTERVSET_H_

#include "BaseSet.h"

class CAnatomiaPatologicaIntervSet : public CBaseSet
{

	DECLARE_DYNAMIC(CAnatomiaPatologicaIntervSet)

public:

	CAnatomiaPatologicaIntervSet();

	long m_lID;
	CString m_sCodice;
	CString m_sDescrizione;
	CString m_sTipo;
	long m_lIDPrestazione;
	CString m_sDescrizioneAnatomia;
	CString m_sAPSede;
	long m_lUO;
	BOOL m_bEliminato;

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

#endif /* _ANATOMIAPATOLOGICAINTERVSET_H_ */