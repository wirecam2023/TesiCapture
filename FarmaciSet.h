#ifndef _FARMACISET_H_
	#define _FARMACISET_H_

#include "BaseSet.h"

class CFarmaciSet : public CBaseSet
{
	DECLARE_DYNAMIC(CFarmaciSet)

public:

	CFarmaciSet();

	long m_lID;
	CString m_sAIC;
	CString m_sNome;
	CString m_sPrincipioAttivo;
	CString m_sDescrizione;
	CString m_sClasse;
	CString m_sNota1;
	CString m_sNota2;
	CString m_sDitta;
	CString m_sCampoLibero;
	CString m_sBugiardinoRTF;
	CString m_sBugiardinoTXT;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	CString GetFarmacoRicetta(long lID);
	// CString GetNome(long lID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _FARMACISET_H_ */