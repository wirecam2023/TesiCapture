#ifndef _VISTAFARMACIGRUPPIRICSET_H_
	#define _VISTAFARMACIGRUPPIRICSET_H_

#include "BaseSet.h"

class CVistaFarmaciGruppiRicSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaFarmaciGruppiRicSet)

public:

	CVistaFarmaciGruppiRicSet();

	long m_lID;
	long m_lIDGruppo;
	CString m_sNome;
	CString m_sPrincipioAttivo;
	CString m_sDescrizione;
	long m_lQuantita;
	CString m_sTestoLibero;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};

#endif /* _VISTAFARMACIGRUPPIRICSET_H_ */