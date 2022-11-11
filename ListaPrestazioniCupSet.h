#ifndef _LISTAPRESTAZIONICUPSET_H_
	#define _LISTAPRESTAZIONICUPSET_H_

#include "BaseSet.h"

class CListaPrestazioniCupSet : public CBaseSet
{

	DECLARE_DYNAMIC(CListaPrestazioniCupSet)

public:

	CListaPrestazioniCupSet();

	long m_lContatore;
	CString m_sOrderNumber;
	CString m_sRequestNumber;
	long m_lIdPrestazioneEndox;
	long m_lQuantita;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() {return NULL; };
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) {};

};

#endif /* _ANATOMIAPATOLOGICASET_H_ */