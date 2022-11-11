#ifndef _SALEESAMESET_H_
	#define _SALEESAMESET_H_

#include "BaseSet.h"

class CSaleEsameSet : public CBaseSet
{
	DECLARE_DYNAMIC(CSaleEsameSet)

public:

	CSaleEsameSet();

	long m_lID;
	CString m_sDescrizione;
	//CString m_sCodiceIntegrazione;
	long m_lIDSede;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	// Sandro 15/04/2014 //
	long GetIDSala(CString sDescrizione);
	long GetIdSalaFromIdSede(int lIDSede);
	//CString GetCodiceSedeEstFromIdSede(int lIDSede);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _SALEESAMESET_H_ */