#ifndef _CHECKLISTSET_H_
	#define _CHECKLISTSET_H_

#include "BaseSet.h"

class CCheckListSet : public CBaseSet
{

	DECLARE_DYNAMIC(CCheckListSet)

public:

	CCheckListSet();

	long m_lID;
	CString m_sCodice;
	CString m_sDescrizione;
	long m_lPresentazione;
	BOOL m_bItemAlmenoUno;
	BOOL m_bItemPiuDiUno;
	long m_lCampoCL;
	long m_lOrdine;
	long m_lUO;
	BOOL m_bEliminato;

	//
	BOOL GetEspansa(long lID);
	// BOOL GetSceltaMultipla(long lID);
	CString GetStringCodice(long lID);
	CString GetStringDescrizione(long lID);

	// ridefinisco DeleteRecordset (in realt� cambia flag eliminato) //
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

#endif /* _CHECKLISTSET_H_ */