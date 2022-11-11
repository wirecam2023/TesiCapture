#ifndef _ANATOMIAPATOLOGICASET_H_
	#define _ANATOMIAPATOLOGICASET_H_

#include "BaseSet.h"

class CAnatomiaPatologicaSet : public CBaseSet
{

	DECLARE_DYNAMIC(CAnatomiaPatologicaSet)

public:

	CAnatomiaPatologicaSet();

	long m_lID;
	long m_lIDEsame;
	CString m_sIDCampione;
	CString m_sTipo;
	CString m_sIntervCodice;
	CString m_sIntervProcedura;
	long m_lPrelievi;
	CString m_sDescrizione;
	CString m_sTopografia;
	CString m_sSnomed1;
	CString m_sSnomed2;
	CString m_sSnomed3;
	long m_lIDPrestazioneAssociata;
	CString m_sDescrizioneAnatomia;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	BOOL HasMaterials(long idEsame);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ANATOMIAPATOLOGICASET_H_ */