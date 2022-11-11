#ifndef _VISTAESAMIPENDENTISET_H_
	#define _VISTAESAMIPENDENTISET_H_

#include "BaseSet.h"

class CVistaEsamiPendentiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaEsamiPendentiSet)

public:

	CVistaEsamiPendentiSet();

	CString m_sPazienteCognome;
	CString m_sPazienteNome;
	CString m_sEsameTipo;
	long m_lEsameID;
	long m_lEsameData;
	CString m_sMedicoCognome;
	CString m_sMedicoNome;
	CString m_sEsameSala;
	CString m_sInvianteMedico;
	CString m_sFicha;
	CString m_sFichaItem;
	long m_lUO;
	long m_lRefertoLen;
	CString m_sRedattoreCognome;
	CString m_sRedattoreNome;
	CString m_sTesto000;

	BOOL MedicoHasEsamiAperti(long lIDMedico);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};

#endif /* _VISTAESAMIPENDENTISET_H_ */