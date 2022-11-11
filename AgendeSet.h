#pragma once

#include "BaseSet.h"

class CAgendeSet : public CBaseSet
{
	DECLARE_DYNAMIC(CAgendeSet)

public:

	CAgendeSet();

	long m_lID;
	CString m_sDescrizione;
	CString m_sCodiceIntegrazione;
	long m_lIDSala;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	// Sandro 15/04/2014 //
	long GetIDSala(CString sDescrizione);
	CString GetCodiceIntegrazioneFromIdSala(int lIDSala);
	//CString GetCodiceSedeEstFromIdSede(int lIDSede);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};
