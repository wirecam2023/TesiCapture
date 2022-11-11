#ifndef _REPORTSMACROSET_H_
	#define _REPORTSMACROSET_H_

#include "BaseSet.h"

class CReportsMacroSet : public CBaseSet
{

	DECLARE_DYNAMIC(CReportsMacroSet)

public:

	CReportsMacroSet();

	long m_lID;
	CString m_sCodice;
	CString m_sDescrizione;
	long m_lImmaginiCopie;
	long m_lEtichetteIstopatologiaCopie;
	CString m_sReportDaFirmare;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	CString GetReportDaFirmare(long lID);
	long GetImmaginiCopie(long lID); // negativo niente stampa, 0 chiede quante copie stampare //
	long GetEtichetteIstopatologiaCopie(long lID); // negativo niente stampa, 0 chiede quante copie stampare //

	//
	void SetReportDaFirmare(long lID, CString sReportDaFirmare);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _REPORTSMACROSET_H_ */