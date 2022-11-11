#ifndef _EXTPRESTAZIONISET_H_
	#define _EXTPRESTAZIONISET_H_

#include "BaseSet.h"

class CExtPrestazioniSet : public CBaseSet
{
	DECLARE_DYNAMIC(CExtPrestazioniSet)

public:

	CExtPrestazioniSet();

	long m_lID;
	long m_lIDOrdine;
	CString m_sIDPrestazione;			// 50
	CString m_sCodicePrestazione;		// 50
	CString m_sDescrizionePrestazione;	// 255
	CString m_sNote;					// 4000
	long m_lQuantita;
	BOOL m_bEliminato;
	CString m_sDataRichiesta;			// 14
	CString m_sNumeroRicetta;			// 50

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	// BOOL UpdateRecordset(const CString &strCommento);

	CString GetNumeroRicetta(int idExtPrestazione);

	CString GetCodice(CString sIDPrestazione);
	CString GetDescrizione(CString sIDPrestazione);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual CBaseSet* CreateNew();

};

#endif /* _EXTPRESTAZIONISET_H_ */