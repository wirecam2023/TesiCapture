#ifndef _PREMOTAZIONIBOLZANOSET_H_
	#define _PREMOTAZIONIBOLZANOSET_H_

#include "BaseSet.h"

class CPrenotazioniBolzanoSet : public CBaseSet  
{
	DECLARE_DYNAMIC(CPrenotazioniBolzanoSet)

public:

	CPrenotazioniBolzanoSet(CAMBaseDB* pDatabase);
	virtual ~CPrenotazioniBolzanoSet();

	long	m_lToken;
	BOOL	m_bArrivato;
	CString m_sGiorno;
	CString m_sOra;
	CString	m_sStanza;
	long	m_lContatorePaziente;
	CString	m_sCognomePaziente;
	CString	m_sNomePaziente;
	CString	m_sPrestazione;
	CString m_sTitoloMedico;
	CString m_sCognomeMedico;
	CString m_sNomeMedico;
	BOOL	m_bAccettata;
	CString m_sNote;
	CString m_sReparto;

protected:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};

#endif /* _PREMOTAZIONIBOLZANOSET_H_ */