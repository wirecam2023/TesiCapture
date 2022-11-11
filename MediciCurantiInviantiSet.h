#ifndef _MEDICICURANTISET_H_
	#define _MEDICICURANTISET_H_

#include "BaseSet.h"

class CMediciCurantiInviantiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CMediciCurantiInviantiSet)

public:

	CMediciCurantiInviantiSet(long lCurantiInvianti);

	long m_lContatore;
	CString m_sCognome;
	CString m_sNome;
	CString m_sTitolo;
	long m_lASL;
	CString m_sSede;
	CString m_sVia;
	CString m_sCitta;
	CString m_sCAP;
	CString m_sProvincia;
	CString m_sTelefono;
	CString m_sFax;
	CString m_sEmail;
	CString m_sCodiceFiscale;
	CString m_sCodiceIntegrazione;
	CString m_sLogin;
	BOOL m_bSpeciale;
	long m_lUO;
	BOOL m_bEliminato;

	// passo il contatore e mi ritorna il testo del relativo record //
	CString GetFieldText(long lContatore);
	CString GetLogin(long lContatore);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void	DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void	SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

	long m_lCurantiInvianti;

};

#endif /* _MEDICICURANTISET_H_ */